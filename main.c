#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "operacoes.h"


int main(int argc, char** argv){

    setlocale(LC_ALL, "Portuguese"); //Fun��o para caracteres especiais.

    int pista1=0, pista2=0, pista3=0, ID1=0, ID2=0;     //Vari�veis de controle.
    int UT=0, qtdav1, qtdav2, gastemp, x;       //Vari�veis tempor�rias.
    int *pID1 = &ID1,*pID2 = &ID2,*pP1 = &pista1, *pP2 = &pista2, *pP3 = &pista3;   //Ponteiros para as vari�veis que ser�o utilizadas nas opera��es

    estat *Estatisticas = malloc(sizeof(estat));

    Estatisticas->Decolagens = 0;
    Estatisticas->Aterrissagens = 0;   //Iniciando as var�veis respons�veis pelas estatisticas PARCIAIS.
    Estatisticas->Quedas = 0;
    Estatisticas->Emerg = 0;
    Estatisticas->ACiclos = 0;
    Estatisticas->DCiclos = 0;

    Estatisticas->AvDecolT = 0;
    Estatisticas->AvAterT = 0;   //Iniciando as var�veis respons�veis pelas estatisticas TOTAIS.
    Estatisticas->caiuAvT = 0;
    Estatisticas->EmergT = 0;
    Estatisticas->ACiclosT = 0;
    Estatisticas->DCiclosT = 0;

    srand(time(NULL));  //Fun��o para a gera��o aleatoria de numeros.

    //Filas de decolagem//
    Fila *filaD1 = malloc(sizeof(Celula));
    Fila *filaD2 = malloc(sizeof(Celula));
    Fila *filaD3 = malloc(sizeof(Celula));
    //Filas de aterrissagem//
    Fila *filaA1 = malloc(sizeof(Celula));      //Cria��o das filas que ser�o utilizadas.
    Fila *filaA2 = malloc(sizeof(Celula));
    Fila *filaA3 = malloc(sizeof(Celula));
    Fila *filaA4 = malloc(sizeof(Celula));

    FFVazia(filaD1);FFVazia(filaD2);FFVazia(filaD3);
    FFVazia(filaA1);FFVazia(filaA2);FFVazia(filaA3);FFVazia(filaA4);    //Chamando a fun��o vazia para definir os apontadores de todas as filas.

    printf("            SIMULADOR DE AEROPORTO\n\n");

    printf(" Digite a quantidade de ciclos para a simula��o: ");
    scanf("%d", &x);


    do{

        RemoveGas(filaA1, filaA2, filaA3, filaA4, UT);      //Fun��o que retira 1 do contador de gasolina dos avi�es nas filas

        qtdav1 = 1+rand()%3;    //Gera��o aleat�ria de avi�es para a aterrissagem
        qtdav2 = rand()%3;      //Gera��o aleat�ria de avi�es para a decolagem

        //Filas de Aterrissagem//
        if(UT%2 == 0){  //Se o n�mero correspondente ao ciclo for par, o preenchimento das filas de aterrissagem ser� feito de acordo com a quantidade de avi�es gerados:
            if(qtdav1 == 3){
                gastemp = 1+rand()%20;  //Gera��o aleat�ria de gasolina para cada avi�o
                Enfileira(filaA1, pID1, gastemp);
                gastemp = 1+rand()%20;
                Enfileira(filaA2, pID1, gastemp);
                gastemp = 1+rand()%20;
                Enfileira(filaA4, pID1, gastemp);
            }                           //Nesta parte do preenchimento das filas foi feito um balanceamento para que n�o houvesse tanta diferen�a entre elas.
            if(qtdav1 == 2){
                gastemp = 1+rand()%20;
                Enfileira(filaA1, pID1, gastemp);
                gastemp = 1+rand()%20;
                Enfileira(filaA2, pID1, gastemp);
            }
            if(qtdav1 == 1){
                gastemp = 1+rand()%20;
                Enfileira(filaA1, pID1, gastemp);
            }

        }else{  //Se o n�mero correspondente ao ciclo for �mpar, o preenchimento das filas ser� feito de acordo com a quantidade de avo�es gerados:
            if(qtdav1 == 3){
                gastemp = 1+rand()%20;  //Gera��o aleat�ria de gasolina para cada avi�o.
                Enfileira(filaA3, pID1, gastemp);
                gastemp = 1+rand()%20;
                Enfileira(filaA4, pID1, gastemp);
                gastemp = 1+rand()%20;
                Enfileira(filaA1, pID1, gastemp);
            }
            if(qtdav1 == 2){
                gastemp = 1+rand()%20;
                Enfileira(filaA3, pID1, gastemp);
                gastemp = 1+rand()%20;
                Enfileira(filaA4, pID1, gastemp);
            }
            if(qtdav1 == 1){
                gastemp = 1+rand()%20;
                Enfileira(filaA3, pID1, gastemp);
            }
        }

        //Filas de Decolagem//
        gastemp = 20;   //Por padr�o todos avi�es iniciam com o tanque cheio.

        if(qtdav2 == 3){
            Enfileira(filaD1, pID2, gastemp);
            Enfileira(filaD2, pID2, gastemp);
            Enfileira(filaD3, pID2, gastemp);
        }
        if(qtdav2 == 2){
            if(UT%2==0){
            Enfileira(filaD1, pID2, gastemp);
            Enfileira(filaD2, pID2, gastemp);       //Nesta parte do preenchimento das filas de decolagem tamb�m foi feito um balanceamento de acordo com a
                                                    //quantidade de avi�es gerados simultaneamente com a condi��o �mpar ou par dos ciclos.
            }else{
            Enfileira(filaD1, pID2, gastemp);
            Enfileira(filaD3, pID2, gastemp);
            }
        }
        if(qtdav2 == 1){
            if(UT%2==0){
            Enfileira(filaD1, pID2, gastemp);
            }else{
            Enfileira(filaD2, pID2, gastemp);
            }
        }

        ContCiclos(filaA1, filaA2, filaA3, filaA4, filaD1, filaD2, filaD3); //Fun��o para aumentar em 1 os contadores de ciclo dos avi�es.

        UT++;   //Aumenta 1 na unidade de tempo.
        printf("\n===================================================");
        printf("\n==================== Ciclo %d ====================\n\n", UT);
        printf(" Fila Aterrissagem 1\n");
        Imprime(filaA1);
        printf("\n");
        printf("\n Fila Aterrissagem 2\n");
        Imprime(filaA2);
        printf("\n");
        printf("\n Fila Aterrissagem 3\n");
        Imprime(filaA3);
        printf("\n");
        printf("\n Fila Aterrissagem 4\n");
        Imprime(filaA4);
        printf("\n==================================================\n\n");     //Mostragem das filas ap�s o preenchimento.
        printf(" Fila Decolagem 1\n");
        Imprime(filaD1);
        printf("\n");
        printf("\n Fila Decolagem 2\n");
        Imprime(filaD2);
        printf("\n");
        printf("\n Fila Decolagem 3\n");
        Imprime(filaD3);
        printf("\n==================================================\n");

        printf(" 0 - Desocupada / 1 - Ocupada\n\n");

        Aterrissagem(filaA1, filaA2, filaA3, filaA4, pP1, pP2, pP3, Estatisticas);  //Fun��o para a aterrissagem dos avi�es, leva como par�metro as filas, pistas e a vari�vel de estat�sticas.
        printf(" Pistas p�s Aterrissagem\n");
        printf(" P1 -> %d\n", pista1);
        printf(" P2 -> %d\n", pista2);      //Mostragem situa��o das pistas p�s aterrissagem.
        printf(" P3 -> %d\n\n", pista3);
        Decolagem(filaD1, filaD2, filaD3, pP1, pP2, pP3, Estatisticas); //Fun��o para a decolagem dos av�es, leva como par�metro as filas, pistas e a vari�vel de estat�sticas.
        printf(" Pistas p�s Decolagem\n");
        printf(" P1 -> %d\n", pista1);
        printf(" P2 -> %d\n", pista2);      //Mostragem situa��o das pistas p�s decolagem.
        printf(" P3 -> %d\n", pista3);


        printf("\n==================================================\n");
        printf("\n      ESTAT�STICAS DO CICLO\n");
        printf("\n Aterrissagens                %.0f", Estatisticas->Aterrissagens);    //Mostragem das estat�sticas parciais,
        printf("\n Decolagens                   %.0f", Estatisticas->Decolagens);
        printf("\n Aterrissagens de emerg�ncia  %d", Estatisticas->Emerg);
        printf("\n Quedas                       %d", Estatisticas->Quedas);
        printf("\n Tempo M�dio Aterrissagens    %.2f ciclos", Estatisticas->ACiclos/Estatisticas->Aterrissagens);
        printf("\n Tempo M�dio Decolagens       %.2f ciclos\n", Estatisticas->DCiclos/Estatisticas->Decolagens);

        pista1=0;
        pista2=0;       //Desocupando as pistas.
        pista3=0;

        Estatisticas->Decolagens = 0;
        Estatisticas->Aterrissagens = 0;    //Zerando os contadores parciais.
        Estatisticas->Quedas = 0;
        Estatisticas->Emerg = 0;
        Estatisticas->ACiclos = 0;
        Estatisticas->DCiclos = 0;


    }while(UT != x);    //While roda enquanto n�o for igual ao numero de ciclos desejado.

    printf("\n==================================================\n");
    printf("\n      ESTAT�STICAS TOTAIS\n");
    printf("\n Aterrissagens                %.0f", Estatisticas->AvAterT);    //Mostragem das estat�sticas totais,
    printf("\n Decolagens                   %.0f", Estatisticas->AvDecolT);
    printf("\n Aterrissagens de emerg�ncia  %d", Estatisticas->EmergT);
    printf("\n Quedas                       %d", Estatisticas->caiuAvT);
    printf("\n Tempo M�dio Aterrissagens    %.2f ciclos", Estatisticas->ACiclosT/Estatisticas->AvAterT);
    printf("\n Tempo M�dio Decolagens       %.2f ciclos\n", Estatisticas->DCiclosT/Estatisticas->AvDecolT);


    return (EXIT_SUCCESS);
}






