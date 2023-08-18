public class Main {
    public static void main(String[] args) throws Exception {
        float var_operador_1,var_operador_2 ;
        var_operador_1 = 10;
        var_operador_2 = 5 ;

        Operacao[] os = new Operacao[4];
        os[0] = new Adicao(var_operador_1, var_operador_2) ;
        os[1] = new Subtracao(var_operador_1, var_operador_2) ;
        os[2] = new Coeficiente(var_operador_1, var_operador_2) ;
        os[3] = new Produto(var_operador_1, var_operador_2) ;


    }
}
