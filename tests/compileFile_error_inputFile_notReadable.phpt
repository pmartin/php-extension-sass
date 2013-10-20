--TEST--
Sass->compileFile() throws an Exception when input file is not readable
--FILE--
<?php
$inputFile = __DIR__ . '/test-scss-in';
$scss = '$myColor: red; .test {color: $myColor}';
file_put_contents($inputFile, $scss);

// We don't have the right to read the input file
chmod($inputFile, 0000);

$sass = new Sass();
try {
    $sass->compileFile($inputFile);
}
catch (InvalidArgumentException $e) {
    printf("Code: %d\n", $e->getCode());
    printf("Message: %s\n", $e->getMessage());
}
?>
--EXPECTF--
Code: 2
Message: Cannot read file %stest-scss-in
--CLEAN--
<?php
$inputFile = __DIR__ . '/test-scss-in';
file_exists($inputFile) && unlink($inputFile);
?>
