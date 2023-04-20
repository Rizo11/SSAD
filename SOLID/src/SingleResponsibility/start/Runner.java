package SingleResponsibility.start;

public class Runner {
    String data = Reader.readFromFile();
    Report.generateReport(data);
}
