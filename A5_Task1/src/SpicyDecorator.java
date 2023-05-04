public class SpicyDecorator extends MenuItemDecorator{
    @Override
    public void print() {
        super.print();
        System.out.println("\t\t-- This item is vegetarian (+ $4)");
    }

    @Override
    public String getName() {
        return super.getName();
    }

    @Override
    public double getPrice() {
        return super.getPrice() + 4.0;
    }

    public SpicyDecorator(IMenu newMenuItem) {
        super(newMenuItem);
    }
}
