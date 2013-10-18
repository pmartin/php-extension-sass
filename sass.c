#include "php_sass.h"


/* {{{ sass_module_entry */
zend_module_entry sass_module_entry = {
    STANDARD_MODULE_HEADER,
    "sass",
    sass_functions, /* Function entries */
    NULL, /* Module init */
    NULL, /* Module shutdown */
    NULL, /* Request init */
    NULL, /* Request shutdown */
    NULL, /* Module information */
    "0.1", /* Replace with version number for your extension */
    STANDARD_MODULE_PROPERTIES
};
/* }}} */


ZEND_BEGIN_ARG_INFO(arginfo_test, 0)
ZEND_END_ARG_INFO();


zend_function_entry sass_functions[] =
{
    PHP_FE(sass_test, arginfo_test)
    {NULL, NULL, NULL} /* Marks the end of function entries */
};


PHP_FUNCTION(sass_test)
{
    php_printf("plop\n");
}


#ifdef COMPILE_DL_SASS
ZEND_GET_MODULE(sass)
#endif
