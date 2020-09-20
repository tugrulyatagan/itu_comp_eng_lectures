#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<string.h>
#include<sys/shm.h>
#include<time.h>

/*key atamalar*/
#define KEYSEM 1234
#define KEYSEM2 1236
#define KEYSHM 1238

void mergeSort(int *a, int p, int r);
void merge(int* a, int p, int q, int r);
void mysignal( void ){}

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

void mysigset(int num){
	struct sigaction mysigaction;
	mysigaction.sa_handler = (void*) mysignal;
	mysigaction.sa_flags = 0;
	sigaction(num, &mysigaction, NULL);
}

int main(int argc, char* argv[]){
	int f=1, i, n;
	int cocuklar[3];
	int sonsem=0, sem2=0, shmid=0;
	int *dizi = NULL;
	struct shmid_ds shmbuffer;

	mysigset(12);
   
	for(i=0; i<3; i++){
		if(f>0)/*cocuklar olusturuluyor*/
			f = fork();

		if(f==-1){
			printf("fork error....\n");
			exit(1);
		}

		if(f==0)
			break;

		else
			cocuklar[i] = f;
	}

	if(f!=0){ 
		i = 0;     
		srand(time(NULL));   
		while(i==0){ /*cift bir sayi bulana kadar devam*/
			n=rand()%99+2;/*n = dizinin eleman sayisi*/
			if(n%2==0)
				i++;
		}      

		sonsem = semget(KEYSEM2, 1, 0700|IPC_CREAT);/*semafor yarat*/
		semctl(sonsem, 0, SETVAL, 0);/*degerini sifira ata*/
		
		sem2 = semget(KEYSEM, 1, 0700|IPC_CREAT);/*semafor yarat*/
		semctl(sem2, 0, SETVAL, 0);/*degerini sifira ata*/
    
		shmid = shmget(KEYSHM, sizeof(int)*n, 0700|IPC_CREAT);/*ortak alan yarat*/
		dizi = (int*) shmat(shmid, 0, 0);/*ortak alan icin yer al*/
      
		srand(time(NULL)); 
		for(i=0; i<n; i++)/*diziyi random olarak doldur*/
			dizi[i] = rand()%5000;

		sleep(2);
		
		printf("anne kaynaklari yaratti ve cocuklari baslatacak.\n");
	
		for(i=0; i<3; i++)/*cocuklari uyandir*/
			kill(cocuklar[i], 12);	

		sem_wait(sonsem, 3);/*cocuklari bekle*/
	
		printf("Tum cocuklar oldu\n");

		printf("Minimum = %d\n", dizi[0]);
		printf("Maximum = %d\n", dizi[n-1]);

   		shmdt(dizi);/*alinan kaynaklari iade et*/
		semctl(sonsem, 0, IPC_RMID, 0);
      		semctl(sem2, 0, IPC_RMID, 0);
		shmctl(shmid, IPC_RMID, 0);
		exit(0);
	}

	else{
		pause();

		sem2 = semget(KEYSEM, 1, 0);/*semaforu oku*/
		sonsem = semget(KEYSEM2, 1, 0);/*semaforu oku*/
		
		shmid = shmget(KEYSHM, sizeof(int), 0);
		dizi = (int *) shmat(shmid, 0, 0);/*ortak alana baglan*/
		
		shmctl(shmid, IPC_STAT, &shmbuffer);
		n = shmbuffer.shm_segsz/sizeof(int);/*eleman sayisini ortak alanin boyutunu kullanarak hesapla*/
                  
		if(i==0){
			printf("cocuk %d basliyor....\n", i);		
			mergeSort(dizi, 0, n/2-1);/*dizinin ilk yarisini sirala*/
			sem_signal(sem2, 1);/*merge icin sinyal ver*/
		}
		
		if(i==1){  
			printf("cocuk %d basliyor....\n", i); 
			mergeSort(dizi, n/2, n-1);/*dizinin ikinci yarisini sirala*/
			sem_signal(sem2, 1);/*merge icin sinyal ver*/
		}
		
		if(i==2){
			sem_wait(sem2, 2);/*merge icin 2 sinyal bekle*/
			printf("cocuk %d basliyor....\n", i);
			merge(dizi, 0, (n-1)/2, n-1);/*merge et*/
		}
		
		shmdt(dizi);
		printf("cocuk %d bitiyor....\n", i);
		sem_signal(sonsem, 1);/*anne icin sinyal yolla*/
		
		exit(0);      
	}

	return 0;
}

void merge(int* a, int p, int q, int r){
	int n1 = q-p+1;
	int n2 = r-q;
	int *L = (int*) malloc(sizeof(int)*n1);
	int *R = (int*) malloc(sizeof(int)*n2);
	int i,j,k,l=0,m=0;
    
	for(i=0; i<n1; i++)
		L[i] = a[p+i];

	for(j=0; j<n2; j++)
		R[j] = a[q+j+1];

	L[n1]=5000;
	R[n2]=5000;
	for(k=p; k<=r; k++){
		if(L[l]<=R[m]){
			a[k] = L[l];
			l++;
		}
		else{
			a[k] = R[m];
			m++;
		}
	}
}

void mergeSort(int *a, int p, int r){
	int q;
	if(p<r){
		q=((p+r)/2);
		mergeSort(a,p,q);
		mergeSort(a,q+1,r);
		merge(a,p,q,r);
	}
}