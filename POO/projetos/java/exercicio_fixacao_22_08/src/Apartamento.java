public class Apartamento extends Moradia {
    protected int andar;

    public Apartamento(int _andar, String _rua, int _numero, Pessoa _p) {
        super(_rua, _numero, _p);
        this.andar = _andar;
    }

    public void setAndar(int andar) {
        this.andar = andar;
    }

    public void imprimeDados(boolean flag) {
        p.mostrarDados();
        if (flag) {
            System.out.format("\n\tAtributos do apartamento:\n andar: %d e seu custo total é: %.2f\n", andar,this.calculaCustosTotais());

        } else {
            System.out.format("\n\tAtributos do apartamento:\n andar: %d\n", andar);
        }
    }

    public int getAndar() {
        return andar;
    }

    public float calculaCustosTotais() {

        return 7000;
    }
}
