/* 
 * File:   yazici_R.c
 * Author: ubuntu
 *
 * Created on May 18, 2011, 3:53 PM
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
#include <sys/timeb.h>

/*key atamalar*/
#define semYI 111111
#define semYB 222222
#define semSB 333333
#define semR 444444
#define shmDizi 555555
#define shmMsgSB 666666
#define shmMsgR 777777
#define semkey 888888

int main(int argc, char* argv[]){

    int shmDiziID=0, shmSBID=0, shmRID=0, i;
    int R=0, SB=0, sem=0, YI=0, YB=0;
    char *msgR = NULL;  //yazdirilacak renkli katar
    char *msgSB = NULL;  //yazdirilacak siyah beyaz katar
    int *dizi = NULL; //dizinin 1.elemani sb isteyen sayisini, 2.elemani r isteyen sayisini tutuyor
                      //eger yazici tipi olarak SB atanmissa dizinin 3.elemani 1, eger yazici tipi olarak R atanmissa 2 oluyor    
    struct shmid_ds shmbuffer;
    struct timeb tp;
    long int referansR;
    long int referansSB;

    if(argc!=2){
        printf("Yanlis veri girdiniz");
	exit(0);
    }

    shmDiziID = shmget(shmDizi, sizeof(int)*4, 0700|IPC_CREAT);/*ortak alan yarat*/
    dizi = (int*) shmat(shmDiziID, 0, 0);/*ortak alana baglan*/
    //kaynaklari hazirla
    R = semget(semR, 1, 0700|IPC_CREAT);/*renkli yazici semaforu*/
    SB = semget(semSB, 1, 0700|IPC_CREAT);/* siyah beyaz yazici semaforu*/
    YI = semget(semYI, 1, 0700|IPC_CREAT);/*eleman sayisi arttirma islemi kesilmesin diye*/
    YB = semget(semYB, 1, 0700|IPC_CREAT);/*yazici birakma islemi kesilmesin diye*/
    sem = semget(semkey, 1, 0700|IPC_CREAT);/*mesaj hazirlanirken kullanılan semafor*/
    semctl(R, 0, SETVAL, 1);
    semctl(SB, 0, SETVAL, 1);    
    semctl(YI, 0, SETVAL, 1);    
    semctl(YB, 0, SETVAL, 1);    
    semctl(sem, 0, SETVAL, 1);

    for(i=0; i<4; i++)
        dizi[i]=0;

    while(1){//ilk giris icin referans zamani al
        ftime(&tp);
        if(dizi[2]==1 && strcmp(argv[1],"SB")==0){
            referansSB=tp.time;
	    break;
        }
	if(dizi[3]==1 && strcmp(argv[1],"R")==0){
            referansR=tp.time;
	    break;
        }
    }

    while(1){//yazdirilcak mesaji yazdir
        ftime(&tp);
	if(tp.time-referansSB>=10 && dizi[0]==0 && strcmp(argv[1],"SB")==0)
	    break;
	if(tp.time-referansR>=10 && dizi[1]==0 && strcmp(argv[1],"R")==0)
	    break;

	if(dizi[2]==1 && strcmp(argv[1],"SB")==0){            
	    shmSBID = shmget(shmMsgSB, sizeof(int), 0700|IPC_CREAT);
            msgSB = (char*) shmat(shmSBID, 0, 0);/*mesaji al*/
            printf("[%ld] %s\n",tp.time-referansSB, msgSB);//mesaji yazdir
            dizi[2]=0;//yazdirildi sinyali ver
	    sleep(2);//2 saniye uyu	    
        }
        if(dizi[3]==1 && strcmp(argv[1],"R")==0){
	    shmRID = shmget(shmMsgR, sizeof(int), 0700|IPC_CREAT);
            msgR = (char*) shmat(shmRID, 0, 0);/*mesaji al*/
            printf("[%ld] %s\n",tp.time-referansR, msgR);//mesaji yazdir
            dizi[3]=0;//yazdirildi sinyali ver
	    sleep(2);//2 saniye uyu
        }
    }
    shmdt(dizi);
    shmdt(msgR);
    shmdt(msgSB);
    exit(0);
}