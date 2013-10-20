--TEST--
Sass->compileFile() compiles CSS to a file
--FILE--
<?php
$inputFile = __DIR__ . '/test-scss-in';
$scss = '$myColor: red; .test {color: $myColor}';
file_put_contents($inputFile, $scss);

$outputFile = __DIR__ . '/test-css-out';

$sass = new Sass();
$return = $sass->compileFile($inputFile, $outputFile);
var_dump($return);

$css = file_get_contents($outputFile);
var_dump($css);
?>
--EXPECT--
NULL
string(24) ".test {
  color: red; }
"
--CLEAN--
<?php
$inputFile = __DIR__ . '/test-scss-in';
$outputFile = __DIR__ . '/test-css-out';
file_exists($inputFile) && unlink($inputFile);
file_exists($outputFile) && unlink($outputFile);
?>
