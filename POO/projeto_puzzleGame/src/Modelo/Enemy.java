package Modelo;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import Controler.Tela;
import java.awt.Graphics;
import java.io.Serializable;
import java.util.Random;

public class Enemy extends Personagem implements Serializable {

    private int timer;
    private int pointer;
    Random random = new Random();

    public Enemy(String sNomeImagePNG) {

        super(sNomeImagePNG);
        this.bTransponivel = true;
        this.timer = random.nextInt(10);
        this.pointer = random.nextInt(4)+1;
        this.isEnemy = true;
    }

    public void autoDesenho() {
        super.autoDesenho();

        if (this.timer % Consts.TIMER_FIRE == 0) {
            this.timer = 0;
            Project f = new Project("fire.png", pointTo());
            f.setPosicao(pPosicao.getLinha(), pPosicao.getColuna());
            Desenho.acessoATelaDoJogo().addPersonagem(f);
        }
        this.timer++;
        if (this.timer > 1000) {
            this.timer = 0;
        }

    }

    public int pointTo() {
        int pointLocal = (this.pointer % 4) + 1;
        this.pointer++;
        return pointLocal;
    }

}
