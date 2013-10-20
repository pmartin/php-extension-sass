# PHP Extension: SASS

[![Build Status](https://travis-ci.org/pmartin/php-extension-sass.png?branch=master)](https://travis-ci.org/pmartin/php-extension-sass)

This bundles the [libsass](https://github.com/hcatlin/libsass) C/C++ library into a PHP Extension.


## About sass and libsass

[Quoting](http://sass-lang.com/documentation/file.SASS_REFERENCE.html) its documentation:

> [Sass](http://sass-lang.com/) is an extension of CSS that adds power and elegance to the basic language. It allows you to use [variables](http://sass-lang.com/documentation/file.SASS_REFERENCE.html#variables_), [nested rules](http://sass-lang.com/documentation/file.SASS_REFERENCE.html#nested_rules), [mixins](http://sass-lang.com/documentation/file.SASS_REFERENCE.html#mixins), [inline imports](http://sass-lang.com/documentation/file.SASS_REFERENCE.html#import), and more, all with a fully CSS-compatible syntax. Sass helps keep large stylesheets well-organized, and get small stylesheets up and running quickly, particularly with the help of [the Compass style library](http://compass-style.org/).

And [libsass](https://github.com/hcatlin/libsass) is, still quoting:

> Libsass is a C/C++ port of the Sass CSS precompiler. The original version was written in Ruby, but this version is meant for efficiency and portability.

This project bundles this [libsass](https://github.com/hcatlin/libsass) library into a PHP Extension.


## Installing the Extension

To install this extension, you first have to fetch its sources:

    git clone git@github.com:pmartin/php-extension-sass.git

Then, you have to fetch, libsass, which is linked as a git submodule:

    git submodule init
    git submodule update

After that, you can compile libsass to a static extension -- a file called `libsass.a`:

    cd libsass
    make
    cd ..

And, finally, it's time to compile and install *(if the tests pass ;-))* the PHP Extension itself:

    phpize
    ./configure --with-sass=./libsass
    make
    NO_INTERACTION=1 make test
    sudo make install

Don't forget to add the following directive to your `php.ini` file:

    extension = sass.so


## Usage

Here's an example that demonstrates how to compile a SCSS string:

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
    ?>

And here's how you would compile a SCSS file to a CSS file:

    <?php
    $inputFile = __DIR__ . '/test-scss-in';
    $outputFile = __DIR__ . '/test-css-out';

    $sass = new Sass();
    $sass->compileFile($inputFile, $outputFile);
    ?>

For more examples of what can and cannot be done, you can take a look at `--FILE--` section of the `.phpt` files in the `tests/` directory.

## API Reference

This extension provides a `Sass` class to PHP.

This class exports the following constants:

 * Possible values for the `outputStyle` option:
   * `Sass::STYLE_NESTED`
   * `Sass::STYLE_EXPANDED`
   * `Sass::STYLE_COMPACT`
   * `Sass::STYLE_COMPRESSED`
 * Possible values for the `sourceComments` option:
   * `Sass::SOURCE_COMMENTS_NONE`
   * `Sass::SOURCE_COMMENTS_DEFAULT`
   * `Sass::SOURCE_COMMENTS_MAP`

This class provides the following methods:

 * `void __construct()`
 * `string compileString(string $scss)`
   * Compiles the `$scss` string given as a parameter,
   * And return the compiled CSS.
   * Throws a `RuntimeException` if the SCSS string was invalid, and/or failed to be compiled.
 * `string|null compileFile(string $inputFile [, string $outputFile])`
   * If `$outputFile` is given, this method compiles the SCSS content of `$inputFile` to the CSS file `$outputFile`.
   * If `$outputFile` is not passed, the method compiles the SCSS content of `$inputFile` and returns the compiled CSS as a string.
   * Throws an `InvalidArgumentException` if `$inputFile` cannot be read,
   * Throws a `RuntimeException` if `$outputFile` cannot be written,
   * Throws a `RuntimeException` if the SCSS string was invalid, and/or failed to be compiled.
 * `Sass setOutputStyle(int $outputStyle)`
   * Configures the output's style.
   * Throws an `InvalidArgumentException` if `$outputStyle` is not one of the `Sass::STYLE_*` constants.
 * `Sass setSourceComments(int $sourceComments)`
   * Configures what kind of source comments, if any, must be generated.
   * Throws an `InvalidArgumentException` if `$sourceComments` is not one of the `Sass::SOURCE_COMMENTS_*` constants.
 * `Sass setIncludePaths(string $includePaths)`
   * Configures the include paths in which the libsass' compiler will look for imported files.
   * Can contain several directories paths, separated by a `:` *(on Linux)* or a `;` *(on Windows)*.
