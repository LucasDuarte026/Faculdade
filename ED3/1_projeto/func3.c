#include "structs.h"
#include "func3.h"
#include "func1.h" //   Precisa do scan_quote_string()

void functionality_3old(const char binArchiveName[], int n)
{
    FILE *bin = fopen(binArchiveName, "rb");
    if (bin == NULL)
    {
        printf("\nFalha no processamento do arquivo.\n");
        return;
    }

    Cabecalho cabecalho;
    fread(&cabecalho.status, sizeof(char), 1, bin);
    fread(&cabecalho.proxRRN, sizeof(int), 1, bin);
    fread(&cabecalho.nroTecnologia, sizeof(int), 1, bin);
    fread(&cabecalho.nroParesTecnologia, sizeof(int), 1, bin);

    if (cabecalho.status == '0')
    {
        printf("\nArquivo binário não está consistente.\n");
        fclose(bin);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        char nomeCampo[MAX_STRING_LENGTH];
        char valorCampo[MAX_STRING_LENGTH];
        scanf("%s", nomeCampo);
        scan_quote_string(valorCampo);

        int found = 0;
        Dados dados;

        fseek(bin, sizeof(Cabecalho), SEEK_SET);

        while (fread(&dados.removido, sizeof(char), 1, bin))
        {
            if (dados.removido == '0')
            {
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
                    (strcmp(nomeCampo, "peso") == 0 && atoi(valorCampo) == dados.peso))
                {
                    printf("%s,%d,%d,%s,%d\n", dados.nomeTecnologiaOrigem.string, dados.grupo, dados.popularidade, dados.nomeTecnologiaDestino.string, dados.peso);
                    found = 1;
                }

                free(dados.nomeTecnologiaOrigem.string);
                free(dados.nomeTecnologiaDestino.string);
            }
            else
            {
                fseek(bin, TAM_REGISTRO, SEEK_CUR);
            }
        }

        if (!found)
        {
            printf("Registro inexistente.\n");
        }
    }

    fclose(bin);
}

void printa_registro(Dados *dados)
{
    // nomeTecn:ologiaOrigem,grupo,popularidade,nomeTecnologiaDestino,peso
    // Mostra o nome da origem
    if (dados->nomeTecnologiaOrigem.tamanho == 0)
    {
        printf("NULO, ");
    }
    else
    {
        printf("%s, ", dados->nomeTecnologiaOrigem.string);
    }

    // Mostra o nome do grupo
    if (dados->grupo == -1)
    {
        printf("NULO, ");
    }
    else
    {
        printf("%d, ", dados->grupo);
    }
    // Mostra o nome do grupo
    if (dados->popularidade == -1)
    {
        printf("NULO, ");
    }
    else
    {
        printf("%d, ", dados->popularidade);
    }

    // Mostra o nome da destino
    if (dados->nomeTecnologiaDestino.tamanho == 0)
    {
        printf("NULO, ");
    }
    else
    {
        printf("%s, ", dados->nomeTecnologiaDestino.string);
    }

    // Mostra o nome do grupo
    if (dados->peso == -1)
    {
        printf("NULO");
    }
    else
    {
        printf("%d", dados->peso);
    }
    printf("\n");
}

void functionality_3(const char binArchiveName[], int n)
{
    FILE *bin = fopen(binArchiveName, "rb");
    if (bin == NULL)
    {
        printf("\nFalha no processamento do arquivo.\n");
        return;
    }

    Cabecalho cabecalho;
    fread(&cabecalho, sizeof(Cabecalho), 1, bin);

    if (cabecalho.status == '0')
    {
        printf("Falha no processamento do arquivo.\r\n");
        fclose(bin);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        char nomeCampo[MAX_STRING_LENGTH];
        char valorCampo[MAX_STRING_LENGTH];
        scanf("%s", nomeCampo);
        scan_quote_string(valorCampo);

        int found = 0;
        Dados dados;

        fseek(bin,13, SEEK_SET);

        while (fread(&dados.removido, sizeof(char), 1, bin))
        {
            if (dados.removido == '0')
            {
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
                    (strcmp(nomeCampo, "peso") == 0 && atoi(valorCampo) == dados.peso))
                {
                    printa_registro(&dados);
                    // printf("%s, %d, %d, %s, %d\n",  dados.nomeTecnologiaOrigem.string, dados.grupo, dados.popularidade, dados.nomeTecnologiaDestino.string, dados.peso);
                    found = 1;
                }

                free(dados.nomeTecnologiaOrigem.string);
                free(dados.nomeTecnologiaDestino.string);
            }
            else
            {
                // fseek(bin, TAM_REGISTRO, SEEK_CUR);
            }
        }

        if (!found)
        {
            printf("Registro inexistente.\n");
        }
    }

    fclose(bin);
}