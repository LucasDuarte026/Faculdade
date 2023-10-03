#include "structs.h"
#include "func1.h"




    //  Em static estão as funções não chamadas fora de functionality_1
static void readline(char *string)
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

static void binarioNaTela(const char *nomeArquivoBinario)
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

static FILE *init_bin(FILE *bin)
{
    Cabecalho cabecalho;
    cabecalho.status = '0';
    cabecalho.proxRRN = 0;
    cabecalho.nroParesTecnologia = 0;
    cabecalho.nroTecnologia =0;

    fseek(bin, 0, SEEK_SET); // volta para o inicio
    fwrite(&cabecalho, sizeof(Cabecalho), 1, bin);

    return bin;
}

static void Atualizar_Cabecalho(FILE *bin, char status,int nroTecnologia, int nroParesTecnologia, int prox)
{
    Cabecalho cabecalho;
    cabecalho.status = status;
    cabecalho.proxRRN = prox;
    cabecalho.nroTecnologia = nroTecnologia;
    cabecalho.nroParesTecnologia = nroParesTecnologia;

    fseek(bin, 0, SEEK_SET); // volta para o inicio
    fwrite(&cabecalho, sizeof(Cabecalho), 1, bin);
}

static void Escrever_Dados(FILE *bin, Dados dados)
{
    fwrite(&dados.removido, sizeof(char), 1, bin);
    fwrite(&dados.grupo, sizeof(int), 1, bin);
    fwrite(&dados.popularidade, sizeof(int), 1, bin);
    fwrite(&dados.peso, sizeof(int), 1, bin);

    fwrite(&dados.nomeTecnologiaOrigem.tamanho, sizeof(int), 1, bin);
    fwrite(dados.nomeTecnologiaOrigem.string, sizeof(char), dados.nomeTecnologiaOrigem.tamanho, bin);

    fwrite(&dados.nomeTecnologiaDestino.tamanho, sizeof(int), 1, bin);
    fwrite(dados.nomeTecnologiaDestino.string, sizeof(char), dados.nomeTecnologiaDestino.tamanho, bin);

    int tamanhoAtual = sizeof(char) + 3 * sizeof(int) + 2 * sizeof(int) + dados.nomeTecnologiaOrigem.tamanho + dados.nomeTecnologiaDestino.tamanho;

    // Calcule a quantidade de lixo
    int quantidadeLixo = TAM_REGISTRO - tamanhoAtual;

    // Escreva o lixo no arquivo binário
    for (int i = 0; i < quantidadeLixo; i++)
    {
        fwrite(LIXO, sizeof(char), 1, bin);
    }
}

static Dados LerRegistroCSV(FILE *csv)
{ // le o registro
    Dados dados;
    dados.removido = NAO_REMOVIDO;
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

static char **testa_unico(int *prt_quant_tec, Dados dado, char **tecnologies)
{
    int _quant = *prt_quant_tec;
    int flag = 0;

    // Verifica se dado.nomeTecnologiaOrigem.string já existe em tecnologies
    for (int i = 0; i < *prt_quant_tec; i++)
    {
        if (strcmp(dado.nomeTecnologiaOrigem.string, tecnologies[i]) == 0)
        {
            flag = 1; // Tecnologia já existe
            break;
        }
    }

    if (!flag)
    {
        _quant++;
        tecnologies = realloc(tecnologies, _quant * sizeof(char *));
        tecnologies[_quant - 1] = strdup(dado.nomeTecnologiaOrigem.string);

        *prt_quant_tec = _quant;
    }

    return tecnologies;
}

static char **testa_par(int *prt_quant_tec_par, Dados dado, char **pares)
{
    int stringConcatMaxSize = strlen(dado.nomeTecnologiaDestino.string) + strlen(dado.nomeTecnologiaOrigem.string) + 1;
    char aux[stringConcatMaxSize];
    strcpy(aux, dado.nomeTecnologiaOrigem.string);  // Copia origem na aux
    strcat(aux, dado.nomeTecnologiaDestino.string); // Concatena o destino

    int quant_tec_par = *prt_quant_tec_par; //  Pega o ponteiro
    for (int i = 0; i < quant_tec_par; i++)
    {
        if (strcmp(pares[i], aux) == 0) // Testa se existe
        {
            return pares; // Sai se existir
        }
    }

    quant_tec_par++;                                        // soma um na quantidade
    pares = realloc(pares, quant_tec_par * sizeof(char *)); // realoca dinamicamente
    pares[quant_tec_par - 1] = malloc(strlen(aux) + 1);     // Aloca memória para a nova string
    strcpy(pares[quant_tec_par - 1], aux);                  // Copia o conteúdo de aux para a nova memória alocada

    *prt_quant_tec_par = quant_tec_par; // Passa pro ponteiro
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

    int proxRNN = 1; //  armazena onde está o prox RNN

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
    printf("\nNumeros de tecnologia:\n\t-> Simples:\t|%d|\n\t-> Duplicado:\t|%d|\n", quant_tec, duplicade_quant_tec); // mostrar os dados
    Atualizar_Cabecalho(bin, '1',quant_tec, duplicade_quant_tec, proxRNN);                                                                          // Aqui ajustar ainda !!!!!!---

    fclose(bin); //  Fecha o arquivo binário
    fclose(csv); //  Fecha o arquivo csv

    binarioNaTela(binArchiveName);
    return 0;
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