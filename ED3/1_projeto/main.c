
/*
Dados dos integrantes:

    -> Lucas Sales Duarte - 11734490
    ->
Alunos do curso de graduação de engenharia de computação
*/

#include <stdio.h>

int main(int argc, char const *argv[])
{

    printf("\n-------- -------- -------- -------- -------- \n\n"); // apagar ao fim

    
    printf("\targc: %d\n", argc);
    //  leitura de entrada de decisão:

    const char decision = *argv[1]; // recebe a decisão

    if (decision != '1' && decision != '2' && decision != '3' && decision != '4')
    {
        printf("\n\t -> Erro de decisão\n"); // caso a escolha n seja válida
        return 1;
    } 


    const char *csvArchiveName = argv[2] ;
    const char *binArchiveName = argv[3] ;
    printf("\n%s", csvArchiveName);
    printf("\n%s", binArchiveName);

    //  -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- 
    // primeira etapa é criar o arquivo binário:

    // fopen






    //  -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- -- - -- 
    printf("\n\n-------- -------- -------- -------- -------- \n"); // apagar ao fim
    return 0;
}
