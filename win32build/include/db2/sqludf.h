/******************************************************************************
 *
 * Source File Name = SQLUDF.H
 *
 * (C) COPYRIGHT International Business Machines Corp. 1987, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Function = Include File for use in compiling User Defined Function.
 *            Intended to help writers of UDFs deal with the interface
 *            between DBMS and UDF.  Contains:
 *              common structures
 *              "language types" for the SQL types
 *              enumerated type declaration for call-type argument
 *              SQLSTATE constants
 *              macro for prescribed part of the argument list
 *              macro for scratchpad oriented part of argument list
 *              macros to address prescribed parts of argument list
 *              macros to test for argument null and notnull
 *
 * Operating System = Common C Include File
 *
 *****************************************************************************/

#ifndef  SQL_H_SQLUDF
#define SQL_H_SQLUDF            /* Permit duplicate Includes */

#ifdef __cplusplus
extern "C" {
#endif

#include "sqlsystm.h"             /* System-Specific Include   */

#if (defined(DB2OS2) || defined(DB2NT))
#pragma pack(4)
#elif (defined(DB2WIN))
#pragma pack(2)
#elif (defined(DB2MAC))
#if (defined(DB2PPC))
#pragma align 4
#elif (defined(DB268K))
#pragma align 2
#endif
#elif (defined(DB2HP) || defined(DB2SNI))

#elif (defined(DB2SUN))
#pragma options align=natural
#elif (defined(DB2AIX))
#pragma options align=power
#endif

/*==============================================*/
/*==============================================*/
/*== Common #defines, used in this file.      ==*/
/*==============================================*/
/*==============================================*/
#define   SQLUDF_SQLSTATE_LEN       5    /* length of SQLSTATE   */
#define   SQLUDF_SCRATCHPAD_LEN   100    /* length of scratchpad */
#define   SQLUDF_FQNAME_LEN        27    /* length of fully-qualified name */
#define   SQLUDF_SPECNAME_LEN      18    /* length of function specific name */
#define   SQLUDF_MSGTEXT_LEN       70    /* length of message text area */
#define   SQLUDF_MAX_IDENT_LEN    128    /* max length of identifier */
#define   SQLUDF_SH_IDENT_LEN       8    /* length of short identifier */
/* LIMIT on total number of columns for a result table of TABLE FUNCTION.
** This is DIFFERENT than the regular limit on DB2/CS tables.
*/
#define SQLUDF_MAXCOL_TABFUN       255

/*==============================================*/
/*==============================================*/
/*== Common structures.                       ==*/
/*== Note:  these are used in the C "language ==*/
/*==        type" definitions which follow.   ==*/
/*==============================================*/
/*==============================================*/

#ifndef SQL_SQLDBCHAR_DEFN
#define SQL_SQLDBCHAR_DEFN
  typedef unsigned short sqldbchar;
#endif

/*---------------------------------------------------------------------*/
/* Structure used for  VARCHAR FOR BIT DATA, LONG VARCHAR              */
/*---------------------------------------------------------------------*/
SQL_STRUCTURE  sqludf_vc_fbd
{
   unsigned short length;         /* length of data */
   char           data[1];        /* first char of data */
};

/*-------------------------------------------------*/
/* Structure used for: LONG VARGRAPHIC             */
/*-------------------------------------------------*/
SQL_STRUCTURE  sqludf_vg
{
   unsigned short length;         /* length of data */
#ifdef SQL_WCHART_CONVERT
   wchar_t        data[1];        /* first char of data */
#else
   sqldbchar      data[1];        /* first char of data */
#endif
};

/*---------------------------------*/
/* Structure used for: BLOB, CLOB  */
/*---------------------------------*/
SQL_STRUCTURE  sqludf_lob
{
   unsigned long  length;         /* length of data */
   char           data[1];        /* first char of data */
};

/*----------------------------*/
/* Structure used for: DBCLOB */
/*----------------------------*/
SQL_STRUCTURE  sqludf_lobg
{
   unsigned long  length;         /* length of data */
#ifdef SQL_WCHART_CONVERT
   wchar_t        data[1];        /* first char of data */
#else
   sqldbchar      data[1];        /* first char of data */
#endif
};

/*------------------------------------------------------------*/
/* Structure used for: the scratchpad.                        */
/* Note: This structure as provided by DB2/CS gives the       */
/*       overall size/structure of the scratchpad argument.   */
/*       Individual UDFs which use a scratchpad may wish to   */
/*       override the "data" variable of this scratchpad      */
/*       with variables that make sense for the particular    */
/*       UDF.                                                 */
/* Note: Remember that the "data" variable is initialized     */
/*       by DB2/CS to all \0 before the first call.           */
/*------------------------------------------------------------*/
SQL_STRUCTURE  sqludf_scratchpad
{
   unsigned long  length;         /* length of scratchpad data */
   char           data[SQLUDF_SCRATCHPAD_LEN]; /* scratchpad data, init. to all \0 */
};


/*------------------------------------------------------------*/
/* Structure used for: Database code page.                    */
/*------------------------------------------------------------*/
/* DB2/CS code page structure */
struct db2_cs_cdpg
{
  unsigned long  sbcs;                          /* DB single byte CS          */
  unsigned long  dbcs;                          /* DB double byte CS          */
  unsigned long  comp;                          /* DB composite codepage CS   */
  unsigned char  dummy[36];                     /* reserved for later use     */
};

struct db2_mvs_cdpg
{
  unsigned long ascii_sbcs;
  unsigned long ascii_dbcs;
  unsigned long ascii_mixed;
  unsigned long ebcdic_sbcd;
  unsigned long ebcdic_dbcs;
  unsigned long ebcdic_mixed;
  unsigned long encoding_scheme;
  unsigned char reserved[20];
};

/* code page structure */
union db_cdpg
{
  struct db2_cs_cdpg cdpg_cs;                   /* DB2/CS code page           */
  struct db2_mvs_cdpg cdpg_mvs;                 /* DB2/MVS code page          */
};


/*===============================================================*/
/*== Operating System "platform" definitions.                  ==*/
/*===============================================================*/
#define SQLUDF_PLATFORM_UNKNOWN         0         /* Unknown platform         */
#define SQLUDF_PLATFORM_OS2             1         /* OS/2                     */
#define SQLUDF_PLATFORM_WINDOWS         3         /* Windows                  */
#define SQLUDF_PLATFORM_AIX             4         /* AIX                      */
#define SQLUDF_PLATFORM_NT              5         /* NT                       */
#define SQLUDF_PLATFORM_HP              6         /* HP                       */
#define SQLUDF_PLATFORM_SUN             7         /* Sun                      */
#define SQLUDF_PLATFORM_MVS             8         /* MVS                      */
#define SQLUDF_PLATFORM_SNI            13         /* Siemens Nixdorf          */
#define SQLUDF_PLATFORM_WINDOWS95      15         /* Windows 95               */
#define SQLUDF_PLATFORM_SCO            16         /* SCO                      */

/*------------------------------------------------------------*/
/* Structure used for: dbinfo.                                */
/* Note: This structure as provided by DB2/CS to the UDF      */
/*       contains additional information which may be used to */
/*       enable (but not require) additional capability or    */
/*       optimizations on the part of the external function.  */
/*       This argument is only present if the DBINFO          */
/*       keyword is specified in the CREATE FUNCTION          */
/*       statement.                                           */
/*       Embedded SQL Programming Guide discusses the         */
/*       possible uses of this information.                   */
/*------------------------------------------------------------*/
SQL_STRUCTURE  sqludf_dbinfo
{
  unsigned short    dbnamelen;                     /* database name length    */
  unsigned char     dbname[SQLUDF_MAX_IDENT_LEN];  /* database name           */
  unsigned short    authidlen;                     /* authorization ID length */
  unsigned char     authid[SQLUDF_MAX_IDENT_LEN];  /* appl authorization ID   */
  union db_cdpg     codepg;                        /* database code page      */
  unsigned short    tbschemalen;                   /* table schema name length*/
  unsigned char     tbschema[SQLUDF_MAX_IDENT_LEN];/* table schema name       */
  unsigned short    tbnamelen;                     /* table name length       */
  unsigned char     tbname[SQLUDF_MAX_IDENT_LEN];  /* table name              */
  unsigned short    colnamelen;                    /* column name length      */
  unsigned char     colname[SQLUDF_MAX_IDENT_LEN]; /* column name             */

  /*---------------------------------------------------------------*/
  /* Database version/release.  The field has the format pppvvrrm: */
  /*   ppp -- identifies the product name                          */
  /*   vv  -- two digit rversion identifier such as '03'           */
  /*   rr  -- two digit release identifier such as '01'            */
  /*   m   -- one digit modification level identifier such as '0'  */
  /*---------------------------------------------------------------*/
  unsigned char     ver_rel[SQLUDF_SH_IDENT_LEN];

  /*---------------------------------------------------------------*/
  /* OS Platform information. Please refer to Operating System     */
  /* "platform" definitions above for its defination.              */
  /*---------------------------------------------------------------*/
  unsigned long     platform;
  unsigned short    numtfcol;                      /* number of entires in    */
                                                   /* the TF column list array*/
  unsigned char     resd1[24];                     /* Reserved- for expansion */
  /*---------------------------------------------------------------*/
  /* ftcolumn will be allocated dynamically if TF                  */
  /* is defined; otherwise, this pointer points to NULL.           */
  /*---------------------------------------------------------------*/
  unsigned short   *tfcolumn;
  unsigned char     resd2[24];                     /* Reserved- for expansion */
};


/*===============================================================*/
/*===============================================================*/
/*== "Language type" definitions, for argument/result values.  ==*/
/*== Usage note: define input and output SQL arguments as      ==*/
/*==             pointers to these types.  For example:        ==*/
/*==                  SQLUDF_INTEGER *arg1,   or               ==*/
/*==                  SQLUDF_NULLIND *arg1_nullind,            ==*/
/*===============================================================*/
/*===============================================================*/
#define   SQLUDF_SMALLINT    short                /* for SMALLINT            */
#define   SQLUDF_INTEGER     long                 /* for INTEGER             */
#define   SQLUDF_DOUBLE      double               /* for DOUBLE PRECISION (FLOAT) */
#define   SQLUDF_REAL        float                /* for REAL (FLOAT4)       */
#define   SQLUDF_CHAR        char                 /* for CHAR w/wo FOR BIT DATA */
#define   SQLUDF_VARCHAR     char                 /* for VARCHAR             */
#define   SQLUDF_VARCHAR_FBD SQL_STRUCTURE sqludf_vc_fbd /* VARCHAR FOR BIT DATA */
#define   SQLUDF_LONG        SQL_STRUCTURE sqludf_vc_fbd /* LONG VAR w/wo FOR BIT DATA */

#ifdef SQL_WCHART_CONVERT
#define   SQLUDF_GRAPH       wchar_t              /* for GRAPHIC             */
#else
#define   SQLUDF_GRAPH       sqldbchar            /* for GRAPHIC             */
#endif

#ifdef SQL_WCHART_CONVERT
#define   SQLUDF_VARGRAPH    wchar_t              /* for VARGRAPHIC          */
#else
#define   SQLUDF_VARGRAPH    sqldbchar            /* for VARGRAPHIC          */
#endif

#define   SQLUDF_LONGVARG    SQL_STRUCTURE sqludf_vg /* for LONG VARGRAPHIC  */
#define   SQLUDF_DATE        char                 /* for DATE                */
#define   SQLUDF_TIME        char                 /* for TIME                */
#define   SQLUDF_STAMP       char                 /* for TIMESTAMP           */
#define   SQLUDF_CLOB        SQL_STRUCTURE sqludf_lob  /* for CLOB           */
#define   SQLUDF_BLOB        SQL_STRUCTURE sqludf_lob  /* for BLOB           */
#define   SQLUDF_DBCLOB      SQL_STRUCTURE sqludf_lobg /* for DBCLOB         */

#define   SQLUDF_NULLIND     short                /* for null indicators     */

typedef unsigned long   udf_locator;
#define   SQLUDF_LOCATOR     unsigned long /* for LOB LOCATOR                */

/*===============================================================*/
/*===============================================================*/
/*== "Language type" definitions, for scratchpad and call type ==*/
/*== arguments to a UDF.                                       ==*/
/*== Usage note: define arguments as pointers                  ==*/
/*==             to these types.  For example:                 ==*/
/*==                  SQLUDF_SCRATCHPAD  *scrpad,              ==*/
/*===============================================================*/
/*===============================================================*/
#define   SQLUDF_SCRATCHPAD  SQL_STRUCTURE sqludf_scratchpad /* for scratchpad */
#define   SQLUDF_CALL_TYPE   enum sqludf_call_type           /* for call type */

/*===============================================================*/
/*===============================================================*/
/*== "DBINFO" definitions, for dbinfo arguments to a UDF.      ==*/
/*== Usage note: define arguments as pointer. For example:     ==*/
/*==                  SQLUDF_DBINFO  *dbinfo                   ==*/
/*===============================================================*/
/*===============================================================*/
#define   SQLUDF_DBINFO  SQL_STRUCTURE sqludf_dbinfo         /* for dbinfo */


/*=====================================================================*/
/*=====================================================================*/
/*== Enumerated type, for call-type argument (used with scratchpad). ==*/
/*=====================================================================*/
/*=====================================================================*/
enum sqludf_call_type
{
  SQLUDF_FIRST_CALL  = -1,  /* first call since setting scratchpad to hex 0s  */
  SQLUDF_NORMAL_CALL =  0,  /* normal call                                    */
  SQLUDF_FINAL_CALL  =  1   /* special last call for cleanup (no real args!)  */
};

/* Redefine UDF/TF  call types to use for Table functions. */
#define   SQLUDF_TF_OPEN   SQLUDF_FIRST_CALL  /* Open table  */
#define   SQLUDF_TF_FETCH  SQLUDF_NORMAL_CALL /* Fetch next row */
#define   SQLUDF_TF_CLOSE  SQLUDF_FINAL_CALL  /* Close table */

/* The following are deprecated; please use the SQLUDF_TF_* forms instead */
#define   SQL_TF_OPEN   SQLUDF_FIRST_CALL  /* Open table  */
#define   SQL_TF_FETCH  SQLUDF_NORMAL_CALL /* Fetch next row */
#define   SQL_TF_CLOSE  SQLUDF_FINAL_CALL  /* Close table */



/*=========================================================================*/
/*=========================================================================*/
/*== Macros, for defining the always-present (trailing) input arguments: ==*/
/*=========================================================================*/
/*=========================================================================*/

/*-----------------------------------------------------------------------*/
/* For the case WITHOUT scratchpad / final_call / dbinfo arguments:      */
/* SQLUDF_TRAIL_ARGS                                                     */
/* defines the always present trailing arguments-- pointers to:          */
/*               sqlstate,                                               */
/*               fully qualified function name,                          */
/*               function specific name,                                 */
/*               message text                                            */
/*                                                                       */
/* Usage note: when both SCRATCHPAD and FINAL CALL are defined for the   */
/*             function, use SQLUDF_TRAIL_ARGS_ALL immediately below.    */
/*                                                                       */
/*             When SCRATCHPAD is defined and FINAL CALL is not, use     */
/*             SQLUDF_TRAIL_ARGS with an additional argument appended    */
/*             which is a pointer to: SQL_SCRATCHPAD                     */
/*             E.G.:  SQL_SCRATCHPAD scratch_ptr                         */
/*                                                                       */
/*             When DBINFO is defined, use an additional argument        */
/*             appended at the end of the above argument list.           */
/*             This argument is a pointer to: SQLUDF_DBINFO              */
/*-----------------------------------------------------------------------*/
#define   SQLUDF_TRAIL_ARGS char   sqludf_sqlstate[SQLUDF_SQLSTATE_LEN+1], \
                            char   sqludf_fname[SQLUDF_FQNAME_LEN+1], \
                            char   sqludf_fspecname[SQLUDF_SPECNAME_LEN+1], \
                            char   sqludf_msgtext[SQLUDF_MSGTEXT_LEN+1]

/*-----------------------------------------------------------------------*/
/* For the case WITH scratchpad / final_call arguments:                  */
/* SQLUDF_TRAIL_ARGS_ALL                                                 */
/* defines the trailing arguments which are present-- pointers to:       */
/*               sqlstate,                                               */
/*               fully qualified function name,                          */
/*               function specific name,                                 */
/*               message text,                                           */
/*               scratchpad,                                             */
/*               call type                                               */
/*                                                                       */
/* Usage note: this can be used when                                     */
/*             - SCRATCHPAD and FINAL CALL are both defined for UDF.     */
/*                                                                       */
/*             But CANNOT be used for the case where SCRATCHPAD is not   */
/*             defined and FINAL CALL is defined.  In that case the      */
/*             call type argument immediately follows the                */
/*             message text argument.                                    */
/*-----------------------------------------------------------------------*/
#define SQLUDF_TRAIL_ARGS_ALL char   sqludf_sqlstate[SQLUDF_SQLSTATE_LEN+1], \
                              char   sqludf_fname[SQLUDF_FQNAME_LEN+1], \
                              char   sqludf_fspecname[SQLUDF_SPECNAME_LEN+1], \
                              char   sqludf_msgtext[SQLUDF_MSGTEXT_LEN+1], \
                              SQLUDF_SCRATCHPAD *sqludf_scratchpad, \
                              SQLUDF_CALL_TYPE  *sqludf_call_type


/*===========================================================*/
/*===========================================================*/
/*== Macros, for referencing the trailing input arguments. ==*/
/*===========================================================*/
/*===========================================================*/

/*------------------------------------------------------------------*/
/* For the always-present arguments.  Note: all are char arrays.    */
/*------------------------------------------------------------------*/
#define   SQLUDF_STATE     sqludf_sqlstate   /* SQLSTATE returned by UDF      */
#define   SQLUDF_FNAME     sqludf_fname      /* fully qual func name          */
#define   SQLUDF_FSPEC     sqludf_fspecname  /* func specific name            */
#define   SQLUDF_MSGTX     sqludf_msgtext    /* message text returned by UDF  */

/*------------------------------------------------------------------*/
/* For the scratchpad.  Note: SQLUDF_SCRAT is a pointer.               */
/*------------------------------------------------------------------*/
#define   SQLUDF_SCRAT    (sqludf_scratchpad) /* scratchpad area             */

/*------------------------------------------------------------------*/
/* For the call type.   Note: pointer to enum type is dereferenced. */
/*------------------------------------------------------------------*/
#define   SQLUDF_CALLT (*sqludf_call_type) /* call type (used with scr'pad)  */


/*==============================================================*/
/*==============================================================*/
/*== Special sqlstate (SQLUDF_STATE) values that UDF can set. ==*/
/*== Usage note: the values "38xxx" and "01Hxx" are included  ==*/
/*==             for completeness and for their educational   ==*/
/*==             value.  You will want to define and use your ==*/
/*==             won constants with your own values           ==*/
/*==             substituted for the generic "x"s.            ==*/
/*==============================================================*/
/*==============================================================*/
#define   SQLUDF_STATE_OK      "00000"  /* good return, no problem -         */
                                        /* SQLUDF_STATE is init'd to this    */
                                        /* value by DB2 before calling UDF.  */
#define   SQLUDF_STATE_SQLCALL "38502"  /* error- UDF issued SQL call,       */
                                        /* DB2 returned error (-487) to UDF. */
#define   SQLUDF_STATE_ERR     "38xxx"  /* error- xxx is UDF-defined, UDF    */
                                        /* should overwrite, but NOT USE     */
                                        /* values 0xx thru 5xx, as these are */
                                        /* reserved by IBM.                  */
#define   SQLUDF_STATE_WARN    "01Hxx"  /* warning - xx is UDF-defined, UDF  */
                                        /* should overwrite, any values OK.  */


/*================================================*/
/*================================================*/
/*== Macros, for testing for argument nullness: ==*/
/*================================================*/
/*================================================*/

/*------------------------------------------------------*/
/* Test for argument NULL.                              */
/* pass pointer to null indicator, returns TRUE if NULL */
/*------------------------------------------------------*/
#define   SQLUDF_NULL(nullptr)      (*nullptr < 0)

/*----------------------------------------------------------*/
/* Test for argument NOT NULL.                              */
/* pass pointer to null indicator, returns TRUE if NOT NULL */
/*----------------------------------------------------------*/
#define   SQLUDF_NOTNULL(nullptr)   (*nullptr >= 0)

#if (defined(DB2OS2) || defined(DB2NT) || defined(DB2WIN))
#pragma pack()
#elif (defined(DB2MAC))
#pragma align
#elif (defined(DB2HP) || defined(DB2SNI))

#elif (defined(DB2AIX) || defined(DB2SUN))
#pragma options align=reset
#endif


extern int SQL_API_FN sqludf_length(
    udf_locator        *udfloc_p,       /* in:  Pointer to user-provided LOB */
                                        /*      locator value.               */
    long               *return_len_p    /* in/out: Pointer to where the LOB  */
                                        /*      length is to be returned.    */
);

extern int SQL_API_FN sqludf_substr(
    udf_locator        *udfloc_p,       /* in:  Pointer to user-provided LOB */
                                        /*      locator value.               */
    long                start,          /* in:  Substring start value, first */
                                        /*      byte is byte 1.              */
    long                length,         /* in:  Number of bytes to be        */
                                        /*      returned.                    */
    unsigned char      *buffer_p,       /* in/out: Pointer to the buffer     */
                                        /*      into which the bytes are to  */
                                        /*      be placed.                   */
    long               *return_len_p    /* in/out: Pointer to where the      */
                                        /*      number of bytes actually     */
                                        /*      returned is to be placed     */
                                        /*      (can be smaller than length).*/
);

extern int SQL_API_FN sqludf_append(
    udf_locator        *udfloc_p,       /* in:  Pointer to user-provided LOB */
                                        /*      locator value.               */
    unsigned char      *buffer_p,       /* in:  Pointer to the buffer con-   */
                                        /*      taining the bytes which are  */
                                        /*      to be appended.              */
    long                length,         /* in:  Number of bytes to be        */
                                        /*      appended.                    */
    long               *return_len_p    /* in/out: Pointer to where the      */
                                        /*      number of bytes actually     */
                                        /*      appended is to be placed.    */
);

extern int SQL_API_FN sqludf_create_locator(
    int                 loc_type,       /* in:  Type of LOB;  can be any of  */
                                        /*      the types from sql.h repre-  */
                                        /*      senting LOBs; for example:   */
                                        /*      SQL_TYP_CLOB  for type CLOB, */
                                        /*      SQL_TYP_BLOB  for type BLOB, */
                                        /*      SQL_TYP_DBCLOB for   DBCLOB. */
    udf_locator       **loc_p           /* in/out:  Pointer to a preset      */
                                        /*      pointer to where the locator */
                                        /*      is to be returned.           */
);

extern int SQL_API_FN sqludf_free_locator(
    udf_locator        *udfloc_p        /* in:  Pointer to user-provided LOB */
                                        /*      locator value.               */
);


#ifdef __cplusplus
}
#endif

#endif /* SQL_H_SQLUDF */               /* end self-include protection */

