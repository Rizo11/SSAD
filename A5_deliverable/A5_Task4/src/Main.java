import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
class Item {
    private String name;
    private int quantity;

    public Item(String name, int quantity) {
        this.name = name;
        this.quantity = quantity;
    }

    public String getName() {
        return name;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }
}

class GroceryList implements Iterable {
    private List<Item> items;

    GroceryList(List<Item> items_) {
        items = items_;
    }

    List<Item> getGroceries() {
        return items;
    }

    @Override
    public GroceryListIterator iterator() {
        return new GroceryListIterator(this);
    }
}

class GroceryListIterator implements Iterator {
    private int currentIndex = 0;
    private GroceryList groceryList_;

    @Override
    public boolean hasNext() {
        List<Item> groceries = groceryList_.getGroceries();
        return currentIndex < groceries.size();
    }

    @Override
    public Item next() {
        List<Item> groceries = groceryList_.getGroceries();
        if (hasNext()) {
            Item item = groceries.get(currentIndex++);
            if (item.getQuantity() > 0) {
                return item;
            } else {
                return next();
            }
        } else {
            return null;
        }
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }

    public GroceryListIterator(GroceryList groceryList) {
        groceryList_ = groceryList;
        currentIndex = 0;
    }
}

class GroceryShop {
    private GroceryList items;

    public GroceryShop(List<Item> items_) {
        items = new GroceryList(items_);
    }

    public void purchase(String name, int quantity) {
        GroceryListIterator iterator = items.iterator();
        boolean found = false;
        while (iterator.hasNext()) {
            Item item = iterator.next();
            if (item.getName().equals(name)) {
                if (item.getQuantity() >= quantity) {
                    item.setQuantity(item.getQuantity() - quantity);
                    found = true;
                    System.out.println("Purchase successful: " + quantity + " " + name);
                } else {
                    System.out.println("Sorry, only " + item.getQuantity() + " " + name + " is available");
                    item.setQuantity(item.getQuantity() - item.getQuantity());
                    found = true;
                }
                break;
            }
        }
        if (!found) {
            System.out.println("Sorry, " + name + " is not available");
        }
    }

    // Iterate through the grocery list and print
    public void print() {
        GroceryListIterator groceryList = items.iterator();
        Item item;
        while (groceryList.hasNext()) {
            item = groceryList.next();
            if (item == null) {
                continue;
            }
            System.out.println(item.getName() + " - " + item.getQuantity());
        }

        System.out.println();
    }
}

public class Main {
    public static void main(String[] args) {

        GroceryShop groceryShop = new GroceryShop(readData());
        System.out.println("Grocery shop list:");
        groceryShop.print();


        // Create a new grocery shop

        // Customer 1
        groceryShop.purchase("bread", 1);
        groceryShop.purchase("milk", 2);
        groceryShop.purchase("lemon", 1);

        System.out.println("\nUpdated Grocery shop list:");
        groceryShop.print();

        // Customer 2
        groceryShop.purchase("bread", 1);
        groceryShop.purchase("milk", 1);
        groceryShop.purchase("lemon", 1);


        System.out.println("\nUpdated Grocery shop list:");
        groceryShop.print();
        // Customer 3
        groceryShop.purchase("bread", 1);
        groceryShop.purchase("milk", 2);
        groceryShop.purchase("lemon", 2);


        System.out.println("\nGrocery shop list:");
        groceryShop.print();
    }

    public static List<Item> readData() {
        ArrayList<Item> items = new ArrayList<>();
        // Load the grocery list from the file
        try {
            BufferedReader reader = new BufferedReader(new FileReader("shop.txt"));
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.replaceAll("[()]", "").split(", ");
                Item item = new Item(parts[0], Integer.parseInt(parts[1]));
                items.add(item);
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return items;
    }
}