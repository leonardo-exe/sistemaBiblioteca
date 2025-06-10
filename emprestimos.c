#include "biblioteca.h"

//inicializa lista vazia
EMPRESTIMO* criarListaEmprestimo()
{
	EMPRESTIMO* novaLista = (EMPRESTIMO*)malloc(sizeof(EMPRESTIMO));
	if (!novaLista)
		return NULL;
	novaLista->prox = NULL;
	return novaLista;
}
char* obterData() {
    time_t agora;
    struct tm* infoTempo;
    char* buffer = (char*)malloc(9); 
    if (buffer == NULL) {
        return NULL; 
    }
    time(&agora);
    infoTempo = localtime(&agora);
    strftime(buffer, 9, "%d/%m/%y", infoTempo);
    return buffer;
}
//função que grava no arquivo .bin
static void gravaBin(CABECALHO cab, EMPRESTIMO_BIN estrutura)
{
	FILE* bin = fopen("emprestimos.bin", "r+b");
	if (!bin) {
		printf("erro ao abrir arquivo 'emprestimos.bin'\n");
		return;
	}
	fseek(bin, 0, SEEK_SET);
	fwrite(&cab, sizeof(CABECALHO), 1, bin);
	fseek(bin, cab.cabeca, SEEK_SET);
	fwrite(&estrutura, sizeof(EMPRESTIMO_BIN), 1, bin);
	fclose(bin);
}
static int usuarioExiste(USUARIO* lista, int codigo)
{
	if (lista == NULL || vaziaU(lista))
	{
		printf("nao eh possivel registrar emprestimo para um usuario nao cadastrado\n");
		return 0;
	}
	if (lista->arquivo.codigo == codigo)
		return 1;
	return usuarioExiste(lista->prox, codigo);
}
static int livroExiste(LIVRO* lista, int codigo)
{
	if (lista == NULL || vaziaL(lista))
	{
		printf("nao eh possivel registrar emprestimo de um livro nao cadastrado\n");
		return 0;
	}
	if (lista->arquivo.informacoes.codigo == codigo)
		return 1;
	return livroExiste(lista->prox, codigo);
}
//registra um emprestimo de livro
EMPRESTIMO* emprestar(CABECALHO** cab, int codUsuario, int codLivro, EMPRESTIMO* listaE, USUARIO* listaU, LIVRO* listaL)
{
	if (!(usuarioExiste(listaU, codUsuario) && livroExiste(listaL, codLivro)))
		return NULL;
	EMPRESTIMO* novoEmprestimo = (EMPRESTIMO*)malloc(sizeof(EMPRESTIMO));
	if (!novoEmprestimo)
		return NULL;
	novoEmprestimo->prox = listaE;
	novoEmprestimo->arquivo.codLivro = codLivro;
	novoEmprestimo->arquivo.codUsuario = codUsuario;
	novoEmprestimo->arquivo.prox = (*cab)->cabeca;
	strcpy(novoEmprestimo->arquivo.dataDevolucao, "-");
	char* data = obterData();
	strcpy(novoEmprestimo->arquivo.dataEmprestimo, data);
	free(data);
	(*cab)->cabeca = (*cab)->topo;
	(*cab)->topo += sizeof(EMPRESTIMO);
	gravaBin(**cab, novoEmprestimo->arquivo);
	printf("emprestimo cadastrado!\n");
	return novoEmprestimo;
}
//registra um emprestimo de livro recebido por txt
EMPRESTIMO* emprestartxt(CABECALHO** cab, int codUsuario, int codLivro, char* emprestimo, char* devolucao, EMPRESTIMO* listaE)
{
	EMPRESTIMO* novoEmprestimo = (EMPRESTIMO*)malloc(sizeof(EMPRESTIMO));
	if (!novoEmprestimo)
		return NULL;
	novoEmprestimo->prox = listaE;
	novoEmprestimo->arquivo.codLivro = codLivro;
	novoEmprestimo->arquivo.codUsuario = codUsuario;
	novoEmprestimo->arquivo.prox = (*cab)->cabeca;
	strcpy(novoEmprestimo->arquivo.dataDevolucao, devolucao);
	strcpy(novoEmprestimo->arquivo.dataEmprestimo, emprestimo);
	(*cab)->cabeca = (*cab)->topo;
	(*cab)->topo += sizeof(EMPRESTIMO);
	gravaBin(**cab, novoEmprestimo->arquivo);
	printf("...\n");
	return novoEmprestimo;
}
//registra data de devolução
void devolver(int codUsuario, int codLivro, EMPRESTIMO** listaE, CABECALHO* cab)
{
	if (*listaE == NULL || vaziaE(*listaE))
	{
		printf("nao existe registro de empretimo para esta pessoa ou deste livro\n");
		return;
	}
	if ((*listaE)->arquivo.codLivro == codLivro && (*listaE)->arquivo.codUsuario == codUsuario) {
		char* data = obterData();
		strcpy((*listaE)->arquivo.dataDevolucao, data);
		free(data);
		printf("Devolucao registrada!\n");
		gravabin(cab, *listaE, "emprestimos.bin");
		return;
	}
	devolver(codUsuario, codLivro, &(*listaE)->prox, cab);
}
//imprime todos os empréstimos na tela
void listarEmprestimos(EMPRESTIMO* lista)
{
	if (lista == NULL)
		return;
	if (vaziaE(lista))
		return;
	printf("----------\n");
	printf("Codigo do livro: %d\nCodigo do usuario: %d\nData emprestimo: %s\nData devolucao: %s\n", 
		lista->arquivo.codLivro, lista->arquivo.codUsuario, lista->arquivo.dataEmprestimo, lista->arquivo.dataDevolucao);
	printf("----------\n");
	listarEmprestimos(lista->prox);
}
