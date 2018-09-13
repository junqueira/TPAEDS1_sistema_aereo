#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tadListaDeVoo.h"

void printGets(tadVoo *aux) {
    printf("VID: %d\n", getVid(aux)); //
    printf("Hora Decolagem: %s\n", getHrDecolagem(aux));
    printf("Hora Prevista para Pouso: %s\n", getHrPrevPouso(aux));
    printf("Aeroporto Decolagem: %s\n", getAeroportoDecolagem(aux));
    printf("Aeroporto Previsto para Pouso: %s\n", getAeroportoPrevPouso(aux));
    printf("Pista de Decolagem: %d\n\n", getPistaDecolagem(aux));
}
//inicializa a lista encadeada(recebida como parâmetro) vazia

void fazListaVazia(tadListaVoo* listaVoo) {
    listaVoo->primeiro = (tipoApontador) malloc(sizeof (tipoCelula)); //Aloca um espaço do tamanho de uma célula para
    // receber a célula cabeça e armazena no ponteiro que aponta para o primeiro elemento da lista
    listaVoo->ultimo = listaVoo->primeiro; //Faz o ponteiro último apontar para o primeiro elemento
    listaVoo->primeiro->prox = NULL; //Faz o ponteiro próx(próximo) da minha célula cabeça apontar para NULL
}
//Verifica se minha lista encadeada(recebida como parâmetro) está vazia

int vazia(tadListaVoo listaVoo) {
    return (listaVoo.primeiro == listaVoo.ultimo); //retorna 1 caso a igualdade seja verdadeira
}

//Imprime todos os voos da lista encadeada (recebida como parâmetro)

void imprimeVoo(tadListaVoo listaVoo) {
    tipoApontador aux; //Crio um ponteiro auxiliar para percorrer a lista
    aux = listaVoo.primeiro->prox; //Faço o ponteiro ser igual ao ponteiro prox do primeiro elemento da lista(célula cabeça)
    while (aux != NULL) { //Enquanto o ponteiro próx(próximo) não apontar para NULL
        printGets(&aux->voo);
        aux = aux->prox; //Incrementa meu ponteiro para o próximo elemento da lista
    }
}

//Insere um item(voo) de lista linear na minha lista encadeada(recebida como parâmetro) e retorna 0 caso operação tenha sucesso

int insereVoo(tadVoo voo, tadListaVoo* listaVoo) {
    tipoApontador posicao, novo; //Crio um ponteiro para posição em que deve ser inserido e um ponteiro para o novo item
    posicao = listaVoo->primeiro; //Posição começa do primeiro elemento(célula cabeça)
    //Enquanto meu ponteiro prox(próximo) não apontar para NULL E minha comparação de string(hora de decolagem
    // do voo contido na lista encadeada e do voo recebido como parâmetro) for menor do que 0, percorra a lista
    while (posicao->prox != NULL) {
        if (strcmp(posicao->prox->voo.hrDecolagem, voo.hrDecolagem) >= 0) {
            novo = (tipoApontador) malloc(sizeof (tipoCelula)); //Aloco um espaço para minha nova célula para nova informação
            novo->voo = voo; //Minha informação contida na célula será o voo recebido como parâmetro
            novo->prox = posicao->prox; //Aponto meu ponteiro de prox(próximo) para o mesmo local em que meu antigo ponteiro
            // da posição em que devo colocar apontava
            posicao->prox = novo; //Aponto meu antigo ponteiro da posição em que devo colocar apontava, para o novo item da listacao->prox = novo; //Aponto meu antigo ponteiro da posição em que devo colocar apontava, para o novo item da lista
            return 0; //Retorno 0 pois meu item(TADVoo) já foi inserido corretamente
        }
        posicao = posicao->prox; //Incrementa meu ponteiro para o próximo elemento da lista
    }
    listaVoo->ultimo->prox = (tipoApontador) malloc(sizeof (tipoCelula)); //Aloco um espaço para minha nova célula para nova informação
    listaVoo->ultimo = listaVoo->ultimo->prox;
    listaVoo->ultimo->voo = voo; //Minha informação contida na célula será o voo recebido como parâmetro
    listaVoo->ultimo->prox = NULL;
    return 0;
}

//Retira o item da lista e retorna o item (TADVoo) para uso no programa

int retornaVoo(tadListaVoo* listaVoo, int vid, tadVoo* voo) {
    tipoApontador posicao, aux; //Crio um ponteiro posicao para percorrer a lista e um ponteiro auxiliar para
    // receber meu novo ponteiro
    if(vazia(*listaVoo)) return 1;
    posicao = listaVoo->primeiro; //Posição começa do primeiro elemento(célula cabeça)
    while (posicao->prox != NULL && posicao->prox->voo.vid != vid) {
        //Enquanto meu ponteiro prox(próximo) não apontar para NULL E meu VID do item (TADVoo) for diferente do que
        //eu recebi como parâmetro, percorra a lista
        posicao = posicao->prox; //Incrementa meu ponteiro para o próximo elemento da lista
    }
    aux = posicao->prox; //Meu ponteiro auxiliar vai receber o ponteiro prox da posição encontrada
    *voo = aux->voo; //Meu item(TADVoo) dessa posicao vai ser armazenado no TADVoo criado anteriormente
    posicao->prox = aux->prox; //A posição do próximo vai ser a mesma do próximo do ponteiro auxiliar
    if (posicao->prox == NULL) listaVoo->ultimo = posicao; //Se a próxima posição for NULL meu ponteiro para o último
    //recebe essa posição
    free(aux); //Libero a célula do HEAP
    return 0; //Retorno o item encontrado
}

//Procuro o item da lista e retorno o item(TADVoo) para o uso no programa

tadVoo procuraVoo(tadListaVoo* listaVoo, int vid) {
    tipoApontador posicao; //Crio um ponteiro posicao para percorrer a lista e armazenar a posição encontrada
    posicao = listaVoo->primeiro; //Posição começa do primeiro elemento da lista(célula cabeça)
    while (posicao->prox != NULL && posicao->prox->voo.vid != vid) {
        //Enquanto meu ponteiro prox(próximo) não apontar para NULL E meu VID do item (TADVoo) for diferente do que
        //eu recebi como parâmetro, percorra a lista
        posicao = posicao->prox; //Incrementa meu ponteiro para o próximo elemento da lista
    }
    return posicao->prox->voo; //Retorno o item encontrado sem retirá-lo da lista encadeada
}