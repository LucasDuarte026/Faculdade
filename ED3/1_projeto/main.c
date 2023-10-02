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
#define MAX_STRING_LENGTH 100

typedef struct
{ // 13 bytes em status e 4 bytes no resto
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

typedef struct
{
    char removido;                        // 1 byte
    int grupo;                            // 4 bytes
    int popularidade;                     // 4 bytes
    int peso;                             // 4 bytes
    StringVariavel nomeTecnologiaOrigem;  // tamanho variável
    StringVariavel nomeTecnologiaDestino; // tamanho variável

} Dados;

void readline(char *string)
{
    char c = 0;

    do
    {
        c = (char)getchar();

    } while (c == '\n' || c == '\r');

    int i = 0;

    do
    {
        string[i] = c;
        i++;
        c = getchar();
    } while (c != '\n' && c != '\r');

    string[i] = '\0';
}

void binarioNaTela(const char *nomeArquivoBinario)
{ /* Você não precisa entender o código dessa função. */

    /* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
     *  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

    unsigned long i, cs;
    unsigned char *mb;
    size_t fl;
    FILE *fs;
    if (nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb")))
    {
        fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
        return;
    }
    fseek(fs, 0, SEEK_END);
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    mb = (unsigned char *)malloc(fl);
    fread(mb, 1, fl, fs);

    cs = 0;
    for (i = 0; i < fl; i++)
    {
        cs += (unsigned long)mb[i];
    }
    printf("%lf\n", (cs / (double)100));
    free(mb);
    fclose(fs);
}

void scan_quote_string(char *str)
{

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

    while ((R = getchar()) != EOF && isspace(R))
        ; // ignorar espaços, \r, \n...

    if (R == 'N' || R == 'n')
    { // campo NULO
        getchar();
        getchar();
        getchar();       // ignorar o "ULO" de NULO.
        strcpy(str, ""); // copia string vazia
    }
    else if (R == '\"')
    {
        if (scanf("%[^\"]", str) != 1)
        { // ler até o fechamento das aspas
            strcpy(str, "");
        }
        getchar(); // ignorar aspas fechando
    }
    else if (R != EOF)
    { // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
        str[0] = R;
        scanf("%s", &str[1]);
    }
    else
    { // EOF
        strcpy(str, "");
    }
}

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

void Atualizar_Cabecalho(FILE *bin, int nroTecnologia, int nroParesTecnologia, int prox)
{
    Cabecalho cabecalho;
    fseek(bin, 0, SEEK_SET); // volta para o inicio
    fread(&cabecalho, sizeof(Cabecalho), 1, bin);

    cabecalho.status = '1';
    cabecalho.proxRRN = prox;
    cabecalho.nroTecnologia = nroTecnologia;
    cabecalho.nroParesTecnologia = nroParesTecnologia;

    fseek(bin, 0, SEEK_SET); // volta para o inicio
    fwrite(&cabecalho, sizeof(Cabecalho), 1, bin);
}

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

Dados LerRegistroCSV(FILE *csv)
{ // le o registro
    Dados dados;
    dados.removido = '-';
    dados.nomeTecnologiaOrigem.string = NULL;
    dados.nomeTecnologiaOrigem.tamanho = 0;
    dados.nomeTecnologiaDestino.string = NULL;
    dados.nomeTecnologiaDestino.tamanho = 0;

    char *nomeTecnologiaOrigem;
    int grupo;
    int popularidade;
    char *nomeTecnologiaDestino;
    int peso;

    char bufferOrigem[MAX_STRING_LENGTH];
    char bufferDestino[MAX_STRING_LENGTH];

    if (fscanf(csv, " %[^,],%d,%d, %[^,],%d", bufferOrigem, &dados.grupo, &dados.popularidade, bufferDestino, &dados.peso) == 5)
    {
        dados.nomeTecnologiaOrigem.tamanho = strlen(bufferOrigem); // documentar pq funciona
        dados.nomeTecnologiaOrigem.string = strdup(bufferOrigem);

        dados.nomeTecnologiaDestino.tamanho = strlen(bufferDestino);
        dados.nomeTecnologiaDestino.string = strdup(bufferDestino);
        // printf("%s,%d,%d,%s,%d\n", dados.nomeTecnologiaOrigem.string, dados.grupo, dados.popularidade, dados.nomeTecnologiaDestino.string, dados.peso); // para ler os dados escritos
    }

    return dados;
}

char **testa_unico(int *prt_quant_tec, Dados dado, char **tecnologies)
{
    int quant_tec = *prt_quant_tec;     // Pega o valor do ponteiro
    for (int i = 0; i < quant_tec; i++)
    {

        if (strcmp(tecnologies[i], dado.nomeTecnologiaOrigem.string) == 0) // testa se já existe
        {
            return tecnologies; //  Retorna o vetor da mesma forma
        }
    }

    quant_tec++;        //  Soma um na quantidade
    tecnologies = realloc(tecnologies, quant_tec * sizeof(char *)); //  Incrementa quant_tec e realoca tecnologias com um tamanho maior
    tecnologies[quant_tec - 1] = dado.nomeTecnologiaOrigem.string;  //  Armazena de fato a tecnologia no no local
    *prt_quant_tec = quant_tec;     // Passa pro ponteiro
    return tecnologies;
}

char **testa_par(int *prt_quant_tec_par, Dados dado, char **pares)
{
    int stringConcatMaxSize = strlen(dado.nomeTecnologiaDestino.string) + strlen(dado.nomeTecnologiaOrigem.string) + 1;
    char aux[stringConcatMaxSize];
    strcpy(aux, dado.nomeTecnologiaOrigem.string);  // Copia origem na aux
    strcat(aux, dado.nomeTecnologiaDestino.string); // Concatena o destino

    int quant_tec_par = *prt_quant_tec_par;         //  Pega o ponteiro
    for (int i = 0; i < quant_tec_par; i++)
    {
        if (strcmp(pares[i], aux) == 0)             // Testa se existe
        {
            return pares;                           // Sai se existir
        }
    }

    quant_tec_par;      // soma um na quantidade
    pares = realloc(pares, quant_tec_par * sizeof(char *)); // realoca dinamicamente
    pares[quant_tec_par - 1] = malloc(strlen(aux) + 1); // Aloca memória para a nova string
    strcpy(pares[quant_tec_par - 1], aux);              // Copia o conteúdo de aux para a nova memória alocada

    *prt_quant_tec_par = quant_tec_par;                 // Passa pro ponteiro 
    return pares;
}

short int Functionality_1(const char csvArchiveName[], const char binArchiveName[])
{
    // printf("\n\n\tcsv:%s\t\tbinary:\t%s\n", csvArchiveName, binArchiveName); // nome dos arquivos usados

    FILE *csv = fopen(csvArchiveName, "r");   // buscar o csv
    FILE *bin = fopen(binArchiveName, "wb+"); // criar o bin

    if (csv == NULL || bin == NULL)
    {
        printf("\nFalha no processamento do arquivo.\n");
        return 1; // Caso o csv não seja encontrado ou o bin não criado, passa 1 DE ERRO para o file
    }

    bin = init_bin(bin); // inicializar o bin

    int proxRNN = 0; //  armazena onde está o prox RNN

    int quant_tec = 0;           //  Contado para quantidade de tecnologias
    int duplicade_quant_tec = 0; //  Contado para quantidade de tecnologias duplicadas
    char **tecnologies = NULL;   //  Inicializa um vetor que armazena ponteiros strings
    char **pares = NULL;         //  Inicializa um vetor que armazena ponteiros strings dos pares

    char headerLine[MAX_STRING_LENGTH];         //  Cria o ponteiro que armazenará a primeira linha completa
    fgets(headerLine, sizeof(headerLine), csv); //  Pular a primeira linha
    while (!feof(csv))
    {
        Dados dados;
        dados = LerRegistroCSV(csv); //  Lê o arquivo linha a linha e armazana em dados
        Escrever_Dados(bin, dados);  //  Escreve o dado no arquivo binário  
        tecnologies = testa_unico(&quant_tec, dados, tecnologies);
        pares = testa_par(&duplicade_quant_tec, dados, pares);

        // for (int i = 0; i < quant_tec; i++){printf("quant_tec:|%d|\ti:%d\t%s\n", quant_tec, i, tecnologies[i]);} // mostrar os dados

        // for (int i = 0; i < quant_tec; i++)
        // {
        //     printf("tec:\t%s", tecnologies[i]);
        // }

        free(dados.nomeTecnologiaOrigem.string);  // apaga os elementos variaveis para serem alocados novamente com seu tamanho variável
        free(dados.nomeTecnologiaDestino.string); // apaga os elementos variaveis para serem alocados novamente com seu tamanho variável
        // free(dados);
        proxRNN++;
    }
    printf("\nNumeros de tecnologia:\n\t-> Simples:\t|%d|\n\t-> Duplicado:\t|%d|\n",quant_tec,duplicade_quant_tec);                                       // mostrar os dados
    Atualizar_Cabecalho(bin, 1, 1, proxRNN); // Aqui ajustar ainda !!!!!!---

    fclose(bin); //  Fecha o arquivo binário
    fclose(csv); //  Fecha o arquivo csv

    binarioNaTela(binArchiveName);
    return 0;
}

void Recuperar_Dados(const char binArchiveName[])
{
    FILE *bin = fopen(binArchiveName, "rb"); // abrir o bin para leitura
    if (bin == NULL)
    {
        printf("\nFalha no processamento do arquivo.\n");
        return;
    }

    // Ler o cabecalho
    Cabecalho cabecalho;
    fread(&cabecalho, sizeof(Cabecalho), 1, bin);

    // Função criada para ver status
    if (cabecalho.status == '0')
    {
        printf("\nArquivo binário não está consistente.\n");
        fclose(bin);
        return;
    }

    Dados dados;
    while (fread(&dados.removido, sizeof(char), 1, bin))
    {
        if (dados.removido == '-')
        { // Se o registro não estiver removido logicamente
            fread(&dados.grupo, sizeof(int), 1, bin);
            fread(&dados.popularidade, sizeof(int), 1, bin);
            fread(&dados.peso, sizeof(int), 1, bin);

            fread(&dados.nomeTecnologiaOrigem.tamanho, sizeof(int), 1, bin);
            dados.nomeTecnologiaOrigem.string = (char *)malloc(dados.nomeTecnologiaOrigem.tamanho + 1);
            fread(dados.nomeTecnologiaOrigem.string, sizeof(char), dados.nomeTecnologiaOrigem.tamanho, bin);
            dados.nomeTecnologiaOrigem.string[dados.nomeTecnologiaOrigem.tamanho] = '\0';

            fread(&dados.nomeTecnologiaDestino.tamanho, sizeof(int), 1, bin);
            dados.nomeTecnologiaDestino.string = (char *)malloc(dados.nomeTecnologiaDestino.tamanho + 1);
            fread(dados.nomeTecnologiaDestino.string, sizeof(char), dados.nomeTecnologiaDestino.tamanho, bin);
            dados.nomeTecnologiaDestino.string[dados.nomeTecnologiaDestino.tamanho] = '\0';

            // Exibir os dados
            // printf("Grupo: %d\n", dados.grupo);
            // printf("Popularidade: %d\n", dados.popularidade);
            // printf("Peso: %d\n", dados.peso);
            // printf("Nome Tecnologia Origem: %s\n", dados.nomeTecnologiaOrigem.string);
            // printf("Nome Tecnologia Destino: %s\n", dados.nomeTecnologiaDestino.string);
            // printf("-------------------------------\n");

            // Liberar memória alocada para strings
            free(dados.nomeTecnologiaOrigem.string);
            free(dados.nomeTecnologiaDestino.string);
        }
        else
        {
            // Se o registro estiver removido logicamente, pular para o próximo registro
            fseek(bin, TAM_REGISTRO - sizeof(char), SEEK_CUR);
        }
    }

    fclose(bin);
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

    // printf("os argumentos são \t%s\t%s\t%s\n", argumento_1, argumento_2, argumento_3);  //   Ver o que está sendo lido no momento

    const char csvArchiveName[] = "tecnologia.csv";  // inserção manual do nome dos arquivos para debug
    const char binArchiveName[] = "output_file.bin"; // inserção manual do nome dos arquivos para debug

    // const char *csvArchiveName = argumento_2;
    // const char *binArchiveName = argumento_3;
    switch (decision)
    {
    case '1':
        if (Functionality_1(csvArchiveName, binArchiveName))
        {
            printf("\nFalha no processamento do arquivo.");
        };
        break;
    case '2': // Supondo que a opção 2 seja para recuperar e exibir os dados
        Recuperar_Dados(binArchiveName);
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
    printf("\n\t\tSucesso\n");                                     // apagar ao fim
    printf("\n\n-------- -------- -------- -------- -------- \n"); // apagar ao fim
    return 0;
}
