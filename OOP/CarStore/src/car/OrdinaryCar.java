package car;

import enums.EngineType;
import enums.Model;
import enums.Region;

public class OrdinaryCar extends AbstractCar {

    public OrdinaryCar(Model model, int year, int price, EngineType engineType, Region region) {
        super(model, year, price, engineType, region);
    }

}
