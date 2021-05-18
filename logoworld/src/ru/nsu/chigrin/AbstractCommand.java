package ru.nsu.chigrin;

import java.util.stream.Stream;

public abstract class AbstractCommand {
    public AbstractCommand(){};
    public abstract void setArguments(Stream stream);
    public abstract void exec(AbstractExecutor ae);
}
