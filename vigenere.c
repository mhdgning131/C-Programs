#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main() {
	char chaine[100];
	char cle[100];
	char texte[100];
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	int poschaine, poscle, postexte;
	int lenchaine, lencle, choix;
	
retry:
	printf("Veuillez choisir une option: \n");
	printf("  1. Chiffrement\n  2. Dechiffrement");
	scanf("%d", &choix);
	while (getchar() != '\n');
	
	system("cls || clear");
	printf("Entrez une chaine de caracteres : ");
	scanf("%[^\n]", chaine);
	while (getchar() != '\n');
	
	printf("Entrez la cle : ");
	scanf("%[^\n]", cle);
	while (getchar() != '\n');
	
	for (int i = 0; chaine[i]; i++) {
		chaine[i] = tolower(chaine[i]);
	}
	for (int i = 0; cle[i]; i++) {
		cle[i] = tolower(cle[i]);
	}
	
	lenchaine = strlen(chaine);
	lencle = strlen(cle);
	
	int texteIndex = 0;
	for (int i = 0; i < lenchaine; i++) {
		poscle = i % lencle;
		
		poschaine = chaine[i] - 'a';
		poscle = cle[poscle] - 'a';
		
		if (choix == 1) {
			postexte = (poschaine + poscle) % 26;
			texte[texteIndex++] = alphabet[postexte];
		}else if(choix == 2) {
			postexte = (poschaine - poscle + 26) % 26;
			texte[texteIndex++] = alphabet[postexte];
		}else {
			system("cls || clear");
			goto retry;
		}
	}
	
	texte[texteIndex] = '\0';
	
	printf("\nChiffre de Vigenere :\n");
	printf("Texte original : %s\n", chaine);
	printf("Cle : %s\n", cle);
	printf("Texte chiffre : %s\n", texte);
}
