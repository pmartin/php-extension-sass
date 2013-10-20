--TEST--
Sass->setSourceComments() success cases
--FILE--
<?php
$sass = new Sass();
$sass->setSourceComments(Sass::SOURCE_COMMENTS_NONE);
$sass->setSourceComments(Sass::SOURCE_COMMENTS_DEFAULT);
$sass->setSourceComments(Sass::SOURCE_COMMENTS_MAP);
var_dump($sass);
?>
--EXPECT--
object(Sass)#1 (0) {
}
