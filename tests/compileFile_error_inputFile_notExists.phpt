--TEST--
Sass->compileFile() throws an Exception when input file doesn't exist
--FILE--
<?php
$inputFile = __DIR__ . '/not-a-file';

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
Message: Cannot read file %snot-a-file
