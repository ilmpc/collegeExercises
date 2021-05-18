import java.util.Arrays;
import java.util.stream.Stream;

class Decoder {
    private MorseTable morseTable;

    Decoder(MorseTable morseTable) {
        this.morseTable = morseTable;
    }

    private String replaceMorseWithSym(String s) {
        StringBuilder result = new StringBuilder();
        for (String a : s.split("\\s+")) {
                if(a.isEmpty()){
                    continue;
                }
                result.append(morseTable.decode(a));
        }
        return result.toString();
    }

    Stream<String> decode(Stream<String> inputStream) {
        return inputStream
                .map(this::replaceMorseWithSym)
                .distinct();
    }
}
