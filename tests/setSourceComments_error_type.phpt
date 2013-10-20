--TEST--
Sass->setSourceComments() with invalid sourceComments type
--FILE--
<?php
$sass = new Sass();
$sass->setSourceComments("plop");
?>
--EXPECTF--
Warning: Sass::setSourceComments() expects parameter 1 to be long, string given in %s on line %d
