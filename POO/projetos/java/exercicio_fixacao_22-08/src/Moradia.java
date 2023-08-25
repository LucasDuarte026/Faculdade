public abstract class Moradia {

    protected String rua;
    protected int numero;
    protected Pessoa p;

    public Moradia(String rua, int numero, Pessoa p) {
        this.rua = rua;
        this.numero = numero;
        this.p = p;
    }

    public String getRua() {
        return rua;
    }

    public int getNumero() {
        return numero;
    }

    public Pessoa getPessoa() {
        return p;
    }

    public void setRua(String rua) {
        this.rua = rua;
    }

    public void setNumero(int numero) {
        this.numero = numero;
    }

    public void setP(Pessoa p) {
        this.p = p;
    }
    public abstract float calculaCustosTotais(); 

}
