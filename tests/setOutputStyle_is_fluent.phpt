--TEST--
Sass->setOutputStyle() should be fluent
--FILE--
<?php
$sass = new Sass();
$result = $sass->setOutputStyle(Sass::STYLE_NESTED);
$result2 = $result->setOutputStyle(Sass::STYLE_COMPACT);
if ($sass === $result && $sass === $result2) {
    echo "fluent";
}
else {
    echo "not fluent";
}
?>
--EXPECT--
fluent
