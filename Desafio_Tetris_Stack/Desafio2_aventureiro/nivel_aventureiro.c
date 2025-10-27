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

typedef struct{
    peca itens[MAX]; // Contém um vetor de Pessoa 
    int topo; // Topo, que representa o índice do último elemento inserido

} Pilha;

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

void inicializarPilha(Pilha *p){
    p->topo = -1;

}

int pilhaVazia(Pilha *p){
    return p->topo == -1;
}

int pilhaCheia(Pilha *p){
    return p->topo == MAX -1;
}


// Inserir 
void push(Pilha *p, peca nova){
    if(pilhaCheia(p)){
        printf("Pilha cheia. Nao e possivel inserir elementos");
        return;
    }
    p->topo++; // Incrementa o topo 
    p->itens[p->topo] = nova; // Insere o novo elemento naquela posição.
}

// Remover
void pop(Pilha *p, peca *removida){
    if(pilhaVazia(p)){
        printf("Pilha vazia. Nao e possivel remover\n");
        return;
    }
     *removida = p->itens[p->topo]; // Copia o conteúdo do topo para o ponteiro removido
     p->topo--; // Reduz o topo.
}

// Mostrar pilha
void mostrarPilha(Pilha *p) {

    printf("Pilha (topo -> base):\n");
    if (p->topo < 0) {
        printf("[vazia]\n");
        return;
}
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c, %d]\n", p->itens[i].tipo, p->itens[i].id);
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
  fila f;
  Pilha pilha;
  inicializarFila(&f);
  inicializarPilha(&pilha); // Inicializa a fila
  srand(time(NULL)); // Semente para números aleatórios

  int opcao;
  peca n, removida; // Peça temporária
  int contador = 0; // Contador para IDs das peças

  printf("\n=== JOGO TETRIS STACK ===\n");
  printf(" \n--- Pecas inicias ---\n");
  for(int i = 0; i < 5; i++){
    gerarPeca(&n, contador++);
    inserir(&f, n);
  }

  exibirFila(&f);

  do
  {   printf("\n===========================================\n");
      printf("         MENU DE OPCOES     \n");
      printf("==============================================\n");
      printf("1 - Jogar peca (remover no inicio)\n");
      printf("2 - Reservar peca\n");
      printf("3 - Usar peca reservada\n");
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

              remover(&f, &removida); // Remove a peça do início da fila
              printf("Peca [%c, %d] saiu do jogo!\n", removida.tipo, removida.id);

              // Gerar peças novas
              gerarPeca(&n, contador++);
              // insere na fila
              inserir(&f, n);
              printf("Nova peca [%c, %d] entrou no fim da fila.\n", n.tipo, n.id);


              printf("\nEstado atual: \n");

              exibirFila(&f); // Exibe o estado atual da fila

              printf("\nPressione ENTER para continuar...");
              getchar() , getchar(); 
                break;
                
          case 2:
          // Verifica se a pilha está cheia
          if(pilhaCheia(&pilha)){
              printf("Pilha cheia! Nao e possivel inserir nova peca.\n");
              break;
          }
                 // gera uma peca para reserva
                gerarPeca(&n, contador++);
                 
                // Insere na pilha
                push(&pilha, n);
                printf("Reservou: [%c, %d]\n", n.tipo, n.id);

                // Mostra o estado atual
                mostrarPilha(&pilha);
                printf("\nPressione ENTER para continuar...");
                getchar() , getchar(); 
                break;
              
          case 3:

          // Verifica se a pilha está vazia
           if (pilhaVazia(&pilha)) {
           printf("Pilha vazia! Nenhuma peca reservada.\n");
           break;
           }
               // remove o elemento usado
               pop(&pilha, &removida);
               printf("Usou [%c,%d]\n",removida.tipo,removida.id);
               mostrarPilha(&pilha);

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


