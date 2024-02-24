#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>//srand() fonksiyonu icin
#include <unistd.h>//sleep() fonksiyonu icin


typedef struct hayvan
{
    int sayi;
    int verdigiUrunMiktari;
    int aclikDurumu;
    int alis;
    int satis;
}hayvan_t;

typedef struct hayvanlar
{
    hayvan_t inek;
    hayvan_t koyun;
    hayvan_t tavuk;
}hayvanlar_t;

typedef struct yem
{
    float miktar;
    float fiyat;
}yem_t;

typedef struct yemler
{
    yem_t hazirYem;
    yem_t yonca;
    yem_t saman;
    yem_t bugday;
}yemler_t;

typedef struct ciftlik
{
    int kasa;
    hayvanlar_t hayvanToplulugu;
    yemler_t yemBilgileri;
}ciftlik_t;

void clrscr() //Console Ekranini Temizlemek Icin Kullanilan Fonksiyon. Ref : https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
{
    system("@cls||clear");
}
void nasilOynanir()
{
    printf("\n\n\n\n\t\t\t\t\t###CIFTLIK SIMULASYONU OYUNUMUZA HOSGELDINIZ###\n");
    printf("Asagida verilen miktarlarda baslangic urunleriniz, bir miktar paraniz ve hayvanlariniz bulunmaktadir.\n");
    printf("Verilen seceneklerden istediginiz sekilde ilerleyerek iflas etmeden ve olabildigince fazla hayvan ile oyunu surdurmeye calisiniz.\n");
    printf("Zaman ilerletmeyi sectiginizde:\n");
    printf("-Hayvanlarinizin bazilari hastalanip olebilir.\n");
    printf("-Hayvanlariniz urun verebilir.\n");
    printf("-Hayvanlariniz acikabilir.\n");
    printf("-Ciftlik normal surecinde devam edebilir.");
    printf("\n-Eger aclik seviyesi 5 olursa bir hayvaninizi kaybedersiniz ve aclik sifirlanir.");
    printf("\nAlim-Satim yaparken dikkatli olunuz. Kasaniz sifirin altina duserse ve ayni zamanda tum hayvanlarinizi kaybederseniz oyun biter.");
    printf("\nOyunu kazanmak icin:");
    printf("\n\t-Toplam hayvan sayisi 500'den fazla ve ayni zamanda,");
    printf("\n\t-Kasa 500.000 TL'den fazla olmalidir.");
}
ciftlik_t* ciftlikOlustur()//oyun baslatildiginde benim tarafimdan girilen default degerler bir ciftlige atanir.
{
    ciftlik_t* yeniCiftlik = malloc(sizeof(ciftlik_t)); //ciftlik icin bellekte dinamik yer ayirtilir.
    //Ilk degerler atanir.
    yeniCiftlik->hayvanToplulugu.inek.sayi = 10;
    yeniCiftlik->hayvanToplulugu.inek.verdigiUrunMiktari = 0;
    yeniCiftlik->hayvanToplulugu.inek.aclikDurumu = 0;
    yeniCiftlik->hayvanToplulugu.inek.alis = 5000;
    yeniCiftlik->hayvanToplulugu.inek.satis = 10000;

    yeniCiftlik->hayvanToplulugu.koyun.sayi = 10;
    yeniCiftlik->hayvanToplulugu.koyun.verdigiUrunMiktari = 0;
    yeniCiftlik->hayvanToplulugu.koyun.aclikDurumu = 0;
    yeniCiftlik->hayvanToplulugu.koyun.alis = 800;
    yeniCiftlik->hayvanToplulugu.koyun.satis = 1500;

    yeniCiftlik->hayvanToplulugu.tavuk.sayi = 10;
    yeniCiftlik->hayvanToplulugu.tavuk.aclikDurumu = 0;
    yeniCiftlik->hayvanToplulugu.tavuk.verdigiUrunMiktari = 0;
    yeniCiftlik->hayvanToplulugu.tavuk.alis = 5;
    yeniCiftlik->hayvanToplulugu.tavuk.satis = 40;

    yeniCiftlik->yemBilgileri.hazirYem.fiyat = 2;
    yeniCiftlik->yemBilgileri.hazirYem.miktar = 100;
    yeniCiftlik->yemBilgileri.yonca.fiyat = 0.50;
    yeniCiftlik->yemBilgileri.yonca.miktar = 100;
    yeniCiftlik->yemBilgileri.bugday.fiyat = 1.5;
    yeniCiftlik->yemBilgileri.bugday.miktar = 100;
    yeniCiftlik->yemBilgileri.saman.fiyat = 0.1;
    yeniCiftlik->yemBilgileri.saman.miktar = 100;


    yeniCiftlik->kasa = 10000;
}
void ciftlikBilgisiGoster(ciftlik_t* ciftlik) // Ciftligin son durumunu kullaniciya gosterir.
{
    printf("\n\n###Ciftlik Durumu###\n");
    printf("#Hayvanlar         #Aclik Durumlari     #Kalan Yemler           #Urunler                   #Kasa\n");
    printf("@Inek: %d adet     @Inek: %d            @Hazir Yem: %.2f kg     @Inek Sutu: %d lt          %d TL",ciftlik->hayvanToplulugu.inek.sayi,ciftlik->hayvanToplulugu.inek.aclikDurumu,ciftlik->yemBilgileri.hazirYem.miktar,ciftlik->hayvanToplulugu.inek.verdigiUrunMiktari,ciftlik->kasa);
    printf("\n@Koyun: %d adet    @Koyun: %d           @Bugday: %.2f kg        @Koyun Sutu: %d lt\n",ciftlik->hayvanToplulugu.koyun.sayi,ciftlik->hayvanToplulugu.koyun.aclikDurumu,ciftlik->yemBilgileri.bugday.miktar,ciftlik->hayvanToplulugu.koyun.verdigiUrunMiktari);
    printf("@Tavuk: %d adet    @Tavuk: %d           @Yonca %.2f kg          @Yumurta: %d tane\n",ciftlik->hayvanToplulugu.tavuk.sayi,ciftlik->hayvanToplulugu.tavuk.aclikDurumu,ciftlik->yemBilgileri.yonca.miktar,ciftlik->hayvanToplulugu.tavuk.verdigiUrunMiktari);
    printf("                                       @Saman %.2f kg\n",ciftlik->yemBilgileri.saman.miktar);


}
void secenekMenusuYazdir()//Secenekleri gosterir.
{
    printf("\n");
    printf("Ne Yapmak Istersin?");
    printf("\n1-)Zaman Ilerlesin");
    printf("\n2-)Hayvan Besle");
    printf("\n3-)Hayvan Sat");
    printf("\n4-)Hayvan Al");
    printf("\n5-)Mahsul Sat");
    printf("\n6-)Yem Satin Al");
    printf("\n7-)Iflas Ver\n");
}
void hayvanAcikir(ciftlik_t* ciftlik)//Icerisinde uretilen rastgele sayilara gore hayvanlardaan bir grub acikir. Eger hayvan kalmadiysa acikilma olmaz.
{
    int rastgeleSayi;
    rastgeleSayi= rand()%30;
    if(rastgeleSayi>=0 && rastgeleSayi<=10 && ciftlik->hayvanToplulugu.inek.sayi>0)
    {
        //Inek acikir
        printf("\nNE OLDU?  : Inekleriniz acikti ");
        ciftlik->hayvanToplulugu.inek.aclikDurumu++;
    }
    else if(rastgeleSayi>10 && rastgeleSayi<=20 && ciftlik->hayvanToplulugu.koyun.sayi>0)
    {
        //Koyun acikir
        printf("\nNE OLDU?  : Koyunlariniz acikti ");
        ciftlik->hayvanToplulugu.koyun.aclikDurumu++;
    }
    else if(rastgeleSayi>20 && rastgeleSayi<=30 && ciftlik->hayvanToplulugu.tavuk.sayi>0)
    {
        //Tavuk acikir
        printf("\nNE OLDU?  : Tavuklariniz acikti ");
        ciftlik->hayvanToplulugu.tavuk.aclikDurumu++;
    }
    else if(ciftlik->hayvanToplulugu.inek.sayi+ ciftlik->hayvanToplulugu.tavuk.sayi + ciftlik->hayvanToplulugu.koyun.sayi == 0)
        printf("Hic Hayvan Yok. Hayvan Alacak Paraniz Yok Mu ?");
    else // Herhangi bir bug durumunda bu statement'a girilir.
        printf("\nNE OLDU? : Hayvanlar Uretime Devam Ediyor.");
}
void hayvanOldu(ciftlik_t* ciftlik)//Sansiz bir giris yapildiginde kullanici hayvanlarindan birini kaybeder. Rastgele uretilen sayi hangi hayvanin kaybedilecegine karar verir.
{
    int rastgeleSayi;
    rastgeleSayi= rand()%30;
    if(rastgeleSayi<=10 && ciftlik->hayvanToplulugu.inek.sayi>0)
    {
        //Inek ölür
        printf("\nNE OLDU? : Malesef 1 Adet Inek Kaybettiniz.");
        ciftlik->hayvanToplulugu.inek.sayi--;
    }

    else if(rastgeleSayi>10 && rastgeleSayi<=20 && ciftlik->hayvanToplulugu.koyun.sayi>0)
    {
        //Koyun ölür
        printf("\nNE OLDU? : Malesef 1 Adet Koyun Kaybettiniz.");
        ciftlik->hayvanToplulugu.koyun.sayi--;
    }
    else if(rastgeleSayi>20 && rastgeleSayi<=30 && ciftlik->hayvanToplulugu.tavuk.sayi>0)
    {
        //Tavuk ölür
        printf("\nNE OLDU? : Malesef 1 Adet Tavuk Kaybettiniz.");
        ciftlik->hayvanToplulugu.tavuk.sayi--;
    } else if(ciftlik->hayvanToplulugu.koyun.sayi+ ciftlik->hayvanToplulugu.inek.sayi + ciftlik->hayvanToplulugu.tavuk.sayi == 0)
        printf("Hic Hayvan Yok. Hayvan Alacak Paraniz Yok Mu ?");
    else
        printf("\nNE OLDU? : Hayvanlar Uretime Devam Ediyor.");
}
void uretimYapildi(ciftlik_t* ciftlik)//Hayvanlar rastgele uretilen sayilara gore yine rastgele bir miktarda urun uretirler. Hayvanlarin uretebilecegi maksimumum urunler sinirlandirilmistir.
{
    int rastgeleSayi;
    rastgeleSayi= rand()%30;
    if(rastgeleSayi<=10 && ciftlik->hayvanToplulugu.inek.sayi>0)
    {
        int rastSayi2 = rand()%25+1;
        printf("\nSanslisiniz! Her inek %d lt sut uretti.",rastSayi2);
        ciftlik->hayvanToplulugu.inek.verdigiUrunMiktari += ciftlik->hayvanToplulugu.inek.sayi*rastSayi2;
    }
    else  if(rastgeleSayi<=20  && rastgeleSayi>10 && ciftlik->hayvanToplulugu.koyun.sayi>0)
    {
        int rastSayi2 = rand()%5+1;
        printf("\nSanslisiniz! Her koyun %d lt sut uretti.",rastSayi2);
        ciftlik->hayvanToplulugu.koyun.verdigiUrunMiktari += ciftlik->hayvanToplulugu.koyun.sayi*rastSayi2;
    }
    else  if(rastgeleSayi<=30  && rastgeleSayi>20 && ciftlik->hayvanToplulugu.tavuk.sayi>0)
    {
        printf("\nSanslisiniz! Her tavuk 1 tane yumurta yumurtladi.");
        ciftlik->hayvanToplulugu.tavuk.verdigiUrunMiktari += ciftlik->hayvanToplulugu.tavuk.sayi;
    } else if(ciftlik->hayvanToplulugu.inek.sayi+ ciftlik->hayvanToplulugu.tavuk.sayi + ciftlik->hayvanToplulugu.koyun.sayi == 0)
        printf("Hic Hayvan Yok. Hayvan Alacak Paraniz Yok Mu ?");
    else
        printf("\nNE OLDU? : Hayvanlar Uretime Devam Ediyor.");
}
void hayvanBesle(ciftlik_t* ciftlik)//Hayvanlar kullanicinin tercih ettigi besin ile beslenirler.
{
    printf("\nHangi Hayvani Besleyeceksiniz ?");
    printf("\n1-Inek");
    printf("\n2-Koyun");
    printf("\n3-Tavuk\n");

    int cevap = 0;
    scanf("%d",&cevap);

    if(cevap == 1 && ciftlik->hayvanToplulugu.inek.sayi>0)
    {
        printf("1-)Saman(20kg) , 2-)Yem(10kg) --> Her inek icin\n");
        int cevap2 = 0;
        scanf("%d",&cevap2);
        if(cevap2 == 1)
        {
            if(ciftlik->hayvanToplulugu.inek.sayi*20 <= ciftlik->yemBilgileri.saman.miktar)
            {
                printf("Inekler Beslendi.");
                ciftlik->hayvanToplulugu.inek.aclikDurumu = 0;
                ciftlik->yemBilgileri.saman.miktar-=ciftlik->hayvanToplulugu.inek.sayi*20;
            }else{
                printf("Yeterli Saman Yok.");
            }
        }else if(cevap2 == 2)
        {
            if(ciftlik->hayvanToplulugu.inek.sayi*10 <= ciftlik->yemBilgileri.hazirYem.miktar)
            {
                printf("Inekler Beslendi.");
                ciftlik->hayvanToplulugu.inek.aclikDurumu = 0;
                ciftlik->yemBilgileri.hazirYem.miktar-=ciftlik->hayvanToplulugu.inek.sayi*10;
            }else{
                printf("Yeterli Yem Yok.");
            }
        }

    }else if(cevap == 2 && ciftlik->hayvanToplulugu.koyun.sayi>0)
    {
        printf("1-)Yonca(10kg) , 2-)Yem(5kg) --> Her koyun icin\n");
        int cevap2 = 0;
        scanf("%d",&cevap2);
        if(cevap2 == 1)
        {
            if(ciftlik->hayvanToplulugu.koyun.sayi*10 <= ciftlik->yemBilgileri.yonca.miktar)
            {
                printf("Koyunlar Beslendi.");
                ciftlik->hayvanToplulugu.koyun.aclikDurumu = 0;
                ciftlik->yemBilgileri.yonca.miktar-=ciftlik->hayvanToplulugu.koyun.sayi*10;
            }else{
                printf("Yeterli Yonca Yok.");
            }
        }else if(cevap2 == 2)
        {
            if(ciftlik->hayvanToplulugu.koyun.sayi*5 <= ciftlik->yemBilgileri.hazirYem.miktar)
            {
                printf("Koyunlar Beslendi.");
                ciftlik->hayvanToplulugu.koyun.aclikDurumu = 0;
                ciftlik->yemBilgileri.hazirYem.miktar-=ciftlik->hayvanToplulugu.koyun.sayi*5;
            }else{
                printf("Yeterli Yem Yok.");
            }
        }

    }else if(cevap == 3 && ciftlik->hayvanToplulugu.tavuk.sayi>0)
    {
        printf("\nBugday ile besleniyor.(300gr)-->Her tavuk icin");
        if(ciftlik->hayvanToplulugu.tavuk.sayi*0.3<=ciftlik->yemBilgileri.bugday.miktar)
        {
            printf("\nTavuklar Beslendi");
            ciftlik->hayvanToplulugu.tavuk.aclikDurumu = 0;
            ciftlik->yemBilgileri.bugday.miktar -= ciftlik->hayvanToplulugu.tavuk.sayi*0.3;
        } else
            printf("\nYeterli Bugday Yok");

    } else
        printf("Gecerli Secim Yapiniz.");
}
void aclikKontrol(ciftlik_t* ciftlik)//Eger hayvanlardan herhangi bir grubun aclik seviyesei 5 ve katiysa o gruuptan bir hayvan kaybedilir ve aclik durumu sifirlanir.
{
    if(ciftlik->hayvanToplulugu.inek.aclikDurumu%5 == 0 && ciftlik->hayvanToplulugu.inek.aclikDurumu!=0 && ciftlik->hayvanToplulugu.inek.sayi>0)
    {
        printf("Bir Adet Inek Acliktan Oldu :(");
        ciftlik->hayvanToplulugu.inek.sayi--;
        ciftlik->hayvanToplulugu.inek.aclikDurumu = 0;
    }
    else if(ciftlik->hayvanToplulugu.tavuk.aclikDurumu %5 == 0 && ciftlik->hayvanToplulugu.tavuk.aclikDurumu!=0 && ciftlik->hayvanToplulugu.tavuk.sayi>0)
    {
        printf("Bir Adet Tavuk Acliktan Oldu :(");
        ciftlik->hayvanToplulugu.tavuk.sayi--;
        ciftlik->hayvanToplulugu.tavuk.aclikDurumu = 0;
    }
    else if(ciftlik->hayvanToplulugu.koyun.aclikDurumu %5 == 0 && ciftlik->hayvanToplulugu.koyun.aclikDurumu!=0 && ciftlik->hayvanToplulugu.koyun.sayi>0)
    {
        printf("Bir Adet Koyun Acliktan Oldu :(");
        ciftlik->hayvanToplulugu.koyun.sayi--;
        ciftlik->hayvanToplulugu.koyun.aclikDurumu = 0;
    } else return;
}
void hayvanSat(ciftlik_t* ciftlik)//Kullanici kasasini dengeye sokmak icin hayvan satabilir. Satilan hayvan sonucu kasaya para girer hayvan sayisi azalir.
{
    printf("\nPiyasa Hayvan Satis Fiyatlari : \n");
    printf("1-)Inek : %d\n",ciftlik->hayvanToplulugu.inek.satis);
    printf("2-)Koyun: %d\n",ciftlik->hayvanToplulugu.koyun.satis);
    printf("3-)Tavuk: %d\n",ciftlik->hayvanToplulugu.tavuk.satis);

    printf("\nNe Satmak Istersin ? ");
    int cevap = 0;
    scanf("%d",&cevap);
    printf("\nKac Tane Satmak Istersin?\n");
    int adet;
    scanf("%d",&adet);
    if(cevap==1 && adet<=ciftlik->hayvanToplulugu.inek.sayi)
    {
        printf("\nInek Satildi.");
        ciftlik->kasa+=ciftlik->hayvanToplulugu.inek.satis*adet;
        ciftlik->hayvanToplulugu.inek.sayi-=adet;
    }else if(cevap==2 && adet<=ciftlik->hayvanToplulugu.koyun.sayi)
    {
        printf("\nKoyun Satildi.");
        ciftlik->kasa+=ciftlik->hayvanToplulugu.koyun.satis*adet;
        ciftlik->hayvanToplulugu.koyun.sayi-=adet;
    }else if(cevap==3 && adet<=ciftlik->hayvanToplulugu.tavuk.sayi)
    {
        printf("\nTavuk Satildi.");
        ciftlik->kasa+=ciftlik->hayvanToplulugu.tavuk.satis*adet;
        ciftlik->hayvanToplulugu.tavuk.sayi-=adet;
    } else
        printf("Gecersiz Giris veya O Kadar Hayvaniniz Yok");
}
void hayvanAl(ciftlik_t* ciftlik)//Kullanici cok fazla hayvan kaybederse iflas etmemek icin hayvan satin alabilir.
{
    printf("\nPiyasa Hayvan Alis Fiyatlari : \n");
    printf("1-)Inek : %d\n",ciftlik->hayvanToplulugu.inek.alis);
    printf("2-)Koyun: %d\n",ciftlik->hayvanToplulugu.koyun.alis);
    printf("3-)Tavuk: %d\n",ciftlik->hayvanToplulugu.tavuk.alis);

    printf("\nNe Almak Istersin ? ");
    int cevap = 0;
    scanf("%d",&cevap);
    int adet = 1;
    printf("\nKac Adet Alacaksiniz?\n");
    scanf("%d",&adet);
    if(cevap==1 && ciftlik->kasa>=ciftlik->hayvanToplulugu.inek.alis*adet)
    {
        printf("\nInek Alindi.");
        ciftlik->kasa-=ciftlik->hayvanToplulugu.inek.alis*adet;
        ciftlik->hayvanToplulugu.inek.sayi+=adet;
    }else if(cevap==2 && ciftlik->kasa>=ciftlik->hayvanToplulugu.koyun.alis*adet)
    {
        printf("\nKoyun Alindi.");
        ciftlik->kasa-=ciftlik->hayvanToplulugu.koyun.alis*adet;
        ciftlik->hayvanToplulugu.koyun.sayi+=adet;
    }else if(cevap==3 && ciftlik->kasa>=ciftlik->hayvanToplulugu.tavuk.alis*adet)
    {
        printf("\nTavuk Alindi.");
        ciftlik->kasa-=ciftlik->hayvanToplulugu.tavuk.alis*adet;
        ciftlik->hayvanToplulugu.tavuk.sayi+=adet;
    } else
        printf("Gecersiz Giris veya Yeterli Paraniz Yok");
}
void mahsulSat(ciftlik_t* ciftlik)//Hayvanlarin urettigi mahsulleri kullanici satabilir.
{
    printf("\nElde Edilecek Kazanclar:\n");
    printf("1-)Inek Sutu --> 3 TL/lt\n");
    printf("2-)Koyun Sutu --> 4 TL/lt\n");
    printf("3-)Yumurta  --> 2 TL/adet\n");
    printf("Ne Saticaksiniz?\n");
    int cevap;
    scanf("%d",&cevap);
    int kilo;
    printf("Kac Litre(Adet) Satacaksiniz?\n");
    scanf("%d",&kilo);
    if(cevap == 1)
    {
        if(ciftlik->hayvanToplulugu.inek.verdigiUrunMiktari>=kilo)
        {
            printf("%d lt Inek Sutu Satildi. Elde  Edilen Kazanc: %d TL",ciftlik->hayvanToplulugu.inek.verdigiUrunMiktari,ciftlik->hayvanToplulugu.inek.verdigiUrunMiktari*3);
            ciftlik->kasa+=kilo*3;
            ciftlik->hayvanToplulugu.inek.verdigiUrunMiktari -= kilo;
        } else
            printf("Yeterli Inek Sutu Yok");
    }
    else if(cevap == 2)
    {
        if(ciftlik->hayvanToplulugu.koyun.verdigiUrunMiktari>=kilo)
        {
            printf("%d lt Koyun Sutu Satildi. Elde  Edilen Kazanc: %d TL",ciftlik->hayvanToplulugu.koyun.verdigiUrunMiktari,ciftlik->hayvanToplulugu.koyun.verdigiUrunMiktari*4);
            ciftlik->kasa+=kilo*4;
            ciftlik->hayvanToplulugu.koyun.verdigiUrunMiktari -= kilo;
        } else
            printf("Yeterli Koyun Sutu Yok");
    }
    else if(cevap == 3)
    {
        if(ciftlik->hayvanToplulugu.tavuk.verdigiUrunMiktari>=kilo)
        {
            printf("%d Adet Yumurta Satildi. Elde  Edilen Kazanc: %d TL",ciftlik->hayvanToplulugu.tavuk.verdigiUrunMiktari,ciftlik->hayvanToplulugu.tavuk.verdigiUrunMiktari*2);
            ciftlik->kasa+=kilo*2;
            ciftlik->hayvanToplulugu.tavuk.verdigiUrunMiktari -= kilo;
        } else
            printf("Yeterli Yumurta Yok");
    } else{
        printf("Hatali Giris");
    }
}
int iflasKontrol(ciftlik_t* ciftlik)//Eger toplam hayvan sayisi sifir ve kasa 0 veya negatif ise yani borclanilmis ise oyun iflas ile sonlanir.
{
    int toplamHayvan = ciftlik->hayvanToplulugu.tavuk.sayi+ciftlik->hayvanToplulugu.koyun.sayi+ciftlik->hayvanToplulugu.inek.sayi;
    if(ciftlik->kasa<=0 && toplamHayvan<=0)
    {
        printf("\nIFLAS ETTINIZ!\n");
        printf("KALAN HAYAN = %d\n",toplamHayvan);
        printf("KASA = %d",ciftlik->kasa);
        return 1;
    } else return 0;

}
void yemAl(ciftlik_t* ciftlik)//Hayvanlari beslemek icin yem alinir.
{

    printf("\nFiyat Listesi:\n");
    printf("1-)Hazir Yem(kg) --> 7 TL\n");
    printf("2-)Saman(kg) --> 1 TL\n");
    printf("3-)Bugday(kg) --> 4 TL\n");
    printf("4-)Yonca--> 2 TL\n");

    printf("Seciminiz:\n");
    int cevap;
    scanf("%d",&cevap);
    printf("Kac Kilo?\n");
    int kilo;
    scanf("%d",&kilo);

    if(cevap == 1)
    {
        if(ciftlik->kasa<kilo*7)
        {
            printf("\nKasa Yetersiz\n");
            return;
        }
        ciftlik->kasa -= kilo*7;
        ciftlik->yemBilgileri.hazirYem.miktar+= kilo;
        printf("Hazir Yem Alindi.\n");
    }else if(cevap == 2)
    {
        if(ciftlik->kasa<kilo*1)
        {
            printf("\nKasa Yetersiz\n");
            return;
        }
        ciftlik->kasa -= kilo*1;
        ciftlik->yemBilgileri.saman.miktar+= kilo;
        printf("Saman Alindi.\n");
    }else if(cevap == 3)
    {
        if(ciftlik->kasa<kilo*4)
        {
            printf("\nKasa Yetersiz\n");
            return;
        }
        ciftlik->kasa -= kilo*4;
        ciftlik->yemBilgileri.bugday.miktar+= kilo;
        printf("Bugday Alindi.\n");
    }else if(cevap == 4)
    {
        if(ciftlik->kasa<kilo*2)
        {
            printf("\nKasa Yetersiz\n");
            return;
        }
        ciftlik->kasa -= kilo*2;
        ciftlik->yemBilgileri.yonca.miktar+= kilo;
        printf("Yonca Alindi.\n");
    }
}

void kazanmaKontrol(ciftlik_t *ciftlik)//Nasil oynanir kisminda yazilan kazanma sartlari saglanirsa oyun biter
{
	int kasa = ciftlik->kasa;
	int toplamHayvan = ciftlik->hayvanToplulugu.inek.sayi + ciftlik->hayvanToplulugu.koyun.sayi+ ciftlik->hayvanToplulugu.tavuk.sayi;
	
	if(kasa>=500000 && toplamHayvan>=500)
	{
		printf("\n\nTEBRIKLER. OYUNU KAZANDINIZ.\n\n");
		exit(0);
	}
}
int main() {

    srand(time(0));//surekli ayni rastgele sayilari uretmemek icin
    ciftlik_t *benimCiftligim = ciftlikOlustur(); // ciftlik olusturuldu
    int cevap;
    int kaderSayisi =0;
    nasilOynanir(); //kullaniciya bilgi vermek icin cagrilan fonksioyn
    printf("\n\nBaslamak Icin bir rakam tuslayip enter basiniz.\n");
    int baslangic;
    scanf("%d",&baslangic);
    clrscr();
    printf("\n\n\n\n\n\t\t\t\t\tOyun Basliyor...");
    
    while(1) // Oyunun Baslangic Noktasi. Kasa Sifirlanmadikca ve ayni zamanda hayvanlar bitmedikce oyun surer
    {
        sleep(3);
        clrscr();
        if(iflasKontrol(benimCiftligim) == 1) // iflas kontrol iflas icin 1 dondurur
            exit(0);//program bitirir
        kazanmaKontrol(benimCiftligim);
        aclikKontrol(benimCiftligim);// Bu fonksiyon eger aclik seviyesi 5 olursa o grup hayvanlardan bir tanesini oldurur ve aclik sifirlanir.
        ciftlikBilgisiGoster(benimCiftligim);//Her secimden sonra ciftligin son durumunu gosteren fonksiyon.
        secenekMenusuYazdir();//Kullanicinin oyunu surdurmek icin secebilecegi secenekleri gosteren fonksiyon
        scanf("%d",&cevap);//Siradaki hamle alinir
        if(cevap == 1) {
            kaderSayisi = rand()%30; // Zamanin nasil ilerlemesine karar vermek icin 0-30 arasi rastgele sayi uretilir ve belli araliklarla asagidaki fonksiyonlar cagrilir.
            if(kaderSayisi>=0 && kaderSayisi<=10)
                hayvanAcikir(benimCiftligim);
            else if(kaderSayisi>10 && kaderSayisi<=20)
                hayvanOldu(benimCiftligim);
            else if(kaderSayisi>20 && kaderSayisi<=30)
                uretimYapildi(benimCiftligim);

        }
        else if(cevap == 2)
            hayvanBesle(benimCiftligim);
        else if(cevap == 3)
            hayvanSat(benimCiftligim);
        else if(cevap == 4)
            hayvanAl(benimCiftligim);
        else if(cevap == 5)
            mahsulSat(benimCiftligim);
        else if(cevap == 6)
            yemAl(benimCiftligim);
        else if(cevap == 7)
        {
            printf("\n!!!Kasaniz Henuz %d!!!\n",benimCiftligim->kasa);
            printf("Iflas Vermekte Kararlimisin?\n1-)Evet 2-)Hayir\n");
            int iflas = 0;
            scanf("%d",&iflas);
            if(iflas==1)
            {
                printf("\nIFLAS ETTINIZ\n");
                exit(0);
            } else // iflasdan vazgecilirse while dongusune geri donulur
                continue;
        } else
            printf("\nGecersiz Giris Yapildi");

    }
    return 0;
}

