#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "operacoes.h"

void Imprime(Fila *fila){

    Apontador aux;  //Auxiliar que ajuda na mostragem das filas.

    if(Vazia(fila)){
        printf(" Fila vazia.\n");
    }else{

        aux = fila->frente->prox;

        while(aux != NULL){ //Printa na tela enquanto a fila estiver preenchida.
            printf(" ID = %d  || Gas = %d  || QtdCiclos = %d\n", aux->aviao.ID, aux->aviao.gas, aux->aviao.Ciclos);
            aux=aux->prox;
        }
    }
}

void Enfileira(Fila *fila, int *ID, int gastemp){

    fila->tras->prox = malloc(sizeof(Celula));
    fila->tras = fila->tras->prox;
    fila->tras->aviao.ID = *ID;
    fila->tras->aviao.gas = gastemp;
    fila->tras->aviao.Ciclos = 0;   //Inicia em 0 contador de ciclos do avião.
    fila->tras->prox = NULL;
    fila->tam++;    //Aumenta o tamanho da fila.
    *ID = *ID + 2;  //Aumenta em 2 o contador de ID dos aviões.

}

void FFVazia(Fila *fila){

    fila->frente = malloc(sizeof(Celula));
    fila->tras = fila->frente;
    fila->frente->prox = NULL;
    fila->tam = 0;  //Inicia em 0 o tamanho da fila.

}

int Vazia(Fila *fila){
    return(fila->frente == fila->tras); //Verifica se a fila está vazia.
}

void DesenfileiraA(Fila *fila, estat *Estatisticas){

    Apontador aux;

    if(Vazia(fila)){
        printf("\n Fila vazia.");
    }else{
        aux = fila->frente;
        Estatisticas->ACiclos += aux->prox->aviao.Ciclos;       //Somatório no contador parcial e total de ciclos dos aviões.
        Estatisticas->ACiclosT += aux->prox->aviao.Ciclos;
        if(aux->prox->aviao.gas <=0){
            Estatisticas->caiuAvT++;
            Estatisticas->Quedas++;     //Aumenta o contador total e parcial de quedas se a gasolina estiver em 0.
            Estatisticas->AvAterT--;    //Diminui o contador total e parcial das aterrissagens para ocorer um anulamento adiante.
            Estatisticas->Aterrissagens--;
        }
        fila->frente = fila->frente->prox;
        fila->tam--;    //Diminui o tamanho da fila.
        Estatisticas->AvAterT++;
        Estatisticas->Aterrissagens++;  //Aumenta o contador total e parcial de aterrissagens.

    }

}

void DesenfileiraD(Fila *fila, estat *Estatisticas){

    Apontador aux;

    if(Vazia(fila)){
        printf("\n Fila vazia.");
    }else{
        aux = fila->frente;
        Estatisticas->DCiclos += aux->prox->aviao.Ciclos;       //Somatório no contador parcial e total de ciclos dos aviões.
        Estatisticas->DCiclosT += aux->prox->aviao.Ciclos;
        fila->frente = fila->frente->prox;
        fila->tam--;    //Diminui o tamanho da fila.
        Estatisticas->AvDecolT++;   //Aumenta o contador total e parcial de decolagens.
        Estatisticas->Decolagens++;
    }
}

void RemoveGas(Fila *filaA1, Fila *filaA2, Fila *filaA3, Fila *filaA4, int UT){

    if(UT > 0){         //Se o ciclo for maior que 0, em todas as filas ocorrerá uma diminuição em 1 do contador de gasolina dos aviões.
        Apontador aux;
        if(!Vazia(filaA1)){
        aux = filaA1->frente->prox;
            while(aux != NULL){
                aux->aviao.gas--;
                aux = aux->prox;
            }
        }

        if(!Vazia(filaA2)){
        aux = filaA2->frente->prox;
            while(aux != NULL){
                aux->aviao.gas--;
                aux = aux->prox;
            }
        }

        if(!Vazia(filaA3)){
        aux = filaA3->frente->prox;
            while(aux != NULL){
                aux->aviao.gas--;
                aux = aux->prox;
            }
        }

        if(!Vazia(filaA4)){
        aux = filaA4->frente->prox;
            while(aux != NULL){
                aux->aviao.gas--;
                aux = aux->prox;
            }
        }
    }

}

void Aterrissagem(Fila *filaA1, Fila *filaA2, Fila *filaA3, Fila *filaA4, int *p1, int *p2, int *p3, estat *Estatisticas){

    if((Vazia(filaA1)) && (Vazia(filaA2)) && (Vazia(filaA3)) && (Vazia(filaA4))){   //Verificação de filas vazias.

    }else{

        VerificarEmergencia(filaA1, filaA2, filaA3, filaA4, p1, p2, p3, Estatisticas);
        //Verifica antes de qualquer aterrissagem a existência de alguma emergência.

        printf(" Pistas pós Verificação de Emergência\n");
        printf(" P1 -> %d\n", *p1);
        printf(" P2 -> %d\n", *p2);     //Mostragem situação das pistas pós verificação de emergência.
        printf(" P3 -> %d\n\n", *p3);

        //Se a pista 1 estiver desocupada(igual a 0), verifica-se qual das filas 1 e 2 tem o maior tamanho e ocorre a retirada de 1 avião.
        if(*p1 == 0){
            if(filaA1->tam >= filaA2->tam){
                if(!Vazia(filaA1)){
                DesenfileiraA(filaA1, Estatisticas);
                *p1 = 1;//Ocupação da pista 1.
                }
            }else{
                if(!Vazia(filaA2)){
                DesenfileiraA(filaA2, Estatisticas);
                *p1 = 1;//Ocupação da pista 1.
                }
            }
        }

        //Se a pista 2 estiver desocupada(igual a 0), verifica-se qual das filas 3 e 4 tem o maior tamanho e ocorre a retirade de 1 avião.
        if(*p2 == 0){
            if(filaA3->tam >= filaA4->tam){
                if(!Vazia(filaA3)){
                DesenfileiraA(filaA3, Estatisticas);
                *p2 = 1;//Ocupação da pista 2.
                }
            }else{
                if(!Vazia(filaA4)){
                DesenfileiraA(filaA4, Estatisticas);
                *p2 = 1;//Ocupação da pista 2.
                }
            }
        }
    }
}

void Decolagem(Fila *filaD1, Fila *filaD2, Fila *filaD3, int *p1, int *p2, int *p3, estat *Estatisticas){

    if((Vazia(filaD1)) && (Vazia(filaD2)) && (Vazia(filaD3))){  //Verificação de filas vazias.

    }else{

        if(*p1 == 0){//Se a pista 1 estiver desocupada ocorre o desenfileiramento da fila 1.
            if(!Vazia(filaD1)){
            DesenfileiraD(filaD1, Estatisticas);
            *p1 = 1;//Ocupação da pista 1.
            }
        }
        if(*p2 == 0){//Se a pista 2 estiver desocupada ocorre o desenfileiramento da fila 2.
            if(!Vazia(filaD2)){
            DesenfileiraD(filaD2, Estatisticas);
            *p2 = 1;//Ocupação da pista 2.
            }
        }
        if(*p3 == 0){//Se a pista 3 estiver desocupada ocorre o desenfileiramento da fila 3.
            if(!Vazia(filaD3)){
            DesenfileiraD(filaD3, Estatisticas);
            *p3 = 1;//Ocupação da pista 3.
            }
        }
        //Se as pistas 1 e 2 estiverem ocupadas, a pista 3 poderá ser usada para desenfileiramentos das filas 1 e 2.
        if(*p1 == 1 && *p2 == 1 && *p3 == 0){
            if(!Vazia(filaD1) && !Vazia(filaD2)){//Se as duas estiverem preenchidas ocorre uma comparação para desenfileirar a maior.
                if(filaD1->tam >= filaD2->tam){
                    DesenfileiraD(filaD1, Estatisticas);
                    *p3 = 1;//Ocupação da pista 3.
                }else{
                    DesenfileiraD(filaD2, Estatisticas);
                    *p3 = 1;//Ocupação da pista 3.
                }
            }else if(!Vazia(filaD1)){//Caso alguma das filas esteja vazia, ocorre o desenfileiramento da que não está.
                DesenfileiraD(filaD1, Estatisticas);
                *p3 = 1;//Ocupação da pista 3.
            }else if(!Vazia(filaD2)){
                DesenfileiraD(filaD2, Estatisticas);
                *p3 = 1;//Ocupação da pista 3.
            }
        }
        //Se as pista 1 estiver ocupada, a pista 2 poderá ser usada para desenfileiramentos da fila 1.
        if(*p1 == 1 && *p2 == 0){
            if(!Vazia(filaD1)){
                    DesenfileiraD(filaD1, Estatisticas);
                    *p2 = 1;//Ocupação da pista 2.
            }
        }
        //Se as pistas 2 estiver ocupada, a pista 1 poderá ser usada para desenfileiramentos da fila 2.
        if(*p1 == 0 && *p2 == 1){
            if(!Vazia(filaD2)){
                    DesenfileiraD(filaD1, Estatisticas);
                    *p1 = 1;//Ocupação da pista 1.
            }
        }

    }

}

void VerificarEmergencia(Fila *filaA1, Fila *filaA2, Fila *filaA3, Fila *filaA4, int *p1, int *p2, int *p3, estat *Estatisticas){

    Apontador aux;

    if(!Vazia(filaA1)){
        aux = filaA1->frente->prox;
        if(aux->aviao.gas == 1){        //Verifica-se o primeiro avião presente na fila está em situação de emergência.
            if(*p3 == 0){               //Caso esteja, o mesmo é retirado da fila prioritariamente.
                DesenfileiraA(filaA1, Estatisticas);
                Estatisticas->Emerg++;      //Aumenta o contador parcial e total de pousos de emergência.
                Estatisticas->EmergT++;
                *p3=1;
            }else if(*p1 == 0){     //Verificação de qual pista pode ser usada para o pouso de emergência.
                DesenfileiraA(filaA1, Estatisticas);
                Estatisticas->Emerg++;      //Aumenta o contador parcial e total de pousos de emergência.
                Estatisticas->EmergT++;
                *p1=1;
            }else if(*p2 == 0){
                DesenfileiraA(filaA1, Estatisticas);
                Estatisticas->Emerg++;      //Aumenta o contador parcial e total de pousos de emergência.
                Estatisticas->EmergT++;
                *p2=1;
            }
        }else{      //Se o primeiro avião da fila não está em emergência ocorre a verificação de emergência da segunda posição.
                    //Caso haja emergência, o primeiro e segundo avião são reirados da fila.
            aux=aux->prox;

            if(aux != NULL && aux->aviao.gas == 1 ){
                if(*p2 == 0 && *p3 == 0){      //Verificação de quais pistas podem ser utilizadas.
                DesenfileiraA(filaA1, Estatisticas);
                DesenfileiraA(filaA1, Estatisticas);
                *p3 = 1;
                *p2 = 1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
                }else if(*p1 == 0 && *p2 == 0){
                    DesenfileiraA(filaA1, Estatisticas);
                    DesenfileiraA(filaA1, Estatisticas);
                    *p1 = 1;
                    *p2 = 1;
                    Estatisticas->Emerg++;
                    Estatisticas->EmergT++;
                    Estatisticas->Emerg++;
                    Estatisticas->EmergT++;

                }
            }
        }
    }

    if(!Vazia(filaA2)){                 //A mesma verificação ocorre para todas as filas de aterrisagem.
        aux = filaA2->frente->prox;
        if(aux->aviao.gas == 1){
            if(*p3 == 0){
                DesenfileiraA(filaA2, Estatisticas);
                *p3=1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
            }else if(*p1 == 0){                     //Verificação de qual pista pode ser usada para o pouso de emergência.
                DesenfileiraA(filaA2, Estatisticas);
                *p1=1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
            }else if(*p2 == 0){
                DesenfileiraA(filaA2, Estatisticas);
                *p2=1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
            }
        }else{
            aux=aux->prox;

            if(aux != NULL && aux->aviao.gas == 1 ){
                if(*p2 == 0 && *p3 == 0){               //Verificação de quais pistas podem ser utilizadas.
                DesenfileiraA(filaA2, Estatisticas);
                DesenfileiraA(filaA2, Estatisticas);
                *p3 = 1;
                *p2 = 1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
                }else if(*p1 == 0 && *p2 == 0){
                    DesenfileiraA(filaA2, Estatisticas);
                    DesenfileiraA(filaA2, Estatisticas);
                    *p1 = 1;
                    *p2 = 1;
                    Estatisticas->Emerg++;
                    Estatisticas->EmergT++;
                    Estatisticas->Emerg++;
                    Estatisticas->EmergT++;

                }
            }
        }
    }

    if(!Vazia(filaA3)){
        aux = filaA3->frente->prox;
        if(aux->aviao.gas == 1){
            if(*p3 == 0){
                DesenfileiraA(filaA3, Estatisticas);
                *p3=1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
            }else if(*p1 == 0){     //Verificação de qual pista pode ser usada para o pouso de emergência.
                DesenfileiraA(filaA3, Estatisticas);
                *p1=1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
            }else if(*p2 == 0){
                DesenfileiraA(filaA3, Estatisticas);
                *p2=1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
            }
        }else{
            aux=aux->prox;

            if(aux != NULL && aux->aviao.gas == 1 ){
                if(*p2 == 0 && *p3 == 0){               //Verificação de quais pistas podem ser utilizadas.
                DesenfileiraA(filaA3, Estatisticas);
                DesenfileiraA(filaA3, Estatisticas);
                *p3 = 1;
                *p2 = 1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
                }else if(*p1 == 0 && *p2 == 0){
                    DesenfileiraA(filaA3, Estatisticas);
                    DesenfileiraA(filaA3, Estatisticas);
                    *p1 = 1;
                    *p2 = 1;
                    Estatisticas->Emerg++;
                    Estatisticas->EmergT++;
                    Estatisticas->Emerg++;
                    Estatisticas->EmergT++;

                }
            }
        }
    }


    if(!Vazia(filaA4)){
        aux = filaA4->frente->prox;
        if(aux->aviao.gas == 1){
            if(*p3 == 0){
                DesenfileiraA(filaA4, Estatisticas);
                *p3=1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
            }else if(*p1 == 0){     //Verificação de qual pista pode ser usada para o pouso de emergência.
                DesenfileiraA(filaA4, Estatisticas);
                *p1=1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
            }else if(*p2 == 0){
                DesenfileiraA(filaA4, Estatisticas);
                *p2=1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
            }
        }else{
            aux=aux->prox;

            if(aux != NULL && aux->aviao.gas == 1 ){
                if(*p2 == 0 && *p3 == 0){               //Verificação de quais pistas podem ser utilizadas.
                DesenfileiraA(filaA4, Estatisticas);
                DesenfileiraA(filaA4, Estatisticas);
                *p3 = 1;
                *p2 = 1;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
                Estatisticas->Emerg++;
                Estatisticas->EmergT++;
                }else if(*p1 == 0 && *p2 == 0){
                    DesenfileiraA(filaA4, Estatisticas);
                    DesenfileiraA(filaA4, Estatisticas);
                    *p1 = 1;
                    *p2 = 1;
                    Estatisticas->Emerg++;
                    Estatisticas->EmergT++;
                    Estatisticas->Emerg++;
                    Estatisticas->EmergT++;

                }
            }
        }
    }
}

void ContCiclos(Fila *filaA1, Fila *filaA2, Fila *filaA3, Fila *filaA4, Fila *filaD1, Fila *filaD2, Fila *filaD3){

    Apontador aux;      //Em todas as filas de aterrissagem e decolagem ocorre um aumento em 1 do contador de ciclos dos aviões.
                        //Primeiramente é verificado a existência de cada fila e após isso toda ela é percorrida para o aumento dos contadores.

        if(!Vazia(filaA1)){
        aux = filaA1->frente->prox;
            while(aux != NULL){
                aux->aviao.Ciclos++;
                aux = aux->prox;
            }
        }

        if(!Vazia(filaA2)){
        aux = filaA2->frente->prox;
            while(aux != NULL){
                aux->aviao.Ciclos++;
                aux = aux->prox;
            }
        }

        if(!Vazia(filaA3)){
        aux = filaA3->frente->prox;
            while(aux != NULL){
                aux->aviao.Ciclos++;
                aux = aux->prox;
            }
        }

        if(!Vazia(filaA4)){
        aux = filaA4->frente->prox;
            while(aux != NULL){
                aux->aviao.Ciclos++;
                aux = aux->prox;
            }
        }

        if(!Vazia(filaD1)){
        aux = filaD1->frente->prox;
            while(aux != NULL){
                aux->aviao.Ciclos++;
                aux = aux->prox;
            }
        }

        if(!Vazia(filaD2)){
        aux = filaD2->frente->prox;
            while(aux != NULL){
                aux->aviao.Ciclos++;
                aux = aux->prox;
            }
        }

        if(!Vazia(filaD3)){
            aux = filaD3->frente->prox;
            while(aux != NULL){
                aux->aviao.Ciclos++;
                aux = aux->prox;
            }
        }


}
