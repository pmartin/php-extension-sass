--TEST--
Compile an SCSS string, with specific options
--FILE--
<?php
$sass = new Sass();
$sass
    ->setSourceComments(Sass::SOURCE_COMMENTS_NONE)
    ->setOutputStyle(Sass::STYLE_COMPRESSED)
;
$scss = <<<'SCSS'
$color1: red;
$defaultSize: 12px;
.test {
    color: $color1;
    font-size: $defaultSize;
    span {
        font-size: $defaultSize * 0.75;
    }
}
SCSS;
$css = $sass->compileString($scss);
var_dump($css);
?>
--EXPECT--
string(64) ".test {color:#ff0000;font-size:12px;}.test span {font-size:9px;}"
