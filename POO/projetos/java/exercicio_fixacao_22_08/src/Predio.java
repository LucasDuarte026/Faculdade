public class Predio {

    private String nome;
    private Apartamento[] aps;
    private int andares;

    public Predio(Apartamento[] _aps, String nome, int andares) {
        this.nome = nome;
        this.andares = andares;
        this.aps = _aps;
    }

    public void imprimeDados() {
        System.out.format("\n  -- -- Prédio %s -- --\n e nos %d andares, contém:\n\n\n", nome, andares);
        for (Apartamento i : aps) {
            i.imprimeDados(false); // Sem mostrar os custos
        }

    }

    public void setMoradorDeAp(String _rua, int numDoAp, Pessoa _p) {
        int andar = numDoAp / 100;
        Apartamento novoMorador = new Apartamento(andar, _rua, numDoAp, _p);

        Apartamento[] aps2 = new Apartamento[aps.length + 1];
        for (int i = 0; i < aps.length; i++) {
            aps2[i] = this.aps[i];
        }
        aps2[aps.length] = novoMorador;
        aps = aps2;
    }

    public String getNome() {
        return nome;
    }

    public Apartamento[] getAps() {
        return aps;
    }

    public int getAndares() {
        return andares;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setAps(Apartamento[] aps) {
        this.aps = aps;
    }

    public void setAndares(int andares) {
        this.andares = andares;
    }

}
