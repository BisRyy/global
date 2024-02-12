<?php
$x = 4;
$y = 6;
$z = 8;

$x = $y + $z;
$y = $x + $z;
$z = $x + $y;

// comment will be ignored

$a = $z + $y - ($x % $y) + ($x * $z) + ($y / 2) * ($x - $y * $z); // Another Comment

echo ($a + $x + $y + $z), "\n"; // prints -7938

echo ($x + $y), "\n";  // prints 36

$result = 2 * ($x + $y);

echo $result, "\n"; // prints 72

$c = 7;

$result = $x - $y * $c;

echo $result, "\n"; // prints -140

$a = 4;

$b = 2;

$result = $a * $b;

echo $result, "\n"; // prints 8

echo "string", "\n";

// one liner if statement
$test1 = 10;
$test2 = 20;
if($test1 + $test2 >= 20) echo "It's True!", "\n"; else echo "It's not true!";

?>