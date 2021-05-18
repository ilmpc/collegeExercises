import java.util.stream.Stream;

class Encoder {
    private MorseTable morseTable;

    Encoder(MorseTable morseTable) {
        this.morseTable = morseTable;
    }

    private String replaceSymWithMorse(String s) {
        StringBuilder result = new StringBuilder();
        for (char a : s.toCharArray()) {
            result.append(morseTable.encode(a)).append(" ");
        }
        return result.toString();
    }

    Stream<String> encode(Stream<String> inputStream) {
        return inputStream
                .map(this::replaceSymWithMorse)
                .distinct();
    }
}
