package Modelo;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import Controler.Tela;
import auxiliar.Posicao;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.Serializable;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;

public abstract class Personagem implements Serializable {

    protected ImageIcon iImage;
    protected Posicao pPosicao;
    protected Posicao pPosicaoAnterior;

    protected boolean bTransponivel;
    /*Pode passar por cima?*/
    protected boolean bProject;
    /*Se encostar, morre?*/
    protected boolean isKey;
    /*para ser chave*/
    protected boolean isBox;
    /*para ser caixa*/
    protected boolean isPorta;
    /*para ser Porta*/
    protected boolean isBotao;
    /*para ser botão*/
    protected boolean isSpecialBlock;
    /*para ser passagem especial*/
    protected boolean isTiro;
    /*para ser um tiro interagível*/
    protected boolean isEnemy;
    /*para ser a um inimigo*/
    boolean isHeart;
    /*para ser a um coração*/
    protected int characterCount;

    /*contador do characterCount*/
 /*para ser um coração de vida*/
    protected Personagem(String sNomeImagePNG) {
        this.pPosicao = new Posicao(1, 1);
        this.bTransponivel = true;
        this.bProject = false;
        this.isKey = false;/*para ser chave*/
        this.isBox = false;/*para ser caixa*/
        this.isPorta = false;   //  Para ser porta
        this.isBotao = false;   //  Para ser botao
        this.isHeart = false;   //  Para ser coração

        try {
            iImage = new ImageIcon(new java.io.File(".").getCanonicalPath() + Consts.PATH + sNomeImagePNG);
            Image img = iImage.getImage();
            BufferedImage bi = new BufferedImage(Consts.CELL_SIDE, Consts.CELL_SIDE, BufferedImage.TYPE_INT_ARGB);
            Graphics g = bi.createGraphics();
            g.drawImage(img, 0, 0, Consts.CELL_SIDE, Consts.CELL_SIDE, null);
            iImage = new ImageIcon(bi);
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }

    public Posicao getPosicao() {
        /*TODO: Retirar este método para que objetos externos nao possam operar
         diretamente sobre a posição do Personagem*/
        return pPosicao;
    }

    public void mudar_imagem(String sNomeImagePNG) {
        /*usada a mesma lógica acima*/
        try {
            iImage = new ImageIcon(new java.io.File(".").getCanonicalPath() + Consts.PATH + sNomeImagePNG);
            Image img = iImage.getImage();
            BufferedImage bi = new BufferedImage(Consts.CELL_SIDE, Consts.CELL_SIDE, BufferedImage.TYPE_INT_ARGB);
            Graphics g = bi.createGraphics();
            g.drawImage(img, 0, 0, Consts.CELL_SIDE, Consts.CELL_SIDE, null);
            iImage = new ImageIcon(bi);
        } catch (IOException ex) {
            Logger.getLogger(Personagem.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    public Posicao getPosicaoAnterior() {

        return pPosicaoAnterior;
    }

    public boolean isbTransponivel() {
        return bTransponivel;
    }

    public boolean isbKey() {
        return isKey;
    }

    public boolean isbPorta() {
        return isPorta;
    }

    public boolean isbBox() {
        return this.isBox;
    }

    public boolean isbBotao() {
        return this.isBotao;
    }

    public boolean isbTiro() {
        return this.isTiro;
    }

    public boolean isbEnemy() {
        return this.isEnemy;
    }

    public boolean isbHeart() {
        return this.isHeart;
    }

    public boolean isbProject() {
        return this.bProject;
    }

    public void setbTransponivel(boolean bTransponivel) {
        this.bTransponivel = bTransponivel;
    }

    public void setSpecialBlock(boolean set) {
        this.isSpecialBlock = set;
    }

    public boolean isSpecialBlock() {
        return this.isSpecialBlock;
    }

    public int getCharacterCount() {
        return this.characterCount;
    }

    public void autoDesenho() {
        Desenho.desenhar(this.iImage, this.pPosicao.getColuna(), this.pPosicao.getLinha());
    }

    public boolean setPosicao(int linha, int coluna) {
        return pPosicao.setPosicao(linha, coluna);
    }

    public boolean moveUp() {
        return this.pPosicao.moveUp();
    }

    public boolean moveDown() {
        return this.pPosicao.moveDown();
    }

    public boolean moveRight() {
        return this.pPosicao.moveRight();
    }

    public boolean moveLeft() {
        return this.pPosicao.moveLeft();
    }
}
