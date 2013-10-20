Getting the sources of the extension (+ the library):

    git clone .git@github.com:pmartin/php-extension-sass.git
    git submodule init
    git submodule update


Compiling the (static) libsass.a library:
Its sources are in a git submodule: libsass/

    cd libsass
    make
    #  => this creates the libsass.a static library
    # /!\ Needs to be run after a 'make clean' for the extension


Configuring and compiling the extension (PHP 5.3):

    $HOME/bin/php-5.3-debug/bin/phpize
    ./configure --with-sass=./libsass \
        --with-php-config=$HOME/bin/php-5.3-debug/bin/php-config
    make
    make test

Configuring and compiling the extension (PHP 5.4):

    $HOME/bin/php-5.4-debug/bin/phpize
    ./configure --with-sass=./libsass \
        --with-php-config=$HOME/bin/php-5.4-debug/bin/php-config
    make
    make test


To execute the tests without any interaction:

    export NO_INTERACTION=1
    make test
