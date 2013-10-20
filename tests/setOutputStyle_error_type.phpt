--TEST--
Sass->setOutputStyle() with type for parameter style
--FILE--
<?php
$sass = new Sass();
$sass->setOutputStyle("Hello");
?>
--EXPECTF--
Warning: Sass::setOutputStyle() expects parameter 1 to be long, string given in %s on line %d
