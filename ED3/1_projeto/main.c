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
    {
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
        char removido;
        int grupo;
        int popularidade;
        int peso;
        StringVariavel nomeTecnologiaOrigem;
        StringVariavel nomeTecnologiaDestino;
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

void Atualizar_Cabecalho(FILE *bin, int nroTecnologia, int nroParesTecnologia, int prox)
{
    Cabecalho cabecalho;
    fseek(bin, 0, SEEK_SET);
    fread(&cabecalho, sizeof(Cabecalho), 1, bin);

    cabecalho.status = '1';
    cabecalho.proxRRN = prox;
    cabecalho.nroTecnologia = nroTecnologia;
    cabecalho.nroParesTecnologia = nroParesTecnologia;

    fseek(bin, 0, SEEK_SET);
    fwrite(&cabecalho, sizeof(Cabecalho), 1, bin);
}

void Escrever_Dados(FILE *bin, Dados dados)
{
    fwrite(&dados.removido, sizeof(char), 1, bin);
    fwrite(&dados.grupo, sizeof(int), 1, bin);
    fwrite(&dados.popularidade, sizeof(int), 1, bin);
    fwrite(&dados.peso, sizeof(int), 1, bin);
    
    fwrite(&dados.nomeTecnologiaOrigem.tamanho, sizeof(int), 1, bin);
    fwrite(dados.nomeTecnologiaOrigem.string, sizeof(char), dados.nomeTecnologiaOrigem.tamanho, bin);
    
    fwrite(&dados.nomeTecnologiaDestino.tamanho, sizeof(int), 1, bin);
    fwrite(dados.nomeTecnologiaDestino.string, sizeof(char), dados.nomeTecnologiaDestino.tamanho, bin);

    int tamanhoAtual = sizeof(char) + 3*sizeof(int) + 2*sizeof(int) + dados.nomeTecnologiaOrigem.tamanho + dados.nomeTecnologiaDestino.tamanho;
    
    // Calcule a quantidade de lixo
    int quantidadeLixo = TAM_REGISTRO - tamanhoAtual;
    
    // Escreva o lixo no arquivo binário
    for (int i = 0; i < quantidadeLixo; i++) {
        fwrite(LIXO, sizeof(char), 1, bin);
    }
}


Dados LerRegistroCSV(FILE *csv)
{
    Dados dados;
    dados.removido = '-';
    dados.nomeTecnologiaOrigem.string = NULL;
    dados.nomeTecnologiaOrigem.tamanho = 0;
    dados.nomeTecnologiaDestino.string = NULL;
    dados.nomeTecnologiaDestino.tamanho = 0;

    char bufferOrigem[MAX_STRING_LENGTH];
    char bufferDestino[MAX_STRING_LENGTH];

    if (fscanf(csv, " %[^,],%d,%d, %[^,],%d", bufferOrigem, &dados.grupo, &dados.popularidade, bufferDestino, &dados.peso) == 5)
    {
        dados.nomeTecnologiaOrigem.tamanho = strlen(bufferOrigem);
        dados.nomeTecnologiaOrigem.string = strdup(bufferOrigem);

        dados.nomeTecnologiaDestino.tamanho = strlen(bufferDestino);
        dados.nomeTecnologiaDestino.string = strdup(bufferDestino);
        printf("%s,%d,%d,%s,%d\n",  dados.nomeTecnologiaOrigem.string, dados.grupo, dados.popularidade, dados.nomeTecnologiaDestino.string, dados.peso);
    }

    return dados;
}

    void functionality_2(const char binArchiveName[]) {
        FILE *bin = fopen(binArchiveName, "rb"); // abrir o bin para leitura
        if (bin == NULL) {
            printf("\nFalha no processamento do arquivo.\n");
            return;
        }

        //Ler o cabecalho
        Cabecalho cabecalho;
        fread(&cabecalho, sizeof(Cabecalho), 1, bin);

        //Função criada para ver status
        if (cabecalho.status == '0') {
            printf("\nArquivo binário não está consistente.\n");
            fclose(bin);
            return;
        }

        Dados dados;
        while (fread(&dados.removido, sizeof(char), 1, bin)) {
        if (dados.removido == '-') { // Se o registro não estiver removido logicamente
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
            printf("Grupo: %d\n", dados.grupo);
            printf("Popularidade: %d\n", dados.popularidade);
            printf("Peso: %d\n", dados.peso);
            printf("Nome Tecnologia Origem: %s\n", dados.nomeTecnologiaOrigem.string);
            printf("Nome Tecnologia Destino: %s\n", dados.nomeTecnologiaDestino.string);
            printf("-------------------------------\n");

            // Liberar memória alocada para strings
            free(dados.nomeTecnologiaOrigem.string);
            free(dados.nomeTecnologiaDestino.string);
        } else {
            // Se o registro estiver removido logicamente, pular para o próximo registro
            fseek(bin, TAM_REGISTRO - sizeof(char), SEEK_CUR);
        }
    }

    fclose(bin);
}

    short int functionality_1(const char csvArchiveName[], const char binArchiveName[])
{
    printf("\n\n\tcsv:%s\t\tbinary:\t%s\n", csvArchiveName, binArchiveName);
    FILE *csv = fopen(csvArchiveName, "r");
    FILE *bin = fopen(binArchiveName, "wb+");

    if (csv == NULL || bin == NULL)
    {
        printf("\nainda nada\n");
        return 1;
    }

    bin = init_bin(bin);

    Dados dados;

    char headerLine[MAX_STRING_LENGTH];
    fgets(headerLine, sizeof(headerLine), csv);

    int nroTecnologia = 0;
    int nroParesTecnologia = 0;
    int proxRRN = 0;

    while (!feof(csv))
    {
        dados = LerRegistroCSV(csv);
        Escrever_Dados(bin, dados);

        nroTecnologia++;
        nroParesTecnologia++;

        free(dados.nomeTecnologiaOrigem.string);
        free(dados.nomeTecnologiaDestino.string);
    }

    Atualizar_Cabecalho(bin, nroTecnologia, nroParesTecnologia, proxRRN);
    fclose(csv);
    fclose(bin);

    binarioNaTela(binArchiveName);
    return 0;
}

    void functionality_3(const char binArchiveName[], int n) {
    FILE *bin = fopen(binArchiveName, "rb");
    if (bin == NULL) {
        printf("\nFalha no processamento do arquivo.\n");
        return;
    }

    Cabecalho cabecalho;
    fread(&cabecalho, sizeof(Cabecalho), 1, bin);

    if (cabecalho.status == '0') {
        printf("\nArquivo binário não está consistente.\n");
        fclose(bin);
        return;
    }

    for (int i = 0; i < n; i++) {
        char nomeCampo[MAX_STRING_LENGTH];
        char valorCampo[MAX_STRING_LENGTH];
        scanf("%s", nomeCampo);
        scan_quote_string(valorCampo);

        int found = 0;
        Dados dados;

        fseek(bin, sizeof(Cabecalho), SEEK_SET);

        while (fread(&dados.removido, sizeof(char), 1, bin)) {
            if (dados.removido == '-') {
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

                if ((strcmp(nomeCampo, "nomeTecnologiaOrigem") == 0 && strcmp(valorCampo, dados.nomeTecnologiaOrigem.string) == 0) ||
                    (strcmp(nomeCampo, "nomeTecnologiaDestino") == 0 && strcmp(valorCampo, dados.nomeTecnologiaDestino.string) == 0) ||
                    (strcmp(nomeCampo, "grupo") == 0 && atoi(valorCampo) == dados.grupo) ||
                    (strcmp(nomeCampo, "popularidade") == 0 && atoi(valorCampo) == dados.popularidade) ||
                    (strcmp(nomeCampo, "peso") == 0 && atoi(valorCampo) == dados.peso)) {
                    printf("%s,%d,%d,%s,%d\n", dados.nomeTecnologiaOrigem.string, dados.grupo, dados.popularidade, dados.nomeTecnologiaDestino.string, dados.peso);
                    found = 1;
                }

                free(dados.nomeTecnologiaOrigem.string);
                free(dados.nomeTecnologiaDestino.string);
            } else {
                fseek(bin, TAM_REGISTRO - sizeof(char), SEEK_CUR);
            }
        }

        if (!found) {
            printf("Registro inexistente.\n");
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

        printf("os argumentos são \t%s\t%s\t%s\n", argumento_1, argumento_2, argumento_3);

        const char csvArchiveName[] = "tecnologia_curtoTESTE.csv";  // inserção manual do nome dos arquivos para debug
        const char binArchiveName[] = "output_file.bin"; // inserção manual do nome dos arquivos para debug

        // const char *csvArchiveName = argumento_2;
        // const char *binArchiveName = argumento_3;
        switch (decision)
        {
        case '1':
            if (functionality_1(csvArchiveName, binArchiveName))
            {
                printf("\nFalha no processamento do arquivo.");
            };
            break;
      case '2': // Supondo que a opção 2 seja para recuperar e exibir os dados
            functionality_2(binArchiveName);
            break;

        case '3':
            int n;
            scanf("%d", &n);
            functionality_3(binArchiveName, n);
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
