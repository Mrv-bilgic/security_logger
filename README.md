{\rtf1\ansi\ansicpg1254\cocoartf2868
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\froman\fcharset0 Times-Bold;\f1\froman\fcharset0 Times-Roman;\f2\fmodern\fcharset0 Courier;
}
{\colortbl;\red255\green255\blue255;\red0\green0\blue0;\red109\green109\blue109;}
{\*\expandedcolortbl;;\cssrgb\c0\c0\c0;\cssrgb\c50196\c50196\c50196;}
{\*\listtable{\list\listtemplateid1\listhybrid{\listlevel\levelnfc23\levelnfcn23\leveljc0\leveljcn0\levelfollow0\levelstartat0\levelspace360\levelindent0{\*\levelmarker \{disc\}}{\leveltext\leveltemplateid1\'01\uc0\u8226 ;}{\levelnumbers;}\fi-360\li720\lin720 }{\listname ;}\listid1}
{\list\listtemplateid2\listhybrid{\listlevel\levelnfc0\levelnfcn0\leveljc0\leveljcn0\levelfollow0\levelstartat1\levelspace360\levelindent0{\*\levelmarker \{decimal\}}{\leveltext\leveltemplateid101\'01\'00;}{\levelnumbers\'01;}\fi-360\li720\lin720 }{\listname ;}\listid2}
{\list\listtemplateid3\listhybrid{\listlevel\levelnfc23\levelnfcn23\leveljc0\leveljcn0\levelfollow0\levelstartat0\levelspace360\levelindent0{\*\levelmarker \{disc\}}{\leveltext\leveltemplateid201\'01\uc0\u8226 ;}{\levelnumbers;}\fi-360\li720\lin720 }{\listname ;}\listid3}
{\list\listtemplateid4\listhybrid{\listlevel\levelnfc23\levelnfcn23\leveljc0\leveljcn0\levelfollow0\levelstartat0\levelspace360\levelindent0{\*\levelmarker \{disc\}}{\leveltext\leveltemplateid301\'01\uc0\u8226 ;}{\levelnumbers;}\fi-360\li720\lin720 }{\listname ;}\listid4}}
{\*\listoverridetable{\listoverride\listid1\listoverridecount0\ls1}{\listoverride\listid2\listoverridecount0\ls2}{\listoverride\listid3\listoverridecount0\ls3}{\listoverride\listid4\listoverridecount0\ls4}}
\paperw11900\paperh16840\margl1440\margr1440\vieww28260\viewh17660\viewkind0
\deftab720
\pard\pardeftab720\sa321\partightenfactor0

\f0\b\fs48 \cf0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 Syslog-Sentinel: \'d6ncelik Tabanl\uc0\u305  IDS Sim\'fclasyonu\
\pard\pardeftab720\sa240\partightenfactor0

\f1\b0\fs24 \cf0 Bu proje, Linux tabanl\uc0\u305  sistem g\'fcnl\'fcklerini (Syslog) i\u351 lemek ve siber g\'fcvenlik odakl\u305  bir 
\f0\b Sald\uc0\u305 r\u305  Tespit Sistemi (IDS)
\f1\b0 sim\'fclasyonu olu\uc0\u351 turmak amac\u305 yla geli\u351 tirilmi\u351  bir C uygulamas\u305 d\u305 r. Veriler, bellek \'fczerinde 
\f0\b \'d6ncelikli \'c7ift Y\'f6nl\'fc Ba\uc0\u287 l\u305  Liste (Priority Doubly Linked List)
\f1\b0  yap\uc0\u305 s\u305  kullan\u305 larak y\'f6netilmektedir.\
\pard\pardeftab720\sa298\partightenfactor0

\f0\b\fs36 \cf0 \uc0\u55357 \u56524  Proje \'d6zeti\
\pard\pardeftab720\sa240\partightenfactor0

\f1\b0\fs24 \cf0 Sistemde olu\uc0\u351 an olaylar (logs), \'f6nem derecelerine g\'f6re (Severity Level) anl\u305 k olarak s\u305 n\u305 fland\u305 r\u305 l\u305 r. Bu uygulama, binlerce sat\u305 rl\u305 k log ak\u305 \u351 \u305  i\'e7erisinde kritik g\'fcvenlik ihlallerini (\'f6rne\u287 in; Brute Force sald\u305 r\u305 s\u305  veya yetkisiz eri\u351 im denemeleri) otomatik olarak listenin ba\u351 \u305 na (Head) ta\u351 \u305 r ve sistem y\'f6neticisine ger\'e7ek zamanl\u305  bir \'f6nceliklendirme sunar.\
\pard\pardeftab720\sa298\partightenfactor0

\f0\b\fs36 \cf0 \uc0\u55357 \u57056  Teknik Mimari\
\pard\pardeftab720\sa240\partightenfactor0

\f1\b0\fs24 \cf0 Uygulama, temelinde \uc0\u351 u veri yap\u305 s\u305  prensiplerini bar\u305 nd\u305 r\u305 r:\
\pard\tx220\tx720\pardeftab720\li720\fi-720\sa240\partightenfactor0
\ls1\ilvl0
\f0\b \cf0 \kerning1\expnd0\expndtw0 \outl0\strokewidth0 {\listtext	\uc0\u8226 	}\expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 Dinamik Bellek Y\'f6netimi:
\f1\b0  
\f2\fs26 malloc()
\f1\fs24  fonksiyonu ile her log kayd\uc0\u305  i\'e7in \'e7al\u305 \u351 ma zaman\u305 nda (Runtime) bellek tahsis edilir. Bu, belirsiz say\u305 daki log ak\u305 \u351 \u305 n\u305 n y\'f6netilmesini sa\u287 lar.\
\ls1\ilvl0
\f0\b \kerning1\expnd0\expndtw0 \outl0\strokewidth0 {\listtext	\uc0\u8226 	}\expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 \'c7ift Y\'f6nl\'fc Ba\uc0\u287 lant\u305 :
\f1\b0  Her d\'fc\uc0\u287 \'fcm (node), 
\f2\fs26 nextEvent
\f1\fs24  ve 
\f2\fs26 prevEvent
\f1\fs24  i\uc0\u351 aret\'e7ileri sayesinde ileri ve geri navigasyona imkan tan\u305 r.\
\ls1\ilvl0
\f0\b \kerning1\expnd0\expndtw0 \outl0\strokewidth0 {\listtext	\uc0\u8226 	}\expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 \'d6ncelik Algoritmas\uc0\u305 :
\f1\b0  Yeni eklenen veriler, \'f6nem derecelerine g\'f6re (O(1) durumunda ba\uc0\u351 a) listeye yerle\u351 tirilir.\
\pard\pardeftab720\sa298\partightenfactor0

\f0\b\fs36 \cf0 \uc0\u55357 \u56960  Neden \'c7ift Y\'f6nl\'fc Ba\u287 l\u305  Liste?\
\pard\pardeftab720\sa240\partightenfactor0

\f1\b0\fs24 \cf0 Projenin bu veri yap\uc0\u305 s\u305 yla tasarlanmas\u305 n\u305 n temel teknik gerek\'e7eleri \u351 unlard\u305 r:\
\pard\tx220\tx720\pardeftab720\li720\fi-720\sa240\partightenfactor0
\ls2\ilvl0
\f0\b \cf0 \kerning1\expnd0\expndtw0 \outl0\strokewidth0 {\listtext	1	}\expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 Geriye D\'f6n\'fck \uc0\u304 z S\'fcrme (Traceback):
\f1\b0  Bir g\'fcvenlik alarm\uc0\u305  durumunda, sald\u305 r\u305 n\u305 n k\'f6k nedenini bulmak i\'e7in 
\f2\fs26 prev
\f1\fs24 i\uc0\u351 aret\'e7ileri kullan\u305 larak ge\'e7mi\u351 e d\'f6n\'fck h\u305 zl\u305  analiz yap\u305 labilir.\
\ls2\ilvl0
\f0\b \kerning1\expnd0\expndtw0 \outl0\strokewidth0 {\listtext	2	}\expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 Esnek Kapasite:
\f1\b0  Syslog verisinin boyutu \'f6nceden kestirilemedi\uc0\u287 i i\'e7in statik diziler (Array) yerine bellek verimlili\u287 i sa\u287 layan ba\u287 l\u305  listeler tercih edilmi\u351 tir.\
\ls2\ilvl0
\f0\b \kerning1\expnd0\expndtw0 \outl0\strokewidth0 {\listtext	3	}\expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 H\uc0\u305 zl\u305  M\'fcdahale:
\f1\b0  En kritik hatalar listenin ba\uc0\u351 \u305 nda tutuldu\u287 u i\'e7in eri\u351 im s\'fcresi minimize edilmi\u351 tir.\
\pard\pardeftab720\sa298\partightenfactor0

\f0\b\fs36 \cf0 \uc0\u55357 \u56523  Kullan\u305 lan Teknolojiler\
\pard\tx220\tx720\pardeftab720\li720\fi-720\sa240\partightenfactor0
\ls3\ilvl0
\fs24 \cf0 \kerning1\expnd0\expndtw0 \outl0\strokewidth0 {\listtext	\uc0\u8226 	}\expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 Dil:
\f1\b0  C (ISO C99 Standartlar\uc0\u305 )\
\ls3\ilvl0
\f0\b \kerning1\expnd0\expndtw0 \outl0\strokewidth0 {\listtext	\uc0\u8226 	}\expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 Protokol:
\f1\b0  RFC 5424 (Syslog Standartlar\uc0\u305 )\
\ls3\ilvl0
\f0\b \kerning1\expnd0\expndtw0 \outl0\strokewidth0 {\listtext	\uc0\u8226 	}\expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 \uc0\u304 \u351 letim Sistemi Ortam\u305 :
\f1\b0  Linux / POSIX\
\pard\pardeftab720\sa298\partightenfactor0

\f0\b\fs36 \cf0 \uc0\u9881 \u65039  Kurulum ve \'c7al\u305 \u351 t\u305 rma\
\pard\pardeftab720\sa240\partightenfactor0

\f1\b0\fs24 \cf0 Projeyi yerel makinenizde derlemek ve \'e7al\uc0\u305 \u351 t\u305 rmak i\'e7in a\u351 a\u287 \u305 daki ad\u305 mlar\u305  izleyin:\
\pard\pardeftab720\partightenfactor0
\cf0 Bash\
\
\pard\pardeftab720\partightenfactor0

\f2\fs26 \cf0 # Proje dizinine gidin\
cd security_logger\
\
# GCC ile derleyin\
gcc -o syslog_sentinel security_logger.c\
\
# Uygulamay\uc0\u305  \'e7al\u305 \u351 t\u305 r\u305 n\
./syslog_sentinel\
\
\pard\pardeftab720\sa298\partightenfactor0

\f0\b\fs36 \cf0 \uc0\u55357 \u56514  Dosya Yap\u305 s\u305 \
\pard\tx220\tx720\pardeftab720\li720\fi-720\sa240\partightenfactor0
\ls4\ilvl0
\f2\b0\fs26 \cf0 \kerning1\expnd0\expndtw0 \outl0\strokewidth0 {\listtext	\uc0\u8226 	}\expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 security_logger.c
\f1\fs24 : T\'fcm veri yap\uc0\u305 s\u305  tan\u305 mlar\u305 n\u305 , \'f6ncelikli ekleme algoritmalar\u305 n\u305  ve ana sim\'fclasyonu i\'e7eren kaynak kod.\
\ls4\ilvl0
\f2\fs26 \kerning1\expnd0\expndtw0 \outl0\strokewidth0 {\listtext	\uc0\u8226 	}\expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 README.md
\f1\fs24 : Proje d\'f6k\'fcmantasyonu ve teknik a\'e7\uc0\u305 klamalar.\
\pard\pardeftab720\partightenfactor0
\cf3 \strokec3 \
\pard\pardeftab720\sa280\partightenfactor0

\f0\b\fs28 \cf0 \strokec2 \uc0\u55357 \u56481  Kullan\u305 m Notu\
\pard\pardeftab720\sa240\partightenfactor0

\f1\b0\fs24 \cf0 Uygulama \'e7al\uc0\u305 \u351 t\u305 r\u305 ld\u305 \u287 \u305 nda, sim\'fcle edilen log verileri \'f6nem derecelerine g\'f6re otomatik olarak s\u305 ralanacakt\u305 r. \'c7\u305 kt\u305  panelinde en \'fcstte yer alan kay\u305 tlar, sistemin m\'fcdahale etmesi gereken en kritik olaylar\u305  temsil eder.\
}