--TEST--
Sass->setIncludePaths() should be fluent
--FILE--
<?php
$sass = new Sass();
$result = $sass->setIncludePaths("/directory/");
$result2 = $result->setIncludePaths("/other/directory/");
if ($sass === $result && $sass === $result2) {
    echo "fluent";
}
else {
    echo "not fluent";
}
?>
--EXPECT--
fluent
