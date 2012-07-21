PHP_ARG_ENABLE(phalcon, whether to enable phalcon framework, [ --enable-phalcon   Enable phalcon framework])

if test "$PHP_PHALCON" = "yes"; then
  AC_DEFINE(HAVE_PHALCON, 1, [Whether you have Phalcon Framework])
  PHP_NEW_EXTENSION(phalcon, phalcon.c kernel/main.c kernel/fcall.c kernel/require.c kernel/debug.c kernel/assert.c kernel/object.c kernel/array.c kernel/operators.c kernel/concat.c kernel/exception.c kernel/memory.c session/namespace.c loader.c text.c test.c router/rewrite.c router/regex.c config/exception.c config/adapter/ini.c exception.c db.c logger.c cache/exception.c cache/frontend/output.c cache/frontend/none.c cache/frontend/data.c cache/backend.c cache/backend/memcache.c cache/backend/apc.c cache/backend/file.c acl/exception.c acl/adapter/memory.c acl/role.c acl/resource.c cache.c dispatcher/exception.c view.c registry.c view/engine.c view/exception.c view/engine/php.c view/engine/twig.c view/engine/mustache.c paginator/exception.c paginator/adapter/array.c paginator/adapter/model.c tag/exception.c tag/select.c internal/test.c internal/testparent.c internal/testtemp.c internal/testdummy.c controller.c request/exception.c request/file.c paginator.c utils.c response/exception.c response/headers.c dispatcher.c translate.c db/pool.c db/profiler.c db/exception.c db/reference.c db/adapter/mysql.c db/adapter/postgresql.c db/profiler/item.c db/rawvalue.c db/column.c db/index.c db/result/mysql.c db/result/postgresql.c db/dialect/mysql.c db/dialect/postgresql.c model/validator/uniqueness.c model/validator/exclusionin.c model/validator/regex.c model/validator/inclusionin.c model/validator/numericality.c model/validator/email.c model/query.c model/exception.c model/base.c model/validator.c model/row.c model/metadata.c model/message.c model/manager.c model/metadata/memory.c model/metadata/apc.c model/metadata/session.c model/resultset.c tag.c response.c request.c transaction/exception.c transaction/failed.c transaction/manager.c controller/front.c session.c flash.c config.c filter.c acl.c translate/exception.c translate/adapter/array.c logger/exception.c logger/adapter/file.c logger/item.c transaction.c loader/exception.c, $ext_shared)
fi
