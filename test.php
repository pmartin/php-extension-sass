<?php

$sass = new Sass();
$sass
	->setSourceComments(Sass::SOURCE_COMMENTS_NONE)
	->setOutputStyle(Sass::STYLE_EXPANDED)
	->setIncludePaths('/tmp/pmn/')
;

$filePathIn = '/tmp/test-scss-in';
$filePathInIncluded = '/tmp/pmn/test-scss-included';

$included = <<<'SCSS'
$color1: red;
$defaultSize: 12px;
SCSS;
file_put_contents($filePathInIncluded, $included);

$scss = <<<'SCSS'
@import 'test-scss-included';
.test {
	color: $color1;
	font-size: $defaultSize;
	span {
		font-size: $defaultSize * 0.75;
	}
}
SCSS;
file_put_contents($filePathIn, $scss);

try {
	$css = $sass->compileFile($filePathIn);
	echo "RESULT: ";
	var_dump($css);
}
catch (Exception $e) {
	printf("Exception.code: %d\n", $e->getCode());
	printf("Exception.message: %s\n", trim($e->getMessage()));
}

file_exists($filePathIn) && unlink($filePathIn);
file_exists($filePathInIncluded) && unlink($filePathInIncluded);

