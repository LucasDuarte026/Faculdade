package Controler;

import Modelo.Personagem;
import Modelo.Hero;
import Modelo.Box;
import Modelo.Enemy;
import Modelo.Parede;
import auxiliar.Posicao;
import java.util.ArrayList;

public class ControleDeJogo {

    boolean FlagPassouBotao = false;

    public void desenhaTudo(ArrayList<Personagem> e) {
        for (int i = 0; i < e.size(); i++) {
            e.get(i).autoDesenho();
        }
        e.get(0).autoDesenho(); // redesenha o personagem para ele ficar por cima
    }

    public int processaTudo(ArrayList<Personagem> umaFase) {
        Hero hero = (Hero) umaFase.get(0);
        if (hero.getLifeQuant() < 0) {
            System.out.println("voce morreu. Nao tem mais vidas. Hearts | acabou | ");
            return -1;
        }
        Personagem pIesimoPersonagem;
        for (int i = 1; i < umaFase.size(); i++) {
            pIesimoPersonagem = umaFase.get(i);

            if (hero.getPosicao().igual(pIesimoPersonagem.getPosicao())) {

                if (pIesimoPersonagem.isbPorta()) {
                    if (hero.faseFinalizada()) {
                        System.out.println("-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- ");
                        System.out.println("Parabens, voce passou para a proxima fase!");
                        System.out.println("-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- ");
                        return 1;
                    }
                    if (!pIesimoPersonagem.isbTransponivel()) {
                        if (hero.getKeyQuant() > 0) {
                            System.out.print("\nInteracao de personagem: Porta aberta");

                            pIesimoPersonagem.mudar_imagem("porta_aberta.png");
                            pIesimoPersonagem.setbTransponivel(true);
                            hero.subtractKey();
                            hero.add_doorOpened();
                        } else {
                            hero.voltaAUltimaPosicao();
                            System.out.println("chaves insuficientes, va atras!");
                            hero.printQuantKey();
                        }
                    }
                }
                if (pIesimoPersonagem.isbBox()) {
                    System.out.print("\nInteracao de personagem: ");
                    Posicao caixaPos = pIesimoPersonagem.getPosicao();
                    Posicao heroPos = hero.getPosicao();
                    System.out.println("Empurrando caixa");
                    if (heroPos.getColunaAnterior() - caixaPos.getColuna() < 0) {
                        /*caixa vai para cima*/
                        pIesimoPersonagem.setPosicao(caixaPos.getLinha(), caixaPos.getColuna() + 1);

                    } else if (heroPos.getColunaAnterior() - caixaPos.getColuna() > 0) {
                        /*Caixa vai para baixo*/
                        pIesimoPersonagem.setPosicao(caixaPos.getLinha(), caixaPos.getColuna() - 1);

                    } else if (heroPos.getLinhaAnterior() - caixaPos.getLinha() < 0) {
                        /*Caixa vai para baixo*/
                        pIesimoPersonagem.setPosicao(caixaPos.getLinha() + 1, caixaPos.getColuna());

                    } else if (heroPos.getLinhaAnterior() - caixaPos.getLinha() > 0) {
                        /*Caixa vai para baixo*/
                        pIesimoPersonagem.setPosicao(caixaPos.getLinha() - 1, caixaPos.getColuna());
                    }
                    break;
                }
                if (pIesimoPersonagem.isbTransponivel()) {
                    if (pIesimoPersonagem.isbKey()) {
                        System.out.print("\nInteracao de personagem: ");

                        hero.addKey();
                        hero.printQuantKey();
                        umaFase.remove(pIesimoPersonagem);

                    } else if (pIesimoPersonagem.isbBotao() && !FlagPassouBotao) {
                        System.out.print("\nInteracao de personagem: apertou o botao ");

                        pIesimoPersonagem.mudar_imagem("botao_verde.png");
                        Personagem bloco_especial;
                        for (int k = 1; k < umaFase.size(); k++) {
                            bloco_especial = umaFase.get(k);
                            if (bloco_especial.isSpecialBlock()) {
                                System.out.println("Passagem pelo muro quebrado aberto");
                                bloco_especial.mudar_imagem("brick_quebrado.png");
                                bloco_especial.setbTransponivel(true);
                                break;
                            }
                        }

                        FlagPassouBotao = true;
                    } else if (pIesimoPersonagem.isbHeart()) {
                        umaFase.remove(pIesimoPersonagem);
                        hero.add_lifeQuant();
                        System.out.format("Voce recebeu uma vida. Hearts | %d |\n", hero.getLifeQuant());
                    } else if (pIesimoPersonagem.isbEnemy()) {
                        hero.voltaAUltimaPosicao();
                        hero.subtract_lifeQuant();
                        System.out.format("Voce foi atingido por um inimigo. Hearts | %d |\n", hero.getLifeQuant());
                    } else if (pIesimoPersonagem.isbProject()) {
                        umaFase.remove(pIesimoPersonagem);
                        hero.voltaAUltimaPosicao();
                        hero.subtract_lifeQuant();
                        System.out.format("Voce foi atingido por um projetil. Hearts | %d |\n", hero.getLifeQuant());
                    }
                }
            }
            Personagem outro;
            for (int j = i + 1; j < umaFase.size(); j++) {
                outro = umaFase.get(j);
                if (outro.getPosicao().igual(pIesimoPersonagem.getPosicao())) {

                    if (pIesimoPersonagem.isbEnemy()) {
                        if (outro.isbTiro()) {
                            hero.add_opponent_killed();
                            System.out.format(" -> Eliminou um oponente. Inimigos abatidos:  | %d | \n", hero.getEnemiesKilled());
                            umaFase.remove(pIesimoPersonagem);
                            umaFase.remove(outro);
                        }

                    }
                }
            }
        }
        return 0;
    }

    /*Retorna true se a posicao p é válida para Hero com relacao a todos os personagens no array*/
    public boolean ehPosicaoValida(ArrayList<Personagem> umaFase, Posicao p, boolean isEnemy, int characterCount) {
        Personagem pIesimoPersonagem;
        for (int i = 1; i < umaFase.size(); i++) {
            pIesimoPersonagem = umaFase.get(i);
            if (!pIesimoPersonagem.isbTransponivel()) {
                if (pIesimoPersonagem.getPosicao().igual(p) && pIesimoPersonagem.isbPorta()) {
                    if (isEnemy) {
                        return false;
                    } else {
                        return true;
                    }
                }
                if (pIesimoPersonagem.getPosicao().igual(p)) {
                    if (isEnemy || characterCount == 0) {
                        return false;
                    }
                }
            }
            if (pIesimoPersonagem.isbTransponivel() && pIesimoPersonagem.getPosicao().igual(p)) {
                if (isEnemy && pIesimoPersonagem.getCharacterCount() != characterCount) {
                    return false;
                }
            }

        }
        return true;

    }
}
