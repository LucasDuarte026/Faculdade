#include <stdio.h>
#include <stdlib.h>

/*MAN LEMBRANDO QUE É SÓ O ESBOÇO, DPS TEM Q COLOCAR OS .h da vida 
etc, mas ja deixei montado pra vc meu lindo DPS APAGA ISSO TB. TAMBEM AS MODIFICAÇÕES NECE
SSARIAS PARA FUNFAR, PQ NAO FAÇO IDEIA, MAS É BOM IR TENDO O ARQUVI NE*/

// Estruturas de dados
typedef struct {
    // Defina os campos do registro aqui
    // aqui vamo colocar os krl q ela pedir
} Registro;

// Protótipos de funções charlos :0
void obterDadosDeArquivo(char *nomeArquivo);
void gerarArquivoBinario(Registro *registros, int numRegistros, char *nomeArquivoBinario);
Registro *lerArquivoBinario(char *nomeArquivoBinario, int *numRegistros);
void buscarRegistro(Registro *registros, int numRegistros, char *chaveBusca);

int main() {
    int opcao;
    char nomeArquivo[100];
    Registro *registros = NULL;
    int numRegistros = 0;

    printf("Digite a opção desejada:\n");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1: // Suponha que 1 seja a opção para obter dados de um arquivo
            printf("Digite o nome do arquivo de entrada:\n");
            scanf("%s", nomeArquivo);
            obterDadosDeArquivo(nomeArquivo);
            break;
        case 2: // Suponha que 2 seja a opção para gerar arquivo binário
            // Implementação da funcionalidade aqui
            break;
        // Adicione mais cases para outras funcionalidades
        default:
            printf("Opção inválida!\n");
            break;
    }

    return 0;
}

// A partir daqui para baixo é as funções, modularizadas, ainda precisa adicionar mais
// só que essas são as "principais".
void obterDadosDeArquivo(char *nomeArquivo) {
    
}

void gerarArquivoBinario(Registro *registros, int numRegistros, char *nomeArquivoBinario) {
    
}
Registro *lerArquivoBinario(char *nomeArquivoBinario, int *numRegistros) {
    
    return NULL;
}

void buscarRegistro(Registro *registros, int numRegistros, char *chaveBusca) {
    //Vou ver usar os algoritmos de busca q fizemos em ED2!!!!
       
       /* for (int i = 0; i < numRegistros; i++) {
        if (strcmp(registros[i].nomeTecnologiaOrigem, chaveBusca) == 0) {
            printf("Registro encontrado: %s\n", registros[i].nomeTecnologiaOrigem);
            // Você pode imprimir ou processar outros campos do registro aqui
            return;
        }
    }
    printf("Registro não encontrado.\n");
    */
    
}