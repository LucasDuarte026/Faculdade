/*
 *   Dados dos integrantes:
 *
 *   -> Lucas Sales Duarte - 11734490
 *   -> João Victor de Almeida - 13695424
 *   Alunos do curso de graduação de engenharia de computação
 */

//  inserir bibliotecas com as funções locais
#include "structs.h"
#include "func1.h"
#include "func2.h"
#include "func3.h"
#include "func4.h"


int main(int argc, char const *argv[])
{

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
    // const char *argumento_4 = argv[4];
    // const char *argumento_5 = argv[5];

    // printf("os argumentos são \t%s\t%s\t%s\n", argumento_1, argumento_2, argumento_3);  //   Ver o que está sendo lido no momento

    // const char csvArchiveName[] = "dados1.csv";  // inserção manual do nome dos arquivos para debug
    // const char binArchiveName[] = "output_file.bin"; // inserção manual do nome dos arquivos para debug

    const char *csvArchiveName;
    const char *binArchiveName;

    int n;
    int RRN;
    switch (decision)
    {
    case '1':
        csvArchiveName = argumento_2;
        binArchiveName = argumento_3;
        // csvArchiveName = "dados1.csv";  // inserção manual do nome dos arquivos para debug
        // binArchiveName = "dados1.bin"; // inserção manual do nome dos arquivos para debug
        if (Functionality_1(csvArchiveName, binArchiveName))
        {
            printf("\nFalha no processamento do arquivo.");
        };
        break;
    case '2': // Supondo que a opção 2 seja para recuperar e exibir os dados
        binArchiveName = argumento_2;
        functionality_2(binArchiveName);
        break;

    case '3':
        // printf("tamanho cabcalho:\t|%ld|\n",sizeof(Cabecalho)); // teste para averiguar o tamanho do cabecalho no inicio do arquivo
        n = argumento_3[0] - 48;
        binArchiveName = argumento_2;

        functionality_3(binArchiveName, n);
        break;
    case '4':
        binArchiveName = argumento_2;
        RRN = atoi(argumento_3);
        functionality_4(binArchiveName, RRN);
        break;
    default:
        break;
    }

    //  -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - --


    return 0;
}
