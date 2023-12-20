#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Celula *Apontador;
typedef struct Avioes{
    int ID;     //Struct com os dados dos aviões.
    int gas;
    int Ciclos;
}Avioes;

typedef struct Celula{
    Avioes aviao;
    Apontador prox;     //Struct da célula com a variável do avião e o apontador para a próxima celula.
}Celula;

typedef struct Fila{
    Apontador frente, tras;     //Struct da fila com os apontadores para o ínicio e fim da fila e a variável para o tamanho.
    int tam;
}Fila;

typedef struct estat{
    float AvDecolT, Aterrissagens;
    float AvAterT, Decolagens;
    int caiuAvT, Quedas;                //Struct com as estatísticas totais e parciais do simulador.
    int Emerg, EmergT;
    float ACiclos, ACiclosT;    //Ciclos aterrisagem total e parcial.
    float DCiclos, DCiclosT;    //Ciclos decolagem total e parcial
}estat;

void FFVazia(Fila *fila);//Inicia a fila.
void Enfileira(Fila *fila, int *ID, int gastemp);//Insere avião na fila.
void Imprime(Fila *fila);//Imprime a fila na tela.
int Vazia(Fila *fila);//Verifica se a fila está vazia.
void DesenfileiraA(Fila *fila, estat *Estatisticas);//Desenfileira avião no processo de aterrissagem.
void DesenfileiraD(Fila *fila, estat *Estatisticas);//Desenfileira avião no processo de decolagem.

void RemoveGas(Fila *filaA1, Fila *filaA2, Fila *filaA3, Fila *filaA4, int UT);
//Remove uma unidade da gasolina por unidade de tempo de todos os aviões presentes nas filas.

void Aterrissagem(Fila *filaA1, Fila *filaA2, Fila *filaA3, Fila *filaA4, int *p1, int *p2, int *p3, estat *Estatisticas);
//Função que realiza a aterrissagem de acordo com as pistas.

void Decolagem(Fila *filaD1, Fila *filaD2, Fila *filaD3, int *p1, int *p2, int *p3, estat *Estatisticas);//Função que realiza a decolagem de acordo com as pistas.
void VerificarEmergencia(Fila *filaA1, Fila *filaA2, Fila *filaA3, Fila *filaA4, int *p1, int *p2, int *p3, estat *Estatisticas);
//Verifica se em alguma das filas é necessário uma aterrissagem de emergência por causa do combustível.

void ContCiclos(Fila *filaA1, Fila *filaA2, Fila *filaA3, Fila *filaA4, Fila *filaD1, Fila *filaD2, Fila *filaD3);
//Funçaõ que soma 1 nos contadores de ciclo de cada avião.

