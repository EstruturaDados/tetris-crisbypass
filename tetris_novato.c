#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// Se estivermos no windows, vamos incluir usar uma saída de console com padrão adequado para utf-8.
#ifdef _WIN32
#include <Windows.h>
#endif

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

// **** Definições de constantes. ****

/// @brief Tamanho reservado para o máximo de elementos na fila.
#define TAM_MAX_FILA 5

// **** Declarações de estruturas. ****

/// @brief Define uma struct chamada Peca(alias), com os campos: tipo (char) e id (int).
typedef struct
{
	/// @brief Caractere que representa o tipo da peça('I', 'O', 'T', 'L').
	char tipo;
	/// @brief Número inteiro único que representa a ordem de criação da peça.
	int id;
} Peca;

/// @brief Define uma struct com um alias Fila, para uma fila circular com capacidade de TAM_MAX_FILA.
typedef struct {
	Peca itens[TAM_MAX_FILA];
	int inicio;
	int fim;
	int total;
} Fila;

// **** Declarações das funções. ****

// **** Interface de usuário. ****

/// @brief Exibe o menu principal.
/// @param Inteiro. Ponteiro via referência, para conter o valor da opção.
void exibirMenuPrincipal(int* opcao);

// **** Funções de Lógica Principal ****

/// @brief Efetua procedimentos para a remoção de peças da fila.
/// @param Fila. Ponteiro via referência, para aplicar a remoção.
void acaoJogarPeca(Fila* fila);
/// @brief Efetua procedimentos para a inserção de peças na fila.
/// @param Fila. Ponteiro via referência, para aplicar a remoção.
/// @param Inteiro. Ponteiro via referência, para atribuição e leitura
/// de valores do contador sequencial único.
void acaoInserirPeca(Fila* fila, int* sequencial);
/// @brief Inicializa a fila. Baseado no conteúdo da plataforma.
/// @param Fila. Ponteiro via referência, para efetuar a inicialização.
void inicializarFila(Fila* fila);
/// @brief Verifica se a fila está cheia. Baseado no conteúdo da plataforma.
/// @param Fila. Ponteiro usado para efetuar a verificação. Somente leitura.
/// @returns Verdadeiro(true) se a fila está cheia. Caso contrário, Falso(false). 
bool filaCheia(const Fila* fila);
/// @brief Verifica se a fila está vazia. Baseado no conteúdo da plataforma.
/// @param Fila. Ponteiro usado para efetuar a verificação. Somente leitura.
/// @returns Verdadeiro(true) se a fila está vazia. Caso contrário, Falso(false).
bool filaVazia(const Fila* fila);
/// @brief Enfileira(ou sobrescreve) o elemento se houver alocações disponíveis na fila. Baseado no conteúdo da plataforma.
/// @param Fila. Ponteiro via referência, usado no enfileiramento.
/// @param Peca. Elemento previamente populado e identificado de forma única, a ser enfileirado.
/// @returns Verdadeiro(true), em caso de sucesso. Caso contrário, Falso(false).
bool enqueue(Fila* f, Peca p);
/// @brief Marca para sobrescrever(desenfileirar) o primeiro elemento de acordo com a ordem atual da fila.
/// Baseado no conteúdo da plataforma.
/// @param Fila. Ponteiro via referência, usado no desenfileiramento.
/// @returns Peca. Ponteiro a conter o elemento desenfileirado.
Peca* dequeue(Fila* fila);
/// @brief Mostra os elementos enfileirados de acordo com a ordem atual da fila. Baseado no conteúdo da plataforma.
/// @param Fila. Ponteiro usado para efetuar a listagem. Somente leitura.
void mostrarFila(const Fila* f);
/// @brief Verifica e enfileira totalmente se necessário com novos elementos a fila em questão.
/// @param Fila. Ponteiro via referência, a ser usado para efetuar o enfileiramento.
/// @param Inteiro. Ponteiro via referência, para atribuição e leitura
/// de valores do contador sequencial único.
void popularFila(Fila* fila, int* sequencial);
/// @brief Cria aleatoriamente um novo elemento do tipo Peca, para uso posterior.
/// @param Inteiro. Ponteiro via referência, para atribuição e leitura
/// de valores do contador sequencial único.
/// @returns Peca. Conforme as especificações.
Peca gerarPeca(int* sequencial);
/// @brief Efetua a tentativa de criar automaticamente um novo elemento do tipo Peca na fila,
/// além de efetuar controle e verificação de identificação única.
/// @param Fila. Ponteiro via referência, usado no desenfileiramento.
/// @param Inteiro. Ponteiro via referência, para atribuição e leitura
/// de valores do contador sequencial único.
/// @returns Verdadeiro(true), em caso de sucesso. Caso contrário, Falso(false).
bool autoGeracao(Fila* fila, int* sequencial);

// **** Funções utilitárias ****

/// @brief Limpa o buffer de entrada do teclado (stdin), evitando problemas 
/// com leituras consecutivas de scanf e getchar.
void limparBufferEntrada();
/// @brief Função para limpar '\n' deixado pelo fgets.
/// @param str Conteúdo do texto a ser analisado e limpo.
void limparEnter(char* str);


/// @brief Ponto de entrada do programa.
/// @returns Inteiro. Zero, em caso de sucesso. Ex: EXIT_SUCCESS. 
/// Ou diferente de Zero, em caso de falha. Ex: EXIT_FAILURE.
int main() {

	// Configurações de caracteres para ajuste de ortografia para saída do console(UTF-8).
#ifdef _WIN32
	// Plataforma Windows.
	SetConsoleOutputCP(CP_UTF8);
#endif

	// Inicializa o gerador de números aleatórios.
	srand((unsigned int)time(NULL));

	printf("======================================================\n");
	printf("======== 🧱  TETRIS STACK - Nível Novato  🧱 ========\n");
	printf("======================================================\n");

	// Poderíamos também usar um contador estático, para os valores únicos. 
	// Mas vamos manter de acordo com escopo do tempo de vida do método main.
	int opcao = 0, sequencial = 0;

	Fila fila;
	inicializarFila(&fila);
	popularFila(&fila, &sequencial);

	do
	{
		// Após cada ação, devemos mostrar o estado atual da fila.
		// Então vamos efetuar a exibição por padrão.
		mostrarFila(&fila);

		exibirMenuPrincipal(&opcao);

		switch (opcao)
		{
		case 1:
			acaoJogarPeca(&fila);
			break;
		case 2:
			acaoInserirPeca(&fila, &sequencial);
			break;
		case 0:
			//  0  Sair.
			printf("\n==== Saindo do sistema... ====\n");
			break;
		default:
			// Continua.
			printf("\n==== ⚠️  Opção inválida. ====\n");
			break;
		}

	} while (opcao != 0);

	printf("\n==== Operação encerrada. ====\n");


	return EXIT_SUCCESS;
}

// **** Implementações das funções. ****

// **** Interface de usuário. ****

void exibirMenuPrincipal(int* opcao)
{
	printf("\n1 - Jogar Peça(dequeue).\n");
	printf("2 - Inserir Nova Peça(enqueue).\n");
	printf("0 - Sair.\n");

	int invalido;

	do
	{
		printf("Escolha uma opção: ");
		invalido = scanf("%d", opcao) != 1; // Sem o operador '&'. Já temos um ponteiro.
		limparBufferEntrada();
		if (invalido)
		{
			printf("\n==== ⚠️  Entrada inválida. Tente novamente. ====\n");
		}
	} while (invalido);
}

// **** Funções de Lógica Principal ****

void acaoJogarPeca(Fila* fila)
{
	Peca* peca = dequeue(fila);

	if (peca != NULL)
	{
		printf("\n  ✅  Peça Id %d removida da fila.\n", peca->id);
		printf("\n  ℹ️  Ação de jogar peça foi efetuada com êxito.\n");
		return;
	}

	printf("\n  ℹ️  Ação de jogar peça foi abortada.\n");
}

void acaoInserirPeca(Fila* fila, int* sequencial)
{
	if (autoGeracao(fila, sequencial))
	{
		printf("\n  ℹ️  Ação de inserção da fila efetuada com êxito.\n");
		return;
	}
	
	printf("\n  ℹ️  A ação de inserção da fila foi abortada.\n");	
}

void inicializarFila(Fila* f)
{
	f->inicio = 0;
	f->fim = 0;
	f->total = 0;
}

bool filaCheia(const Fila* fila)
{
	return fila->total == TAM_MAX_FILA;
}

bool filaVazia(const Fila* fila)
{
	return fila->total == 0;
}

bool enqueue(Fila* fila, Peca peca)
{
	if (filaCheia(fila))
	{
		printf("\n ⚠️  Fila cheia. Não é possível inserir.\n");
		return false;
	}

	fila->itens[fila->fim] = peca;
	fila->fim = (fila->fim + 1) % TAM_MAX_FILA;
	fila->total++;

	return true;
}

Peca* dequeue(Fila* fila)
{
	if (filaVazia(fila))
	{
		printf("\n ⚠️  Fila vazia. Não é possível remover.\n");
		return NULL;
	}

	Peca* peca = &fila->itens[fila->inicio];
	fila->inicio = (fila->inicio + 1) % TAM_MAX_FILA;
	fila->total--;

	return peca;
}

void mostrarFila(const Fila* f)
{
	printf("\n==== Estado Atual da Fila ====\n");
	printf("\n");
	for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % TAM_MAX_FILA)
	{
		printf("[%c, %d] ", f->itens[idx].tipo, f->itens[idx].id);
	}
	printf("\n");
}

void popularFila(Fila* fila, int* sequencial)
{
	// Enquanto temos alocações disponíveis, continuamos enfileirando elementos.
	while (fila->total < TAM_MAX_FILA)
	{
		if (!autoGeracao(fila, sequencial))
		{
			printf(" ⚠️  Falha ao popular a fila. Operação abortada.");
			break;
		}
	}
}

Peca gerarPeca(int* sequencial)
{
	int codPeca = rand() % 4 + 1; // Escolhendo uma "forma" de peça aleatoriamente.

	Peca peca; // Vamos preparar os dados da peça para atribuição.

	(*sequencial)++; // Acrescentando ao valor do ponteiro do contador único.

	peca.id = *sequencial; // Atribuindo o valor atualizado do ponteiro ao identificador da peça a ser gerada.

	// Optar somente entre os tipos de peça: 'I', 'O', 'T' ou 'L'.
	switch (codPeca)
	{
	case 1:
		peca.tipo = 'I';
		break;
	case 2:
		peca.tipo = 'O';
		break;
	case 3:
		peca.tipo = 'T';
		break;
	default:
		peca.tipo = 'L';
		break;
	}

	return peca; // Peça pronta para uso.
}

bool autoGeracao(Fila* fila, int* sequencial)
{
	Peca peca = gerarPeca(sequencial);
	if (enqueue(fila, peca))
	{
		printf("\n  ✅  Nova Peça Id %d inserida na fila.\n", peca.id);
		return true;
	}
	// Vamos devolver o valor sequencial único anterior, se a inserção não for bem sucedida.
	(*sequencial)--;

	return false;
}

// **** Funções utilitárias ****

void limparBufferEntrada()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void limparEnter(char* str)
{
	str[strcspn(str, "\n")] = '\0';
}