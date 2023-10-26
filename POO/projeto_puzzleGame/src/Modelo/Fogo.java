package Modelo;

import Auxiliar.Desenho;
import Controler.Tela;
import java.awt.Graphics;
import java.io.Serializable;

public class Fogo extends Personagem implements Serializable {

    private int decision;

    public Fogo(String sNomeImagePNG, int whereToGO) {
        super(sNomeImagePNG);
        this.bMortal = true;
        this.decision = whereToGO;
    }

    @Override
    public void autoDesenho() {
        super.autoDesenho();
        switch (decision) {
            case 1:
                if (!this.moveRight()) {
                    Desenho.acessoATelaDoJogo().removePersonagem(this);
                }
                break;
            case 2:
                if (!this.moveDown()) {
                    Desenho.acessoATelaDoJogo().removePersonagem(this);
                }
                break;
            case 3:
                if (!this.moveLeft()) {
                    Desenho.acessoATelaDoJogo().removePersonagem(this);
                }
                break;
            case 4:
                if (!this.moveUp()) {
                    Desenho.acessoATelaDoJogo().removePersonagem(this);
                }
                break;
            default:
                break;
        }
    }

}
