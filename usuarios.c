#include "biblioteca.h"

//inicializa uma lista vazia de usuarios
USUARIO* criaListaUsuarios()
{
	USUARIO* novaLista = (USUARIO*)malloc(sizeof(USUARIO));
	if (!novaLista)
		return NULL;
	novaLista->prox = NULL;
	return novaLista;
}
//função que grava no arquivo .bin
static void gravaBin(CABECALHO cab, USUARIO_BIN estrutura)
{
	FILE* bin = fopen("usuarios.bin", "r+b");
	if (!bin) {
		printf("erro ao abrir arquivo 'usuarios.bin'\n");
		return;
	}
	fseek(bin, 0, SEEK_SET);
	fwrite(&cab, sizeof(CABECALHO), 1, bin);
	fseek(bin, cab.cabeca, SEEK_SET);
	fwrite(&estrutura, sizeof(USUARIO_BIN), 1, bin);
	fclose(bin);
}
//coloca um novo usuario na lista, e grava no .bin
USUARIO* cadastrarUsuario(CABECALHO** cab, USUARIO* lista, int cod, char* nome)
{
	USUARIO* novoUsuario = (USUARIO*)malloc(sizeof(USUARIO));
	if (!novoUsuario)
		return NULL;
	novoUsuario->prox = lista;
	novoUsuario->arquivo.codigo = cod;
	novoUsuario->arquivo.prox = (*cab)->cabeca;
	strcpy(novoUsuario->arquivo.nome, nome);
	(*cab)->cabeca = (*cab)->topo;
	(*cab)->topo += sizeof(USUARIO);
	gravaBin(**cab, novoUsuario->arquivo);
	printf("...\n");
	return novoUsuario;
}
//função auxiliar que imprime um usuário
static void printUsuario(USUARIO_BIN dados)
{
	printf("----------\n");
	printf("Codigo: %d\nNome: %s\n", dados.codigo, dados.nome);
	printf("----------\n");
}
//imprime na tela todos os usuários
void listarUsuarios(USUARIO* cabeca)
{
	if (cabeca == NULL)
		return;
	if (vaziaU(cabeca))
		return;
	printUsuario(cabeca->arquivo);
	listarUsuarios(cabeca->prox);
}
void buscaUsuarioCod(USUARIO* lista, int cod)
{
	if (lista == NULL)
		return;
	if (vaziaU(lista))
		return;
	if (lista->arquivo.codigo == cod)
		printUsuario(lista->arquivo);
	buscaUsuarioCod(lista->prox, cod);
}
void buscaNome(USUARIO* lista, char* titulo)
{
	if (lista == NULL)
		return;
	if (vaziaU(lista))
		return;
	if (!strcmp(lista->arquivo.nome, titulo))
		printUsuario(lista->arquivo);
	buscaNome(lista->prox, titulo);
}
int totalUsuarios(USUARIO* lista)
{
	if (lista == NULL)
		return 0;
	if (vaziaU(lista))
		return 0;
	return 1 + totalUsuarios(lista->prox);
}