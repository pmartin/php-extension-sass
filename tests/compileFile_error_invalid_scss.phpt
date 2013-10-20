--TEST--
Sass->compileFile() throws an Exception when SCSS is not valid
--FILE--
<?php
$inputFile = __DIR__ . '/test-scss-in';
$scss = '$myColor /: red; .test {color !!: $myColor}';
file_put_contents($inputFile, $scss);

$sass = new Sass();
try {
    $sass->compileFile($inputFile);
}
catch (RuntimeException $e) {
    printf("Code: %d\n", $e->getCode());
    printf("Message: %s\n", $e->getMessage());
}
?>
--EXPECTF--
Code: 1
Message: %stest-scss-in:1: error: expected ':' after $myColor in assignment statement
--CLEAN--
<?php
$inputFile = __DIR__ . '/test-scss-in';
file_exists($inputFile) && unlink($inputFile);
?>
