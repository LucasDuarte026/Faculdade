public class Adicao extends Operacao {

    public Adicao(float operador_1, float operador_2) {
        super(operador_1, operador_2);
    }
    public float operar(){
        float result = this.operador_1+this.operador_2;
        return result;

    }
}
