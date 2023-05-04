public abstract class MenuItemDecorator implements IMenu{
    private IMenu menuItem;

    public MenuItemDecorator(IMenu newMenuItem) {
        menuItem = newMenuItem;
    }

    @Override
    public void print() {
        menuItem.print();
    }

    @Override
    public String getName() {
        return menuItem.getName();
    }

    @Override
    public double getPrice() {
        return menuItem.getPrice();
    }

}
