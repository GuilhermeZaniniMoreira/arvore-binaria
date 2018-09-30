#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct no {
    int valor;
    no *esq;
    no *dir;
    no *cima;
};

no *primeiro = NULL;

// protótipos das funções
void inserir(int valor);
void mostrarElemento();

int main();
int altura(struct no* no);
int desbalanceamento(struct no* no);

struct no* acharMenor(struct no *no);
struct no* excluir(struct no* primeiro, int valor);

void preOrdem(struct no* no);
void posOrdem(struct no* no);
void emOrdem(struct no* no);

int opcao = 0;
int valor = 0;
int profundidade = 0;
int profundidadeGlobal = 0;

int main() {
	
	setlocale(LC_ALL, "Portuguese");
	
	for (;;) {
		
		printf ("\n 1 - Inserir");
		printf ("\n 2 - Excluir");
		printf ("\n 3 - Mostrar elemento");
		printf ("\n 4 - Profundidade da árvore");
		printf ("\n 5 - Percurso");
		printf ("\n 6 - Desbalanceamento");
		printf ("\n 7 - Sair");
		printf ("\n Digite:  ");
		scanf ("%d", &opcao);
		
		if (opcao == 1) {
			 	
			printf ("\n Digite o valor: ");
			scanf ("%d", &valor);
			 	
			inserir(valor);
			 	
			printf ("\n %d foi inserido!\n", valor);
			
			system("pause");
			
			system("cls");
			
		} else if (opcao == 2) {
			 	
			printf ("\n Digite o valor que deseja excluir:  ");
			scanf ("%d", &valor);
			
			excluir(primeiro, valor);
			
			printf ("\n%d foi excluido!", valor);
			
			system("cls");
				
		} else if (opcao == 3) {
			mostrarElemento();
		} else if (opcao == 4) {
			
			system("cls");
			printf ("\n A profunidade é: %i\n", profundidadeGlobal);
			system("pause");
			
		} else if (opcao == 5) {
			
			printf ("\n 1 - Em Ordem");
			printf ("\n 2 - Pré Ordem");
			printf ("\n 3 - Pós Ordem");
			printf ("\n Digite: ");
			scanf ("%d", &opcao);
			
			if (opcao == 1) {
				printf ("\n");
				emOrdem(primeiro);
				printf ("\n");
				system("pause");
				system("cls");
			} else if (opcao == 2) {
				printf ("\n");
				preOrdem(primeiro);
				printf ("\n");
				system("pause");
				system("cls");
			} else if (opcao == 3) {
				printf ("\n");
				posOrdem(primeiro);
				printf ("\n");
				system("pause");
				system("cls");
			} else {
				printf ("\n Opção inválida!");
			}
			
		} else if (opcao == 6) {
			int valor = desbalanceamento(primeiro);
			printf ("\n %i \n", valor);
		} else if (opcao == 7) {
			system("pause");
			exit(0);		
		} else {
			printf ("\n Opção inválida!");
		}
	}
}

void inserir(int valor) {
	
	int profundidadeLocal = 0;
	
    no *temp;
    struct no *p = (struct no*)malloc(sizeof(struct no));
    p -> valor = valor;
    p -> esq = NULL;
    p -> dir = NULL;
    
    if (primeiro == NULL) {
    	p -> cima = NULL;
        primeiro = p;
    } else {
    	
		temp = primeiro;
		
        while(1) {
        	
        	// se parametro for menor que valor do primeiro
            if (valor < temp -> valor) {
            	
            	profundidadeLocal++;
            	/*
				 irá settar a esquerda pois é menor
				 se esq do primeiro for igual a NULL então irá settar nesta possição e retornar ao menu (break)
				*/
                if (temp -> esq == NULL) {
                	p -> cima = temp;
                	temp -> esq = p;
                    break;
                } else {
                	/* 
					 se esq for diferente de NULL então temporário não terá mais o valor de priemeiro
                     e terá o valor da esquerda, assim, com o while será executando novamente com outro valor o temp
                	*/
                	
                	temp = temp -> esq;
				}
			
			// se parametro for maior que o valor do primeiro	
            } else {
            	
            	profundidadeLocal++;
            	
				if(temp -> dir == NULL) {
					p -> cima = temp;
                    temp -> dir = p;
                    break;
                } else {
                  	temp = temp -> dir;
				}  
			}
        }
    }
    
    if (profundidadeLocal > profundidadeGlobal) {
    	profundidadeGlobal = profundidadeLocal;
	}
}


void mostrarElemento() {
	
	if (primeiro == NULL) {
		printf ("\n Não há elementos!");
	} else {
		
		no* temp = primeiro;
		
		while(1) {
			
			system("cls");
			
			printf ("\n\n Elemento atual: %d\n\n", temp -> valor);
			
			printf ("\n 1 - Cima");
			printf ("\n 2 - Esquerda");
			printf ("\n 3 - Direita");
			printf ("\n 4 - Retornar ao menu");
			printf ("\n Digite: ");
			scanf ("%d", &opcao);
			
			if (opcao == 1) {
				
				if (temp -> cima == NULL) {
					printf ("\n Não há elementos\n");
					system("pause");
					mostrarElemento();
				} else {
					temp = temp -> cima;
				}
				
			} else if (opcao == 2) {
				
				if (temp -> esq == NULL) {
					printf ("\n Não há elementos\n");
					system("pause");
					mostrarElemento();
				} else {
					temp = temp -> esq;
				}
				
			} else if (opcao == 3) {
								
				if (temp -> dir == NULL) {
					printf ("\n Não há elementos\n");
					system("pause");
					mostrarElemento();
				} else {
					temp = temp -> dir;
				}
				
			} else if (opcao == 4) {
				
				system("cls");
				main();
				
			} else {
				printf ("\n Opção inválida!");
			}
		}
	}
}

int desbalanceamento(struct no* no) {
	if (no == NULL) {
		return 0;
	} else {
		return (altura(no->dir) - altura(no->esq));
	}
}

int altura(struct no* no)  {

   if (no == NULL) {
       return 0;
   } else {
   	
   		int alturaEsq = altura(no->esq);
   		int alturaDir = altura(no->dir);
   		
   		if (alturaEsq > alturaDir) {
   			return 1 + alturaEsq;
		} else {
			return 1 + alturaDir;
		}
   }
}

void preOrdem(struct no* no) {
	
    if (no == NULL) {
    	return;
	}
	
    printf (" %i - ", no->valor);
    
    preOrdem(no->esq);
	preOrdem(no->dir);
}

void posOrdem(struct no* no) {
	
    if (no == NULL) {
    	return;
	}
	
	posOrdem(no->esq);
	
	posOrdem(no->dir);
	
    printf (" %i - ", no->valor);
    
}

void emOrdem(struct no* no) {
	
	if (no == NULL) {
		return;
	}
	
	emOrdem(no->esq);
	printf (" %i - ", no->valor);
	emOrdem(no->dir);
}

struct no* acharMenor(struct no* no) {
    struct no* atual = no;
 
    /* achar menor valor */
    while (atual -> esq != NULL) {
    	atual = atual -> esq;
	}
 
    return atual;
}

struct no* excluir(struct no* primeiro, int valor) {
    // se primeiro for igual a NULL
    if (primeiro == NULL) {
    	printf ("\n Não existem elementos!\n");
    	system("pause");
    	main();
	}
	
	/* 
		Se valor que deseja deletar é menor que o valor do primeiro
		então valor está no lado esquerdo da arvore
		por recursividade irá percorrer a árvore até encontrar
		quando encontrar irá executar o else
	*/
    if (valor < primeiro -> valor) {
        primeiro -> esq = excluir(primeiro -> esq, valor);
        main();
	/* 
		Se valor que deseja deletar é maior que o valor do primeiro
		então valor está no lado direito da arvore
		por recursividade irá percorrer a árvore até encontrar
		quando encontrar irá executar o else
	*/
    } else if (valor > primeiro -> valor) {
        primeiro -> dir = excluir(primeiro -> dir, valor);
        main();
        
    // Se valor que deseja deletar é igual ao valor do primeiro
    } else {
        // se primeiro tem apenas um filho ou não tem nenhum
        if (primeiro -> esq == NULL) { // se esq for NULL temp recebe o nó a direita do nó atual
            struct no *temp = primeiro -> dir;
            free(primeiro);
            return temp;
        } else if (primeiro -> dir == NULL) { // se esq for NULL temp recebe o nó a esquerda do nó atual
            struct no *temp = primeiro -> esq;
            free(primeiro);
            return temp;
        } else { // no com dois filhos

	    	/*
			   achar menor valor no lado direito da arvore
	    	   passa como parametro o no ao lado direito no nó atual
	    	   nó temp recebe a estrutura do nó com menor valor
		    */
	        struct no* temp = acharMenor(primeiro -> dir);
	
	        // copia o valor encontrado para primeiro elementos da esquerda e direita são mantidos
	        primeiro -> valor = temp -> valor;
	 
	        /* 
			   Deleta o valor encontrado como menor pois ele foi substituido
	           passando como parametro o elemento a direita pois se sabe que este elemento veio da direita do elemento atual
	           e também o valor
	        */
	        primeiro -> dir = excluir(primeiro -> dir, temp -> valor);	
		}
    }
    
    return primeiro;
}
