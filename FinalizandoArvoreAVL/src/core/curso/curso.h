#pragma once

#include "../../structs/info/struct_curso.h"
#include "../../arvoreAVL/arvore_avl.h"

// Auxs

void showCurso(Info info);
void freeNodeCurso(Info info);

// ---------------------------------------------------------------------------------------

// - Permitir o cadastro de um curso na árvore de curso.
// - Não é necessário cadastrar disciplinas no momento do cadastro do curso.
int cadastrarCursos(Arvore **arvoreCurso);