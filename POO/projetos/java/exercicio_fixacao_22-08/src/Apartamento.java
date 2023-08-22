public class Apartamento {
    private int andar;
    private Moradia m;

    public Apartamento(int andar, Moradia m2) {
        this.andar = andar;
        this.m = m2;
    }


    public void mostrarDados() {
        m.imprimeDados();
        System.out.format("\n\tAtributos do apartamento:\n andar: %d\n", andar);

    }
}
