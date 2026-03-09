---

# Syslog-Sentinel: Öncelik Tabanlı IDS Simülasyonu

Bu proje, Linux tabanlı sistem günlüklerini (Syslog) işlemek ve siber güvenlik odaklı bir **Saldırı Tespit Sistemi (IDS)** simülasyonu oluşturmak amacıyla geliştirilmiş bir C uygulamasıdır. Veriler, bellek üzerinde **Öncelikli Çift Yönlü Bağlı Liste (Priority Doubly Linked List)** yapısı kullanılarak yönetilmektedir.

## 📌 Proje Özeti

Sistemde oluşan olaylar (logs), önem derecelerine göre (Severity Level) anlık olarak sınıflandırılır. Bu uygulama, binlerce satırlık log akışı içerisinde kritik güvenlik ihlallerini (örneğin; Brute Force saldırısı veya yetkisiz erişim denemeleri) otomatik olarak listenin başına (Head) taşır ve sistem yöneticisine gerçek zamanlı bir önceliklendirme sunar.

## 🛠 Teknik Mimari

Uygulama, temelinde şu veri yapısı prensiplerini barındırır:

* **Dinamik Bellek Yönetimi:** `malloc()` fonksiyonu ile her log kaydı için çalışma zamanında (Runtime) bellek tahsis edilir. Bu, belirsiz sayıdaki log akışının yönetilmesini sağlar.
* **Çift Yönlü Bağlantı:** Her düğüm (node), `nextEvent` ve `prevEvent` işaretçileri sayesinde ileri ve geri navigasyona imkan tanır.
* **Öncelik Algoritması:** Yeni eklenen veriler, önem derecelerine göre ($O(1)$ durumunda başa) listeye yerleştirilir.

## 🚀 Neden Çift Yönlü Bağlı Liste?

Projenin bu veri yapısıyla tasarlanmasının temel teknik gerekçeleri şunlardır:

1. **Geriye Dönük İz Sürme (Traceback):** Bir güvenlik alarmı durumunda, saldırının kök nedenini bulmak için `prev` işaretçileri kullanılarak geçmişe dönük hızlı analiz yapılabilir.
2. **Esnek Kapasite:** Syslog verisinin boyutu önceden kestirilemediği için statik diziler (Array) yerine bellek verimliliği sağlayan bağlı listeler tercih edilmiştir.
3. **Hızlı Müdahale:** En kritik hatalar listenin başında tutulduğu için erişim süresi minimize edilmiştir.

## 📋 Kullanılan Teknolojiler

* **Dil:** C (ISO C99 Standartları)
* **Protokol:** RFC 5424 (Syslog Standartları)
* **İşletim Sistemi Ortamı:** Linux / POSIX

## ⚙️ Kurulum ve Çalıştırma

Projeyi yerel makinenizde derlemek ve çalıştırmak için aşağıdaki adımları izleyin:

```bash
# Proje dizinine gidin
cd security_logger

# GCC ile derleyin
gcc -o syslog_sentinel security_logger.c

# Uygulamayı çalıştırın
./syslog_sentinel

```

## 📂 Dosya Yapısı

* `security_logger.c`: Tüm veri yapısı tanımlarını, öncelikli ekleme algoritmalarını ve ana simülasyonu içeren kaynak kod.
* `README.md`: Proje dökümantasyonu ve teknik açıklamalar.

---

### 💡 Kullanım Notu

Uygulama çalıştırıldığında, simüle edilen log verileri önem derecelerine göre otomatik olarak sıralanacaktır. Çıktı panelinde en üstte yer alan kayıtlar, sistemin müdahale etmesi gereken en kritik olayları temsil eder.