package Modelo;

import java.io.Serializable;
import java.util.ArrayList;

public class SalvaDado implements Serializable {
    private ArrayList<Personagem> personagens;
    private int valorNumerico;

    public SalvaDado(ArrayList<Personagem> personagens, int valorNumerico) {
        this.personagens = personagens;
        this.valorNumerico = valorNumerico;
    }

    public ArrayList<Personagem> getPersonagens() {
        return personagens;
    }

    public int getValorNumerico() {
        return valorNumerico;
    }
}

