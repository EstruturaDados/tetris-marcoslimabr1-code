/*
 * Projeto: Tetris Stack - Controle de Peças (Nível Novato)
 * Desenvolvedor: [Seu Nome / Gemini]
 * Empresa: ByteBros
 * Descrição: Implementação de fila circular para gerenciamento de peças futuras.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Definições e Constantes ---
#define MAX_FILA 5 // Tamanho fixo da fila (Capacidade)

// Definição da estrutura da Peça
typedef struct {
    char nome;  // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;     // Identificador único da peça
} Peca;

// --- Variáveis Globais (Estado da Fila) ---
Peca fila[MAX_FILA];
int inicio = 0;
int fim = 0;
int tamanhoAtual = 0;
int contadorIdGlobal = 0; // Garante que cada peça tenha um ID único crescente

// --- Protótipos das Funções ---
Peca gerarPeca();
void inicializarFila();
void enfileirar(); // Enqueue
void desenfileirar(); // Dequeue (Jogar peça)
void exibirFila();
void limparBuffer();

// --- Função Principal ---
int main() {
    // Inicializa a semente para geração de números aleatórios
    srand(time(NULL));

    int opcao;

    // 1. Inicializar a fila com peças automáticas
    inicializarFila();

    // Loop principal do jogo
    do {
        // Limpa a tela (opcional, funciona em Windows/Linux com adaptações, aqui faremos simples)
        printf("\n========================================\n");
        printf("       BYTEBROS - TETRIS STACK          \n");
        printf("========================================\n");
        
        // 2. Exibir o estado atual
        exibirFila();

        printf("\nOpcoes de acao:\n");
        printf("1 - Jogar peca (Dequeue / Remover frente)\n");
        printf("2 - Inserir nova peca (Enqueue / Adicionar ao final)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                desenfileirar();
                break;
            case 2:
                enfileirar();
                break;
            case 0:
                printf("Encerrando simulacao...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

// Gera uma peça com tipo aleatório e ID sequencial
Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    
    // Escolhe um índice aleatório entre 0 e 3
    novaPeca.nome = tipos[rand() % 4];
    novaPeca.id = contadorIdGlobal;
    
    contadorIdGlobal++; // Incrementa para a próxima peça ser única
    return novaPeca;
}

// Preenche a fila inicialmente até a capacidade máxima
void inicializarFila() {
    printf("Inicializando sistema... Gerando pecas iniciais.\n");
    while (tamanhoAtual < MAX_FILA) {
        Peca p = gerarPeca();
        fila[fim] = p;
        fim = (fim + 1) % MAX_FILA; // Lógica circular
        tamanhoAtual++;
    }
}

// Adiciona uma nova peça ao final da fila (Enqueue)
void enfileirar() {
    if (tamanhoAtual == MAX_FILA) {
        printf("\n[AVISO] A fila esta cheia! Jogue uma peca antes de inserir outra.\n");
        return;
    }

    Peca nova = gerarPeca();
    fila[fim] = nova;
    
    // Atualiza o índice 'fim' circularmente
    fim = (fim + 1) % MAX_FILA; 
    tamanhoAtual++;
    
    printf("\n>> Peca [%c %d] inserida com sucesso.\n", nova.nome, nova.id);
}

// Remove a peça da frente da fila (Dequeue / Jogar)
void desenfileirar() {
    if (tamanhoAtual == 0) {
        printf("\n[ERRO] A fila esta vazia! Use a opcao 2 para gerar pecas.\n");
        return;
    }

    Peca removida = fila[inicio];
    
    // Remove a peça da frente
    inicio = (inicio + 1) % MAX_FILA;
    tamanhoAtual--;

    printf("\n>> Voce jogou a peca: [%c %d]\n", removida.nome, removida.id);

    // --- TRUQUE DO TETRIS REAL ---
    // Adiciona uma nova peça automaticamente logo após jogar
    // Assim a fila nunca fica vazia e sempre tem 5 próximas peças!
    printf("   (Automatico: Gerando nova peca para o final da fila...)\n");
    enfileirar(); 
}
void exibirFila() {
    printf("Fila de pecas Futuras: ");
    if (tamanhoAtual == 0) {
        printf("[ Vazia ]");
    } else {
        int i = inicio;
        for (int count = 0; count < tamanhoAtual; count++) {
            printf("[%c %d] ", fila[i].nome, fila[i].id);
            i = (i + 1) % MAX_FILA; // Avança circularmente apenas para visualização
        }
    }
    printf("\n");
    // Mostra info técnica para depuração (opcional)
    printf("(Debug: Inicio=%d, Fim=%d, Total=%d)\n", inicio, fim, tamanhoAtual);
}