import org.apache.commons.collections4.BidiMap;
import org.apache.commons.collections4.bidimap.DualHashBidiMap;
import org.apache.commons.io.IOUtils;

import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;

class MorseTable {
    private BidiMap<Character, String> table;

    MorseTable() {
        table = new DualHashBidiMap<>();
        table.put('a', "..-");
    }
    MorseTable(InputStream inputStream) throws IOException {
        String input = IOUtils.toString(inputStream, StandardCharsets.UTF_8);
        table = new DualHashBidiMap<>();
        String[] words = input.split("\\s+");
        if(words.length % 2 == 1){
            throw new IllegalArgumentException("Таблица должна быть взаимооднозначной.");
        }
        for (int i = 0; i < words.length; i+=2) {
            table.put(words[i].charAt(0),words[i+1]);
        }
    }

    String encode(char symbol) {
        if(Character.isSpaceChar(symbol))
            return "/";
        symbol = Character.toLowerCase(symbol);
        return table.getOrDefault(symbol,"NSS"); //TODO catch NPE
    }

    char decode(String morse) throws IllegalArgumentException{
        if(morse.contentEquals("/")){
            return ' ';
        }
        if(morse.contentEquals("NSS")){
            return '#';
        }
        Character result = table.getKey(morse);
        if(result == null)
            throw new IllegalArgumentException(morse);
        return result;
    }
}
