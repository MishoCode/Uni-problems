package car;

import enums.EngineType;
import enums.Model;
import enums.Region;

public class SportsCar extends AbstractCar{
    public SportsCar(Model model, int year, int price, EngineType engineType, Region region) {
        super(model, year, price, engineType, region);
    }
}
