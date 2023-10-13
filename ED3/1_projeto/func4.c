#include "structs.h"
#include "func4.h"
#include "func3.h"

static void pula_RRN(FILE *bin, int RRN)
{

    fseek(bin, 13, SEEK_SET); //  Aponta para o primeiro registro
    Dados dados_provisorio; //  Inicializa o dado que será só para correr acima dos outros até o RRN desejado
    int RRN_counter = 0;    //  Contador que será usado para chegar até o RRN desejado
    while (fread(&dados_provisorio.removido, sizeof(char), 1, bin) && RRN_counter < RRN) // análogo à funcionalidade 3,
    {
        if (dados_provisorio.removido == '0')
        {
            RRN_counter++;
            fread(&dados_provisorio.grupo, sizeof(int), 1, bin);
            fread(&dados_provisorio.popularidade, sizeof(int), 1, bin);
            fread(&dados_provisorio.peso, sizeof(int), 1, bin);

            fread(&dados_provisorio.nomeTecnologiaOrigem.tamanho, sizeof(int), 1, bin);
            dados_provisorio.nomeTecnologiaOrigem.string = (char *)malloc(dados_provisorio.nomeTecnologiaOrigem.tamanho + 1);
            fread(dados_provisorio.nomeTecnologiaOrigem.string, sizeof(char), dados_provisorio.nomeTecnologiaOrigem.tamanho, bin);
            dados_provisorio.nomeTecnologiaOrigem.string[dados_provisorio.nomeTecnologiaOrigem.tamanho] = '\0';

            fread(&dados_provisorio.nomeTecnologiaDestino.tamanho, sizeof(int), 1, bin);
            dados_provisorio.nomeTecnologiaDestino.string = (char *)malloc(dados_provisorio.nomeTecnologiaDestino.tamanho + 1);
            fread(dados_provisorio.nomeTecnologiaDestino.string, sizeof(char), dados_provisorio.nomeTecnologiaDestino.tamanho, bin);
            dados_provisorio.nomeTecnologiaDestino.string[dados_provisorio.nomeTecnologiaDestino.tamanho] = '\0';
            free(dados_provisorio.nomeTecnologiaOrigem.string);
            free(dados_provisorio.nomeTecnologiaDestino.string);
        }
    }
}

void functionality_4(const char binArchiveName[], const int RRN)
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

    Dados dados;

    pula_RRN(bin, RRN);

    // le tudo do registro a seguir
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
            break;
        }
    }
    if (!fread(&dados.removido, sizeof(char), 1, bin))
    {
        printf("Registro inexistente.\n");
        fclose(bin);
        return;
    }
    printa_registro(&dados);
    free(dados.nomeTecnologiaOrigem.string);
    free(dados.nomeTecnologiaDestino.string);

    fclose(bin);
    return;
}