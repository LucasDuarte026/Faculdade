package Modelo;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import Controler.Tela;
import java.awt.Graphics;
import java.io.Serializable;

public class Seta extends Personagem implements Serializable{
    
    public Seta(String sNomeImagePNG) {
        super(sNomeImagePNG);
        this.bTransponivel = true;
    }

    public void autoDesenho() {
        super.autoDesenho();
    }    
}
