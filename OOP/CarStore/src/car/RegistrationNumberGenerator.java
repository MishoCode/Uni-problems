package car;

import enums.Region;

import java.util.EnumMap;
import java.util.Map;
import java.util.Random;

public class RegistrationNumberGenerator {

    private static final Map<Region, Integer> REGION_INTEGER_MAP = new EnumMap<>(Region.class);
    private static final Random random = new Random();

    public static String generateNumber(Region region){
        if(!REGION_INTEGER_MAP.containsKey(region)){
            REGION_INTEGER_MAP.put(region,1000);
        }

        Integer currentNumber = REGION_INTEGER_MAP.get(region);
        REGION_INTEGER_MAP.put(region,currentNumber+1);

        char firstRandomChar = (char)(random.nextInt(26) + 'A');
        char secondRandomChar = (char)(random.nextInt(26) + 'A');

        return region.getPrefix() + currentNumber + firstRandomChar + secondRandomChar;
    }
}
