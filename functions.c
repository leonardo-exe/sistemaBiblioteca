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
		if (tipo == ' ' || tipo == '\n')
			continue;
		if (tipo == 'L')
		{
			INFO informacoes = {0};
			fscanf(arquivo, "%d%*c", &informacoes.codigo);
			readString(informacoes.titulo, arquivo, tipo);
			readString(informacoes.autor, arquivo, tipo);
			readString(informacoes.editora, arquivo, tipo);
			fscanf(arquivo, "%d%*c%d%*c%d%*c", &informacoes.edicao, &informacoes.ano, &informacoes.qtdExemplares);
			if (!livrosRepetidos(*listaL, informacoes.titulo, informacoes.autor, informacoes.edicao, informacoes.ano, informacoes.qtdExemplares))
				*listaL = cadastrarLivro(cab1, *listaL, informacoes);
			else 
				gravabin(*cab1, *listaL, "livros.bin");
		}
		if (tipo == 'U')
		{
			int codigo;
			char nome[51];
			fscanf(arquivo, "%d%*c", &codigo);
			readString(nome, arquivo, tipo);
			if (!vaziaU(*listaU) || !usuariosRepetidos(*listaU, nome))
				*listaU = cadastrarUsuario(cab2, *listaU, codigo, nome);
		}
		if (tipo == 'E')
		{
			int codU, codL;
			char emprestimo[11], devolucao[11];
			fscanf(arquivo, "%d%*c%d%*c", &codU, &codL);
			readString(emprestimo, arquivo, 'L');
			readString(devolucao, arquivo, tipo);
			*listaE = emprestartxt(cab3, codU, codL, emprestimo, devolucao, *listaE);
		}
	}
	fclose(arquivo);
	printf("Arquivo texto carregado para o programa\n");
}//funções que cadastram sem gravar no .bin
static LIVRO* crialivroBin(LIVRO* lista, LIVRO_BIN inf)
{
	LIVRO* novoLivro = (LIVRO*)malloc(sizeof(LIVRO));
	if (!novoLivro)
		return NULL;
	novoLivro->prox = lista;
	novoLivro->arquivo = inf;
	return novoLivro;
}
static USUARIO* criausuarioBin(USUARIO* lista, USUARIO_BIN inf)
{
	USUARIO* novoUsuario = (USUARIO*)malloc(sizeof(USUARIO));
	if (!novoUsuario)
		return NULL;
	novoUsuario->prox = lista;
	novoUsuario->arquivo = inf;
	return novoUsuario;
}
static EMPRESTIMO* criaemprestimoBin(EMPRESTIMO* lista, EMPRESTIMO_BIN inf)
{
	EMPRESTIMO* novoEmprestimo = (EMPRESTIMO*)malloc(sizeof(EMPRESTIMO));
	if (!novoEmprestimo)
		return NULL;
	novoEmprestimo->prox = lista;
	novoEmprestimo->arquivo = inf;
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
	fseek(arquivo1, 0, SEEK_SET);
	fread(*cab1, sizeof(CABECALHO), 1, arquivo1);
	fseek(arquivo2, 0, SEEK_SET);
	fread(*cab2, sizeof(CABECALHO), 1, arquivo2);
	fseek(arquivo3, 0, SEEK_SET);
	fread(*cab3, sizeof(CABECALHO), 1, arquivo3);
	
	fseek(arquivo1, (*cab1)->cabeca, SEEK_SET);
	LIVRO_BIN aux1;
	while (fread(&aux1, sizeof(LIVRO_BIN), 1, arquivo1))
	{
		*listaL = crialivroBin(*listaL, aux1);
		if (aux1.prox == -1) break;
		fseek(arquivo1, aux1.prox, SEEK_SET);
	}

	fseek(arquivo2, (*cab2)->cabeca, SEEK_SET);
	USUARIO_BIN aux2;
	while (fread(&aux2, sizeof(USUARIO_BIN), 1, arquivo2))
	{
		*listaU = criausuarioBin(*listaU, aux2);
		if (aux2.prox == -1) break;
		fseek(arquivo2, aux2.prox, SEEK_SET);
	}

	fseek(arquivo3, (*cab3)->cabeca, SEEK_SET);
	EMPRESTIMO_BIN aux3;
	while (fread(&aux3, sizeof(EMPRESTIMO_BIN), 1, arquivo3))
	{
		*listaE = criaemprestimoBin(*listaE, aux3);
		if (aux3.prox == -1) break;
		fseek(arquivo3, aux3.prox, SEEK_SET);
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
	if (!arq) 
	{
		printf("nao foi possivel abrir arquivo %s\n", arquivo);
		return;
	}
	fseek(arq, 0, SEEK_SET);
	fwrite(cab, sizeof(CABECALHO), 1, arq);
	if (arquivo[0] == 'l') 
	{
		LIVRO* aux = lista;
		while (aux->prox != NULL)
		{
			fwrite(&aux->arquivo, sizeof(LIVRO_BIN), 1, arq);
			fseek(arq, aux->arquivo.prox, SEEK_SET);
			aux = aux->prox;
		}
	}
	if (arquivo[0] == 'u') 
	{
		USUARIO* aux = lista;
		while (aux->prox != NULL)
		{
			fwrite(&aux->arquivo, sizeof(USUARIO_BIN), 1, arq);
			fseek(arq, aux->arquivo.prox, SEEK_SET);
			aux = aux->prox;
		}
	}
	if (arquivo[0] == 'e')
	{
		EMPRESTIMO* aux = lista;
		while (aux->prox != NULL)
		{
			fwrite(&aux->arquivo, sizeof(EMPRESTIMO_BIN), 1, arq);
			fseek(arq, aux->arquivo.prox, SEEK_SET);
			aux = aux->prox;
		}
	}

}
