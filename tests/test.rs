fn main() {
    let x = 4;
    let y = 6;
    let z = 8;

    x = y + z;
    y = x + z;
    z = x + y;

    // comment will be ignored

    let a = z + y - (x % y) + (x * z) + (y / 2) * (x - y * z); // Another Comment

    println!(a + x + y + z); // prints -7938

    println!(x + y);  // prints 36

    let result = 2 * (x + y);

    println!(result); // prints 72

    let c = 7;

    let result = x - y * c;

    println!(result); // prints -140

    let a = 4;

    let b = 2;

    let result = a * b;

    println!(result); // prints 8

    println!("string");
}
