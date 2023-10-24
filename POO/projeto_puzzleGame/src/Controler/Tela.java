package Controler;

import Modelo.Personagem;
import Modelo.Caveira;
import Modelo.Hero;
import Modelo.Parede;
import Modelo.Key;
import Modelo.Box;
import Modelo.Porta;
import Modelo.BichinhoVaiVemHorizontal;
import Auxiliar.Consts;
import Auxiliar.Desenho;
import Modelo.ZigueZague;
import auxiliar.Posicao;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;
import javax.swing.JButton;

public class Tela extends javax.swing.JFrame implements MouseListener, KeyListener {

    private Hero hero;
    private ArrayList<Personagem> faseAtual;
    private ControleDeJogo cj = new ControleDeJogo();
    private Graphics g2;

    public Tela() {
        Desenho.setCenario(this);
        initComponents();
        this.addMouseListener(this);
        /*mouse*/

        this.addKeyListener(this);
        /*teclado*/
 /*Cria a janela do tamanho do tabuleiro + insets (bordas) da janela*/
        this.setSize(Consts.RES * Consts.CELL_SIDE + getInsets().left + getInsets().right,
                Consts.RES * Consts.CELL_SIDE + getInsets().top + getInsets().bottom);

        faseAtual = new ArrayList<Personagem>();

        /*Cria faseAtual adiciona personagens*/
        hero = new Hero("olha_baixo.png");
        hero.setPosicao(0, 0);
        this.addPersonagem(hero);

        init_fase1();

        /*
        ZigueZague zz = new ZigueZague("robo.png");
        zz.setPosicao(5, 5);
        this.addPersonagem(zz);

        BichinhoVaiVemHorizontal bBichinhoH = new BichinhoVaiVemHorizontal("roboPink.png");
        bBichinhoH.setPosicao(3, 3);
        this.addPersonagem(bBichinhoH);

        BichinhoVaiVemHorizontal bBichinhoH2 = new BichinhoVaiVemHorizontal("roboPink.png");
        bBichinhoH2.setPosicao(6, 6);
        this.addPersonagem(bBichinhoH2);

        Caveira bV = new Caveira("caveira.png");
        bV.setPosicao(9, 1);
        this.addPersonagem(bV);
        
        Key key1 = new Key("key1.png");
        key1.setPosicao(8, 0);
        this.addPersonagem(key1);

  

        Box caixa1 = new Box("box.png");
        caixa1.setPosicao(5, 2);
        this.addPersonagem(caixa1);

        Box caixa2 = new Box("box.png");
        caixa2.setPosicao(10, 6);
        this.addPersonagem(caixa2);

        Porta porta1 = new Porta("porta_fechada.png");
        porta1.setPosicao(5, 4);
        this.addPersonagem(porta1);

        Porta porta2 = new Porta("porta_fechada.png");
        porta2.setPosicao(5, 7);
        this.addPersonagem(porta2);
         */
    }

    public void init_fase1() {
        /* Os valores para cada um são uma estimativa por cima de quantos onjetos deste terão na fase*/

        int quant_hero = 1;
        int quant_paredes = 100;
        int quant_caixas = 2;
        int quant_portas = 3;
        int quant_chaves = 3;

        int counter_hero = 0;
        int counter_paredes = 0;
        int counter_caixas = 0;
        int counter_portas = 0;
        int counter_chaves = 0;

        /*  criando o vetor de objetos*/
        Hero heroes[] = new Hero[quant_hero];
        Parede bricks[] = new Parede[quant_paredes];
        Box boxes[] = new Box[quant_caixas];
        Porta portas[] = new Porta[quant_portas];
        Key keys[] = new Key[quant_chaves];

        int[][] fase_1
                = {
                    {9, 0, 0, 1, 2, 1, 1, 1, 0, 0, 0},
                    {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 3, 0, 4, 1, 2, 0, 4, 1, 0},
                    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0},
                    {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 4}

                };
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                /*
                    index:
                    0 -> fundo preto
                    1 -> parede
                    2 -> chave
                    3 -> box
                    4 -> porta
                    5 -> botão
                    6
                    7
                    8
                    9 -> hero
    
                 */
                switch (fase_1[i][j]) {

                    case 1:

                        bricks[counter_paredes] = new Parede("bricks.png");
                        bricks[counter_paredes].setPosicao(i, j);
                        this.addPersonagem(bricks[counter_paredes]);
                        counter_paredes++;
                        break;
                    case 2:

                        keys[counter_chaves] = new Key("key1.png");
                        keys[counter_chaves].setPosicao(i, j);
                        this.addPersonagem(keys[counter_chaves]);
                        counter_chaves++;
                        break;
                    
                    case 3:

                        boxes[counter_caixas] = new Box("box.png");
                        boxes[counter_caixas].setPosicao(i, j);
                        this.addPersonagem(boxes[counter_caixas]);
                        break;
                    case 4:

                        portas[counter_portas] = new Porta("porta_fechada.png");
                        portas[counter_portas].setPosicao(i, j);
                        this.addPersonagem(portas[counter_portas]);
                        counter_portas++;
                        break;
                     
                    case 9:

                        heroes[counter_hero] = new Hero("olha_baixo.png");
                        heroes[counter_hero].setPosicao(i, j);
                        this.addPersonagem(heroes[counter_hero]);
                        counter_hero++;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    public void init_paredes_fase1() {
        Parede bricks[] = new Parede[121];
        int[][] fase_1
                = {
                    {0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0},
                    {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
                    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0},
                    {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0}

                };

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                if (fase_1[i][j] == 1) {
                    bricks[i] = new Parede("bricks.png");
                    bricks[i].setPosicao(i, j);
                    this.addPersonagem(bricks[i]);
                }
            }
        }
    }

    public boolean ehPosicaoValida(Posicao p) {
        return cj.ehPosicaoValida(this.faseAtual, p);
    }

    public void addPersonagem(Personagem umPersonagem) {
        faseAtual.add(umPersonagem);
    }

    public void removePersonagem(Personagem umPersonagem) {
        faseAtual.remove(umPersonagem);
    }

    public Graphics getGraphicsBuffer() {
        return g2;
    }

    public void paint(Graphics gOld) {
        Graphics g = this.getBufferStrategy().getDrawGraphics();
        /*Criamos um contexto gráfico*/
        g2 = g.create(getInsets().left, getInsets().top, getWidth() - getInsets().right, getHeight() - getInsets().top);
        /**
         * ***********Desenha cenário de fundo*************
         */
        for (int i = 0; i < Consts.RES; i++) {
            for (int j = 0; j < Consts.RES; j++) {
                try {
                    Image newImage = Toolkit.getDefaultToolkit().getImage(new java.io.File(".").getCanonicalPath() + Consts.PATH + "fundo_preto.png");
                    g2.drawImage(newImage,
                            j * Consts.CELL_SIDE, i * Consts.CELL_SIDE, Consts.CELL_SIDE, Consts.CELL_SIDE, null);

                } catch (IOException ex) {
                    Logger.getLogger(Tela.class
                            .getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
        if (!this.faseAtual.isEmpty()) {
            this.cj.desenhaTudo(faseAtual);
            this.cj.processaTudo(faseAtual);
        }

        g.dispose();
        g2.dispose();
        if (!getBufferStrategy().contentsLost()) {
            getBufferStrategy().show();
        }
    }

    public void go() {
        TimerTask task = new TimerTask() {
            public void run() {
                repaint();
            }
        };
        Timer timer = new Timer();
        timer.schedule(task, 0, Consts.PERIOD);
    }

    public void keyPressed(KeyEvent e) {
        if (e.getKeyCode() == KeyEvent.VK_C) {
            this.faseAtual.clear();
        } else if (e.getKeyCode() == KeyEvent.VK_UP) {
            hero.moveUp();
        } else if (e.getKeyCode() == KeyEvent.VK_DOWN) {
            hero.moveDown();
        } else if (e.getKeyCode() == KeyEvent.VK_LEFT) {
            hero.moveLeft();
        } else if (e.getKeyCode() == KeyEvent.VK_RIGHT) {
            hero.moveRight();
        }

        this.setTitle("-> Cell: " + (hero.getPosicao().getColuna()) + ", "
                + (hero.getPosicao().getLinha()));

        //repaint(); /*invoca o paint imediatamente, sem aguardar o refresh*/
    }

    public void mousePressed(MouseEvent e) {
        /* Clique do mouse desligado*/
        int x = e.getX();
        int y = e.getY();

        this.setTitle("X: " + x + ", Y: " + y
                + " -> Cell: " + (y / Consts.CELL_SIDE) + ", " + (x / Consts.CELL_SIDE));

        this.hero.getPosicao().setPosicao(y / Consts.CELL_SIDE, x / Consts.CELL_SIDE);

        repaint();
    }


    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("POO2023-1 - Skooter");
        setAlwaysOnTop(true);
        setAutoRequestFocus(false);
        setResizable(false);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 561, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 500, Short.MAX_VALUE)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents
    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables

    public void mouseMoved(MouseEvent e) {
    }

    public void mouseClicked(MouseEvent e) {
    }

    public void mouseReleased(MouseEvent e) {
    }

    public void mouseEntered(MouseEvent e) {
    }

    public void mouseExited(MouseEvent e) {
    }

    public void mouseDragged(MouseEvent e) {
    }

    public void keyTyped(KeyEvent e) {
    }

    public void keyReleased(KeyEvent e) {
    }
}
