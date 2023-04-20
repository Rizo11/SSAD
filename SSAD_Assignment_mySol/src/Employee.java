public abstract class Employee {
    private String name;
    private double salary;

    public Employee(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
    public double getSalary() {
        return salary;
    }
    protected void setSalary(double salary) {
        this.salary = salary;
    }
}
