public class MenuItem implements IMenu{
    private String name;
    private double price;
    @Override
    public void print() {
        System.out.printf("\t%s, $%.1f\n", getName(), getPrice());
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public double getPrice() {
        return price;
    }

    MenuItem(String name_, double price_) {
        name = name_;
        price = price_;
    }
}
