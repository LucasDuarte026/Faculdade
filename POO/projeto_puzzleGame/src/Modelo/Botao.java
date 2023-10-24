package Modelo;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import Controler.Tela;
import java.awt.Graphics;
import java.io.Serializable;

public class Botao extends Personagem implements Serializable{
    
    public Botao(String sNomeImagePNG) {
        super(sNomeImagePNG);
        this.bTransponivel = true;
        this.isBotao=true;
    }

    public void autoDesenho() {
        super.autoDesenho();
    }    
}
