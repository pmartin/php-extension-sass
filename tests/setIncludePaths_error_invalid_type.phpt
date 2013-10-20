--TEST--
Sass->setIncludePaths() with invalid includePaths type
--FILE--
<?php
$sass = new Sass();
$sass->setIncludePaths(new stdClass());
?>
--EXPECTF--
Warning: Sass::setIncludePaths() expects parameter 1 to be string, object given in %s on line %d
