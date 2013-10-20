#ifndef SASS_H_
#define SASS_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/standard/php_string.h"
#include "zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"

#include "sass_interface.h"

extern zend_module_entry sass_module_entry;


PHP_MINIT_FUNCTION(sass);
PHP_MINFO_FUNCTION(sass);


extern zend_class_entry *ce_Sass;


typedef struct {
    zend_object zo;
    struct sass_options options;
} sass_object;


zend_object_value sass_object_new(zend_class_entry *class_type TSRMLS_DC);
int sass_object_cast(zval *readobj, zval *writeobj, int type TSRMLS_DC);
void sass_object_free(void *_object TSRMLS_DC);

PHP_METHOD(Sass, __construct);
PHP_METHOD(Sass, setOutputStyle);
PHP_METHOD(Sass, setSourceComments);
PHP_METHOD(Sass, setIncludePaths);
PHP_METHOD(Sass, compileString);
PHP_METHOD(Sass, compileFile);


#endif /* SASS_H_ */
