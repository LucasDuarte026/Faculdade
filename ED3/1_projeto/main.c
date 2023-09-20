
/*
Dados dos integrantes:

    -> Lucas Sales Duarte - 11734490
    -> João Victor de Almeida - 13695424
Alunos do curso de graduação de engenharia de computação
*/
#include <stdio.h>

#define LIXO "$"
#define TAM_REGISTRO_FIXO 21
#define TAM_REGISTRO 76



typedef struct main
{
    //13 bytes em status e 4 bytes no resto
    char status; 
    int proxRRN;
    int nroTecnologia;
    int nroParesTecnologia;
}Cabecalho;

typedef struct{

    int tamanho;
    char* string;

}StringVariavel;

typedef struct{
    
    char removido;

    int grupo;
    int popuralidade;
    //Complementar, nao consegui acompanhar ... 

}aaaa;

FILE* init_bin(FILE* bin){

    unsigned char *data = "lucas 11 12 15"; 
    for (int i = 0; i < sizeof(data); i++) {
        fwrite(&data[i], sizeof(data[i]), 1, bin);
    }

    return bin;
}
FILE *archive_open(const char *nameArchive)
{
    // entrada do arquivoe seu retorno em ponteiro
    FILE *file;
    file = fopen(nameArchive, "r");

    return file;
}

void printarRNN(FILE* bin,int RNN){


    unsigned char byte;
    while (fread(&byte, sizeof(byte), 1, bin) == 1) {
        printf("Byte lido: %c\n", byte);
    }


}

void printar_binario(FILE* bin)
{
    int RNN = 3;
    printarRNN(bin,RNN);
}

short int functionality_1(const char *csvArchiveName, const char *binArchiveName)
{
    FILE *csv = archive_open(csvArchiveName); // buscar o csv
    FILE *bin = fopen(binArchiveName, "wb");   // criar o bin

    if (csv == NULL || bin == NULL)
    {
        return 1; // Caso o csv não seja encontrado ou o bin não criado, passa 1 DE ERRO para o file
    }

    //  -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - --
    //  leitura de entrada de decisão:
    bin = init_bin(bin);
    fclose(bin);

    bin = fopen(binArchiveName, "rb");   // abrir no modo leitura

    int technology_number = 0;
    int even_technology_number = 0;
    

    fclose(csv);
    // printar_binario(bin);
    printarRNN(bin,0);
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

    // const char *csvArchiveName = argv[2];
    // const char *binArchiveName = argv[3];

    const char *csvArchiveName = "stack_network_links.csv";
    const char *binArchiveName = "output_file.bin";

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
