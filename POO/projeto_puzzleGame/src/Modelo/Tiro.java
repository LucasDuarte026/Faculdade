package Modelo;

import Auxiliar.Desenho;
import Controler.Tela;
import java.awt.Graphics;
import java.io.Serializable;

public class Tiro extends Personagem implements Serializable {

    private int decision;

    public Tiro(String sNomeImagePNG, int heroOrientation) {
        super(sNomeImagePNG);
        this.bProject = true;
        this.decision = heroOrientation;
        this.isTiro = true;
    }

    @Override
    public void autoDesenho() {
        super.autoDesenho();

        /*
    1 -> direita
    2 -> baixo
    3 -> esquerda
    4 -> cima
         */
        switch (decision) {
            case 1:
                this.mudar_imagem("tiro_right.png");

                if (!this.moveRight()) {
                    Desenho.acessoATelaDoJogo().removePersonagem(this);
                }
                break;
            case 2:
                this.mudar_imagem("tiro_down.png");

                if (!this.moveDown()) {
                    Desenho.acessoATelaDoJogo().removePersonagem(this);

                }
                break;
            case 3:
                this.mudar_imagem("tiro_left.png");

                if (!this.moveLeft()) {
                    Desenho.acessoATelaDoJogo().removePersonagem(this);

                }
                break;
            case 4:
                this.mudar_imagem("tiro_up.png");

                if (!this.moveUp()) {
                    Desenho.acessoATelaDoJogo().removePersonagem(this);

                }
                break;
            default:
                break;
        }

    }

    /*
    1 -> direita
    2 -> baixo
    3 -> esquerda
    4 -> cima
     */
}
