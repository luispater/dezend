/*****************************************************************************
 *
 * Source File Name = SQLDA.H
 *
 * (C) COPYRIGHT International Business Machines Corp. 1987, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Function = Include File defining:
 *              SQL Descriptor Area
 *
 * Operating System = Common C Include File
 *
 ****************************************************************************/

#ifndef  SQLDASIZE             /* Permit duplicate Includes                 */

#include "sqlsystm.h"          /* System-Specific Include                   */
/* _SQLOLDCHAR defaults to 'char'.  See sqlsystm.h for details. */

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

/* SQLDA: SQL Descriptor Area - Variable descriptor                         */

SQL_STRUCTURE  sqlname                  /* Variable Name                    */
{
    short          length;              /* Name length [1..30]              */
    _SQLOLDCHAR    data[30];            /* Variable or Column name          */
};

SQL_STRUCTURE  sqldistinct_type         /* name of distinct type            */
{
    short          length;              /* Name length [1..27]              */
    char           data[27];            /* Name of distince type            */
    char           reserved1[3];        /*reserved                          */
};

SQL_STRUCTURE  sqlvar                   /* Variable Description             */
{
    short          sqltype;             /* Variable data type               */
    short          sqllen;              /* Variable data length             */
    _SQLOLDCHAR   *SQL_POINTER sqldata; /* Pointer to variable data value   */
    short         *SQL_POINTER sqlind;  /* Pointer to Null indicator        */
    struct sqlname sqlname;             /* Variable name                    */
};

SQL_STRUCTURE  sqlda
{
    _SQLOLDCHAR    sqldaid[8];          /* Eye catcher = 'SQLDA   '         */
    /************************************************************************/
    /* The 7th byte has special meaning.  If it is a '2', this means there  */
    /* are twice as many sqlvars as there are host variables or columns.    */
    /* This is typically used when Large Objects (LOBs) or User Defined     */
    /* Types (UDFs) are present in the SQLDA.  The first N entries use the  */
    /* sqlvar structure and the second N entries use the sqlvar2 structure. */
    /************************************************************************/
    long           sqldabc;             /* SQLDA size in bytes=16+44*SQLN   */
    short          sqln;                /* Number of SQLVAR elements        */
    short          sqld;                /* # of columns or host vars.       */
    struct sqlvar  sqlvar[1];           /* first SQLVAR element             */
};

/* macro for allocating SQLDA */
#define   SQLDASIZE(n) (sizeof(struct sqlda) + \
                       ((long) n-1) * sizeof(struct sqlvar))

/****************************************************************************/
/* Because we may need to support 8 byte lengths in the future,             */
/* sql8bytelen is defined using 8 bytes.  Currently, however, we have only  */
/* four byte integers.                                                      */
/****************************************************************************/
union sql8bytelen
{
    long        reserve1[2];    /* reserved for future 8 byte lengths.      */
    long        sqllonglen;     /* this is what is currently used           */
};

/****************************************************************************/
/* The sqlvar2 structure maps the second "N" sqlvar entries.  The           */
/* second "N" entries are used to hold the length of LOB columns            */
/* and host variables.  The second "N" entries may also be used to          */
/* hold the SQLDATALEN field for LOB columns on a FETCH USING               */
/* DESCRIPTOR request.                                                      */
/*                                                                          */
/* To set or retrieve these fields, use the macros provided below.          */
/****************************************************************************/

SQL_STRUCTURE  sqlvar2          /* Variable Description                     */
{
   union sql8bytelen len;       /* Eight byte length. 4 bytes used now      */
   char *SQL_POINTER sqldatalen;/* Pointer to four (4) byte                 */
                                /* length buffer. This may be               */
                                /* used to hold the length for              */
                                /* lob data types.                          */
   struct sqldistinct_type sqldatatype_name;/*distinct type name.           */
};

/****************************************************************************/
/* Macros for using the sqlvar2 fields.                                     */
/****************************************************************************/

/****************************************************************************/
/* A '2' in the 7th byte of sqldaid indicates a doubled amount of sqlvars.  */
/****************************************************************************/
#define   SQLDOUBLED  '2'
#define   SQLSINGLED  ' '

/****************************************************************************/
/* GETSQLDOUBLED(daptr) will return 1 if the SQLDA pointed to by daptr      */
/* has been doubled, or 0 if it has not been doubled.                       */
/****************************************************************************/
#define GETSQLDOUBLED(daptr) (((daptr)->sqldaid[6] == ( char) SQLDOUBLED) ? \
    (1)         : \
    (0)           )

/****************************************************************************/
/* SETSQLDOUBLED(daptr, SQLDOUBLED) will make the 7th byte of sqldaid to    */
/* be a '2'.                                                                */
/* SETSQLDOUBLED(daptr, SQLSINGLED) will make the 7th byte of sqldaid to    */
/* be a ' '.                                                                */
/****************************************************************************/
#define SETSQLDOUBLED(daptr, newvalue) (((daptr)->sqldaid[6] = (newvalue)))

/****************************************************************************/
/* GETSQLDALONGLEN(daptr,n) will return the data length of the nth entry    */
/* in the sqlda pointed to by daptr. Use this only if the sqlda was         */
/* doubled and the nth SQLVAR entry has a LOB datatype.                     */
/****************************************************************************/
#define GETSQLDALONGLEN(daptr,n)    (    \
    (long) (((struct sqlvar2 *) &((daptr)->sqlvar[(n) + ((daptr)->sqld)]))->len.sqllonglen))

/****************************************************************************/
/* SETSQLDALONGLEN(daptr,n,len) will set the sqllonglen field of the        */
/* sqlda pointed to by daptr to len for the nth entry. Use this only if     */
/* the sqlda was doubled and the nth SQLVAR entry has a LOB datatype.       */
/****************************************************************************/
#define SETSQLDALONGLEN(daptr,n,length)  { \
    struct sqlvar2     *var2ptr; \
    var2ptr = (struct sqlvar2 *) &((daptr)->sqlvar[(n) + ((daptr)->sqld)]); \
    var2ptr->len.sqllonglen  =  (long ) (length); \
    }

/****************************************************************************/
/* GETSQLDALENPTR(daptr,n) will return a pointer to the data length for     */
/* the nth entry in the sqlda pointed to by daptr.  Unlike the inline       */
/* value (union sql8bytelen len), which is 8 bytes, the sqldatalen pointer  */
/* field returns a pointer to a long (4 byte) integer.                      */
/* If the SQLDATALEN pointer is zero, a NULL pointer will be returned.      */
/*                                                                          */
/* NOTE: Use this only if the sqlda has been doubled.                       */
/****************************************************************************/
#define GETSQLDALENPTR(daptr,n) (   \
    (((struct sqlvar2 *) &(daptr)->sqlvar[(n) + (daptr)->sqld])->sqldatalen == NULL) ? \
    ((long *) NULL ) : \
    ((long *) ((struct sqlvar2 *) &(daptr)->sqlvar[(n) + (daptr)->sqld])->sqldatalen ) )

/****************************************************************************/
/* SETSQLDALENPTR(daptr,n,ptr) will set a pointer to the data length for    */
/* the nth entry in the sqlda pointed to by daptr.                          */
/* Use this only if the sqlda has been doubled.                             */
/****************************************************************************/
#define SETSQLDALENPTR(daptr,n,ptr)  {  \
    struct sqlvar2 *var2ptr;    \
    var2ptr = (struct sqlvar2 *) &((daptr)->sqlvar[(n) + ((daptr)->sqld)]); \
    var2ptr->sqldatalen  = (char *) ptr; \
    }

#if (defined(DB2OS2) || defined(DB2NT) || defined(DB2WIN))
#pragma pack()
#elif (defined(DB2MAC))
#pragma align
#elif (defined(DB2HP) || defined(DB2SNI))

#elif (defined(DB2AIX) || defined(DB2SUN))
#pragma options align=reset
#endif

#endif /* SQLDASIZE */
