#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MS 1000			//usleep'te kullanılmak üzere milisaniye sabiti
#define KEY (1983) 		//Semafor yaratmakta kullanılmak üzere anahtar değeri

//Semafor işlemlerinde kullanılmak üzee tanımlanmış veri yapısı
union semun {
     int val;              
     struct semid_ds *buf; 
     ushort *array;        
};

//Partini yapıldığı odayı temsil eden değişkenleri içeren yapı
typedef struct room				
{
	int dean_in;
	int num_of_stu;			
} ROOM;

ROOM aRoom;		//Paylaşılan oda değişkeni

typedef struct sembuf SEMBUF;

//Paralel çalışarak giriş çıkışların benzetimini yapacak yordamlar
void *dean_enter(void *);

void *dean_leave(void *);

void *stu_enter(void *);

void *stu_leave(void *);

main()
{
	//İplik değişkenleri
     	pthread_t t_dean_ent,t_dean_lea,t_stu_ent,t_stu_lea;
	int de_ret,dl_ret,se_ret,sl_ret;

	//Ortak değişkenlere ilk değerleri atanıyor
	aRoom.dean_in=0;
	aRoom.num_of_stu=0;

	int semid,j;
     	union semun arg;

	srand(time(NULL));

        //SEMAFORLAR,numaraları ve başlangıç değerleri ile: 
    	//SEM #0-STUDENT(1) #1-DEAN(1) #2-EMPTY(0) #3-FULL(0) #4-DEANIN(0)
     	{//semaphore init

        	// 5 semaforlu bir semafor seti yaratılıyor
        	semid = semget(KEY, 5, 0666 | IPC_CREAT);

		//ilk semaforun başlangıç değerleri 1'e ayarlanıyor
	       	arg.val = 1;
     		for(j=0;j<2;j++)
        		semctl(semid, j, SETVAL, arg);
		
		//geri kalanların başlangıç değerleri 0'a ayarlanıyor
	       	arg.val = 0;
     		for(j=2;j<5;j++)
        		semctl(semid, j, SETVAL, arg);

    	}

    	//İplikler yaratılıyor. Öğrenci ve dekan girişlerini ve çıkışlarını ayrı ayrı benzeten yordamlar
	//sürekli çalışarak dekan veya öğrenciler tarafından odaya girme/çıkma isteklerini kontrol edecekler
	de_ret = pthread_create( &t_dean_ent, NULL, dean_enter, NULL);

	dl_ret = pthread_create( &t_dean_lea, NULL, dean_leave, NULL);

	se_ret = pthread_create( &t_stu_ent, NULL, stu_enter, NULL);

	sl_ret = pthread_create( &t_stu_lea, NULL, stu_leave, NULL);

    	//İpliklerin çalışması bittikten sonra iplikler sonlandırıl
     	pthread_join( t_dean_ent, NULL);
     	pthread_join( t_dean_lea, NULL);
     	pthread_join( t_stu_ent, NULL);
     	pthread_join( t_stu_lea, NULL);

   	//semaforlar yok ediliyor
     	semctl(semid, 0, IPC_RMID, arg);

	exit(0);
}

//Dekanın odaya girme isteğini benzeten iplik yordamı
void *dean_enter(void *ptr)
{
	int count=0;
     	int semid;
     	SEMBUF sb;

     	sb.sem_flg=0;

     	semid = semget(KEY, 5, 0);			//semafor setimizi elde ediyoruz

	while(count<100000)
	{
     		usleep(MS* (rand()%500) );		//belirli bir süre uyuyup

		//P(Stu)
	        sb.sem_op=-1;       
        	sb.sem_num=0;
		semop(semid, &sb, 1);

		//P(Dean)
	        sb.sem_op=-1;       
        	sb.sem_num=1;
		semop(semid, &sb, 1);

		//Eğer odada yeterli sayıda öğrenci yoksa ve dekan dışarda ise...
		if(aRoom.num_of_stu>0 && aRoom.num_of_stu<50 && aRoom.dean_in==0)
		{
			//V(Dean)
			sb.sem_op=1;       
			sb.sem_num=1;
			semop(semid, &sb, 1);

			//V(Stu)
	        	sb.sem_op=1;       
        		sb.sem_num=0;
			semop(semid, &sb, 1);

			//Dekanı (Ready) semaforu üzerinde bekletmeye başla
			printf("\nDean waiting outside\n");

			//P(Ready)
	        	sb.sem_op=-1;       
        		sb.sem_num=3;
			semop(semid, &sb, 1);	
		}
		else
		{
			//V(Dean)
			sb.sem_op=1;       
			sb.sem_num=1;
			semop(semid, &sb, 1);
		}

		//Dekan odaya girebilince
		//P(Dean)
	        sb.sem_op=-1;       
        	sb.sem_num=1;
		semop(semid, &sb, 1);

		if(aRoom.dean_in==0 && aRoom.num_of_stu>0)
		{
			aRoom.dean_in=1;
			printf("\nDean in room\n");
		}

		//V(Dean)
	        sb.sem_op=1;       
        	sb.sem_num=1;
		semop(semid, &sb, 1);

		//V(Stu)
	        sb.sem_op=1;       
        	sb.sem_num=0;
		semop(semid, &sb, 1);

		count++;		
	}
}

//Dekanın odadan çıkma isteğini benzeten iplik yordamı
void *dean_leave(void *ptr)
{
	int count=0;
     	int semid;
     	SEMBUF sb;

     	sb.sem_flg=0;

     	semid = semget(KEY, 5, 0);			//semafor setimizi elde ediyoruz
	
	while(count<100000)
	{
     		usleep(MS* (rand()%500) );		//belirli bir süre uyuyup

		//Öğrencilerin odayı boşaltmasını bekliyoruz
		//P(Empty)
        	sb.sem_op=-1;       
       		sb.sem_num=2;
		semop(semid, &sb, 1);

		//P(Dean)
	        sb.sem_op=-1;       
        	sb.sem_num=1;
		semop(semid, &sb, 1);
		//Dekan odadaysa çıkıyor
		if(aRoom.dean_in==1)
		{
			aRoom.dean_in=0;
			printf("\nDean left the room\n");

			//Çıktığının sinyalini veriyor
			//V(D_in)
			sb.sem_op=1;       
			sb.sem_num=4;
			semop(semid, &sb, 1);
		}

		//V(Dean)
	        sb.sem_op=1;       
        	sb.sem_num=1;
		semop(semid, &sb, 1);
			
		count++;		
	}
}

//Öğrencilerin odaya girme isteğini benzeten iplik yordamı
void *stu_enter(void *ptr)
{
	int count=0;
     	int semid;
     	SEMBUF sb;

     	sb.sem_flg=0;

     	semid = semget(KEY, 5, 0);			//semafor setimizi elde ediyoruz

	while(count<1000)
	{
     		usleep(MS* (rand()%100) );		//belirli bir süre uyuyup

		//P(Dean)
	        sb.sem_op=-1;       
        	sb.sem_num=1;
		semop(semid, &sb, 1);

		//Eğer dekan odadaysa öğrenci içeride bekliyor
		if(aRoom.dean_in==1)
		{
			//V(Dean)
		        sb.sem_op=1;       
        		sb.sem_num=1;
			semop(semid, &sb, 1);

			printf("\nStudent waiting outside\n");				

			//Dekan odadan çıkma sinyalini verene kadar
			//P(D_in)
		        sb.sem_op=-1;       
	        	sb.sem_num=4;
			semop(semid, &sb, 1);

		}
		else
		{
			//V(Dean)
		        sb.sem_op=1;       
        		sb.sem_num=1;
			semop(semid, &sb, 1);
		}

		//Sonra içeriye giriyor
		//P(Stu)
	        sb.sem_op=-1;       
        	sb.sem_num=0;
		semop(semid, &sb, 1);

		aRoom.num_of_stu++;
		printf("\n%d students in room\n",aRoom.num_of_stu);
		//Eğer odada 50den fazla öğrenci varsa
		if(aRoom.num_of_stu>50)
		{
			//Dekana GİR sinyali gönderiliyor
			//V(Ready)
		        sb.sem_op=1;       
       			sb.sem_num=3;
			semop(semid, &sb, 1);
		}

		//V(Stu)
	        sb.sem_op=1;       
		sb.sem_num=0;
		semop(semid, &sb, 1);

		count++;		
	}
}

//Öğrencilerin odaya çıkma isteğini benzeten iplik yordamı
void *stu_leave(void *ptr)
{
	int count=0;
     	int semid;
     	SEMBUF sb;

     	sb.sem_flg=0;

     	semid = semget(KEY, 5, 0);			//semafor setimizi elde ediyoruz

	while(count<1000)
	{
     		usleep(MS* (rand()%300) );		//belirli bir süre uyuyup	

		//P(Stu)
	        sb.sem_op=-1;       
        	sb.sem_num=0;
		semop(semid, &sb, 1);

		//Odada öğrenci varsa biri çıksın
		if(aRoom.num_of_stu>0)
		{
			aRoom.num_of_stu--;
			printf("\n%d students in room\n",aRoom.num_of_stu);
		}
		
		//Öğrenci yoksa oda boş sinyali verilsin
		if(aRoom.num_of_stu==0)
		{
			//V(Empty)
		        sb.sem_op=1;       
       			sb.sem_num=2;
			semop(semid, &sb, 1);
		}

		//V(Stu)
	        sb.sem_op=1;       
 		sb.sem_num=0;
		semop(semid, &sb, 1);

		count++;		
	}
}
