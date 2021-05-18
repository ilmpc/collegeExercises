package ru.nsu.chigrin;

import org.newdawn.slick.BasicGame;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;


public class UI extends BasicGame {
    private State state;

    public UI(String title) {
        super(title);
    }

    public UI setState(int width, int height) {
        state = new State(width, height);
        return this;
    }

    @Override
    public void init(GameContainer container) throws SlickException {
        //
    }

    @Override
    //Delta is the amount of time that has passed since the last update
    public void update(GameContainer container, int delta) throws SlickException {

    }

    @Override
    public void render(GameContainer container, Graphics g) throws SlickException {
        g.setAntiAlias(true);
        state.getShapes().forEach(g::draw);
    }
}