package Modelo;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.io.IOException;
import java.io.Serializable;
import java.util.Random;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Mob extends Personagem implements Serializable {

    private boolean bRight;
    private int timer;

    Random random = new Random();

    public Mob(String sNomeImagePNG, int characterCount) {
        super(sNomeImagePNG);
        this.bTransponivel = true;
        bRight = true;
        this.isEnemy = true;
        this.characterCount = characterCount;

        timer = random.nextInt(10);

    }

    public void autoDesenho() {
        if (timer % Consts.TIMER_WALK == 0) {
            if (bRight) {
                this.setPosicao(pPosicao.getLinha(), pPosicao.getColuna() + 1);
            } else {
                this.setPosicao(pPosicao.getLinha(), pPosicao.getColuna() - 1);
            }
            if (timer % 20 * Consts.TIMER_WALK == 0) {
                bRight = !bRight;
            }
        }
        super.autoDesenho();
        timer++;
        if (timer > 1000) {
            timer = 0;
        }
    }

    public void voltaAUltimaPosicao() {
        this.pPosicao.volta();

    }

    public boolean setPosicao(int linha, int coluna) {
        if (this.pPosicao.setPosicao(linha, coluna)) {
            if (!Desenho.acessoATelaDoJogo().ehPosicaoValida(this.getPosicao(), true,this.characterCount)) {
                this.voltaAUltimaPosicao();
            }
            return true;
        }
        return false;
    }
}
