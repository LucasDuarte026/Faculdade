
/*
Dados dos integrantes:

    -> Lucas Sales Duarte - 11734490
    ->
Alunos do curso de graduação de engenharia de computação
*/

#include <stdio.h>

typedef struct {
    int numRegistros;
    int status; // 1 para consistente, 0 para inconsistentes
} Cabecalho;

typedef struct {
    char nomeTecnologiaOrigem[50];
    int grupo;
} Registro;


FILE* init_bin(FILE* bin){
    Cabecalho cabecalho;
    cabecalho.numRegistros = 0; 
    cabecalho.status = 1; 

    
    fwrite(&cabecalho, sizeof(Cabecalho), 1, bin);

    return bin;
}


FILE *archive_open(const char *nameArchive)
{
    // entrada do arquivoe seu retorno em ponteiro
    FILE *file;
    file = fopen(nameArchive, "r");

    return file;
}

void printar_binario(const char *binArchiveName) {
    FILE *bin = fopen(binArchiveName, "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário.\n");
        return;
    }

    Cabecalho cabecalho;
    fread(&cabecalho, sizeof(Cabecalho), 1, bin);

    printf("Número de registros: %d\n", cabecalho.numRegistros);
    printf("Status do arquivo: %s\n", cabecalho.status == 1 ? "Consistente" : "Inconsistente");

    Registro registro;
    while (fread(&registro, sizeof(Registro), 1, bin) == 1) {
        // Imprime os campos do registro aqui
        // Exemplo:
        // printf("Nome da Tecnologia: %s\n", registro.nomeTecnologiaOrigem);
    }

    fclose(bin);
}


short int functionality_1(const char *csvArchiveName, const char *binArchiveName)
{
    FILE *csv = archive_open(csvArchiveName); // buscar o csv
    FILE *bin = fopen(binArchiveName, 'w');   // criar o bin

    if (csv == NULL || bin == NULL)
    {
        return 1; // Caso o csv não seja encontrado ou o bin não criado, passa 1 DE ERRO para o file
    }

    //  -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - --
    //  leitura de entrada de decisão:
    bin = init_bin(bin);

    int technology_number = 0;
    int even_technology_number = 0;
    

    fclose(csv);
    printar_binario(binArchiveName);
    fclose(bin);
    return 0;
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

    const char *csvArchiveName = argv[2];
    const char *binArchiveName = argv[3];
    switch (decision)
    {
    case '1':
        if (functionality_1(csvArchiveName, binArchiveName) == 1)
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
    printf("\n\n-------- -------- -------- -------- -------- \n"); // apagar ao fim
    return 0;
}
