#include <stdio.h>
#include <stdlib.h>

#include "../../core/aluno/aluno.h"
#include "../../core/curso/curso.h"
#include "../../core/disciplina/disciplina.h"
#include "../../core/matricula/matricula.h"
#include "../../core/nota/nota.h"

#include "../../core/buscas/buscas.h"
#include "../validacoes/validacoes.h"

#include "menu.h"

void menu(int *opcao)
{
  printf("0 - Sair\n");
  printf("1 - Cadastrar Curso\n");
  printf("2 - Cadastrar Disciplina\n");
  printf("3 - Cadastrar Aluno\n");
  printf("4 - Cadastrar Matricula\n");
  printf("5 - Cadastrar Nota\n");
  printf("6 - Mostrar Todos os Cursos\n");
  printf("7 - Mostrar Todos os Alunos de um Curso\n");
  printf("8 - Mostrar Todas as Disciplinas de um Curso\n");
  printf("9 - Mostrar Disciplinas de um Período de um Curso\n");
  printf("10 - Mostrar Disciplinas de um Aluno\n");
  printf("11 - Mostrar Notas de um Aluno por Período\n");
  printf("12 - Mostrar Nota de uma Disciplina\n");
  printf("13 - Remover Disciplina de um Curso\n");
  printf("14 - Remover Disciplina da Árvore de Matrícula\n");
  printf("15 - Mostrar Histórico de um Aluno\n");
  printf("Digite a opção desejada: ");
  scanf("%d", opcao);
  printf("--------------------------------------------------------------\n");
}

void initMenu(ListAluno *alunos, Arvore *arvoreCursos)
{
  (void)alunos;
  int opcao = -1;

  while (opcao != 0)
  {
    menu(&opcao);

    Arvore *arvoreCursoAtual = NULL;
    Arvore *arvoreDisciplinaAtual = NULL;
    Arvore *arvoreMatriculaAtual = NULL;
    ListAluno *alunoAtual = NULL;

    Arvore *arvoreDisciplinas = NULL;
    Arvore *arvoreMatriculas = NULL;
    Arvore *arvoreNotas = NULL;

    int codCurso = 0;
    int codDisciplina = 0;
    int codMatricula = 0;
    int codAluno = 0;
    int periodo = 0;

    switch (opcao)
    {
    case 0:
      break;

    case 1:
      if (!cadastrarCursos(&arvoreCursos))
        printf("Não foi possível cadastrar o curso\n");
      break;

    case 2:
      if (!cadastrarDisciplinas(arvoreCursos))
        printf("Não foi possível cadastrar a disciplina\n");
      break;

    case 3:
     if(!cadastrarAlunos(&alunos, arvoreCursos))
        printf("Não foi possível cadastrar o aluno\n");
      break;

    case 4:
      if (!cadastrarMatriculas(alunos, arvoreCursos))
        printf("Não foi possível cadastrar a matricula\n");
      break;

    case 5:
      if (!cadastrarNotas(alunos))
        printf("Não foi possível cadastrar a nota\n");
      break;

    case 6:
      if (!arvoreCursos)
        printf("Nenhum curso cadastrado!\n");
      else
        MostrarTodosOsCursosDoCampus(arvoreCursos);
      break;

    case 7:
      if (!arvoreCursos || !alunos)
        printf("Nenhum curso ou aluno cadastrado!\n");
      else if (!getCursoValido(&codCurso, arvoreCursos, &arvoreCursoAtual))
        printf("Curso invalido\n");
      else
        mostrarTodosOsAlunosDeUmCurso(arvoreCursoAtual, alunos);
      break;

    case 8:
      if (!arvoreCursos)
        printf("Nenhum curso cadastrado!\n");
      else if (!getCursoValido(&codCurso, arvoreCursos, &arvoreCursoAtual))
        printf("Curso invalido\n");
      else
        mostrarTodasAsDisciplinasDeUmCurso(arvoreCursoAtual);
      break;

    case 9:
      if (!arvoreCursos)
        printf("Nenhum curso cadastrado!\n");
      else if (!getCursoValido(&codCurso, arvoreCursos, &arvoreCursoAtual))
        printf("Curso invalido\n");
      else if (!getPeriodoValido(&periodo, arvoreCursoAtual->info.curso.quantidadeDePeriodo))
        printf("Periodo invalido\n");
      else
        mostrarDisciplinasDeUmPeriodoDeUmCurso(arvoreCursoAtual, periodo);
      break;

    case 10:
      if (!alunos && !arvoreCursos)
        printf("Nenhum curso ou aluno cadastrado!\n");
      else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
        printf("Aluno invalido\n");
      else
      {
        Info info;
        info.curso.codigo = alunoAtual->aluno.codigoDoCurso;
        if (!(searchNodeTree(arvoreCursos, info, &arvoreCursoAtual)))
          printf("Curso do aluno não encontrado\n");
        else if (!arvoreCursoAtual->info.curso.arvoreDisciplinas)
          printf("Curso sem disciplinas\n");
        // A linha abaixo está com erro, em vez de nota e pata verificar se aluno tem disciplina.
        else if (!(arvoreNotas = alunoAtual->aluno.arvoreNota))
          printf("Aluno sem notas\n");
        else
          mostrarDisciplinasDeUmAluno(alunoAtual->aluno.arvoreMatricula, arvoreCursoAtual->info.curso.arvoreDisciplinas);
      }
      break;

    case 11:
      if (!alunos || !arvoreCursos)
        printf("Nenhum aluno ou curso cadastrado\n");
      else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
        printf("Aluno invalido\n");
      else
      {
        Info info;
        info.curso.codigo = alunoAtual->aluno.codigoDoCurso;

        if (!(searchNodeTree(arvoreCursos, info, &arvoreCursoAtual)))
          printf("Curso do aluno não encontrado\n");
        else if (!(getPeriodoValido(&periodo, arvoreCursoAtual->info.curso.quantidadeDePeriodo)))
          printf("Periodo invalido\n");
        else
          mostrarNotasDeUmAlunoPorPeriodo(alunoAtual->aluno.arvoreNota, periodo);
      }
      break;

    case 12:
      // Mostrar a nota de uma disciplina de um determinado aluno,
      //     mostrando o período e a carga horária da disciplina.
      if (!arvoreCursos || !alunos)
        printf("Nenhum curso cadastrado!\n");
      else if (!getCursoValido(&codCurso, arvoreCursos, &arvoreCursoAtual))
        printf("curso invalido\n");
      else if (!(arvoreDisciplinas = arvoreCursoAtual->info.curso.arvoreDisciplinas))
        printf("Curso sem disciplinas\n");
      else if (!getDisciplinaValida(&codDisciplina, arvoreDisciplinas, &arvoreDisciplinaAtual))
        printf("disciplina invalida\n");
      else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
        printf("aluno invalido\n");
      else if (!alunoAtual->aluno.arvoreNota)
        printf("Aluno sem notas\n");
      else
        mostrarNotaDeUmaDisciplina(alunoAtual->aluno.arvoreNota, arvoreDisciplinaAtual);

      break;

    case 13:
      // Permitir a remoção de uma disciplina de um curso, desde que nenhum aluno esteja matriculado nela.

      if (!arvoreCursos)
        printf("Nenhum curso cadastrado!\n");
      else if (!getCursoValido(&codCurso, arvoreCursos, &arvoreCursoAtual))
        printf("curso invalido\n");
      else if (!(arvoreDisciplinas = arvoreCursoAtual->info.curso.arvoreDisciplinas))
        printf("Curso sem disciplinas\n");
      else if (!getDisciplinaValida(&codDisciplina, arvoreDisciplinas, &arvoreDisciplinaAtual))
        printf("disciplina invalida\n");
      else if (boolAlunoInDisciplina(alunos, codDisciplina))
        printf("Não pode remover disciplina com aluno matriculado!\n");
      else if (!removerNodeArvore(&arvoreDisciplinas, arvoreDisciplinaAtual->info))
        printf("Não foi possível remover a disciplina\n");
      break;

    case 14:
      if (!alunos)
        printf("Nenhum aluno cadastrado!\n");
      else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
        printf("Aluno invalido\n");
      else if (!(arvoreMatriculas = alunoAtual->aluno.arvoreMatricula))
        printf("Aluno sem matriculas\n");
      else if (!getMatriculaValida(&codMatricula, alunoAtual->aluno.arvoreMatricula, &arvoreMatriculaAtual))
        printf("Matricula invalida\n");
      else if (!removerNodeArvore(&arvoreMatriculas, arvoreMatriculaAtual->info))
        printf("Não foi possível remover a matricula\n");
      break;

    case 15:
      if (!alunos || !arvoreCursos)
        printf("Nenhum aluno ou curso cadastrado\n");
      else if (!getAlunoValido(&codAluno, alunos, &alunoAtual))
        printf("aluno invalido\n");
      else
        imprimirHistoricoAluno(alunoAtual, arvoreCursos);
      break;

    default:
      printf("Opção inválida!\n");
      break;
    }
    printf("--------------------------------------------------------------\n");
  }
}