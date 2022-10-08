#ifndef mini_h_included
#define mini_h_included

//Déclaration de la structure dictionnaire
typedef struct{
	char nom[30],sign[40];
}dict;
///////////////////////
//Déclaration d'un maillon
typedef struct element{
	dict d;
	struct element *next;
}element;
///////////////////
//Créer les data d'un élement
element *creedic(char x1[30],char x2[40]){
	element *e=(element*)malloc(sizeof(element));
	if(e==NULL){
		printf("Erreur\n");
		exit(0);
	}
	strcpy(e->d.nom,x1);
	strcpy(e->d.sign,x2);
	return e;
}

////////////////
//Ajouter à la fin
element *ajoutfn(element *head,char x1[30],char x2[40]){
    element *adr,*e;
	e=creedic(x1,x2);
	e->next=NULL;
	if(head==NULL) head=e;
	else{
		adr=head;
		while(adr->next!=NULL) adr=adr->next;
		adr->next=e;
	}
	return head; 
}
//////////////////

////////////////
//Ajout des mots du fichier text au dictionnaire
element *ajoutaudic(element *t,FILE *f1,int po){
	f1=fopen("mots.txt","r");
	char nom[30],sing[40],p[2];
	int j,j2;
	while(fscanf(f1,"%s%s%s",nom,p,sing)==3){
		j=nom[0]-'A';
		j2=nom[0]-'a';
		if(j==po || j2==po){
			t=ajoutfn(t,nom,sing);
		}				
	}
	rewind(f1);
	return t;
}

////////////////////////////////////////////////
//Affichage des listes
void affdict(element *head){
	if(head==NULL){
		printf("Il n'y a pas des mots dans le dictionnaire qui commence par votre lettre saisie!\n");
		return;
	}
	element *adr=head;int i,n;char c[40];
	while(adr!=NULL){
		n=strlen(adr->d.sign);
		strcpy(c,adr->d.sign);
		for(i=0;i<n;i++){
			if(c[i]=='_') c[i]=' ';
		}
		printf("%s : %s \n",adr->d.nom,c);
		printf("---------------------------\n");
		adr=adr->next;
	}
	printf("\n");
}

////////////////////////
//Fonction qui permet la comparaison correcte des chaines de caractères
int strcomparaison(char ch1[30],char ch2[30]){
	char c,c1;int i,ct1=0,ct2=0;
    int j,j1;
    ct1=strlen(ch1);
	ct2=strlen(ch2);
    i=0;
    if(ct1<ct2){
        while((ch1[i]==ch2[i] || abs(ch1[i]-ch2[i])==32)&&i<ct1) i++;
    }else if(ct1>=ct2){
	    while((ch1[i]==ch2[i] || abs(ch1[i]-ch2[i])==32)&&i<ct2) i++;            
    }
    c=ch1[i];
    c1=ch2[i];
    if(c==c1) return 0;//chaine 1 = chaine 2
    	
    if(c>='A' && c<='Z') j=c-'A';
    else if(c>='a' && c<='z') j=c-'a';
     
    if(c1>='A' && c1<='Z') j1=c1-'A';
    else if(c1>='a' && c1<='z') j1=c1-'a';
     
    if(j<j1) return -1;//chaine 1 avant chaine 2
   	if(j>j1) return 1;//chaine 1 apres chaine 2
}
//////////////////////////////////////////
////////////////////
//Tri par ordre alphabétique
element *trialph(element *head){
	if(head==NULL) return head;
	element *adr1=head,*adr2;char c[30],c2[40];
	while(adr1!=NULL){
		adr2=adr1;
		while(adr2!=NULL){
			if(strcomparaison(adr1->d.nom,adr2->d.nom)>0){
				strcpy(c,adr1->d.nom);
				strcpy(c2,adr1->d.sign);
				strcpy(adr1->d.nom,adr2->d.nom);
				strcpy(adr1->d.sign,adr2->d.sign);
				strcpy(adr2->d.nom,c);
				strcpy(adr2->d.sign,c2);
			}
			adr2=adr2->next;
		}
		adr1=adr1->next;
	}
	
	return head;
}
///////////////////////////
//2).Rechercher la signification d'un mot donné
void rechercheMot(element *head,char m[30]){
	if(head==NULL) goto l;
	element *adr=head;char c[40];int n,i;
	while(adr!=NULL){
		if(strcomparaison(m,adr->d.nom)==0){
			n=strlen(adr->d.sign);
			strcpy(c,adr->d.sign);
			for(i=0;i<n;i++){
				if(c[i]=='_') c[i]=' ';
			}
			
			printf("%s : %s \n",adr->d.nom,c);
			
			return;
		}
		adr=adr->next;
	}
	l:
	printf("Mot introuvable!\n");
}
////////////////////////////
//Fonction de validation d'un mot
int mot_valid(char x[30]){
	int i=0,n=0;
	while(x[i]!='\0'){
		if(isalpha(x[i])==0){
			n=1;
			break;
		}
		i++;
	}
	if(n==1) return 0;
	return 1;
}

//////////////////////////////
//Fonction de validation du fichier text(dictionnaire initial)
FILE *valid_fic(FILE *f1){
	char nom[30],p[2],sing[40];int i,j,k,n=0;
	char x[50][30],x2[50][40];
	while(fscanf(f1,"%s%s%s",nom,p,sing)==3){
		strcpy(x[n],nom);
		strcpy(x2[n],sing);
		n++;
			
	}
	fclose(f1);
	f1=fopen("mots.txt","w");
	for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            while(strcomparaison(x[i],x[j])==0||mot_valid(x[j])==0){
                k=j;
                do{
                	strcpy(x[k],x[k+1]);
                    strcpy(x2[k],x2[k+1]);
                    k++;
                }while(k<n);
                n--;
            }	
        }
    }
    
    if(mot_valid(x[0])==0){
        k=0;
        do{
            strcpy(x[k],x[k+1]);
            strcpy(x2[k],x2[k+1]);
            k++;
        }while(k<n);
        n--;
    }	
    
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            while(strcomparaison(x2[i],x2[j])==0){
                k=j;
                do{
                	strcpy(x2[k],x2[k+1]);
                	strcpy(x[k],x[k+1]);
                	k++;
                }while(k<n);
                n--;
            }	
        }
    }
    for(i=0;i<n;i++){
        fprintf(f1,"%s\t%s\t%s\n",x[i],p,x2[i]);
	}
	fclose(f1);	
	return f1;
}

/////////////////////////////////////////
//Suppression d'un element du fichier
FILE *supp(FILE *f1,char x[30]){
	f1=fopen("mots.txt","r");
	FILE *f2=fopen("aide.txt","w");
	char nom[30],p[2],sing[40];
	rewind(f1);
	while(fscanf(f1,"%s%s%s",nom,p,sing)==3){
		if(strcomparaison(nom,x)!=0){
			fprintf(f2,"%s\t%s\t%s\n",nom,p,sing);
		}
	}
	fclose(f2);
	fclose(f1);
	f2=fopen("aide.txt","r");
	f1=fopen("mots.txt","w");
	while(fscanf(f2,"%s%s%s",nom,p,sing)==3){
		fprintf(f1,"%s\t%s\t%s\n",nom,p,sing);
	}
	fclose(f1);
	fclose(f2);

	return f1;	
    
}

////////////////////////////////////////
//3).Supprimer un mot
element *supprimerMot(element *head,char m[30],FILE *f1){
	if(head==NULL) goto l;
	element *adr,*p;
	if(strcomparaison(head->d.nom,m)==0){
		p=head;
		head=head->next;
		rewind(f1);
		f1=supp(f1,p->d.nom);
		free(p);
		return head;
	}
	adr=head;
	while(adr->next!=NULL){
		if(strcomparaison(adr->next->d.nom,m)==0){
			p=adr->next;
			adr->next=adr->next->next;
			rewind(f1);
			f1=supp(f1,p->d.nom);
			free(p);
			printf("%s est supprime.\n",m);
			return head;
		}
		adr=adr->next;
	}
	l:
	printf("le mot est introuvable!\n");
	
	return head;
}	

/////////////////////////////////////////	
//4).Supprimer toutes les mots commançant par une lettre donnée
element *supptout(element *head,FILE *f1){
	if(head==NULL){
		printf("Il n'y a pas des mots dans le dictionnaire qui commence par votre lettre saisie!\n");
		return head;
	}
	element *p;
	while(head!=NULL){
		p=head;
		head=head->next;
		rewind(f1);
		f1=supp(f1,p->d.nom);
		free(p);
	}
	printf("Toutes les mots sont supprimees.\n");
	return head;
}

///////////////////////////////////////////////
//Fonction qui compte le nbre des lignes dans fichier texte
int compte(FILE *f){
    char c;int nbl=0;
    while((c=fgetc(f))!=EOF){
                           if(c=='\n') nbl++;
    }
    return nbl; 
}

////////////////////////////////////////
//tester l'existence d'un mot et une signification
int mot_existe(FILE *f1,char x[30],char x2[40],int ch){
	int n=compte(f1);
	rewind(f1);
	char nom[50][30],p[2],sing[50][40];
	int i=0;
	while(fscanf(f1,"%s%s%s",nom[i],p,sing[i])==3){
		i++;
	}
	if(ch==0){
		for(i=0;i<n;i++){
			if(strcomparaison(x,nom[i])==0 ||strcomparaison(x2,sing[i])==0){
				return 0;
			}
		}
	}else if(ch==1){
		for(i=0;i<n;i++){
			if(strcomparaison(x,nom[i])==0){
				return 0;
			}
		}
	}else if(ch==2){
		for(i=0;i<n;i++){
			if(strcomparaison(x2,sing[i])==0){
				return 0;
			}
		}
	}
	
	return 1;
}

////////////////////////////////////////
/////////////////////////////////////////

FILE *ecrirefichier(FILE *f1,char x[30],char x2[40]){
	f1=fopen("mots.txt","r");
	int n=compte(f1),i=0;
	rewind(f1);
	char nom[50][30],p[2],sing[50][40];
	while(fscanf(f1,"%s%s%s",nom[i],p,sing[i])==3){
		i++;
	}
	if(mot_existe(f1,x,x2,0)==1){
		fclose(f1);
	
		f1=fopen("mots.txt","w");
		if(f1){
		for(i=0;i<n;i++){
			fprintf(f1,"%s\t%s\t%s\n",nom[i],p,sing[i]);
		}
		fprintf(f1,"%s\t%s\t%s\n",x,p,x2);
		fclose(f1);
	}else printf("Erreur\n");
	}
	
	
	return f1;
}

////////////////////////////////////////
//5).Ajouter un mot et sa signification 
element *ajouter_mot(element *head,char x[30],char x2[40],FILE *f1){
	element *adr,*e;
	e=creedic(x,x2);
	if(head==NULL){
		e->next=NULL;
		head=e;
		goto l;
	}
	if(strcomparaison(x,head->d.nom)<0){
		e->next=head;
		head=e;
		goto l;
	}
	adr=head;
	while(adr->next!=NULL){
		if(strcomparaison(x,adr->next->d.nom)<0){
			e->next=adr->next;
			adr->next=e;
			goto l;
		}
		adr=adr->next;
	}

	e->next=NULL;
	adr->next=e;
l:
	f1=ecrirefichier(f1,x,x2);
	printf("C'est ajoute!\n");
	
		
	
	return head;
}

//////////////////////////////////////
//7).Compter le nbre de mots qui commence par une lettre donnée
int comptmot(element *head){
	int nbm=0;
	element *adr=head;
	while(adr!=NULL){
		nbm++;
		adr=adr->next;
	}
	return nbm;
}
/////////////////////////////////////

//8).Compter le nbre de mots du dictionnaire
int comptmotdict(FILE *f1){
	f1=fopen("mots.txt","r");
	return compte(f1);
}

/////////////////////////////////////
//Modification d'une signifaication dans un fichier
FILE *modifierFile(FILE *f1,char x[30],char x2[40]){
	f1=fopen("mots.txt","r");
	int n=compte(f1),i=0;
	rewind(f1);
	char nom[50][30],p[2],sing[50][40];
	while(fscanf(f1,"%s%s%s",nom[i],p,sing[i])==3){
		i++;
	}
	fclose(f1);
	f1=fopen("mots.txt","w");
	if(f1){
		for(i=0;i<n;i++){
			if(strcomparaison(x,nom[i])==0){
				strcpy(sing[i],x2);
			}
			fprintf(f1,"%s\t%s\t%s\n",nom[i],p,sing[i]);
		}
		
		fclose(f1);
	}else printf("Erreur\n");
	return f1;
}
///////////////////////////////////////////

//Modification d'une signifaication
element *modifier_sign(element *head,char x[30],char x2[40],FILE *f1){
	element *adr=head;
	while(adr!=NULL){
		if(strcomparaison(x,adr->d.nom)==0){
			strcpy(adr->d.sign,x2);
			goto l;
		}
		adr=adr->next;
	}
	l:
	f1=modifierFile(f1,x,x2);
	printf("C'est modifie!\n");
	return head;
}
/////////////////////////////////////////

#endif
