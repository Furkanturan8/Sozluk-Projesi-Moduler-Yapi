#include "sozluk.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

sozluk kelime;

void kelimeEkle(){
	system("cls");
	
	printf("Kelime Ekleme Sayfas� \n\n");
	printf("T�rk�e    : "); scanf(" %[^\n]s",kelime.turkce); 
	printf("Ingilizce : "); scanf(" %[^\n]s",kelime.ingilizce); 
	strlwr(kelime.ingilizce); 
	strlwr(kelime.turkce); 
	 
	FILE * ptr=fopen("sozluk.dat","a+b");
	fwrite(&kelime,sizeof(sozluk),1, ptr); 
	fclose(ptr);
	printf("\nKelime Kayd� Tamamland� !\n\n");
	 
}

	void turkceIngilizce(){
		system("cls");
		printf("T�rk�e-Ingilizce Kelime Arama\n\n");
		char kelimeBul[20];
		printf("Aramak istedi�iniz T�rk�e kelime : "); scanf(" %[^\n]s",kelimeBul);
		strlwr(kelimeBul);
		
		int durum=0;

		FILE * ptr=fopen("sozluk.dat","r+b");
			rewind(ptr);
		while( fread (&kelime,sizeof(sozluk),1,ptr)!=NULL ){
			
			if(strcmp(kelimeBul,kelime.turkce)==0){
				system("cls");
				printf("\t\tKelime Bulundu...\n\nT�rk�e:  %-20s Ingilizce: %-20s \n\n\n\n",kelime.turkce,kelime.ingilizce);
				durum=1;
				break;
			}
		}
		fclose(ptr);
		if(durum==0)
			printf("\nListede Kelime Yok !\n\n");
		
		
	}
	void ingilizceTurkce(){
		system("cls");
		printf("Ingilizce - T�rk�e Kelime Arama\n\n");
		char kelimeBul[20];
		printf("Aramak istedi�iniz Ingilizce kelime : "); scanf(" %[^\n]s",kelimeBul);
		strlwr(kelimeBul);
		
		int durum=0;

		FILE * ptr=fopen("sozluk.dat","r+b");
			rewind(ptr);
		while( fread (&kelime,sizeof(sozluk),1,ptr)!=NULL ){
			
			if(strcmp(kelimeBul,kelime.ingilizce)==0){
				system("cls");
				printf("\t\tKelime Bulundu...\n\nIngilizce:  %-20s T�rk�e: %-20s \n\n\n\n",kelime.ingilizce,kelime.turkce);
				durum=1;
				break;
			}
		}
		fclose(ptr);
		if(durum==0)
			printf("\nListede Kelime Yok !\n\n");
		
	}
	
void kelimeBul(){
	system("cls");
	int secim;
	printf("Kelime Arama Sayfas� \n\n");
	printf("1) T�rk�e - Ingilizce Arama\n");
	printf("2) Ingilizce - T�rk�e Arama\n");
	printf("0) Ana Menu \n");
	printf("\nSe�iminiz : "); scanf("%d",&secim);
	
	if(secim==1)
		turkceIngilizce();
	else if(secim==2)
		ingilizceTurkce();
	else
		printf("\nAna Men�ye Y�nlendiriliyorsunuz...\n\n---------------------------------\n\n");
	
		
}
	
	
void kelimeListele(){
	
	system("cls");
	int sayac=0;
	printf("Kelime Listeleme Sayfas� \n\n");
	printf("%-10s%-20s%-20s \n","Numara","T�rk�e","Ingilizce");
	printf("--------------------------------------------\n");
	 
	FILE * ptr=fopen("sozluk.dat","r+b");
	while(fread(&kelime,sizeof(sozluk),1, ptr)!=NULL)
	{
		sayac++;
		printf("%-10d%-20s%-20s \n",sayac,kelime.turkce,kelime.ingilizce);
	}
	fclose(ptr);
	
	if(sayac==0)
		printf("Listede Hi� Kelime Yok !\n\n");
	else
		printf("\n\nListede %d adet kelimeniz var...\n\n--------------------------------------------\n\n",sayac);
	
}
void kelimeSil(){
	
	system("cls");
	int silNo,sayac=0;
	printf("Kelime Listeleme Sayfas� \n\n");
	printf("%-10s%-20s%-20s \n","Numara","T�rk�e","Ingilizce");
	printf("--------------------------------------------\n");
	 
	FILE * ptr=fopen("sozluk.dat","r+b");
	while(fread(&kelime,sizeof(sozluk),1, ptr)!=NULL)
	{
		sayac++;
		printf("%-10d%-20s%-20s \n",sayac,kelime.turkce,kelime.ingilizce);
	}
	
	
	if(sayac==0)
		printf("Listede Hi� Kelime Yok !\n\n");
	else
	{
		printf("\n\nSilmek �stedi�iniz Kelimenin Numaras�n� Giriniz: "); scanf("%d",&silNo);
		if(silNo<=0 || silNo>sayac){
			printf("\nHatal� Numara Girdiniz!\n\n");
		}	
		else{
			sayac=0;
			rewind(ptr);
			FILE*yedekPtr=fopen("yedek.dat","w+b");
			while(fread(&kelime,sizeof(sozluk),1,ptr)!=NULL){
				sayac++;
				
				if(silNo!=sayac) //silinmek istenen kelime haric hepsi diger dosyaya yedeklensin
					fwrite(&kelime,sizeof(sozluk),1,yedekPtr);
				
			}
			fclose(ptr);
			fclose(yedekPtr);
			
			//eski dosyay� silip yeni yedek dosyas�n�n ismini sozluk.dat yapal�m
			remove("sozluk.dat");
			rename("yedek.dat","sozluk.dat");
			
			printf("\n%d numaral� kelime listeden silindi !\n\n",silNo);
		}
	}
	fclose(ptr);	
}

int sozlukMenu(){
	
	int secim;
	printf("�ngilizce T�rk�e S�zl�k Uygulamas�\n\n");
	printf("\n\t1-Kelime Ekle\n");
	printf("\n\t2-Kelime Bul\n");
	printf("\n\t3-Kelime Listele\n");
	printf("\n\t4-Kelime Sil\n");
	printf("\n\t0-Uygulamay� Kapat\n");	
	printf("\n\tSe�iminiz: "); scanf("%d",&secim);
	
	return secim;
}
void sozlukIslemler(){
	
	int secim=sozlukMenu();
	while(secim!=0){
		
		switch (secim){
		
			case 1: kelimeEkle(); break; 
			case 2: kelimeBul(); break;
			case 3: kelimeListele(); break;
			case 4: kelimeSil(); break;
			case 0: break;
			 default: printf("Hatal� Se�im Yapt�n�z!\n\n");
		
		}
	secim=sozlukMenu();
	}
	printf("\n\nProgram Kapat�l�yor...\n\n");
	
	
}
