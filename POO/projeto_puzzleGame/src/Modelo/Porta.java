package Modelo;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import Controler.Tela;
import auxiliar.Posicao;
import java.awt.Graphics;
import java.io.Serializable;

public class Porta extends Personagem implements Serializable {

    public Porta(String sNomeImagePNG) {
        super(sNomeImagePNG);
        this.bTransponivel = false;
        this.isPorta = true;

    }

    public void autoDesenho() {
        super.autoDesenho();

    }

    public void abre_porta(boolean hasKey) {
        if (hasKey) {
            this.setbTransponivel(true);
            this.mudar_imagem("porta_aberta.png");
        } else {
            System.out.println("Personagem sem chave, vá buscá-la!!");
        }
    }

    public void move_box(Posicao anterior) {

    }
}
