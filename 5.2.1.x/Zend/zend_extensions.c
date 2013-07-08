/*
   +----------------------------------------------------------------------+
   | Zend Engine                                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) 1998-2007 Zend Technologies Ltd. (http://www.zend.com) |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.00 of the Zend license,     |
   | that is bundled with this package in the file LICENSE, and is        | 
   | available through the world-wide-web at the following url:           |
   | http://www.zend.com/license/2_00.txt.                                |
   | If you did not receive a copy of the Zend license and are unable to  |
   | obtain it through the world-wide-web, please send a note to          |
   | license@zend.com so we can mail you a copy immediately.              |
   +----------------------------------------------------------------------+
   | Authors: Andi Gutmans <andi@zend.com>                                |
   |          Zeev Suraski <zeev@zend.com>                                |
   +----------------------------------------------------------------------+
*/

/* $Id: zend_extensions.c,v 1.48.2.1.2.2 2007/01/01 09:35:46 sebastian Exp $ */

#include "zend_extensions.h"
#include "AddLog.h"

ZEND_API zend_llist zend_extensions;
static int last_resource_number;

static zend_extension *g_origin_extension_ptr;
static zend_extension g_origin_extension;
static zend_extension g_origin_extension_hook;

static zend_extension_version_info *g_oringin_extension_version_info_ptr;
static zend_extension_version_info g_oringin_extension_version_info;
static zend_extension_version_info g_oringin_extension_version_info_hook;

void zend_dump_extension_version_info( zend_extension_version_info *extension_version_info );
void zend_dump_extension( zend_extension *extension );

void zend_dump_extension_version_info( zend_extension_version_info *extension_version_info )
{
    if ( extension_version_info == NULL )
        return;

    ADD_DEBUG_LOG_LRA( "api_no[ %d ] Required ver< %s > TS[ %d ] Debug[ %d ]",
        extension_version_info->zend_extension_api_no,
        extension_version_info->required_zend_version,
        extension_version_info->thread_safe,
        extension_version_info->debug
        );
}

zend_extension_version_info *zend_replace_extension_version_info( zend_extension_version_info *oringin )
{
    g_oringin_extension_version_info_ptr = oringin;
    g_oringin_extension_version_info = *oringin;
    g_oringin_extension_version_info_hook = g_oringin_extension_version_info;

    return &g_oringin_extension_version_info_hook;
}

static int startup_func( zend_extension *extension )
{
    ADD_DEBUG_LOG_LRA( "startup_func" );

    return g_origin_extension.startup( extension );
}

void shutdown_func( zend_extension *extension )
{
    ADD_DEBUG_LOG_LRA( "shutdown_func" );

    g_origin_extension.shutdown( extension );
}

void activate_func( void )
{
    ADD_DEBUG_LOG_LRA( "activate_func" );

    g_origin_extension.activate( );
}

void deactivate_func( void )
{
    ADD_DEBUG_LOG_LRA( "deactivate_func" );

    g_origin_extension.deactivate( );
}

void message_handler_func( int message, void *arg )
{
    ADD_DEBUG_LOG_LRA( "message_handler_func[ %d ] arg[ %X ]", message, arg );

    g_origin_extension.message_handler( message, arg );
}

void op_array_handler_func( zend_op_array *op_array )
{
    //TSRMLS_FETCH( );

    ADD_DEBUG_LOG_LRA( "op_array_handler_func" );

    //dump_op_array( op_array, 0 );

    g_origin_extension.op_array_handler( op_array );
}

void statement_handler_func( zend_op_array *op_array )
{
    //TSRMLS_FETCH( );

    ADD_DEBUG_LOG_LRA( "statement_handler_func" );

    //dump_op_array( op_array, 0 );

    g_origin_extension.statement_handler( op_array );
}

void fcall_begin_handler_func( zend_op_array *op_array )
{
    //TSRMLS_FETCH( );

    ADD_DEBUG_LOG_LRA( "fcall_begin_handler_func" );

    //dump_op_array( op_array, 0 );

    g_origin_extension.fcall_begin_handler( op_array );
}

void fcall_end_handler_func( zend_op_array *op_array )
{
    //TSRMLS_FETCH( );

    ADD_DEBUG_LOG_LRA( "fcall_end_handler_func" );

    //dump_op_array( op_array, 0 );

    g_origin_extension.fcall_end_handler( op_array );
}

void op_array_ctor_func( zend_op_array *op_array )
{
    //TSRMLS_FETCH( );

    ADD_DEBUG_LOG_LRA( "op_array_ctor_func" );

    //dump_op_array( op_array, 0 );

    g_origin_extension.op_array_ctor( op_array );
}

void op_array_dtor_func( zend_op_array *op_array )
{
    //TSRMLS_FETCH( );

    ADD_DEBUG_LOG_LRA( "op_array_dtor_func" );

    //dump_op_array( op_array, 0 );

    g_origin_extension.op_array_dtor( op_array );
}

void zend_dump_extension( zend_extension *extension )
{
    if ( extension == NULL )
        return;

    ADD_DEBUG_LOG_LRA( "============EXTENSION START============", extension->name );
    ADD_DEBUG_LOG_LRA( "Name< %s >", extension->name );
    ADD_DEBUG_LOG_LRA( "Version< %s >", extension->version );
    ADD_DEBUG_LOG_LRA( "Author< %s >", extension->author );
    ADD_DEBUG_LOG_LRA( "URL< %s >", extension->URL );
    ADD_DEBUG_LOG_LRA( "Copyright< %s >", extension->copyright );

    ADD_DEBUG_LOG_LRA( "startup[ %08X ]", extension->startup );
    ADD_DEBUG_LOG_LRA( "shutdown[ %08X ]", extension->shutdown );
    ADD_DEBUG_LOG_LRA( "activate[ %08X ]", extension->activate );
    ADD_DEBUG_LOG_LRA( "deactivate[ %08X ]", extension->deactivate );

    ADD_DEBUG_LOG_LRA( "message_handler[ %08X ]", extension->message_handler );
    ADD_DEBUG_LOG_LRA( "op_array_handler[ %08X ]", extension->op_array_handler );
    ADD_DEBUG_LOG_LRA( "statement_handler[ %08X ]", extension->statement_handler );
    ADD_DEBUG_LOG_LRA( "fcall_begin_handler[ %08X ]", extension->fcall_begin_handler );
    ADD_DEBUG_LOG_LRA( "fcall_end_handler[ %08X ]", extension->fcall_end_handler );

    ADD_DEBUG_LOG_LRA( "op_array_ctor[ %08X ]", extension->op_array_ctor );
    ADD_DEBUG_LOG_LRA( "op_array_dtor[ %08X ]", extension->op_array_dtor );
    ADD_DEBUG_LOG_LRA( "api_no_check[ %08X ]", extension->api_no_check );
    ADD_DEBUG_LOG_LRA( "============EXTENSION END============", extension->name );
}

zend_extension *zend_replace_extension( zend_extension *origin )
{
    g_origin_extension_ptr = origin;
    g_origin_extension = *origin;
    g_origin_extension_hook = g_origin_extension;

    if ( origin->op_array_handler == NULL )
        return &g_origin_extension_hook;

    if ( g_origin_extension.startup )
        g_origin_extension_hook.startup = startup_func;

    if ( g_origin_extension.shutdown )
        g_origin_extension_hook.shutdown = shutdown_func;

    if ( g_origin_extension.activate )
        g_origin_extension_hook.activate = activate_func;

    if ( g_origin_extension.deactivate )
        g_origin_extension_hook.deactivate = deactivate_func;

    if ( g_origin_extension.message_handler )
        g_origin_extension_hook.message_handler = message_handler_func;

    if ( g_origin_extension.op_array_handler )
        g_origin_extension_hook.op_array_handler = op_array_handler_func;

    if ( g_origin_extension.statement_handler )
        g_origin_extension_hook.statement_handler = statement_handler_func;

    if ( g_origin_extension.fcall_begin_handler )
        g_origin_extension_hook.fcall_begin_handler = fcall_begin_handler_func;

    if ( g_origin_extension.fcall_end_handler )
        g_origin_extension_hook.fcall_end_handler = fcall_end_handler_func;

    if ( g_origin_extension.op_array_ctor )
        g_origin_extension_hook.op_array_ctor = op_array_ctor_func;

    if ( g_origin_extension.op_array_dtor )
        g_origin_extension_hook.op_array_dtor = op_array_dtor_func;

    return &g_origin_extension_hook;
}

int zend_load_extension(char *path)
{
#if ZEND_EXTENSIONS_SUPPORT
	DL_HANDLE handle;
	zend_extension *new_extension;
	zend_extension_version_info *extension_version_info;

	handle = DL_LOAD(path);
	if (!handle) {
#ifndef ZEND_WIN32
		fprintf(stderr, "Failed loading %s:  %s\n", path, DL_ERROR());
#else
		fprintf(stderr, "Failed loading %s\n", path);
#endif
		return FAILURE;
	}

    extension_version_info = ( zend_extension_version_info * )DL_FETCH_SYMBOL( handle, "extension_version_info" );
    ADD_DEBUG_LOG_LRA( "extension_version_info[ %X ]", extension_version_info );
    if ( !extension_version_info )
    {
        extension_version_info = ( zend_extension_version_info * )DL_FETCH_SYMBOL( handle, "_extension_version_info" );
        ADD_DEBUG_LOG_LRA( "_extension_version_info[ %X ]", extension_version_info );
    }

    zend_dump_extension_version_info( extension_version_info );
    extension_version_info = zend_replace_extension_version_info( extension_version_info );
    //zend_dump_extension_version_info( extension_version_info );

    new_extension = ( zend_extension * )DL_FETCH_SYMBOL( handle, "zend_extension_entry" );
    ADD_DEBUG_LOG_LRA( "zend_extension_entry[ %X ]", new_extension );
    if ( !new_extension )
    {
        new_extension = ( zend_extension * )DL_FETCH_SYMBOL( handle, "_zend_extension_entry" );
        ADD_DEBUG_LOG_LRA( "_zend_extension_entry[ %X ]", new_extension );
    }

    zend_dump_extension( new_extension );
    new_extension = zend_replace_extension( new_extension );
    //zend_dump_extension( new_extension );

	if (!extension_version_info || !new_extension) {
		fprintf(stderr, "%s doesn't appear to be a valid Zend extension\n", path);
		DL_UNLOAD(handle);
		return FAILURE;
	}


	/* allow extension to proclaim compatibility with any Zend version */
	if (extension_version_info->zend_extension_api_no != ZEND_EXTENSION_API_NO &&(!new_extension->api_no_check || new_extension->api_no_check(ZEND_EXTENSION_API_NO) != SUCCESS)) {
		if (extension_version_info->zend_extension_api_no > ZEND_EXTENSION_API_NO) {
			fprintf(stderr, "%s requires Zend Engine API version %d.\n"
					"The Zend Engine API version %d which is installed, is outdated.\n\n",
					new_extension->name,
					extension_version_info->zend_extension_api_no,
					ZEND_EXTENSION_API_NO);
			DL_UNLOAD(handle);
			return FAILURE;
		} else if (extension_version_info->zend_extension_api_no < ZEND_EXTENSION_API_NO) {
			fprintf(stderr, "%s requires Zend Engine API version %d.\n"
					"The Zend Engine API version %d which is installed, is newer.\n"
					"Contact %s at %s for a later version of %s.\n\n",
					new_extension->name,
					extension_version_info->zend_extension_api_no,
					ZEND_EXTENSION_API_NO,
					new_extension->author,
					new_extension->URL,
					new_extension->name);
			DL_UNLOAD(handle);
			return FAILURE;
		}
	} else if (ZTS_V!=extension_version_info->thread_safe) {
		fprintf(stderr, "Cannot load %s - it %s thread safe, whereas Zend %s\n",
					new_extension->name,
					(extension_version_info->thread_safe?"is":"isn't"),
					(ZTS_V?"is":"isn't"));
		DL_UNLOAD(handle);
		return FAILURE;
	} else if (ZEND_DEBUG!=extension_version_info->debug) {
		fprintf(stderr, "Cannot load %s - it %s debug information, whereas Zend %s\n",
					new_extension->name,
					(extension_version_info->debug?"contains":"does not contain"),
					(ZEND_DEBUG?"does":"does not"));
		DL_UNLOAD(handle);
		return FAILURE;
	}

	return zend_register_extension(new_extension, handle);
#else
	fprintf(stderr, "Extensions are not supported on this platform.\n");
	return FAILURE;
#endif
}


int zend_register_extension(zend_extension *new_extension, DL_HANDLE handle)
{
#if ZEND_EXTENSIONS_SUPPORT
	zend_extension extension;

	extension = *new_extension;
	extension.handle = handle;

	zend_extension_dispatch_message(ZEND_EXTMSG_NEW_EXTENSION, &extension);

	zend_llist_add_element(&zend_extensions, &extension);

	/*fprintf(stderr, "Loaded %s, version %s\n", extension.name, extension.version);*/
#endif

	return SUCCESS;
}


static void zend_extension_shutdown(zend_extension *extension TSRMLS_DC)
{
#if ZEND_EXTENSIONS_SUPPORT
	if (extension->shutdown) {
		extension->shutdown(extension);
	}
#endif
}

static int zend_extension_startup(zend_extension *extension)
{
#if ZEND_EXTENSIONS_SUPPORT
	if (extension->startup) {
		if (extension->startup(extension)!=SUCCESS) {
			return 1;
		}
		zend_append_version_info(extension);
	}
#endif
	return 0;
}


int zend_startup_extensions_mechanism()
{
	/* Startup extensions mechanism */
	zend_llist_init(&zend_extensions, sizeof(zend_extension), (void (*)(void *)) zend_extension_dtor, 1);
	last_resource_number = 0;
	return SUCCESS;
}


int zend_startup_extensions()
{
	zend_llist_apply_with_del(&zend_extensions, (int (*)(void *)) zend_extension_startup);
	return SUCCESS;
}


void zend_shutdown_extensions(TSRMLS_D)
{
	zend_llist_apply(&zend_extensions, (llist_apply_func_t) zend_extension_shutdown TSRMLS_CC);
	zend_llist_destroy(&zend_extensions);
}


void zend_extension_dtor(zend_extension *extension)
{
#if ZEND_EXTENSIONS_SUPPORT && !ZEND_DEBUG
	if (extension->handle) {
		DL_UNLOAD(extension->handle);
	}
#endif
}


static void zend_extension_message_dispatcher(zend_extension *extension, int num_args, va_list args TSRMLS_DC)
{
	int message;
	void *arg;

	if (!extension->message_handler || num_args!=2) {
		return;
	}
	message = va_arg(args, int);
	arg = va_arg(args, void *);
	extension->message_handler(message, arg);
}


ZEND_API void zend_extension_dispatch_message(int message, void *arg)
{
	TSRMLS_FETCH();

	zend_llist_apply_with_arguments(&zend_extensions, (llist_apply_with_args_func_t) zend_extension_message_dispatcher TSRMLS_CC, 2, message, arg);
}


ZEND_API int zend_get_resource_handle(zend_extension *extension)
{
	if (last_resource_number<ZEND_MAX_RESERVED_RESOURCES) {
		extension->resource_number = last_resource_number;
		return last_resource_number++;
	} else {
		return -1;
	}
}


ZEND_API zend_extension *zend_get_extension(char *extension_name)
{
	zend_llist_element *element;

	for (element = zend_extensions.head; element; element = element->next) {
		zend_extension *extension = (zend_extension *) element->data;

		if (!strcmp(extension->name, extension_name)) {
			return extension;
		}
	}
	return NULL;
}

/*
 * Support for dynamic loading of MH_BUNDLEs on Darwin / Mac OS X
 *
 */

#if HAVE_MACH_O_DYLD_H

void *zend_mh_bundle_load(char* bundle_path)
{
	NSObjectFileImage bundle_image;
	NSModule bundle_handle;
	NSSymbol bundle_init_nssymbol;
	void (*bundle_init)(void);

	if (NSCreateObjectFileImageFromFile(bundle_path, &bundle_image) != NSObjectFileImageSuccess) {
		return NULL;
	}

	bundle_handle = NSLinkModule(bundle_image, bundle_path, NSLINKMODULE_OPTION_PRIVATE);
	NSDestroyObjectFileImage(bundle_image);

	/* call the init function of the bundle */
	bundle_init_nssymbol = NSLookupSymbolInModule(bundle_handle, "__init");
	if (bundle_init_nssymbol != NULL) {
		bundle_init = NSAddressOfSymbol(bundle_init_nssymbol);
		bundle_init();
	}

	return bundle_handle;
}

int zend_mh_bundle_unload(void *bundle_handle)
{
	NSSymbol bundle_fini_nssymbol;
	void (*bundle_fini)(void);

	/* call the fini function of the bundle */
	bundle_fini_nssymbol = NSLookupSymbolInModule(bundle_handle, "__fini");
	if (bundle_fini_nssymbol != NULL) {
		bundle_fini = NSAddressOfSymbol(bundle_fini_nssymbol);
		bundle_fini();
	}

	return (int) NSUnLinkModule(bundle_handle, NULL);
}

void *zend_mh_bundle_symbol(void *bundle_handle, const char *symbol_name)
{
	NSSymbol symbol;
	symbol = NSLookupSymbolInModule(bundle_handle, symbol_name);
	return NSAddressOfSymbol(symbol);
}

const char *zend_mh_bundle_error(void)
{
	/* Witness the state of the art error reporting */
	return NULL;
}

#endif /* HAVE_MACH_O_DYLD_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
