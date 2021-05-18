package ru.nsu.chigrin;


import org.newdawn.slick.geom.Point;
import org.newdawn.slick.geom.Shape;
import org.newdawn.slick.geom.Vector2f;

import java.util.ArrayList;
import java.util.List;

class State {
    private List<Shape> lines;
    private int width, height;

    public State(int width, int height) {
        this.width = width;
        this.height = height;
        lines = new ArrayList<>();
        lines.add(new Point(0,0));
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    List<Shape> getShapes() {
        return lines;
    }

    void addShape(Shape shape) {
        lines.add(shape);
    }

    void setPoint(int x, int y) {
        lines.get(0).setX(x);
        lines.get(0).setY(y);
    }
    Vector2f getPoint(){
        return lines.get(0).getLocation();
    }
}
