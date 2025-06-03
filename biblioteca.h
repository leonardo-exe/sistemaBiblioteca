#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
//struct que guarda as informações de um livro
typedef struct {
	int codigo;
	char titulo[151];
	char autor[201];
	char editora[51];
	int edicao;
	int ano;
	int qtdExemplares;
}INFO;
//cabecalho dos arquivos binários, guarda a cabeça e o topo da lista 
typedef struct {
	int cabeca;
	int topo;
}CABECALHO;
//struct que será armazenada no arquivo binário que conterá a lista de livros, 
//possui as informações do livro e o numero de registro do proximo da lista no arquivo 
typedef struct {
	INFO informacoes;
	int prox;
}LIVRO_BIN;
//struct nó usada para manter a lista dinâmica na memória, 
//possui as informações do livro e o endereço do próximo elemento na memória durante a execução do programa
typedef struct noLivro {
	LIVRO_BIN arquivo;
	struct noLivro* prox;
}LIVRO;
//struct que será armazenada no arquivo binário que conterá a lista de usuários,
//possui as informações do usuário e o numero de registro do proximo da lista no arquivo
typedef struct {
	int codigo;
	char nome[51];
	int prox;
}USUARIO_BIN;
//struct nó usada para manter a lista dinâmica na memória, 
//possui as informações do usuario e o endereço do próximo elemento na memória durante a execução do programa
typedef struct noUsuario {
	USUARIO_BIN arquivo;
	struct noUsuario* prox;
}USUARIO;
//struct que será armazenada no arquivo binário que conterá a lista de empréstimos,
//possui as informações de empréstimo e o numero de registro do proximo da lista no arquivo
typedef struct {
	int codUsuario;
	int codLivro;
	char dataEmprestimo[11];
	char dataDevolucao[11];
	int prox;
}EMPRESTIMO_BIN;
//struct nó usada para manter a lista dinâmica na memória, 
//possui as informações do empréstimo e o endereço do próximo elemento na memória durante a execução do programa
typedef struct noEmpresta {
	EMPRESTIMO_BIN arquivo;
	struct noEmpresta* prox;
}EMPRESTIMO;
//verificam se a lista é vazia
//pré-condição: nenhuma
//pós-condição: nenhuma
//entrada: recebe um ponteiro para a lista
//retorno: retorna 1 caso a lista seja vazia, e 0 para os outros casos
int vaziaL(LIVRO* lista);
int vaziaU(USUARIO* lista);
int vaziaE(EMPRESTIMO* lista);
//cria uma estrutura cabecalho para o arquivo binario
//pré-condição: nenhuma
//pós-condição: cabecalho é alocado na memória e gravado no arquivo binário correspondente
//entrada: uma letra minuscula representando qual arquivo estará sendo inicializado
//retorno: um ponteiro sem tipo para a estrutura cabecalho correspondente 
void* criaCabecalho(char tipo);
//cria uma lista vazia
//pré-condição: nenhuma
//pós-condição: lista é alocada na memória
//entrada: nenhuma
//retorno: ponteiro para uma lista sem elementos
LIVRO* criaListaLivros();
//insere um novo livro na lista
//pré-condição: devem ter sido inicializados uma lista e um cabeçalho correspondentes
//pós-condição: o elemento é adcionado, se tornando a nova cabeça da lista
//entrada: endereço para a estrutura de cabeçalho do respectivo arquivo binário onde a estrutura será gravada,
//endereço da estrutura cabeça de uma lista inicializada e uma estrutura do tipo INFO que guarda as especificações do livro
//retorno: endereço da estrutura adicionada e que representa a nova cabeça da lista
LIVRO* cadastrarLivro(CABECALHO** cab, LIVRO* lista, INFO info);
//imprime as informações de todos os livros da lista
//pré-condição: a lista não pode ser vazia
//pós-condição: nenhuma
//entrada: endereço da cabeça da lista
//retorno: nenhum
void listarLivros(LIVRO* cabeca);
//dado um codigo de livro, busca o livro na lista e imprime os dados correspondentes na tela
//pré-condição: a lista deve existir e conter itens
//pós-condição: nenhuma
//entrada: endereço da cabeça da lista e o número inteiro que representa o livro
//retorno: nenhum
void buscaLivroCod(LIVRO* lista, int cod);
//dado um titulo de livro, busca o livro na lista e imprime os dados correspondentes na tela
//pré-condição: a lista deve existir e conter itens
//pós-condição: nenhuma
//entrada: endereço da cabeça da lista e a string do titulo que representa o livro
//retorno: nenhum
void buscaTit(LIVRO* lista, char* titulo);
//retorna o total de livros diferentes na lista
//pré-condição: a lista deve existir
//pós-condição: nenhuma
//entrada: endereço da cabeça da lista
//retorno: inteiro com a quantidade de livros na lista
int totalLivros(LIVRO* lista);
//cria uma lista vazia
//pré-condição: nenhuma
//pós-condição: lista é alocada na memória
//entrada: nenhuma
//retorno: ponteiro para uma lista sem elementos
USUARIO* criaListaUsuarios();
//insere um novo livro na lista
//pré-condição: devem ter sido inicializados uma lista e um cabeçalho correspondentes
//pós-condição: o elemento é adcionado, se tornando a nova cabeça da lista
//entrada: endereço para a estrutura de cabeçalho do respectivo arquivo binário onde a estrutura será gravada, 
//ponteiro para a cabeça da lista, inteiro único que representa o usuario e string que representa seu nome
//retorno: endereço da estrutura adicionada e que representa a nova cabeça da lista
USUARIO* cadastrarUsuario(CABECALHO** cab, USUARIO* lista, int cod, char* nome);
//imprime as informações de todos os usuarios da lista
//pré-condição: a lista não pode ser vazia
//pós-condição: nenhuma
//entrada: endereço da cabeça da lista
//retorno: nenhum
void listarUsuarios(USUARIO* cabeca);
//dado um codigo de usuario, busca o usuario na lista e imprime os dados correspondentes na tela
//pré-condição: a lista deve existir e conter itens
//pós-condição: nenhuma
//entrada: endereço da cabeça da lista e o número inteiro que representa o usuario
//retorno: nenhum
void buscaUsuarioCod(USUARIO* lista, int cod);
//dado um nome de usuario, busca o usuario na lista e imprime os dados correspondentes na tela
//pré-condição: a lista deve existir e conter itens
//pós-condição: nenhuma
//entrada: endereço da cabeça da lista e a string que representa o nome do usuario
//retorno: nenhum
void buscaNome(USUARIO* lista, char* titulo);
//retorna o total de usuario na lista
//pré-condição: a lista deve existir
//pós-condição: nenhuma
//entrada: endereço da cabeça da lista
//retorno: inteiro com a quantidade de usuarios na lista
int totalUsuarios(USUARIO* lista);
//cria uma lista vazia
//pré-condição: nenhuma
//pós-condição: lista é alocada na memória
//entrada: nenhuma
//retorno: ponteiro para uma lista sem elementos
EMPRESTIMO* criarListaEmprestimo();
//registra um empréstimo na lista, salva o usuario o livro e a data do emprestimo
//pré-condição: existir uma lista de livros e de usuários com itens e uma de emprestimo inicializada
//pós-condição: é adicionado um empréstimo na cabeça da lista
//entrada: endereço da estrutura cabeçalho do arquivo emprestimo.bin, dois inteiros representando respectivamente o usuario e o livro,
//e os respectivos endereços das cabeças das listas de livros, usuarios e emprestimos
//retorno: ponteiro para a nova cabeça da lista de empréstimos
EMPRESTIMO* emprestar(CABECALHO** cab, int codUsuario, int codLivro, EMPRESTIMO* listaE);
//registra um empréstimo na lista, recebido de registro em um arquivo txt
//pré-condição: existir uma lista de livros e de usuários com itens e uma de emprestimo inicializada
//pós-condição: é adicionado um empréstimo na cabeça da lista
//entrada: endereço da estrutura cabeçalho do arquivo emprestimo.bin, dois inteiros representando respectivamente o usuario e o livro,
//e duas strings representando as datas de emprestimo e devolucao e os respectivos endereços das cabeças das listas de livros, usuarios e emprestimos
//retorno: ponteiro para a nova cabeça da lista de empréstimos
EMPRESTIMO* emprestartxt(CABECALHO** cab, int codUsuario, int codLivro, char* emprestimo, char* devolucao, EMPRESTIMO* listaE);
//registra a devolução de um livro já emprestado
//pré-condição: existir uma lista de livros de usuarios e de emprestimo com itens
//pós-condição: adiciona uma data de devolução ao livro especificado
//entrada: dois inteiros que representam respectivamente o código do usuário e do livro e o endereço da cabeça da lista de empréstimos
//retorno: nenhum
void devolver(int codUsuario, int codLivro, EMPRESTIMO** lista);
//imprime todos os dados de empréstimo registrados
//pré-condição: deve existir uma lista de empréstimos não vazia
//pós-condição: nenhuma
//entrada: endereço para a cabeça da lista de empréstimos
//retorno: nenhum
void listarEmprestimos(EMPRESTIMO* lista);
//carrega para o programa os dados de um arquivo .txt 
//pré-condição: deve existir um arquivo .txt na formatação correta para leitura, 
//e as listas de livros, usuarios e emprestimos e o cabeçalho inicializados
//pós-condição: aloca os arquivos na lista, cria um arquivo .bin e grava as informações nele
//entrada: string com o nome do arquivo .txt, endereços das cabeças das listas de livros, usuarios e emprestimos
void carregaArquivotxt(char* nomeArq, LIVRO** listaL, USUARIO** listaU, EMPRESTIMO** listaE, CABECALHO** cab1, CABECALHO** cab2, CABECALHO** cab3);
//carrega para o programa os dados de tres arquivos .bin
//pré-condição: devem existir arquivos binários correspondentes não vazios, e listas de livros, usuarios e emprestimos inicializadas
//pós-condição: aloca os arquivos na lista
//entrada: endereço das respectivas listas de livros, usuarios e emprestimos
//retorno: nenhum
//formato da entrada: 
//L;<codigo>;<titulo>;<autor>;<editora>;<edicao>;<ano>;<exemplares>; para livro
//U;<codigo>;<nome>; para usuario
//E;<codUsuario>;<codLivro>;<dataEmprestimo>;<dataDevolução>; para emprestimo
void carregaArquivobin(CABECALHO** cab1, CABECALHO** cab2, CABECALHO** cab3, LIVRO** listaL, USUARIO** listaU, EMPRESTIMO** listaE);
//função que retorna data de hoje no formato ##/##/##
char* obterData();
//função que libera toda a memoria alocada
void liberaMemoria(CABECALHO* cab1, CABECALHO* cab2, CABECALHO* cab3, LIVRO* lista1, USUARIO* lista2, EMPRESTIMO* lista3);
#endif