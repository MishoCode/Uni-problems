import car.Car;
import enums.Model;
import exceptions.CarAlreadyRegisteredException;
import exceptions.CarModelNotFoundException;
import exceptions.CarNotFoundException;

import java.util.*;

public class CarStore {

    private Map<String, Car> carRegistry = new HashMap<>();
    private Map<Model, List<Car>> carModels = new EnumMap<Model, List<Car>>(Model.class);
    private int totalPrice;

    public void add(Car car) {
        if (car == null) {
            throw new IllegalArgumentException("Provided car cannot be null.");
        }

        if(carRegistry.containsKey(car.getRegistrationNumber())){
            throw new CarAlreadyRegisteredException("Provided car is already present in the store.");
        }
        carRegistry.put(car.getRegistrationNumber(), car);

        if (!carModels.containsKey(car.getModel())) {
            List<Car> newModelCars = new ArrayList<>();
            carModels.put(car.getModel(), newModelCars);
        }

        List<Car> carsByModel = carModels.get(car.getModel());
        carsByModel.add(car);
        carModels.put(car.getModel(), carsByModel);

        totalPrice+=car.getPrice();
    }

    public void addAll(Collection<Car> cars) {
        if (cars.isEmpty()) {
            throw new IllegalArgumentException("Provided collection of cars cannot be empty.");
        }

        for (Car c : cars) {
            //carRegistry.put(c.getRegistrationNumber(), c);
            add(c);
        }
    }

    public void remove(Car car) {
        if (car == null) {
            throw new IllegalArgumentException("Provided car cannot be null.");
        }

        if (!carRegistry.containsKey(car.getRegistrationNumber())) {
            throw new CarNotFoundException("Provided car is not present in the store registry");
        }

        carRegistry.remove(car.getRegistrationNumber());

        Model currentCarModel = car.getModel();
        List<Car> carsByModel = carModels.get(currentCarModel);
        carsByModel.remove(car);
        if (carsByModel.isEmpty()) {
            carModels.remove(currentCarModel);
        }

        totalPrice-=car.getPrice();
    }

    public Collection<Car> getCarsByModel(Model model) {
        if (model == null) {
            throw new IllegalArgumentException("Provided model cannot be null.");
        }

        if (!carModels.containsKey(model)) {
            throw new CarModelNotFoundException("Provided model is not present in the store.");
        }

        List<Car> foundCars = carModels.get(model);
        //Collections.sort(foundCars, Comparator.comparing(Car::getYear));
        TreeSet<Car> orderedByYear = new TreeSet<>(Comparator.comparing(Car::getYear));
        for(Car c : foundCars){
            orderedByYear.add(c);
        }
        return orderedByYear;
    }

    public Car getCarByRegistrationNumber(String registrationNumber) {
        if (registrationNumber == null) {
            throw new IllegalArgumentException("Provided registration number cannot be null.");
        }

        if (!carRegistry.containsKey(registrationNumber)) {
            throw new CarNotFoundException("Provided car is not present in the store.");
        }

        return carRegistry.get(registrationNumber);
    }

    public Collection<Car> getCars() {
        TreeSet<Car> carsInDefaultOrder = new TreeSet<>(new DefaultComparator());
        for (Car c : carRegistry.values()) {
            carsInDefaultOrder.add(c);
        }

        return carsInDefaultOrder;
    }

    public Collection<Car> getCars(Comparator<Car> comparator) {
        if(comparator == null){
            throw new IllegalArgumentException("Provided comparator cannot be null.");
        }

        TreeSet<Car> orderedCars = new TreeSet<>(comparator);
        for (Car c : carRegistry.values()) {
            orderedCars.add(c);
        }

        return orderedCars;
    }

    public Collection<Car> getCars(Comparator<Car> comparator, boolean isReversed){
        if(comparator == null){
            throw new IllegalArgumentException("Provided comparator cannot be null.");
        }

        if(isReversed){
            return getCars(comparator.reversed());
        }else{
            return getCars(comparator);
        }
    }

    public int getNumberOfCars(){
        return carRegistry.size();
    }

    public int getTotalPriceForCars(){
        return totalPrice;
    }
}
