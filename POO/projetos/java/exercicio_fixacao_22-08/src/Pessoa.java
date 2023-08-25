public class Pessoa {
    private String nome;
    private String cpf;
    private String rg;

    public Pessoa(String _nome, String _cpf, String _rg) {
        this.nome = _nome;
        this.cpf = _cpf;
        this.rg = _rg;

    }

    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");
    }

    public void setNome(String _name) {
        this.nome = _name;
    
        System.out.format("\nNovo nome é %s",this.nome);
    }
    public void setCPF(String _cpf) {
        this.cpf = _cpf;
    
        System.out.format("\nNovo cpf é %s",this.cpf);
    }
    public void setRG(String _rg) {
        this.rg = _rg;
    
        System.out.format("\nNovo rg é %s",this.rg);
    }
    public String getName(){
        return this.nome;
    }
    public String getCPF(){
        return this.cpf;
    }
    public String getRG(){
        return this.rg;
    }

    public void mostrarDados() {
    
        System.out.format("\n\t -- -- Morador -- -- \nNome: %s",this.nome);
        System.out.format("\nCPF: %s",this.cpf);
        System.out.format("\nRG: %s",this.rg);
    }}
