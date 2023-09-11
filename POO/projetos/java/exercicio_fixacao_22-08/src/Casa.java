public class Casa extends Moradia {
    private int metragem;

    public Casa(int _metragem, String _rua, int _numero, Pessoa _p) {
        super(_rua, _numero, _p);
        this.metragem = _metragem;

    }


    
    public void imprimeDados(boolean flag) {
        p.mostrarDados();
        if (flag) {
            System.out.format("\n\tAtributos da casa:\n metragem da casa: %d e o custo é %.2f\n", metragem,this.calculaCustosTotais());
            this.calculaCustosTotais();
            
        } else {
            System.out.format("\n\tAtributos da casa:\n metragem da casa: %d e o custo é %.2f\n", metragem,this.calculaCustosTotais());

        }
    }
    
    public void imprimeDados() {
        p.mostrarDados();
        System.out.format("\n\tEndereço\nrua: %s e número: %d", rua, numero);

    }
    public float calculaCustosTotais() {

        return 5000;
    }

}