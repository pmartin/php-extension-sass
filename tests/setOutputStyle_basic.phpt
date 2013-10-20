--TEST--
Sass->setOutputStyle() success cases
--FILE--
<?php
$sass = new Sass();
$sass->setOutputStyle(Sass::STYLE_NESTED);
$sass->setOutputStyle(Sass::STYLE_EXPANDED);
$sass->setOutputStyle(Sass::STYLE_COMPACT);
$sass->setOutputStyle(Sass::STYLE_COMPRESSED);
var_dump($sass);
?>
--EXPECT--
object(Sass)#1 (0) {
}
