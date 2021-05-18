package ru.nsu.chigrin;

import org.newdawn.slick.AppGameContainer;
import org.newdawn.slick.SlickException;

public class Engine {
    //Load pr

    public static void main(String[] args) throws SlickException {

        //Create a new game container named app under a new SetupClass named Setup Test
        AppGameContainer app = new AppGameContainer(new UI("Title Ha").setState(800,600));
        //arguments 1 and 2 are resolution of window by height and width
        //3rd argument is the boolean determining whether it is full screen
        app.setDisplayMode(800, 600, false);
        app.setTargetFrameRate(30);

        //Start the app
        app.start();

    }
}
