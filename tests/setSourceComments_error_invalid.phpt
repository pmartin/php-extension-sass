--TEST--
Sass->setSourceComments() with invalid sourceComments value
--FILE--
<?php
$sass = new Sass();
try {
    $sass->setSourceComments(123);
}
catch (InvalidArgumentException $e) {
    printf("Code: %d\n", $e->getCode());
    printf("Message: %s\n", $e->getMessage());
}
?>
--EXPECT--
Code: 1
Message: Invalid sourceComments: 123
