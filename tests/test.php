$x = 4;
$y = 6;
$z = 8;

$x = $y + $z;
$y = $x + $z;
$z = $x + $y;

// comment will be ignored

$a = $z + $y - ($x % $y) + ($x * $z) + ($y / 2) * ($x - $y * $z); // Another Comment

echo ($a + $x + $y + $z); // prints -7938

echo ($x + $y);  // prints 36

$result = 2 * ($x + $y);

echo $result; // prints 72

$c = 7;

$result = $x - $y * $c;

echo $result; // prints -140

$a = 4;

$b = 2;

$result = $a * $b;

echo $result; // prints 8

echo "string";
