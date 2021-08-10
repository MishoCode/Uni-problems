package car;

import enums.EngineType;
import enums.Model;

public interface Car {

    public Model getModel();

    public int getYear();

    public int getPrice();

    public EngineType getEngineType();

    public String getRegistrationNumber();
}
