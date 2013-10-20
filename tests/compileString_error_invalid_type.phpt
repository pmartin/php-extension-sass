--TEST--
Try to compile an invalid data-type
--FILE--
<?php
$sass = new Sass();
$css = $sass->compileString(array("boom"));
?>
--EXPECTF--
Warning: Sass::compileString() expects parameter 1 to be string, array given in %s on line %d
