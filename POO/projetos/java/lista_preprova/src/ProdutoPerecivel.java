public class ProdutoPerecivel extends Produto {

    static int validade;

    public static int getValidade() {
        return validade;
    }

    public ProdutoPerecivel(String _name, String _code, String _description, int _unique_price, int _in_stock) {
        super(_name, _code, _description, _unique_price, _in_stock);
    }

    public boolean increasePerecivel(int quant) {
        if (this.getIn_stock() == 0) {
            this.setIn_stock(quant);
            return  true;
        } else {
            return false;
        }
    }

}
