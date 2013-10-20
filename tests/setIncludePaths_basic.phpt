--TEST--
Sass->setIncludePaths() should allow to import a file from another folder
--FILE--
<?php
$includeDir = __DIR__ . '/test-includepath-subdir';
mkdir($includeDir);

$includedScss = '$myColor: red;';
$includedFile = $includeDir . '/test-scss-included';
file_put_contents($includedFile, $includedScss);

$scss = '@import \'test-scss-included\'; .test {color: $myColor}';
$inputFile = __DIR__ . '/test-scss-in';
file_put_contents($inputFile, $scss);

$sass = new Sass();
$sass->setIncludePaths($includeDir);
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
$includeDir = __DIR__ . '/test-includepath-subdir';
$includedFile = $includeDir . '/test-scss-included';

file_exists($inputFile) && unlink($inputFile);
file_exists($includedFile) && unlink($includedFile);
is_dir($includeDir) && rmdir($includeDir);
?>
