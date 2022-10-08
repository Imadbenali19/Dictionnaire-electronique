#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"mini.h"
main(){
	FILE *fic=fopen("mots.txt","r");
	
	if(fic){
	
		fic=valid_fic(fic);
		rewind(fic);
		fic=fopen("mots.txt","r");
		int ch,ch2,tem,tr;char c;int j,j1;char mot[30],sign[40],src[35];
		int i,k,n;
		element *t[26];
		for(i=0;i<26;i++){
			t[i]=NULL;
		}
		
		for(i=0;i<26;i++){
			rewind(fic);
			t[i]=ajoutaudic(t[i],fic,i);
			//affdict(t[i]);
		}
		//affdict(t[0]);
		
//Menu electronique
	do{
		printf("************************Menu Dictionnaire Electronique**************************\n");
		printf("1. Afficher la liste triee par ordre alphabetique des mots commençant par une lettre donnee.\n");
		printf("2. Rechercher la signification d’un mot donnee.\n");
		printf("3. Supprimer un mot donne.\n");
		printf("4. Supprimer tous les mots commencant par une lettre donnee.\n");
		printf("5. Ajouter au dictionnaire un mot donne ainsi que sa signification.\n");
		printf("6. Modifier la signification d'un mot existant dans le dictionnaire.\n");
		printf("7. Compter le nombre de mots commençant par une lettre donnee.\n");
		printf("8. Compter le nombre de mots du dictionnaire.\n");
		printf("9. Quitter.\n");
		do{
			printf("Donnez votre choix : ");
			scanf("%d",&ch);
		}while(ch!=1&&ch!=2&&ch!=3&&ch!=4&&ch!=5&&ch!=6&&ch!=7&&ch!=8&&ch!=9);
		if(ch==9){
			printf("Au revoir!");
			exit(1);
		}
		switch(ch){
			case 1:
				rewind(fic);
				
				do{
					printf("Donnez une lettre : ");
					fflush(stdin);scanf("%c",&c);
				}while(c<'A'||c>'Z'&&c<'a'||c>'z');
				j=c-'A';j1=c-'a';
				if(c>='A'&&c<='Z'){
					t[j]=trialph(t[j]);
					affdict(t[j]);
				}else{
					t[j1]=trialph(t[j1]);
					affdict(t[j1]);
				}		
			break;
			
			case 2:
				printf("Donnez un mot a rechercher : ");
				fflush(stdin);gets(mot);
				j=mot[0]-'A';j1=mot[0]-'a';
				if(mot[0]>='A'&&mot[0]<='Z') rechercheMot(t[j],mot);
				else if(mot[0]>='a'&&mot[0]<='z') rechercheMot(t[j1],mot);
			break;
			
			case 3:
				rewind(fic);
				printf("Donnez un mot a supprimer : ");
				fflush(stdin);gets(mot);
				j=mot[0]-'A';j1=mot[0]-'a';
				if(mot[0]>='A'&&mot[0]<='Z') t[j]=supprimerMot(t[j],mot,fic);
				else if(mot[0]>='a'&&mot[0]<='z') t[j1]=supprimerMot(t[j1],mot,fic);
				
			break;
			
			case 4:
				rewind(fic);
				do{
					printf("Donnez une lettre : ");
					fflush(stdin);scanf("%c",&c);
				}while(c<'A'||c>'Z'&&c<'a'||c>'z');
				j=c-'A';j1=c-'a';
				//affdict(t[j1]);
				if(c>='A'&&c<='Z') t[j]=supptout(t[j],fic);
				else t[j1]=supptout(t[j1],fic);		
			break;
			
			case 5:
				rewind(fic);
				tem=1;
				do{
					rewind(fic);
					if(tem==0){
						do{
							printf("Voulez vous continuer : (1 pour oui ; 0 pour non)");
							scanf("%d",&ch2);
						}while(ch2!=0 && ch2!=1);
						if(ch2==0) goto l;
					}
					do{
						printf("Donnez le mot : ");
						fflush(stdin);gets(mot);
					}while(mot_valid(mot)==0);
					printf("Donnez la signification : ");
					fflush(stdin);gets(sign);
					n=strlen(sign);
					for(k=0;k<n;k++){
						if(sign[k]==' ') sign[k]='_';
					}
					if(mot_existe(fic,mot,sign,0)==0){
						tem=0;
						printf("Mot ou signification deja existe dans le dictionnaire!\n");
					}
					rewind(fic);
				}while(mot_existe(fic,mot,sign,0)==0);
				rewind(fic);
				j=mot[0]-'A';j1=mot[0]-'a';
				if(mot[0]>='A'&&mot[0]<='Z'){
					t[j]=ajouter_mot(t[j],mot,sign,fic);
					affdict(t[j]);
				}
				else if(mot[0]>='a'&&mot[0]<='z') t[j1]=ajouter_mot(t[j1],mot,sign,fic);
				l:	
			break;
			
			case 6:
				rewind(fic);
				tr=0;
				printf("Donnez la source de la signification de votre signification : ");
				fflush(stdin);gets(src);
				if(strcomparaison(src,"Larousse")!=0 && strcomparaison(src,"Littre")!=0  ){
					printf("Desole! On ne peut accepter que les sources les bien connuees telles que (Larousse , Littre).\n");
					goto l1;
				}
				while(1){
					do{
						rewind(fic);
						printf("Donnez le mot dont vous voulez modifier sa signification : ");
						fflush(stdin);gets(mot);
						if(mot_existe(fic,mot,sign,1)!=0){
							printf("Mot non existant!\n");
						}
						rewind(fic);
						if(tr==2){
							printf("Vieullez essayez apres un moment.\n");
							goto l1;
						}
						tr++;
					}while(mot_existe(fic,mot,sign,1)!=0);
					tr--;
					do{
						rewind(fic);
						printf("Donnez la nouvelle signification : ");
						fflush(stdin);gets(sign);
						n=strlen(sign);
						for(k=0;k<n;k++){
							if(sign[k]==' ') sign[k]='_';
						}
						rewind(fic);
						if(mot_existe(fic,mot,sign,2)==0){
							printf("Signification deja existante!\n!");
						}
						rewind(fic);
						if(tr==2){
							printf("Vieullez essayez apres un moment.\n");
							goto l1;
						}
						tr++;	
					}while(mot_existe(fic,mot,sign,2)==0);
					break;
					
				}
				rewind(fic);
				j=mot[0]-'A';j1=mot[0]-'a';
				if(mot[0]>='A'&&mot[0]<='Z'){
					t[j]=modifier_sign(t[j],mot,sign,fic);
					affdict(t[j]);
				}
				else if(mot[0]>='a'&&mot[0]<='z') t[j1]=modifier_sign(t[j1],mot,sign,fic);
				
				l1:	
				
			break;
			
			case 7:
				rewind(fic);
				do{
					printf("Donnez une lettre : ");
					fflush(stdin);scanf("%c",&c);
				}while(c<'A'||c>'Z'&&c<'a'||c>'z');
				j=c-'A';j1=c-'a';
				if(c>='A'&&c<='Z') printf("Le nbre de mots qui commence par %c est : %d\n",c,comptmot(t[j]));
				else printf("Le nbre de mots qui commence par %c est : %d\n",c,comptmot(t[j1]));
			break;
			
			case 8:
				rewind(fic);
				printf("Le nbre de mots du dictionnaire est : %d\n",comptmotdict(fic));
			break;	
				
		}
		
	}while(ch!=9);	
		
		fclose(fic);
		
		
	}else printf("Erreur d'ouverture du fichier\n");
	
	
	system("pause");
}
