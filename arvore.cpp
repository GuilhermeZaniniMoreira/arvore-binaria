#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct no
{
	int valor;
	no *esq;
	no *dir;
	no *cima;
};

no *primeiro = NULL;

// prot�tipos das fun��es
void inserir(int valor);
void mostrarElemento();

int main();
int altura(struct no *no);
int desbalanceamento(struct no *no);

struct no *acharMenor(struct no *no);
struct no *excluir(struct no *primeiro, int valor);

void preOrdem(struct no *no);
void posOrdem(struct no *no);
void emOrdem(struct no *no);

int opcao = 0;
int valor = 0;
int profundidade = 0;
int profundidadeGlobal = 0;

int main()
{

	setlocale(LC_ALL, "Portuguese");

	for (;;)
	{

		printf("\n 1 - Inserir");
		printf("\n 2 - Excluir");
		printf("\n 3 - Mostrar elemento");
		printf("\n 4 - Profundidade da �rvore");
		printf("\n 5 - Percurso");
		printf("\n 6 - Desbalanceamento");
		printf("\n 7 - Sair");
		printf("\n Digite:  ");
		scanf("%d", &opcao);

		if (opcao == 1)
		{

			printf("\n Digite o valor: ");
			scanf("%d", &valor);

			inserir(valor);

			printf("\n %d foi inserido!\n", valor);

			system("pause");

			system("cls");
		}
		else if (opcao == 2)
		{

			printf("\n Digite o valor que deseja excluir:  ");
			scanf("%d", &valor);

			excluir(primeiro, valor);

			printf("\n%d foi excluido!", valor);

			system("cls");
		}
		else if (opcao == 3)
		{
			mostrarElemento();
		}
		else if (opcao == 4)
		{

			system("cls");
			printf("\n A profunidade �: %i\n", profundidadeGlobal);
			system("pause");
		}
		else if (opcao == 5)
		{

			printf("\n 1 - Em Ordem");
			printf("\n 2 - Pr� Ordem");
			printf("\n 3 - P�s Ordem");
			printf("\n Digite: ");
			scanf("%d", &opcao);

			if (opcao == 1)
			{
				printf("\n");
				emOrdem(primeiro);
				printf("\n");
				system("pause");
				system("cls");
			}
			else if (opcao == 2)
			{
				printf("\n");
				preOrdem(primeiro);
				printf("\n");
				system("pause");
				system("cls");
			}
			else if (opcao == 3)
			{
				printf("\n");
				posOrdem(primeiro);
				printf("\n");
				system("pause");
				system("cls");
			}
			else
			{
				printf("\n Op��o inv�lida!");
			}
		}
		else if (opcao == 6)
		{
			int valor = desbalanceamento(primeiro);
			printf("\n %i \n", valor);
		}
		else if (opcao == 7)
		{
			system("pause");
			exit(0);
		}
		else
		{
			printf("\n Op��o inv�lida!");
		}
	}
}

void inserir(int valor)
{

	int profundidadeLocal = 0;

	no *temp;
	struct no *p = (struct no *)malloc(sizeof(struct no));
	p->valor = valor;
	p->esq = NULL;
	p->dir = NULL;

	if (primeiro == NULL)
	{
		p->cima = NULL;
		primeiro = p;
	}
	else
	{

		temp = primeiro;

		while (1)
		{

			// se parametro for menor que valor do primeiro
			if (valor < temp->valor)
			{

				profundidadeLocal++;
				/*
					ira settar a esquerda pois � menor
					se esq do primeiro for igual a NULL ent�o ir� settar nesta possi��o e retornar ao menu (break)
				*/
				if (temp->esq == NULL)
				{
					p->cima = temp;
					temp->esq = p;
					break;
				}
				else
				{
					/*
	 					se esq for diferente de NULL ent�o tempor�rio n�o ter� mais o valor de priemeiro
						e ter� o valor da esquerda, assim, com o while ser� executando novamente com outro valor o temp
					*/

					temp = temp->esq;
				}

				// se parametro for maior que o valor do primeiro
			}
			else
			{

				profundidadeLocal++;

				if (temp->dir == NULL)
				{
					p->cima = temp;
					temp->dir = p;
					break;
				}
				else
				{
					temp = temp->dir;
				}
			}
		}
	}

	if (profundidadeLocal > profundidadeGlobal)
	{
		profundidadeGlobal = profundidadeLocal;
	}
}

void mostrarElemento()
{

	if (primeiro == NULL)
	{
		printf("\n N�o h� elementos!");
	}
	else
	{

		no *temp = primeiro;

		while (1)
		{

			system("cls");

			printf("\n\n Elemento atual: %d\n\n", temp->valor);

			printf("\n 1 - Cima");
			printf("\n 2 - Esquerda");
			printf("\n 3 - Direita");
			printf("\n 4 - Retornar ao menu");
			printf("\n Digite: ");
			scanf("%d", &opcao);

			if (opcao == 1)
			{

				if (temp->cima == NULL)
				{
					printf("\n N�o h� elementos\n");
					system("pause");
					mostrarElemento();
				}
				else
				{
					temp = temp->cima;
				}
			}
			else if (opcao == 2)
			{

				if (temp->esq == NULL)
				{
					printf("\n N�o h� elementos\n");
					system("pause");
					mostrarElemento();
				}
				else
				{
					temp = temp->esq;
				}
			}
			else if (opcao == 3)
			{

				if (temp->dir == NULL)
				{
					printf("\n N�o h� elementos\n");
					system("pause");
					mostrarElemento();
				}
				else
				{
					temp = temp->dir;
				}
			}
			else if (opcao == 4)
			{

				system("cls");
				main();
			}
			else
			{
				printf("\n Op��o inv�lida!");
			}
		}
	}
}

int desbalanceamento(struct no *no)
{
	if (no == NULL)
	{
		return 0;
	}
	else
	{
		return (altura(no->dir) - altura(no->esq));
	}
}

int altura(struct no *no)
{

	if (no == NULL)
	{
		return 0;
	}
	else
	{

		int alturaEsq = altura(no->esq);
		int alturaDir = altura(no->dir);

		if (alturaEsq > alturaDir)
		{
			return 1 + alturaEsq;
		}
		else
		{
			return 1 + alturaDir;
		}
	}
}

void preOrdem(struct no *no)
{

	if (no == NULL)
	{
		return;
	}

	printf(" %i - ", no->valor);

	preOrdem(no->esq);
	preOrdem(no->dir);
}

void posOrdem(struct no *no)
{

	if (no == NULL)
	{
		return;
	}

	posOrdem(no->esq);

	posOrdem(no->dir);

	printf(" %i - ", no->valor);
}

void emOrdem(struct no *no)
{

	if (no == NULL)
	{
		return;
	}

	emOrdem(no->esq);
	printf(" %i - ", no->valor);
	emOrdem(no->dir);
}

struct no *acharMenor(struct no *no)
{
	struct no *atual = no;

	/* achar menor valor */
	while (atual->esq != NULL)
	{
		atual = atual->esq;
	}

	return atual;
}

struct no *excluir(struct no *primeiro, int valor)
{
	// se primeiro for igual a NULL
	if (primeiro == NULL)
	{
		printf("\n N�o existem elementos!\n");
		system("pause");
		main();
	}

	/*
		Se valor que deseja deletar � menor que o valor do primeiro
		ent�o valor est� no lado esquerdo da arvore
		por recursividade ir� percorrer a �rvore at� encontrar
		quando encontrar ir� executar o else
	*/
	if (valor < primeiro->valor)
	{
		primeiro->esq = excluir(primeiro->esq, valor);
		main();
		/*
			Se valor que deseja deletar � maior que o valor do primeiro
			ent�o valor est� no lado direito da arvore
			por recursividade ir� percorrer a �rvore at� encontrar
			quando encontrar ir� executar o else
		*/
	}
	else if (valor > primeiro->valor)
	{
		primeiro->dir = excluir(primeiro->dir, valor);
		main();

		// Se valor que deseja deletar � igual ao valor do primeiro
	}
	else
	{
		// se primeiro tem apenas um filho ou n�o tem nenhum
		if (primeiro->esq == NULL)
		{ // se esq for NULL temp recebe o n� a direita do n� atual
			struct no *temp = primeiro->dir;
			free(primeiro);
			return temp;
		}
		else if (primeiro->dir == NULL)
		{ // se esq for NULL temp recebe o n� a esquerda do n� atual
			struct no *temp = primeiro->esq;
			free(primeiro);
			return temp;
		}
		else
		{ // no com dois filhos

			/*
			  achar menor valor no lado direito da arvore
				passa como parametro o no ao lado direito no n� atual
				n� temp recebe a estrutura do n� com menor valor
			*/
			struct no *temp = acharMenor(primeiro->dir);

			// copia o valor encontrado para primeiro elementos da esquerda e direita s�o mantidos
			primeiro->valor = temp->valor;

			/*
		    Deleta o valor encontrado como menor pois ele foi substituido
				passando como parametro o elemento a direita pois se sabe que este elemento veio da direita do elemento atual
				e tamb�m o valor
			*/
			primeiro->dir = excluir(primeiro->dir, temp->valor);
		}
	}

	return primeiro;
}
