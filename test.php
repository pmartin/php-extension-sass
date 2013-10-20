<?php

$sass = new Sass();
$sass
	->setSourceComments(Sass::SOURCE_COMMENTS_MAP)
	->setOutputStyle(Sass::STYLE_EXPANDED)
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

$filePathIn = tempnam(sys_get_temp_dir(), 'scss_');
$filePathOut = tempnam(sys_get_temp_dir(), 'css_');
file_put_contents($filePathIn, $scss);

try {
	//$css = $sass->compileString($scss);
	
	//*
	$sass->compileFile($filePathIn, $filePathOut);
	$css = file_get_contents($filePathOut);
	/*/
	$css = $sass->compileFile($filePathIn);
	//*/
	
	echo "RESULT: ";
	var_dump($css);
}
catch (Exception $e) {
	printf("Exception.code: %d\n", $e->getCode());
	printf("Exception.message: %s\n", trim($e->getMessage()));
}

file_exists($filePathIn) && unlink($filePathIn);
file_exists($filePathOut) && unlink($filePathOut);

