#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
#include<stdbool.h>

#define MAX_ETUDIANTS 100
#define MAX_NOM 60

typedef enum {
    MASCULIN = 1,
    FEMININ,
} Sexe;

typedef struct {
	int ine;
	char nom[MAX_NOM];
	char prenom[MAX_NOM];
	Sexe sexe;
	int jour;
	int mois;
	int annee;
} Etudiant;

typedef struct {
	Etudiant* etudiants;
	int nbreEtudiant;
} BaseEtudiant;

//-----------------DÉCLARATION DES FONCTIONS-----------------//
void clean();
void pause();
void effacetampon();
int calculAge(Etudiant* etudiant);
void moyenneAge(BaseEtudiant* base);
void trierparnom(BaseEtudiant* base);
void listeEtudiant(BaseEtudiant* base);
void liberermalloc(BaseEtudiant* base);
void etudiantplusage(BaseEtudiant* base);
void enregistrement (BaseEtudiant* base);
void rechercheparine(BaseEtudiant* base);
void etudiantmoinsage(BaseEtudiant* base);
void modifieretudiant(BaseEtudiant* base);
void etudiantsparmois(BaseEtudiant* base);
void supprimeretudiant(BaseEtudiant* base);
void initialisationEtudiants(BaseEtudiant* base);
void initialisationEtudiants(BaseEtudiant* base);
//----------------------------------------------------//

void pause() {
	printf("\nAppuyez sur Entree pour continuer...");
	getchar();
}

void clean() {
	system("cls || clear");
}

void menuprincipal() {
	clean();
	printf("\n+=============<[ \033[96;4mGESTION DES ETUDIANTS\033[0m ]>================+\n");
	printf("|%-56s|\n"," ");
	printf("|%-56s|\033[56D\t1. Enregistrement\n", " ");
	printf("|%-56s|\033[56D\t2. Liste\n", " ");
	printf("|%-56s|\033[56D\t3. Recherche (par INE)\n", " ");
	printf("|%-56s|\033[56D\t4. Moyenne d'age\n", " ");
	printf("|%-56s|\033[56D\t5. Etudiant le moins age\n", " ");
	printf("|%-56s|\033[56D\t6. Etudiant le plus age\n", " ");
	printf("|%-56s|\033[56D\t7. Etudiants nes a un mois donne\n", " ");
	printf("|%-56s|\033[56D\t8. Suppression\n", " ");
	printf("|%-56s|\033[56D\t9. Modification\n", " ");
	printf("|%-56s|\033[56D\t10. Tri par nom\n", " ");
	printf("|%-56s|\n"," ");
	printf("|========================================================|\n");
	printf("|%-56s|\033[56D \033[91m0- Quitter\033[0m\n", " ");
	printf("|========================================================|\n");
	printf("|%-56s|\033[56D\t    Votre choix : ", " ");
	printf("\n+========================================================+\n\033[26C");
	printf("\033[2A");
}
bool menu(BaseEtudiant* base) {
	int choix;
	bool continuer = true;
	do {
		menuprincipal();
		scanf(" %d", &choix);
		effacetampon();

		switch(choix) {
			case 1:
				clean();
				printf("-=====:[ \033[96;4mENREGISTREMENT D'UN ETUDIANT\033[0m ]:========================-\n|\n");
				enregistrement(base);
				pause();
				break;

			case 2:
				clean();
				printf("-=====:[ \033[96;4mLISTE DES ETUDIANTS\033[0m ]:========================-\n\n");
				listeEtudiant(base);
				pause();
				break;

			case 3:
				clean();
				printf("-=====:[ \033[96;4mRECHERCHE PAR INE\033[0m ]:========================-\n\n");
				rechercheparine(base);
				pause();
				break;

			case 4:
				clean();
				printf("-=====:[ \033[96;4mMOYENNE D'AGE\033[0m ]:========================-\n\n");
				moyenneAge(base);
				pause();
				break;

			case 5:
				clean();
				printf("-=====:[ \033[96;4mETUDIANT LE MOINS AGE\033[0m ]:========================-\n\n");
				etudiantmoinsage(base);
				pause();
				break;

			case 6:
				clean();
				printf("-=====:[ \033[96;4mETUDIANT LE PLUS AGE\033[0m ]:========================-\n\n");
				etudiantplusage(base);
				pause();
				break;

			case 7:
				clean();
				printf("-=====:[ \033[96;4mRECHERCHE ETUDIANT PAR MOIS\033[0m ]:========================-\n\n");
				etudiantsparmois(base);
				pause();
				break;


			case 8:
				clean();
				printf("-=====:[ \033[96;4mSUPPRIMER UN ETUDIANT\033[0m ]:========================-\n\n");
				supprimeretudiant(base);
				pause();
				break;

			case 9:
				clean();
				printf("-=====:[ \033[96;4mMODIFIER LES DONNEES D'UN ETUDIANT\033[0m ]:========================-\n\n");
				modifieretudiant(base);
				pause();
				break;

			case 10:
				clean();
				printf("-=====:[ \033[96;4mTRI DES ETUDIANTS PAR NOM\033[0m ]:========================-\n\n");	
				trierparnom(base);
				pause();
				break;

			case 0:
				clean();
				printf("Programme Termine !\nAu Revoir.");
				continuer = false;
				break;

			default:
				printf("\n\n\033[91mChoix Invalide !\033[0m\n");
				sleep(1);
		}
	} while (choix != '0' && continuer);

	return continuer;
}

void initialisationEtudiants(BaseEtudiant* base) {
	base->etudiants = malloc(MAX_ETUDIANTS * sizeof(Etudiant));
	if (base->etudiants == NULL) {
		printf("\033[91m:( Erreur d'allocatoion memoire\033[0m\n");
		exit(1);
	}
	base->nbreEtudiant = 0;
}

void enregistrement(BaseEtudiant* base) {
	if (base->nbreEtudiant >= MAX_ETUDIANTS) {
		printf("\033[91m:( La base est pleine!\033[0m\n");
		return;
	}

	Etudiant e;
	printf("| Renseignez les donnees de l'etudiant: \n|\n");
retry:
	printf("[--> \033[96mINE \033[0m: ");
	scanf("%d", &e.ine);
	effacetampon();

	for (int i = 0; i < base->nbreEtudiant; i++) {
		if (base->etudiants[i].ine == e.ine) {
			printf("\033[91mCet INE existe deja!\033[0m\n");
			goto retry;
		}
	}

	printf("[--> \033[96mNom\033[0m : ");
	scanf("%[^\n]", e.nom);
	effacetampon();

	printf("[--> \033[96mPrenom \033[0m: ");
	scanf("%[^\n]", e.prenom);
	effacetampon();

	printf("[--> \033[96mSex \033[0m\033[38;5;8m(1 = Masculin; 2 = Feminin)\033[0m: ");
	scanf("%d", (int*)&e.sexe);
	effacetampon();

	do {
		printf("[--> \033[96mDate de naissance\033[0m \033[38;5;8m(JJ MM AAAA)\033[0m : ");
		scanf("%d %d %d", &e.jour, &e.mois, &e.annee);
		effacetampon();

		if (e.mois < 1 || e.mois > 12 || e.jour < 1 || e.jour > 31 || e.annee < 1900 || e.annee > 2024) {
			printf("\033[91m(X) Date invalide! Veuillez reessayer.\033[0m\n");
			continue;
		}
		break;
	} while (1);

	base->etudiants[base->nbreEtudiant++] = e;
	printf("\n\033[96m:) Etudiant enregistre avec succes!\033[0m\n");
}

/*		PREMIERE VERSION DE LA FONCTION ENREGISTREMENT

	void enregistrement (BaseEtudiant* base) {
	if (base->nbreEtudiant >= MAX_ETUDIANTS) {
		printf("\033[91m:(capacite max d'etudiants atteinte.\033[0m\n");
		return;
	}

	Etudiant e;

	printf("Veuillez entrer l'INE: ");
	scanf("%d", &e.ine);
	effacetampon();

	printf("Veuillez entrer le nom: ");
	scanf("%[^\n]", e.nom);
	effacetampon();

	printf("Veuillez entrer le prenom: ");
	scanf("%[^\n]", e.prenom);
	getchar();

	printf("Veuillez entrer le sexe (1 = Masculin; 2 = Feminin): ");
	scanf("%d", (int*)&e.sexe);
	getchar();

	printf("Veuillez entrer le jour de naissance (JJ MM  AAAA): ");
	scanf("%d %d %d", &e.jour, &e.mois, &e.annee);

	base->etudiants[base->nbreEtudiant++] = e;

	printf("\n\033[96mEtudiant enregistre avec succes !\033[0m\n");
}*/


void listeEtudiant(BaseEtudiant* base) {

	printf("[-Liste des Etuduants: \n\n");
	printf("\033[96m%-15s %-20s %-20s %-15s %s\033[0m", "INE", "Preom", "Nom", "Sex","Date de naissance\n");
	printf("--------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < base->nbreEtudiant; i++) {
		printf("%-15d %-20s %-20s %-20s %02d/%02d%/%d\n",
		       base->etudiants[i].ine,
		       base->etudiants[i].prenom,
		       base->etudiants[i].nom,
		       base->etudiants[i].sexe == MASCULIN ? "MASCULIN" : "FEMININ",
		       base->etudiants[i].jour,
		       base->etudiants[i].mois,
		       base->etudiants[i].annee);
	}
}

void rechercheparine(BaseEtudiant* base) {
	if (base->nbreEtudiant == 0) {
		printf("\033[91m:( La base est vide.\033[0m");
		return;
	}

	int ine;
	printf("Entrez l'INE a rechercher: ");
	scanf("%d", &ine);
	getchar();

	for (int i = 0; i < base->nbreEtudiant; i++) {
		if (base->etudiants[i].ine == ine) {
			printf("\033[96m:) Etudiant trouve :\033[0m\n\n");
			printf("\033[96mINE\033[0m: %d\n", base->etudiants[i].ine);
			printf("\033[96mNom\033[0m: %s\n", base->etudiants[i].nom);
			printf("\033[96mPrenom\033[0m: %s\n", base->etudiants[i].prenom);
			printf("\033[96mSexe\033[0m: %s\n", base->etudiants[i].sexe == MASCULIN ? "MASCULIN" : "FEMININ");
			printf("\033[96mDate de Naissance\033[0m: %d/%d/%d\n",
			       base->etudiants[i].jour,
			       base->etudiants[i].mois,
			       base->etudiants[i].annee);
			return;
		}
	}
	printf("\033[91m:( Aucun etudiant trouve avec cet INE.\n\n");
}

int calculAge(Etudiant* etudiant) {
	int anneeActu = 2025;
	int Mois = 12;
	int jour = 24;
	int age = anneeActu - etudiant->annee;
	if(Mois < etudiant->mois || (Mois == etudiant->mois && jour < etudiant->jour)) {
		age--;
	}
	return age;
}

void moyenneAge(BaseEtudiant* base) {
	if (base->nbreEtudiant == 0) {
		printf("\033[91m:( Aucun etudiant enregistre.\033[0m");
		return;
	}

	double sommeAge = 0.0;
	for(int i=0; i < base->nbreEtudiant; i++) {
		sommeAge += calculAge(&base->etudiants[i]);
	}
	printf("La moyenne d'age est de: \033[96m%.2lf\033[0m ans\n", sommeAge/base->nbreEtudiant);
}

void etudiantmoinsage(BaseEtudiant* base) {
	if (base->nbreEtudiant == 0) {
		printf("\033[91m:( La base est vide.\033[0m");
		return;
	}

	int indexmin = 0;
	int agemin = calculAge(&base->etudiants[0]);

	for (int i = 1; i < base->nbreEtudiant; i++) {
		int age_courant = calculAge(&base->etudiants[i]);
		if (age_courant < agemin) {
			agemin = age_courant;
			indexmin = i;
		}
	}

	printf("Etudiant le plus age :\n\n");
	printf("\033[96m%-15s %-20s %-20s %-15s %s\033[0m", "INE", "Nom", "Prenom", "Sex","Date de naissance\n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("%-15d %-20s %-20s %-20s %02d/%02d%/%d\n",
	       base->etudiants[indexmin].ine,
	       base->etudiants[indexmin].prenom,
	       base->etudiants[indexmin].nom,
	       base->etudiants[indexmin].sexe == MASCULIN ? "MASCULIN" : "FEMININ",
	       base->etudiants[indexmin].jour,
	       base->etudiants[indexmin].mois,
	       base->etudiants[indexmin].annee);
}

void etudiantplusage(BaseEtudiant* base) {
	if (base->nbreEtudiant == 0) {
		printf("\033[91m:( Aucun etudiant enregistre.\033[0m\n");
		return;
	}

	int indexmax = 0;
	int agemax = calculAge(&base->etudiants[0]);

	for (int i = 1; i < base->nbreEtudiant; i++) {
		int age = calculAge(&base->etudiants[i]);
		if (age > agemax) {
			agemax = age;
			indexmax = i;
		}
	}

	printf("Etudiant le plus age :\n\n");
	printf("\033[96m%-15s %-20s %-20s %-15s %s\033[0m", "INE", "Nom", "Prenom", "Sex","Date de naissance\n");
	printf("--------------------------------------------------------------------------------------------\n");
	printf("%-15d %-20s %-20s %-20s %02d/%02d%/%d\n\n",
	       base->etudiants[indexmax].ine,
	       base->etudiants[indexmax].prenom,
	       base->etudiants[indexmax].nom,
	       base->etudiants[indexmax].sexe == MASCULIN ? "MASCULIN" : "FEMININ",
	       base->etudiants[indexmax].jour,
	       base->etudiants[indexmax].mois,
	       base->etudiants[indexmax].annee);

}

void etudiantsparmois(BaseEtudiant* base) {
	if (base->nbreEtudiant == 0) {
		printf("\033[91m:( Aucun etudiant enregistre.\033[0m\n");
		return;
	}

	int mois;
	do {
		printf("Entrez le numero du mois (1-12) : ");
		scanf("%d", &mois);
		effacetampon();

		if (mois < 1 || mois > 12) {
			printf("Mois invalide! Veuillez entrer un nombre entre 1 et 12.\n");
			continue;
		}
		break;
	} while (1);

	printf("\nEtudiants nes en %s :\n",
	(char *[12]) {
		"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin",
		"Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"
	}[mois-1]);

	int trouve = 0;
	for (int i = 0; i < base->nbreEtudiant; i++) {
		if (base->etudiants[i].mois == mois) {
			printf("\033[96m%-15s %-20s %-20s %-15s %s\033[0m", "INE", "Nom", "Prenom", "Sex","Date de naissance\n");
			printf("--------------------------------------------------------------------------------------------\n");
			printf("%-15d %-20s %-20s %-20s %02d/%02d%/%d\n",
			       base->etudiants[i].ine,
			       base->etudiants[i].prenom,
			       base->etudiants[i].nom,
			       base->etudiants[i].sexe == MASCULIN ? "MASCULIN" : "FEMININ",
			       base->etudiants[i].jour,
			       base->etudiants[i].mois,
			       base->etudiants[i].annee);
			trouve = 1;
		}
	}

	if (!trouve) {
		printf("\033[91m:( Aucun etudiant n'est ne ce mois-la.\033[0m\n");
	}
}

void supprimeretudiant(BaseEtudiant* base) {
	if (base->nbreEtudiant == 0) {
		printf("\033[91m:( La base est vide.\033[0m\n");
		return;
	}

	int ine;
	printf("Entrez l'INE de l'etudiant a supprimer : ");
	scanf("%d", &ine);
	effacetampon();

	int index = -1;
	for (int i = 0; i < base->nbreEtudiant; i++) {
		if (base->etudiants[i].ine == ine) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		printf("\033[91m:( Aucun etudiant trouve avec cet INE.\033[0m\n");
		return;
	}

	for (int i = index; i < base->nbreEtudiant - 1; i++) {
		base->etudiants[i] = base->etudiants[i + 1];
	}

	base->nbreEtudiant -= 1;
	printf("\033[96m:) Etudiant supprime avec succes!\033[0m\n");
}

void modifieretudiant(BaseEtudiant* base) {
	if (base->nbreEtudiant == 0) {
		printf("\033[91m:( La base est vide.\033[0m\n");
		return;
	}

	int ine;
	printf("[--> Entrez \033[96ml'INE\033[0m de l'etudiant a modifier : ");
	scanf("%d", &ine);
	effacetampon();

	int index = -1;
	for (int i = 0; i < base->nbreEtudiant; i++) {
		if (base->etudiants[i].ine == ine) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		printf("\033[91m:( Aucun etudiant trouve avec cet INE.\033[0m\n");
		return;
	}

	printf("\nModification de l\'etudiant :\n");
	printf("\033[96m1. INE\033[0m: ( %d )", base->etudiants[index].ine);
	printf("\033[96m2. Nom\033[0m: ( %s )\n", base->etudiants[index].nom);
	printf("\033[96m3. Prenom\033[0m:  ( %s )\n", base->etudiants[index].prenom);
	printf("\033[96m4. Sexe\033[0m: ( %s )\n", base->etudiants[index].sexe == MASCULIN ? "MASCULIN" : "FEMININ");
	printf("\033[96m5. Date de naissance\033[0m ( %02d/%02d/%d )\n",
	       base->etudiants[index].jour,
	       base->etudiants[index].mois,
	       base->etudiants[index].annee);

	int choix;
	printf("\nQue souhaitez-vous modifier (1-4) ? : ");
	scanf("%d", &choix);
	effacetampon();

	switch(choix) {
		case 1:
			printf("\033[96mNouvel INE :\033[0m ");
			scanf("%s", &base->etudiants[index].nom);
			break;

		case 2:
			printf("\033[96mNouveau Nom :\033[0m ");
			scanf("%s", &base->etudiants[index].nom);
			break;

		case 3:
			printf("\033[96mNouveau prenom :\033[0m ");
			scanf("%s", &base->etudiants[index].prenom);
			break;


		case 4:
			do {
				printf("[--> \033[96mSex \033[0m\033[38;5;8m(1 = Masculin; 2 = Feminin)\033[0m: ");
				scanf("%d", (int*)&base->etudiants[index].sexe);
				effacetampon();

				if (base->etudiants[index].sexe < 1 || base->etudiants[index].sexe > 2) {
					printf("\033[91m:( Le sexe choisi n'est tout simplement pas valide !!!\033[0m\n");
					continue;
				}
				break;
			} while (1);
			break;

		case 5:
			do {
				printf("\033[96mNouvelle date de naissance (JJ/MM/AAAA) :\033[0m ");
				scanf("%d/%d/%d",
				      &base->etudiants[index].jour,
				      &base->etudiants[index].mois,
				      &base->etudiants[index].annee);
				effacetampon();

				if (base->etudiants[index].mois < 1 || base->etudiants[index].mois > 12 ||
				        base->etudiants[index].jour < 1 || base->etudiants[index].jour > 31 ||
				        base->etudiants[index].annee < 1960 || base->etudiants[index].annee > 2024) {
					printf("\033[91m:( Date invalide! Veuillez reessayer.\033[0m\n");
					continue;
				}
				break;
			} while (1);
			break;

		default:
			printf("\033[91m:( Choix invalide!\033[0m\n");
			return;
	}

	printf("\033[96m:) Modification effectuee avec succes!\033[0m\n");
}

void trierparnom(BaseEtudiant* base) {
	if (base->nbreEtudiant == 0) {
		printf("\033[91m:( Il n'y a aucun etudiant enregistre !\033[0m\n");
		return;
	} else if (base->nbreEtudiant == 1) {
		printf("\033[91m Nb: Tri non necessaire car il existe un seul etudiant !\033[0m\n");
		return;
	}

	//Note: tri non optimisé, à revoir.
	int echange;
	for (int i = 0; i < base->nbreEtudiant - 1; i++) {
		echange = 0;
		for (int j = 0; j < base->nbreEtudiant - i - 1; j++) {
			if (strcmp(base->etudiants[j].nom, base->etudiants[j + 1].nom) > 0) {

				Etudiant temp = base->etudiants[j];
				base->etudiants[j] = base->etudiants[j + 1];
				base->etudiants[j + 1] = temp;
				echange = 1;
			} else if (strcmp(base->etudiants[j].nom, base->etudiants[j + 1].nom) == 0) {
				if (strcmp(base->etudiants[j].prenom, base->etudiants[j + 1].prenom) > 0) {
					Etudiant temp = base->etudiants[j];
					base->etudiants[j] = base->etudiants[j + 1];
					base->etudiants[j + 1] = temp;
					echange = 1;
				}
			}
		}
		if (!echange) break;
	}

	printf("\033[96m:) Liste triee avec succes!\033[0m\n\n");
	listeEtudiant(base);
}

void liberermalloc(BaseEtudiant* base) {
	if (base->etudiants != NULL) {
		free(base->etudiants);
		base->etudiants = NULL;
		base->nbreEtudiant = 0;
	}
}

void effacetampon() {
	int c;
	while((c = getchar() != '\n' && c != EOF));
}

int main () {
	BaseEtudiant base;

	initialisationEtudiants(&base);

	menu(&base);

	liberermalloc(&base);
}
