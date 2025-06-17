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
//coloca um novo usuario na lista, e grava no .bin
USUARIO* cadastrarUsuario(USUARIO* lista, int cod, char* nome)
{
	USUARIO* novoUsuario = (USUARIO*)malloc(sizeof(USUARIO));
	if (!novoUsuario)
		return NULL;
	novoUsuario->prox = lista;
	novoUsuario->arquivo.codigo = cod;
	strcpy(novoUsuario->arquivo.nome, nome);
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
int usuariosRepetidos(USUARIO* lista, char* nome)
{
	if (lista == NULL)
		return 0;
	if (vaziaU(lista))
		return 0;
	if (!strcmp(lista->arquivo.nome, nome))
		return 1;
	return usuariosRepetidos(lista->prox, nome);
}