--TEST--
Sass->compileFile() throws an Exception when out file is not writeable
--FILE--
<?php
$inputFile = __DIR__ . '/test-scss-in';
$scss = '$myColor: red; .test {color: $myColor}';
file_put_contents($inputFile, $scss);

$outputFile = __DIR__ . '/not-existing-dir/test-css-out';

$sass = new Sass();
try {
    $sass->compileFile($inputFile, $outputFile);
}
catch (RuntimeException $e) {
    printf("Code: %d\n", $e->getCode());
    printf("Message: %s\n", $e->getMessage());
}
?>
--EXPECTF--
Code: 3
Message: Cannot write to %s%enot-existing-dir%etest-css-out
--CLEAN--
<?php
$inputFile = __DIR__ . '/test-scss-in';
file_exists($inputFile) && unlink($inputFile);
?>
