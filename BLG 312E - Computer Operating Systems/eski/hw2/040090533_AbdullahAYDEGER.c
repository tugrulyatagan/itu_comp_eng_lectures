/************************************************************
*	Ad Soyad			: Abdullah AYDEÐER					*
*   Numara				: 040090533							*
*	Dersin Adý			: Ýþletim Sistemleri				*
*	Öðretim Görevlisi	: Þima UYAR							*
*	Ödev				: 2									*
*	Teslim Tarihi		: 12.04.2012						*
*************************************************************/



#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define GNU SOURCE
#define KEYSHM1 1234
#define KEYSHM2 1235
#define KEYSHM3 1236
#define KEYSHM4 1237
#define SEMKEY1 1300
#define SEMKEY2 1301


void sem_signal(int semid, int val){
	struct sembuf semafor;
	semafor.sem_num = 0;
	semafor.sem_op = val;
	semafor.sem_flg = 1;
	semop(semid, &semafor, 1);
	}
	
void sem_wait(int semid, int val){
	struct sembuf semafor;
	semafor.sem_num = 0;
	semafor.sem_op = (-1*val);
	semafor.sem_flg = 1;
	semop(semid, &semafor, 1);
	}

void mysignal(void){}	

void mysigset(int num){
	struct sigaction mysigaction;
	mysigaction.sa_handler = (void*) mysignal;
	mysigaction.sa_flags = 0;
	sigaction(num, &mysigaction, NULL);
}
	
int main(int argc, char *argval[],char *env[] ){
	int f=0;
	int getN, getK, *cocuklarim;	
	getN = atoi(argval[1]);		//getN degeri komut satirindan girilen dizideki toplam eleman degeri
	getK = atoi(argval[2]);		//getK degeri komut satirindan girilen toplam olusturulacak proses sayisi
	int shmid1, shmid2, shmid3, shmid4;		//paylasilan bellek alanlari icin kullanilacak id degiskenleri
	int *globaldizi, *globalN, *globalK, *EB;		//paylasilan bellek alanlarinda kullanilacak pointerlar
	int sonSemaforGeldiMi = 0;	//1 adet semafor(annenin çocuk prosesleri beklemesi icin gerekli senkronizasyonu saglamak amaciyla kullanildi)
	int indis = 0;		//cocuk proseslerin kacinci sirada oldugunu saklamasi icin kullanilan degisken

	int i;	//dongu degiskeni

	cocuklarim = malloc(sizeof(int)*getK);		//cocuklar dizisine cocuk proses kadar yer ayirildi, anne prosesin cocuk proseslerinin id'lerini saklamak icin

	mysigset(12);

	for(i=0; i<getK; i++){	//'getK' degeri kadar
		f = fork();		//cocuk yarat
		indis = i;		//cocuklarin indisini sakla(cocuklar icin ileride gerekli olacak)
		if(f == -1){	
			printf("Fork yaratirken hata olustu\n");
			exit(1);
		}
		if(f == 0)	//cocuk proses ise
			break;	//for döngüsüne daha devam etme

		cocuklarim[i] = f;	//anne proseste cocuklarin 'f' degiskeninde bulunan "id" degerlerini sakla(senkronizasyon icin kullanilacak)
	}
	
	if(f != 0){		//anne proses
		srand (time(NULL));		//rastgele sayi uretmek icin

		sonSemaforGeldiMi = semget(SEMKEY1,1,0700|IPC_CREAT);	//senkronizasyon semaforu yaratildi
		semctl(sonSemaforGeldiMi,0,SETVAL,0);					//ilk degeri '0' yapildi
	
		shmid1 = shmget(KEYSHM1, sizeof(int)*(getN),0700|IPC_CREAT);	//Dizi icin bellekten 'N' boyutlu paylasilan bellek bolgesi alindi
		globaldizi = (int *)shmat(shmid1, 0, 0);				//Bu bellek bolgesine erisim(anne proseste) 'globaldizi' degiskeni uzerinden mumkun

		shmid2 = shmget(KEYSHM2, sizeof(int),0700|IPC_CREAT);	//Dizinin boyutu 'N' degerinin saklanmasi icin paylasilan bellek bolgesi alindi
		globalN = (int *)shmat(shmid2, 0, 0);				//Bu 'N' degerine erisim(anne proseste) 'globalN' degeri uzerinden mumkun

		shmid3 = shmget(KEYSHM3, sizeof(int),0700|IPC_CREAT);	//Toplam yaratilan proses sayisini saklayabilmek icin paylasilan bellek bolgesi alindi
		globalK = (int *)shmat(shmid3, 0, 0);				//Bu bellek bolgesine erisim(anne proseste) 'globalK' degeri uzerinden mumkun

		shmid4 = shmget(KEYSHM4, sizeof(int)*(getK),0700|IPC_CREAT);	//Cocuk proseslerin bulduklari en buyuk degeri yazacaklari dizi icin paylasilan yer alindi
		EB = (int *)shmat(shmid4, 0, 0);			//Bu diziye erisim 'EB' degiskeni uzerinden mumkun

		for(i = 0; i<getN; i++){	//Dizinin boyu kadar 
			globaldizi[i] = rand()%1000;	//Rastgele sayi uret ve paylasilan bellek alanina yaz(urettigim rastgele sayilar 0-1000 arasinda olacaktir)
			printf("Diziye atanan deger %d.eleman icin = %d \n",i+1, globaldizi[i]);
		}

		*globalN = getN;	//Toplam dizi boyu paylasilan bellek alanina yazildi
		*globalK = getK;	//Toplam cocuk proses sayisi paylasilan bellek alanina yazildi
				
		for(i=0; i<getK; i++)	//Cocuk proses sayisi kadar 
			kill( cocuklarim[i], 12);	//cocuklarim dizisindeki 'id' degerli proseslere(yani buradaki cocuk proseslere olacak) sinyal gonder
			
		sem_wait(sonSemaforGeldiMi,getK);	//Tum cocuklar isini bitirince anne proses devam edebilsin

		int max = *EB;	//max degeri baslangic olarak en buyuklerin bulundugu 'EB' dizisinin ilk elemanini gostersin

		for(i = 0; i < getK; i++){	//Proses sayisi kadar
			printf("Cocuk proses %d'nin buldugu en buyuk eleman = %d\n", i+1, EB[i]);
			if(max < EB[i])	//Gelen eleman 'max' degerinden buyukse
				max = EB[i];	//'max' degerini guncelle
		}
		printf("\nAnne Proses: Tum Dizideki En Buyuk Eleman = %d\n",max);
		
		//Kurdugun(attach) baglantilari kopar(detach). Yani kaynaklari iade et.
		shmdt(globaldizi);	
		shmdt(EB);
		shmdt(globalK);
		shmdt(globalN);
		
		//Semaforlar ve paylaþýlan bellek alanlarý iade ediliyor
		semctl(sonSemaforGeldiMi, 0, IPC_RMID, 0);
		shmctl(shmid1, IPC_RMID, 0);
		shmctl(shmid2, IPC_RMID, 0);
		shmctl(shmid3, IPC_RMID, 0);
		shmctl(shmid4, IPC_RMID, 0);

		exit(0);	//anne proses(yani main program) bitiyor..
		
	}	

	else{	//cocuksa
		
		pause();	//Tum cocuklar anneden sinyal('kill' sinyali) beklemede

		//int *cocukDizisi;

		sonSemaforGeldiMi = semget(SEMKEY1,1,0);	//SEMKEY1 id'li semaforun degeri 'sonSemaforGeldiMi' degiskenine atandi

		shmid1=shmget (KEYSHM1, sizeof(int)*(getN), 0);		//KEYSHM1-2-3-4 seklinde id degerleri olan daha onceden yaratilan paylasilan bellek alanlarina erisim saglaniyor
		shmid2=shmget (KEYSHM2, sizeof(int), 0);
		shmid3=shmget (KEYSHM3, sizeof(int), 0);
		shmid4=shmget (KEYSHM4, sizeof(int)*(getK), 0);

		globaldizi = (int*) shmat(shmid1,0,0);	//shmid1 icin globaldizi degiskeni uzerinden erisim mumkun
		globalN = (int*) shmat(shmid2,0,0);		//shmid2 icin..
		globalK = (int*) shmat(shmid3,0,0);		//shmid3 icin..
		EB = (int*) shmat(shmid4,0,0);			//shmid4 icin..

		int elemanSayim = (*globalN)/(*globalK);	//Cocuk proseslerin toplam eleman sayisi(en buyugunu bulacagi alt dizideki) dizideki 
														//toplam eleman sayisinin proses sayisina bolumunden elde edilebilir	
														
		int max = globaldizi[indis*elemanSayim];	//max degeri cocugun tarayacagi alt dizinin ilk elemanina esit olsun **baslangic icin**
		for(i = (indis*elemanSayim)+1; i <(indis*elemanSayim)+elemanSayim; i++){	//Cocuk prosesin eleman sayisi kadar
			if(max < globaldizi[i])	//Eger gelen deger max'dan buyukse
				max = globaldizi[i];	//max'ýn degerini degistir
		}
		EB[indis] = max;	//EB paylasilan bellek bolgesine max degerini yaz
		
		//Kurdugun baglantilari kopar
		shmdt(globalK);
		shmdt(globalN);
		shmdt(globaldizi);
		shmdt(EB);

		sem_signal(sonSemaforGeldiMi,1);	//Cocuk proses isini bitirdi, anneye sinyal gonder(tum cocuklar bitince anne devam edebilecek)

		exit(0);	//cocuk prosesin calismasi bitiyor..
	}
	
	return 0;
}
	