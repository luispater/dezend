/*
**      msql.h  -
**
**
** Copyright (c) 1993-95  David J. Hughes
** Copyright (c) 1995  Hughes Technologies Pty Ltd
**
** Permission to use, copy, and distribute for non-commercial purposes,
** is hereby granted without fee, providing that the above copyright
** notice appear in all copies and that both the copyright notice and this
** permission notice appear in supporting documentation.
**
** This software is provided "as is" without any expressed or implied warranty.
**
** ID = "$Id:"
**
*/

/*
** prevent double loading (start)
*/
#ifndef __H_MSQL
#define __H_MSQL
#if WIN32
#define __STDC__ 1
#	ifdef APIENTRY
#	undef APIENTRY
#	endif
#    define APIENTRY
#endif

#ifndef APIENTRY
#  ifndef OS2
#    define APIENTRY
#  else
#    ifdef BCPP
#      define _System   _syscall
#      define _Optlink
#    endif
#    define APIENTRY _System
#  endif
#endif

#if defined(__STDC__) || defined(__cplusplus) || defined(OS2)
#  define __ANSI_PROTO(x)       x
#else
#  define __ANSI_PROTO(x)       ()
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef char    ** m_row;

typedef struct field_s {
        char    *name,
                *table;
        int     type,
                length,
                flags;
} m_field;



typedef struct  m_data_s {
        int     width;
        m_row   data;
        struct  m_data_s *next;
} m_data;

typedef struct m_fdata_s {
        m_field field;
        struct m_fdata_s *next;
} m_fdata;



typedef struct result_s {
        m_data  *queryData,
                *cursor;
        m_fdata *fieldData,
                *fieldCursor;
        int     numRows,
                numFields;
} m_result;


#define msqlNumRows(res) res->numRows
#define msqlNumFields(res) res->numFields


#define INT_TYPE        1
#define CHAR_TYPE       2
#define REAL_TYPE       3
#define IDENT_TYPE      4
#define NULL_TYPE       5

#define NOT_NULL_FLAG   1
#define PRI_KEY_FLAG    2

#define IS_PRI_KEY(n)   (n & PRI_KEY_FLAG)
#define IS_NOT_NULL(n)  (n & NOT_NULL_FLAG)

/*
** Definition of "localhost" (127.0.0.1)
*/
#define MSQL_LOCALHOST  "localhost"

/*
** Pre-declarations for the API library functions
*/
#ifndef _MSQL_SERVER_SOURCE
        extern char         msqlErrMsg[];
        char     * APIENTRY msqlGetErrMsg __ANSI_PROTO((char *));    /* OS/2 */
        int        APIENTRY msqlUserConnect __ANSI_PROTO((char *, char *)); /* OS/2 */
        int        APIENTRY msqlConnect __ANSI_PROTO((char *));
        int        APIENTRY msqlSelectDB __ANSI_PROTO((int, char*));
        int        APIENTRY msqlQuery __ANSI_PROTO((int, char*));
        int        APIENTRY msqlCreateDB __ANSI_PROTO((int, char*));
        int        APIENTRY msqlDropDB __ANSI_PROTO((int, char*));
        int        APIENTRY msqlShutdown __ANSI_PROTO((int));
        int        APIENTRY msqlReloadAcls __ANSI_PROTO((int));
        int        APIENTRY msqlGetProtoInfo();
        char     * APIENTRY msqlGetServerInfo();
        char     * APIENTRY msqlGetHostInfo();
        void       APIENTRY msqlClose __ANSI_PROTO((int));
        void       APIENTRY msqlDataSeek __ANSI_PROTO((m_result*, int));
        void       APIENTRY msqlFieldSeek __ANSI_PROTO((m_result*, int));
        void       APIENTRY msqlFreeResult __ANSI_PROTO((m_result*));
        m_row      APIENTRY msqlFetchRow __ANSI_PROTO((m_result*));
        m_field  * APIENTRY msqlFetchField __ANSI_PROTO((m_result *));
        m_result * APIENTRY msqlListDBs __ANSI_PROTO((int));
        m_result * APIENTRY msqlListTables __ANSI_PROTO((int));
        m_result * APIENTRY msqlListFields __ANSI_PROTO((int, char*));
        m_result * APIENTRY msqlStoreResult();
#endif

#ifdef __cplusplus
        }
#endif

/*
** prevent double loading (end)
*/
#endif

