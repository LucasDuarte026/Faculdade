public class Moradia {

    private String rua;
    private int numero;
    private Pessoa p;

    public Moradia(String rua, int numero, Pessoa p) {
        this.rua = rua;
        this.numero = numero;
        this.p = p;
    }

    public void imprimeDados(){
            p.mostrarDados();
            System.out.format("\n\tEndereço\nrua: %s e número: %d",rua,numero);
    
    }

}
