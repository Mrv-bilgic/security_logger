#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief AMAÇ: Linux Syslog standartlarındaki (RFC 5424) önem derecelerini
 * kod içerisinde anlamlı isimlendirmelerle temsil etmek.
 * Değişken İsimlendirme Mantığı: 'SEV_' (Severity) ön eki ile hangi seviye
 * olduğu açıkça belirtilmiştir.
 */
typedef enum {
    SEV_EMERGENCY = 0, // En yüksek öncelik: Sistem tamamen kapalı
    SEV_CRITICAL  = 2, // Kritik: Aktif bir saldırı veya donanım arızası
    SEV_ERROR     = 3, // Hata: Bir servis düzgün çalışmıyor
    SEV_WARNING   = 4, // Uyarı: Potansiyel tehdit veya risk durumu
    SEV_INFO      = 6, // Bilgilendirme: Normal sistem akış mesajları
    SEV_DEBUG     = 7  // Hata Ayıklama: Geliştiriciler için teknik detaylar
} LogSeverity;

/**
 * @brief AMAÇ: Her bir Syslog kaydını bellekte bir 'düğüm' olarak saklamak.
 * Yapı İsmi (SecurityEventNode): Sadece bir 'Node' değil, bir güvenlik olayını
 * temsil ettiği için bu isim seçilmiştir.
 */
typedef struct SecurityEventNode {
    char eventTimestamp[20];       // AMAÇ: Olayın gerçekleştiği tam saati tutar.
    LogSeverity severityRank;      // AMAÇ: Logun öncelik sırasını belirlemek için sayısal değer tutar.
    char sourceIP[16];             // AMAÇ: Olayın hangi IP adresinden kaynaklandığını kayıt altına alır.
    char logMessage[128];          // AMAÇ: Olayın detaylı metin açıklamasını saklar.
    
    // İşaretçi İsimlendirme Mantığı: 'next'/'prev' yerine 'Event' takısı eklenerek
    // olaylar arası bağ vurgulanmıştır.
    struct SecurityEventNode* nextEvent; // AMAÇ: Listede kendisinden sonra gelen (daha düşük öncelikli) olayı işaret eder.
    struct SecurityEventNode* prevEvent; // AMAÇ: Listede kendisinden önce gelen (daha yüksek öncelikli) olayı işaret eder.
} SecurityEventNode;

/**
 * @brief FONKSİYON AMACI: Bellekte yeni bir güvenlik olayı için yer ayırmak ve verileri başlatmak.
 * Neden 'createEvent'?: Fonksiyon ismi, bir olayın yaratılma sürecini doğrudan ifade eder.
 */
SecurityEventNode* createEvent(LogSeverity severity, const char* ip, const char* msg) {
    SecurityEventNode* newEvent = (SecurityEventNode*)malloc(sizeof(SecurityEventNode));
    if (newEvent == NULL) {
        printf("Kritik Hata: Bellek ayrilamadi!\n");
        return NULL;
    }

    // Zaman Damgası: ssn:dd:ss formatında otomatik alınır.
    time_t rawTime = time(NULL);
    struct tm* timeInfo = localtime(&rawTime);
    strftime(newEvent->eventTimestamp, 20, "%H:%M:%S", timeInfo);

    newEvent->severityRank = severity;
    strncpy(newEvent->sourceIP, ip, 16);
    strncpy(newEvent->logMessage, msg, 128);
    
    newEvent->nextEvent = NULL;
    newEvent->prevEvent = NULL;
    return newEvent;
}

/**
 * @brief FONKSİYON AMACI: Gelen logu önem derecesine göre (Priority) listenin doğru konumuna yerleştirmek.
 * Neden 'processAndInsert'?: Sadece ekleme yapmaz, önce logu 'işler' (önceliğine bakar), sonra 'yerleştirir'.
 */
void processAndInsertLog(SecurityEventNode** head, LogSeverity severity, const char* ip, const char* msg) {
    SecurityEventNode* newNode = createEvent(severity, ip, msg);
    
    // DURUM 1: Liste boşsa veya yeni log en yüksek önceliğe sahipse (severity değeri en küçükse)
    if (*head == NULL || (*head)->severityRank > severity) {
        newNode->nextEvent = *head;
        if (*head != NULL) (*head)->prevEvent = newNode;
        *head = newNode;
        return;
    }

    // DURUM 2: Listenin içine, uygun öncelik sırasına göre yerleştirme (Priority Insertion)
    SecurityEventNode* current = *head;
    while (current->nextEvent != NULL && current->nextEvent->severityRank <= severity) {
        current = current->nextEvent;
    }

    newNode->nextEvent = current->nextEvent;
    if (current->nextEvent != NULL) {
        current->nextEvent->prevEvent = newNode;
    }
    current->nextEvent = newNode;
    newNode->prevEvent = current;
}

/**
 * @brief FONKSİYON AMACI: Bellekteki tüm logları tablo halinde kullanıcıya sunmak.
 */
void displaySecurityDashboard(SecurityEventNode* head) {
    printf("\n>>> [ SYS-SENTINEL GÜVENLIK IZLEME PANELI ] <<<\n");
    printf("%-10s | %-10s | %-15s | %-s\n", "SAAT", "ÖNCELIK", "KAYNAK IP", "OLAY MESAJI");
    printf("----------------------------------------------------------------------\n");
    
    SecurityEventNode* iterator = head; // 'iterator' ismi listenin üzerinde gezindiğini belirtir.
    while (iterator != NULL) {
        printf("%-10s | %-10d | %-15s | %-s\n",
               iterator->eventTimestamp, iterator->severityRank,
               iterator->sourceIP, iterator->logMessage);
        iterator = iterator->nextEvent;
    }
}

int main() {
    // 'alertQueue' (Alarm Kuyruğu): İsmi, verilerin bir kuyruk mantığında beklediğini belirtir.
    SecurityEventNode* alertQueue = NULL;

    // ÖRNEK VERİ AKIŞI (Simülasyon)
    processAndInsertLog(&alertQueue, SEV_INFO, "192.168.1.10", "Sistem rutin kontrolü yapildi.");
    processAndInsertLog(&alertQueue, SEV_WARNING, "192.168.1.45", "Süpheli oturum açma denemesi.");
    
    // Kritik bir olay simüle ediliyor - Listenin en başına fırlamalı!
    processAndInsertLog(&alertQueue, SEV_EMERGENCY, "10.0.0.99", "KRITIK: SQL Injection saldirisi tespit edildi!");

    processAndInsertLog(&alertQueue, SEV_ERROR, "192.168.1.2", "Firewall servisi durduruldu!");

    // Sonuçları görselleştir
    displaySecurityDashboard(alertQueue);

    return 0;
}
