package Modelo;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import Controler.Tela;
import java.awt.Graphics;
import java.io.Serializable;

public class Key extends Personagem implements Serializable {

    public Key(String sNomeImagePNG) {
        super(sNomeImagePNG);
        this.bTransponivel = true;
        this.isKey = true;
    }

    public void autoDesenho() {
        super.autoDesenho();

    }
}
