#include "biblioteca.h"

//inicializa uma lista vazia que poderá ser incrementada (esse elemento vazio será sempre a cauda da lista)
LIVRO* criaListaLivros()
{
	LIVRO* novaLista = (LIVRO*)malloc(sizeof(LIVRO));
	if (!novaLista) 
		return NULL;
	novaLista->prox = NULL;
	return novaLista;
}
//função que grava no arquivo .bin
static void gravaBin(CABECALHO cab, LIVRO_BIN estrutura)
{
	FILE* bin = fopen("livros.bin", "r+b");
	if (!bin) {
		printf("erro ao abrir arquivo 'livros.bin'\n");
		return;
	}
	fseek(bin, 0, SEEK_SET);
	fwrite(&cab, sizeof(CABECALHO), 1, bin);
	fseek(bin, cab.cabeca, SEEK_SET);
	fwrite(&estrutura, sizeof(LIVRO_BIN), 1, bin);
	fclose(bin);
}
//adciona elementos na cabeça da lista, atualiza o cabeçalho, e grava no arquivo .bin
LIVRO* cadastrarLivro(CABECALHO** cab, LIVRO* lista, INFO info)
{
	LIVRO* novoLivro = (LIVRO*)malloc(sizeof(LIVRO));
	if (!novoLivro) 
		return NULL;
	novoLivro->arquivo.informacoes = info;
	novoLivro->arquivo.prox = (*cab)->cabeca;
	novoLivro->prox = lista;
	(*cab)->cabeca = (*cab)->topo;
	(*cab)->topo += sizeof(LIVRO_BIN);
	//gravaBin(**cab, novoLivro->arquivo);
	printf("...\n");
	return novoLivro;
}
//funcao que imprime o livro, separada apenas para melhor organizacao e reaproveitamento
static void printLivro(LIVRO livro)
{
	if (livro.arquivo.informacoes.qtdExemplares == -1)
		return;
	printf("----------\n");
	printf("Codigo: %d\nTitulo: %s\nAutor: %s\nEditora: %s\nEdicao: %d\nAno: %d\nExemplares: %d\n",
		livro.arquivo.informacoes.codigo,
		livro.arquivo.informacoes.titulo,
		livro.arquivo.informacoes.autor,
		livro.arquivo.informacoes.editora,
		livro.arquivo.informacoes.edicao,
		livro.arquivo.informacoes.ano,
		livro.arquivo.informacoes.qtdExemplares);
	printf("----------\n");

}
//imprime na tela todos os livros da lista
void listarLivros(LIVRO* cabeca) {
	if (cabeca == NULL)
		return;
	if (vaziaL(cabeca)) 
		return;
	printLivro(*cabeca);
	listarLivros(cabeca->prox);
}
//imprime os dados do livro com o respectivo codigo
void buscaLivroCod(LIVRO* lista, int cod)
{
	if (lista == NULL)
		return;
	if (vaziaL(lista))
		return;
	if (lista->arquivo.informacoes.codigo == cod)
		printLivro(*lista);
	buscaLivroCod(lista->prox, cod);
}
//imprime os dados do livro com o respectivo titulo
void buscaTit(LIVRO* lista, char* titulo)
{
	if (lista == NULL)
		return;
	if (vaziaL(lista))
		return;
	if (!strcmp(lista->arquivo.informacoes.titulo, titulo))
		printLivro(*lista);
	buscaTit(lista->prox, titulo);
}
//retorna a quantidade de livros cadastrados
int totalLivros(LIVRO* lista)
{
	if (lista == NULL)
		return 0;
	if (vaziaL(lista))
		return 0;
	return 1 + totalLivros(lista->prox);
}
int livrosRepetidos(LIVRO* lista, char* titulo, char* autor, int edicao, int ano, int quantia)
{
	if (lista == NULL || vaziaL(lista))
		return 0;
	if (!strcmp(lista->arquivo.informacoes.titulo, titulo) && !strcmp(lista->arquivo.informacoes.autor, autor) && lista->arquivo.informacoes.edicao == edicao && lista->arquivo.informacoes.ano == ano)
	{
		lista->arquivo.informacoes.qtdExemplares += quantia;
		return 1;
	}
	return livrosRepetidos(lista->prox, titulo, autor, edicao, ano, quantia);
}