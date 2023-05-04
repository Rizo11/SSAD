public class Main {
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