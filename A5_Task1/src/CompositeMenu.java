import java.util.ArrayList;
import java.util.List;

public class CompositeMenu implements IMenu {
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
