// Proprietário: Antonio Vandré Pedrosa Furtunato Gomes (bit.ly/antoniovandre_legadoontologico).

// Biblioteca C de funções e constantes pertencentes a Antonio Vandré Pedrosa Furtunato Gomes, versão de distribuição.

// Licença de uso: Atribuição-NãoComercial-CompartilhaIgual (CC BY-NC-SA).

// Última atualização: 12-07-2020.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define __USE_GNU
#include <math.h>

#include "antoniovandre_constantes.c"

#include "antoniovandre_extra.c"

#define TAMANHO_BUFFER_SMALL 30 // Para pequenos buffers.
#define TAMANHO_BUFFER_WORD 8192 // Para strings pequenas.
#define TAMANHO_BUFFER_PHRASE 81920 // Para strings grandes.
#define VALOR_MAX 100000000
#define DELIMITADORSTRING ',' // Deve ser um char;
#define STRINGSAIDAERRO "Erro de saida de uma string."
#define STRINGSAIDAERROOVER "Erro de saida de uma string por over."
#define MENSAGEM_ERRO_OVER "Um dos números atingiu o limite máximo."
#define TENTATIVASLOGICAS 2 // Podem ser necessárias mais de uma verificação lógica em alguns trechos.
#define TOKENINICIOEVAL '('
#define TOKENFIMEVAL ')'
#define EPSILON 0.0000000001 // Para funções de Cálculo Diferencial.
#define VARIAVELDESUBSTITUICAO 'x' // Deve ser uma letra não presente nos nomes das funções.
#define NUMEROPARTICOESSOMARIEMANN 100 // Para Cálculo Integral.

typedef struct {char * token; long double valor; char * comentario;} tokenfuncaoconstante; // Estrutura para funções e constantes.

#define ARQUIVO_MATHSOBRE "/usr/share/antoniovandre_sobre.txt"
// #define ARQUIVO_MATH_ESTATISTICAS "antoniovandre_math_estatisticas.txt"
#define ARQUIVO_PRECISAO_REAL "/usr/share/antoniovandre_precisao_real.txt"


// Função de output do sobre/about dos softwares matemáticos.

int antoniovandre_mathsobre ()
	{
	FILE * filesobre;
	char antoniovandre_sobre_buffer_char;

	filesobre = fopen(ARQUIVO_MATHSOBRE, "r");

	if (filesobre == NULL)
		{
		printf ("Erro ao abrir arquivo sobre.\n");
		return -1;
		}

	while (! feof(filesobre))
		{
		antoniovandre_sobre_buffer_char = fgetc (filesobre);
		if (antoniovandre_sobre_buffer_char != (char) EOF) printf ("%c", antoniovandre_sobre_buffer_char);
		}

	fclose (filesobre);
	}

// Função de salvar as estatísticas de uso dos softwares matemáticos.

int antoniovandre_salvarmathestatisticas (char * cabecalho)
	{
	FILE * filemathestatisticas;
	char antoniovandre_estatisticas_buffer [TAMANHO_BUFFER_WORD];
	unsigned long int antoniovandre_estatisticas_contador;
	int flag = 0;
	int flag2 = 0;
	char tc;
	char tc2;

	filemathestatisticas = fopen(ARQUIVO_MATH_ESTATISTICAS, "r+");

	if (filemathestatisticas == NULL)
		{
		filemathestatisticas = fopen(ARQUIVO_MATH_ESTATISTICAS, "w");

		if (filemathestatisticas == NULL)
			{
			printf ("Erro ao abrir ou criar arquivo de estatísticas.\n");
			return -1;
			}

		flag2 = 1;
		}

	while ((! feof (filemathestatisticas)) && flag2 == 0)
		{
		fscanf (filemathestatisticas, "%s", antoniovandre_estatisticas_buffer);

		if (! strcmp (antoniovandre_estatisticas_buffer, cabecalho))
			{
			fscanf (filemathestatisticas, "%s", antoniovandre_estatisticas_buffer);

			antoniovandre_estatisticas_contador = atoi (antoniovandre_estatisticas_buffer);
			antoniovandre_estatisticas_contador++;

			fseek (filemathestatisticas, (-1) * strlen (antoniovandre_estatisticas_buffer), SEEK_CUR);

			fprintf (filemathestatisticas, "%lu", antoniovandre_estatisticas_contador);

			if ((int) log10 (antoniovandre_estatisticas_contador - 1) != (int) log10(antoniovandre_estatisticas_contador))
				{
				tc = fgetc (filemathestatisticas);
				if (tc != EOF) fseek (filemathestatisticas, (-1) * sizeof (char), SEEK_CUR);
				fputc ('\n', filemathestatisticas);

				if (tc != EOF)
					do
						{
						tc2 = fgetc (filemathestatisticas);
						if (tc2 != EOF) fseek (filemathestatisticas, (-1) * sizeof (char), SEEK_CUR);
						fputc (tc, filemathestatisticas);
						tc = tc2;
						} while (tc != EOF);
				}

			flag = 1;
			}
		}

	if (flag == 0)
		{
		char cabecalho_buffer [strlen (cabecalho)];

		strcpy (cabecalho_buffer, cabecalho);
		strcat (cabecalho_buffer, " 1\n");

		fprintf (filemathestatisticas, "%s", cabecalho_buffer);
		}

	fclose (filemathestatisticas);
	}

// Função que retorna a precisão real (numérica) para floats.

int antoniovandre_precisao_real ()
	{
	FILE * fileprecisaoreal;
	char antoniovandre_precisao_real_buffer [TAMANHO_BUFFER_WORD];
	int antoniovandre_precisao_real_valor;

	fileprecisaoreal = fopen(ARQUIVO_PRECISAO_REAL, "r");

	if (fileprecisaoreal == NULL)
		{
		printf ("Erro ao abrir arquivo de precisão real.\n");
		return -1;
		}

	fscanf (fileprecisaoreal, "%s", antoniovandre_precisao_real_buffer);

	antoniovandre_precisao_real_valor = atoi (antoniovandre_precisao_real_buffer);

	if (antoniovandre_precisao_real_valor == 0)
		{
		printf ("Erro ao ler arquivo de precisão real.\n");
		return -1;
		}

	fclose (fileprecisaoreal);

	return antoniovandre_precisao_real_valor;
	}

// Array de letras.

const char * antoniovandre_letras = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Array de letras minúsculas.

const char * antoniovandre_letrasminusculas = "abcdefghijklmnopqrstuvwxyz";

// Array de números.

const char * antoniovandre_numeros = ".-0123456789";

// Array de operadores.

const char * antoniovandre_operadores = "+-*/^";

// Remover letras de uma string.

char * antoniovandre_removerletras (char * str)
	{
	int tam1 = strlen (str);
	int tam2 = strlen (antoniovandre_letras);
	char * strf;
	int i;
	int j;
	int flag;
	int contador = 0;

	strf = malloc (TAMANHO_BUFFER_PHRASE);

	for (i = 0; i < tam1; i++)
		{
		flag = 0;

		for (j = 0; j < tam2; j++)
			if (str [i] == antoniovandre_letras [j]) flag = 1;

		if (flag == 0) strf [contador++] = str [i];
		}

	return strf;
	}

// Remover números de uma string.

char * antoniovandre_removernumeros (char * str)
	{
	int tam1 = strlen (str);
	int tam2 = strlen (antoniovandre_numeros);
	char * strf;
	int i;
	int j;
	int flag;

	strf = malloc (TAMANHO_BUFFER_PHRASE);

	for (i = 0; i < tam1; i++)
		{
		flag = 0;

		for (j = 0; j < tam2; j++)
			if (str [i] == antoniovandre_numeros [j]) flag = 1;

		if (flag == 0) strncat (strf, & str [i], 1);
		}

	return strf;
	}

// Verificar se string é monômio.

int antoniovandre_monomio (char * str)
	{
	int contador = 0;
	int flag;
	int i;
	int j;

	for (i = 1; i < strlen (str); i++)
		{
		flag = 0;

		for (j = 0; j < strlen (antoniovandre_numeros); j++)
			if (str [i] == antoniovandre_numeros [j]) flag = 1;

		if (flag == 1)
			for (j = 0; j < strlen (antoniovandre_letras); j++)
				if (str [i - 1] == antoniovandre_letras [j]) return 0;
		}

	for (i = 1; i < strlen (str); i++) if (str [i] == '-') return 0;

	for (i = 0; i < strlen (str); i++)
		{if (str [i] == '.') contador++; if (contador == 2) return 0;}

	if (strcmp (antoniovandre_removerletras (antoniovandre_removernumeros (str)), "") || (! strcmp (str, "-")))
		return 0;
	else
		return -1;
	}

// Parte numérica de um monômio.

long double antoniovandre_partenumericamonomio (char * str)
	{
	char * err;

	if (antoniovandre_monomio (str))
		{
		if (! strcmp (antoniovandre_removerletras (str), ""))
			return 1;
		else if (! strcmp (antoniovandre_removerletras (str), "-") && strlen (str) != 1)
			return -1;
		else
			return (strtold (antoniovandre_removerletras (str), & err));
		}
	else
		return 0;
	}

// Parte literal de um monômio.

char * antoniovandre_parteliteralmonomio (char * str)
	{
	if (antoniovandre_monomio (str))
		return antoniovandre_removernumeros (str);
	else
		return NULL;
	}

// Número para string.

char * antoniovandre_numeroparastring (long double numero)
	{
	int potencia_min = (-1) * antoniovandre_precisao_real ();
	int potencia_max = log10 (VALOR_MAX);
	char * strr;
	int algarismo;
	int i;
	int flag = 0;

	strr = malloc (TAMANHO_BUFFER_WORD);

	if (numero < 0)
		{
		numero *= -1;
		strcat (strr, "-");
		}

	if (numero > VALOR_MAX) return STRINGSAIDAERROOVER;

	for (i = potencia_max; i >= potencia_min; i--)
		{
		if (i == -1)
			{
			if (numero < 1) strcat (strr, "0");

			strcat (strr, ".");
			}

		if (i >= 0)
			algarismo = (int) fmodl (((long double) numero / (long double) powl (10, i)), 10);
		else
			algarismo = (int) fmodl (((long double) numero * (long double) powl (10, (-1) * i)), 10);

		if (algarismo != 0) flag = 1;

		if (flag == 1 || i < 0)
			{
			switch (algarismo)
				{
				case 0:
					strcat (strr, "0");
					break;
				case 1:
					strcat (strr, "1");
					break;
				case 2:
					strcat (strr, "2");
					break;
				case 3:
					strcat (strr, "3");
					break;
				case 4:
					strcat (strr, "4");
					break;
				case 5:
					strcat (strr, "5");
					break;
				case 6:
					strcat (strr, "6");
					break;
				case 7:
					strcat (strr, "7");
					break;
				case 8:
					strcat (strr, "8");
					break;
				case 9:
					strcat (strr, "9");
					break;
				default:
					strcat (strr, "0");
				}
			}
		}

	return strr;
	}

// Comparar strings sem ordem.

int antoniovandre_compararstringssemorden (char * str1, char * str2)
	{
	int tam1 = strlen (str1);
	int tam2 = strlen (str2);
	char c;
	int contador1;
	int contador2;
	int i;
	int j;

	for (i = 0; i < tam1; i++)
		{
		c = str1 [i];

		contador1 = 0;

		for (j = 0; j < tam1; j++) if (c == str1 [j]) contador1++;

		contador2 = 0;

		for (j = 0; j < tam2; j++) if (c == str2 [j]) contador2++;

		if (contador1 != contador2) return -1;
		}

	if (tam1 != tam2) return -1;

	return 0;
	}

// Enésima substring de uma string separada por delimitadores. Inicia-se contando do 0;

char * antoniovandre_nthsubstr (char * str, int n)
	{
	char * strf;
	int tam = strlen (str);
	int inicio = 0;
	int fim = 0;
	int ponteiro = 0;
	int shifti = 0;
	int shiftf = 0;
	int contador = 0;
	int i;

	strf = (char *) malloc (TAMANHO_BUFFER_PHRASE);

	for (i = 0; i < tam; i++)
		if (str [i] == DELIMITADORSTRING)
			if (n == contador++)
				{
				inicio = ponteiro;
				fim = i;
				}
			else
				ponteiro = i;

	if (fim == 0)
		{
		inicio = ponteiro;
		fim = tam - 1;
		}

	if (inicio != 0) shifti = 1;
	if (fim != tam - 1) shiftf = 1;

	contador = 0;

	for (i = inicio + shifti; i <= fim - shiftf; i++) strf [contador++] = str [i];

	return strf;
	}

// Reduzir termos semelhantes.

char * antoniovandre_reduzirtermossemelhantes (char * args)
	{
	int nargs = 1;
	char * strf;
	char * parteliteral;
	char * strt = (char *) malloc (TAMANHO_BUFFER_WORD);;
	int i;
	int j;
	int flag;
	int contador = 0;

	for (i = 0; i < strlen (args); i++) if (args [i] == DELIMITADORSTRING) nargs++;

	char * strlit [nargs];
	long double coefs [nargs];

	for (i = 0; i < nargs; i++) strlit [i] = (char *) malloc (TAMANHO_BUFFER_WORD);

	for (i = 0; i < nargs; i++)
		{
		flag = 0; j = 0;

		while (flag == 0 && j++ < TENTATIVASLOGICAS)
			if (antoniovandre_monomio (antoniovandre_nthsubstr (args, i))) flag = 1;

		if (flag == 1)
			{
			parteliteral = malloc (TAMANHO_BUFFER_WORD);

			strcpy (parteliteral, antoniovandre_parteliteralmonomio (antoniovandre_nthsubstr (args, i)));

			flag = 0;

			for (j = 0; j < contador; j++)
				if (! antoniovandre_compararstringssemorden (strlit [j], parteliteral))
					{
					coefs [j] += (long double) antoniovandre_partenumericamonomio (antoniovandre_nthsubstr (args, i));
					flag = 1;
					break;
					}
			if (flag == 0)
				{
				strcpy (strlit [contador], parteliteral);
				coefs [contador++] = (long double) antoniovandre_partenumericamonomio (antoniovandre_nthsubstr (args, i));
				}

			free (parteliteral);
			}
		else
			return (STRINGSAIDAERRO);
		}

	strf = (char *) malloc (TAMANHO_BUFFER_WORD);

	flag = 0;

	for (i = 0; i < contador; i++)
		if (coefs [i] != 0)
			{
			strcpy (strt, antoniovandre_numeroparastring (coefs [i]));

			if (! strcmp (strt, STRINGSAIDAERROOVER)) return (STRINGSAIDAERROOVER);

			if (i == 0) 
				memmove (strf, strt, strlen (antoniovandre_numeroparastring (coefs [i])));
			else
				strcat (strf, strt);
			strcat (strf, strlit [i]);
			if (i < contador - 1) strf [strlen (strf)] = ' ';

			flag = 1;
			}

	if (flag == 1)
		return (strf);
	else
		return (antoniovandre_numeroparastring (0));
	}

// Valor numérico de um polinômio.

char * antoniovandre_valornumericopolinomio (char * args)
	{
	int nargs = 1;
	int indice_inicio = -1;
	char * strt = (char *) malloc (TAMANHO_BUFFER_WORD);
	char * strt2 = (char *) malloc (TAMANHO_BUFFER_WORD);
	char * str = (char *) malloc (TAMANHO_BUFFER_WORD);
	char * str2 = (char *) malloc (TAMANHO_BUFFER_WORD);
	char * str3 = (char *) malloc (TAMANHO_BUFFER_WORD);
	char * str4 = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	char * str5 = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	long double coef;
	long double fator;
	int i;
	int j;
	int k;
	int contador;
	int flag;
	int flag2 = 0;
	char c = DELIMITADORSTRING;
	char * err;

	strcpy (str4, "");

	for (i = 0; i < strlen (args); i++)
		{
		if (args [i] == DELIMITADORSTRING) nargs++;
		if ((args [i] == '=') && (indice_inicio == -1)) indice_inicio = nargs - 1;
		}

	if (indice_inicio != -1)
		{
		if (indice_inicio == 0) return STRINGSAIDAERRO;

		for (i = indice_inicio; i < nargs; i++)
			{
			flag = 0; contador = 0;

			while ((flag == 0) && (contador++ < TENTATIVASLOGICAS))
				{
				strt = antoniovandre_nthsubstr (args, i);

				if (strt [1] == '=') flag = 1;
				}

			if (flag == 0) return STRINGSAIDAERRO;

			flag = 0;

			for (j = 0; j < strlen (antoniovandre_letras); j++)
				if (strt [0] == antoniovandre_letras [j]) flag = 1;

			if (flag == 0) return STRINGSAIDAERRO;

			strcpy (strt2, "");

			for (j = 2; j < strlen (strt); j++) strncat (strt2, & strt [j], 1);

			fator = strtold (strt2, & err);

			if (* err != 0) return STRINGSAIDAERRO;

			if (fator > VALOR_MAX) return STRINGSAIDAERROOVER;

			for (j = 0; j < indice_inicio; j++)
				{
				flag = 0; contador = 0;

				while ((flag == 0) && (contador++ < TENTATIVASLOGICAS))
					{
					if (flag2 == 0)
						str = antoniovandre_nthsubstr (args, j);
					else
						str = antoniovandre_nthsubstr (str5, j);

					if (antoniovandre_monomio (str)) flag = 1;
					}

				if (flag == 0) return STRINGSAIDAERRO;

				coef = antoniovandre_partenumericamonomio (str);

				if (coef > VALOR_MAX) return STRINGSAIDAERROOVER;

				str2 = antoniovandre_parteliteralmonomio (str);

				strcpy (str3, "");

				for (k = 0; k < strlen (str2); k++)
					if (strt [0] == str2 [k])
						coef *= fator;
					else
						strncat (str3, & str2 [k], 1);

				if (coef > VALOR_MAX) return STRINGSAIDAERROOVER;

				strcat (str4, antoniovandre_numeroparastring (coef));
				strcat (str4, str3);
				strncat (str4, &c, 1);
				}

			str4 [strlen (str4) - 1] = '\0';
			strcpy (str5, str4);
			strcpy (str4, "");

			flag2 = 1;
			}
		}

	if (indice_inicio != -1)
		return antoniovandre_reduzirtermossemelhantes (str5);
	else
		return antoniovandre_reduzirtermossemelhantes (args);
	}

// Função de verificação de uma expressão algébrica.

int antoniovandre_expressao (char * str)
	{
	int flag;
	int i;
	int j;

	for (i = 0; i < strlen (str); i++)
		{
		flag = 0;

		for (j = 0; j < strlen (antoniovandre_numeros); j++) if (str [i] == antoniovandre_numeros [j]) flag = 1;

		for (j = 0; j < strlen (antoniovandre_letras); j++) if (str [i] == antoniovandre_letras [j]) flag = 1;

		for (j = 0; j < strlen (antoniovandre_operadores); j++) if (str [i] == antoniovandre_operadores [j]) flag = 1;

		if ((str [i] == TOKENINICIOEVAL) || (str [i] == TOKENFIMEVAL)) flag = 1;

		if (flag == 0) return 0;
		}

	return 1;
	}

// Substring.

char * antoniovandre_substring (char * str, int inicio, int fim)
	{
	char * strt = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	int i;

	strcpy (strt, "");

	for (i = inicio; i <= fim; i++)
		strncat (strt, & str [i], 1);

	return strt;
	}

// Função eval célula função. Os nomes das funções devem conter apenas letras minúsculas. Os nomes das constantes devem conter apenas letras maiúsculas.

char * antoniovandre_evalcelulafuncao (char * str)
	{
	tokenfuncaoconstante funcoesconstantes [TAMANHO_BUFFER_SMALL];
	int tamanhotokenfuncaoconstante;
	int tamanhotokenfuncaoconstantemax = 0;
	int tokenid = -1;
	int tokeninicio;
	long double resultado;
	long double argumento;
	long double coeficiente;
	char * buffer = (char *) malloc (TAMANHO_BUFFER_WORD);
	int i;
	int j;
	char * err;
	char * err2;

	for (i = 0; i < TAMANHO_BUFFER_SMALL; i++)
		{
		funcoesconstantes [i].token = (char *) malloc (TAMANHO_BUFFER_WORD);
		strcpy (funcoesconstantes [i].token, "");

		funcoesconstantes [i].valor = (long double) 0;

		funcoesconstantes [i].comentario = (char *) malloc (TAMANHO_BUFFER_PHRASE);
		strcpy (funcoesconstantes [i].comentario, "");
		}

	strcpy (funcoesconstantes [0].token, "arccossec");
	strcpy (funcoesconstantes [0].comentario, "Função arco-cossecante.");

	strcpy (funcoesconstantes [1].token, "arcsec");
	strcpy (funcoesconstantes [1].comentario, "Função arco-secante.");

	strcpy (funcoesconstantes [2].token, "arccotg");
	strcpy (funcoesconstantes [2].comentario, "Função arco-cotangente.");

	strcpy (funcoesconstantes [3].token, "arctg");
	strcpy (funcoesconstantes [3].comentario, "Função arco-tangente.");

	strcpy (funcoesconstantes [4].token, "arccos");
	strcpy (funcoesconstantes [4].comentario, "Função arco-cosseno.");

	strcpy (funcoesconstantes [5].token, "arcsen");
	strcpy (funcoesconstantes [5].comentario, "Função arco-seno.");

	strcpy (funcoesconstantes [6].token, "cossec");
	strcpy (funcoesconstantes [6].comentario, "Função cossecante.");

	strcpy (funcoesconstantes [7].token, "sec");
	strcpy (funcoesconstantes [7].comentario, "Função secante.");

	strcpy (funcoesconstantes [8].token, "sen");
	strcpy (funcoesconstantes [8].comentario, "Função seno.");

	strcpy (funcoesconstantes [9].token, "cos");
	strcpy (funcoesconstantes [9].comentario, "Função cosseno.");

	strcpy (funcoesconstantes [10].token, "cotg");
	strcpy (funcoesconstantes [10].comentario, "Função cotangente.");

	strcpy (funcoesconstantes [11].token, "tg");
	strcpy (funcoesconstantes [11].comentario, "Função tangente.");

	strcpy (funcoesconstantes [12].token, "logdois");
	strcpy (funcoesconstantes [12].comentario, "Função logaritmo na base 2.");

	strcpy (funcoesconstantes [13].token, "logdez");
	strcpy (funcoesconstantes [13].comentario, "Função logaritmo na base 10.");

	strcpy (funcoesconstantes [14].token, "ln");
	strcpy (funcoesconstantes [14].comentario, "Função logaritmo natural.");

	strcpy (funcoesconstantes [15].token, "PI");
	funcoesconstantes [15].valor = (long double) M_PIl;
	strcpy (funcoesconstantes [15].comentario, "Constante pi, razão entre o comprimento e o diâmetro de uma circunferência.");

	strcpy (funcoesconstantes [16].token, "E");
	funcoesconstantes [16].valor = (long double) M_El;
	strcpy (funcoesconstantes [16].comentario, "Constante e, base do logaritmo natural.");

	strcpy (funcoesconstantes [17].token, FISICA_C_SI);
	funcoesconstantes [17].valor = (long double) FISICA_C_SI_VALOR;
	strcpy (funcoesconstantes [17].comentario, "Constante c, velocidade da luz no vácuo.");

	for (i = 0; i < strlen (str); i++)
		for (j = 0; j < TAMANHO_BUFFER_SMALL; j++)
			if (! strcmp (antoniovandre_substring (str, i, i + strlen (funcoesconstantes [j].token) - 1), funcoesconstantes [j].token))
				{
				tamanhotokenfuncaoconstante = strlen (funcoesconstantes [j].token);

				if (tamanhotokenfuncaoconstantemax < tamanhotokenfuncaoconstante)
					{
					tamanhotokenfuncaoconstantemax = tamanhotokenfuncaoconstante;
					tokenid = j;
					tokeninicio = i;
					}
				}

	if (tokenid != -1)
		if (funcoesconstantes [tokenid].valor != 0)
			{
			coeficiente = 1;

			if (tokeninicio > 0)
				{
				buffer = antoniovandre_substring (str, 0, tokeninicio - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}	
				}

			if (strcmp (antoniovandre_substring (str, tokeninicio + tamanhotokenfuncaoconstantemax, strlen (str) - 1), "")) return STRINGSAIDAERRO;

			return antoniovandre_numeroparastring ((long double) coeficiente * funcoesconstantes [tokenid].valor);
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 8), "arccossec"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 9, strlen (str) - 1), & err);

			if ((* err != 0) || ((argumento > -1) && (argumento < 1))) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente * asinl (1 / (long double) argumento)));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 5), "arcsec"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 6, strlen (str) - 1), & err);

			if ((* err != 0) || ((argumento > -1) && (argumento < 1))) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente * acosl (1 / (long double) argumento)));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 6), "arccotg"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 7, strlen (str) - 1), & err);

			if (* err != 0) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			if (argumento == 0) resultado = (long double) coeficiente * M_PI_2l; else if (argumento < 0) resultado = (long double) coeficiente * (atanl (1 / (long double) argumento) + M_PIl); else resultado = (long double) coeficiente * atanl (1 / (long double) argumento);

			return antoniovandre_numeroparastring ((long double) resultado);
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 4), "arctg"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 5, strlen (str) - 1), & err);

			if (* err != 0) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente * atanl ((long double) argumento)));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 5), "arccos"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 6, strlen (str) - 1), & err);

			if ((* err != 0) || (argumento < -1) || (argumento > 1)) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente * acosl ((long double) argumento)));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 5), "arcsen"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 6, strlen (str) - 1), & err);

			if ((* err != 0) || (argumento < -1) || (argumento > 1)) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente * asinl ((long double) argumento)));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 5), "cossec"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 6, strlen (str) - 1), & err);

			if ((* err != 0) || (fmodl (argumento, M_PIl) == 0)) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente / sinl ((long double) argumento)));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 2), "sec"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 3, strlen (str) - 1), & err);

			if ((* err != 0) || (fmodl (argumento, M_PIl) == strtold (antoniovandre_numeroparastring (M_PI_2l), & err2))) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente / cosl ((long double) argumento)));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 2), "sen"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 3, strlen (str) - 1), & err);

			if (* err != 0) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente * sinl ((long double) argumento)));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 2), "cos"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 3, strlen (str) - 1), & err);

			if (* err != 0) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente * cosl ((long double) argumento)));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 3), "cotg"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 4, strlen (str) - 1), & err);

			if ((* err != 0) || (fmodl (argumento, M_PIl) == 0)) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente / tanl ((long double) argumento)));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 1), "tg"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 2, strlen (str) - 1), & err);

			if ((* err != 0) || (fmodl (argumento, M_PIl) == strtold (antoniovandre_numeroparastring (M_PI_2l), & err2))) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente * tanl ((long double) argumento)));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 6), "logdois"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 7, strlen (str) - 1), & err);

			if ((* err != 0) || (argumento <= 0)) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente * logl ((long double) argumento) / M_LN2l));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 5), "logdez"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 6, strlen (str) - 1), & err);

			if ((* err != 0) || (argumento <= 0)) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente * logl ((long double) argumento) / M_LN10l));
			}

	for (i = 0; i < strlen (str); i++)
		if (! strcmp (antoniovandre_substring (str, i, i + 1), "ln"))
			{
			coeficiente = 1;

			if (i > 0)
				{
				buffer = antoniovandre_substring (str, 0, i - 1);

				if (! strcmp (buffer, "-"))
					coeficiente = -1;
				else
					{
					coeficiente = strtold (buffer, & err);
					if (* err != 0) return STRINGSAIDAERRO;
					if (coeficiente > VALOR_MAX) return STRINGSAIDAERROOVER;
					}
				}

			argumento = strtold (antoniovandre_substring (str, i + 2, strlen (str) - 1), & err);

			if ((* err != 0) || (argumento <= 0)) return STRINGSAIDAERRO;

			if (argumento > VALOR_MAX) return STRINGSAIDAERROOVER;

			return antoniovandre_numeroparastring ((long double) ((long double) coeficiente * logl ((long double) argumento)));
			}

	strtold (str, & err);

	if ((* err != 0) || (! strcmp (str, "")))
		return STRINGSAIDAERRO;
	else
		return str;
	}

// Função eval célula.

char * antoniovandre_evalcelula (char * str)
	{
	char * strt = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	char * strt2 = (char *) malloc (TAMANHO_BUFFER_WORD);
	char * strt3 = (char *) malloc (TAMANHO_BUFFER_WORD);
	char * strtv1 = (char *) malloc (TAMANHO_BUFFER_WORD);
	char * strtv2 = (char *) malloc (TAMANHO_BUFFER_WORD);
	char * strt4 = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	int posicoes_operadores [TAMANHO_BUFFER_PHRASE];
	long double valor;
	long double valort;
	long double valort2;
	int contador;
	int i;
	int j;
	int k;
	int flag;
	int flag2;
	int flag3;
	int flag4;
	int ponteiro;
	int ponteiroinicio;
	int ponteirofim;
	int finalponteirocelula;
	char * err;
	char tc = ' ';
	char tc2;

	strcpy (strt, "");

	for (i = 0; i < strlen (str); i++)
		if (str [i] != tc) strncat (strt, & str [i], 1);

	if (! strcmp (strt, "")) return STRINGSAIDAERRO;

	tc = strt [0];

	for (i = 0; i < strlen (antoniovandre_operadores); i++)
		{
		tc2 = antoniovandre_operadores [i];

		if ((tc == tc2) && (tc2 != '-'))
			return STRINGSAIDAERRO;
		}

	while (1)
		{
		for (i = 0; i < TAMANHO_BUFFER_PHRASE; i++) posicoes_operadores [i] = -1;

		contador = 0; flag4 = 0;

		for (i = 0; i < strlen (strt); i++)
			for (j = 0; j < strlen (antoniovandre_operadores); j++)
				{
				flag3 = 0;

				for (k = 0; k < strlen (antoniovandre_letrasminusculas); k++)
					{
					if (((i == 0) && (antoniovandre_operadores [j] == '-')) || ((contador > 0) && (posicoes_operadores [contador - 1] == i - 1) && (antoniovandre_operadores [j] == '-')) || ((i > 0) && (strt [i - 1] == antoniovandre_letrasminusculas [k]) && (antoniovandre_operadores [j] == '-')))
						{
						flag3 = 1;
						flag4 = 1;
						}
					}
				if ((strt [i] == antoniovandre_operadores [j]) && flag3 == 0) posicoes_operadores [contador++] = i;
				}

		if (posicoes_operadores [0] == -1) break;

		for (i = 0; i < TAMANHO_BUFFER_PHRASE; i++)
			if (posicoes_operadores [i] > 0)
				{
				flag = 0;
				flag2 = 0;

				for (j = 0; j < TAMANHO_BUFFER_PHRASE; j++)
					if (strt [posicoes_operadores [j]] == '^') flag2 = 1;

				for (j = 0; j < TAMANHO_BUFFER_PHRASE; j++)
					if (((strt [posicoes_operadores [j]] == '*') || (strt [posicoes_operadores [j]] == '/')) && flag2 == 1) flag = 1;

				strcpy (strt2, "");

				if (i > 0)
					ponteiro = posicoes_operadores [i - 1] + 1;
				else
					ponteiro = 0;

				ponteiroinicio = ponteiro;

				for (j = ponteiro; j < posicoes_operadores [i]; j++)
					strncat (strt2, & strt [j], 1);

				strcpy (strt3, "");

				if (posicoes_operadores [i + 1] == -1)
					ponteiro = strlen (strt);
				else
					ponteiro = posicoes_operadores [i + 1];

				ponteirofim = ponteiro;

				for (j = posicoes_operadores [i] + 1; j < ponteiro; j++)
					strncat (strt3, & strt [j], 1);

				if ((! strcmp (strt2, "")) || (! strcmp (strt3, "")))
					return STRINGSAIDAERRO;

				strtv1 = antoniovandre_evalcelulafuncao (strt2);
				strtv2 = antoniovandre_evalcelulafuncao (strt3);

				if (! strcmp (strtv1, STRINGSAIDAERRO)) return STRINGSAIDAERRO;
				if (! strcmp (strtv2, STRINGSAIDAERRO)) return STRINGSAIDAERRO;

				if (! strcmp (strtv1, STRINGSAIDAERROOVER)) return STRINGSAIDAERROOVER;
				if (! strcmp (strtv2, STRINGSAIDAERROOVER)) return STRINGSAIDAERROOVER;

				valort = strtold (strtv1, & err);
				if (* err != 0) return STRINGSAIDAERRO;

				valort2 = strtold (strtv2, & err);
				if (* err != 0) return STRINGSAIDAERRO;

				if (strt [posicoes_operadores [i]] == '^')
					{
					valor = powl (valort, valort2);
					if (isnan (valor) || isinf (valor)) return STRINGSAIDAERRO;
					if (valor > VALOR_MAX) return STRINGSAIDAERROOVER;
					break;
					}

				if ((strt [posicoes_operadores [i]] == '*') && (flag2 == 0))
					{
					valor = valort * valort2;
					if (valor > VALOR_MAX) return STRINGSAIDAERROOVER;
					break;
					}

				if ((strt [posicoes_operadores [i]] == '/') && (flag2 == 0))
					{
					if (valort2 == 0) return STRINGSAIDAERRO;

					valor = valort / valort2;
					if (valor > VALOR_MAX) return STRINGSAIDAERROOVER;
					break;
					}

				if ((strt [posicoes_operadores [i]] == '+') && (flag == 0) && (flag2 == 0))
					{
					valor = valort + valort2;
					if (valor > VALOR_MAX) return STRINGSAIDAERROOVER;
					break;
					}

				if ((strt [posicoes_operadores [i]] == '-') && (flag == 0) && (flag2 == 0))
					{
					valor = valort - valort2;
					if (valor > VALOR_MAX) return STRINGSAIDAERROOVER;
					break;
					}
				}

		strcpy (strt4, "");

		for (i = 0; i < ponteiroinicio; i++)
			strncat (strt4, & strt [i], 1);

		strcat (strt4, antoniovandre_numeroparastring (valor));

		for (i = ponteirofim; i < strlen (strt); i++)
			strncat (strt4, & strt [i], 1);

		strcpy (strt, strt4);
		}

	return antoniovandre_evalcelulafuncao (strt);
	}

// Função eval.

char * antoniovandre_eval (char * str)
	{
	char * str2 = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	char * str3 = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	char * str4 = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	char * str5 = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	int inicio;
	int fim;
	int i;
	int flag;
	int flag2;

	strcpy (str2, "");

	for (i = 0; i < strlen (str); i++)
		if (str [i] != ' ') strncat (str2, & str [i], 1);

	if (! strcmp (str2, "")) return STRINGSAIDAERRO;

	do
		{
		inicio = 0;
		fim = strlen (str2) - 1;
		flag = 0;
		flag2 = 0;

		for (i = 0; i < strlen (str2); i++)
			{
			if (str2 [i] == TOKENINICIOEVAL)
				{
				inicio = i + 1;
				flag = 1;
				}

			if (str2 [i] == TOKENFIMEVAL)
				{
				fim = i - 1;
				flag2 = 1;
				break;
				}
			}

		strcpy (str3, "");

		if (flag == flag2)
			{
			for (i = 0; i < inicio - 1; i++)
				strncat (str3, & str2 [i], 1);

			strcpy (str4, "");

			for (i = inicio; i <= fim; i++)
				strncat (str4, & str2 [i], 1);

			str5 = antoniovandre_evalcelula (str4);

			if (! strcmp (str5, STRINGSAIDAERRO)) return STRINGSAIDAERRO;
			if (! strcmp (str5, STRINGSAIDAERROOVER)) return STRINGSAIDAERROOVER;

			for (i = 0; i < strlen (str5); i++)
				strncat (str3, & str5 [i], 1);

			for (i = fim + 2; i < strlen (str2); i++)
				strncat (str3, & str2 [i], 1);

			strcpy (str2, str3);
			}
		} while (! ((flag == 0) && (flag2 == 0)));

	return antoniovandre_evalcelula (str2);
	}

// Derivada em um ponto.

char * antoniovandre_derivada (char * str, long double ponto)
	{
	char * str2 = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	char * str3 = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	long double valorsup;
	long double valorinf;
	int i;
	char * err;

	if (ponto > VALOR_MAX) return STRINGSAIDAERROOVER;

	strcpy (str2, "");

	for (i = 0; i < strlen (str); i++)
		if (str [i] == VARIAVELDESUBSTITUICAO)
			strcat (str2, antoniovandre_numeroparastring ((long double) ((long double) ponto + (long double) EPSILON)));
		else
			strncat (str2, & str [i], 1);

	valorsup = strtold (antoniovandre_eval (str2), & err);

	if (* err != 0) return STRINGSAIDAERRO;

	strcpy (str3, "");

	for (i = 0; i < strlen (str); i++)
		if (str [i] == VARIAVELDESUBSTITUICAO)
			strcat (str3, antoniovandre_numeroparastring ((long double) ((long double) ponto - (long double) EPSILON)));
		else
			strncat (str3, & str [i], 1);

	valorinf = strtold (antoniovandre_eval (str3), & err);

	if (* err != 0) return STRINGSAIDAERRO;

	return antoniovandre_numeroparastring ((long double) ((long double) valorsup - (long double) valorinf) / (long double) (2 * (long double) EPSILON));
	}

// Integral definida.

char * antoniovandre_integraldefinida (char * str, long double a, long double b)
	{
	char * str2 = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	char * str3 = (char *) malloc (TAMANHO_BUFFER_PHRASE);
	long double integral = 0;
	long double norma;
	long double parcela;
	int i;
	int j;
	char * err;

	norma = (long double) ( (long double) b - (long double) a) / (long double) NUMEROPARTICOESSOMARIEMANN;

	for (j = 0; j < NUMEROPARTICOESSOMARIEMANN; j++)
		{
		strcpy (str2, "");

		for (i = 0; i < strlen (str); i++)
			if (str [i] == VARIAVELDESUBSTITUICAO)
				strcat (str2, antoniovandre_numeroparastring ((long double) ((long double) a + (long double) j * (long double) norma + (long double) ((long double) norma / 2))));
			else
				strncat (str2, & str [i], 1);

		strcpy (str3, antoniovandre_eval (str2));

		if (! strcmp (str3, STRINGSAIDAERROOVER)) return STRINGSAIDAERROOVER;

		parcela = strtold (str3, & err) * (long double) norma;

		if (* err != 0) return STRINGSAIDAERRO;

		integral += (long double) parcela;

		if (integral > VALOR_MAX) return STRINGSAIDAERROOVER;
		}

	return antoniovandre_numeroparastring (integral);
	}

