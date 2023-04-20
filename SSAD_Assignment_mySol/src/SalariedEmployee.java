public class SalariedEmployee extends Employee implements Payable{
    public SalariedEmployee(String name, double salary) {
        super(name);
        setSalary(salary);
    }

    @Override
    public double calculatePay() {
        return getSalary();
    }
}
