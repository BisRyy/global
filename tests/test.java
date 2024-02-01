package tests;

public class test {
    public void main(String[] args){
        int x = 4;
        int y = 6;
        int z = 8;

        x = y + z;
        y = x + z;
        z = x + y;

        // comment will be ignored

        int a = z + y - (x % y) + (x * z) + (y / 2) * (x - y * z); // Another Comment

        System.out.println(a + x + y + z); // prints -7938

        System.out.println(x + y); // prints 36

        int result = 2 * (x + y);

        System.out.println(result); // prints 72

        int c = 7;

        result = x - y * c;

        System.out.println(result); // prints -140
}

}
