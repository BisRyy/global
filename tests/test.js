var x = 4;
var y = 6;
var z = 8;

x = y + z;
y = x + z;
z = x + y;

// comment will be ignored

var a = z + y - (x % y) + (x * z) + (y / 2) * (x - y * z); // Another Comment

console.log(a + x + y + z); // prints -7938

console.log(x + y);  // prints 36

var result = 2 * (x + y);

console.log(result); // prints 72

var c = 7;

result = x - y * c;

console.log(result); // prints -140

a = 4;

var b = 2;

result = a * b;

console.log(result); // prints 8

console.log("string");
