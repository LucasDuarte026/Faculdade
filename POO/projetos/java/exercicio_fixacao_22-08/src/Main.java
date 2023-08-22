public class Main {

    public static void main(String[] args) {

        Pessoa p1 = new Pessoa("Lucas Sales Duarte", "47431267894", "5793306021");
        Pessoa p2 = new Pessoa("João Victor", "47741286", "44562154653");

        Moradia m1 = new Moradia("adolfo cata", 601, p1);
        Moradia m2 = new Moradia("são Sebastião", 505, p2);
        // m1.imprimeDados();

        // Casa c1 = new Casa(500,m1);
        // Casa c2 = new Casa(400,m2);

        Apartamento a1 = new Apartamento(5,m1);
        Apartamento a2 = new Apartamento(2,m2);
        Apartamento aps[] = {a1,a2};

        Predio predio1 = new Predio(aps,"Alvares",6);
        predio1.mostrarDados();
        // c1.mostrarDados();
        // c2.mostrarDados();


        System.out.println("\n");
    }

}
