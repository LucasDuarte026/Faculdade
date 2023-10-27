package Modelo;

import Auxiliar.Desenho;
import Controler.Tela;
import java.awt.Graphics;
import java.io.Serializable;

public class Project extends Personagem implements Serializable {

    private int decision;

    public Project(String sNomeImagePNG, int whereToGO) {
        super(sNomeImagePNG);
        this.bProject = true;
        this.decision = whereToGO;
    }

    @Override
    public void autoDesenho() {
        super.autoDesenho();
        switch (decision) {
            case 1:
                this.mudar_imagem("fire_right.png");

                if (!this.moveRight()) {
                    Desenho.acessoATelaDoJogo().removePersonagem(this);
                }
                break;
            case 2:
                this.mudar_imagem("fire_down.png");

                if (!this.moveDown()) {
                    Desenho.acessoATelaDoJogo().removePersonagem(this);
                }
                break;
            case 3:
                this.mudar_imagem("fire_left.png");

                if (!this.moveLeft()) {
                    Desenho.acessoATelaDoJogo().removePersonagem(this);
                }
                break;
            case 4:
                this.mudar_imagem("fire_up.png");

                if (!this.moveUp()) {
                    Desenho.acessoATelaDoJogo().removePersonagem(this);
                }
                break;
            default:
                break;
        }
    }

}
