package Modelo;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import Controler.ControleDeJogo;
import Controler.Tela;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.io.IOException;
import java.io.Serializable;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Hero extends Personagem implements Serializable {

    protected int quant_keys = 0;

    public Hero(String sNomeImagePNG) {
        super(sNomeImagePNG);

    }

    public void voltaAUltimaPosicao() {
        this.pPosicao.volta();
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

    public boolean moveUp() {
        if (super.moveUp()) {
            this.mudar_imagem("olha_cima.png");
            return validaPosicao();
        }
        return false;
    }

    public boolean moveDown() {
        if (super.moveDown()) {
            this.mudar_imagem("olha_baixo.png");
            return validaPosicao();
        }
        return false;
    }

    public boolean moveRight() {
        if (super.moveRight()) {
            this.mudar_imagem("olha_direita.png");
            return validaPosicao();
        }
        return false;
    }

    public boolean moveLeft() {
        if (super.moveLeft()) {
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
    public int getKeyQuant(){
        return this.quant_keys;
    }
}
