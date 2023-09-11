public class Main {

    public static void main(String[] args) {

    // 1
        //  a)
        Pessoa p1 = new Pessoa("Lucas Sales Duarte", "47431267894", "5793306021");
        Pessoa p2 = new Pessoa("João Victor", "47741286", "44562154653");

        //  B)
        System.out.format("\t\n1)\n\tPessoa 1: %s do cpf: %s e rg: %s\n",p1.getName(),p1.getCPF(),p1.getRG());
        System.out.format("\tPessoa 2: %s do cpf: %s e rg: %s\n",p2.getName(),p2.getCPF(),p2.getRG());
    
    // 2 
        // a e b
        

        Casa c1 = new Casa(500,"Adolfo catani", 601, p1);
        Casa c2 = new Casa(400,"São Sebastião", 505, p2);
        c1.imprimeDados(true);
        c2.imprimeDados(true);
    //  3
        // a e b
        Pessoa p3 = new Pessoa("Daniel FIlho", "444568132", "879312798");
        Pessoa p4 = new Pessoa("Manoel Thomaz Gama da Silva Neto", "798132795", "321898461");

        Apartamento a1 = new Apartamento(5,"Adolfo catani", 003, p1);
        Apartamento a2 = new Apartamento(2,"Adolfo catani", 602, p2);
        Apartamento a3 = new Apartamento(5,"Adolfo catani", 203, p3);
        Apartamento a4 = new Apartamento(2,"Adolfo catani", 105, p4);

        // c
        System.out.println("\n 3 -> C)");
        Apartamento aps[] = {a1,a2,a3,a4};
        for(Apartamento ap: aps){
            ap.imprimeDados(true);
        }

    // 4)
        // a)
        System.out.println("\n\n 4 -> a)");
        
        Predio predio_alvares = new Predio(aps,"Alvares",6);
        predio_alvares.imprimeDados();
        
        // b)
        System.out.println("\n\n 4 -> b) e c)");
        Pessoa p5 = new Pessoa("João Marcelo bataglini", "789132132", "741582396");

        predio_alvares.setMoradorDeAp( "Adolfo catani", 805, p5);
        predio_alvares.imprimeDados();

        System.out.println("\n");
    }
    // 5)
        // a)       está faltando o 5

}
