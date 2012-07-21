
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

#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/array.h"

/**
 * Phalcon_Db_Adapter_Postgresql
 *
 * Phalcon_Db_Adapter_Postgresql is the Phalcon_Db adapter for the PostgreSQL database.
 * 
 */

/**
 * Constructor for Phalcon_Db_Adapter_Postgresql. This method does not should to be called directly. Use Phalcon_Db::factory instead
 *
 * @param stdClass $descriptor
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, __construct){

	zval *descriptor = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &descriptor) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!descriptor) {
		PHALCON_ALLOC_ZVAL_MM(descriptor);
		ZVAL_NULL(descriptor);
	} else {
		PHALCON_SEPARATE_PARAM(descriptor);
	}
	
	if (!zend_is_true(descriptor)) {
		PHALCON_INIT_VAR(descriptor);
		phalcon_read_property(&descriptor, this_ptr, SL("_descriptor"), PH_NOISY_CC);
	}
	PHALCON_CALL_METHOD_PARAMS_1_NORETURN(this_ptr, "connect", descriptor, PH_NO_CHECK);
	
	PHALCON_MM_RESTORE();
}

/**
 * This method is automatically called in Phalcon_Db_Postgresql constructor.
 * Call it when you need to restore a database connection
 *
 * @param stdClass $descriptor
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, connect){

	zval *descriptor = NULL, *connection_string = NULL, *id_connection = NULL;
	zval *t0 = NULL, *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL, *t5 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &descriptor) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!descriptor) {
		PHALCON_ALLOC_ZVAL_MM(descriptor);
		ZVAL_NULL(descriptor);
	} else {
		PHALCON_SEPARATE_PARAM(descriptor);
	}
	
	if (!zend_is_true(descriptor)) {
		PHALCON_INIT_VAR(descriptor);
		phalcon_read_property(&descriptor, this_ptr, SL("_descriptor"), PH_NOISY_CC);
	}
	
	PHALCON_INIT_VAR(connection_string);
	ZVAL_STRING(connection_string, "", 1);
	eval_int = phalcon_isset_property(descriptor, SL("host") TSRMLS_CC);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(t0);
		phalcon_read_property(&t0, descriptor, SL("host"), PH_NOISY_CC);
		PHALCON_ALLOC_ZVAL_MM(r0);
		PHALCON_CONCAT_SVS(r0, "host=", t0, " ");
		phalcon_concat_self(&connection_string, r0 TSRMLS_CC);
	}
	
	eval_int = phalcon_isset_property(descriptor, SL("port") TSRMLS_CC);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(t1);
		phalcon_read_property(&t1, descriptor, SL("port"), PH_NOISY_CC);
		PHALCON_ALLOC_ZVAL_MM(r1);
		PHALCON_CONCAT_SVS(r1, "port=", t1, " ");
		phalcon_concat_self(&connection_string, r1 TSRMLS_CC);
	}
	
	eval_int = phalcon_isset_property(descriptor, SL("name") TSRMLS_CC);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(t2);
		phalcon_read_property(&t2, descriptor, SL("name"), PH_NOISY_CC);
		PHALCON_ALLOC_ZVAL_MM(r2);
		PHALCON_CONCAT_SVS(r2, "dbname=", t2, " ");
		phalcon_concat_self(&connection_string, r2 TSRMLS_CC);
	}
	
	eval_int = phalcon_isset_property(descriptor, SL("username") TSRMLS_CC);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(t3);
		phalcon_read_property(&t3, descriptor, SL("username"), PH_NOISY_CC);
		PHALCON_ALLOC_ZVAL_MM(r3);
		PHALCON_CONCAT_SVS(r3, "user=", t3, " ");
		phalcon_concat_self(&connection_string, r3 TSRMLS_CC);
	}
	
	eval_int = phalcon_isset_property(descriptor, SL("password") TSRMLS_CC);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(t4);
		phalcon_read_property(&t4, descriptor, SL("password"), PH_NOISY_CC);
		PHALCON_ALLOC_ZVAL_MM(r4);
		PHALCON_CONCAT_SV(r4, "password=", t4);
		phalcon_concat_self(&connection_string, r4 TSRMLS_CC);
	}
	
	PHALCON_INIT_VAR(t5);
	ZVAL_LONG(t5, 2);
	
	PHALCON_INIT_VAR(id_connection);
	PHALCON_CALL_FUNC_PARAMS_2(id_connection, "pg_connect", connection_string, t5);
	if (zend_is_true(id_connection)) {
		phalcon_update_property_zval(this_ptr, SL("_idConnection"), id_connection TSRMLS_CC);
		PHALCON_CALL_PARENT_PARAMS_1_NORETURN(this_ptr, "Phalcon\\Db\\Adapter\\Postgresql", "__construct", descriptor);
	} else {
		PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Connection to PostgreSQL failed");
		return;
	}
	
	PHALCON_MM_RESTORE();
}

/**
 * Sends SQL statements to the PostgreSQL database server returning success state.
 * When the SQL sent have returned any row, the result is a PHP resource.
 *
 * $resultset = $connection->query("SELECT * FROM robots WHERE type=?", array("mechanical"));
 *
 * @param  string $sqlStatement
 * @return Phalcon_Db_Result_Postgresql|boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, query){

	zval *sql_statement = NULL, *id_connection = NULL, *result = NULL;
	zval *number_error = NULL, *error_message = NULL;
	zval *t0 = NULL, *t1 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL;
	zval *i0 = NULL, *i1 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &sql_statement) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_CALL_METHOD_PARAMS_1_NORETURN(this_ptr, "_beforequery", sql_statement, PH_NO_CHECK);
	
	PHALCON_INIT_VAR(id_connection);
	phalcon_read_property(&id_connection, this_ptr, SL("_idConnection"), PH_NOISY_CC);
	
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_idConnection"), PH_NOISY_CC);
	
	PHALCON_INIT_VAR(result);
	PHALCON_CALL_FUNC_PARAMS_2(result, "pg_query", t0, sql_statement);
	if (zend_is_true(result)) {
		PHALCON_CALL_METHOD_PARAMS_1_NORETURN(this_ptr, "_afterquery", sql_statement, PH_NO_CHECK);
		phalcon_update_property_zval(this_ptr, SL("_lastResultset"), result TSRMLS_CC);
		
		PHALCON_ALLOC_ZVAL_MM(r0);
		PHALCON_CALL_FUNC_PARAMS_1(r0, "pg_result_status", result);
		
		PHALCON_INIT_VAR(t1);
		ZVAL_LONG(t1, 2);
		
		PHALCON_ALLOC_ZVAL_MM(r1);
		is_equal_function(r1, r0, t1 TSRMLS_CC);
		if (zend_is_true(r1)) {
			PHALCON_ALLOC_ZVAL_MM(i0);
			object_init_ex(i0, phalcon_db_result_postgresql_ce);
			PHALCON_CALL_METHOD_PARAMS_1_NORETURN(i0, "__construct", result, PH_CHECK);
			
			RETURN_CTOR(i0);
		}
		
		PHALCON_MM_RESTORE();
		RETURN_TRUE;
	}
	
	PHALCON_INIT_VAR(number_error);
	PHALCON_CALL_METHOD(number_error, this_ptr, "noerror", PH_NO_CHECK);
	
	PHALCON_ALLOC_ZVAL_MM(r2);
	PHALCON_CONCAT_SVS(r2, " when executing \"", sql_statement, "\"");
	
	PHALCON_INIT_VAR(error_message);
	PHALCON_CALL_METHOD_PARAMS_1(error_message, this_ptr, "error", r2, PH_NO_CHECK);
	
	PHALCON_ALLOC_ZVAL_MM(i1);
	object_init_ex(i1, phalcon_db_exception_ce);
	PHALCON_CALL_METHOD_PARAMS_2_NORETURN(i1, "__construct", error_message, number_error, PH_CHECK);
	phalcon_throw_exception(i1 TSRMLS_CC);
	return;
}

/**
 * Returns number of affected rows by the last INSERT/UPDATE/DELETE repoted by PostgreSQL
 *
 * @return int
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, affectedRows){

	zval *t0 = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_lastResultset"), PH_NOISY_CC);
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_FUNC_PARAMS_1(r0, "pg_affected_rows", t0);
	RETURN_CTOR(r0);
}

/**
 * Closes active connection returning success. Phalcon automatically closes and destroys active connections within Phalcon_Db_Pool
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, close){

	zval *id_connection = NULL, *success = NULL;

	PHALCON_MM_GROW();
	PHALCON_INIT_VAR(id_connection);
	phalcon_read_property(&id_connection, this_ptr, SL("_idConnection"), PH_NOISY_CC);
	if (zend_is_true(id_connection)) {
		PHALCON_INIT_VAR(success);
		PHALCON_CALL_FUNC_PARAMS_1(success, "pg_close", id_connection);
		phalcon_update_property_null(this_ptr, SL("_idConnection") TSRMLS_CC);
		
		RETURN_CCTOR(success);
	} else {
		PHALCON_MM_RESTORE();
		RETURN_TRUE;
	}
	
	PHALCON_MM_RESTORE();
}

/**
 * Gets the active connection unique identifier. A pgsql resource
 *
 * @param boolean $asString
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, getConnectionId){

	zval *as_string = NULL, *id_connection = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &as_string) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!as_string) {
		PHALCON_ALLOC_ZVAL_MM(as_string);
		ZVAL_BOOL(as_string, 0);
	}
	
	PHALCON_INIT_VAR(id_connection);
	phalcon_read_property(&id_connection, this_ptr, SL("_idConnection"), PH_NOISY_CC);
	if (zend_is_true(as_string)) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		PHALCON_CALL_FUNC_PARAMS_1(r0, "strval", id_connection);
		RETURN_CTOR(r0);
	} else {
		
		RETURN_CCTOR(id_connection);
	}
	
	PHALCON_MM_RESTORE();
}

/**
 * Escapes a value to avoid SQL injections
 *
 * @param string $str
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, escapeString){

	zval *str = NULL;
	zval *t0 = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &str) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, SL("_idConnection"), PH_NOISY_CC);
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_FUNC_PARAMS_2(r0, "pg_escape_string", t0, str);
	RETURN_CTOR(r0);
}

/**
 * Bind params to SQL select
 *
 * @param string $sqlSelect
 * @param array $params
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, bindParams){

	zval *sql_select = NULL, *params = NULL, *select = NULL, *id_connection = NULL;
	zval *bind_value = NULL, *index = NULL, *value = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL, *r5 = NULL, *r6 = NULL;
	zval *r7 = NULL;
	zval *c0 = NULL, *c1 = NULL;
	HashTable *ah0;
	HashPosition hp0;
	zval **hd;
	char *hash_index;
	uint hash_index_len;
	ulong hash_num;
	int hash_type;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &sql_select, &params) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(r0);
	phalcon_fast_count(r0, params TSRMLS_CC);
	if (zend_is_true(r0)) {
		PHALCON_CPY_WRT(select, sql_select);
		
		PHALCON_INIT_VAR(id_connection);
		phalcon_read_property(&id_connection, this_ptr, SL("_idConnection"), PH_NOISY_CC);
		if (phalcon_valid_foreach(params TSRMLS_CC)) {
			ah0 = Z_ARRVAL_P(params);
			zend_hash_internal_pointer_reset_ex(ah0, &hp0);
			fes_32b0_0:
			if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
				goto fee_32b0_0;
			} else {
				PHALCON_INIT_VAR(index);
				PHALCON_GET_FOREACH_KEY(index, ah0, hp0);
			}
			PHALCON_INIT_VAR(bind_value);
			ZVAL_ZVAL(bind_value, *hd, 1, 0);
			PHALCON_INIT_VAR(r1);
			PHALCON_CALL_FUNC_PARAMS_1(r1, "is_numeric", bind_value);
			if (zend_is_true(r1)) {
				PHALCON_CPY_WRT(value, bind_value);
			} else {
				PHALCON_INIT_VAR(r2);
				PHALCON_CALL_FUNC_PARAMS_2(r2, "pg_escape_string", id_connection, bind_value);
				PHALCON_INIT_VAR(value);
				PHALCON_CONCAT_SVS(value, "¡!", r2, "¡!");
			}
			if (Z_TYPE_P(index) == IS_LONG) {
				PHALCON_INIT_VAR(r3);
				PHALCON_CONCAT_SV(r3, "?", index);
				PHALCON_INIT_VAR(r4);
				phalcon_fast_str_replace(r4, r3, value, select TSRMLS_CC);
				PHALCON_CPY_WRT(select, r4);
			} else {
				if (Z_TYPE_P(index) == IS_STRING) {
					PHALCON_INIT_VAR(r5);
					PHALCON_CONCAT_SVS(r5, ":", index, ":");
					PHALCON_INIT_VAR(r6);
					phalcon_fast_str_replace(r6, r5, value, select TSRMLS_CC);
					PHALCON_CPY_WRT(select, r6);
				} else {
					PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Invalid bind parameter");
					return;
				}
			}
			zend_hash_move_forward_ex(ah0, &hp0);
			goto fes_32b0_0;
			fee_32b0_0:
			if(0){}
		} else {
			return;
		}
		
		PHALCON_INIT_VAR(c0);
		ZVAL_STRING(c0, "¡!", 1);
		
		PHALCON_INIT_VAR(c1);
		ZVAL_STRING(c1, "'", 1);
		
		PHALCON_ALLOC_ZVAL_MM(r7);
		phalcon_fast_str_replace(r7, c0, c1, select TSRMLS_CC);
		RETURN_CTOR(r7);
	}
	
	RETURN_CCTOR(sql_select);
}

/**
 * Returns last error message from PostgreSQL
 *
 * @param string $errorString
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, error){

	zval *error_string = NULL, *id_connection = NULL, *error_message = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &error_string) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!error_string) {
		PHALCON_ALLOC_ZVAL_MM(error_string);
		ZVAL_NULL(error_string);
	}
	
	PHALCON_INIT_VAR(id_connection);
	phalcon_read_property(&id_connection, this_ptr, SL("_idConnection"), PH_NOISY_CC);
	if (zend_is_true(id_connection)) {
		PHALCON_INIT_VAR(error_message);
		PHALCON_CALL_FUNC_PARAMS_1(error_message, "pg_last_error", id_connection);
	} else {
		PHALCON_INIT_VAR(error_message);
		PHALCON_CALL_FUNC(error_message, "pg_last_error");
	}
	
	PHALCON_INIT_VAR(error_message);
	PHALCON_CONCAT_SVSV(error_message, "\"", error_message, "\" ", error_string);
	phalcon_update_property_zval(this_ptr, SL("_lastError"), error_message TSRMLS_CC);
	
	RETURN_CCTOR(error_message);
}

/**
 * Returns last error code from PostgreSQL
 *
 * @param string $errorString
 * @param resurce $resultQuery
 * @return int
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, noError){

	zval *result_query = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &result_query) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!result_query) {
		PHALCON_ALLOC_ZVAL_MM(result_query);
		ZVAL_NULL(result_query);
	}
	
	PHALCON_MM_RESTORE();
	RETURN_LONG(0);
}

/**
 * Returns insert id for the auto_increment column inserted in the last SQL statement
 *
 * @param string $table
 * @param string $primaryKey
 * @param string $sequenceName
 * @return int
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, lastInsertId){


	
}

/**
 * Gets a list of columns
 *
 * @param array $columnList
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, getColumnList){

	zval *column_list = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &column_list) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_STATIC_PARAMS_1(r0, "phalcon\\db\\dialect\\postgresql", "getcolumnlist", column_list);
	RETURN_CTOR(r0);
}

/**
 * Appends a LIMIT clause to $sqlQuery argument
 *
 * @param string $sqlQuery
 * @param int $number
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, limit){

	zval *sql_query = NULL, *number = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &sql_query, &number) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_STATIC_PARAMS_2(r0, "phalcon\\db\\dialect\\postgresql", "limit", sql_query, number);
	RETURN_CTOR(r0);
}

/**
 * Generates SQL checking for the existence of a schema.table
 *
 * @param string $tableName
 * @param string $schemaName
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, tableExists){

	zval *table_name = NULL, *schema_name = NULL, *sql = NULL, *num = NULL;
	zval *c0 = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &table_name, &schema_name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!schema_name) {
		PHALCON_ALLOC_ZVAL_MM(schema_name);
		ZVAL_NULL(schema_name);
	}
	
	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_2(sql, "phalcon\\db\\dialect\\postgresql", "tableexists", table_name, schema_name);
	
	PHALCON_INIT_VAR(c0);
	ZVAL_LONG(c0, 2);
	
	PHALCON_INIT_VAR(num);
	PHALCON_CALL_METHOD_PARAMS_2(num, this_ptr, "fetchone", sql, c0, PH_NO_CHECK);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	phalcon_array_fetch_long(&r0, num, 0, PH_NOISY_CC);
	
	RETURN_CCTOR(r0);
}

/**
 * Generates SQL checking for the existence of a schema.view
 *
 * @param string $viewName
 * @param string $schemaName
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, viewExists){

	zval *view_name = NULL, *schema_name = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &view_name, &schema_name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!schema_name) {
		PHALCON_ALLOC_ZVAL_MM(schema_name);
		ZVAL_NULL(schema_name);
	}
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD_PARAMS_2(r0, this_ptr, "tableexists", view_name, schema_name, PH_NO_CHECK);
	RETURN_CTOR(r0);
}

/**
 * Devuelve un FOR UPDATE valido para un SELECT del RBDM
 *
 * @param string $sqlQuery
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, forUpdate){

	zval *sql_query = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &sql_query) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CONCAT_VS(r0, sql_query, " FOR UPDATE");
	
	RETURN_CTOR(r0);
}

/**
 * Devuelve un SHARED LOCK valido para un SELECT del RBDM
 *
 * @param string $sqlQuery
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, sharedLock){

	zval *sql_query = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &sql_query) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CONCAT_VS(r0, sql_query, " LOCK IN SHARE MODE");
	
	RETURN_CTOR(r0);
}

/**
 * Creates a table using PostgreSQL SQL
 *
 * @param string $tableName
 * @param string $schemaName
 * @param array $definition
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, createTable){

	zval *table_name = NULL, *schema_name = NULL, *definition = NULL;
	zval *sql = NULL;
	zval *i0 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &definition) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (Z_TYPE_P(definition) != IS_ARRAY) { 
		PHALCON_ALLOC_ZVAL_MM(i0);
		object_init_ex(i0, phalcon_db_exception_ce);
		PHALCON_ALLOC_ZVAL_MM(r0);
		PHALCON_CONCAT_SVS(r0, "Invalid definition to create the table '", table_name, "'");
		PHALCON_CALL_METHOD_PARAMS_1_NORETURN(i0, "__construct", r0, PH_CHECK);
		phalcon_throw_exception(i0 TSRMLS_CC);
		return;
	}
	eval_int = phalcon_array_isset_string(definition, SL("columns")+1);
	if (!eval_int) {
		PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "The table must contain at least one column");
		return;
	}
	
	PHALCON_ALLOC_ZVAL_MM(r1);
	phalcon_array_fetch_string(&r1, definition, SL("columns"), PH_NOISY_CC);
	
	PHALCON_ALLOC_ZVAL_MM(r2);
	phalcon_fast_count(r2, r1 TSRMLS_CC);
	if (!zend_is_true(r2)) {
		PHALCON_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "The table must contain at least one column");
		return;
	}
	
	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_3(sql, "phalcon\\db\\dialect\\postgresql", "createtable", table_name, schema_name, definition);
	
	PHALCON_ALLOC_ZVAL_MM(r3);
	PHALCON_CALL_METHOD_PARAMS_1(r3, this_ptr, "query", sql, PH_NO_CHECK);
	RETURN_CTOR(r3);
}

/**
 * Drops a table from a schema/database
 *
 * @param string $tableName
 * @param   string $schemaName
 * @param boolean $ifExists
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, dropTable){

	zval *table_name = NULL, *schema_name = NULL, *if_exists = NULL, *sql = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz|z", &table_name, &schema_name, &if_exists) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!if_exists) {
		PHALCON_ALLOC_ZVAL_MM(if_exists);
		ZVAL_BOOL(if_exists, 1);
	}
	
	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_3(sql, "phalcon\\db\\dialect\\postgresql", "droptable", table_name, schema_name, if_exists);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "query", sql, PH_NO_CHECK);
	RETURN_CTOR(r0);
}

/**
 * Adds a column to a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param Phalcon_Db_Column $column
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, addColumn){

	zval *table_name = NULL, *schema_name = NULL, *column = NULL, *sql = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &column) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_3(sql, "phalcon\\db\\dialect\\postgresql", "addcolumn", table_name, schema_name, column);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "query", sql, PH_NO_CHECK);
	RETURN_CTOR(r0);
}

/**
 * Modifies a table column based on a definition
 *
 * @param string $tableName
 * @param string $schemaName
 * @param Phalcon_Db_Column $column
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, modifyColumn){

	zval *table_name = NULL, *schema_name = NULL, *column = NULL, *sql = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &column) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_3(sql, "phalcon\\db\\dialect\\postgresql", "modifycolumn", table_name, schema_name, column);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "query", sql, PH_NO_CHECK);
	RETURN_CTOR(r0);
}

/**
 * Drops a column from a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param string $columnName
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, dropColumn){

	zval *table_name = NULL, *schema_name = NULL, *column_name = NULL;
	zval *sql = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &column_name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_3(sql, "phalcon\\db\\dialect\\postgresql", "dropcolumn", table_name, schema_name, column_name);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "query", sql, PH_NO_CHECK);
	RETURN_CTOR(r0);
}

/**
 * Adds an index to a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param DbIndex $index
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, addIndex){

	zval *table_name = NULL, *schema_name = NULL, *index = NULL, *sql = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &index) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_3(sql, "phalcon\\db\\dialect\\postgresql", "addindex", table_name, schema_name, index);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "query", sql, PH_NO_CHECK);
	RETURN_CTOR(r0);
}

/**
 * Drop an index from a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param string $indexName
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, dropIndex){

	zval *table_name = NULL, *schema_name = NULL, *index_name = NULL;
	zval *sql = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &index_name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_3(sql, "phalcon\\db\\dialect\\postgresql", "dropindex", table_name, schema_name, index_name);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "query", sql, PH_NO_CHECK);
	RETURN_CTOR(r0);
}

/**
 * Adds a primary key to a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param Phalcon_Db_Index $index
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, addPrimaryKey){

	zval *table_name = NULL, *schema_name = NULL, *index = NULL, *sql = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &index) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_3(sql, "phalcon\\db\\dialect\\postgresql", "addprimarykey", table_name, schema_name, index);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "query", sql, PH_NO_CHECK);
	RETURN_CTOR(r0);
}

/**
 * Drops primary key from a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, dropPrimaryKey){

	zval *table_name = NULL, *schema_name = NULL, *sql = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &table_name, &schema_name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_2(sql, "phalcon\\db\\dialect\\postgresql", "dropprimarykey", table_name, schema_name);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "query", sql, PH_NO_CHECK);
	RETURN_CTOR(r0);
}

/**
 * Adds a foreign key to a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param Phalcon_Db_Reference $reference
 * @return boolean true
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, addForeignKey){

	zval *table_name = NULL, *schema_name = NULL, *reference = NULL, *sql = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &reference) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_3(sql, "phalcon\\db\\dialect\\postgresql", "addforeignkey", table_name, schema_name, reference);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "query", sql, PH_NO_CHECK);
	RETURN_CTOR(r0);
}

/**
 * Drops a foreign key from a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @param string $referenceName
 * @return boolean true
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, dropForeignKey){

	zval *table_name = NULL, *schema_name = NULL, *reference_name = NULL;
	zval *sql = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &table_name, &schema_name, &reference_name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_3(sql, "phalcon\\db\\dialect\\postgresql", "dropforeignkey", table_name, schema_name, reference_name);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "query", sql, PH_NO_CHECK);
	RETURN_CTOR(r0);
}

/**
 * Returns the SQL column definition from a column
 *
 * @param Phalcon_Db_Column $column
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, getColumnDefinition){

	zval *column = NULL;
	zval *r0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &column) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_STATIC_PARAMS_1(r0, "phalcon\\db\\dialect\\postgresql", "getcolumndefinition", column);
	RETURN_CTOR(r0);
}

/**
 * Generates SQL describing a table
 *
 * @param string $table
 * @param string $schema
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, describeTable){

	zval *table = NULL, *schema = NULL, *sql = NULL, *describe = NULL, *final_describe = NULL;
	zval *field = NULL;
	zval *c0 = NULL;
	zval *a0 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL;
	HashTable *ah0;
	HashPosition hp0;
	zval **hd;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &table, &schema) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!schema) {
		PHALCON_ALLOC_ZVAL_MM(schema);
		ZVAL_NULL(schema);
	}
	
	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_2(sql, "phalcon\\db\\dialect\\postgresql", "describetable", table, schema);
	
	PHALCON_INIT_VAR(c0);
	ZVAL_LONG(c0, 2);
	
	PHALCON_INIT_VAR(describe);
	PHALCON_CALL_METHOD_PARAMS_2(describe, this_ptr, "fetchall", sql, c0, PH_NO_CHECK);
	
	PHALCON_INIT_VAR(final_describe);
	array_init(final_describe);
	if (phalcon_valid_foreach(describe TSRMLS_CC)) {
		ah0 = Z_ARRVAL_P(describe);
		zend_hash_internal_pointer_reset_ex(ah0, &hp0);
		fes_32b0_1:
		if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
			goto fee_32b0_1;
		}
		
		PHALCON_INIT_VAR(field);
		ZVAL_ZVAL(field, *hd, 1, 0);
		PHALCON_INIT_VAR(a0);
		array_init(a0);
		PHALCON_INIT_VAR(r0);
		phalcon_array_fetch_string(&r0, field, SL("field"), PH_NOISY_CC);
		phalcon_array_update_string(&a0, SL("Field"), &r0, PH_COPY | PH_SEPARATE TSRMLS_CC);
		PHALCON_INIT_VAR(r1);
		phalcon_array_fetch_string(&r1, field, SL("type"), PH_NOISY_CC);
		phalcon_array_update_string(&a0, SL("Type"), &r1, PH_COPY | PH_SEPARATE TSRMLS_CC);
		PHALCON_INIT_VAR(r2);
		phalcon_array_fetch_string(&r2, field, SL("null"), PH_NOISY_CC);
		phalcon_array_update_string(&a0, SL("Null"), &r2, PH_COPY | PH_SEPARATE TSRMLS_CC);
		PHALCON_INIT_VAR(r3);
		phalcon_array_fetch_string(&r3, field, SL("key"), PH_NOISY_CC);
		phalcon_array_update_string(&a0, SL("Key"), &r3, PH_COPY | PH_SEPARATE TSRMLS_CC);
		PHALCON_INIT_VAR(r4);
		phalcon_array_fetch_string(&r4, field, SL("extra"), PH_NOISY_CC);
		phalcon_array_update_string(&a0, SL("Extra"), &r4, PH_COPY | PH_SEPARATE TSRMLS_CC);
		phalcon_array_append(&final_describe, a0, PH_SEPARATE TSRMLS_CC);
		zend_hash_move_forward_ex(ah0, &hp0);
		goto fes_32b0_1;
		fee_32b0_1:
		if(0){}
	} else {
		return;
	}
	
	RETURN_CTOR(final_describe);
}

/**
 * List all tables on a database
 *
 * @param string $schemaName
 * @return array
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, listTables){

	zval *schema_name = NULL, *sql = NULL, *tables = NULL, *all_tables = NULL, *table = NULL;
	zval *c0 = NULL;
	zval *r0 = NULL;
	HashTable *ah0;
	HashPosition hp0;
	zval **hd;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &schema_name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!schema_name) {
		PHALCON_ALLOC_ZVAL_MM(schema_name);
		ZVAL_NULL(schema_name);
	}
	
	PHALCON_INIT_VAR(sql);
	PHALCON_CALL_STATIC_PARAMS_1(sql, "phalcon\\db\\dialect\\postgresql", "listtables", schema_name);
	
	PHALCON_INIT_VAR(c0);
	ZVAL_LONG(c0, 2);
	
	PHALCON_INIT_VAR(tables);
	PHALCON_CALL_METHOD_PARAMS_2(tables, this_ptr, "fetchall", sql, c0, PH_NO_CHECK);
	
	PHALCON_INIT_VAR(all_tables);
	array_init(all_tables);
	if (phalcon_valid_foreach(tables TSRMLS_CC)) {
		ah0 = Z_ARRVAL_P(tables);
		zend_hash_internal_pointer_reset_ex(ah0, &hp0);
		fes_32b0_2:
		if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
			goto fee_32b0_2;
		}
		
		PHALCON_INIT_VAR(table);
		ZVAL_ZVAL(table, *hd, 1, 0);
		PHALCON_INIT_VAR(r0);
		phalcon_array_fetch_long(&r0, table, 0, PH_NOISY_CC);
		phalcon_array_append(&all_tables, r0, PH_SEPARATE TSRMLS_CC);
		zend_hash_move_forward_ex(ah0, &hp0);
		goto fes_32b0_2;
		fee_32b0_2:
		if(0){}
	} else {
		return;
	}
	
	RETURN_CTOR(all_tables);
}

/**
 * Returns a database date formatted
 *
 * @param string $date
 * @param string $format
 * @return string
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, getDateUsingFormat){


	
}

/**
 * Lists table indexes
 *
 * @param string $table
 * @param string $schema
 * @return Phalcon_Db_Index[]
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, describeIndexes){


	
}

/**
 * Lists table references
 *
 * @param string $table
 * @param string $schema
 * @return Phalcon_Db_Reference[]
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, describeReferences){


	
}

/**
 * Gets creation options from a table
 *
 * @param string $tableName
 * @param string $schemaName
 * @return array
 */
PHP_METHOD(Phalcon_Db_Adapter_Postgresql, tableOptions){


	
}

