--TEST--
Constructor works
--FILE--
<?php
$sass = new Sass();
var_dump($sass);
?>
--EXPECT--
object(Sass)#1 (0) {
}
