#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
//struct que guarda as informa��es de um livro
typedef struct {
	int codigo;
	char titulo[151];
	char autor[201];
	char editora[51];
	int edicao;
	int ano;
	int qtdExemplares;
}INFO;
//cabecalho dos arquivos bin�rios, guarda a cabe�a e o topo da lista 
typedef struct {
	int cabeca;
	int topo;
}CABECALHO;
//struct que ser� armazenada no arquivo bin�rio que conter� a lista de livros, 
//possui as informa��es do livro e o numero de registro do proximo da lista no arquivo 
typedef struct {
	INFO informacoes;
	int prox;
}LIVRO_BIN;
//struct n� usada para manter a lista din�mica na mem�ria, 
//possui as informa��es do livro e o endere�o do pr�ximo elemento na mem�ria durante a execu��o do programa
typedef struct noLivro {
	LIVRO_BIN arquivo;
	struct noLivro* prox;
}LIVRO;
//struct que ser� armazenada no arquivo bin�rio que conter� a lista de usu�rios,
//possui as informa��es do usu�rio e o numero de registro do proximo da lista no arquivo
typedef struct {
	int codigo;
	char nome[51];
	int prox;
}USUARIO_BIN;
//struct n� usada para manter a lista din�mica na mem�ria, 
//possui as informa��es do usuario e o endere�o do pr�ximo elemento na mem�ria durante a execu��o do programa
typedef struct noUsuario {
	USUARIO_BIN arquivo;
	struct noUsuario* prox;
}USUARIO;
//struct que ser� armazenada no arquivo bin�rio que conter� a lista de empr�stimos,
//possui as informa��es de empr�stimo e o numero de registro do proximo da lista no arquivo
typedef struct {
	int codUsuario;
	int codLivro;
	char dataEmprestimo[11];
	char dataDevolucao[11];
	int prox;
}EMPRESTIMO_BIN;
//struct n� usada para manter a lista din�mica na mem�ria, 
//possui as informa��es do empr�stimo e o endere�o do pr�ximo elemento na mem�ria durante a execu��o do programa
typedef struct noEmpresta {
	EMPRESTIMO_BIN arquivo;
	struct noEmpresta* prox;
}EMPRESTIMO;
//verificam se a lista � vazia
//pr�-condi��o: nenhuma
//p�s-condi��o: nenhuma
//entrada: recebe um ponteiro para a lista
//retorno: retorna 1 caso a lista seja vazia, e 0 para os outros casos
int vaziaL(LIVRO* lista);
int vaziaU(USUARIO* lista);
int vaziaE(EMPRESTIMO* lista);
//cria uma estrutura cabecalho para o arquivo binario
//pr�-condi��o: nenhuma
//p�s-condi��o: cabecalho � alocado na mem�ria e gravado no arquivo bin�rio correspondente
//entrada: uma letra minuscula representando qual arquivo estar� sendo inicializado
//retorno: um ponteiro sem tipo para a estrutura cabecalho correspondente 
void* criaCabecalho(char tipo);
//cria uma lista vazia
//pr�-condi��o: nenhuma
//p�s-condi��o: lista � alocada na mem�ria
//entrada: nenhuma
//retorno: ponteiro para uma lista sem elementos
LIVRO* criaListaLivros();
//insere um novo livro na lista
//pr�-condi��o: devem ter sido inicializados uma lista e um cabe�alho correspondentes
//p�s-condi��o: o elemento � adcionado, se tornando a nova cabe�a da lista
//entrada: endere�o para a estrutura de cabe�alho do respectivo arquivo bin�rio onde a estrutura ser� gravada,
//endere�o da estrutura cabe�a de uma lista inicializada e uma estrutura do tipo INFO que guarda as especifica��es do livro
//retorno: endere�o da estrutura adicionada e que representa a nova cabe�a da lista
LIVRO* cadastrarLivro(CABECALHO** cab, LIVRO* lista, INFO info);
//imprime as informa��es de todos os livros da lista
//pr�-condi��o: a lista n�o pode ser vazia
//p�s-condi��o: nenhuma
//entrada: endere�o da cabe�a da lista
//retorno: nenhum
void listarLivros(LIVRO* cabeca);
//dado um codigo de livro, busca o livro na lista e imprime os dados correspondentes na tela
//pr�-condi��o: a lista deve existir e conter itens
//p�s-condi��o: nenhuma
//entrada: endere�o da cabe�a da lista e o n�mero inteiro que representa o livro
//retorno: nenhum
void buscaLivroCod(LIVRO* lista, int cod);
//dado um titulo de livro, busca o livro na lista e imprime os dados correspondentes na tela
//pr�-condi��o: a lista deve existir e conter itens
//p�s-condi��o: nenhuma
//entrada: endere�o da cabe�a da lista e a string do titulo que representa o livro
//retorno: nenhum
void buscaTit(LIVRO* lista, char* titulo);
//retorna o total de livros diferentes na lista
//pr�-condi��o: a lista deve existir
//p�s-condi��o: nenhuma
//entrada: endere�o da cabe�a da lista
//retorno: inteiro com a quantidade de livros na lista
int totalLivros(LIVRO* lista);
//cria uma lista vazia
//pr�-condi��o: nenhuma
//p�s-condi��o: lista � alocada na mem�ria
//entrada: nenhuma
//retorno: ponteiro para uma lista sem elementos
USUARIO* criaListaUsuarios();
//insere um novo livro na lista
//pr�-condi��o: devem ter sido inicializados uma lista e um cabe�alho correspondentes
//p�s-condi��o: o elemento � adcionado, se tornando a nova cabe�a da lista
//entrada: endere�o para a estrutura de cabe�alho do respectivo arquivo bin�rio onde a estrutura ser� gravada, 
//ponteiro para a cabe�a da lista, inteiro �nico que representa o usuario e string que representa seu nome
//retorno: endere�o da estrutura adicionada e que representa a nova cabe�a da lista
USUARIO* cadastrarUsuario(CABECALHO** cab, USUARIO* lista, int cod, char* nome);
//imprime as informa��es de todos os usuarios da lista
//pr�-condi��o: a lista n�o pode ser vazia
//p�s-condi��o: nenhuma
//entrada: endere�o da cabe�a da lista
//retorno: nenhum
void listarUsuarios(USUARIO* cabeca);
//dado um codigo de usuario, busca o usuario na lista e imprime os dados correspondentes na tela
//pr�-condi��o: a lista deve existir e conter itens
//p�s-condi��o: nenhuma
//entrada: endere�o da cabe�a da lista e o n�mero inteiro que representa o usuario
//retorno: nenhum
void buscaUsuarioCod(USUARIO* lista, int cod);
//dado um nome de usuario, busca o usuario na lista e imprime os dados correspondentes na tela
//pr�-condi��o: a lista deve existir e conter itens
//p�s-condi��o: nenhuma
//entrada: endere�o da cabe�a da lista e a string que representa o nome do usuario
//retorno: nenhum
void buscaNome(USUARIO* lista, char* titulo);
//retorna o total de usuario na lista
//pr�-condi��o: a lista deve existir
//p�s-condi��o: nenhuma
//entrada: endere�o da cabe�a da lista
//retorno: inteiro com a quantidade de usuarios na lista
int totalUsuarios(USUARIO* lista);
//cria uma lista vazia
//pr�-condi��o: nenhuma
//p�s-condi��o: lista � alocada na mem�ria
//entrada: nenhuma
//retorno: ponteiro para uma lista sem elementos
EMPRESTIMO* criarListaEmprestimo();
//registra um empr�stimo na lista, salva o usuario o livro e a data do emprestimo
//pr�-condi��o: existir uma lista de livros e de usu�rios com itens e uma de emprestimo inicializada
//p�s-condi��o: � adicionado um empr�stimo na cabe�a da lista
//entrada: endere�o da estrutura cabe�alho do arquivo emprestimo.bin, dois inteiros representando respectivamente o usuario e o livro,
//e os respectivos endere�os das cabe�as das listas de livros, usuarios e emprestimos
//retorno: ponteiro para a nova cabe�a da lista de empr�stimos
EMPRESTIMO* emprestar(CABECALHO** cab, int codUsuario, int codLivro, EMPRESTIMO* listaE);
//registra um empr�stimo na lista, recebido de registro em um arquivo txt
//pr�-condi��o: existir uma lista de livros e de usu�rios com itens e uma de emprestimo inicializada
//p�s-condi��o: � adicionado um empr�stimo na cabe�a da lista
//entrada: endere�o da estrutura cabe�alho do arquivo emprestimo.bin, dois inteiros representando respectivamente o usuario e o livro,
//e duas strings representando as datas de emprestimo e devolucao e os respectivos endere�os das cabe�as das listas de livros, usuarios e emprestimos
//retorno: ponteiro para a nova cabe�a da lista de empr�stimos
EMPRESTIMO* emprestartxt(CABECALHO** cab, int codUsuario, int codLivro, char* emprestimo, char* devolucao, EMPRESTIMO* listaE);
//registra a devolu��o de um livro j� emprestado
//pr�-condi��o: existir uma lista de livros de usuarios e de emprestimo com itens
//p�s-condi��o: adiciona uma data de devolu��o ao livro especificado
//entrada: dois inteiros que representam respectivamente o c�digo do usu�rio e do livro e o endere�o da cabe�a da lista de empr�stimos
//retorno: nenhum
void devolver(int codUsuario, int codLivro, EMPRESTIMO** lista);
//imprime todos os dados de empr�stimo registrados
//pr�-condi��o: deve existir uma lista de empr�stimos n�o vazia
//p�s-condi��o: nenhuma
//entrada: endere�o para a cabe�a da lista de empr�stimos
//retorno: nenhum
void listarEmprestimos(EMPRESTIMO* lista);
//carrega para o programa os dados de um arquivo .txt 
//pr�-condi��o: deve existir um arquivo .txt na formata��o correta para leitura, 
//e as listas de livros, usuarios e emprestimos e o cabe�alho inicializados
//p�s-condi��o: aloca os arquivos na lista, cria um arquivo .bin e grava as informa��es nele
//entrada: string com o nome do arquivo .txt, endere�os das cabe�as das listas de livros, usuarios e emprestimos
void carregaArquivotxt(char* nomeArq, LIVRO** listaL, USUARIO** listaU, EMPRESTIMO** listaE, CABECALHO** cab1, CABECALHO** cab2, CABECALHO** cab3);
//carrega para o programa os dados de tres arquivos .bin
//pr�-condi��o: devem existir arquivos bin�rios correspondentes n�o vazios, e listas de livros, usuarios e emprestimos inicializadas
//p�s-condi��o: aloca os arquivos na lista
//entrada: endere�o das respectivas listas de livros, usuarios e emprestimos
//retorno: nenhum
//formato da entrada: 
//L;<codigo>;<titulo>;<autor>;<editora>;<edicao>;<ano>;<exemplares>; para livro
//U;<codigo>;<nome>; para usuario
//E;<codUsuario>;<codLivro>;<dataEmprestimo>;<dataDevolu��o>; para emprestimo
void carregaArquivobin(CABECALHO** cab1, CABECALHO** cab2, CABECALHO** cab3, LIVRO** listaL, USUARIO** listaU, EMPRESTIMO** listaE);
//fun��o que retorna data de hoje no formato ##/##/##
char* obterData();
//fun��o que libera toda a memoria alocada
void liberaMemoria(CABECALHO* cab1, CABECALHO* cab2, CABECALHO* cab3, LIVRO* lista1, USUARIO* lista2, EMPRESTIMO* lista3);
#endif