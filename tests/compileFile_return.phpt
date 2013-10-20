--TEST--
Sass->compileFile() returns compiled CSS
--FILE--
<?php
$inputFile = __DIR__ . '/test-scss-in';
$scss = '$myColor: red; .test {color: $myColor}';
file_put_contents($inputFile, $scss);

$sass = new Sass();
$css = $sass->compileFile($inputFile);
var_dump($css);
?>
--EXPECT--
string(24) ".test {
  color: red; }
"
--CLEAN--
<?php
$inputFile = __DIR__ . '/test-scss-in';
file_exists($inputFile) && unlink($inputFile);
?>
