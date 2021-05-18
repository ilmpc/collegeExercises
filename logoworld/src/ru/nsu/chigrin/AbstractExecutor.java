package ru.nsu.chigrin;

import org.newdawn.slick.geom.Vector2f;

public class AbstractExecutor {
    private boolean drawMode = false;
    private State state;

    public AbstractExecutor(State state) {
        this.state = state;
    }

    enum direction {
        left, right, up, down;
    }

    void teleport(int x, int y) {
        if (x < 0 || x > state.getWidth()) {
            return;
        }
        if (y < 0 || y > state.getHeight()) {
            return;
        }
        state.setPoint(x, y);
    }

    void move(direction d, int steps) {
        Vector2f vector = state.getPoint();
        if (drawMode) {
        } else {
            switch (d) {
                case left:
                    steps *= -1;
                case right:
                    state.setPoint(((int) vector.x + steps) % state.getWidth(), (int) vector.y);
                    break;
                case down:
                    steps *= -1;
                case up:
                    state.setPoint((int) vector.x, ((int) vector.y + steps) % state.getHeight());
                    break;
            }
        }
    }

    void setDrawMode(boolean set) {
        drawMode = set;
    }
}
