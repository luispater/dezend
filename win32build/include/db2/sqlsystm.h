/******************************************************************************
 *
 * Source File Name = SQLSYSTM.H
 *
 *
 * (C) COPYRIGHT International Business Machines Corp. 1993
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Function = Include File defining:
 *              Operating System Specific Information
 *
 * Operating System = NT 3.5
 *
 *****************************************************************************/

#ifndef  SQL_H_SQLSYSTM
   #define SQL_H_SQLSYSTM          /* Permit duplicate Includes */


#ifndef DB2NT
  #define DB2NT     1
#endif


#ifndef SQL_API_RC
 #define SQL_API_RC      int
 #define SQL_STRUCTURE   struct
 #define SQL_POINTER
 #define SQL_API_FN      __stdcall
 #define SQL_API_INTR    __stdcall
 #define PSQL_API_FN     __stdcall *
#endif

/******************************************************************************
**
** The SQLOLDCHAR macro may be used to maintain compatibility between
** version 1 applications and version 2 header files.  In version 1, many
** strings were declared as 'unsigned char'.  In keeping with the spirit
** of ANSI C, all character data, structure members and function
** parameters with string semantics have been changed to 'char' in version 2.
** This change may produce type conflicts with some compilers.  Adding
** -DSQLOLDCHAR to the compile command will cause the changed items to
** revert to their version 1 types.  Note that this should be used for
** compatibility purposes only.  New code should be written using plain
** 'char' where indicated in the documentation.
******************************************************************************/

#undef _SQLOLDCHAR
#ifdef SQLOLDCHAR
 #define _SQLOLDCHAR     unsigned char
#else
 #define _SQLOLDCHAR     char
#endif

#endif /* SQL_H_SQLSYSTM */
