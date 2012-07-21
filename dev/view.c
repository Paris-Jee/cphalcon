
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2012 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  +------------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_phalcon.h"
#include "phalcon.h"

#include "Zend/zend_operators.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_interfaces.h"

#include "kernel/main.h"
#include "kernel/memory.h"

#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/operators.h"

/**
 * Phalcon\iew
 *
 * Phalcon_View is a class for working with the "view" portion of the model-view-controller pattern.
 * That is, it exists to help keep the view script separate from the model and controller scripts.
 * It provides a system of helpers, output filters, and variable escaping.
 *
 * 
 */

/**
 * Phalcon_View constructor
 *
 * @param Phalcon_Config|stClass $options
 */
PHP_METHOD(Phalcon_View, __construct){

	zval *options = NULL, *view_options = NULL;
	zval *a0 = NULL, *a1 = NULL, *a2 = NULL, *a3 = NULL, *a4 = NULL;

	PHALCON_MM_GROW();
	
	PHALCON_ALLOC_ZVAL_MM(a0);
	array_init(a0);
	zend_update_property(phalcon_view_ce, this_ptr, SL("_viewParams"), a0 TSRMLS_CC);
	
	PHALCON_ALLOC_ZVAL_MM(a1);
	array_init(a1);
	zend_update_property(phalcon_view_ce, this_ptr, SL("_templatesBefore"), a1 TSRMLS_CC);
	
	PHALCON_ALLOC_ZVAL_MM(a2);
	array_init(a2);
	zend_update_property(phalcon_view_ce, this_ptr, SL("_templatesAfter"), a2 TSRMLS_CC);
	
	PHALCON_ALLOC_ZVAL_MM(a3);
	array_init(a3);
	zend_update_property(phalcon_view_ce, this_ptr, SL("_registeredEngines"), a3 TSRMLS_CC);
	
	PHALCON_ALLOC_ZVAL_MM(a4);
	array_init(a4);
	zend_update_property(phalcon_view_ce, this_ptr, SL("_params"), a4 TSRMLS_CC);
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &options) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!options) {
		PHALCON_ALLOC_ZVAL_MM(options);
		ZVAL_NULL(options);
	}
	
	if (zend_is_true(options)) {
		if (Z_TYPE_P(options) != IS_OBJECT) {
			PHALCON_THROW_EXCEPTION_STR(phalcon_model_exception_ce, "Options parameter must be an object");
			return;
		}
		PHALCON_CPY_WRT(view_options, options);
	} else {
		PHALCON_INIT_VAR(view_options);
		object_init(view_options);
	}
	phalcon_update_property_zval(this_ptr, SL("_options"), view_options TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Sets views directory. Depending of your platform, always add a trailing slash or backslash
 *
 * @param string $viewsDir
 */
PHP_METHOD(Phalcon_View, setViewsDir){

	zval *views_dir = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &views_dir) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, SL("_viewsDir"), views_dir TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Gets views directory
 *
 * @return string
 */
PHP_METHOD(Phalcon_View, getViewsDir){

	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_viewsDir"), PH_NOISY_CC);
	
	RETURN_CCTOR(t0);
}

/**
 * Sets base path. Depending of your platform, always add a trailing slash or backslash
 *
 * @param string $basePath
 */
PHP_METHOD(Phalcon_View, setBasePath){

	zval *base_path = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &base_path) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, SL("_basePath"), base_path TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Sets the render level for the view
 *
 * @param string $level
 */
PHP_METHOD(Phalcon_View, setRenderLevel){

	zval *level = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &level) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, SL("_renderLevel"), level TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Sets default view name. Must be a file without extension in the views directory
 *
 * @param string $name
 */
PHP_METHOD(Phalcon_View, setMainView){

	zval *view_path = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &view_path) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, SL("_mainView"), view_path TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Appends template before controller layout
 *
 * @param string|array $templateBefore
 */
PHP_METHOD(Phalcon_View, setTemplateBefore){

	zval *template_before = NULL;
	zval *a0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &template_before) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (Z_TYPE_P(template_before) != IS_ARRAY) { 
		PHALCON_ALLOC_ZVAL_MM(a0);
		array_init(a0);
		phalcon_array_append(&a0, template_before, PH_SEPARATE TSRMLS_CC);
		phalcon_update_property_zval(this_ptr, SL("_templatesBefore"), a0 TSRMLS_CC);
	} else {
		phalcon_update_property_zval(this_ptr, SL("_templatesBefore"), template_before TSRMLS_CC);
	}
	
	PHALCON_MM_RESTORE();
}

/**
 * Resets any template before layouts
 *
 */
PHP_METHOD(Phalcon_View, cleanTemplateBefore){


	PHALCON_MM_GROW();
	phalcon_update_property_null(this_ptr, SL("_templatesBefore") TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Appends template after controller layout
 *
 * @param string|array $templateAfter
 */
PHP_METHOD(Phalcon_View, setTemplateAfter){

	zval *template_after = NULL;
	zval *a0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &template_after) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (Z_TYPE_P(template_after) != IS_ARRAY) { 
		PHALCON_ALLOC_ZVAL_MM(a0);
		array_init(a0);
		phalcon_array_append(&a0, template_after, PH_SEPARATE TSRMLS_CC);
		phalcon_update_property_zval(this_ptr, SL("_templatesAfter"), a0 TSRMLS_CC);
	} else {
		phalcon_update_property_zval(this_ptr, SL("_templatesAfter"), template_after TSRMLS_CC);
	}
	
	PHALCON_MM_RESTORE();
}

/**
 * Resets any template before layouts
 *
 */
PHP_METHOD(Phalcon_View, cleanTemplateAfter){


	PHALCON_MM_GROW();
	phalcon_update_property_null(this_ptr, SL("_templatesAfter") TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Adds parameters to views (alias of setVar)
 *
 * @param string $key
 * @param mixed $value
 */
PHP_METHOD(Phalcon_View, setParamToView){

	zval *key = NULL, *value = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &key, &value) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_viewParams"), PH_NOISY_CC);
	phalcon_array_update(&t0, key, &value, PH_COPY TSRMLS_CC);
	phalcon_update_property_zval(this_ptr, SL("_viewParams"), t0 TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Adds parameters to views
 *
 * @param string $key
 * @param mixed $value
 */
PHP_METHOD(Phalcon_View, setVar){

	zval *key = NULL, *value = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &key, &value) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_viewParams"), PH_NOISY_CC);
	phalcon_array_update(&t0, key, &value, PH_COPY TSRMLS_CC);
	phalcon_update_property_zval(this_ptr, SL("_viewParams"), t0 TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Returns parameters to views
 *
 * @return array
 */
PHP_METHOD(Phalcon_View, getParamsToView){

	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_viewParams"), PH_NOISY_CC);
	
	RETURN_CCTOR(t0);
}

/**
 * Gets the name of the controller rendered
 *
 * @return string
 */
PHP_METHOD(Phalcon_View, getControllerName){

	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_controllerName"), PH_NOISY_CC);
	
	RETURN_CCTOR(t0);
}

/**
 * Gets the name of the action rendered
 *
 * @return string
 */
PHP_METHOD(Phalcon_View, getActionName){

	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_actionName"), PH_NOISY_CC);
	
	RETURN_CCTOR(t0);
}

/**
 * Gets extra parameters of the action rendered
 */
PHP_METHOD(Phalcon_View, getParams){

	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_params"), PH_NOISY_CC);
	
	RETURN_CCTOR(t0);
}

/**
 * Starts rendering process enabling the output buffering
 */
PHP_METHOD(Phalcon_View, start){


	PHALCON_MM_GROW();
	phalcon_update_property_null(this_ptr, SL("_content") TSRMLS_CC);
	PHALCON_CALL_FUNC_NORETURN("ob_start");
	
	PHALCON_MM_RESTORE();
}

/**
 * Loads registered template engines, if none is registered use Phalcon_View_Engine_Php
 *
 * @return array
 */
PHP_METHOD(Phalcon_View, _loadTemplateEngines){

	zval *engines = NULL, *registered_engines = NULL, *engine = NULL;
	zval *extension = NULL, *options = NULL, *name = NULL, *class_name = NULL;
	zval *t0 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL;
	zval *i0 = NULL, *i1 = NULL, *i2 = NULL;
	zval *a0 = NULL;
	HashTable *ah0;
	HashPosition hp0;
	zval **hd;
	char *hash_index;
	uint hash_index_len;
	ulong hash_num;
	int hash_type;
	int eval_int;
	zend_class_entry *ce0;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_engines"), PH_NOISY_CC);
	if (!zend_is_true(t0)) {
		PHALCON_INIT_VAR(engines);
		array_init(engines);
		
		PHALCON_INIT_VAR(registered_engines);
		phalcon_read_property(&registered_engines, this_ptr, SL("_registeredEngines"), PH_NOISY_CC);
		
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_fast_count(r0, registered_engines TSRMLS_CC);
		if (!zend_is_true(r0)) {
			PHALCON_ALLOC_ZVAL_MM(i0);
			object_init_ex(i0, phalcon_view_engine_php_ce);
			PHALCON_ALLOC_ZVAL_MM(a0);
			array_init(a0);
			PHALCON_CALL_METHOD_PARAMS_2_NORETURN(i0, "__construct", this_ptr, a0, PH_CHECK);
			phalcon_array_update_string(&engines, SL(".phtml"), &i0, PH_COPY | PH_SEPARATE TSRMLS_CC);
		} else {
			if (phalcon_valid_foreach(registered_engines TSRMLS_CC)) {
				ah0 = Z_ARRVAL_P(registered_engines);
				zend_hash_internal_pointer_reset_ex(ah0, &hp0);
				fes_b0d8_0:
				if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
					goto fee_b0d8_0;
				} else {
					PHALCON_INIT_VAR(extension);
					PHALCON_GET_FOREACH_KEY(extension, ah0, hp0);
				}
				PHALCON_INIT_VAR(engine);
				ZVAL_ZVAL(engine, *hd, 1, 0);
				PHALCON_INIT_VAR(options);
				array_init(options);
				if (Z_TYPE_P(engine) == IS_ARRAY) { 
					eval_int = phalcon_array_isset_long(engine, 0);
					if (eval_int) {
						PHALCON_INIT_VAR(name);
						phalcon_array_fetch_long(&name, engine, 0, PH_NOISY_CC);
					} else {
						PHALCON_THROW_EXCEPTION_STR(phalcon_view_exception_ce, "The template engine name is required");
						return;
					}
					eval_int = phalcon_array_isset_long(engine, 1);
					if (eval_int) {
						PHALCON_INIT_VAR(options);
						phalcon_array_fetch_long(&options, engine, 1, PH_NOISY_CC);
					}
				} else {
					if (Z_TYPE_P(engine) == IS_STRING) {
						PHALCON_CPY_WRT(name, engine);
					} else {
						if (Z_TYPE_P(engine) == IS_OBJECT) {
							PHALCON_CALL_METHOD_PARAMS_2_NORETURN(engine, "initialize", this_ptr, options, PH_NO_CHECK);
							phalcon_array_update(&engines, extension, &engine, PH_COPY | PH_SEPARATE TSRMLS_CC);
							goto fes_b0d8_0;
						} else {
							PHALCON_THROW_EXCEPTION_STR(phalcon_view_exception_ce, "The template engine is invalid");
							return;
						}
					}
				}
				
				PHALCON_INIT_VAR(class_name);
				PHALCON_CONCAT_SV(class_name, "Phalcon\\View\\Engine\\", name);
				
				PHALCON_INIT_VAR(r1);
				PHALCON_CALL_FUNC_PARAMS_1(r1, "class_exists", class_name);
				if (zend_is_true(r1)) {
					ce0 = phalcon_fetch_class(class_name TSRMLS_CC);
					PHALCON_INIT_VAR(i1);
					object_init_ex(i1, ce0);
					PHALCON_CALL_METHOD_PARAMS_2_NORETURN(i1, "__construct", this_ptr, options, PH_CHECK);
					phalcon_array_update(&engines, extension, &i1, PH_COPY | PH_SEPARATE TSRMLS_CC);
				} else {
					PHALCON_INIT_VAR(i2);
					object_init_ex(i2, phalcon_view_exception_ce);
					PHALCON_INIT_VAR(r2);
					PHALCON_CONCAT_SVS(r2, "Template engine '", class_name, "' cannot be loaded");
					PHALCON_CALL_METHOD_PARAMS_1_NORETURN(i2, "__construct", r2, PH_CHECK);
					phalcon_throw_exception(i2 TSRMLS_CC);
					return;
				}
				zend_hash_move_forward_ex(ah0, &hp0);
				goto fes_b0d8_0;
				fee_b0d8_0:
				if(0){}
			} else {
				return;
			}
		}
		
		phalcon_update_property_zval(this_ptr, SL("_engines"), engines TSRMLS_CC);
	} else {
		PHALCON_INIT_VAR(engines);
		phalcon_read_property(&engines, this_ptr, SL("_engines"), PH_NOISY_CC);
	}
	
	RETURN_CCTOR(engines);
}

/**
 * Checks whether view exists on registered extensions and render it
 *
 * @param array $engines
 * @param string $viewPath
 * @param boolean $silence
 * @param Phalcon_Cache $cache
 */
PHP_METHOD(Phalcon_View, _engineRender){

	zval *engines = NULL, *view_path = NULL, *silence = NULL, *cache = NULL, *not_exists = NULL;
	zval *view_params = NULL, *views_dir_path = NULL, *render_level = NULL;
	zval *cache_level = NULL, *key = NULL, *view_options = NULL, *cache_options = NULL;
	zval *cached_view = NULL, *engine = NULL, *extension = NULL, *view_engine_path = NULL;
	zval *t0 = NULL, *t1 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL;
	zval *i0 = NULL;
	HashTable *ah0;
	HashPosition hp0;
	zval **hd;
	char *hash_index;
	uint hash_index_len;
	ulong hash_num;
	int hash_type;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzzz", &engines, &view_path, &silence, &cache) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(not_exists);
	ZVAL_BOOL(not_exists, 1);
	
	PHALCON_INIT_VAR(view_params);
	phalcon_read_property(&view_params, this_ptr, SL("_viewParams"), PH_NOISY_CC);
	
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_basePath"), PH_NOISY_CC);
	
	PHALCON_ALLOC_ZVAL_MM(t1);
	phalcon_read_property(&t1, this_ptr, SL("_viewsDir"), PH_NOISY_CC);
	
	PHALCON_INIT_VAR(views_dir_path);
	PHALCON_CONCAT_VVV(views_dir_path, t0, t1, view_path);
	if (zend_is_true(cache)) {
		PHALCON_INIT_VAR(render_level);
		phalcon_read_property(&render_level, this_ptr, SL("_renderLevel"), PH_NOISY_CC);
		
		PHALCON_INIT_VAR(cache_level);
		phalcon_read_property(&cache_level, this_ptr, SL("_cacheLevel"), PH_NOISY_CC);
		
		PHALCON_ALLOC_ZVAL_MM(r0);
		is_smaller_or_equal_function(r0, cache_level, render_level TSRMLS_CC);
		if (zend_is_true(r0)) {
			PHALCON_ALLOC_ZVAL_MM(r1);
			PHALCON_CALL_METHOD(r1, cache, "isstarted", PH_NO_CHECK);
			if (!zend_is_true(r1)) {
				PHALCON_INIT_VAR(key);
				ZVAL_NULL(key);
				
				PHALCON_INIT_VAR(view_options);
				phalcon_read_property(&view_options, this_ptr, SL("_options"), PH_NOISY_CC);
				eval_int = phalcon_isset_property(view_options, SL("cache") TSRMLS_CC);
				if (eval_int) {
					PHALCON_INIT_VAR(cache_options);
					phalcon_read_property(&cache_options, view_options, SL("cache"), PH_NOISY_CC);
					if (Z_TYPE_P(cache_options) == IS_OBJECT) {
						eval_int = phalcon_isset_property(cache_options, SL("key") TSRMLS_CC);
						if (eval_int) {
							PHALCON_INIT_VAR(key);
							phalcon_read_property(&key, cache_options, SL("key"), PH_NOISY_CC);
						}
					}
				}
				
				if (!zend_is_true(key)) {
					PHALCON_INIT_VAR(key);
					PHALCON_CALL_FUNC_PARAMS_1(key, "md5", view_path);
				}
				
				PHALCON_INIT_VAR(cached_view);
				PHALCON_CALL_METHOD_PARAMS_1(cached_view, cache, "start", key, PH_NO_CHECK);
				if (Z_TYPE_P(cached_view) != IS_NULL) {
					phalcon_update_property_zval(this_ptr, SL("_content"), cached_view TSRMLS_CC);
					PHALCON_MM_RESTORE();
					RETURN_NULL();
				}
			}
			
			PHALCON_ALLOC_ZVAL_MM(r2);
			PHALCON_CALL_METHOD(r2, cache, "isfresh", PH_NO_CHECK);
			if (!zend_is_true(r2)) {
				PHALCON_MM_RESTORE();
				RETURN_NULL();
			}
		}
	}
	
	if (phalcon_valid_foreach(engines TSRMLS_CC)) {
		ah0 = Z_ARRVAL_P(engines);
		zend_hash_internal_pointer_reset_ex(ah0, &hp0);
		fes_b0d8_1:
		if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
			goto fee_b0d8_1;
		} else {
			PHALCON_INIT_VAR(extension);
			PHALCON_GET_FOREACH_KEY(extension, ah0, hp0);
		}
		PHALCON_INIT_VAR(engine);
		ZVAL_ZVAL(engine, *hd, 1, 0);
		PHALCON_INIT_VAR(view_engine_path);
		PHALCON_CONCAT_VV(view_engine_path, views_dir_path, extension);
		if (phalcon_file_exists(view_engine_path TSRMLS_CC) == SUCCESS) {
			PHALCON_CALL_METHOD_PARAMS_2_NORETURN(engine, "render", view_engine_path, view_params, PH_NO_CHECK);
			
			PHALCON_INIT_VAR(not_exists);
			ZVAL_BOOL(not_exists, 0);
			goto fee_b0d8_1;
		}
		zend_hash_move_forward_ex(ah0, &hp0);
		goto fes_b0d8_1;
		fee_b0d8_1:
		if(0){}
	} else {
		return;
	}
	if (zend_is_true(not_exists)) {
		if (!zend_is_true(silence)) {
			PHALCON_ALLOC_ZVAL_MM(i0);
			object_init_ex(i0, phalcon_view_exception_ce);
			PHALCON_ALLOC_ZVAL_MM(r3);
			PHALCON_CONCAT_SVS(r3, "View '", views_dir_path, "' was not found in the views directory");
			PHALCON_CALL_METHOD_PARAMS_1_NORETURN(i0, "__construct", r3, PH_CHECK);
			phalcon_throw_exception(i0 TSRMLS_CC);
			return;
		}
	}
	
	PHALCON_MM_RESTORE();
}

/**
 * Register templating engines
 *
 * @param array $engines
 */
PHP_METHOD(Phalcon_View, registerEngines){

	zval *engines = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &engines) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (Z_TYPE_P(engines) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STR(phalcon_view_exception_ce, "Engines to register must be an array");
		return;
	}
	phalcon_update_property_zval(this_ptr, SL("_registeredEngines"), engines TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Executes render process from request data
 *
 * @param string $controllerName
 * @param string $actionName
 * @param array $params
 */
PHP_METHOD(Phalcon_View, render){

	zval *controller_name = NULL, *action_name = NULL, *params = NULL;
	zval *layouts_dir = NULL, *engines = NULL, *pick_view = NULL, *render_view = NULL;
	zval *render_controller = NULL, *cache = NULL, *cache_level = NULL;
	zval *silence = NULL, *render_level = NULL, *templates_before = NULL;
	zval *template_before = NULL, *templates_after = NULL, *template_after = NULL;
	zval *a0 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL, *r5 = NULL, *r6 = NULL;
	zval *r7 = NULL, *r8 = NULL, *r9 = NULL, *r10 = NULL, *r11 = NULL, *r12 = NULL;
	zval *t0 = NULL, *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL, *t5 = NULL;
	HashTable *ah0, *ah1;
	HashPosition hp0, hp1;
	zval **hd;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz|z", &controller_name, &action_name, &params) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!params) {
		PHALCON_ALLOC_ZVAL_MM(a0);
		array_init(a0);
		PHALCON_CPY_WRT(params, a0);
	}
	
	PHALCON_INIT_VAR(layouts_dir);
	phalcon_read_property(&layouts_dir, this_ptr, SL("_layoutsDir"), PH_NOISY_CC);
	if (!zend_is_true(layouts_dir)) {
		PHALCON_INIT_VAR(layouts_dir);
		ZVAL_STRING(layouts_dir, "layouts/", 1);
	}
	
	phalcon_update_property_zval(this_ptr, SL("_controllerName"), controller_name TSRMLS_CC);
	phalcon_update_property_zval(this_ptr, SL("_actionName"), action_name TSRMLS_CC);
	phalcon_update_property_zval(this_ptr, SL("_params"), params TSRMLS_CC);
	phalcon_update_property_bool(this_ptr, SL("_initEngines"), 0 TSRMLS_CC);
	
	PHALCON_INIT_VAR(engines);
	PHALCON_CALL_METHOD(engines, this_ptr, "_loadtemplateengines", PH_NO_CHECK);
	
	PHALCON_INIT_VAR(pick_view);
	phalcon_read_property(&pick_view, this_ptr, SL("_pickView"), PH_NOISY_CC);
	if (!zend_is_true(pick_view)) {
		PHALCON_INIT_VAR(render_view);
		PHALCON_CONCAT_VSV(render_view, controller_name, "/", action_name);
		PHALCON_CPY_WRT(render_controller, controller_name);
	} else {
		PHALCON_INIT_VAR(render_view);
		phalcon_array_fetch_long(&render_view, pick_view, 0, PH_NOISY_CC);
		eval_int = phalcon_array_isset_long(pick_view, 1);
		if (eval_int) {
			PHALCON_INIT_VAR(render_controller);
			phalcon_array_fetch_long(&render_controller, pick_view, 1, PH_NOISY_CC);
		} else {
			PHALCON_CPY_WRT(render_controller, controller_name);
		}
	}
	
	PHALCON_INIT_VAR(cache);
	ZVAL_NULL(cache);
	
	PHALCON_INIT_VAR(cache_level);
	phalcon_read_property(&cache_level, this_ptr, SL("_cacheLevel"), PH_NOISY_CC);
	if (zend_is_true(cache_level)) {
		PHALCON_INIT_VAR(cache);
		PHALCON_CALL_METHOD(cache, this_ptr, "getcache", PH_NO_CHECK);
	}
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_FUNC(r0, "ob_get_contents");
	phalcon_update_property_zval(this_ptr, SL("_content"), r0 TSRMLS_CC);
	
	PHALCON_INIT_VAR(silence);
	ZVAL_BOOL(silence, 1);
	
	PHALCON_INIT_VAR(render_level);
	phalcon_read_property(&render_level, this_ptr, SL("_renderLevel"), PH_NOISY_CC);
	if (zend_is_true(render_level)) {
		PHALCON_INIT_VAR(t0);
		ZVAL_LONG(t0, 1);
		PHALCON_ALLOC_ZVAL_MM(r1);
		is_smaller_or_equal_function(r1, t0, render_level TSRMLS_CC);
		if (zend_is_true(r1)) {
			PHALCON_CALL_METHOD_PARAMS_4_NORETURN(this_ptr, "_enginerender", engines, render_view, silence, cache, PH_NO_CHECK);
		}
		
		PHALCON_INIT_VAR(t1);
		ZVAL_LONG(t1, 2);
		
		PHALCON_ALLOC_ZVAL_MM(r2);
		is_smaller_or_equal_function(r2, t1, render_level TSRMLS_CC);
		if (zend_is_true(r2)) {
			PHALCON_INIT_VAR(templates_before);
			phalcon_read_property(&templates_before, this_ptr, SL("_templatesBefore"), PH_NOISY_CC);
			if (zend_is_true(templates_before)) {
				PHALCON_INIT_VAR(silence);
				ZVAL_BOOL(silence, 0);
				if (Z_TYPE_P(templates_before) == IS_ARRAY) { 
					if (phalcon_valid_foreach(templates_before TSRMLS_CC)) {
						ah0 = Z_ARRVAL_P(templates_before);
						zend_hash_internal_pointer_reset_ex(ah0, &hp0);
						fes_b0d8_2:
						if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
							goto fee_b0d8_2;
						}
						PHALCON_INIT_VAR(template_before);
						ZVAL_ZVAL(template_before, *hd, 1, 0);
						PHALCON_INIT_VAR(r3);
						PHALCON_CONCAT_VV(r3, layouts_dir, template_before);
						PHALCON_CALL_METHOD_PARAMS_4_NORETURN(this_ptr, "_enginerender", engines, r3, silence, cache, PH_NO_CHECK);
						zend_hash_move_forward_ex(ah0, &hp0);
						goto fes_b0d8_2;
						fee_b0d8_2:
						if(0){}
					} else {
						return;
					}
				} else {
					PHALCON_ALLOC_ZVAL_MM(r4);
					PHALCON_CONCAT_VV(r4, layouts_dir, template_before);
					PHALCON_CALL_METHOD_PARAMS_4_NORETURN(this_ptr, "_enginerender", engines, r4, silence, cache, PH_NO_CHECK);
				}
				
				PHALCON_INIT_VAR(silence);
				ZVAL_BOOL(silence, 1);
			}
		}
		
		PHALCON_INIT_VAR(t2);
		ZVAL_LONG(t2, 3);
		
		PHALCON_ALLOC_ZVAL_MM(r5);
		is_smaller_or_equal_function(r5, t2, render_level TSRMLS_CC);
		if (zend_is_true(r5)) {
			PHALCON_ALLOC_ZVAL_MM(r6);
			PHALCON_CONCAT_VV(r6, layouts_dir, render_controller);
			PHALCON_CALL_METHOD_PARAMS_4_NORETURN(this_ptr, "_enginerender", engines, r6, silence, cache, PH_NO_CHECK);
		}
		
		PHALCON_INIT_VAR(t3);
		ZVAL_LONG(t3, 4);
		
		PHALCON_ALLOC_ZVAL_MM(r7);
		is_smaller_or_equal_function(r7, t3, render_level TSRMLS_CC);
		if (zend_is_true(r7)) {
			PHALCON_INIT_VAR(templates_after);
			phalcon_read_property(&templates_after, this_ptr, SL("_templatesAfter"), PH_NOISY_CC);
			if (zend_is_true(templates_after)) {
				PHALCON_INIT_VAR(silence);
				ZVAL_BOOL(silence, 0);
				if (Z_TYPE_P(templates_after) == IS_ARRAY) { 
					if (phalcon_valid_foreach(templates_after TSRMLS_CC)) {
						ah1 = Z_ARRVAL_P(templates_after);
						zend_hash_internal_pointer_reset_ex(ah1, &hp1);
						fes_b0d8_3:
						if(zend_hash_get_current_data_ex(ah1, (void**) &hd, &hp1) != SUCCESS){
							goto fee_b0d8_3;
						}
						PHALCON_INIT_VAR(template_after);
						ZVAL_ZVAL(template_after, *hd, 1, 0);
						PHALCON_INIT_VAR(r8);
						PHALCON_CONCAT_VV(r8, layouts_dir, template_after);
						PHALCON_CALL_METHOD_PARAMS_4_NORETURN(this_ptr, "_enginerender", engines, r8, silence, cache, PH_NO_CHECK);
						zend_hash_move_forward_ex(ah1, &hp1);
						goto fes_b0d8_3;
						fee_b0d8_3:
						if(0){}
					} else {
						return;
					}
				} else {
					PHALCON_ALLOC_ZVAL_MM(r9);
					PHALCON_CONCAT_VV(r9, layouts_dir, templates_after);
					PHALCON_CALL_METHOD_PARAMS_4_NORETURN(this_ptr, "_enginerender", engines, r9, silence, cache, PH_NO_CHECK);
				}
				
				PHALCON_INIT_VAR(silence);
				ZVAL_BOOL(silence, 1);
			}
		}
		
		PHALCON_INIT_VAR(t4);
		ZVAL_LONG(t4, 5);
		
		PHALCON_ALLOC_ZVAL_MM(r10);
		is_smaller_or_equal_function(r10, t4, render_level TSRMLS_CC);
		if (zend_is_true(r10)) {
			PHALCON_ALLOC_ZVAL_MM(t5);
			phalcon_read_property(&t5, this_ptr, SL("_mainView"), PH_NOISY_CC);
			PHALCON_CALL_METHOD_PARAMS_4_NORETURN(this_ptr, "_enginerender", engines, t5, silence, cache, PH_NO_CHECK);
		}
		
		if (zend_is_true(cache)) {
			PHALCON_ALLOC_ZVAL_MM(r11);
			PHALCON_CALL_METHOD(r11, cache, "isstarted", PH_NO_CHECK);
			if (zend_is_true(r11)) {
				PHALCON_ALLOC_ZVAL_MM(r12);
				PHALCON_CALL_METHOD(r12, cache, "isfresh", PH_NO_CHECK);
				if (zend_is_true(r12)) {
					PHALCON_CALL_METHOD_NORETURN(cache, "save", PH_NO_CHECK);
				}
			}
		}
	}
	
	PHALCON_MM_RESTORE();
}

/**
 * Choose a view different to render than last-controller/last-action
 *
 * @param string $renderView
 */
PHP_METHOD(Phalcon_View, pick){

	zval *render_view = NULL, *separator = NULL, *pick_view = NULL, *layout = NULL;
	zval *parts = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &render_view) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(separator);
	ZVAL_STRING(separator, "/", 1);
	if (Z_TYPE_P(render_view) == IS_ARRAY) { 
		PHALCON_CPY_WRT(pick_view, render_view);
	} else {
		PHALCON_INIT_VAR(layout);
		ZVAL_NULL(layout);
		
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_fast_strpos(r0, render_view, separator TSRMLS_CC);
		if (zend_is_true(r0)) {
			PHALCON_INIT_VAR(parts);
			phalcon_fast_explode(parts, separator, render_view TSRMLS_CC);
			
			PHALCON_INIT_VAR(layout);
			phalcon_array_fetch_long(&layout, parts, 0, PH_NOISY_CC);
		}
		
		PHALCON_INIT_VAR(pick_view);
		array_init(pick_view);
		phalcon_array_append(&pick_view, render_view, PH_SEPARATE TSRMLS_CC);
		if (Z_TYPE_P(layout) != IS_NULL) {
			phalcon_array_append(&pick_view, layout, PH_SEPARATE TSRMLS_CC);
		}
	}
	
	phalcon_update_property_zval(this_ptr, SL("_pickView"), pick_view TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Renders a partial view
 *
 * @param string $partialPath
 */
PHP_METHOD(Phalcon_View, partial){

	zval *partial_path = NULL, *vfalse = NULL, *previous_content = NULL;
	zval *r0 = NULL, *r1 = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &partial_path) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(vfalse);
	ZVAL_BOOL(vfalse, 0);
	
	PHALCON_INIT_VAR(previous_content);
	phalcon_read_property(&previous_content, this_ptr, SL("_content"), PH_NOISY_CC);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD(r0, this_ptr, "_loadtemplateengines", PH_NO_CHECK);
	PHALCON_CALL_METHOD_PARAMS_4_NORETURN(this_ptr, "_enginerender", r0, partial_path, vfalse, vfalse, PH_NO_CHECK);
	
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_content"), PH_NOISY_CC);
	
	PHALCON_ALLOC_ZVAL_MM(r1);
	PHALCON_CONCAT_VV(r1, previous_content, t0);
	phalcon_update_property_zval(this_ptr, SL("_content"), r1 TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Finishes the render process by stopping the output buffering
 */
PHP_METHOD(Phalcon_View, finish){


	PHALCON_MM_GROW();
	PHALCON_CALL_FUNC_NORETURN("ob_end_clean");
	
	PHALCON_MM_RESTORE();
}

/**
 * Set the cache object or cache parameters to do the resultset caching
 *
 * @param Phalcon\Cache\Backend|object $cache
 */
PHP_METHOD(Phalcon_View, setCache){

	zval *cache = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &cache) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (Z_TYPE_P(cache) != IS_OBJECT) {
		PHALCON_THROW_EXCEPTION_STR(phalcon_model_exception_ce, "Cache must be an object instance");
		return;
	}
	phalcon_update_property_zval(this_ptr, SL("_cache"), cache TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Create a Phalcon\Cache based on the internal cache options
 *
 * @return Phalcon\Cache
 */
PHP_METHOD(Phalcon_View, _createCache){

	zval *options = NULL, *cache_options = NULL, *array_options = NULL;
	zval *r0 = NULL, *r1 = NULL;
	zval *t0 = NULL;
	zval *p0[] = { NULL, NULL, NULL, NULL };
	int eval_int;

	PHALCON_MM_GROW();
	PHALCON_INIT_VAR(options);
	phalcon_read_property(&options, this_ptr, SL("_options"), PH_NOISY_CC);
	eval_int = phalcon_isset_property(options, SL("cache") TSRMLS_CC);
	if (!eval_int) {
		PHALCON_THROW_EXCEPTION_STR(phalcon_view_exception_ce, "Cache options aren't defined");
		return;
	}
	
	PHALCON_INIT_VAR(cache_options);
	phalcon_read_property(&cache_options, options, SL("cache"), PH_NOISY_CC);
	eval_int = phalcon_isset_property(cache_options, SL("adapter") TSRMLS_CC);
	if (!eval_int) {
		PHALCON_THROW_EXCEPTION_STR(phalcon_model_exception_ce, "Cache adapter isn't defined");
		return;
	}
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	phalcon_cast(r0, cache_options, IS_ARRAY);
	PHALCON_CPY_WRT(array_options, r0);
	
	PHALCON_INIT_VAR(p0[0]);
	ZVAL_STRING(p0[0], "Output", 1);
	
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, cache_options, SL("adapter"), PH_NOISY_CC);
	p0[1] = t0;
	p0[2] = array_options;
	p0[3] = array_options;
	
	PHALCON_ALLOC_ZVAL_MM(r1);
	PHALCON_CALL_STATIC_PARAMS(r1, "phalcon\\cache", "factory", 4, p0);
	RETURN_CTOR(r1);
}

/**
 * Returns the cache instance used to cache
 *
 * @return Phalcon\Cache\Backend
 */
PHP_METHOD(Phalcon_View, getCache){

	zval *cache = NULL;

	PHALCON_MM_GROW();
	PHALCON_INIT_VAR(cache);
	phalcon_read_property(&cache, this_ptr, SL("_cache"), PH_NOISY_CC);
	if (zend_is_true(cache)) {
		if (Z_TYPE_P(cache) != IS_OBJECT) {
			PHALCON_INIT_VAR(cache);
			PHALCON_CALL_METHOD(cache, this_ptr, "_createcache", PH_NO_CHECK);
			phalcon_update_property_zval(this_ptr, SL("_cache"), cache TSRMLS_CC);
		}
	} else {
		PHALCON_INIT_VAR(cache);
		PHALCON_CALL_METHOD(cache, this_ptr, "_createcache", PH_NO_CHECK);
		phalcon_update_property_zval(this_ptr, SL("_cache"), cache TSRMLS_CC);
	}
	
	
	RETURN_CCTOR(cache);
}

/**
 * Cache the actual view render to certain level
 *
 * @param boolean|array $options
 */
PHP_METHOD(Phalcon_View, cache){

	zval *options = NULL, *view_options = NULL, *cache_options = NULL;
	zval *value = NULL, *key = NULL;
	zval *t0 = NULL;
	HashTable *ah0;
	HashPosition hp0;
	zval **hd;
	char *hash_index;
	uint hash_index_len;
	ulong hash_num;
	int hash_type;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &options) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!options) {
		PHALCON_ALLOC_ZVAL_MM(options);
		ZVAL_BOOL(options, 1);
	}
	
	if (Z_TYPE_P(options) == IS_ARRAY) { 
		PHALCON_INIT_VAR(view_options);
		phalcon_read_property(&view_options, this_ptr, SL("_options"), PH_NOISY_CC);
		eval_int = phalcon_isset_property(view_options, SL("cache") TSRMLS_CC);
		if (eval_int) {
			PHALCON_INIT_VAR(cache_options);
			phalcon_read_property(&cache_options, view_options, SL("cache"), PH_NOISY_CC);
		} else {
			PHALCON_INIT_VAR(cache_options);
			object_init(cache_options);
		}
		
		if (phalcon_valid_foreach(options TSRMLS_CC)) {
			ah0 = Z_ARRVAL_P(options);
			zend_hash_internal_pointer_reset_ex(ah0, &hp0);
			fes_b0d8_4:
			if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
				goto fee_b0d8_4;
			} else {
				PHALCON_INIT_VAR(key);
				PHALCON_GET_FOREACH_KEY(key, ah0, hp0);
			}
			PHALCON_INIT_VAR(value);
			ZVAL_ZVAL(value, *hd, 1, 0);
			phalcon_update_property_zval_zval(cache_options, key, value TSRMLS_CC);
			zend_hash_move_forward_ex(ah0, &hp0);
			goto fes_b0d8_4;
			fee_b0d8_4:
			if(0){}
		} else {
			return;
		}
		eval_int = phalcon_isset_property(cache_options, SL("level") TSRMLS_CC);
		if (eval_int) {
			PHALCON_ALLOC_ZVAL_MM(t0);
			phalcon_read_property(&t0, cache_options, SL("level"), PH_NOISY_CC);
			phalcon_update_property_zval(this_ptr, SL("_cacheLevel"), t0 TSRMLS_CC);
		} else {
			phalcon_update_property_long(this_ptr, SL("_cacheLevel"), 5 TSRMLS_CC);
		}
		
		phalcon_update_property_zval(view_options, SL("cache"), cache_options TSRMLS_CC);
		phalcon_update_property_zval(this_ptr, SL("_options"), view_options TSRMLS_CC);
	} else {
		if (zend_is_true(options)) {
			phalcon_update_property_long(this_ptr, SL("_cacheLevel"), 5 TSRMLS_CC);
		} else {
			phalcon_update_property_long(this_ptr, SL("_cacheLevel"), 0 TSRMLS_CC);
		}
	}
	
	PHALCON_MM_RESTORE();
}

/**
 * Externally sets the view content
 *
 * @param string $content
 */
PHP_METHOD(Phalcon_View, setContent){

	zval *content = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &content) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, SL("_content"), content TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Returns cached ouput from another view stage
 *
 * @return string
 */
PHP_METHOD(Phalcon_View, getContent){

	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_content"), PH_NOISY_CC);
	
	RETURN_CCTOR(t0);
}

/**
 * Disable view. No show any view or template
 *
 */
PHP_METHOD(Phalcon_View, disable){


	PHALCON_MM_GROW();
	phalcon_update_property_long(this_ptr, SL("_renderLevel"), 0 TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

