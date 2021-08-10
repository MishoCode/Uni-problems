package car;

import enums.EngineType;
import enums.Model;
import enums.Region;

public class AbstractCar implements Car{

    private Model model;
    private int year;
    private int price;
    private EngineType engineType;
    private Region region;

    private String registrationNumber;

    protected AbstractCar(Model model, int year, int price, EngineType engineType, Region region) {
        this.model = model;
        this.year = year;
        this.price = price;
        this.engineType = engineType;
        this.region = region;
        this.registrationNumber = RegistrationNumberGenerator.generateNumber(this.region);
    }

    @Override
    public Model getModel() {
        return this.model;
    }

    @Override
    public int getYear() {
        return this.year;
    }

    @Override
    public int getPrice() {
        return this.price;
    }

    @Override
    public EngineType getEngineType() {
        return this.engineType;
    }

    @Override
    public String getRegistrationNumber() {
        return this.registrationNumber;
    }
}
