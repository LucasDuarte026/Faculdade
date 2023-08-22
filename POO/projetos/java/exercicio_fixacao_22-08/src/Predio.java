public class Predio  {
    
    private String nome;
    private Apartamento[] aps;
    private int andares;
    public Predio(Apartamento[] _aps, String nome, int andares) {
        this.nome = nome;
        this.andares = andares;
        this.aps = _aps;
    }
    
    public void mostrarDados() {
        System.out.format("\n  -- -- prédio %s -- --\n e nos %d andares, contém:", nome, andares);
        for(Apartamento i : aps){
            i.mostrarDados();
        }
        
    }
    
}
