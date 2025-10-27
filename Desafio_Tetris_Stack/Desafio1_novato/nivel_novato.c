#include <stdio.h> // Para funções de entrada e saída
#include <stdlib.h> // Para funções de alocação de memória e geração de números aleatórios
#include <time.h> // Para função time

// Definição da estrutura da peça
typedef struct{
    char tipo;
    int id;
} peca ;

// Definição do tamanho máximo da fila
#define MAX 5

// Definição da estrutura da fila
typedef struct{
    peca itens[MAX];
    int inicio;
    int fim;
    int total;
} fila;

// Inicializar a fila
void inicializarFila(fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(fila *f){
    return f->total == MAX;
}

int filaVazia(fila *f){
    return f->total == 0;
}

// Inserir elemento na fila

void inserir(fila *f, peca p){
    if(filaCheia(f)){
        printf("Fila cheia! Nao e possivel inserir [%c, %d]\n", p.tipo, p.id);
        return;
    }
    
    // Insere o item no fim da fila
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;

}

// Remover elemento da fila
void remover(fila *f, peca *p){
    if(filaVazia(f)){
        printf("Fila vazia! Nao e possivel remover. \n");
        return;
    }
    // Remove o item do início da fila
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void exibirFila(fila *f){
    // Percorre a fila do início ao fim considerando a circularidade
    for(int i = 0, idx = f->inicio; i < f->total; i++,
        idx = (idx + 1) % MAX)
        {
            // Fila de peças
            printf("[%c, %d] ", f->itens[idx].tipo,
            f->itens[idx].id);
           
        }
        printf("\n");
}
// Função para gerar uma peça aleatória
void gerarPeca(peca *p, int id){
    char tipos[] = {'I', 'O', 'T', 'L'};
    p->tipo = tipos[rand() % 4];
    p->id = id;
}

int main(){  
  fila f; // Declara a fila
  inicializarFila(&f); // Inicializa a fila
  srand(time(NULL)); // Semente para números aleatórios

  int opcao;
  peca p, removida; // Peça temporária
  int contador = 0; // Contador para IDs das peças

  printf("\n=== JOGO TETRIS STACK ===\n");
  printf(" \n--- Pecas inicias ---\n");
  for(int i = 0; i < 5; i++){
    gerarPeca(&p, contador++);
    inserir(&f, p);
  }

  exibirFila(&f);

  do
  {   printf("\n===========================================\n");
      printf("         MENU DE OPCOES     \n");
      printf("==============================================\n");
      printf("1 - Jogar peca (remover no inicio)\n");
      printf("2 - Inserir nova Peca (adicionar peca no final)\n");
      printf("3 - Exibir Pecas\n");
      printf("0 - Sair\n");
      printf("---------------------------\n");
      
      printf("Escolha uma opcao: ");
      scanf("%d", &opcao);

      switch(opcao){
        // Remover peça
          case 1:
              if(filaVazia(&f)){ // Verifica se a fila está vazia
                    printf("Fila vazia! Nao e possivel jogar mais pecas.\n");
                    break;
              }
               
              printf("\n--- Remover peca ---\n");

              remover(&f, &p); // Remove a peça do início da fila
              printf("\nPeca removida: [%c, %d]\n", p.tipo, p.id); // Exibe a peça removida
              printf("\nEstado atual: \n");

              exibirFila(&f); // Exibe o estado atual da fila

              printf("\nPressione ENTER para continuar...");
              getchar() , getchar(); 
                break;
                
          case 2:
          // Inserir nova peça
          if(filaCheia(&f)){
              printf("Fila cheia! Nao e possivel inserir nova peca.\n");
              break;
          }
                printf("\n---- Inserindo nova peca ---\n");
                gerarPeca(&p, contador++);
                inserir(&f, p); // Insere a nova peça no final da fila
                printf("\nPeca inserida: [%c, %d]\n", p.tipo, p.id); // Exibe a peça inserida
                printf("\nEstado atual: \n");
                exibirFila(&f);

                printf("\nPressione ENTER para continuar...");
                getchar() , getchar(); 
                break;
              
          case 3:
          // Exibir peças
              printf("\n---- Pecas na fila ----\n");
              exibirFila(&f);
              break;
          case 0:
              printf("Saindo...\n");
              break;
          default:
              printf("Opcao invalida! Tente novamente.\n");
      }

  } while(opcao != 0);

  return 0;


}


