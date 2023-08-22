public class Casa {
    private int metragem;
    private Moradia m;



    public Casa(int metragem, Moradia m) {
        this.metragem = metragem;
        this.m = m;
    }


    public void mostrarDados() {
        m.imprimeDados();
        System.out.format("\n\tAtributos da casa:\n metragem da casa: %d\n", metragem);

    }
}