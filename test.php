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
try {
	$css = $sass->compileString($scss);
	
	echo "RESULT: ";
	var_dump($css);
}
catch (RuntimeException $e) {
	printf("Exception.code: %d\n", $e->getCode());
	printf("Exception.message: %s\n", trim($e->getMessage()));
}

