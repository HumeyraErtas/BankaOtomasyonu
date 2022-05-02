#include <stdio.h>
#include <stdlib.h>
#include<conio.h>

enum TipBelirleme
{
	bireysel ,
	ticari
};

typedef struct
{
	char adi[30];
	char soyadi[30];
	int numarasi;
	enum TipBelirleme musteritipi;
	float para;
}Musteri;
typedef struct
{
	int tarih;
	int hesabinnumarasi;
	int gidenhesapno;
	char yapilanis[20];
	float tutar;
	double gelenpara;
	double bankadangiden;
}Rapor;
FILE *fp,*fp2;
int i , secim,temp,temp2, girilenmusteri=0,yenipara;
Musteri musteriler[1000], *p=musteriler;
Rapor rapor;


void Baslangic(){
    int toplam=p+girilenmusteri;
	fp = fopen("bireyselmusteri.txt","r");
	while (fp != NULL)
	{

		(fread((toplam), sizeof(Musteri), 1, fp));
		{
			girilenmusteri++;
		}
    }
    fclose(fp);
    fp = fopen("ticarimusteri.txt","r");
    while(fp != NULL)
    {
    	(fread((toplam), sizeof(Musteri), 1, fp));
    	{
    		girilenmusteri++;
    	}
    	printf("Tum Musteri sayisi %d\n",girilenmusteri);
    }
    fclose(fp);
}


    void MusteriGirisi()
{
	printf("\n----------------MUSTERI BILGILERI GIRISI----------------\n");
	fflush(stdin);
	printf("Lutfen adinizi giriniz:");
	scanf("%s",(p+girilenmusteri)->adi);
	fflush(stdin);
	printf("Lutfen soyadinizi giriniz:");
	scanf("%s",(p+girilenmusteri)->soyadi);
	fflush(stdin);
	printf("Musteri tipini giriniz (bireysel icin 0,ticari icin 1 tuslayin):");
	scanf("%d",&(p+girilenmusteri)->musteritipi);

	srand(time(NULL));
	temp=rand()%1000;
	for(i=0; i<girilenmusteri; i++)
	{
		if(temp == (p+i)->numarasi)
		{
			temp=rand()%1000;
			printf("Bu hesap numarasy kullanylmaktadir tekrar hesap no uretiliyor %d yeni uretilen",temp);
			i=0;
		}
	}
	(p+girilenmusteri)->numarasi = temp;
	if((p+girilenmusteri)->musteritipi==bireysel)
	{
		fp= fopen("bireyselmusteri.txt","a");
		fwrite((p+girilenmusteri), sizeof(Musteri), 1, fp);
		fclose(fp);
	}
	else
	{
		fp= fopen("ticarimusteri.txt","a");
		fwrite((p+girilenmusteri), sizeof(Musteri), 1, fp);
		fclose(fp);
	}
	girilenmusteri++;
	fflush(stdin);
	printf("MUSTERI NUMARANIZ :%d \n",(p+girilenmusteri-1)->numarasi);
}


 void IslemMenu()
{


    printf("1-PARA CEKME\n");
    printf("2-PARA YATIRMA\n");
    printf("3-HAVALE\n");
    printf("4-BANKA GELIR GIDER RAPORU\n");
    printf("5-HESAP OZETI\n");
    printf("6-HESAP KAPAMA\n");
    printf("7-EXIT\n");

    printf("Lutfen yapmak istediginiz islemi seciniz: ");

}
void BankaRaporuAl()
{
	double toplam=0.0;
	for(i=0;i<girilenmusteri;i++)
	{
		toplam+=(p+i)->para;
	}

	fp= fopen("rapor.txt","r");
	printf("  TARIH       ISLEM       HESAP NO    GIDEN HESAP NO       TUTARI\n");
	while(fread(&rapor,sizeof(Rapor),1,fp)==1)
	{
		printf("%8d%15s     %4d        %4d               %.2f\n"
			,rapor.tarih, rapor.yapilanis, rapor.hesabinnumarasi, rapor.gidenhesapno, rapor.tutar);
	}
	printf("------------------------------------------\nBankada bulunana toplam para miktari %.2lf\n\n",rapor.bankadangiden);
    printf("------------------------------------------\nBankaya gelen toplam para miktari %.2lf\n\n",rapor.gelenpara);
	fclose(fp);
}
void HesapOzeti(int temp, int temp2)
{
    fp = fopen("rapor.txt","r");
    fp2 = fopen("dekont.txt","w");
    fprintf(fp2,"-----------------------------DEKONT---------------------------\n");
    fprintf(fp2,"  TARIH       ISLEM       HESAP NO    GIDEN HESAP NO       TUTARI\n");
    printf("\n-----------------------------DEKONT---------------------------\n");
    printf("  TARIH       ISLEM       HESAP NO    GIDEN HESAP NO       TUTARI\n");
    while (fread(&rapor, sizeof(Rapor),1,fp)!=EOF)
    {
        for(i=0;i<girilenmusteri;i++)
        {
        if(rapor.hesabinnumarasi == (p+i)->numarasi || rapor.gidenhesapno == (p+i)->numarasi)
        {
            if(rapor.tarih >= temp && rapor.tarih <= temp2)
            {
                printf("%8d %15s     %4d        %4d               %.2f\n"
			    ,rapor.tarih, rapor.yapilanis, rapor.hesabinnumarasi, rapor.gidenhesapno, rapor.tutar);
                fprintf(fp2,"%8d %15s     %4d        %4d               %.2f\n"
			    ,rapor.tarih, rapor.yapilanis, rapor.hesabinnumarasi, rapor.gidenhesapno, rapor.tutar);
            }
        }
        }
    }
    fclose(fp);
    fclose(fp2);
}


void BankaRaporaYaz()
{
	fp=fopen("rapor.txt","a");
	fwrite(&rapor,sizeof(Rapor),1,fp);
	fclose(fp);
}
structDosyaYaz(){
	fp = fopen("bireysel.txt","w");
	fp2 = fopen("ticari.txt","w");
	for(i=0;i<girilenmusteri;i++)
	{
		if((p+i)->musteritipi == bireysel)
		{
			fwrite((p+i), sizeof(Musteri),1,fp);
		}
		else
		{
			fwrite((p+i), sizeof(Musteri),1,fp2);
		}
	}
	fclose(fp);
	fclose(fp2);
}


int main()
{
    int hesapno,i,j,x=0,y=0,menu_secim,temp,tarih,sakla;
    int cekilentutar, yatirilantutar,havaleNO;
    char e_h;
    float havale,giden_para;

  Baslangic();
while(1)
    {
        printf("------------------------ANA MENU------------------------\n");
        printf("1-Musteri Kaydi Yapma\n");
        printf("2-Musteri Girisi Yapma\n");
        printf("0-Cikis.\n");
        printf("Seciminizi giriniz:");
        scanf("%d",&secim);

        switch ( secim )
        {
        case 1:
            MusteriGirisi();
            break;

        case 2:
    zipla:
    printf("Hesap numaranizi giriniz: ");
    scanf("%d",&hesapno);
    for(i=0; i<girilenmusteri; i++)
	{
		if(hesapno== (p+i)->numarasi)
        {
            printf("Adi :%s\t  Soyadi:%s\t HESAP NUMARASI:%d\n\n",(p+i)->adi,(p+i)->soyadi,(p+i)->numarasi);
            x=1;
        }
      }
if(x==0)
   {
    printf("Boyle bir musteri bulunmamaktadir, lutfen tekrar deneyiniz\n");
    goto zipla;
   }else
         zipla3:
            IslemMenu();
            scanf("%d",&menu_secim);
            switch(menu_secim){
            zipla2:
        case 1:
          fflush(stdin);
       printf("Para cekme tarihinizi giriniz(01012000seklinde): ");
       scanf("%d",&rapor.tarih);
       fflush(stdin);
	 printf("Musteri tipini giriniz (bireysel icin 0,ticari icin 1 tuslayin):");
	 scanf("%d",&(p+girilenmusteri)->musteritipi);

        if((p+girilenmusteri)->musteritipi==bireysel)
        {

            printf("Cekilecek tutari giriniz: ");
            scanf("%d",&cekilentutar);

            if(cekilentutar>750)
            {
                printf("Bireysel icin olan limiti astiniz!!!");
                printf("Yeniden deneyiniz!!!");
                goto zipla2;
            }
            for(i=0;i<girilenmusteri;i++)

            {
            if(cekilentutar>(p+i)->para)
            {
                printf("Bakiye yetersiz, en fazla %.3f cekebilirsiniz");
                printf("Yeniden deneyiniz\n");
                goto zipla2 ;
            }
                else
                    {
                    printf("Kalan bakiye %.3f dir\n",(p+i)->para-cekilentutar);
                        goto zipla3;

                }

           yenipara=(p+i)->para-cekilentutar;
          rapor.hesabinnumarasi=(p+i)->numarasi;
          rapor.tutar=yenipara;
          rapor.gidenhesapno=0;
          strcpy(rapor.yapilanis,"Para Yatirma");
          structDosyaYaz();
          BankaRaporaYaz();


            }
        }

        else
        {

            printf("Cekilecek tutari giriniz: ");
            scanf("%d",&cekilentutar);
            sakla=cekilentutar;
            if(cekilentutar>1500)
            {
                printf("Ticari icin olan limiti astiniz!!!");
                printf("Yeniden deneyiniz!!!");
                goto zipla2;
            }
            for(i=0;i<girilenmusteri;i++)
            {
            if(cekilentutar>(p+i)->para)
            {
                printf("Bakiye yetersiz, en fazla %.3f cekebilirsiniz");
                printf("Yeniden deneyiniz\n");
                goto zipla2 ;
            }
                else
                    {
                    printf("Kalan bakiye %.3f dir\n",(p+i)->para-cekilentutar);
                        goto zipla3;

                }
                yenipara=(p+i)->para-cekilentutar;
          rapor.hesabinnumarasi=(p+i)->numarasi;
          rapor.tutar=yenipara;
          rapor.gidenhesapno=0;
          strcpy(rapor.yapilanis,"Para Cekme");
          structDosyaYaz();
          BankaRaporaYaz();


            }
        }

            break;
        case 2:
            zipla4:

                 printf("Para yatirma tarihinizi giriniz(01012000seklinde): ");
               scanf("%d",&rapor.tarih);
                printf("Yatirilacak tutari giriniz:");
                scanf("%d",&yatirilantutar);
                rapor.gelenpara=yatirilantutar;
                for(i=0;i<girilenmusteri;i++)
                {
                    (p+i)->para+=yatirilantutar;
                    printf("Hesabinizda bulunan miktar: %.3f dir",(p+i)->para);
                    printf("Yeniden para yatirmak istiyor musunuz?");
                    scanf("%s",&e_h);
                    if(e_h=='e')
                    {
                        goto zipla4;
                    }
                    else
                    {
                        goto zipla3;
                    }

           yenipara=(p+i)->para+yatirilantutar;
          rapor.hesabinnumarasi=(p+i)->numarasi;
          rapor.tutar=yenipara;
          rapor.gidenhesapno=0;
          strcpy(rapor.yapilanis,"Para Yatirma");
          structDosyaYaz();
          BankaRaporaYaz();

                }
                break;

       case 3:
                   zipla5:

                  printf("Havale tarihinizi giriniz(01012000seklinde): ");
                  scanf("%d",&rapor.tarih);
                     for(i=0;i<girilenmusteri;i++)

                     {
                         temp=(p+i)->para-cekilentutar;
                     }
                         printf("Hesabinizdaki toplam para: %.3f dir ",temp);


                      printf("Havale yapacaginiz hesap numarasi giriniz: ");
                         scanf("%d",&havaleNO);
                     for(j=0;j<girilenmusteri;j++)
                     {
                         if(havaleNO==(p+j-1)->numarasi);
                         {
                             printf("*****Havale yapacaginiz kisi bilgileri*******\n");
                             printf("Ismi:%s\t   Soyadi:%s\t  ",(p+j)->adi,(p+j)->soyadi);
                             y=1;
                             break;
                         }
                     }
                     if(y==0)
                     {
                         printf("Yanlis hesap numarasi girdiniz\n");
                         goto zipla5;
                     }
                      fflush(stdin);
	 printf("Musteri tipini giriniz (bireysel icin 0,ticari icin 1 tuslayin):");
	 scanf("%d",&(p+girilenmusteri)->musteritipi);
	 if((p+girilenmusteri)->musteritipi==bireysel)
     {


                     printf("Havale yapilacak tutari giriniz:");
                     scanf("%f",&havale);
                     giden_para=havale+havale*2/100;
                     for(i=0; i<girilenmusteri;i++)
                     {
                           temp=(p+i)->para-cekilentutar;
                       if(giden_para>temp)
                       {
                           printf("Bakiye yetersiz!!");
                           goto zipla5;
                       }else
                       do{
                        printf("Hesabinizda kalan miktar %.3f dir\n",temp-(giden_para));
                        printf("Yeniden para gondermek istiyor musunuz?");
                        scanf("%s",&e_h);
                       }while (e_h=='e');
                       goto zipla3;

                     }

     }

if((p+girilenmusteri)->musteritipi==ticari)
     {


                     printf("Havale yapilacak tutari giriniz:");
                     scanf("%f",&havale);
                     giden_para=havale;
                     for(i=0; i<girilenmusteri;i++)
                     {
                           temp=(p+i)->para-cekilentutar;
                       if(giden_para>temp)
                       {
                           printf("Bakiye yetersiz!!");
                           goto zipla5;
                       }else
                       {


                        printf("Hesabinizda kalan miktar %.3f dir\n",temp-(giden_para));

                       goto zipla3;

                     }
                     temp=(p+i)->para-cekilentutar;
                     if(temp>=havale)
                     {
                         temp-=havale;
                         yenipara=temp;
                         rapor.hesabinnumarasi=(p+i)->numarasi;
                          rapor.gidenhesapno=havaleNO;

                  if ((p+i)->musteritipi == bireysel)
                {
                 giden_para=havale+havale*2/100;
                rapor.tutar=temp-(giden_para);
                rapor.bankadangiden=sakla+giden_para;
               }

              else
             {
             giden_para=havale;
            rapor.tutar=temp-havale;
            rapor.bankadangiden=sakla+giden_para;
              }
               strcpy(rapor.yapilanis,"Havale");
             structDosyaYaz();
            BankaRaporaYaz();

        }

     }

        }
        break;


        case 4:
            printf("\n------------------------BANKA RAPORU------------------------\n");
       FILE *rapor;

        int bankadan_giden=0, bankaya_gelen=0, bankadaki_tpara=0;



        rapor=fopen("rapor.txt","w");
        if(rapor==NULL){
            printf("Dosya acilamadi...\n");
            exit(1);
        }
        for(i=0;i<girilenmusteri;i++){
            bankadan_giden+=cekilentutar;
            bankaya_gelen+=yatirilantutar;
            bankadaki_tpara+=(bankaya_gelen-bankadan_giden);

            if(fwrite(&bankadan_giden,sizeof(int),1,rapor)!=1){
                printf("Yazma hatasi!!\n");
                exit(1);
            }
            if(fwrite(&bankaya_gelen,sizeof(int),1,rapor) !=1){
                printf("Yazma hatasi!!\n");
                exit(1);
            }
            if(fwrite(&bankadaki_tpara,sizeof(int),1,rapor) !=1){
                printf("Yazma hatasi!!\n");
                exit(1);
            }

        }
        fclose(rapor);
        rapor=fopen("rapor.txt","r");
        if(rapor==NULL){
            printf("Dosya acilamadi...\n");
            exit(1);
        }
        geridon:
        for(i=0;i<girilenmusteri;i++){
            if(fread(&bankadan_giden,sizeof(int),1,rapor)!=1){
                printf("Yazma hatasi!!\n");
                exit(1);
            }
            if(fread(&bankaya_gelen,sizeof(int),1,rapor) !=1){
                printf("Yazma hatasi!!\n");
                exit(1);
            }
            if(fread(&bankadaki_tpara,sizeof(int),1,rapor) !=1){
                printf("Yazma hatasi!!\n");
                exit(1);
            }
            char cevap;

                printf("Raporu almak istiyormusun.");
                scanf("%c",&cevap);
                do{
            printf("\n------------BANKA GELIR GIDER RAPORU-------------\n");
            printf("Bankaya gelen para miktari: %d\n",bankaya_gelen);
            printf("Bankadan giden para miktari: %d\n",bankadan_giden);
            printf("Bankadaki toplam para miktari: %d\n",bankadaki_tpara);
                }
            while(cevap=='e');
            printf("hatali secim yaptiniz..\n");
                    goto geridon;
                   }
                   fclose(rapor);
                 break;


        }
        case 5:
            printf("\n------------HESAP OZETI------------------\n");
            fflush(stdin);
						    printf("Baslangic tarhini giriniz(01012000 - formatinda giriniz): ");
    					    scanf("%d",&rapor.tarih);
    					    temp=rapor.tarih;
    					    printf("Bitis tarhini giriniz(01012000 - formatinda giriniz): ");
    					    scanf("%d",&rapor.tarih);
    					    temp2=rapor.tarih;
    					    HesapOzeti(temp, temp2);
                            break;

                            case 6:
       printf("Hesabi kapamak istiyor musunuz (E/H)");
       if(toupper(getche()=='E')){
        for(i=0;i<girilenmusteri;i++)
        {
            if((p+i)->para==0)
                remove(fp);
                else
                    printf("Bakiyeniz kapatilmaya uygun degildir lutfen kalan paranizi cekiniz...");
                goto zipla2;
        }
        printf("Hesap kapama islemi basariyla gerceklesti....!!!");
       }
     break;

    }


 }
 return 0;
}
