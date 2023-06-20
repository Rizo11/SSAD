interface Prototype() {
    Car clone();
}

abstract class Vehicle {
    private String brand;
    private String color;

    protected Vehicle(Vehicle vehicle) {
        this.brand = vehicle.brand;
        this.color = vehicle.color;
    }

    public Vehicle() { }
}

class Car extends Vehicle implements Prototype{
    private int topSpeed;

    public Car() {
        super();
    }

    public Car(Car car) {
        super(car);
        this.topSpeed = car.topSpeed;
    }

    @Override
    public Car clone() {
        return new Car(this);
    }
}
public class Main {
    public static void main(String[] args) {
        System.out.println("Hello world!");
    }
}