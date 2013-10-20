--TEST--
Compile an invalid SCSS string
--FILE--
<?php
$sass = new Sass();
$scss = <<<'SCSS'
$color1 -: red /;
SCSS;
try {
    $css = $sass->compileString($scss);
}
catch (RuntimeException $e) {
    printf("Code: %d\n", $e->getCode());
    printf("Message: %s\n", $e->getMessage());
}
?>
--EXPECT--
Code: 1
Message: source string:1: error: expected ':' after $color1 in assignment statement
