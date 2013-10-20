#include "php_sass.h"


/* {{{ sass_module_entry */
zend_module_entry sass_module_entry = {
    STANDARD_MODULE_HEADER,
    "sass",
    NULL, /* Function entries */
    PHP_MINIT(sass), /* Module init */
    NULL, /* Module shutdown */
    NULL, /* Request init */
    NULL, /* Request shutdown */
    NULL, /* Module information */
    "0.1", /* Replace with version number for your extension */
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

zend_class_entry *ce_Sass;
static zend_object_handlers sass_object_handlers;


ZEND_BEGIN_ARG_INFO_EX(arginfo_sass___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sass_setOutputStyle, 0, 0, 1)
    ZEND_ARG_INFO(0, outputStyle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sass_setSourceComments, 0, 0, 1)
    ZEND_ARG_INFO(0, sourceComments)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sass_setIncludePaths, 0, 0, 1)
    ZEND_ARG_INFO(0, includePaths)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sass_compileString, 0, 0, 1)
    ZEND_ARG_INFO(0, scss)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sass_compileFile, 0, 0, 1)
    ZEND_ARG_INFO(0, inputFile)
    ZEND_ARG_INFO(0, outputFile)
ZEND_END_ARG_INFO()


static zend_function_entry sass_class_functions[] = {
    PHP_ME(Sass, __construct, arginfo_sass___construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(Sass, setOutputStyle, arginfo_sass_setOutputStyle, ZEND_ACC_PUBLIC)
    PHP_ME(Sass, setSourceComments, arginfo_sass_setSourceComments, ZEND_ACC_PUBLIC)
    PHP_ME(Sass, setIncludePaths, arginfo_sass_setIncludePaths, ZEND_ACC_PUBLIC)
    PHP_ME(Sass, compileString, arginfo_sass_compileString, ZEND_ACC_PUBLIC)
    PHP_ME(Sass, compileFile, arginfo_sass_compileFile, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};


PHP_MINIT_FUNCTION(sass)
{
    zend_class_entry ce;

    memcpy(&sass_object_handlers, zend_get_std_object_handlers(),
            sizeof(zend_object_handlers));
    sass_object_handlers.cast_object = sass_object_cast;

    INIT_CLASS_ENTRY(ce, "Sass", sass_class_functions);
    ce.create_object = sass_object_new;
    ce_Sass = zend_register_internal_class(&ce TSRMLS_CC);

    zend_declare_class_constant_long(ce_Sass, ZEND_STRL("STYLE_NESTED"), SASS_STYLE_NESTED TSRMLS_CC);
    zend_declare_class_constant_long(ce_Sass, ZEND_STRL("STYLE_EXPANDED"), SASS_STYLE_EXPANDED TSRMLS_CC);
    zend_declare_class_constant_long(ce_Sass, ZEND_STRL("STYLE_COMPACT"), SASS_STYLE_COMPACT TSRMLS_CC);
    zend_declare_class_constant_long(ce_Sass, ZEND_STRL("STYLE_COMPRESSED"), SASS_STYLE_COMPRESSED TSRMLS_CC);

    zend_declare_class_constant_long(ce_Sass, ZEND_STRL("SOURCE_COMMENTS_NONE"), SASS_SOURCE_COMMENTS_NONE TSRMLS_CC);
    zend_declare_class_constant_long(ce_Sass, ZEND_STRL("SOURCE_COMMENTS_DEFAULT"), SASS_SOURCE_COMMENTS_DEFAULT TSRMLS_CC);
    zend_declare_class_constant_long(ce_Sass, ZEND_STRL("SOURCE_COMMENTS_MAP"), SASS_SOURCE_COMMENTS_MAP TSRMLS_CC);

    return SUCCESS;
}


zend_object_value sass_object_new(zend_class_entry *class_type TSRMLS_DC)
{
    zend_object_value retval;

    sass_object *intern = emalloc(sizeof(sass_object));
    memset(intern, 0, sizeof(sass_object));

    zend_object_std_init(&intern->zo, class_type TSRMLS_CC);

    retval.handle = zend_objects_store_put(
        intern,
        (zend_objects_store_dtor_t) zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)sass_object_free,
        NULL TSRMLS_CC
    );

    retval.handlers = &sass_object_handlers;

    return retval;
}


void sass_object_free(void *_object TSRMLS_DC)
{
    sass_object *object = (sass_object *)_object;
    zend_object_std_dtor(&object->zo TSRMLS_CC);

    if (object->options.include_paths != NULL)
    {
        efree(object->options.include_paths);
    }

    efree(object);
}


int sass_object_cast(zval *readobj, zval *writeobj, int type TSRMLS_DC)
{
    php_printf("sass_object_cast\n");

    sass_object *object = (sass_object *)zend_object_store_get_object(readobj TSRMLS_CC);

    return FAILURE;
}


PHP_METHOD(Sass, __construct)
{
    sass_object *object = (sass_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

    // Default options
    object->options.output_style = SASS_STYLE_EXPANDED;
    object->options.source_comments = 0;
    object->options.image_path = "images";
    object->options.include_paths = NULL;
}


PHP_METHOD(Sass, setOutputStyle)
{
    long style;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &style) == FAILURE)
    {
        return;
    }

    if (style != SASS_STYLE_NESTED && style != SASS_STYLE_EXPANDED
            && style != SASS_STYLE_COMPACT && style != SASS_STYLE_COMPRESSED)
    {
        char *msg;
        spprintf(&msg, 0, "Invalid style: %ld", style);
        zend_throw_exception(spl_ce_InvalidArgumentException, msg, 1 TSRMLS_CC);
        efree(msg);
    }

    sass_object *object = (sass_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    object->options.output_style = style;

    RETURN_ZVAL(getThis(), 1, 0);
}


PHP_METHOD(Sass, setSourceComments)
{
    long source_comments;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",
            &source_comments) == FAILURE)
    {
        return;
    }

    if (source_comments != SASS_SOURCE_COMMENTS_NONE
            && source_comments != SASS_SOURCE_COMMENTS_DEFAULT
            && source_comments != SASS_SOURCE_COMMENTS_MAP)
    {
        char *msg;
        spprintf(&msg, 0, "Invalid sourceComments: %ld", source_comments);
        zend_throw_exception(spl_ce_InvalidArgumentException, msg, 1 TSRMLS_CC);
        efree(msg);
    }

    sass_object *object = (sass_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
    object->options.source_comments = source_comments;

    RETURN_ZVAL(getThis(), 1, 0);
}


PHP_METHOD(Sass, setIncludePaths)
{
    char *paths;
    int paths_length;
    if (zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s",
            &paths, &paths_length ) == FAILURE)
    {
        return;
    }

    sass_object *object = (sass_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

    if (object->options.include_paths != NULL)
    {
        efree(object->options.include_paths);
    }
    object->options.include_paths = emalloc(paths_length + 1);

    strncpy(object->options.include_paths, paths, paths_length);
    object->options.include_paths[paths_length] = '\0';

    RETURN_ZVAL(getThis(), 1, 0);
}


PHP_METHOD(Sass, compileString)
{
    char *css_string;
    int css_length;
    if (zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s",
            &css_string, &css_length ) == FAILURE)
    {
        return;
    }

    // Transform css_string to a standard C null-terminated string
    erealloc(css_string, css_length + 1);
    css_string[css_length] = '\0';

    sass_object *object = (sass_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

    struct sass_context* ctx = sass_new_context();
    ctx->options = object->options;
    ctx->source_string = css_string;

    sass_compile(ctx);

    if (ctx->error_status == 0)
    {
        RETVAL_STRING(ctx->output_string, 1);
    }
    else
    {
        char *msg = php_trim(ctx->error_message, strlen(ctx->error_message),
                NULL, 0, NULL, 3 TSRMLS_CC);
        zend_throw_exception(spl_ce_RuntimeException, msg,
                ctx->error_status TSRMLS_CC);
        efree(msg);
    }

    sass_free_context(ctx);
}


PHP_METHOD(Sass, compileFile)
{
    char *input_path, *output_path = NULL;
    int input_path_length, output_path_length = 0;
    if (zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s|s",
            &input_path, &input_path_length,
            &output_path, &output_path_length ) == FAILURE)
    {
        return;
    }

    // Transform input_path to a standard C null-terminated string
    erealloc(input_path, input_path_length + 1);
    input_path[input_path_length] = '\0';

    if (access(input_path, R_OK) == -1)
    {
        char *msg;
        spprintf(&msg, 0, "Cannot read file %s", input_path);
        zend_throw_exception(spl_ce_InvalidArgumentException, msg, 2 TSRMLS_CC);
        efree(msg);
        return;
    }

    sass_object *object = (sass_object *)zend_object_store_get_object(getThis() TSRMLS_CC);

    struct sass_file_context *ctx = sass_new_file_context();
    ctx->options = object->options;
    ctx->input_path = input_path;

    sass_compile_file(ctx);

    if (ctx->error_status == 0)
    {
        if (output_path == NULL)
        {
            RETVAL_STRING(ctx->output_string, 1);
        }
        else
        {
            // Transform output_path to a standard C null-terminated string
            erealloc(output_path, output_path_length + 1);
            output_path[output_path_length] = '\0';

            FILE *out_file = fopen(output_path, "w");
            if (out_file)
            {
                fputs(ctx->output_string, out_file);
                fclose(out_file);
            }
            else
            {
                char *msg;
                spprintf(&msg, 0, "Cannot write to %s", output_path);
                zend_throw_exception(spl_ce_RuntimeException, msg, 3 TSRMLS_CC);
                efree(msg);
            }
        }
    }
    else
    {
        char *msg = php_trim(ctx->error_message, strlen(ctx->error_message),
                NULL, 0, NULL, 3 TSRMLS_CC);
        zend_throw_exception(spl_ce_RuntimeException, msg,
                ctx->error_status TSRMLS_CC);
        efree(msg);
    }

    sass_free_file_context(ctx);
}


#ifdef COMPILE_DL_SASS
ZEND_GET_MODULE(sass)
#endif
