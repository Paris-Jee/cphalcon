
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "ext/pdo/php_pdo_driver.h"


/**
 * This file is part of the Phalcon.
 *
 * (c) Phalcon Team <team@phalcon.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Db\Adapter\Pdo
 *
 * Phalcon\Db\Adapter\Pdo is the Phalcon\Db that internally uses PDO to connect to a database
 *
 * <code>
 * use Phalcon\Db\Adapter\Pdo\Mysql;
 *
 * $config = [
 *     "host"     => "localhost",
 *     "dbname"   => "blog",
 *     "port"     => 3306,
 *     "username" => "sigma",
 *     "password" => "secret",
 * ];
 *
 * $connection = new Mysql($config);
 *</code>
 */
ZEPHIR_INIT_CLASS(Phalcon_Db_Adapter_Pdo) {

	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Db\\Adapter, Pdo, phalcon, db_adapter_pdo, phalcon_db_adapter_ce, phalcon_db_adapter_pdo_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * Last affected rows
	 */
	zend_declare_property_null(phalcon_db_adapter_pdo_ce, SL("_affectedRows"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * PDO Handler
	 *
	 * @var \Pdo
	 */
	zend_declare_property_null(phalcon_db_adapter_pdo_ce, SL("_pdo"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Constructor for Phalcon\Db\Adapter\Pdo
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, __construct) {

	zephir_fcall_cache_entry *_0 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *descriptor_param = NULL;
	zval descriptor;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&descriptor);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &descriptor_param);

	ZEPHIR_OBS_COPY_OR_DUP(&descriptor, descriptor_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "connect", NULL, 0, &descriptor);
	zephir_check_call_status();
	ZEPHIR_CALL_PARENT(NULL, phalcon_db_adapter_pdo_ce, getThis(), "__construct", &_0, 0, &descriptor);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the number of affected rows by the latest INSERT/UPDATE/DELETE executed in the database system
 *
 *<code>
 * $connection->execute(
 *     "DELETE FROM robots"
 * );
 *
 * echo $connection->affectedRows(), " were deleted";
 *</code>
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, affectedRows) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_affectedRows");

}

/**
 * Starts a transaction in the connection
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, begin) {

	zend_long ZEPHIR_LAST_CALL_STATUS, transactionLevel = 0;
	zval *nesting_param = NULL, pdo, eventsManager, savepointName, _0, _1$$4, _2$$5, _5$$6, _6$$7, _7$$8;
	zend_bool nesting, _3$$6, _4$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pdo);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&savepointName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_7$$8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &nesting_param);

	if (!nesting_param) {
		nesting = 1;
	} else {
		nesting = zephir_get_boolval(nesting_param);
	}


	ZEPHIR_OBS_VAR(&pdo);
	zephir_read_property(&pdo, this_ptr, SL("_pdo"), PH_NOISY_CC);
	if (Z_TYPE_P(&pdo) != IS_OBJECT) {
		RETURN_MM_BOOL(0);
	}
	RETURN_ON_FAILURE(zephir_property_incr(this_ptr, SL("_transactionLevel") TSRMLS_CC));
	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("_transactionLevel"), PH_NOISY_CC);
	transactionLevel = zephir_get_intval(&_0);
	if (transactionLevel == 1) {
		zephir_read_property(&_1$$4, this_ptr, SL("_eventsManager"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&eventsManager, &_1$$4);
		if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
			ZEPHIR_INIT_VAR(&_2$$5);
			ZVAL_STRING(&_2$$5, "db:beginTransaction");
			ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_2$$5, this_ptr);
			zephir_check_call_status();
		}
		ZEPHIR_RETURN_CALL_METHOD(&pdo, "begintransaction", NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		_3$$6 = ((transactionLevel) ? 1 : 0);
		if (_3$$6) {
			_3$$6 = nesting;
		}
		_4$$6 = _3$$6;
		if (_4$$6) {
			ZEPHIR_CALL_METHOD(&_5$$6, this_ptr, "isnestedtransactionswithsavepoints", NULL, 0);
			zephir_check_call_status();
			_4$$6 = zephir_is_true(&_5$$6);
		}
		if (_4$$6) {
			zephir_read_property(&_6$$7, this_ptr, SL("_eventsManager"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&eventsManager, &_6$$7);
			ZEPHIR_CALL_METHOD(&savepointName, this_ptr, "getnestedtransactionsavepointname", NULL, 0);
			zephir_check_call_status();
			if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
				ZEPHIR_INIT_VAR(&_7$$8);
				ZVAL_STRING(&_7$$8, "db:createSavepoint");
				ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_7$$8, this_ptr, &savepointName);
				zephir_check_call_status();
			}
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createsavepoint", NULL, 0, &savepointName);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	RETURN_MM_BOOL(0);

}

/**
 * Commits the active transaction in the connection
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, commit) {

	zend_long ZEPHIR_LAST_CALL_STATUS, transactionLevel = 0;
	zval *nesting_param = NULL, pdo, eventsManager, savepointName, _0, _1$$5, _2$$6, _5$$7, _6$$8, _7$$9;
	zend_bool nesting, _3$$7, _4$$7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pdo);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&savepointName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&_7$$9);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &nesting_param);

	if (!nesting_param) {
		nesting = 1;
	} else {
		nesting = zephir_get_boolval(nesting_param);
	}


	ZEPHIR_OBS_VAR(&pdo);
	zephir_read_property(&pdo, this_ptr, SL("_pdo"), PH_NOISY_CC);
	if (Z_TYPE_P(&pdo) != IS_OBJECT) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("_transactionLevel"), PH_NOISY_CC);
	transactionLevel = zephir_get_intval(&_0);
	if (!(transactionLevel)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "There is no active transaction", "phalcon/db/adapter/pdo.zep", 155);
		return;
	}
	if (transactionLevel == 1) {
		zephir_read_property(&_1$$5, this_ptr, SL("_eventsManager"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&eventsManager, &_1$$5);
		if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
			ZEPHIR_INIT_VAR(&_2$$6);
			ZVAL_STRING(&_2$$6, "db:commitTransaction");
			ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_2$$6, this_ptr);
			zephir_check_call_status();
		}
		RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("_transactionLevel") TSRMLS_CC));
		ZEPHIR_RETURN_CALL_METHOD(&pdo, "commit", NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		_3$$7 = ((transactionLevel) ? 1 : 0);
		if (_3$$7) {
			_3$$7 = nesting;
		}
		_4$$7 = _3$$7;
		if (_4$$7) {
			ZEPHIR_CALL_METHOD(&_5$$7, this_ptr, "isnestedtransactionswithsavepoints", NULL, 0);
			zephir_check_call_status();
			_4$$7 = zephir_is_true(&_5$$7);
		}
		if (_4$$7) {
			zephir_read_property(&_6$$8, this_ptr, SL("_eventsManager"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&eventsManager, &_6$$8);
			ZEPHIR_CALL_METHOD(&savepointName, this_ptr, "getnestedtransactionsavepointname", NULL, 0);
			zephir_check_call_status();
			if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
				ZEPHIR_INIT_VAR(&_7$$9);
				ZVAL_STRING(&_7$$9, "db:releaseSavepoint");
				ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_7$$9, this_ptr, &savepointName);
				zephir_check_call_status();
			}
			RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("_transactionLevel") TSRMLS_CC));
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "releasesavepoint", NULL, 0, &savepointName);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	if (transactionLevel > 0) {
		RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("_transactionLevel") TSRMLS_CC));
	}
	RETURN_MM_BOOL(0);

}

/**
 * Closes the active connection returning success. Phalcon automatically closes and destroys
 * active connections when the request ends
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, close) {

	zval __$null, pdo;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&pdo);


	zephir_read_property(&pdo, this_ptr, SL("_pdo"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&pdo) == IS_OBJECT) {
		zephir_update_property_zval(this_ptr, SL("_pdo"), &__$null);
	}
	RETURN_BOOL(1);

}

/**
 * This method is automatically called in \Phalcon\Db\Adapter\Pdo constructor.
 *
 * Call it when you need to restore a database connection.
 *
 *<code>
 * use Phalcon\Db\Adapter\Pdo\Mysql;
 *
 * // Make a connection
 * $connection = new Mysql(
 *     [
 *         "host"     => "localhost",
 *         "username" => "sigma",
 *         "password" => "secret",
 *         "dbname"   => "blog",
 *         "port"     => 3306,
 *     ]
 * );
 *
 * // Reconnect
 * $connection->connect();
 * </code>
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, connect) {

	zend_bool _5$$10;
	zend_string *_4, *_16$$15;
	zend_ulong _3, _15$$15;
	zephir_fcall_cache_entry *_9 = NULL, *_13 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *descriptor_param = NULL, __$true, username, password, dsnParts, dsnAttributes, persistent, options, key, value, *_2, _18, _19, _20, _21, _0$$3, _6$$10, _7$$10, _8$$10, _10$$11, _11$$11, _12$$11, *_14$$15, _17$$16;
	zval descriptor, _1$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&descriptor);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&username);
	ZVAL_UNDEF(&password);
	ZVAL_UNDEF(&dsnParts);
	ZVAL_UNDEF(&dsnAttributes);
	ZVAL_UNDEF(&persistent);
	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_6$$10);
	ZVAL_UNDEF(&_7$$10);
	ZVAL_UNDEF(&_8$$10);
	ZVAL_UNDEF(&_10$$11);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_12$$11);
	ZVAL_UNDEF(&_17$$16);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &descriptor_param);

	if (!descriptor_param) {
		ZEPHIR_INIT_VAR(&descriptor);
		array_init(&descriptor);
	} else {
		zephir_get_arrval(&descriptor, descriptor_param);
	}


	if (ZEPHIR_IS_EMPTY(&descriptor)) {
		ZEPHIR_OBS_VAR(&_0$$3);
		zephir_read_property(&_0$$3, this_ptr, SL("_descriptor"), PH_NOISY_CC);
		zephir_get_arrval(&_1$$3, &_0$$3);
		ZEPHIR_CPY_WRT(&descriptor, &_1$$3);
	}
	ZEPHIR_OBS_VAR(&username);
	if (zephir_array_isset_string_fetch(&username, &descriptor, SL("username"), 0)) {
		zephir_array_unset_string(&descriptor, SL("username"), PH_SEPARATE);
	} else {
		ZEPHIR_INIT_NVAR(&username);
		ZVAL_NULL(&username);
	}
	ZEPHIR_OBS_VAR(&password);
	if (zephir_array_isset_string_fetch(&password, &descriptor, SL("password"), 0)) {
		zephir_array_unset_string(&descriptor, SL("password"), PH_SEPARATE);
	} else {
		ZEPHIR_INIT_NVAR(&password);
		ZVAL_NULL(&password);
	}
	ZEPHIR_OBS_VAR(&options);
	if (zephir_array_isset_string_fetch(&options, &descriptor, SL("options"), 0)) {
		zephir_array_unset_string(&descriptor, SL("options"), PH_SEPARATE);
	} else {
		ZEPHIR_INIT_NVAR(&options);
		array_init(&options);
	}
	zephir_is_iterable(&options, 1, "phalcon/db/adapter/pdo.zep", 296);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&options), _3, _4, _2)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_4 != NULL) { 
			ZVAL_STR_COPY(&key, _4);
		} else {
			ZVAL_LONG(&key, _3);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _2);
		_5$$10 = Z_TYPE_P(&key) == IS_STRING;
		if (_5$$10) {
			ZEPHIR_CALL_METHOD(&_6$$10, &key, "upper", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_7$$10);
			ZEPHIR_CONCAT_SV(&_7$$10, "\\PDO::", &_6$$10);
			ZEPHIR_CALL_FUNCTION(&_8$$10, "defined", &_9, 20, &_7$$10);
			zephir_check_call_status();
			_5$$10 = zephir_is_true(&_8$$10);
		}
		if (_5$$10) {
			ZEPHIR_CALL_METHOD(&_10$$11, &key, "upper", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_11$$11);
			ZEPHIR_CONCAT_SV(&_11$$11, "\\PDO::", &_10$$11);
			ZEPHIR_CALL_FUNCTION(&_12$$11, "constant", &_13, 21, &_11$$11);
			zephir_check_call_status();
			zephir_array_update_zval(&options, &_12$$11, &value, PH_COPY | PH_SEPARATE);
			zephir_array_unset(&options, &key, PH_SEPARATE);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	ZEPHIR_OBS_VAR(&persistent);
	if (zephir_array_isset_string_fetch(&persistent, &descriptor, SL("persistent"), 0)) {
		if (zephir_is_true(&persistent)) {
			zephir_array_update_long(&options, 12, &__$true, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		}
		zephir_array_unset_string(&descriptor, SL("persistent"), PH_SEPARATE);
	}
	if (zephir_array_isset_string(&descriptor, SL("dialectClass"))) {
		zephir_array_unset_string(&descriptor, SL("dialectClass"), PH_SEPARATE);
	}
	ZEPHIR_OBS_VAR(&dsnAttributes);
	if (!(zephir_array_isset_string_fetch(&dsnAttributes, &descriptor, SL("dsn"), 0))) {
		ZEPHIR_INIT_VAR(&dsnParts);
		array_init(&dsnParts);
		zephir_is_iterable(&descriptor, 0, "phalcon/db/adapter/pdo.zep", 318);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&descriptor), _15$$15, _16$$15, _14$$15)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_16$$15 != NULL) { 
				ZVAL_STR_COPY(&key, _16$$15);
			} else {
				ZVAL_LONG(&key, _15$$15);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _14$$15);
			ZEPHIR_INIT_LNVAR(_17$$16);
			ZEPHIR_CONCAT_VSV(&_17$$16, &key, "=", &value);
			zephir_array_append(&dsnParts, &_17$$16, PH_SEPARATE, "phalcon/db/adapter/pdo.zep", 316);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&value);
		ZEPHIR_INIT_NVAR(&key);
		ZEPHIR_INIT_NVAR(&dsnAttributes);
		zephir_fast_join_str(&dsnAttributes, SL(";"), &dsnParts TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(&_18);
	ZVAL_LONG(&_18, 2);
	zephir_array_update_long(&options, 3, &_18, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_VAR(&_19);
	object_init_ex(&_19, php_pdo_get_dbh_ce());
	zephir_read_property(&_20, this_ptr, SL("_type"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_21);
	ZEPHIR_CONCAT_VSV(&_21, &_20, ":", &dsnAttributes);
	ZEPHIR_CALL_METHOD(NULL, &_19, "__construct", NULL, 0, &_21, &username, &password, &options);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("_pdo"), &_19);
	RETURN_MM_BOOL(1);

}

/**
 * Converts bound parameters such as :name: or ?1 into PDO bind params ?
 *
 *<code>
 * print_r(
 *     $connection->convertBoundParams(
 *         "SELECT * FROM robots WHERE name = :name:",
 *         [
 *             "Bender",
 *         ]
 *     )
 * );
 *</code>
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, convertBoundParams) {

	zend_long ZEPHIR_LAST_CALL_STATUS, setOrder = 0;
	zval params;
	zval *sql_param = NULL, *params_param = NULL, boundSql, placeHolders, bindPattern, matches, placeMatch, value, _0, _1, _2, *_3$$3, _6$$3, _4$$4, _5$$6;
	zval sql;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&sql);
	ZVAL_UNDEF(&boundSql);
	ZVAL_UNDEF(&placeHolders);
	ZVAL_UNDEF(&bindPattern);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&placeMatch);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&params);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &sql_param, &params_param);

	if (UNEXPECTED(Z_TYPE_P(sql_param) != IS_STRING && Z_TYPE_P(sql_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sql' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(sql_param) == IS_STRING)) {
		zephir_get_strval(&sql, sql_param);
	} else {
		ZEPHIR_INIT_VAR(&sql);
		ZVAL_EMPTY_STRING(&sql);
	}
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}


	ZEPHIR_INIT_VAR(&placeHolders);
	array_init(&placeHolders);
	ZEPHIR_INIT_VAR(&bindPattern);
	ZVAL_STRING(&bindPattern, "/\\?([0-9]+)|:([a-zA-Z0-9_]+):/");
	ZEPHIR_INIT_VAR(&matches);
	ZVAL_NULL(&matches);
	setOrder = 2;
	ZVAL_LONG(&_0, setOrder);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_LONG(&_2, setOrder);
	zephir_preg_match(&_1, &bindPattern, &sql, &matches, 1, zephir_get_intval(&_0) , 0  TSRMLS_CC);
	if (zephir_is_true(&_1)) {
		zephir_is_iterable(&matches, 0, "phalcon/db/adapter/pdo.zep", 370);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&matches), _3$$3)
		{
			ZEPHIR_INIT_NVAR(&placeMatch);
			ZVAL_COPY(&placeMatch, _3$$3);
			ZEPHIR_OBS_NVAR(&value);
			zephir_array_fetch_long(&_4$$4, &placeMatch, 1, PH_READONLY, "phalcon/db/adapter/pdo.zep", 357 TSRMLS_CC);
			if (!(zephir_array_isset_fetch(&value, &params, &_4$$4, 0 TSRMLS_CC))) {
				if (zephir_array_isset_long(&placeMatch, 2)) {
					ZEPHIR_OBS_NVAR(&value);
					zephir_array_fetch_long(&_5$$6, &placeMatch, 2, PH_READONLY, "phalcon/db/adapter/pdo.zep", 359 TSRMLS_CC);
					if (!(zephir_array_isset_fetch(&value, &params, &_5$$6, 0 TSRMLS_CC))) {
						ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Matched parameter wasn't found in parameters list", "phalcon/db/adapter/pdo.zep", 360);
						return;
					}
				} else {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Matched parameter wasn't found in parameters list", "phalcon/db/adapter/pdo.zep", 363);
					return;
				}
			}
			zephir_array_append(&placeHolders, &value, PH_SEPARATE, "phalcon/db/adapter/pdo.zep", 367);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&placeMatch);
		ZEPHIR_INIT_VAR(&_6$$3);
		ZVAL_STRING(&_6$$3, "?");
		ZEPHIR_CALL_FUNCTION(&boundSql, "preg_replace", NULL, 22, &bindPattern, &_6$$3, &sql);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&boundSql, &sql);
	}
	zephir_create_array(return_value, 2, 0 TSRMLS_CC);
	zephir_array_update_string(return_value, SL("sql"), &boundSql, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("params"), &placeHolders, PH_COPY | PH_SEPARATE);
	RETURN_MM();

}

/**
 * Escapes a value to avoid SQL injections according to the active charset in the connection
 *
 *<code>
 * $escapedStr = $connection->escapeString("some dangerous value");
 *</code>
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, escapeString) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *str_param = NULL, _0;
	zval str;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&str);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &str_param);

	zephir_get_strval(&str, str_param);


	zephir_read_property(&_0, this_ptr, SL("_pdo"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "quote", NULL, 0, &str);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Sends SQL statements to the database server returning the success state.
 * Use this method only when the SQL statement sent to the server doesn't return any rows
 *
 *<code>
 * // Inserting data
 * $success = $connection->execute(
 *     "INSERT INTO robots VALUES (1, 'Astro Boy')"
 * );
 *
 * $success = $connection->execute(
 *     "INSERT INTO robots VALUES (?, ?)",
 *     [
 *         1,
 *         "Astro Boy",
 *     ]
 * );
 *</code>
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, execute) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *sqlStatement_param = NULL, *bindParams = NULL, bindParams_sub, *bindTypes = NULL, bindTypes_sub, __$null, eventsManager, affectedRows, pdo, newStatement, statement, _0, _1$$3, _2$$3, _3$$9;
	zval sqlStatement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&sqlStatement);
	ZVAL_UNDEF(&bindParams_sub);
	ZVAL_UNDEF(&bindTypes_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&affectedRows);
	ZVAL_UNDEF(&pdo);
	ZVAL_UNDEF(&newStatement);
	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$9);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &sqlStatement_param, &bindParams, &bindTypes);

	if (UNEXPECTED(Z_TYPE_P(sqlStatement_param) != IS_STRING && Z_TYPE_P(sqlStatement_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sqlStatement' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(sqlStatement_param) == IS_STRING)) {
		zephir_get_strval(&sqlStatement, sqlStatement_param);
	} else {
		ZEPHIR_INIT_VAR(&sqlStatement);
		ZVAL_EMPTY_STRING(&sqlStatement);
	}
	if (!bindParams) {
		bindParams = &bindParams_sub;
		bindParams = &__$null;
	}
	if (!bindTypes) {
		bindTypes = &bindTypes_sub;
		bindTypes = &__$null;
	}


	zephir_read_property(&_0, this_ptr, SL("_eventsManager"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_0);
	if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
		zephir_update_property_zval(this_ptr, SL("_sqlStatement"), &sqlStatement);
		zephir_update_property_zval(this_ptr, SL("_sqlVariables"), bindParams);
		zephir_update_property_zval(this_ptr, SL("_sqlBindTypes"), bindTypes);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "db:beforeQuery");
		ZEPHIR_CALL_METHOD(&_1$$3, &eventsManager, "fire", NULL, 0, &_2$$3, this_ptr);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_1$$3)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_INIT_VAR(&affectedRows);
	ZVAL_LONG(&affectedRows, 0);
	zephir_read_property(&_0, this_ptr, SL("_pdo"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&pdo, &_0);
	if (Z_TYPE_P(bindParams) == IS_ARRAY) {
		ZEPHIR_CALL_METHOD(&statement, &pdo, "prepare", NULL, 0, &sqlStatement);
		zephir_check_call_status();
		if (Z_TYPE_P(&statement) == IS_OBJECT) {
			ZEPHIR_CALL_METHOD(&newStatement, this_ptr, "executeprepared", NULL, 0, &statement, bindParams, bindTypes);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&affectedRows, &newStatement, "rowcount", NULL, 0);
			zephir_check_call_status();
		}
	} else {
		ZEPHIR_CALL_METHOD(&affectedRows, &pdo, "exec", NULL, 0, &sqlStatement);
		zephir_check_call_status();
	}
	if (Z_TYPE_P(&affectedRows) == IS_LONG) {
		zephir_update_property_zval(this_ptr, SL("_affectedRows"), &affectedRows);
		if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
			ZEPHIR_INIT_VAR(&_3$$9);
			ZVAL_STRING(&_3$$9, "db:afterQuery");
			ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_3$$9, this_ptr);
			zephir_check_call_status();
		}
	}
	RETURN_MM_BOOL(1);

}

/**
 * Executes a prepared statement binding. This function uses integer indexes starting from zero
 *
 *<code>
 * use Phalcon\Db\Column;
 *
 * $statement = $db->prepare(
 *     "SELECT * FROM robots WHERE name = :name"
 * );
 *
 * $result = $connection->executePrepared(
 *     $statement,
 *     [
 *         "name" => "Voltron",
 *     ],
 *     [
 *         "name" => Column::BIND_PARAM_INT,
 *     ]
 * );
 *</code>
 *
 * @param array dataTypes
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, executePrepared) {

	zval _4$$8, _7$$13;
	zend_bool _3$$3;
	zend_string *_2, *_11$$22, *_16$$28;
	zend_ulong _1, _10$$22, _15$$28;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_6 = NULL, *_8 = NULL;
	zval placeholders;
	zval *statement, statement_sub, *placeholders_param = NULL, *dataTypes, dataTypes_sub, wildcard, value, type, castValue, parameter, position, itemValue, *_0, _5$$12, *_9$$22, _12$$24, _13$$25, *_14$$28, _17$$29;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&statement_sub);
	ZVAL_UNDEF(&dataTypes_sub);
	ZVAL_UNDEF(&wildcard);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&castValue);
	ZVAL_UNDEF(&parameter);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&itemValue);
	ZVAL_UNDEF(&_5$$12);
	ZVAL_UNDEF(&_12$$24);
	ZVAL_UNDEF(&_13$$25);
	ZVAL_UNDEF(&_17$$29);
	ZVAL_UNDEF(&placeholders);
	ZVAL_UNDEF(&_4$$8);
	ZVAL_UNDEF(&_7$$13);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &statement, &placeholders_param, &dataTypes);

	ZEPHIR_OBS_COPY_OR_DUP(&placeholders, placeholders_param);


	zephir_is_iterable(&placeholders, 0, "phalcon/db/adapter/pdo.zep", 567);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&placeholders), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&wildcard);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&wildcard, _2);
		} else {
			ZVAL_LONG(&wildcard, _1);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _0);
		if (Z_TYPE_P(&wildcard) == IS_LONG) {
			ZEPHIR_INIT_NVAR(&parameter);
			ZVAL_LONG(&parameter, (zephir_get_numberval(&wildcard) + 1));
		} else if (Z_TYPE_P(&wildcard) == IS_STRING) {
			ZEPHIR_CPY_WRT(&parameter, &wildcard);
		} else {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Invalid bind parameter (1)", "phalcon/db/adapter/pdo.zep", 493);
			return;
		}
		_3$$3 = Z_TYPE_P(dataTypes) == IS_ARRAY;
		if (_3$$3) {
			ZEPHIR_OBS_NVAR(&type);
			_3$$3 = zephir_array_isset_fetch(&type, dataTypes, &wildcard, 0 TSRMLS_CC);
		}
		if (_3$$3) {
			if (ZEPHIR_IS_LONG(&type, 32)) {
				zephir_get_strval(&_4$$8, &value);
				ZEPHIR_CPY_WRT(&castValue, &_4$$8);
				ZEPHIR_INIT_NVAR(&type);
				ZVAL_LONG(&type, 1024);
			} else {
				if (ZEPHIR_GLOBAL(db).force_casting) {
					if (Z_TYPE_P(&value) != IS_ARRAY) {
						do {
							if (ZEPHIR_IS_LONG(&type, 1)) {
								ZVAL_LONG(&_5$$12, 10);
								ZEPHIR_CALL_FUNCTION(&castValue, "intval", &_6, 23, &value, &_5$$12);
								zephir_check_call_status();
								break;
							}
							if (ZEPHIR_IS_LONG(&type, 2)) {
								zephir_get_strval(&_7$$13, &value);
								ZEPHIR_CPY_WRT(&castValue, &_7$$13);
								break;
							}
							if (ZEPHIR_IS_LONG(&type, 0)) {
								ZEPHIR_INIT_NVAR(&castValue);
								ZVAL_NULL(&castValue);
								break;
							}
							if (ZEPHIR_IS_LONG(&type, 5)) {
								ZEPHIR_INIT_NVAR(&castValue);
								ZVAL_BOOL(&castValue, zephir_get_boolval(&value));
								break;
							}
							ZEPHIR_CPY_WRT(&castValue, &value);
							break;
						} while(0);

					} else {
						ZEPHIR_CPY_WRT(&castValue, &value);
					}
				} else {
					ZEPHIR_CPY_WRT(&castValue, &value);
				}
			}
			if (Z_TYPE_P(&castValue) != IS_ARRAY) {
				if (ZEPHIR_IS_LONG(&type, 1024)) {
					ZEPHIR_CALL_METHOD(NULL, statement, "bindvalue", &_8, 0, &parameter, &castValue);
					zephir_check_call_status();
				} else {
					ZEPHIR_CALL_METHOD(NULL, statement, "bindvalue", &_8, 0, &parameter, &castValue, &type);
					zephir_check_call_status();
				}
			} else {
				zephir_is_iterable(&castValue, 0, "phalcon/db/adapter/pdo.zep", 555);
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&castValue), _10$$22, _11$$22, _9$$22)
				{
					ZEPHIR_INIT_NVAR(&position);
					if (_11$$22 != NULL) { 
						ZVAL_STR_COPY(&position, _11$$22);
					} else {
						ZVAL_LONG(&position, _10$$22);
					}
					ZEPHIR_INIT_NVAR(&itemValue);
					ZVAL_COPY(&itemValue, _9$$22);
					if (ZEPHIR_IS_LONG(&type, 1024)) {
						ZEPHIR_INIT_LNVAR(_12$$24);
						ZEPHIR_CONCAT_VV(&_12$$24, &parameter, &position);
						ZEPHIR_CALL_METHOD(NULL, statement, "bindvalue", &_8, 0, &_12$$24, &itemValue);
						zephir_check_call_status();
					} else {
						ZEPHIR_INIT_LNVAR(_13$$25);
						ZEPHIR_CONCAT_VV(&_13$$25, &parameter, &position);
						ZEPHIR_CALL_METHOD(NULL, statement, "bindvalue", &_8, 0, &_13$$25, &itemValue, &type);
						zephir_check_call_status();
					}
				} ZEND_HASH_FOREACH_END();
				ZEPHIR_INIT_NVAR(&itemValue);
				ZEPHIR_INIT_NVAR(&position);
			}
		} else {
			if (Z_TYPE_P(&value) != IS_ARRAY) {
				ZEPHIR_CALL_METHOD(NULL, statement, "bindvalue", &_8, 0, &parameter, &value);
				zephir_check_call_status();
			} else {
				zephir_is_iterable(&value, 0, "phalcon/db/adapter/pdo.zep", 563);
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&value), _15$$28, _16$$28, _14$$28)
				{
					ZEPHIR_INIT_NVAR(&position);
					if (_16$$28 != NULL) { 
						ZVAL_STR_COPY(&position, _16$$28);
					} else {
						ZVAL_LONG(&position, _15$$28);
					}
					ZEPHIR_INIT_NVAR(&itemValue);
					ZVAL_COPY(&itemValue, _14$$28);
					ZEPHIR_INIT_LNVAR(_17$$29);
					ZEPHIR_CONCAT_VV(&_17$$29, &parameter, &position);
					ZEPHIR_CALL_METHOD(NULL, statement, "bindvalue", &_8, 0, &_17$$29, &itemValue);
					zephir_check_call_status();
				} ZEND_HASH_FOREACH_END();
				ZEPHIR_INIT_NVAR(&itemValue);
				ZEPHIR_INIT_NVAR(&position);
			}
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&wildcard);
	ZEPHIR_CALL_METHOD(NULL, statement, "execute", NULL, 0);
	zephir_check_call_status();
	RETVAL_ZVAL(statement, 1, 0);
	RETURN_MM();

}

/**
 * Return the error info, if any
 *
 * @return array
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, getErrorInfo) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("_pdo"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "errorinfo", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return internal PDO handler
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, getInternalHandler) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_pdo");

}

/**
 * Returns the current transaction nesting level
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, getTransactionLevel) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "_transactionLevel");

}

/**
 * Checks whether the connection is under a transaction
 *
 *<code>
 * $connection->begin();
 *
 * // true
 * var_dump(
 *     $connection->isUnderTransaction()
 * );
 *</code>
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, isUnderTransaction) {

	zval pdo;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pdo);

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(&pdo);
	zephir_read_property(&pdo, this_ptr, SL("_pdo"), PH_NOISY_CC);
	if (Z_TYPE_P(&pdo) == IS_OBJECT) {
		ZEPHIR_RETURN_CALL_METHOD(&pdo, "intransaction", NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(0);

}

/**
 * Returns the insert id for the auto_increment/serial column inserted in the latest executed SQL statement
 *
 *<code>
 * // Inserting a new robot
 * $success = $connection->insert(
 *     "robots",
 *     [
 *         "Astro Boy",
 *         1952,
 *     ],
 *     [
 *         "name",
 *         "year",
 *     ]
 * );
 *
 * // Getting the generated id
 * $id = $connection->lastInsertId();
 *</code>
 *
 * @param string sequenceName
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, lastInsertId) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *sequenceName = NULL, sequenceName_sub, __$null, pdo;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&sequenceName_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&pdo);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &sequenceName);

	if (!sequenceName) {
		sequenceName = &sequenceName_sub;
		sequenceName = &__$null;
	}


	ZEPHIR_OBS_VAR(&pdo);
	zephir_read_property(&pdo, this_ptr, SL("_pdo"), PH_NOISY_CC);
	if (Z_TYPE_P(&pdo) != IS_OBJECT) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_RETURN_CALL_METHOD(&pdo, "lastinsertid", NULL, 0, sequenceName);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns a PDO prepared statement to be executed with 'executePrepared'
 *
 *<code>
 * use Phalcon\Db\Column;
 *
 * $statement = $db->prepare(
 *     "SELECT * FROM robots WHERE name = :name"
 * );
 *
 * $result = $connection->executePrepared(
 *     $statement,
 *     [
 *         "name" => "Voltron",
 *     ],
 *     [
 *         "name" => Column::BIND_PARAM_INT,
 *     ]
 * );
 *</code>
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, prepare) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *sqlStatement_param = NULL, _0;
	zval sqlStatement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&sqlStatement);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &sqlStatement_param);

	if (UNEXPECTED(Z_TYPE_P(sqlStatement_param) != IS_STRING && Z_TYPE_P(sqlStatement_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sqlStatement' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(sqlStatement_param) == IS_STRING)) {
		zephir_get_strval(&sqlStatement, sqlStatement_param);
	} else {
		ZEPHIR_INIT_VAR(&sqlStatement);
		ZVAL_EMPTY_STRING(&sqlStatement);
	}


	zephir_read_property(&_0, this_ptr, SL("_pdo"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "prepare", NULL, 0, &sqlStatement);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Sends SQL statements to the database server returning the success state.
 * Use this method only when the SQL statement sent to the server is returning rows
 *
 *<code>
 * // Querying data
 * $resultset = $connection->query(
 *     "SELECT * FROM robots WHERE type = 'mechanical'"
 * );
 *
 * $resultset = $connection->query(
 *     "SELECT * FROM robots WHERE type = ?",
 *     [
 *         "mechanical",
 *     ]
 * );
 *</code>
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, query) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *sqlStatement_param = NULL, *bindParams = NULL, bindParams_sub, *bindTypes = NULL, bindTypes_sub, __$null, eventsManager, pdo, statement, params, types, _0, _1$$3, _2$$3, _3$$7, _4$$10;
	zval sqlStatement;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&sqlStatement);
	ZVAL_UNDEF(&bindParams_sub);
	ZVAL_UNDEF(&bindTypes_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&pdo);
	ZVAL_UNDEF(&statement);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&types);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$7);
	ZVAL_UNDEF(&_4$$10);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &sqlStatement_param, &bindParams, &bindTypes);

	if (UNEXPECTED(Z_TYPE_P(sqlStatement_param) != IS_STRING && Z_TYPE_P(sqlStatement_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sqlStatement' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(sqlStatement_param) == IS_STRING)) {
		zephir_get_strval(&sqlStatement, sqlStatement_param);
	} else {
		ZEPHIR_INIT_VAR(&sqlStatement);
		ZVAL_EMPTY_STRING(&sqlStatement);
	}
	if (!bindParams) {
		bindParams = &bindParams_sub;
		bindParams = &__$null;
	}
	if (!bindTypes) {
		bindTypes = &bindTypes_sub;
		bindTypes = &__$null;
	}


	zephir_read_property(&_0, this_ptr, SL("_eventsManager"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_0);
	if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
		zephir_update_property_zval(this_ptr, SL("_sqlStatement"), &sqlStatement);
		zephir_update_property_zval(this_ptr, SL("_sqlVariables"), bindParams);
		zephir_update_property_zval(this_ptr, SL("_sqlBindTypes"), bindTypes);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "db:beforeQuery");
		ZEPHIR_CALL_METHOD(&_1$$3, &eventsManager, "fire", NULL, 0, &_2$$3, this_ptr);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_1$$3)) {
			RETURN_MM_BOOL(0);
		}
	}
	zephir_read_property(&_0, this_ptr, SL("_pdo"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&pdo, &_0);
	if (Z_TYPE_P(bindParams) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&params, bindParams);
		ZEPHIR_CPY_WRT(&types, bindTypes);
	} else {
		ZEPHIR_INIT_NVAR(&params);
		array_init(&params);
		ZEPHIR_INIT_NVAR(&types);
		array_init(&types);
	}
	ZEPHIR_CALL_METHOD(&statement, &pdo, "prepare", NULL, 0, &sqlStatement);
	zephir_check_call_status();
	if (Z_TYPE_P(&statement) == IS_OBJECT) {
		ZEPHIR_CALL_METHOD(&_3$$7, this_ptr, "executeprepared", NULL, 0, &statement, &params, &types);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&statement, &_3$$7);
	} else {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Cannot prepare statement", "phalcon/db/adapter/pdo.zep", 727);
		return;
	}
	if (Z_TYPE_P(&statement) == IS_OBJECT) {
		if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
			ZEPHIR_INIT_VAR(&_4$$10);
			ZVAL_STRING(&_4$$10, "db:afterQuery");
			ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_4$$10, this_ptr);
			zephir_check_call_status();
		}
		object_init_ex(return_value, phalcon_db_result_pdo_ce);
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 24, this_ptr, &statement, &sqlStatement, bindParams, bindTypes);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_CCTOR(&statement);

}

/**
 * Rollbacks the active transaction in the connection
 */
PHP_METHOD(Phalcon_Db_Adapter_Pdo, rollback) {

	zend_long ZEPHIR_LAST_CALL_STATUS, transactionLevel = 0;
	zval *nesting_param = NULL, pdo, eventsManager, savepointName, _0, _1$$5, _2$$6, _5$$7, _6$$8, _7$$9;
	zend_bool nesting, _3$$7, _4$$7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pdo);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&savepointName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&_7$$9);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &nesting_param);

	if (!nesting_param) {
		nesting = 1;
	} else {
		nesting = zephir_get_boolval(nesting_param);
	}


	ZEPHIR_OBS_VAR(&pdo);
	zephir_read_property(&pdo, this_ptr, SL("_pdo"), PH_NOISY_CC);
	if (Z_TYPE_P(&pdo) != IS_OBJECT) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("_transactionLevel"), PH_NOISY_CC);
	transactionLevel = zephir_get_intval(&_0);
	if (!(transactionLevel)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "There is no active transaction", "phalcon/db/adapter/pdo.zep", 760);
		return;
	}
	if (transactionLevel == 1) {
		zephir_read_property(&_1$$5, this_ptr, SL("_eventsManager"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&eventsManager, &_1$$5);
		if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
			ZEPHIR_INIT_VAR(&_2$$6);
			ZVAL_STRING(&_2$$6, "db:rollbackTransaction");
			ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_2$$6, this_ptr);
			zephir_check_call_status();
		}
		RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("_transactionLevel") TSRMLS_CC));
		ZEPHIR_RETURN_CALL_METHOD(&pdo, "rollback", NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		_3$$7 = ((transactionLevel) ? 1 : 0);
		if (_3$$7) {
			_3$$7 = nesting;
		}
		_4$$7 = _3$$7;
		if (_4$$7) {
			ZEPHIR_CALL_METHOD(&_5$$7, this_ptr, "isnestedtransactionswithsavepoints", NULL, 0);
			zephir_check_call_status();
			_4$$7 = zephir_is_true(&_5$$7);
		}
		if (_4$$7) {
			ZEPHIR_CALL_METHOD(&savepointName, this_ptr, "getnestedtransactionsavepointname", NULL, 0);
			zephir_check_call_status();
			zephir_read_property(&_6$$8, this_ptr, SL("_eventsManager"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&eventsManager, &_6$$8);
			if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
				ZEPHIR_INIT_VAR(&_7$$9);
				ZVAL_STRING(&_7$$9, "db:rollbackSavepoint");
				ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_7$$9, this_ptr, &savepointName);
				zephir_check_call_status();
			}
			RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("_transactionLevel") TSRMLS_CC));
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "rollbacksavepoint", NULL, 0, &savepointName);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	if (transactionLevel > 0) {
		RETURN_ON_FAILURE(zephir_property_decr(this_ptr, SL("_transactionLevel") TSRMLS_CC));
	}
	RETURN_MM_BOOL(0);

}

