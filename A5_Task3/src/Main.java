/*
— создаете class ShapeType (этот класс хранит набор визуальных свойств фигур) с полями fillColor, borderColor и borderColorThickness
— создаете class ShapeTypeFactory (он нужен для создания тех самых ShapeType по-флайуейтовски). Внутри класса объявляем хешмапу String:ShapeType
и метод getShapeType с аргументами fillColor, borderColor и borderColorThickness. Этот метод из переданных аргументов делает хеш, и, если в мапе
по этому хешу (выступающего в роли ключа) находится существующий ShapeType, возвращает найденный ShapeType. В ином случае добавляет в мапу запись,
где ключ - хеш, а значение - созданный нами новый ShapeType с нужными свойствами, ну и возвращает его.
— создаете abstract class Shape (от него будут наследоваться классы конкретных фигур) с единственным полем ShapeType shapeType и абстрактными методами
accept (этот метод понадобится для реализации визитора) и draw (аргументы x и y нужны)
— от Shape'а наследуете классы Circle, Line и т.д. В конструктор должен передаваться ShapeType и индивидуальные для каждой фигуры параметры (как например
lineLength для линии)
— создаете интерфейс Visitor с методами visitLine, visitCircle, ну и так далее
— от Visitor'а имплементируете ExportVisitor, где реализуете каждый из методов (например выводите сообщение "Exporting [название фигуры]"
— в метод accept для каждой фигуры должен передаваться Visitor, а метод должен делать (например, в случае с линией) visitor.visitLine(this);
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

enum Color {
    Red,
    Green,
    Blue
}
class TypeShape {
    Color fillColor;
    Color borderColor;
    Double borderThickness;

    TypeShape(Color fillColor_, Color borderColor_, double borderThickness_) {
        fillColor = fillColor_;
        borderColor = borderColor_;
        borderThickness = borderThickness_;
    }

    @Override
    public String toString() {
        return Integer.toString(fillColor.ordinal()) + Integer.toString(borderColor.ordinal()) + Double.toString(borderThickness);
    }
}

class ShapeFactory {
    private static final Map<String, TypeShape> shapeTypes = new HashMap<>();


    public static TypeShape getTypeShape(TypeShape typeShape) {
        String key = typeShape.toString();

        if(shapeTypes.get(key) == null) {
            shapeTypes.put(key, typeShape);
            System.out.println("Creating shapeType...");
        } else {
            System.out.println("Using an already existing shapeType...");
        }
        return shapeTypes.get(key);

    }
}
abstract class Shape {
    TypeShape typeShape;

    abstract void accept(Visitor visitor);
    abstract void draw(double x, double y);

    Shape(TypeShape typeShape_) {
        typeShape = typeShape_;
    }
}

class Line extends Shape {

    private double lineLength;
    @Override
    void accept(Visitor visitor) {
        visitor.visitLine(this);
    }

    @Override
    void draw(double x, double y) {

    }

    Line(TypeShape typeShape, double lineLength_) {
        super(ShapeFactory.getTypeShape(typeShape));
        lineLength = lineLength_;
    }
}

class Triangle extends Shape {

    private double side1;
    private double side2;
    private double side3;
    @Override
    void accept(Visitor visitor) {
        visitor.visitTriangle(this);
    }

    @Override
    void draw(double x, double y) {
        System.out.println("Drawing...");
    }

    Triangle(double side1_, double side2_, double side3_, TypeShape typeShape_) {
        super(ShapeFactory.getTypeShape(typeShape_));
        side1 = side1_;
        side2 = side2_;
        side3 = side3_;
    }
}

class Circle extends Shape {
    private double radius;

    Circle(double radius_, TypeShape typeShape_) {
        super(ShapeFactory.getTypeShape(typeShape_));
        radius = radius_;
    }

    @Override
    void accept(Visitor visitor) {
        visitor.visitCircle(this);
    }

    @Override
    void draw(double x, double y) {

    }
}

class Rectangle extends Shape {

    private double length;
    private double width;

    Rectangle(double length_, double width_, TypeShape typeShape_) {
        super(ShapeFactory.getTypeShape(typeShape_));
        length = length_;
        width = width_;
    }

    @Override
    void accept(Visitor visitor) {
        visitor.visitRectangle(this);
    }

    @Override
    void draw(double x, double y) {

    }
}

interface Visitor {
    void visitLine(Line line);
    void  visitCircle(Circle circle);
    void visitTriangle(Triangle triangle);
    void visitRectangle(Rectangle rectangle);
}

class ExportVisitor implements Visitor{

    @Override
    public void visitLine(Line line) {
        System.out.println("Exporting Line...");
    }

    @Override
    public void visitCircle(Circle circle) {
        System.out.println("Exporting Circle...");
    }

    @Override
    public void visitTriangle(Triangle triangle) {
        System.out.println("Exporting Triangle...");
    }

    @Override
    public void visitRectangle(Rectangle rectangle) {
        System.out.println("Exporting Rectangle...");
    }
}

public class Main {
    public static void main(String[] args) {
        TypeShape tsh1 = new TypeShape(Color.Blue, Color.Red, 1);
        TypeShape tsh2 = new TypeShape(Color.Green, Color.Red, 1);

        Circle c1 = new Circle(2, tsh1);
        Circle c2 = new Circle(2, tsh1);
        Circle c3 = new Circle(2, tsh2);

        Rectangle r1 = new Rectangle(1, 1, tsh1);
        Rectangle r2 = new Rectangle(1, 1, tsh1);
        Rectangle r3 = new Rectangle(1, 1, tsh2);

        List<Shape> shapes = new ArrayList<Shape>();

        shapes.add(c1);
        shapes.add(c2);
        shapes.add(c3);
        shapes.add(r1);
        shapes.add(r2);
        shapes.add(r3);

        for (var sh : shapes) {
            sh.draw(1, 2);
        }

        ExportVisitor visitor = new ExportVisitor();
        for (var sh : shapes) {
            sh.accept(visitor);
        }
    }
}