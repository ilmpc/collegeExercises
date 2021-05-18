package ru.nsu.chigrin;

import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

public class CommandFactory {
    private Properties properties;
    private Map<String, Class> cachedClass;

    public CommandFactory(Properties properties) {
        this.properties = properties;
        cachedClass = new HashMap<>();
    }

    public AbstractCommand getCommand(String name) throws ClassNotFoundException {
        try {
            if (cachedClass.containsKey(name)) {
                return (AbstractCommand) cachedClass.get(name).newInstance();

            }
            if (properties.containsKey(name)) {
                Class temp = Class.forName(properties.getProperty(name));
                cachedClass.put(name, temp);
                return (AbstractCommand) temp.newInstance();
            }
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
        throw new ClassNotFoundException();
    }
}

