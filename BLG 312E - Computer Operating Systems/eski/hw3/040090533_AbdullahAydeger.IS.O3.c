/************************************************************
*	Ad Soyad			: Abdullah AYDEGER					*
*   Numara				: 040090533							*
*	E-mail				: aydeger@itu.edu.tr				*
*	Dersin Adý			: Ýsletim Sistemleri				*
*	Öðretim Görevlisi	: Sima UYAR							*
*	Ödev				: 3									*
*	Teslim Tarihi		: 04.05.2012						*
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

#define GNU SOURCE
#define KEYSHM1 1111
#define KEYSHM2 1112
#define SEMKEY1 2222
#define SEMKEY2 2223
#define SEMKEY3 2224
#define SEMKEY4 2225
#define SEMKEY5 2226
#define SEMKEY6 2227


void sem_signal(int semid, int val){	//semafor izin islemi
	struct sembuf semafor;
	semafor.sem_num = 0;
	semafor.sem_op = val;
	semafor.sem_flg = 1;
	semop(semid, &semafor, 1);
}
	
void sem_wait(int semid, int val){	//semafor kontrol islemi
	struct sembuf semafor;
	semafor.sem_num = 0;
	semafor.sem_op = (-1*val);
	semafor.sem_flg = 1;
	semop(semid, &semafor, 1);
}

void yayinla(int v){
/************************************************************************************************************
*	Fonksiyon Adi: yayinla																					*
*	Fonksiyon parametreleri: Yayinlanacak integer veri														*
*	Fonksiyon donus degeri : ---																			*
*	Fonksiyonun Ýslevi	   : Parametre olarak verilen veriyi paylasilan(KEYHSM ile) bellek alanina yazmak	*
*************************************************************************************************************/
	int shmid1=shmget(KEYSHM1, sizeof(int), 0);		//paylasilan veriye bag kuruluyor
	int *paylasilanVeri = (int*) shmat(shmid1,0,0);	//shmid1 icin paylasilanVeri degiskeni uzerinden erisim mumkun		
	*paylasilanVeri = v;	//paylasilan veri degistiriliyor
	printf("Yayinladik: %d\n",*paylasilanVeri);	//paylasilan veri ekrana bastiriliyor
	shmdt(paylasilanVeri);	//baglanti kopariliyor
}

int veriyi_al(){
/************************************************************************************************************
*	Fonksiyon Adi: veriyi_al																				*
*	Fonksiyon parametreleri: ---																			*
*	Fonksiyon donus degeri : Paylasilan bellek alanindaki veri												*
*	Fonksiyonun Ýslevi	   : Paylasilan bellek alanindaki(KEYHSM ile) ekranda gostermek ve geri dondurmek	*
*************************************************************************************************************/
	int shmid1=shmget(KEYSHM1, sizeof(int), 0);		//paylasilan veriye baglanti kuruluyor
	int *paylasilanVeri = (int*) shmat(shmid1,0,0);	//shmid1 icin paylasilanVeri degiskeni uzerinden erisim mumkun
	printf("Veriyi ALLDIM %d\n", *paylasilanVeri);	//Veriyi ekranda gosteriyor
	return 	*paylasilanVeri;	//paylasilan veri fonksiyondan geri donduruluyor
}

int main(){
	int f=0;	//cocuklarda buradan kopyalanacagi icin ilk deger '0'
	int m, n;	//m:uretici, n:tuketici sayisi
	int shmid1, shmid2;		//paylasilan bellek alanlari icin kullanilacak id degiskenleri
	int *veri, *paylas;		//paylasilan bellek alanlarinda kullanilacak pointerlar
	int sonTuketiciMi = 0, sonUreticiMi = 0, 
				tuket = 0, disla = 0, uret = 0, kilit = 0;	//semafor degiskenleri
	int indis;		//cocuk proseslerin kacinci sirada oldugunu saklamasi icin kullanilan degisken
	int i;	//dongu degiskeni

	printf("\nLutfen uretici sayisini(m) giriniz: ");
	scanf("%d",&m);
	printf("\nLutfen tuketici sayisini(n) giriniz: ");
	scanf("%d",&n);
		
	uret = semget(SEMKEY1, 1, 0700|IPC_CREAT);	//ilk ureticiye izin verecek semafor
	semctl(uret,0,SETVAL,0);					//ilk degeri '0' yapildi

	tuket = semget(SEMKEY2, 1, 0700|IPC_CREAT);	//tuketicilere izin verecek semafor
	semctl(tuket,0,SETVAL,0);					//ilk degeri '0' yapildi
	
	//printf("Uretici: %d, Tuketici:%d", m, n);
	for(i=1; i<=n+m; i++){	//uretici(m) + tuketici(n) sayisi kadar proses olusturulacak
		f = fork();		//cocuk yarat
		indis = i;		//cocuklarin indisini sakla(cocuklar icin ileride uretici-tuketici belirlemede gerekli)
		if(f == -1){	//Hata durumu
			printf("Fork yaratirken hata olustu\n");
			exit(1);
		}
		if(f == 0)	//cocuk proses ise
			break;	//for döngüsüne daha devam etme
	}

	if(f != 0){		//anne proses	

		sonTuketiciMi = semget(SEMKEY3, 1, 0700|IPC_CREAT);	//Tum tuketicilerin okudugunu belirleyen semafor
		semctl(sonTuketiciMi,0,SETVAL,0);					//ilk degeri '0' yapildi

		disla = semget(SEMKEY4, 1, 0700|IPC_CREAT);	//Tuketicilerin birbirini beklemesi icin kullanilan semafor
		semctl(disla,0,SETVAL,0);					//ilk degeri '0' yapildi
		
		sonUreticiMi = semget(SEMKEY5, 1, 0700|IPC_CREAT);	//Tum ureticilerin bitmesi icin semafor
		semctl(sonUreticiMi,0,SETVAL,0);					//ilk degeri '0' yapildi
			
		kilit = semget(SEMKEY6, 1, 0700|IPC_CREAT);	//Paylasilan bellek alanindaki 'paylas' degiskenine tek tek yazmak icin semafor
		semctl(kilit,0,SETVAL,0);					//ilk degeri '0' yapildi			
	
		shmid1 = shmget(KEYSHM1, sizeof(int), 0700|IPC_CREAT);	//Paylasilan bellek alani olusturuldu
		veri = (int *)shmat(shmid1, 0, 0);				
						
		shmid2 = shmget(KEYSHM2, sizeof(int), 0700|IPC_CREAT);	//Tuketicilerin birbirini beklemesi icin paylasilan bellek alani
		paylas = (int *)shmat(shmid2, 0, 0);
		*paylas = 0;

		shmdt(veri);	//paylasilan bellek alaniyla baglantiyi kopardik
		shmdt(paylas);	//paylasilan bellek alaniyla baglantiyi kopardik
		
		sem_signal(kilit, 1);	//Tuketicilerin paylasilan bellek alani icin ilk izin
		sem_signal(uret, 1);	//Ilk ureticiye izin verildi
		sem_wait(sonUreticiMi, m);		//Tum ureticilerin tamamlanmasi bekleniyor

		printf("\nProgram basariyla bitti\n*****Gule gule*****\n");

		shmctl(shmid1, IPC_RMID, 0);		//Paylasilan bellek alanlari icin alinan bellekler geri veriliyor
		shmctl(shmid2, IPC_RMID, 0);

		semctl(tuket , 0, IPC_RMID , 0);		//Semaforlar icin alinan bellekler geri veriliyor
		semctl(sonUreticiMi , 0, IPC_RMID , 0);
		semctl(disla , 0, IPC_RMID , 0);
		semctl(sonTuketiciMi , 0, IPC_RMID , 0);
		
		exit(0);	//anne proses(yani main program) bitiyor..	
	}	

	else{	//cocuksa
		sonTuketiciMi = semget(SEMKEY3, 1, 0);	
		tuket = semget(SEMKEY2, 1, 0);	
		if(indis > n ){	//ureticiler
			int v;		
			uret = semget(SEMKEY1,1,0);	
			sonUreticiMi = semget(SEMKEY5,1,0);	
			sem_wait(uret, 1);	//Yanlizca bir uretici iceri(bu satirdan alta) girebilir
			printf("\nYayinlamak istediginiz veriyi giriniz:");	
			scanf("%d", &v);
			yayinla(v);		//Yayinla cagrisiyla veri uretici-tuketici paylasilan alanina yaziliyor
			sem_signal(tuket, n);	//Tuketicilerin 'n' adedi icin semafor ayarlandi
			sem_wait(sonTuketiciMi, n);	//Tum tuketicilerin bitmesini beklemekteyiz
			sem_signal(sonUreticiMi, 1);
			sem_signal(uret, 1);		//Yeni ureticiye izin verdik
		}
			
		else if(indis <= n){		//tuketiciler
			disla = semget(SEMKEY4, 1, 0);
			int shm_ID= shmget(KEYSHM2, sizeof(int), 0);	
			paylas = (int *) shmat(shm_ID,0,0);	
			kilit = semget(SEMKEY6, 1, 0);	
			for(i=0; i<m; i++){		//n adet tuketici, her biri m'er kez girecek donguye
				sem_wait(tuket, 1);		//Ureticiden tuket sinyali beklenecek	
				int veri = veriyi_al();	//veriyi_al cagrisiyla uretici-tuketici arasindaki paylasilan veriyi okuduk.

				sem_wait(kilit, 1);		//Ayni anda yanliz bir proses paylasilan bellek alanina erisebilir
					(*paylas)++;	
				sem_signal(kilit, 1);	//Diger proseslerin erisimine izin verdik

				if(*paylas != n){	//Sonuncu proses gelinceye kadar hepsi burada bekler
					sem_wait(disla, 1);
				}		
				if(*paylas == n){	//sonuncu tuketici tum tuketicilerin semaforuna sinyal gonderecek
					*paylas = 0;		//Tuketiciler arasi paylasilan bellek sifirlandi
					sem_signal(disla, n-1);	//Bekleyenleri uyandir
				}
				sem_signal(sonTuketiciMi,1);	//Tum tuketiciler islerinin bittigini ureticiye bildiriyor
			}
		}
		exit(0);	//cocuk prosesin calismasi bitiyor..
	}
	
	return 0;
}


