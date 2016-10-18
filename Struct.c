#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TEMPSS1 45 //temps max pour secteur 1
#define MAX_TEMPSS2 50//...
#define MAX_TEMPSS3 55//...
#define MAX_STAND 5//temps arret max au stand
#define NMAX_ARRET 10//nombre d'arret max par course

#define MIN_TEMPSS1 40//temps min pour secteur 1
#define MIN_TEMPSS2 45//...
#define MIN_TEMPSS3 50//...
#define MIN_STAND 1//temps min arret au stand
#define NMIN_ARRET 0//nombre d'arret min par course (sera peut etre imposé)

/*cette fonction détermine le temps mis pour effectuer un sceteur.
La fonction aléatoire prend en paramètre le secteur dans lequel on se trouve
a=1---->secteur1
*/

double randomTemps(int a){

	if(a==1){
		return (double)MIN_TEMPSS1+rand()/(double)RAND_MAX*(MAX_TEMPSS1-MIN_TEMPSS1);
		
	}
	else if(a==2){

		return (double)MIN_TEMPSS2+rand()/(double)RAND_MAX*(MAX_TEMPSS2-MIN_TEMPSS2);


	}
	else if(a==3){
		
		return (double)MIN_TEMPSS3+rand()/(double)RAND_MAX*(MAX_TEMPSS3-MIN_TEMPSS3);
	}
	else if(a==4){
		
		return (double)MIN_STAND+rand()/(double)RAND_MAX*(MAX_STAND-MIN_STAND);
	
	}
	else{

		printf("argument invalide\n");

	}

}
/*Determine me nombre d'arret au stand (entre 0 et 10)*/
int nbArret(){

	return NMIN_ARRET+(rand()%(NMAX_ARRET-NMIN_ARRET));

}

/*Détermine si une voiture abandonne, avec une probabilité de 5% */
bool estOut(){

	int value=rand()/RAND_MAX*100;
	if(value<5){
		
		return 1;
	}
	else{

		return 0;
	}

}

struct voiture{ //structure voiture

	pid_t pid; //pid du processus
/*variables nécessaires pour les séance d'essai libre*/
	double tempsP1; //temps total séance P1
	double tempsP2;//temps total séance P2
	double tempsP3;//temps total séance p3

	double tempsTotalMoyen;
	double S1Moyen;
	double S2Moyen;
	double S3Moyen;

	double S1tempsP1;//temps secteur 1 seance p1
	double S2tempsP1;//temps secteur 2 seance p1
	double S3tempsP1;//temps secteur 3 seance p1

	double S1tempsP2;//temps secteur 1 seance p2
	double S2tempsP2;//temps secteur 2 seance p2
	double S3tempsP2;//temps secteur 3 seance p2

	double S1tempsP3;//temps secteur 1 seance p3
	double S2tempsP3;//temps secteur 2 seance p3
	double S3tempsP3;//temps secteur 3 seance p3
/*variables nécessaires pour les qualifications (plus tard)*/
	double tempsQ1;
	double tempsQ2;
	double tempsQ3;
/*variables d'état de la voiture*/

	int stand; //si la 
	bool out;



};
int main(int argc,char* argv[]){
	srand(time(NULL)); // Copyright: Amelie
	struct voiture Mavoiture;
	sleep(1);
/*------------------------------------------Séance d'essai 1-----------------------------------*/
	Mavoiture.S1tempsP1=randomTemps(1);
	Mavoiture.S2tempsP1=randomTemps(2);
	Mavoiture.S3tempsP1=randomTemps(3);
	Mavoiture.stand=nbArret();

	int i=0;
	while(i<Mavoiture.stand){

		Mavoiture.S3tempsP1+=randomTemps(4); //rajoute le temps perdu lors des arrets au stand
		i++;
	}

	Mavoiture.tempsP1=Mavoiture.S1tempsP1+Mavoiture.S2tempsP1+Mavoiture.S3tempsP1;

	/*Pour toutes les variables de type double, on ne considère que 3 chiffres après la virgule*/
	printf("Seance essai 1(vendredi matin):\ntemps secteur1:%.3f\ntemps secteur2:%.3f\ntemps secteur3:%.3f\n",Mavoiture.S1tempsP1,Mavoiture.S2tempsP1,Mavoiture.S3tempsP1);
	printf("temps total:%.3f\n",Mavoiture.tempsP1);
	printf("nb arret:%d\n",Mavoiture.stand);

/*------------------------------------------Séance d'essai 2-----------------------------------*/
	char next;
	printf("appuyez sur ENTER pour poursuivre les essais:\n");
	scanf("%c",&next);
	Mavoiture.S1tempsP2=randomTemps(1);
	Mavoiture.S2tempsP2=randomTemps(2);
	Mavoiture.S3tempsP2=randomTemps(3);
	Mavoiture.stand=nbArret();

	i=0;
	while(i<Mavoiture.stand){

			Mavoiture.S3tempsP2+=randomTemps(4); //rajoute le temps perdu lors des arrets au stand
			i++;
		}
	Mavoiture.tempsP2=Mavoiture.S1tempsP2+Mavoiture.S2tempsP2+Mavoiture.S3tempsP2;
	printf("Seance essai 2(vendredi apres-midi):\ntemps secteur1:%.3f\ntemps secteur2:%.3f\ntemps secteur3:%.3f\n",Mavoiture.S1tempsP2,Mavoiture.S2tempsP2,Mavoiture.S3tempsP2);
	printf("temps total:%.3f\n",Mavoiture.tempsP2);
	printf("nb arret:%d\n",Mavoiture.stand);

/*------------------------------------------Séance d'essai 3-----------------------------------*/
	
	printf("appuyez sur ENTER pour poursuivre les essais:\n");
	scanf("%c",&next);
	Mavoiture.S1tempsP3=randomTemps(1);
	Mavoiture.S2tempsP3=randomTemps(2);
	Mavoiture.S3tempsP3=randomTemps(3);
	Mavoiture.stand=nbArret();

	i=0;
	while(i<Mavoiture.stand){

			Mavoiture.S3tempsP3+=randomTemps(4); //rajoute le temps perdu lors des arrets au stand
			i++;
		}
	Mavoiture.tempsP3=Mavoiture.S1tempsP3+Mavoiture.S2tempsP3+Mavoiture.S3tempsP3;
	printf("Seance essai 2(samedi matin):\ntemps secteur1:%.3f\ntemps secteur2:%.3f\ntemps secteur3:%.3f\n",Mavoiture.S1tempsP3,Mavoiture.S2tempsP3,Mavoiture.S3tempsP3);
	printf("temps total:%.3f\n",Mavoiture.tempsP3);
	printf("nb arret:%d\n",Mavoiture.stand);

/*------------------------------------------Statistiques-----------------------------------*/	
	
	Mavoiture.tempsTotalMoyen=(Mavoiture.tempsP1+Mavoiture.tempsP2+Mavoiture.tempsP3)/3;
	Mavoiture.S1Moyen=(Mavoiture.S1tempsP1+Mavoiture.S1tempsP2+Mavoiture.S1tempsP3)/3;
	Mavoiture.S2Moyen=(Mavoiture.S2tempsP1+Mavoiture.S2tempsP2+Mavoiture.S2tempsP3)/3;
	Mavoiture.S3Moyen=(Mavoiture.S3tempsP1+Mavoiture.S3tempsP2+Mavoiture.S3tempsP3)/3;
	
	printf("appuyez sur ENTER pour afficher les statistiques:\n");	
	scanf("%c",&next);

	printf("temps secteur 1 moyen:%.3f\n",Mavoiture.S1Moyen);
	printf("temps secteur 2 moyen:%.3f\n",Mavoiture.S2Moyen);
	printf("temps secteur 3 moyen:%.3f\n",Mavoiture.S3Moyen);
	printf("temps total moyen:%.3f\n",Mavoiture.tempsTotalMoyen);


	return 0;
}