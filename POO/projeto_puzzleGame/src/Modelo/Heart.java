package Modelo;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import Controler.Tela;
import java.awt.Graphics;
import java.io.Serializable;

public class Heart extends Personagem implements Serializable {


    public Heart(String sNomeImagePNG) {
        super(sNomeImagePNG);
        this.bTransponivel = true;
        this.isHeart = true;
    }


    public void autoDesenho() {
        super.autoDesenho();

    }
}
