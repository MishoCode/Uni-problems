package enums;

public enum Region {

    SOFIA("CB"),
    BURGAS("A"),
    VARNA("B"),
    PLOVDIV("PB"),
    RUSE("P"),
    GABROVO("EB"),
    VIDIN("BH"),
    VRATSA("BP");

    String prefix;

    Region(String prefix) {
        this.prefix = prefix;
    }

    public String getPrefix(){
        return this.prefix;
    }
}
