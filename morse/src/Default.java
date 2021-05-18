import java.io.*;
import java.nio.file.Files;
import java.nio.file.NoSuchFileException;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.stream.Stream;

public class Default {
    private static boolean silent = false;

    private static void printHelp(){
        System.out.println("morse encode <filename> <output optional> <table optional> - to encode file with morse code\nmorse decode <filename> <output optional> <table optional> - to decode file with morse code\nKey -s - no output in console");
    }
    public static void main(String[] args) {
        if(args.length == 0){
            printHelp();
            return;
        }
        try {
            switch (args[0]) {
                case "decode":
                    decode(args[1], args.length > 2 ? args[2] : args[1].replace(".mrs", ".txt"), args.length > 3 ? args[3] : "morse.table");
                    break;
                case "encode":
                    encode(args[1], args.length > 2 ? args[2] : args[1].replace(".txt", ".mrs"), args.length > 3 ? args[3] : "morse.table");
                    break;
                default:
                    printHelp();
            }
        } catch (NoSuchFileException e) {
            System.out.println("No such file! Please, check path.");
        }catch (FileNotFoundException e){
            System.out.println("No morse.table file!");
        }catch (java.nio.charset.MalformedInputException e){
            System.out.println("Program works only with UTF-8 files. Check charset!");
        }
        catch (IOException e){
            e.printStackTrace();
        }
        if (Arrays.asList(args).contains("-s")) {
            silent = true;
        }
    }

    private static void decode(String input, String output, String table) throws IOException {
        Stream<String> lines = Files.lines(new File(input).toPath());
        Stream<String> decoded = new Decoder(new MorseTable(new FileInputStream(table)))
                .decode(lines);
        try (PrintWriter pw = new PrintWriter(Files.newBufferedWriter(
                Paths.get(output)))) {
            decoded.forEach(e -> {
                print(e);
                pw.println(e);
            });
        }
    }

    private static void encode(String input, String output, String table) throws IOException {
        Stream<String> lines = Files.lines(new File(input).toPath());
        Stream<String> encoded = new Encoder(new MorseTable(new FileInputStream(table)))
                .encode(lines);
        try (PrintWriter pw = new PrintWriter(Files.newBufferedWriter(
                Paths.get(output)))) {
            encoded.forEach(e -> {
                print(e);
                pw.println(e);
            });
        }
    }

    private static void print(String s) {
        if (!silent) {
            System.out.println(s);
        }
    }

}
