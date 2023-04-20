public class HourlyEmployee extends Employee implements Payable{
    private double hourlyRate;
    private double hoursWorked;
    public double getHourlyRate() {
        return hourlyRate;
    }
    public void setHourlyRate(double hourlyRate) {
        this.hourlyRate = hourlyRate;
    }
    public double getHoursWorked() {
        return hoursWorked;
    }
    public void setHoursWorked(double hoursWorked) {
        this.hoursWorked = hoursWorked;
    }
    public HourlyEmployee(String name, double hourlyRate, double hoursWorked) {
        super(name);
        setHourlyRate(hourlyRate);
        setHoursWorked(hoursWorked);

        double salary = getHourlyRate() * getHoursWorked();
        setSalary(salary);
    }
    @Override
    public double calculatePay() {
        return getSalary();
    }
}
