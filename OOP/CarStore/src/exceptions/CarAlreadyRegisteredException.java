package exceptions;

public class CarAlreadyRegisteredException extends RuntimeException{
    public CarAlreadyRegisteredException(String message) {
        super(message);
    }
}
