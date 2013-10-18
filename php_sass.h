#ifndef SASS_H_
#define SASS_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

extern zend_module_entry sass_module_entry;
extern zend_function_entry sass_functions[];


PHP_FUNCTION(sass_test);


#endif /* SASS_H_ */
