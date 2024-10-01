#pragma once

#include "../../structs/info/struct_curso.h"
#include "../../structs/info/struct_disciplina.h"
#include "../../arvoreBB/arvore_bb.h"

// Auxs

void showDisciplina(Info info);
void freeNodeDisciplina(Info info);

// ---------------------------------------------------------------------------------------

// - Permitir o cadastro de disciplinas em uma árvore de disciplinas de um curso.
// - O curso deve estar cadastrado.
// - O período da disciplina deve estar entre 1 e a quantidade máxima de períodos do curso.
// - A carga horária deve ser múltiplo de 15, variando entre 30 e 90.
int cadastrarDisciplinas(Arvore *curso);

// int ehFolhaDisciplina(NodeDisciplina *raiz);
// NodeDisciplina *soUmFilhoDisciplina(NodeDisciplina *raiz);
// NodeDisciplina *menorFilhoDisciplina(NodeDisciplina *raiz);
// int removerDisciplina(NodeDisciplina **raiz, int codDisciplina);
