//main in i�erisinde tekrar tekrar y�kelemeyi �nlemek i�in kontrol mekanizmas� yazd�k.
#ifndef _SOZLUK_H
#define _SOZLUK_H

typedef struct Sozluk{
	char ingilizce[20],turkce[20];
}sozluk;

void kelimeEkle();

void kelimeBul();
	void turkceIngilizce();
	void ingilizceTurkce();
	
void kelimeListele();
void kelimeSil();

int sozlukMenu();
void sozlukIslemler();

#endif

