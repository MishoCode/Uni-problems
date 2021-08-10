package exceptions;

public class CarModelNotFoundException extends RuntimeException{
    public CarModelNotFoundException(String message) {
        super(message);
    }
}
