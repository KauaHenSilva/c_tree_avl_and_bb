#include "arvore_avl.h"
#include <stdlib.h>

static int altura(Arvore *raiz)
{
  int alturaAtual = -1;

  if (raiz)
  {
    int alturaEsq = altura(raiz->esq);
    int alturaDir = altura(raiz->dir);
    // FeedBack da professora: Não faça oque foi feito na linha 14.
    // Pega a variavel tamanho que está na estrutura da arvore avl! Outra coisa, cuidado com a usabilidade!
    alturaAtual = ((alturaEsq > alturaDir) ? alturaEsq : alturaDir) + 1;
  }

  return alturaAtual;
}

static int rotacaoDireita(Arvore **raiz)
{
  int confirm = 1;

  if (*raiz)
  {
    Arvore *aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;

    (*raiz)->altura = altura(*raiz);
    aux->altura = altura(aux);

    *raiz = aux;
  }
  else
    confirm = 0;

  return confirm;
}

static int rotacaoEsquerda(Arvore **raiz)
{
  int confirm = 1;

  if (*raiz)
  {
    Arvore *aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;

    (*raiz)->altura = altura(*raiz);
    aux->altura = altura(aux);

    *raiz = aux;
  }
  else
    confirm = 0;

  return confirm;
}

static void balanceamento(Arvore **arvore)
{
  Arvore *aux;
  int fb = altura((*arvore)->esq) - altura((*arvore)->dir);

  if (fb >= 2)
  {
    aux = (*arvore)->esq;

    fb = altura(aux->esq) - altura(aux->dir);
    if (fb < 0)
      rotacaoEsquerda(&(*arvore)->esq);
    rotacaoDireita(arvore);
  }
  else if (fb <= -2)
  {
    aux = (*arvore)->dir;

    fb = altura(aux->esq) - altura(aux->dir);
    if (fb > 0)
      rotacaoDireita(&(*arvore)->dir);
    rotacaoEsquerda(arvore);
  }
}

/**
 * @brief Insere um novo nó na árvore binária de busca.
 *
 * Esta função insere um novo nó na árvore binária de busca apontada por `raiz`.
 * A inserção é feita de acordo com a função de comparação fornecida.
 *
 * @param raiz Ponteiro para o ponteiro da raiz da árvore.
 * @param new Ponteiro para o novo nó a ser inserido.
 * @param compareMenor Função de comparação que recebe dois argumentos do tipo
 * Info, retorna 1 caso o primeiro argumento seja menor que o segundo.
 * @param compareMaior Função de comparação que recebe dois argumentos do tipo
 * Info, retorna 1 caso o primeiro argumento seja maior que o segundo.
 *
 *
 * @return Retorna 0 em caso de sucesso e -1 em caso de erro.
 */
int insertTree(Arvore **raiz, Arvore *new)
{
  int confirm = 1;

  if (!*raiz)
  {
    *raiz = new;
  }
  else
  {
    if (new->info.codigo < (*raiz)->info.codigo)
      confirm = insertTree(&(*raiz)->esq, new);
    else if (new->info.codigo > (*raiz)->info.codigo)
      confirm = insertTree(&(*raiz)->dir, new);
    else
      confirm = 0;
  }
  
  if (confirm)
  {
    (*raiz)->altura = altura(*raiz);
    balanceamento(raiz);
  }

  return confirm;
}

/**
 * @brief Libera a memória alocada para a árvore binária.
 *
 * Esta função percorre a árvore binária a partir da raiz e libera a memória
 * alocada para cada nó, utilizando a função fornecida para liberar a informação
 * contida em cada nó.
 *
 * @param raiz Ponteiro para a raiz da árvore binária.
 * @param freeInfo Função utilizada para liberar a memória da informação contida
 * em cada nó. NULL para exquipar a função.
 */
void freeTree(Arvore *raiz, void (*freeInfo)(Info))
{
  if (raiz)
  {
    freeTree(raiz->esq, freeInfo);
    freeTree(raiz->dir, freeInfo);

    if (freeInfo)
      freeInfo(raiz->info);

    free(raiz);
  }
}

/**
 * @brief Aloca memória para a árvore binária.
 *
 * Esta função aloca memória para a estrutura de dados da árvore binária
 * e inicializa a raiz como NULL.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore.
 */
void alocTree(Arvore **raiz)
{
  *raiz = (Arvore *)malloc(sizeof(Arvore));
  (*raiz)->esq = NULL;
  (*raiz)->dir = NULL;
}

/**
 * @brief Exibe a árvore binária.
 *
 * Esta função percorre a árvore binária a partir da raiz e exibe as informações
 * de cada nó utilizando a função fornecida pelo usuário.
 *
 * @param raiz Ponteiro para a raiz da árvore binária.
 * @param showInfo Função fornecida pelo usuário para exibir as informações de
 * cada nó.
 */
void showTree(Arvore *raiz, void (*showInfo)(Info))
{
  if (raiz)
  {
    showInfo(raiz->info);
    showTree(raiz->esq, showInfo);
    showTree(raiz->dir, showInfo);
  }
}

/**
 * @brief Busca um nó na árvore binária.
 *
 * Esta função procura um nó na árvore binária a partir da raiz fornecida,
 * utilizando um código e uma função de comparação.
 *
 * @param raiz Ponteiro para a raiz da árvore.
 * @param codigo Código a ser buscado na árvore.
 * @param result Ponteiro para armazenar o resultado da busca.
 * @param compare Função de comparação que recebe um inteiro e uma estrutura
 * Info, Deve retornar 1 se o primeiro argumento for menor, 0 se forem iguais, 2
 * se o primeiro argumento for maior.
 *
 * @return Retorna 1 se o nó for encontrado, caso contrário, retorna 0.
 */
int searchNodeTree(Arvore *raiz, Info info, Arvore **result)
{
  int confirm = 1;

  if (raiz)
  {
    if (info.codigo == raiz->info.codigo)
      *result = raiz;
    else
    {
      if (info.codigo < raiz->info.codigo)
        confirm = searchNodeTree(raiz->esq, info, result);
      else
        confirm = searchNodeTree(raiz->dir, info, result);
    }
  }
  else
    confirm = 0;

  return confirm;
}

/**
 * @brief Verifica se um nó da árvore é uma folha.
 *
 * Esta função verifica se o nó fornecido (raiz) é uma folha, ou seja,
 * se não possui filhos à esquerda nem à direita.
 *
 * @param raiz Ponteiro para o nó da árvore a ser verificado.
 * @return Retorna 1 se o nó for uma folha, caso contrário, retorna 0.
 */
static int ehFolha(Arvore *raiz)
{
  return (raiz->esq == NULL && raiz->dir == NULL);
}

/**
 * @brief Função que verifica se um nó da árvore possui apenas um filho.
 *
 * @param raiz Ponteiro para o nó raiz da árvore.
 * @return Ponteiro para o nó da árvore que possui apenas um filho.
 */
static Arvore *soUmFilho(Arvore *raiz)
{
  Arvore *aux = NULL;
  if (raiz->esq == NULL && raiz->dir != NULL)
    aux = raiz->dir;
  else if (raiz->esq != NULL && raiz->dir == NULL)
    aux = raiz->esq;
  return aux;
}

/**
 * @brief Encontra o menor filho de uma árvore binária de busca.
 *
 * Esta função percorre a árvore binária de busca a partir da raiz fornecida
 * e retorna o nó que contém o menor valor (mais à esquerda).
 *
 * @param raiz Ponteiro para a raiz da árvore binária de busca.
 * @return Ponteiro para o nó que contém o menor valor na árvore.
 */
static Arvore *menorFilho(Arvore *raiz)
{
  Arvore *atual = raiz;
  while (atual && atual->esq != NULL)
    atual = atual->esq;
  return atual;
}

/**
 * @brief Remove um nó da árvore binária de busca.
 *
 * Esta função remove um nó da árvore binária de busca que contém a informação especificada.
 *
 * @param raiz Ponteiro duplo para a raiz da árvore.
 * @param remove Informação a ser removida da árvore.
 * @param compare Função de comparação que determina a ordem dos elementos na árvore.
 *
 * @return Inteiro indicando o sucesso (1) ou falha (0) da remoção.
 */
int removerNodeArvore(Arvore **raiz, Info remove)
{
  int confirm = 1;

  if (*raiz)
  {

    if (remove.codigo == (*raiz)->info.codigo)
    {
      if (ehFolha(*raiz))
      {
        free((*raiz));
        (*raiz) = NULL;
      }
      else if (soUmFilho(*raiz) != NULL)
      {
        Arvore *aux = (*raiz);
        (*raiz) = soUmFilho(*raiz);
        free(aux);
      }
      else
      {
        Arvore *aux = menorFilho((*raiz)->dir);
        (*raiz)->info = aux->info;
        confirm = removerNodeArvore(&(*raiz)->dir, aux->info);
      }
    }
    else
    {
      if (remove.codigo < (*raiz)->info.codigo)
        confirm = removerNodeArvore(&(*raiz)->esq, remove);
      else
        confirm = removerNodeArvore(&(*raiz)->dir, remove);

      if (raiz)
      {
        (*raiz)->altura = altura(*raiz);
        balanceamento(raiz);
      }
    }
  }
  else
    confirm = 0;

  return confirm;
}
