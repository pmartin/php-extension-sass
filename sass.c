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
    struct sass_context* ctx = sass_new_context();

    struct sass_options options;
    options.output_style = SASS_STYLE_EXPANDED;
    options.source_comments = 0;
    options.image_path = "images";
    options.include_paths = "";
    ctx->options = options;

    ctx->source_string = ".test {color: red;}";

    sass_compile(ctx);

    php_printf("/* RESULT: */\n%s/* END RESULT */\n", ctx->output_string);

    sass_free_file_context(ctx);
}


#ifdef COMPILE_DL_SASS
ZEND_GET_MODULE(sass)
#endif
