/* 
 * File:   kullanici.c
 * Author: ubuntu
 *
 * Created on May 18, 2011, 3:52 PM
 */

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
#define semYI 111111
#define semYB 222222
#define semSB 333333
#define semR 444444
#define shmDizi 555555
#define shmMsgSB 666666
#define shmMsgR 777777
#define semkey 888888

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

char* yazici_iste(char *type){
    int YI=0, shmDiziID=0, SB=0, R=0;
    int *dizi = NULL;

    YI = semget(semYI, 1, 0);
    SB = semget(semSB, 1, 0);
    R = semget(semR, 1, 0);
    shmDiziID = shmget(shmDizi, sizeof(int), 0);
    dizi = (int *) shmat(shmDiziID, 0, 0);
    
    if(strcmp(type,"SB")==0){
        sem_wait(YI, 1);
        dizi[0]++;
        sem_signal(YI, 1);
        sem_wait(SB, 1);
        return "SB";
    }
    if(strcmp(type,"R")==0){
        sem_wait(YI, 1);
        dizi[1]++;
        sem_signal(YI, 1);
        sem_wait(R, 1);
        return "R";
    }
    if(strcmp(type,"H")==0){
        while(1){
            if(dizi[0]==0){
                sem_wait(YI, 1);
                dizi[0]++;
                sem_signal(YI, 1);
                sem_wait(SB, 1);
                return "SB";
            }
            if(dizi[1]==0){
                sem_wait(YI, 1);
                dizi[1]++;
                sem_signal(YI, 1);
                sem_wait(R, 1);
                return "R";
            }
        }
    }
}

void yazici_birak(char *type){
    int YB=0, shmDiziID=0, SB=0, R=0;
    int *dizi = NULL;

    YB = semget(semYB, 1, 0);
    SB = semget(semSB, 1, 0);
    R = semget(semR, 1, 0);

    shmDiziID = shmget(shmDizi, sizeof(int), 0);
    dizi = (int *) shmat(shmDiziID, 0, 0);

    sem_wait(YB, 1);

        if(strcmp(type,"SB")==0){
            dizi[0]--;
            sem_signal(SB, 1);
	}
	if(strcmp(type,"R")==0){
            dizi[1]--;
            sem_signal(R, 1);
	}

    sem_signal(YB, 1);
}

int main(int argc, char* argv[]){

    int shmDiziID=0, shmSBID=0, shmRID=0, R=0, SB=0, i, sem=0;
    char *msgR = NULL;  //yazdirilacak renkli katar
    char *msgSB = NULL;  //yazdirilacak siyah beyaz katar
    int *dizi = NULL; //dizinin 1.elemani sb isteyen sayisini, 2.elemani r isteyen sayisini tutuyor
		      //eger yazici tipi olarak SB atanmissa dizinin 3.elemani 1, 
                      //eger yazici tipi olarak R atanmissa dizinin 4.elemani 1 oluyor
    struct shmid_ds shmbuffer;
    char* return_type=NULL;

    if(argc!= 3){
        printf("Yanlis veri girdiniz");
	exit(0);
    }
 
    shmDiziID = shmget(shmDizi, sizeof(int), 0700|IPC_CREAT);/*bilgilerin bulundugu ortak alan*/
    dizi = (int*) shmat(shmDiziID, 0, 0);

    sem = semget(semkey, 1, 0);

    return_type = yazici_iste(argv[1]);
    //yazici alindi
    sem_wait(sem,1);//yazdirilacak mesaji ayarla, yazdir sinyali ver
        if(strcmp(return_type,"SB")==0){
            shmSBID = shmget(shmMsgSB, sizeof(argv[2]), 0700|IPC_CREAT);/*SB yazdirilcak katar*/
            msgSB = (char*) shmat(shmSBID, 0, 0);
            strcpy(msgSB,argv[2]);
            shmdt(msgSB);
            dizi[2]=1;//SB yazdir sinyali
        }
        if(strcmp(return_type,"R")==0){
            shmRID = shmget(shmMsgR, sizeof(argv[2]), 0700|IPC_CREAT);/*R yazdirilcak katar*/
            msgR = (char*) shmat(shmRID, 0, 0);
            strcpy(msgR,argv[2]);
            shmdt(msgR);
            dizi[3]=1;//R yazdir sinyali
        }
    sem_signal(sem,1);

    while(1){//yazdirildi sinyalini bekle
        if(strcmp(return_type,"SB")==0 && dizi[2]==0){
            yazici_birak("SB");
            break;
        }
        if(strcmp(return_type,"R")==0 && dizi[3]==0){
            yazici_birak("R");
            break;
        }
    }
    shmdt(dizi);
    exit(0);
}