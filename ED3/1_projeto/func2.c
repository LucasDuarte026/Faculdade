#include "structs.h"
#include "func2.h"

    //  Declaração da functionality_2
void functionality_2(const char binArchiveName[])
{
    FILE *bin = fopen(binArchiveName, "rb+"); // abrir o bin para leitura
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
    int registros_lidos = 0;
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
            printf("Grupo: %d\n", dados.grupo);
            printf("Popularidade: %d\n", dados.popularidade);
            printf("Peso: %d\n", dados.peso);
            printf("Nome Tecnologia Origem: %s\n", dados.nomeTecnologiaOrigem.string);
            printf("Nome Tecnologia Destino: %s\n", dados.nomeTecnologiaDestino.string);
            printf("-------------------------------\n");
            registros_lidos++;

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

    if (registros_lidos == 0)
    {
        printf("Nenhum registro válido encontrado no arquivo.\n");
    }

    fclose(bin);
}
