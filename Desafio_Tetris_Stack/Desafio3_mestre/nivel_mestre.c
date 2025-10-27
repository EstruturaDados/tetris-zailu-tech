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
#define pilha_MAX 3

// Definição da estrutura da fila
typedef struct{
    peca itens[MAX];
    int inicio;
    int fim;
    int total;
} fila;

typedef struct{
    peca itens[pilha_MAX]; // Contém um vetor do tipo peca
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
    return p->topo == pilha_MAX -1;
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
  fila f, Invertida;
  Pilha pilha, auxiliar;
  inicializarFila(&f);
  inicializarFila(&Invertida);
  inicializarPilha(&auxiliar);
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
      printf("2 - Enviar peça da fila para a pilha de reserva\n");
      printf("3 - Usar peca da pilha de reserva\n");
      printf("4.  Trocar peça da frente da fila com o topo da pilha\n");
      printf("5.  Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
      printf("0 - Sair\n");
      printf("------------------------------------------------------------\n");
      
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
          if(filaVazia(&f)){ // Verifica se a fila está vazia
            printf("Fila vazia! Nao e possivel jogar mais pecas.\n");
            break;
              }

            if(pilhaCheia(&pilha)){ // Verifica se a pilha está cheia
            printf("Fila Cheia! Nao e possivel enviar mais pecas.\n");
            break;
             }

            // Remove da fila e envia para a pilha reserva
            remover(&f, &removida);
            printf("Peca [%c, %d] removida da fila e enviada para a pilha de reserva.\n",
            removida.tipo, removida.id);

             // Insere na pilha 
            push(&pilha, removida);


            // Gera uma nova peça para o final da fila
            gerarPeca(&n, contador++);
            inserir(&f, n);
            printf("Nova peca [%c, %d] adicionada ao fim da fila.\n", n.tipo, n.id);

            printf("\nFila atual:\n");
            exibirFila(&f);

            printf("\nPilha de reserva:\n");
            mostrarPilha(&pilha);
                
            printf("\nPressione ENTER para continuar...");
            getchar(), getchar();
            break;
                    
             case 3:
             if(pilhaVazia(&pilha)){
              printf("Pilha vazia! Nao e possivel inserir nova peca.\n");
              break;
              }

            // Remove a peca do topo da pilha
            pop(&pilha, &removida);
            printf("Usou [%c,%d]\n",removida.tipo,removida.id);
            mostrarPilha(&pilha);

             // Mostrar estados atualizados
            printf("\nFila atual:\n");
            exibirFila(&f);

            printf("\nPilha de reserva:\n");
            mostrarPilha(&pilha);
            break;

            case 4:
             if(filaVazia(&f)){
               printf("Fila vazia! Nao e possivel trocar.\n");
             break;
            }
            if(pilhaVazia(&pilha)){
            printf("Pilha vazia! Nao e possivel trocar.\n");
            break;
              }


            peca temp =  f.itens[f.inicio]; // O primeiro índice da fila
            f.itens[f.inicio] = pilha.itens[pilha.topo]; // O primeiro índice da fila recebe o último índice da pilha
            pilha.itens[pilha.topo] = temp; // O último índice da pilha recebe o primeiro índice da fila

            printf("Troca realizada entre frente da fila e topo da pilha.\n");

            // Mostrar estados atualizados
            printf("\nFila atual:\n");
            exibirFila(&f);

            printf("\nPilha de reserva:\n");
            mostrarPilha(&pilha);

            printf("\nPressione ENTER para continuar...");
            getchar(), getchar();
            break;

            case 5:
            // Verifica se há 3 pecas na fila e 3 na pilha
            if(f.inicio < 3 || pilha.topo < 2){
            printf("Nao ha pecas suficientes para realizar a troca.\n");
            break;
            }
            printf("\n--- Troca dos 3 primeiros da fila com as 3 pecas da pilha ---\n");
            for(int i = 0; i < 3; i++){
            int idxFila = (f.inicio + i) % MAX; // circular
            int idxPilha = pilha.topo - i; // topo, topo-1, topo-2
            

            // Troca
            peca temp = f.itens[idxFila];
            f.itens[idxFila] = pilha.itens[idxPilha];
            pilha.itens[idxPilha] =temp;
            }

            printf("Troca realizada com sucesso!\n");

            // Mostrar estados atualizados
            printf("\nFila atual:\n");
            exibirFila(&f);

            printf("\nPilha de reserva:\n");
            mostrarPilha(&pilha);

            printf("\nPressione ENTER para continuar...");
            getchar(), getchar();
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




