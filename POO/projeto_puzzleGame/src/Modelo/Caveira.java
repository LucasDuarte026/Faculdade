package Modelo;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import Controler.Tela;
import java.awt.Graphics;
import java.io.Serializable;

public class Caveira extends Personagem implements Serializable{
    private int iContaIntervalos;
    
    public Caveira(String sNomeImagePNG) {
        super(sNomeImagePNG);
        this.bTransponivel = false;
        this.iContaIntervalos = 0;
    }

    public void autoDesenho() {
        super.autoDesenho();

        this.iContaIntervalos++;
        if(this.iContaIntervalos == Consts.TIMER_WALK){
            this.iContaIntervalos = 0;
            Project f = new Project("fire.png",2);
            f.setPosicao(pPosicao.getLinha(),pPosicao.getColuna()+3);
            Desenho.acessoATelaDoJogo().addPersonagem(f);
        }
    }    
}
