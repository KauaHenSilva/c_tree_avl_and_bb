#pragma once

#include <struct_curso.h>

// Auxs

void freeNodeCursos(NodeCurso *node);
void showAllCurso(NodeCurso *curso);
void isCurseOpen(NodeCurso *curso, int id, int *bool);

// ---------------------------------------------------------------------------------------

// - Permitir o cadastro de um curso na árvore de curso.
// - Não é necessário cadastrar disciplinas no momento do cadastro do curso.
int cadastrarCursos(NodeCurso **nodeCurso);

// - Permitir a remoção de uma disciplina de um curso, desde que nenhum aluno esteja matriculado nela.
void removerDisciplinaDeUmCurso();
