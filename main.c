#include "biblioteca.h"  

int main()  
{
	printf("-----BIBLIOTECA-----\n");
	int n = 1;
	while (n)
	{
		printf("0-encerrar programa\n1-carregar arquivos binarios\n2-carregar arquivos texto\n3-nova lista\n");
		scanf("%d", &n);
		if (n)
		{
			CABECALHO* cabL = n == 1 ? criaCabecalho('L', 'S') : criaCabecalho('L', 'N'),
				* cabU = n == 1 ? criaCabecalho('U', 'S') : criaCabecalho('U', 'N'),
				* cabE = n == 1 ? criaCabecalho('E', 'S') : criaCabecalho('E', 'N');
			LIVRO* listaLivros = criaListaLivros();
			USUARIO* listaUsuarios = criaListaUsuarios();
			EMPRESTIMO* listaEmprestimo = criarListaEmprestimo();
			if (!n) break;
			if (n == 1)
				carregaArquivobin(&cabL, &cabU, &cabE, &listaLivros, &listaUsuarios, &listaEmprestimo);
			if (n == 2)
			{
				printf("Digite o nome do arquivo.txt\n");
				char nomeArq[20];
				scanf("%s", nomeArq);
				carregaArquivotxt(nomeArq, &listaLivros, &listaUsuarios, &listaEmprestimo, &cabL, &cabU, &cabE);
			}
			do
			{
				printf("0-encerrar programa\n1-listar livros\n2-cadastrar livro\n3-listar usuarios\n4-cadastrar usuarios\n5-listar emprestimos\n6-emprestar livro\n7-devolver livro\n");
				scanf("%d", &n);
				switch (n)
				{
				case 0: break;
				case 1:
				{
					printf("1-todos os livros\n2-buscar com codigo\n3-buscar com titulo\n4-total de livros\n");
					int num;
					scanf("%d", &num);
					switch (num)
					{
					case 1: listarLivros(listaLivros); break;
					case 2:
					{
						printf("Digite o codigo do livro:\n");
						scanf("%d", &num);
						buscaLivroCod(listaLivros, num);
						break;
					}
					case 3:
					{
						printf("Digite o titulo do livro:\n");
						char tit[151];
						scanf(" %[^\n]%*c", tit);
						buscaTit(listaLivros, tit);
						break;
					}
					case 4: printf("Total de livros = %d\n", totalLivros(listaLivros)); break;
					default: printf("Digite um numero valido!!!\n");
					}
					break;
				}
				case 2:
				{
					INFO livro;
					printf("Digite um codigo para o novo livro:\n");
					scanf("%d", &livro.codigo);
					printf("Digite o titulo do livro:\n");
					scanf(" %[^\n]%*c", livro.titulo);
					printf("Digite o nome do autor do livro:\n");
					scanf(" %[^\n]%*c", livro.autor);
					printf("Digite o nome da editora do livro:\n");
					scanf(" %[^\n]%*c", livro.editora);
					printf("Digite o numero da edicao do livro\n");
					scanf("%d", &livro.edicao);
					printf("Digite o ano de publicacao:\n");
					scanf("%d", &livro.ano);
					printf("Digite a quantidade de livros adquirida:\n");
					scanf("%d", &livro.qtdExemplares);
					livroRepetido(&listaLivros, &cabL, livro.titulo, livro.edicao, livro.qtdExemplares);
					listaLivros = cadastrarLivro(&cabL, listaLivros, livro);
					break;
				}
				case 3:
				{
					printf("1-todos os usuarios\n2-buscar com codigo\n3-buscar com nome\n4-total de livros\n");
					int num;
					scanf("%d", &num);
					switch (num)
					{
					case 1: listarUsuarios(listaUsuarios); break;
					case 2:
					{
						printf("Digite o codigo do usuario:\n");
						scanf("%d", &num);
						buscaUsuarioCod(listaUsuarios, num);
						break;
					}
					case 3:
					{
						printf("Digite o nome do usuario:\n");
						char nome[152];
						scanf(" %[^\n]%*c", nome);
						buscaNome(listaUsuarios, nome);
						break;
					}
					case 4: printf("Total de usuarios = %d\n", totalUsuarios(listaUsuarios)); break;
					default: printf("Digite um numero valido!!!\n");
					}
					break;
				}
				case 4:
				{
					int codigo;
					char nome[51];
					printf("Digite um codigo para o novo usuario:\n");
					scanf("%d", &codigo);
					printf("Digite o nome do novo usuario:\n");
					scanf(" %[^\n]%*c", nome);
					listaUsuarios = cadastrarUsuario(&cabU, listaUsuarios, codigo, nome);
					break;
				}
				case 5: listarEmprestimos(listaEmprestimo); break;
				case 6:
				{
					int codigou, codigol;
					printf("Digite o codigo do usuario:\n");
					scanf("%d", &codigou);
					printf("Digite o codigo do livro:\n");
					scanf("%d", &codigol);
					listaEmprestimo = emprestar(&cabE, codigou, codigol, listaEmprestimo);
					break;
				}
				case 7:
				{
					int codigoU, codigoL;
					printf("Digite o codigo do usuario:\n");
					scanf("%d", &codigoU);
					printf("Digite o codigo do livro:\n");
					scanf("%d", &codigoL);
					devolver(codigoU, codigoL, &listaEmprestimo);
					break;
				}
				default: printf("Digite um numero valido!!!\n");
				}
			} while (n);
			liberaMemoria(cabL, cabU, cabE, listaLivros, listaUsuarios, listaEmprestimo);
		}
	}
	return 0;
}