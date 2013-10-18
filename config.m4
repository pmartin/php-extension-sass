
PHP_ARG_ENABLE(sass, whether to enable sass support,
[  --enable-sass         Enable sass support])

if test "$PHP_SASS" = "yes"; then
    PHP_NEW_EXTENSION(sass, sass.c, $ext_shared)
fi
