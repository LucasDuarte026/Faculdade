
public class Produto {
    private String name;
    private String code;
    private String description; 
    private int unique_price;
    private int in_stock;

    public Produto(String _name,String _code, String _description, int _unique_price, int _in_stock) {
        this.name = _name;
        this.code = _code;
        this.description = _description;
        this.unique_price = _unique_price;
        this.in_stock = _in_stock;
    }

    public String getCode() {
        return code;
    }
    public String getName() {
        return name;
    }
    public String getDescription() {
        return description;
    }
    
    public int getUnique_price() {
        return unique_price;
    }
    
    public int getIn_stock() {
        return in_stock;
    }
    
    public void setCode(String code) {
        this.code = code;
    }
    
    public void setName(String setName) {
        this.name = setName;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setUnique_price(int unique_price) {
        this.unique_price = unique_price;
    }

    public void setIn_stock(int in_stock) {
        this.in_stock = in_stock;
    }

    public void decreaseStock(int quantidade){
        this.setIn_stock(this.getIn_stock() - quantidade);
    } 

    public void increase(int quantidade){
        this.setIn_stock(this.getIn_stock() + quantidade);
    } 
    public void print_description(){
        System.out.format("Produto %s, %s, custo de R$ %d, quantidade %d",getName(),getCode(),getUnique_price(),getIn_stock());
    }
}
