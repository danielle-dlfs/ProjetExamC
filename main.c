#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define TEMPS_MAX 100 //temps maximal pour un secteur
#define TEMPS_MIN 20 //temps minimal pour un secteur
#define SHM_SIZE 2048 //taille définie un peu au hasard...
#define KEY 1234


int main(int argc,char *argv[]){


srand(time(NULL));
char * mem;
int tabPid[22];
int *pointeur;
int pid[23]; //tableau d'identifiant processus 
int i=0;
double tabTemps[22];
int shm_id=shmget(KEY,SHM_SIZE,IPC_CREAT);//creation segment memoire partagee

if(shm_id==-1){
	perror("erreur creation segament memoire partagee");
	exit(EXIT_FAILURE);

}

pid[i]=fork();

if (pid[i]==-1){//test premier fork
		
		
		perror("erreur creation processus fils 1");
		exit(EXIT_FAILURE);

}


if(pid[i]==0){ //processus fils 0
	
	
	sleep(2);
	
	mem=shmat(shm_id,(void *) 0,0);
	tabPid[i]=getpid();
	tabTemps[i]=(double)rand()/(double)RAND_MAX;
	tabTemps[i] *= (double)(TEMPS_MAX-TEMPS_MIN);
	tabTemps[i]+=TEMPS_MIN;
/*ce bloc permet d'écrire dans la memoire partagee...
la fonction strcat ne prend que des string en parametre, il faut donc caster le float
en string pour que cela fonctionne */

	char test[10];
	sprintf(test,"%f",tabTemps[i]);
	strcat(mem,test);

	//strcpy(mem,tabTemsp[i]);
	//printf("%f\n",tabTemps[i]);
	exit(EXIT_SUCCESS);
}
else{ //processus pere
 	
	 /*Cette ligne permet de s'attacher au sgement de memoire partagee*/
	mem=shmat(shm_id,NULL,0);
	

	i++;
	while(i<22){

		pid[i]=fork(); //un nouveau processus fils est créé
		if (pid[i]==-1){
			
			tabPid[i]=getpid();
			perror("erreur creation processus fils");
			exit(EXIT_FAILURE);

		}
		else if(pid[i]==0){ //fils n i
			tabTemps[i]=(double) rand()/(double)RAND_MAX;
			tabTemps[i]*=TEMPS_MAX;
			exit(EXIT_SUCCESS); //important pour éviter une boucle

		}
		
		i++;
		
	}
	sleep(2);//il faut utiliser de la mémoire partagée.
	int i=0;
	printf("%s\n",mem);
/*
	while(i<22){
		printf("processus %d pid:%d pid pere: %d\n",i,tabPid[i],getpid());
		i++;
		sleep(1);
	}
*/
	
}
return 0;

}