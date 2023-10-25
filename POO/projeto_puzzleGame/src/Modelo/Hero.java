package Modelo;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import Controler.ControleDeJogo;
import Controler.Tela;
import Controler.Tiro;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.io.Serializable;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Hero extends Personagem implements Serializable {

    protected int quant_keys = 0;
    protected int opened_doors = 0;
    protected int doorMissionQuant;
    private int iContaIntervalos;
    private int orientation;

    public Hero(String sNomeImagePNG, int doorMissionQuant) {
        super(sNomeImagePNG);
        this.doorMissionQuant = doorMissionQuant;
        iContaIntervalos = 0;
        orientation = 2;    //  Começa atirando para baixo

    }

    public void autoDesenho() {
        super.autoDesenho();

        this.iContaIntervalos++;

        if (this.iContaIntervalos == Consts.TIMER) {
            this.iContaIntervalos = 0;
            Tiro f = new Tiro("fire.png", orientation);
//            f.decide_direction(orientation);
            f.setPosicao(pPosicao.getLinha(), pPosicao.getColuna());
            Desenho.acessoATelaDoJogo().addPersonagem(f);

        }

    }

    

    public boolean faseFinalizada() {
        if (opened_doors >= this.doorMissionQuant) {
            return true;
        } else {
            return false;
        }
    }

    public void voltaAUltimaPosicao() {
        this.pPosicao.volta();
        if (doorMissionQuant > 2) {

        }
    }

    public boolean setPosicao(int linha, int coluna) {
        if (this.pPosicao.setPosicao(linha, coluna)) {
            if (!Desenho.acessoATelaDoJogo().ehPosicaoValida(this.getPosicao())) {
                this.voltaAUltimaPosicao();
            }
            return true;
        }
        return false;
    }

    /*TO-DO: este metodo pode ser interessante a todos os personagens que se movem*/
    private boolean validaPosicao() {
        if (!Desenho.acessoATelaDoJogo().ehPosicaoValida(this.getPosicao())) {
            this.voltaAUltimaPosicao();
            return false;
        }
        return true;
    }

    /*
    1 -> direita
    2 -> baixo
    3 -> esquerda
    4 -> cima
     */
    public boolean moveUp() {
        if (super.moveUp()) {
            this.orientation = 4;
            this.mudar_imagem("olha_cima.png");
            return validaPosicao();
        }
        return false;
    }

    public boolean moveDown() {
        if (super.moveDown()) {
            this.orientation = 2;

            this.mudar_imagem("olha_baixo.png");
            return validaPosicao();
        }
        return false;
    }

    public boolean moveRight() {
        if (super.moveRight()) {
            this.orientation = 1;

            this.mudar_imagem("olha_direita.png");
            return validaPosicao();
        }
        return false;
    }

    public boolean moveLeft() {
        if (super.moveLeft()) {
            this.orientation = 3;

            this.mudar_imagem("olha_esquerda.png");
            return validaPosicao();
        }
        return false;
    }

    public void addKey() {
        this.quant_keys++;
    }

    public void subtractKey() {
        this.quant_keys--;
    }

    public void printQuantKey() {
        System.out.format("Quantidade de chaves e: %d", this.quant_keys);

    }

    public int getKeyQuant() {
        return this.quant_keys;
    }

    public void add_doorOpened() {
        this.opened_doors++;
    }

}
