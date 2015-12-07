/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:luyu                                                          |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_geo.h"
#include "geo_lib.c"
/* If you declare any globals in php_geo.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(geo)
*/

/* True global resources - no need for thread safety here */
static int le_geo;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("geo.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_geo_globals, geo_globals)
    STD_PHP_INI_ENTRY("geo.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_geo_globals, geo_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_geo_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_geo_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "geo", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto string geo_simple_distance(double longitudeA, double latitudeA, double longitudeB, double latitudeB)
    */
PHP_FUNCTION(geo_simple_distance)
{
	int argc = ZEND_NUM_ARGS();
	double longitudeA;
	double latitudeA;
	double longitudeB;
	double latitudeB;

	if (zend_parse_parameters(argc TSRMLS_CC, "dddd", &latitudeA, &longitudeA, &latitudeB, &longitudeB) == FAILURE)
		return;

	// php_error(E_WARNING, "geo_simple_distance: not yet implemented");
    RETURN_DOUBLE(simple_distance(latitudeA, longitudeA, latitudeB, longitudeB));
}
/* }}} */

PHP_FUNCTION(geo_distance)
{
    int argc = ZEND_NUM_ARGS();
    double longitudeA;
    double latitudeA;
    double longitudeB;
    double latitudeB;

    if (zend_parse_parameters(argc TSRMLS_CC, "dddd", &latitudeA, &longitudeA, &latitudeB, &longitudeB) == FAILURE)
        return;

    // php_error(E_WARNING, "geo_simple_distance: not yet implemented");
    RETURN_DOUBLE(get_distance(latitudeA, longitudeA, latitudeB, longitudeB));
}

/* {{{ proto string geo_geohash_encode(double longitude, double latitude)
    */
PHP_FUNCTION(geo_geohash_encode)
{
	int argc = ZEND_NUM_ARGS();
	double longitude;
	double latitude;
    long precision = 12;
    char * result;

	if (zend_parse_parameters(argc TSRMLS_CC, "ddl", &longitude, &latitude , &precision) == FAILURE)
		return;

    if(latitude>90.0 || latitude<-90.0){
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "latitude range from -90.0 to 90.0");
        return;
    }
    if(longitude>180.0 || longitude<-180.0){
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "longitude range from -180.0 to 180.0");
        return;
    }
    if(precision<=0){
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "precision should be a positive number");
        return;
    }


    RETVAL_STRING(geohash_encode(latitude,longitude,precision),1);
	// php_error(E_WARNING, "geo_geohash_encode: not yet implemented");
}
/* }}} */

/* {{{ proto array geo_geohash_decode(string geohash)
    */
PHP_FUNCTION(geo_geohash_decode)
{
	char *geohash = NULL;
	int argc = ZEND_NUM_ARGS();
	int geohash_len;

	if (zend_parse_parameters(argc TSRMLS_CC, "s", &geohash, &geohash_len) == FAILURE)
		return;
    coord_struct result=geohash_decode(geohash);
    array_init(return_value);
    add_assoc_double(return_value,"latitude",result.latitude);
    add_assoc_double(return_value,"longitude",result.longitude);
	// php_error(E_WARNING, "geo_geohash_decode: not yet implemented");
}
/* }}} */


/* {{{ php_geo_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_geo_init_globals(zend_geo_globals *geo_globals)
{
	geo_globals->global_value = 0;
	geo_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(geo)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(geo)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(geo)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(geo)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(geo)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "geo support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ geo_functions[]
 *
 * Every user visible function must have an entry in geo_functions[].
 */
const zend_function_entry geo_functions[] = {
	PHP_FE(confirm_geo_compiled,	NULL)		/* For testing, remove later. */
    PHP_FE(geo_simple_distance, NULL)
	PHP_FE(geo_distance,	NULL)
	PHP_FE(geo_geohash_encode,	NULL)
	PHP_FE(geo_geohash_decode,	NULL)
	PHP_FE_END	/* Must be the last line in geo_functions[] */
};
/* }}} */

/* {{{ geo_module_entry
 */
zend_module_entry geo_module_entry = {
	STANDARD_MODULE_HEADER,
	"geo",
	geo_functions,
	PHP_MINIT(geo),
	PHP_MSHUTDOWN(geo),
	PHP_RINIT(geo),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(geo),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(geo),
	PHP_GEO_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GEO
ZEND_GET_MODULE(geo)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
