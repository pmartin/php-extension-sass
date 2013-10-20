--TEST--
Compile an SCSS string
--FILE--
<?php
$sass = new Sass();
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
string(80) ".test {
  color: red;
  font-size: 12px; }
  .test span {
    font-size: 9px; }
"
