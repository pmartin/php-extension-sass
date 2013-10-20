--TEST--
Sass->setOutputStyle() with invalid style
--FILE--
<?php
$sass = new Sass();
try {
    $sass->setOutputStyle(42);
}
catch (InvalidArgumentException $e) {
    printf("Code: %d\n", $e->getCode());
    printf("Message: %s\n", $e->getMessage());
}
?>
--EXPECT--
Code: 1
Message: Invalid style: 42
