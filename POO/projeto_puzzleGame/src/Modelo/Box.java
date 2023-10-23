package Modelo;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import Controler.Tela;
import auxiliar.Posicao;
import java.awt.Graphics;
import java.io.Serializable;

public class Box extends Personagem implements Serializable {

    public Box(String sNomeImagePNG) {
        super(sNomeImagePNG);
        this.bTransponivel = true;
        this.isBox = true;

    }

    public void autoDesenho() {
        super.autoDesenho();

    }

   

    public void move_box(Posicao anterior) {

        
    }
}
