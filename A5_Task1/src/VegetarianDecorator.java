public class VegetarianDecorator extends MenuItemDecorator{
    public VegetarianDecorator(IMenu newMenuItem) {
        super(newMenuItem);
    }

    @Override
    public void print() {
        super.print();
        System.out.println("\t\t-- This item is spicy (+ $2)");
    }

    @Override
    public String getName() {
        return super.getName();
    }

    @Override
    public double getPrice() {
        return super.getPrice() + 2.0;
    }
}
