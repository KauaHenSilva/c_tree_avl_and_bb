#include "buscas.h"
#include <stdio.h>

#include "../aluno/aluno.h"
#include "../curso/curso.h"
#include "../disciplina/disciplina.h"
#include "../nota/nota.h"
#include "../matricula/matricula.h"

#include "../../arvoreAVL/arvore_avl.h"

void mostrarTodosOsAlunosDeUmCurso(Arvore *arvoreCurso, ListAluno *alunos)
{
  if (alunos)
  {
    if (arvoreCurso->info.curso.codigo == alunos->aluno.codigoDoCurso)
      showAluno(alunos);
    mostrarTodosOsAlunosDeUmCurso(arvoreCurso, alunos->prox);
  }
}

void MostrarTodosOsCursosDoCampus(Arvore *arvoreCursos)
{
  showTree(arvoreCursos, showCurso);
}

void mostrarTodasAsDisciplinasDeUmCurso(Arvore *arvoreCurso)
{
  showTree(arvoreCurso->info.curso.arvoreDisciplinas, showDisciplina);
}

static void showAllDisciplinaByPeriod(Arvore *arvoreDisciplina, int periodo)
{
  if (arvoreDisciplina)
  {
    if (arvoreDisciplina->info.disciplina.periodo == periodo)
      showDisciplina(arvoreDisciplina->info);

    showAllDisciplinaByPeriod(arvoreDisciplina->esq, periodo);
    showAllDisciplinaByPeriod(arvoreDisciplina->dir, periodo);
  }
}

void mostrarDisciplinasDeUmPeriodoDeUmCurso(Arvore *arvoreCurso, int periodo)
{
  showAllDisciplinaByPeriod(arvoreCurso->info.curso.arvoreDisciplinas, periodo);
}

static void _mostarDisciplinasDeUmAluno(Arvore *raizMatriculasAluno, Arvore *raizDisciplina)
{
  if (raizDisciplina)
  {
    showDisciplina(raizDisciplina->info);
    _mostarDisciplinasDeUmAluno(raizMatriculasAluno, raizDisciplina->esq);
    _mostarDisciplinasDeUmAluno(raizMatriculasAluno, raizDisciplina->dir);
  }
}

void mostrarDisciplinasDeUmAluno(Arvore *raizMatriculasAluno, Arvore *raizDisciplina)
{
  if (raizMatriculasAluno)
  {
    if (raizMatriculasAluno->info.matricula.codigo == raizDisciplina->info.disciplina.codigo)
      _mostarDisciplinasDeUmAluno(raizMatriculasAluno, raizDisciplina);
    else if (raizMatriculasAluno->info.matricula.codigo < raizDisciplina->info.disciplina.codigo)
      mostrarDisciplinasDeUmAluno(raizMatriculasAluno->esq, raizDisciplina);
    else
      mostrarDisciplinasDeUmAluno(raizMatriculasAluno->dir, raizDisciplina);
  }
}

void mostrarNotasDeUmAlunoPorPeriodo(Arvore *raizNota, int periodo)
{
  if (raizNota)
  {
    if (raizNota->info.nota.semestreCursado == periodo)
      showNota(raizNota->info);
    mostrarNotasDeUmAlunoPorPeriodo(raizNota->esq, periodo);
    mostrarNotasDeUmAlunoPorPeriodo(raizNota->dir, periodo);
  }
}

void mostrarNotaDeUmaDisciplina(Arvore *raizDisciplinaAtual, Arvore *raizNota)
{
  if (raizNota)
  {
    if (raizNota->info.nota.codDisciplina == raizDisciplinaAtual->info.disciplina.codigo)
    {
      showNota(raizNota->info);
      showDisciplina(raizDisciplinaAtual->info);
    }
    mostrarNotaDeUmaDisciplina(raizDisciplinaAtual, raizNota->esq);
    mostrarNotaDeUmaDisciplina(raizDisciplinaAtual, raizNota->dir);
  }
}

void imprimirHistoricoAluno(ListAluno *aluno, Arvore *raizCursos)
{
  Arvore *arvorecurso;

  Info info;
  info.codigo = aluno->aluno.codigoDoCurso;

  if (searchNodeTree(raizCursos, info, &arvorecurso))
    printf("- Nome do curso: %s\n", arvorecurso->info.curso.nomeDoCurso);
  else
    printf("- Curso não encontrado!\n");

  printf("- disciplinas:\n");
  showTree(arvorecurso->info.curso.arvoreDisciplinas, showDisciplina);

  printf("- Notas por periodo:\n");
  for (int i = 1; i <= arvorecurso->info.curso.quantidadeDePeriodo; i++)
  {
    printf("- Notas do aluno %d no periodo %d: \n", aluno->aluno.matricula, i);
    mostrarNotasDeUmAlunoPorPeriodo(aluno->aluno.arvoreNota, i);
  }
}
