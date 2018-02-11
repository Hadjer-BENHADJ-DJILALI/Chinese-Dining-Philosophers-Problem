#include <stdlib.h>
#include <sys/sem.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main()
{

struct sembuf op;
int op_sem_num,op_sem_op,op_sem_flg;

//creation des semaphores 

int semid,i,k;
int N =5;
int nsems=6;
int tab[5]={2,2,2,2,2};
int semflg = IPC_CREAT |0666 ;
key_t key = ftok ("cle.txt",'a');
semid =semget(key,nsems,semflg); 
printf(" la cle est :%d \n",key);
printf ("l'identificateur : %d \n",semid);


int pidp[N];// creer N philosho


//initialiser les semaphores 

semctl(semid,0,SETVAL,1);// semaphore pour les etats 
semctl(semid,1,SETVAL,0);// semaphore philosophe 1
semctl(semid,2,SETVAL,0);// semaphore philosophe 2
semctl(semid,3,SETVAL,0);// semaphore  philosophe 3
semctl(semid,4,SETVAL,0);// semaphore philosophe 4
semctl(semid,5,SETVAL,0);// semaphore philosophe 5


printf("******-Debut-************ \n");
printf ("0:Affamer \n");
printf ("1:Manger\n");
printf ("2:Penser\n");
printf ("\n");

for (i=0;i<N;i++)
{

pidp[i]=fork();
if (pidp[i]==-1) {printf ("ERREUR DU FORK\n");}
if (pidp[i]==0)
{
while(1)
{
sleep(rand()%20+1);


semid=semget(key,0,0666);

op_sem_num=0;
op_sem_op=-1;
op_sem_flg=0;
semop(semid,&op,1);
tab[i]=0;
printf("\n");
printf(" philosophe n° %d  changer a affamé \n",i);

op_sem_num=0;
op_sem_op=1;
op_sem_flg=0;
semop(semid,&op,1);



if (tab[(i+1)%5]!=1 && tab[(i-1)%5]!=1) 
{
semid=semget(key,0,0666);
 
op_sem_num=0;
op_sem_op=-1;
op_sem_flg=0;
semop(semid,&op,1);

tab[i]=1;

op_sem_num=0;
op_sem_op=1;
op_sem_flg=0;
semop(semid,&op,1);



printf("philosophe n° %d changer a manger \n",i);

/*.for (k=0;k<N;k++)
{
printf(" %d ", tab[k]);

}*/

 printf(" \n");

/// rentre en section critique manger  
semid=semget(key,i,0666); 

 while(1)
{
op_sem_num=i;
op_sem_op=1;
op_sem_flg=0;

printf(" philiosophe %d  Mange!!!!\n",i);
//sleep(5);
printf(" philiosophe %d Fin!!!!\n",i);

op_sem_num=i;
op_sem_op=-1;
op_sem_flg=0;
semop(semid,&op,1);

 exit(0);
}

}



 
break;
}// du if 
exit(0);
}

}// du for


for (i=0;i<N;i++)
{
wait(0);
}
printf("******- Fin -************ \n");

// destruction du semaphore
semctl(semid,0,IPC_RMID,1);
semctl(semid,1,IPC_RMID,1);
semctl(semid,2,IPC_RMID,1);
semctl(semid,3,IPC_RMID,1);
semctl(semid,4,IPC_RMID,1);
semctl(semid,5,IPC_RMID,1);




return 0;
}



