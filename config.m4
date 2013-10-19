dnl config.m4 for extension sass

PHP_ARG_WITH(sass, whether to enable sass support,
[  --with-sass             Include sass support])

if test "$PHP_SASS" != "no"; then
    SEARCH_PATH="$PHP_SASS /usr/local /usr"
    SEARCH_INC="sass_interface.h"
    SEARCH_LIB="libsass.a"
    
    AC_MSG_CHECKING([for sass files])
    for i in $SEARCH_PATH ; do
        if test -r $i/$SEARCH_INC && test -r $i/$SEARCH_LIB; then
            SASS_DIR=$i
            AC_MSG_RESULT(found in $i)
        fi
    done
    if test -z "$SASS_DIR"; then
        AC_MSG_RESULT([not found])
        AC_MSG_ERROR([Please ensure the sass headers and static library are installed])
    fi
    
    PHP_ADD_INCLUDE($SASS_DIR)
    
    PHP_REQUIRE_CXX()
    
    PHP_ADD_LIBRARY(stdc++, 1, SASS_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(sass, $SASS_DIR, SASS_SHARED_LIBADD)
    PHP_SUBST(SASS_SHARED_LIBADD)
    
    PHP_NEW_EXTENSION(sass, sass.c, $ext_shared,,,1)
fi
