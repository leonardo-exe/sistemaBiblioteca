#include "biblioteca.h"

//função que inicializa um arquivo .bin com seu respectivo cabecalho
static void criaBin(char* nome, CABECALHO* cab)
{
	FILE* arc = fopen(nome, "wb");
	if (!arc) {
		printf("erro ao criar arquivo %s\n", nome);
		return;
	}
	fwrite(cab, sizeof(CABECALHO), 1, arc);
	fclose(arc);
}
//funcao que verifica se a lista é vazia
int vaziaL(LIVRO* lista)
{
	return (lista->prox == NULL);
}
//funcao que verifica se a lista é vazia
int vaziaU(USUARIO* lista)
{
	return (lista->prox == NULL);
}
//funcao que verifica se a lista é vazia
int vaziaE(EMPRESTIMO* lista)
{
	return (lista->prox == NULL);
}
//função que aloca e inicializa o cabeçalho, dependendo do parametro char recebido, 'l' para livros,
//'u' para usuarios e 'e' para emprestimos, caso nao seja possivel alocar, ou o parametro for algo nao esperado, 
//retornará NULL
void* criaCabecalho(char tipo, char bin)
{
	CABECALHO* cab = (CABECALHO*)malloc(sizeof(CABECALHO));
	if (cab) {
		cab->cabeca = -1;
			cab->topo = sizeof(CABECALHO);
	}
	char nome[20]; 
	if (tipo == 'L') {
		strcpy(nome, "livros.bin");
	}
	else if (tipo == 'U') {
		strcpy(nome, "usuarios.bin");
	}
	else if (tipo == 'E') {
		strcpy(nome, "emprestimos.bin");
	}
	else {
		strcpy(nome, "");
	}
	if (bin == 'N')
		criaBin(nome, cab);
	return cab;
}
//função auxiliar para ler strings ignorando espaços no comeco e no final
static void readString(char* str, FILE* arc, char tipo)
{
	if (tipo == 'L') {
		char aux[201];
		fscanf(arc, "%[^;]%*c", aux);
		int inicio = 0;
		while (isspace(aux[inicio]))
			inicio++;
		int fim = (int)strlen(aux) - 1;
		while (fim >= inicio && isspace(aux[fim]))
			fim--;
		int len = fim - inicio + 1;
		if (len > 0) {
			strncpy(str, aux + inicio, len);
			str[len] = '\0';
		}
		else {
			str[0] = '\0';
		}
	}
	if (tipo == 'U' || tipo == 'E') {
		char aux[201];
		fscanf(arc, "%[^\n]%*c", aux);
		int inicio = 0;
		while (isspace(aux[inicio]))
			inicio++;
		int fim = (int)strlen(aux) - 1;
		while (fim >= inicio && isspace(aux[fim]))
			fim--;
		int len = fim - inicio + 1;
		if (len > 0) {
			strncpy(str, aux + inicio, len);
			str[len] = '\0';
		}
		else {
			str[0] = '\0';
		}

	}
}
//formato da entrada: 
//L;<codigo>;<titulo>;<autor>;<editora>;<edicao>;<ano>;<exemplares>; para livro
//U;<codigo>;<nome>; para usuario
//E;<codUsuario>;<codLivro>;<dataEmprestimo>;<dataDevolução>; para emprestimo
void carregaArquivotxt(char* nomeArq, LIVRO** listaL, USUARIO** listaU, EMPRESTIMO** listaE, CABECALHO** cab1, CABECALHO** cab2, CABECALHO** cab3)
{
	FILE* arquivo = fopen(nomeArq, "r");
	if (!arquivo)
	{
		printf("Nao foi possivel abrir o arquivo %s\n", nomeArq);
		return;
	}
	char tipo;
	while (fscanf(arquivo, "%c%*c", &tipo) != EOF)
	{
		if (tipo == 'L')
		{
			INFO informacoes = {0};
			fscanf(arquivo, "%d%*c", &informacoes.codigo);
			readString(informacoes.titulo, arquivo, tipo);
			readString(informacoes.autor, arquivo, tipo);
			readString(informacoes.editora, arquivo, tipo);
			fscanf(arquivo, "%d%*c%d%*c%d%*c", &informacoes.edicao, &informacoes.ano, &informacoes.qtdExemplares);
			*listaL = cadastrarLivro(&(*cab1), *listaL, informacoes);
		}
		if (tipo == 'U')
		{
			int codigo;
			char nome[51];
			fscanf(arquivo, "%d%*c", &codigo);
			readString(nome, arquivo, tipo);
			*listaU = cadastrarUsuario(&(*cab2), *listaU, codigo, nome);
		}
		if (tipo == 'E')
		{
			int codU, codL;
			char emprestimo[11], devolucao[11];
			fscanf(arquivo, "%d%*c%d%*c", &codU, &codL);
			readString(emprestimo, arquivo, 'L');
			readString(devolucao, arquivo, tipo);
			*listaE = emprestartxt(&(*cab3), codU, codL, emprestimo, devolucao, *listaE);
		}
	}
	fclose(arquivo);
	printf("Arquivo texto carregado para o programa\n");
}//funções que cadastram sem gravar no .bin
static LIVRO* cadastrarLivrobin(CABECALHO* cab, LIVRO* lista, INFO info)
{
	LIVRO* novoLivro = (LIVRO*)malloc(sizeof(LIVRO));
	if (!novoLivro)
		return NULL;
	novoLivro->arquivo.informacoes = info;
	novoLivro->arquivo.prox = cab->cabeca;
	novoLivro->prox = lista;
	return novoLivro;
}
static USUARIO* cadastrarUsuariobin(CABECALHO* cab, USUARIO* lista, int cod, char* nome)
{
	USUARIO* novoUsuario = (USUARIO*)malloc(sizeof(USUARIO));
	if (!novoUsuario)
		return NULL;
	novoUsuario->prox = lista;
	novoUsuario->arquivo.codigo = cod;
	novoUsuario->arquivo.prox = cab->cabeca;
	strcpy(novoUsuario->arquivo.nome, nome);
	return novoUsuario;
}
static EMPRESTIMO* emprestarbin(CABECALHO* cab, EMPRESTIMO_BIN dados, EMPRESTIMO* listaE)
{
	EMPRESTIMO* novoEmprestimo = (EMPRESTIMO*)malloc(sizeof(EMPRESTIMO));
	if (!novoEmprestimo)
		return NULL;
	novoEmprestimo->prox = listaE;
	novoEmprestimo->arquivo.codLivro = dados.codLivro;
	novoEmprestimo->arquivo.codUsuario = dados.codUsuario;
	if (dados.dataDevolucao)
		strcpy(novoEmprestimo->arquivo.dataDevolucao, dados.dataDevolucao);
	else
		strcpy(novoEmprestimo->arquivo.dataDevolucao, "-");
	char* data = obterData();
	strcpy(novoEmprestimo->arquivo.dataEmprestimo, data);
	free(data);
	return novoEmprestimo;
}
//carrega os dados de um arquivo binario
void carregaArquivobin(CABECALHO** cab1, CABECALHO** cab2, CABECALHO** cab3, LIVRO** listaL, USUARIO** listaU, EMPRESTIMO** listaE)
{
	FILE* arquivo1 = fopen("livros.bin", "rb");
	FILE* arquivo2 = fopen("usuarios.bin", "rb");
	FILE* arquivo3 = fopen("emprestimos.bin", "rb");
	if (!arquivo1)
	{
		printf("Erro ao abrir livros.bin\n");
		fclose(arquivo2);
		fclose(arquivo3);
		return;
	}
	if (!arquivo2)
	{
		printf("Erro ao abrir usuarios.bin\n");
		fclose(arquivo1);
		fclose(arquivo3);
		return;
	}
	if (!arquivo3)
	{
		printf("Erro ao abrir emprestimos.bin\n");
		fclose(arquivo1);
		fclose(arquivo2);
		return;
	}
	fseek(arquivo1, 0, 0);
	fseek(arquivo2, 0, 0);
	fseek(arquivo3, 0, 0);
	fread(*cab1, sizeof(CABECALHO), 1, arquivo1);
	fread(*cab2, sizeof(CABECALHO), 1, arquivo2);
	fread(*cab3, sizeof(CABECALHO), 1, arquivo3);
	LIVRO_BIN aux1;
	USUARIO_BIN aux2;
	EMPRESTIMO_BIN aux3;
	while (fread(&aux1, sizeof(LIVRO_BIN), 1, arquivo1))
	{
		*listaL = cadastrarLivrobin(*cab1, *listaL, aux1.informacoes);
	}
	while (fread(&aux2, sizeof(USUARIO_BIN), 1, arquivo2))
	{
		*listaU = cadastrarUsuariobin(*cab2, *listaU, aux2.codigo, aux2.nome);
	}
	while (fread(&aux3, sizeof(EMPRESTIMO_BIN), 1, arquivo3))
	{
		*listaE = emprestarbin(*cab3, aux3, *listaE);
	}
	printf("Arquivos binarios carregados para o programa!\n");
}
void liberaMemoria(CABECALHO* cab1, CABECALHO* cab2, CABECALHO* cab3, LIVRO* lista1, USUARIO* lista2, EMPRESTIMO* lista3)
{
	free(cab1);
	free(cab2);
	free(cab3);
	if (vaziaL(lista1))
		free(lista1);
	else {
		LIVRO* aux1 = lista1->prox;
		while (aux1 != NULL)
		{
			free(lista1);
			lista1 = aux1;
			aux1 = aux1->prox;
		}
	}
	if (vaziaU(lista2))
		free(lista2);
	else {
		USUARIO* aux2 = lista2->prox;
		while (aux2 != NULL)
		{
			free(lista2);
			lista2 = aux2;
			aux2 = aux2->prox;
		}
	}
	if (vaziaE(lista3))
		free(lista3);
	else {
		EMPRESTIMO* aux3 = lista3->prox;
		while (aux3 != NULL)
		{
			free(lista3);
			lista3 = aux3;
			aux3 = aux3->prox;
		}
	}
	printf("Memoria liberada!\n");
}
void gravabin(CABECALHO* cab, void* lista, char* arquivo)
{
	FILE* arq = fopen(arquivo, "wb");
	if (!arq) return;
	fseek(arq, 0, SEEK_SET);
	fwrite(cab, sizeof(CABECALHO), 1, arq);
	if (arquivo[0] == 'l') 
	{
		LIVRO* aux = lista;
		while (aux->prox != NULL)
		{
			fwrite(&aux->arquivo, sizeof(LIVRO_BIN), 1, arq);
			aux = aux->prox;
		}
	}
	if (arquivo[0] == 'u') 
	{
		USUARIO* aux = lista;
		while (aux->prox != NULL)
		{
			fwrite(&aux->arquivo, sizeof(USUARIO_BIN), 1, arq);
			aux = aux->prox;
		}
	}
	if (arquivo[0] == 'e')
	{
		EMPRESTIMO* aux = lista;
		while (aux->prox != NULL)
		{
			fwrite(&aux->arquivo, sizeof(EMPRESTIMO_BIN), 1, arq);
			aux = aux->prox;
		}
	}

}
