import car.Car;

import java.util.Comparator;

public class DefaultComparator implements Comparator<Car> {
    @Override
    public int compare(Car c1, Car c2) {
        int byModel = c1.getModel().compareTo(c2.getModel());
        if(byModel == 0){
            Integer.compare(c1.getYear(), c2.getYear());
        }
        return byModel;
    }
}
