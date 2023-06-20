import java.util.ArrayList;
import java.util.List;

interface IMenu {
    void print();
    String getName();
    double getPrice();
}

class MenuItem implements IMenu{
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

class CompositeMenu implements IMenu {
    private String name;
    private List<IMenu> menuItems;
    @Override
    public void print() {
        System.out.println(getName() + "[ $" + getPrice() + " ]");
        System.out.println("-------------------------");
        for (var item : menuItems) {
            item.print();
        }
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public double getPrice() {
        double totalPrice = 0.0;
        for (var item : menuItems)
            totalPrice += item.getPrice();

        return totalPrice;
    }

    public void addItem(IMenu newItem) {
        menuItems.add(newItem);
    }

    public CompositeMenu(String name) {
        this.name = name;
        this.menuItems = new ArrayList<IMenu>();
    }
}

abstract class MenuItemDecorator implements IMenu{
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

class SpicyDecorator extends MenuItemDecorator{
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

class VegetarianDecorator extends MenuItemDecorator{
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

class Main {
    public static void main(String[] args) {

        IMenu garlicBread = new MenuItem("Garlic bread", 5.5);
        garlicBread = new VegetarianDecorator(garlicBread);

        IMenu chickenWings = new MenuItem("Chicken Wings", 12.5);
        chickenWings = new SpicyDecorator(chickenWings);

        IMenu tomatoSoup = new MenuItem("Tomato soup", 10.5);
        tomatoSoup = new VegetarianDecorator(tomatoSoup);
        tomatoSoup = new SpicyDecorator(tomatoSoup);

        CompositeMenu appetizerMenu = new CompositeMenu("Appetizer Menu");
        appetizerMenu.addItem(garlicBread);
        appetizerMenu.addItem(chickenWings);
        appetizerMenu.addItem(tomatoSoup);



        CompositeMenu dessertMenu = new CompositeMenu("Dessert Menu");
        IMenu pie = new MenuItem("Pie", 4.5);
        dessertMenu.addItem(pie);
        pie = new VegetarianDecorator(pie);
        dessertMenu.addItem(pie);

        IMenu iceCream = new MenuItem("Ice Cream", 3.0);
        dessertMenu.addItem(iceCream);

        CompositeMenu mainMenu = new CompositeMenu("Main Menu");
        mainMenu.addItem(appetizerMenu);
        mainMenu.addItem(dessertMenu);


        mainMenu.print();

    }
}