package Controler;

import Modelo.Personagem;
import Modelo.Caveira;
import Modelo.Hero;
import Modelo.Parede;
import Modelo.Key;
import Modelo.Box;
import Modelo.Botao;
import Modelo.Heart;
import Modelo.Mob;
import Modelo.Seta;
import Modelo.Enemy;
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
    private boolean flagSpecialBlock;
    private int contador_fase;

    public Tela() {
        this.contador_fase = 1;

        Desenho.setCenario(this);
        initComponents();
        this.addMouseListener(this);
        /*mouse*/

        this.addKeyListener(this);
        /*teclado*/
 /*Cria a janela do tamanho do tabuleiro + insets (bordas) da janela*/
        this.setSize(Consts.RES * Consts.CELL_SIDE + getInsets().left + getInsets().right,
                Consts.RES * Consts.CELL_SIDE + getInsets().top + getInsets().bottom);

        init_fase1();
        if (contador_fase == 2) {
            System.out.println("\n\nFase2 começou");
        }
    }

    public void passaDeFase() {
        switch (contador_fase) {
            case 2:
                contador_fase++;
                init_fase2();
                break;
            case 3:
                contador_fase++;
                //  init_fase2();
                break;
            case 4:
                contador_fase++;
                //   init_fase2();
                break;
        }
    }

    public void init_fase1() {

        System.out.println("/ - - -   - - -   - - -   - - -   - - -   - - -   - - -   - - -  ");
        System.out.println("| Jogo desenvolvido por Joao Victor & Lucas Duarte ");
        System.out.println("| - Aperte R caso queira resetar ");
        System.out.println("| - Aperte S caso queira salvar ");

        System.out.println("|\n|\tFase1:\n-> Colete 3 chaves para abrir cada porta, a ultima eh a saida da fase ");

        System.out.println("\\ - - -   - - -   - - -   - - -   - - -   - - -   - - -   - - -  ");

        /* Os valores para cada um são uma estimativa por cima de quantos onjetos deste terão na fase*/
        faseAtual = new ArrayList<Personagem>();
        int fase1_door_quant = 3;
        int fase1_kiils_quant = 9;

        flagSpecialBlock = false;

        /*Cria o heroi primeiro que todo mundo*/
        hero = new Hero("olha_baixo.png", fase1_door_quant, fase1_kiils_quant);;
        hero.setPosicao(0, 0);
        this.addPersonagem(hero);

        int quant_paredes = 100;
        int quant_caixas = 2;
        int quant_portas = 3;
        int quant_chaves = 4;
        int quant_botoes = 3;
        int quant_enemies = 5;
        int quant_mobs = 5;
        int quant_hearts = 2;
        int quant_setas = 10;

        int counter_paredes = 0;
        int counter_caixas = 0;
        int counter_portas = 0;
        int counter_chaves = 0;
        int counter_botoes = 0;
        int counter_enemies = 0;
        int counter_mobs = 0;
        int counter_hearts = 0;
        int counter_setas = 0;

        /*  criando o vetor de objetos*/
        Parede bricks[] = new Parede[quant_paredes];
        Box boxes[] = new Box[quant_caixas];
        Porta portas[] = new Porta[quant_portas];
        Key keys[] = new Key[quant_chaves];
        Botao botoes[] = new Botao[quant_botoes];
        Enemy enemies[] = new Enemy[quant_enemies];
        Mob mobs[] = new Mob[quant_mobs];
        Heart cores[] = new Heart[quant_hearts];
        Seta setas[] = new Seta[quant_setas];

        int[][] fase_1
                = {
                    {0, 0, 0, 1, 2, 1, 1, 1, 9, 0, 0},
                    {1, 1,-4, 1, 9, 1, 0, 1, 0, 1, 0},
                    {2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 8},
                    {6, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {2, 1, 8, 1, 4, 1, 0, 1, 0, 1, 0},
                    {0, 1, 3, 0, 0, 1, 9, 0, 4, 1, 0},
                    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 0, 1, -2, 1, 0, 1, 8, 1, 0},
                    {0, 1, 8, 1, 0, 1, 0, 1, 0, 1, 5},
                    {0, 0, -3, 1, 0, 1, 0, 1, 1, 1, 0},
                    {-5, 1,0,1, 0, 8,-1, 9, 0, 1, 4}
                /*
                    index:
                    0 -> fundo preto
                    1 -> parede
                    2 -> chave
                    3 -> box
                    4 -> porta
                    5 -> botão
                    6 -> parede especial
                    7 -> porta saida
                    8 -> Enemy inimigo tiro
                    9 -> Mob inimigo andando
                   -1 -> seta direita        
                   -2 -> seta baixo
                   -3 -> seta esquerda
                   -4 -> seta cima
                   -5 -> coração
                        
                 */
 /*             Direções
                   1 -> direita
                   2 -> baixo
                   3 -> esquerda
                   4 -> cima
                 */
                };
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {

                if (fase_1[i][j] == 6) {
                    this.flagSpecialBlock = true;
                    fase_1[i][j] = 1;
                }
                switch (fase_1[i][j]) {

                    case 1:

                        bricks[counter_paredes] = new Parede("bricks.png");
                        bricks[counter_paredes].setPosicao(i, j);
                        if (this.flagSpecialBlock) {
                            bricks[counter_paredes].setSpecialBlock(true);
                            this.flagSpecialBlock = false;
                        }
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

                    case 5:

                        botoes[counter_botoes] = new Botao("botao_vermelho.png");
                        botoes[counter_botoes].setPosicao(i, j);
                        this.addPersonagem(botoes[counter_botoes]);
                        counter_botoes++;
                        break;
                    case 8:

                        enemies[counter_enemies] = new Enemy("morty.png");
                        enemies[counter_enemies].setPosicao(i, j);
                        this.addPersonagem(enemies[counter_enemies]);
                        counter_enemies++;
                        break;

                    case 9:
                        mobs[counter_mobs] = new Mob("skoot.png");
                        mobs[counter_mobs].setPosicao(i, j);
                        this.addPersonagem(mobs[counter_mobs]);
                        counter_mobs++;
                        break;

                    case -1:
                        System.out.println("entrou");
                        setas[counter_setas] = new Seta("azul_direita.png");
                        setas[counter_setas].setPosicao(i, j);
                        this.addPersonagem(setas[counter_setas]);
                        counter_setas++;
                        break;
                    case -2:
                        System.out.println("entrou");
                        setas[counter_setas] = new Seta("laranja_baixo.png");
                        setas[counter_setas].setPosicao(i, j);
                        this.addPersonagem(setas[counter_setas]);
                        counter_setas++;
                        break;
                    case -3:
                        System.out.println("entrou");
                        setas[counter_setas] = new Seta("azul_esquerda.png");
                        setas[counter_setas].setPosicao(i, j);
                        this.addPersonagem(setas[counter_setas]);
                        counter_setas++;
                        break;
                    case -4:
                        System.out.println("entrou");
                        setas[counter_setas] = new Seta("laranja"
                                + "_cima.png");
                        setas[counter_setas].setPosicao(i, j);
                        this.addPersonagem(setas[counter_setas]);
                        counter_setas++;
                        break;

                    case -5:
                        cores[counter_hearts] = new Heart("heart.png");
                        cores[counter_hearts].setPosicao(i, j);
                        this.addPersonagem(cores[counter_hearts]);
                        counter_hearts++;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    public void init_fase2() {

        System.out.println("/ - - -   - - -   - - -   - - -   - - -   - - -   - - -   - - -  ");
        System.out.println("| Jogo desenvolvido por Joao Victor & Lucas Duarte ");
        System.out.println("| - Aperte R caso queira resetar ");
        System.out.println("| - Aperte S caso queira salvar ");

        System.out.println("|\n|\tFase1:\n-> Colete 3 chaves para abrir cada porta, a ultima eh a saida da fase ");

        System.out.println("\\ - - -   - - -   - - -   - - -   - - -   - - -   - - -   - - -  ");

        /* Os valores para cada um são uma estimativa por cima de quantos onjetos deste terão na fase*/
        faseAtual = new ArrayList<Personagem>();
        int fase1_door_quant = 3;
        int fase1_kiils_quant = 9;

        flagSpecialBlock = false;

        /*Cria o heroi primeiro que todo mundo*/
        hero = new Hero("olha_baixo.png", fase1_door_quant, fase1_kiils_quant);
        hero.setPosicao(0, 0);
        this.addPersonagem(hero);

        int quant_paredes = 100;
        int quant_caixas = 2;
        int quant_portas = 3;
        int quant_chaves = 4;
        int quant_botoes = 3;
        int quant_enemies = 5;
        int quant_mobs = 5;
        int quant_hearts = 2;

        int counter_paredes = 0;
        int counter_caixas = 0;
        int counter_portas = 0;
        int counter_chaves = 0;
        int counter_botoes = 0;
        int counter_enemies = 0;
        int counter_mobs = 0;
        int counter_hearts = 0;


        /*  criando o vetor de objetos*/
        Parede bricks[] = new Parede[quant_paredes];
        Box boxes[] = new Box[quant_caixas];
        Porta portas[] = new Porta[quant_portas];
        Key keys[] = new Key[quant_chaves];
        Botao botoes[] = new Botao[quant_botoes];
        Enemy enemies[] = new Enemy[quant_enemies];
        Mob mobs[] = new Mob[quant_mobs];
        Heart cores[] = new Heart[quant_hearts];

        int[][] fase_1
                = {
                    {0, 0, 0, 1, 2, 1, 1, 1, 9, 0, 0},
                    {1, 1, 0, 1, 9, 1, 0, 1, 0, 1, 0},
                    {2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                    {6, 1, 8, 1, 0, 1, 0, 1, 0, 1, 0},
                    {2, 1, 8, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 3, 0, 4, 1, 9, 0, 4, 1, 0},
                    {0, 1, 8, 1, -5, 1, 0, 1, 0, 1, 0},
                    {0, 1, 8, 1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 8, 1, 0, 1, 0, 1, 0, 1, 5},
                    {0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0},
                    {-5, 1, 0, 1, 0, 0, 0, 9, 0, 1, 4}
                /*
                    index:
                    0 -> fundo preto
                    1 -> parede
                    2 -> chave
                    3 -> box
                    4 -> porta
                    5 -> botão
                    6 -> parede especial
                    7 -> porta saida
                    8 -> inimigo tiro
                    9 -> inimigo andando
                   -1 -> coração
    
                 */
                };
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {

                if (fase_1[i][j] == 6) {
                    this.flagSpecialBlock = true;
                    fase_1[i][j] = 1;
                }
                switch (fase_1[i][j]) {

                    case 1:

                        bricks[counter_paredes] = new Parede("bricks.png");
                        bricks[counter_paredes].setPosicao(i, j);
                        if (this.flagSpecialBlock) {
                            bricks[counter_paredes].setSpecialBlock(true);
                            this.flagSpecialBlock = false;
                        }
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

                    case 5:

                        botoes[counter_botoes] = new Botao("botao_vermelho.png");
                        botoes[counter_botoes].setPosicao(i, j);
                        this.addPersonagem(botoes[counter_botoes]);
                        counter_botoes++;
                        break;
                    case 8:

                        enemies[counter_enemies] = new Enemy("morty.png");
                        enemies[counter_enemies].setPosicao(i, j);
                        this.addPersonagem(enemies[counter_enemies]);
                        counter_enemies++;
                        break;

                    case 9:
                        mobs[counter_mobs] = new Mob("skoot.png");
                        mobs[counter_mobs].setPosicao(i, j);
                        this.addPersonagem(mobs[counter_mobs]);
                        counter_mobs++;
                        break;
                    case -5:
                        cores[counter_hearts] = new Heart("heart.png");
                        cores[counter_hearts].setPosicao(i, j);
                        this.addPersonagem(cores[counter_hearts]);
                        counter_hearts++;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    // ideia inicial para instalar as paredes
    /*
    public void init_paredes_fase1_old() {
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
     */
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
            if (this.cj.processaTudo(faseAtual)) {
                contador_fase++;
                passaDeFase();
            }
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
        } else if (e.getKeyCode() == KeyEvent.VK_SPACE) {
            hero.gunFire();
        } else if (e.getKeyCode() == KeyEvent.VK_R) {
            init_fase1();
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
