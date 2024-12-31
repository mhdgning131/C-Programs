#include <stdio.h>
#include <string.h>

int main() {
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int taille = strlen(alphabet);
	
    printf("Carre de Vigenere:\n\n");
    printf("\033[47m   \033[0m");
    for (int i = 0; i < taille; i++) {
        if (i == taille - 1) {
        	printf("\t\033[30;47m%c\033[0m", alphabet[i]);
		}
		else printf("\t\033[30;47m%c  \033[0m", alphabet[i]);
    }
    printf("\n");
    
    for (int i = 0; i < taille; i++) {
        printf("\t\033[30;47m%c \033[0m ", alphabet[i]);
        for (int j = 0; j < taille; j++) {
            char lettre = alphabet[(i + j) % taille];
            printf("%c  ", lettre);
        }
        printf("\n");
    }
}

