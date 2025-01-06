#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#ifdef _WIN32

int precedence(const char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double applyOp(const double a, const double b, const char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : 0;
        default: printf("Erreur !");
    }
    return 0;
}


double evaluate(const char* expr) {
    double values[100];
    char ops[100];
    int valTop = -1, opsTop = -1;

	int i;
    for (i = 0; expr[i]; i++) {

        if (expr[i] == ' ') continue;

        if (isdigit(expr[i])) {
            double val = 0;
            while (i < strlen(expr) && (isdigit(expr[i]) || expr[i] == '.')) {
                if (expr[i] == '.') {
                    i++;
                    double frac = 0.1;
                    while (i < strlen(expr) && isdigit(expr[i])) {
                        val += (expr[i] - '0') * frac;
                        frac /= 10;
                        i++;
                    }
                    i--; 
                } else {
                    val = (val * 10) + (expr[i] - '0');
                }
                i++;
            }
            i--; 
            values[++valTop] = val;
        }

        else if (expr[i] == '(') {
            ops[++opsTop] = expr[i];
        }

        else if (expr[i] == ')') {
            while (opsTop >= 0 && ops[opsTop] != '(') {
                double val2 = values[valTop--];
                double val1 = values[valTop--];
                char op = ops[opsTop--];
                values[++valTop] = applyOp(val1, val2, op);
            }
            opsTop--;
        }

        else {
            while (opsTop >= 0 && precedence(ops[opsTop]) >= precedence(expr[i])) {
                double val2 = values[valTop--];
                double val1 = values[valTop--];
                char op = ops[opsTop--];
                values[++valTop] = applyOp(val1, val2, op);
            }
            ops[++opsTop] = expr[i];
        }
    }

    while (opsTop >= 0) {
        double val2 = values[valTop--];
        double val1 = values[valTop--];
        char op = ops[opsTop--];
        values[++valTop] = applyOp(val1, val2, op);
    }

    return values[valTop];
}

int main() {
    char reponse;
	char expr[100];
    do {
    	system ("cls");
    	memset (expr, 0, sizeof(expr));
    	printf("Entrez une expression : ");
    	fgets(expr, 100, stdin);
    	expr[strcspn(expr, "\n")] = '\0'; 
        const double result = evaluate(expr);
    	if (result == floor(result)){
			printf("Resultat :\033[32m %d\033[0m\n\n", (int)result);
		} 
		else {
			printf("Resultat :\033[32m %.2lf\033[0m\n\n", result);
		} 
    	
    	printf("Voulez-vous continuer (O/N): ");
    	scanf(" %c", &reponse);
    	while (getchar() != '\n');
	}while (reponse == 'o' || reponse == 'O');
	
	printf("Programme termine !\n");
    return 0;
    #endif
}
