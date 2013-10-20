--TEST--
Sass->setSourceComments() should be fluent
--FILE--
<?php
$sass = new Sass();
$result = $sass->setSourceComments(Sass::SOURCE_COMMENTS_NONE);
$result2 = $result->setSourceComments(Sass::SOURCE_COMMENTS_MAP);
if ($sass === $result && $sass === $result2) {
    echo "fluent";
}
else {
    echo "not fluent";
}
?>
--EXPECT--
fluent
