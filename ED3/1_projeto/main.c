/*
Dados dos integrantes:

    -> Lucas Sales Duarte - 11734490
    -> João Victor de Almeida - 13695424
Alunos do curso de graduação de engenharia de computação
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


#define LIXO "$"
#define TAM_REGISTRO_FIXO 21
#define TAM_REGISTRO 76

typedef struct main
{// 13 bytes em status e 4 bytes no resto
    char status;
    int proxRRN;
    int nroTecnologia;
    int nroParesTecnologia;
} Cabecalho;

typedef struct
{

    int tamanho;
    char *string;

} StringVariavel;

typedef struct {
    char removido; // 1 byte
    int grupo; // 4 bytes
    int popularidade; // 4 bytes
    int peso; // 4 bytes
    StringVariavel nomeTecnologiaOrigem; // tamanho variável
    StringVariavel nomeTecnologiaDestino; // tamanho variável

} Dados;

void readline(char* string){
    char c = 0;

    do{
        c = (char) getchar();

    } while(c == '\n' || c == '\r');

    int i = 0;

    do{
        string[i] = c;
        i++;
        c = getchar();
    } while(c != '\n' && c != '\r');

    string[i]  = '\0';
}

void binarioNaTela(const char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}

// !!
FILE *init_bin(FILE *bin)
{
    Cabecalho cabecalho;
    cabecalho.status = '0';
    cabecalho.proxRRN = 0;
    cabecalho.nroParesTecnologia = 0;
    cabecalho.nroTecnologia = 0;
    
    fwrite(&cabecalho.status, sizeof(char), 1, bin);

    return bin;
}
FILE *archive_open(const char *nameArchive)
{
    // entrada do arquivos seu retorno em ponteiro
    FILE *file;
    file = fopen(nameArchive, "r");

    return file;
}

void Atualizar_Cabecalho(FILE *bin, int nroTecnologia, int nroParesTecnologia)
{
    fseek(bin, 0, SEEK_SET);
    Cabecalho cabecalho;
    fread(&cabecalho, sizeof(Cabecalho), 1, bin);

    cabecalho.status = '1'; 
    cabecalho.nroTecnologia = nroTecnologia;
    cabecalho.nroParesTecnologia = nroParesTecnologia;
    
    fseek(bin, 0, SEEK_SET); //volta para o inicio
    fwrite(&cabecalho, sizeof(Cabecalho), 1, bin);
}

//funcao nova
void Escrever_Dados(FILE *bin, Dados dados)
{
    fwrite(&dados.removido, sizeof(char), 1, bin);
    fwrite(&dados.grupo, sizeof(int), 1, bin);
    fwrite(&dados.popularidade, sizeof(int), 1, bin);
    fwrite(&dados.peso, sizeof(int), 1, bin);
    fwrite(&dados.nomeTecnologiaOrigem.tamanho, sizeof(int), 1, bin);
    fwrite(&dados.nomeTecnologiaOrigem.string, sizeof(char), dados.nomeTecnologiaOrigem.tamanho, bin);
    fwrite(&dados.nomeTecnologiaDestino.tamanho, sizeof(int), 1, bin);
    fwrite(&dados.nomeTecnologiaDestino.string, sizeof(char), dados.nomeTecnologiaDestino.tamanho, bin);
}

void printarRNN(FILE *bin, int RNN)
{

    unsigned char byte;
    while (fread(&byte, sizeof(byte), 1, bin) == 1)
    {
        printf("Byte lido: %c\n", byte);
    }
}

void printar_binario(FILE *bin)
{
    int RNN = 3;

    printarRNN(bin, RNN);
}


Dados LerRegistroCSV(FILE *csv){
    Dados dados;
    char buffer[100];

    dados.removido = '-';
    dados.nomeTecnologiaOrigem.string = NULL;
    dados.nomeTecnologiaDestino.string = NULL;

     fscanf(csv, "%d,%d,%d,", &dados.grupo, &dados.popularidade, &dados.peso);
    scan_quote_string(buffer);
    dados.nomeTecnologiaOrigem.tamanho = strlen(buffer);
    dados.nomeTecnologiaOrigem.string = strdup(buffer);
    scan_quote_string(buffer);
    dados.nomeTecnologiaDestino.tamanho = strlen(buffer);
    dados.nomeTecnologiaDestino.string = strdup(buffer);

    return dados;
}


short int functionality_1(const char csvArchiveName[], const char binArchiveName[])
{
    FILE *csv = archive_open(csvArchiveName); // buscar o csv
    FILE *bin = fopen(binArchiveName, "wb+");  // criar o bin

    if (csv == NULL || bin == NULL)
    {
        printf("\nainda nada\n");
        return 1; // Caso o csv não seja encontrado ou o bin não criado, passa 1 DE ERRO para o file
    }

    bin = init_bin(bin); // inicializar o bin

    Dados dados;
    while(!feof(csv)){
        dados = LerRegistroCSV(csv);
        Escrever_Dados(bin, dados);

        free(dados.nomeTecnologiaOrigem.string);
        free(dados.nomeTecnologiaDestino.string);

        Atualizar_Cabecalho(bin, 1, 1); //Aqui ajustar ainda !!!!!!---

        fclose(csv);
        fclose(bin);

        binarioNaTela(binArchiveName);
        return 0;
    }
}

int main(int argc, char const *argv[])

{

    printf("\n-------- -------- -------- -------- -------- \n\n"); // apagar ao fim

    //  -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - --
    //  leitura de entrada de decisão:

    const char decision = *argv[1]; // recebe a decisão

    if (decision != '1' && decision != '2' && decision != '3' && decision != '4')
    {
        printf("\n\t -> Erro de decisão\n"); // caso a escolha n seja válida
        return 1;
    }

    const char *argumento_1 = argv[1];
    const char *argumento_2 = argv[2];
    const char *argumento_3 = argv[3];

    printf("os argumentos são %s\t%s\t%s\n", argumento_1, argumento_2, argumento_3);

    
    const char csvArchiveName[] = "tecnologia.csv";
    const char binArchiveName[] = "output_file.bin";

    switch (decision)
    {
    case '1':
        if (functionality_1(csvArchiveName, binArchiveName))
        {
            printf("\nFalha no processamento do arquivo.");
        };
        break;
    case '2':
        /* code */
        break;
    case '3':
        /* code */
        break;
    case '4':
        /* code */
        break;
    default:
        break;
    }

    //  -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - --
    // primeira etapa é criar o arquivo binário:

    // fopen

    //  -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - --
    printf("\n\t\tSucesso\n"); // apagar ao fim
    printf("\n\n-------- -------- -------- -------- -------- \n"); // apagar ao fim
    return 0;
}
