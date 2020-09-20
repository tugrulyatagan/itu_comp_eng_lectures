/* ******* MUSTERI HESAPLARI PROGRAMI ********************/
/* This program reads a random access file sequentially, *
 * updates data already written to the file, creates new *
 * data to be placed in the file, and deletes data       *
 * already in the file.                                  */
/* (Standart C) FREAD VE FWRITE ILE DOSYA ISLEMLERI ORNEGI. */

#include <stdio.h>

// Global degiskenler:
#define TRUE 1
#define FALSE 0

FILE *fPtr;

struct clientData {
   int acctNum;
   char lastName[15];
   char firstName[10];
   float balance;
};

// Fonksiyon protipleri:
int enterChoice();
void Listele();
void updateRecord();
void newRecord();
void deleteRecord();

bool main()
{
   int choice;
   char cevap;

   if ((fPtr = fopen("musteri.dat", "r")) == NULL)
   {
      printf("\nmusteri.dat dosyasi bulunamadi.\nBos olarak olusturmak istermisiniz? (E/H)");
      cevap = getchar();
      if (cevap != 'e' && cevap != 'E')
  	      return FALSE;
      
      if ((fPtr = fopen("musteri.dat", "w")) == NULL)
      {
         printf("musteri.dat dosyasi olusturulamadi.\n");
         return FALSE;
      }
      else
	 fclose(fPtr);
   }

   while ((choice = enterChoice()) != 5)
   {
	 switch (choice)
         {
	    case 1:
	       Listele();
	       break;
	    case 2:
	       updateRecord();
	       break;
	    case 3:
	       newRecord();
	       break;
	    case 4:
	       deleteRecord();
	       break;
	    default: printf("\nGecersiz secim yaptiniz.\n\n");
         }

   }

   printf("\n\nHOSCAKALIN...\n");
}

void Listele()
{
   struct clientData client;

   fPtr = fopen("musteri.dat", "r");
   if (fPtr == NULL)
   {
      printf("\nmusteri.dat dosyasi acilamadi");
      return;
   }
   printf("\n\n"); 
   printf("%-10s%-16s%-11s%10s\n","MusteriNo", "Soyadi", "Adi","Bakiye(TL)");
   printf("%-10s%-16s%-11s%10s\n","=========", "======", "===","==========");

   fread(&client, sizeof(struct clientData), 1, fPtr);//ilk kayit
   while (!feof(fPtr))
   {
	 if (client.acctNum != 0) //silinmemis ise
	    printf("%-10d%-16s%-11s%10.2f\n",  client.acctNum,
                                             client.lastName,
		                                 client.firstName,
                                             client.balance);
	 fread(&client, sizeof(struct clientData), 1, fPtr);
   }

   fclose(fPtr);
}

void updateRecord()
{
   int account;
   float transaction;
   struct clientData client;
   int bulundu;
   int sayac;

   fPtr = fopen("musteri.dat", "r+");
   if (fPtr == NULL)
   {
      printf("\nmusteri.dat dosyasi acilamadi");
      return;
   }

   printf("Guncellenecek musteri numarasini giriniz: ");
   scanf("%d", &account);

   // Bu musteriyi dosyada ara:
   sayac=0;
   bulundu = FALSE;
   while(!feof(fPtr))
   {
      sayac++;
      fread(&client, sizeof(struct clientData), 1, fPtr);
      if (client.acctNum == account)
      {
	 bulundu = TRUE;
         break;
      }
   }

   if (bulundu == FALSE)
   {
      printf("#%d Nolu musteri kaydi  yok.\n", account);
      return;
   }

   printf("%-6d%-16s%-11s%10.2f\n\n",
	     client.acctNum, client.lastName,
	     client.firstName, client.balance);

   printf("Islem tutarini giriniz (Borc eklemesi + rakam, odeme icin - rakam): ");
   scanf("%f", &transaction);
   client.balance += transaction;
   printf("%-6d%-16s%-11s%10.2f\n",
	     client.acctNum, client.lastName,
	     client.firstName, client.balance);

   fseek(fPtr, (sayac - 1) * sizeof(struct clientData), SEEK_SET);
   fwrite(&client, sizeof(struct clientData), 1, fPtr);
   fclose(fPtr);
}

void deleteRecord()
{
   struct clientData client, blankClient = {0, "", "", 0};
   int account;
   int bulundu;
   int sayac;

   fPtr = fopen("musteri.dat", "r+");
   if (fPtr == NULL)
   {
      printf("\nmusteri.dat dosyasi acilamadi");
      return;
   }

   printf("Silinecek musteri numarasini giriniz: ");
   scanf("%d", &account);

   // Bu musteriyi dosyada ara:
   sayac=0;
   bulundu = FALSE;
   while(!feof(fPtr))
   {
      sayac++;
      fread(&client, sizeof(struct clientData), 1, fPtr);
      if (client.acctNum == account)
      {
         bulundu = TRUE;
	 break;
      }
   }

   if (bulundu == FALSE)
   {
      printf("#%d Nolu musteri kaydi  yok.\n", account);
      return;
   }

   fseek(fPtr, (sayac - 1) * sizeof(struct clientData), SEEK_SET);
   fwrite(&blankClient, sizeof(struct clientData), 1, fPtr);
   fclose(fPtr);
}

void newRecord()
{
   struct clientData client;
   int account;
   int bulundu;
   int sayac;

   fPtr = fopen("musteri.dat", "a+");
   if (fPtr == NULL)
   {
      printf("\nmusteri.dat dosyasi acilamadi");
      return;
   }

   printf("Eklenecek yeni musterinin numarasini giriniz: ");
   scanf("%d", &account);

   // Bu musteriyi dosyada ara:
   sayac=0;
   bulundu = FALSE;
   while(!feof(fPtr))
   {
      sayac++;
      fread(&client, sizeof(struct clientData), 1, fPtr);
      if (client.acctNum == account)
      {
	 bulundu = TRUE;
         break;
      }
   }

   if (bulundu == TRUE)
   {
      printf("#%d Nolu kayitta baska musteri var.\n", client.acctNum);
      return;
   }


   printf("Soyad, Ad ve Hesap Tutarini giriniz (alanlar arasinda bir bosluk birakarak)\n? ");
   scanf("%s%s%f", &client.lastName, &client.firstName,
	    &client.balance);
   client.acctNum = account;

   fwrite(&client, sizeof(struct clientData), 1, fPtr);
   fclose(fPtr);
}


int enterChoice()
{
   int menuChoice;

   printf("\nMUSTERI HESAPLARI MENUSU\n"
	  "1 - Tum musterileri listele\n"
	  "2 - Musteri hesabi guncelle\n"
	  "3 - Yeni musteri ekle\n"
	  "4 - Musteri sil\n"
	  "5 - Programdan Cikis\n"
	  "    Seciminiz? ");
   scanf("%d", &menuChoice);
   printf("\n");
   return menuChoice;
}
