/*
 * $Header: oci.h 15-dec-97.11:06:29 esoyleme Exp $
 */

/* Copyright (c) Oracle Corporation 1995, 1996, 1997, 1998. All Rights Reserved. */
 
/* NOTE:  See 'header_template.doc' in the 'doc' dve under the 'forms' 
      directory for the header file template that includes instructions. 
*/
 
/* 
   NAME 
     oci.h - V8 Oracle Call Interface public definitions

   DESCRIPTION 
     This file defines all the constants and structures required by a V8
     OCI programmer.

   RELATED DOCUMENTS 
     V8 OCI Functional Specification 
     V8 OCI Design Specification
     Oracle Call Interface Programmer's Guide Vol 1 and 2
 
   INSPECTION STATUS 
     Inspection date: 
     Inspection status: 
     Estimated increasing cost defects per page: 
     Rule sets: 
 
   ACCEPTANCE REVIEW STATUS 
     Review date: 
     Review status: 
     Reviewers: 
 
   PUBLIC FUNCTION(S) 
     None

   PRIVATE FUNCTION(S) 
     None
 
   EXAMPLES 
 
   NOTES 


   MODIFIED   (MM/DD/YY)
   ekhor       06/11/98 - WIN32COMMON: added #if defined(__cplusplus) to 
                          get correct ansi prototypes
   aroy        12/19/97 - obsolete OCIStmtBindByPos
   skmishra    01/29/98 - Add OCI_ATTR_PARSE_ERROR_OFFSET
   dchatter    01/08/98 - more comments
   esoyleme    12/15/97 - support failover callback retry
   jwijaya     10/21/97 - change OCILobOffset/Length from ubig_ora to ub4
   cxcheng     07/28/97 - fix compile with SLSHORTNAME
   schandra    06/25/97 - AQ OCI interface
   sgollapu    07/25/97 - Add OCI_ATTR_DESC_PUBLIC
   cxcheng     06/16/97 - add OCI_ATTR_TDO
   skotsovo    06/05/97 - add fntcodes for lob buffering subsystem
   esoyleme    05/13/97 - move failover callback prototype
   skmishra    05/06/97 - stdc compiler fixes
   skmishra    04/22/97 - Provide C++ compatibility
   lchidamb    04/19/97 - add OCI_ATTR_SESSLANG
   ramkrish    04/15/97 - Add OCI_LOB_BUFFER_(NO)FREE
   sgollapu    04/18/97 - Add OCI_ATTR_TABLESPACE
   skaluska    04/17/97 - Add OCI_ATTR_SUB_NAME
   schandra    04/10/97 - Use long OCI names
   aroy        03/27/97 - add OCI_DTYPE_FILE
   sgollapu    03/26/97 - Add OCI_OTYPEs
   skmishra    04/09/97 - Added constant OCI_ROWID_LEN
   dchatter    03/21/97 - add attr OCI_ATTR_IN_V8_MODE
   lchidamb    03/21/97 - add OCI_COMMIT_ON_SUCCESS execution mode
   skmishra    03/20/97 - Added OCI_ATTR_LOBEMPTY
   sgollapu    03/19/97 - Add OCI_ATTR_OVRLD_ID
   aroy        03/17/97 - add postprocessing callback
   sgollapu    03/15/97 - Add OCI_ATTR_PARAM
   cxcheng     02/07/97 - change OCI_PTYPE codes for type method for consistenc
   cxcheng     02/05/97 - add OCI_PTYPE_TYPE_RESULT
   cxcheng     02/04/97 - rename OCI_PTYPE constants to be more consistent
   cxcheng     02/03/97 - add OCI_ATTR, OCI_PTYPE contants for describe type
   esoyleme    01/23/97 - merge neerja callback
   sgollapu    12/30/96 - Remove OCI_DTYPE_SECURITY
   asurpur     12/26/96 - CHanging OCI_NO_AUTH to OCI_AUTH
   sgollapu    12/23/96 - Add more attrs to COL, ARG, and SEQ
   sgollapu    12/12/96 - Add OCI_DESCRIBE_ONLY
   slari       12/11/96 - change prototype of OCICallbackInBind
   nbhatt      12/05/96 - "callback"
   lchidamb    11/19/96 - handle subclassing
   sgollapu    11/09/96 - OCI_PATTR_*
   dchatter    11/04/96 - add attr OCI_ATTR_CHRCNT
   mluong      11/01/96 - test
   cxcheng     10/31/96 - add #defines for OCILobLength etc
   dchatter    10/31/96 - add lob read write call back fp defs
   dchatter    10/30/96 - more changes
   rhari       10/30/96 - Include ociextp.h at the very end
   lchidamb    10/22/96 - add fdo attribute for bind/server handle
   dchatter    10/22/96 - change attr defn for prefetch parameters & lobs/file
                          calls
   slari       10/21/96 - add OCI_ENV_NO_MUTEX
   rhari       10/25/96 - Include ociextp.h
   rxgovind    10/25/96 - add OCI_LOBMAXSIZE, remove OCI_FILE_READWRITE
   sgollapu    10/24/96 - Correct OCILogon and OCILogoff
   sgollapu    10/24/96 - Correct to OCILogon and OCILogoff
   sgollapu    10/21/96 - Add ocilon and ociloff
   skaluska    10/31/96 - Add OCI_PTYPE values
   sgollapu    10/17/96 - correct OCI_ATTR_SVCCTX to OCI_ATTR_SERVER
   rwessman    10/16/96 - Added security functions and fixed olint errors.
   sthakur     10/14/96 - add more COR attributes
   cxcheng     10/14/96 - re-enable LOB functions
   sgollapu    10/10/96 - Add ocibdp and ocibdn
   slari       10/07/96 - add back OCIRowid
   aroy        10/08/96 -  add typedef ocibfill for PRO*C
   mluong      10/11/96 - replace OCI_ATTR_CHARSET* with OCI_ATTR_CHARSET_*
   cxcheng     10/10/96 - temporarily take out #define for lob functions
   sgollapu    10/02/96 - Rename OCI functions and datatypes
   skotsovo    10/01/96 - move orl lob fnts to oci
   aroy        09/10/96 - fix merge errors
   aroy        08/19/96 - NCHAR support
   jboonleu    09/05/96 - add OCI attributes for object cache
   dchatter    08/20/96 - HTYPE ranges from 1-50; DTYPE from 50-255
   slari       08/06/96 - define OCI_DTYPE_ROWID
   sthakur     08/14/96 - complex object support
   schandra    06/17/96 - Convert XA to use new OCI
   abrik       08/15/96 - OCI_ATTR_HEAPALLOC added
   aroy        07/17/96 - terminology change: ocilobd => ocilobl
   aroy        07/03/96 - add lob typedefs for Pro*C
   slari       06/28/96 - add OCI_ATTR_STMT_TYPE
   lchidamb    06/26/96 - reorg #ifndef
   schandra    05/31/96 - attribute types for internal and external client name
   asurpur     05/30/96 - Changing the value of mode
   schandra    05/18/96 - OCI_TRANS_TWOPHASE -> 0x00000001 to 0x00100000
   slari       05/30/96 - add callback function prototypes
   jbellemo    05/23/96 - remove ociisc
   schandra    04/23/96 - loosely-coupled branches
   asurpur     05/15/96 - New mode for ocicpw
   aroy        04/24/96 - making ocihandles opaque
   slari       04/18/96 - add missing defines
   schandra    03/27/96 - V8OCI - add transaction related calls
   dchatter    04/01/96 - add OCI_FILE options
   dchatter    03/21/96 - add oci2lda conversion routines
   dchatter    03/07/96 - add OCI piece definition
   slari       03/12/96 - add describe attributes
   slari       03/12/96 - add OCI_OTYPE_QUERY
   aroy        02/28/96 - Add column attributes
   slari       02/09/96 - add OCI_OBJECT
   slari       02/07/96 - add OCI_HYTPE_DSC
   aroy        01/10/96 - adding function code defines...
   dchatter    01/03/96 - define OCI_NON_BLOCKING
   dchatter    01/02/96 - Add Any descriptor
   dchatter    01/02/96 - Add Select List descriptor
   dchatter    12/29/95 - V8 OCI definitions
   dchatter    12/29/95 - Creation

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ORATYPES 
#include <oratypes.h> 
#endif
 
#ifndef OCIDFN
#include <ocidfn.h>
#endif

#ifndef OCI_ORACLE
# define OCI_ORACLE


 
/*--------------------------------------------------------------------------- 
                     PUBLIC TYPES AND CONSTANTS 
  ---------------------------------------------------------------------------*/

/*-----------------------------Modes ----------------------------------------*/
#define OCI_DEFAULT  0x00 /* the default value for parameters and attributes */
#define OCI_THREADED 0x01      /* the application is in threaded environment */
#define OCI_OBJECT   0x02        /* the application is in object environment */
#define OCI_NON_BLOCKING 0x04              /* non blocking mode of operation */
#define OCI_ENV_NO_MUTEX 0x08 /* the environment handle will not be protected
				 by a mutex internally */

/*-----------------------------Handle Types----------------------------------*/
                                           /* handle types range from 1 - 49 */
#define OCI_HTYPE_FIRST 1                      /* start value of handle type */
#define OCI_HTYPE_ENV 1                                /* environment handle */
#define OCI_HTYPE_ERROR 2                                    /* error handle */
#define OCI_HTYPE_SVCCTX 3                                 /* service handle */
#define OCI_HTYPE_STMT 4                                 /* statement handle */
#define OCI_HTYPE_BIND 5                                      /* bind handle */
#define OCI_HTYPE_DEFINE 6                                  /* define handle */
#define OCI_HTYPE_DESCRIBE 7                              /* describe handle */
#define OCI_HTYPE_SERVER 8                                  /* server handle */
#define OCI_HTYPE_SESSION 9                         /* authentication handle */
#define OCI_HTYPE_TRANS 10                             /* transaction handle */
#define OCI_HTYPE_COMPLEXOBJECT 11        /* complex object retrieval handle */
#define OCI_HTYPE_SECURITY 12                             /* security handle */
#define OCI_HTYPE_LAST 12                     /* last value of a handle type */
/*---------------------------------------------------------------------------*/


/*-------------------------Descriptor Types----------------------------------*/
                                    /* descriptor values range from 50 - 255 */
#define OCI_DTYPE_FIRST 50                 /* start value of descriptor type */
#define OCI_DTYPE_LOB 50                                     /* lob  locator */
#define OCI_DTYPE_SNAP 51                             /* snapshot descriptor */
#define OCI_DTYPE_RSET 52                           /* result set descriptor */
#define OCI_DTYPE_PARAM 53  /* a parameter descriptor obtained from ocigparm */
#define OCI_DTYPE_ROWID  54                              /* rowid descriptor */
#define OCI_DTYPE_COMPLEXOBJECTCOMP  55
                                      /* complex object retrieval descriptor */
#define OCI_DTYPE_FILE 56                                /* File Lob locator */
#define	OCI_DTYPE_AQENQ_OPTIONS 57			  /* enqueue options */
#define	OCI_DTYPE_AQDEQ_OPTIONS 58			  /* dequeue options */
#define OCI_DTYPE_AQMSG_PROPERTIES 59		       /* message properties */
#define OCI_DTYPE_AQAGENT 60					 /* aq agent */
#define OCI_DTYPE_LAST 60                 /* last value of a descriptor type */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

/*-------------------------Object Ptr Types----------------------------------*/
#define OCI_OTYPE_NAME 1				      /* object name */
#define OCI_OTYPE_REF  2				       /* REF to TDO */
#define OCI_OTYPE_PTR  3				       /* PTR to TDO */
/*---------------------------------------------------------------------------*/

/*-----------------------------Attribute Types-------------------------------*/
#define OCI_ATTR_FNCODE  1                          /* the OCI function code */
#define OCI_ATTR_OBJECT   2 /* is the environment initialized in object mode */
#define OCI_ATTR_NONBLOCKING_MODE  3                    /* non blocking mode */
#define OCI_ATTR_SQLCODE  4                                  /* the SQL verb */
#define OCI_ATTR_ENV  5                            /* the environment handle */
#define OCI_ATTR_SERVER 6                               /* the server handle */
#define OCI_ATTR_SESSION 7                        /* the user session handle */
#define OCI_ATTR_TRANS   8                         /* the transaction handle */
#define OCI_ATTR_ROW_COUNT   9                  /* the rows processed so far */
#define OCI_ATTR_SQLFNCODE 10               /* the SQL verb of the statement */
#define OCI_ATTR_PREFETCH_ROWS  11    /* sets the number of rows to prefetch */
#define OCI_ATTR_NESTED_PREFETCH_ROWS 12 /* the prefetch rows of nested table*/
#define OCI_ATTR_PREFETCH_MEMORY 13         /* memory limit for rows fetched */
#define OCI_ATTR_NESTED_PREFETCH_MEMORY 14   /* memory limit for nested rows */
#define OCI_ATTR_CHAR_COUNT  15 
                    /* this specifies the bind and define size in characters */
#define OCI_ATTR_PDSCL   16                          /* packed decimal scale */
#define OCI_ATTR_PDFMT   17                         /* packed decimal format */
#define OCI_ATTR_PARAM_COUNT 18       /* number of column in the select list */
#define OCI_ATTR_ROWID   19                                     /* the rowid */
#define OCI_ATTR_CHARSET  20                      /* the character set value */
#define OCI_ATTR_NCHAR   21                                    /* NCHAR type */
#define OCI_ATTR_USERNAME 22                           /* username attribute */
#define OCI_ATTR_PASSWORD 23                           /* password attribute */
#define OCI_ATTR_STMT_TYPE   24                            /* statement type */
#define OCI_ATTR_INTERNAL_NAME   25             /* user friendly global name */
#define OCI_ATTR_EXTERNAL_NAME   26      /* the internal name for global txn */
#define OCI_ATTR_XID     27           /* XOPEN defined global transaction id */
#define OCI_ATTR_TRANS_LOCK 28                                            /* */
#define OCI_ATTR_TRANS_NAME 29    /* string to identify a global transaction */
#define OCI_ATTR_HEAPALLOC 30                /* memory allocated on the heap */
#define OCI_ATTR_CHARSET_ID 31                           /* Character Set ID */
#define OCI_ATTR_CHARSET_FORM 32                       /* Character Set Form */
#define OCI_ATTR_MAXDATA_SIZE 33       /* Maximumsize of data on the server  */
#define OCI_ATTR_CACHE_OPT_SIZE 34              /* object cache optimal size */
#define OCI_ATTR_CACHE_MAX_SIZE 35   /* object cache maximum size percentage */
#define OCI_ATTR_PINOPTION 36             /* object cache default pin option */
#define OCI_ATTR_ALLOC_DURATION 37
                                 /* object cache default allocation duration */
#define OCI_ATTR_PIN_DURATION 38        /* object cache default pin duration */
#define OCI_ATTR_FDO          39       /* Format Descriptor object attribute */
#define OCI_ATTR_POSTPROCESSING_CALLBACK 40
                                         /* Callback to process outbind data */
#define OCI_ATTR_POSTPROCESSING_CONTEXT 41
                                 /* Callback context to process outbind data */
#define OCI_ATTR_ROWS_RETURNED 42
               /* Number of rows returned in current iter - for Bind handles */
#define OCI_ATTR_FOCBK        43              /* Failover Callback attribute */
#define OCI_ATTR_IN_V8_MODE   44 /* is the server/service context in V8 mode */
#define OCI_ATTR_LOBEMPTY     45                              /* empty lob ? */
#define OCI_ATTR_SESSLANG     46                  /* session language handle */

/* ----------------------- AQ Attribute Types -------------------------------*/
/* ----------------------- Enqueue Options ----------------------------------*/
#define OCI_ATTR_VISIBILITY		47		       /* visibility */
#define OCI_ATTR_RELATIVE_MSGID		48  	      /* relative message id */
#define OCI_ATTR_SEQUENCE_DEVIATION	49	       /* sequence deviation */

/* ----------------------- Dequeue Options ----------------------------------*/
#define OCI_ATTR_CONSUMER_NAME		50		    /* consumer name */
#define OCI_ATTR_DEQ_MODE		51		     /* dequeue mode */
#define OCI_ATTR_NAVIGATION		52		       /* navigation */
#define OCI_ATTR_WAIT			53			     /* wait */
#define OCI_ATTR_DEQ_MSGID		54	       /* dequeue message id */

/* ----------------------- Message Properties -------------------------------*/
#define OCI_ATTR_PRIORITY		55			 /* priority */
#define OCI_ATTR_DELAY			56			    /* delay */
#define OCI_ATTR_EXPIRATION		57		       /* expiration */
#define OCI_ATTR_CORRELATION		58		   /* correlation id */
#define OCI_ATTR_ATTEMPTS		59		    /* # of attempts */
#define OCI_ATTR_RECIPIENT_LIST		60		   /* recipient list */
#define OCI_ATTR_EXCEPTION_QUEUE	61	     /* exception queue name */
#define OCI_ATTR_ENQ_TIME		62 /* enqueue time (only OCIAttrGet) */
#define OCI_ATTR_MSG_STATE		63/* message state (only OCIAttrGet) */

/* ----------------------- AQ Agent -----------------------------------------*/
#define OCI_ATTR_AGENT_NAME		64		       /* agent name */
#define OCI_ATTR_AGENT_ADDRESS		65		    /* agent address */
#define OCI_ATTR_AGENT_PROTOCOL		66		   /* agent protocol */

/*-------------------------Parameter Attribute Types-------------------------*/

#define OCI_ATTR_UNK              101                   /* unknown attribute */
#define OCI_ATTR_NUM_COLS         102                   /* number of columns */
#define OCI_ATTR_LIST_COLUMNS     103        /* parameter of the column list */
#define OCI_ATTR_RDBA             104           /* DBA of the segment header */
#define OCI_ATTR_CLUSTERED        105      /* whether the table is clustered */
#define OCI_ATTR_PARTITIONED      106    /* whether the table is partitioned */
#define OCI_ATTR_INDEX_ONLY       107     /* whether the table is index only */
#define OCI_ATTR_LIST_ARGUMENTS   108      /* parameter of the argument list */
#define OCI_ATTR_LIST_SUBPROGRAMS 109    /* parameter of the subprogram list */
#define OCI_ATTR_REF_TDO          110          /* REF to the type descriptor */
#define OCI_ATTR_LINK             111              /* the database link name */
#define OCI_ATTR_MIN              112                       /* minimum value */
#define OCI_ATTR_MAX              113                       /* maximum value */
#define OCI_ATTR_INCR             114                     /* increment value */
#define OCI_ATTR_CACHE            115   /* number of sequence numbers cached */
#define OCI_ATTR_ORDER            116     /* whether the sequence is ordered */
#define OCI_ATTR_HW_MARK          117                     /* high-water mark */
#define OCI_ATTR_TYPE_SCHEMA      118                  /* type's schema name */
#define OCI_ATTR_TIMESTAMP        119             /* timestamp of the object */
#define OCI_ATTR_NUM_ATTRS        120                /* number of sttributes */
#define OCI_ATTR_NUM_PARAMS       121                /* number of parameters */
#define OCI_ATTR_OBJID            122       /* object id for a table or view */
#define OCI_ATTR_PTYPE            123           /* type of info described by */
#define OCI_ATTR_PARAM            124                /* parameter descriptor */
#define OCI_ATTR_OVERLOAD_ID      125     /* overload ID for funcs and procs */
#define OCI_ATTR_TABLESPACE       126                    /* table name space */
#define OCI_ATTR_TDO              127                       /* TDO of a type */
#define OCI_ATTR_PARSE_ERROR_OFFSET        128         /* Parse Error offset */
/*-------------------------Credential Types----------------------------------*/
#define OCI_CRED_RDBMS    1                    /* database username/password */
#define OCI_CRED_EXT      2               /* externally provided credentials */
/*---------------------------------------------------------------------------*/

/*------------------------Error Return Values--------------------------------*/
#define OCI_SUCCESS 0                      /* maps to SQL_SUCCESS of SAG CLI */
#define OCI_SUCCESS_WITH_INFO 1             /* maps to SQL_SUCCESS_WITH_INFO */
#define OCI_NO_DATA 100                               /* maps to SQL_NO_DATA */
#define OCI_ERROR -1                                    /* maps to SQL_ERROR */
#define OCI_INVALID_HANDLE -2                  /* maps to SQL_INVALID_HANDLE */
#define OCI_NEED_DATA 99                            /* maps to SQL_NEED_DATA */
#define OCI_STILL_EXECUTING -3123                   /* OCI would block error */
#define OCI_CONTINUE -24200    /* Continue with the body of the OCI function */
/*---------------------------------------------------------------------------*/

/*------------------------Parsing Syntax Types-------------------------------*/
#define OCI_V7_SYNTAX 2                                       /* V7 language */
#define OCI_V8_SYNTAX 3                                       /* V8 language */
#define OCI_NTV_SYNTAX 1    /* Use what so ever is the native lang of server */
                     /* these values must match the values defined in kpul.h */
/*---------------------------------------------------------------------------*/

/*------------------------Scrollable Cursor Options--------------------------*/
#define OCI_FETCH_NEXT 0x02                                      /* next row */
#define OCI_FETCH_FIRST 0x04                  /* first row of the result set */
#define OCI_FETCH_LAST 0x08                /* the last row of the result set */
#define OCI_FETCH_PRIOR 0x10         /* the previous row relative to current */
#define OCI_FETCH_ABSOLUTE 0x20                /* absolute offset from first */
#define OCI_FETCH_RELATIVE 0x40                /* offset relative to current */
/*---------------------------------------------------------------------------*/

/*------------------------Bind and Define Options----------------------------*/
#define OCI_SB2_IND_PTR   0x01                                     /* unused */
#define OCI_DATA_AT_EXEC  0x02                       /* data at execute time */
#define OCI_DYNAMIC_FETCH 0x02                          /* fetch dynamically */
#define OCI_PIECEWISE     0x04                    /* piecewise DMLs or fetch */
/*---------------------------------------------------------------------------*/

/*------------------------Execution Modes------------------------------------*/
#define OCI_BATCH_MODE        0x01  /* batch the oci statement for execution */
#define OCI_EXACT_FETCH       0x02         /* fetch the exact rows specified */
#define OCI_KEEP_FETCH_STATE  0x04                                 /* unused */
#define OCI_SCROLLABLE_CURSOR 0x08                      /* cursor scrollable */
#define OCI_DESCRIBE_ONLY     0x10            /* only describe the statement */
#define OCI_COMMIT_ON_SUCCESS 0x20        /* commit, if successful execution */
/*---------------------------------------------------------------------------*/

/*------------------------Authentication Modes-------------------------------*/
#define OCI_MIGRATE     0x0001                    /* migratable auth context */
#define OCI_SYSDBA      0x0002                   /* for SYSDBA authorization */
#define OCI_SYSOPER     0x0004                  /* for SYSOPER authorization */
#define OCI_PRELIM_AUTH 0x0008              /* for preliminary authorization */
/*---------------------------------------------------------------------------*/

/*------------------------Piece Information----------------------------------*/
#define OCI_PARAM_IN 0x01                                    /* in parameter */
#define OCI_PARAM_OUT 0x02                                  /* out parameter */
/*---------------------------------------------------------------------------*/

/*------------------------ Transaction Start Flags --------------------------*/
/* NOTE: OCI_TRANS_JOIN and OCI_TRANS_NOMIGRATE not supported in 8.0.X       */
#define OCI_TRANS_NEW          0x00000001 /* starts a new transaction branch */
#define OCI_TRANS_JOIN         0x00000002    /* join an existing transaction */
#define OCI_TRANS_RESUME       0x00000004         /* resume this transaction */
#define OCI_TRANS_STARTMASK    0x000000ff

#define OCI_TRANS_READONLY     0x00000100   /* starts a readonly transaction */
#define OCI_TRANS_READWRITE    0x00000200 /* starts a read-write transaction */
#define OCI_TRANS_SERIALIZABLE 0x00000400
                                        /* starts a serializable transaction */
#define OCI_TRANS_ISOLMASK     0x0000ff00

#define OCI_TRANS_LOOSE        0x00010000        /* a loosely coupled branch */
#define OCI_TRANS_TIGHT        0x00020000        /* a tightly coupled branch */
#define OCI_TRANS_TYPEMASK     0x000f0000

#define OCI_TRANS_NOMIGRATE    0x00100000      /* non migratable transaction */

/*---------------------------------------------------------------------------*/

/*------------------------ Transaction End Flags ----------------------------*/
#define OCI_TRANS_TWOPHASE      0x01000000           /* use two phase commit */
/*---------------------------------------------------------------------------*/

/*------------------------- AQ Constants ------------------------------------
 * NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE
 * The following constants must match the PL/SQL dbms_aq constants
 * NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE
 */
/* ------------------------- Visibility flags -------------------------------*/
#define OCI_ENQ_IMMEDIATE	1   /* enqueue is an independent transaction */
#define OCI_ENQ_ON_COMMIT	2  /* enqueue is part of current transaction */

/* ----------------------- Dequeue mode flags -------------------------------*/
#define OCI_DEQ_BROWSE		1   /* read message without acquiring a lock */
#define OCI_DEQ_LOCKED		2   /* read and obtain write lock on message */
#define OCI_DEQ_REMOVE		3          /* read the message and delete it */

/* ----------------- Dequeue navigation flags -------------------------------*/
#define OCI_DEQ_FIRST_MSG	 1     /* get first message at head of queue */
#define OCI_DEQ_NEXT_MSG	 3         /* next message that is available */
#define OCI_DEQ_NEXT_TRANSACTION 2    /* get first message of next txn group */

/* --------------------- Message states -------------------------------------*/
#define OCI_MSG_WAITING		1 /* the message delay has not yet completed */
#define OCI_MSG_READY		0    /* the message is ready to be processed */
#define OCI_MSG_PROCESSED	2          /* the message has been processed */
#define OCI_MSG_EXPIRED		3    /* message has moved to exception queue */

/* --------------------- Sequence deviation ---------------------------------*/
#define OCI_ENQ_BEFORE		2  /* enqueue message before another message */
#define OCI_ENQ_TOP		3     /* enqueue message before all messages */

/* ------------------------- Visibility flags -------------------------------*/
#define OCI_DEQ_IMMEDIATE	1   /* dequeue is an independent transaction */
#define OCI_DEQ_ON_COMMIT	2  /* dequeue is part of current transaction */

/* ------------------------ Wait --------------------------------------------*/
#define OCI_DEQ_WAIT_FOREVER 	-1   /* wait forever if no message available */
#define OCI_DEQ_NO_WAIT	 	0  /* do not wait if no message is available */

/* ------------------------ Delay -------------------------------------------*/
#define OCI_MSG_NO_DELAY	0        /* message is available immediately */

/* ------------------------- Expiration -------------------------------------*/
#define OCI_MSG_NO_EXPIRATION -1                /* message will never expire */

/* -------------------------- END AQ Constants ----------------------------- */

/*-----------Object Types **** Not to be Used **** --------------------------*/
/* Deprecated */
#define OCI_OTYPE_UNK           0
#define OCI_OTYPE_TABLE         1
#define OCI_OTYPE_VIEW          2
#define OCI_OTYPE_SYN           3
#define OCI_OTYPE_PROC          4
#define OCI_OTYPE_FUNC          5
#define OCI_OTYPE_PKG           6
#define OCI_OTYPE_STMT          7
/*---------------------------------------------------------------------------*/

/*-----------------------Describe Handle Parameter Attributes ---------------*/
/* Attributes common to Columns and Stored Procs */
#define OCI_ATTR_DATA_SIZE      1                /* maximum size of the data */
#define OCI_ATTR_DATA_TYPE      2     /* the SQL type of the column/argument */
#define OCI_ATTR_DISP_SIZE      3                        /* the display size */
#define OCI_ATTR_NAME           4         /* the name of the column/argument */
#define OCI_ATTR_PRECISION      5                /* precision if number type */
#define OCI_ATTR_SCALE          6                    /* scale if number type */
#define OCI_ATTR_IS_NULL        7                            /* is it null ? */
#define OCI_ATTR_TYPE_NAME      8
  /* name of the named data type or a package name for package private types */
#define OCI_ATTR_SCHEMA_NAME    9             /* the schema name */
#define OCI_ATTR_SUB_NAME       10      /* type name if package private type */
#define OCI_ATTR_POSITION       11
                    /* relative position of col/arg in the list of cols/args */

/* complex object retrieval parameter attributes */
#define OCI_ATTR_COMPLEXOBJECTCOMP_TYPE		50 
#define OCI_ATTR_COMPLEXOBJECTCOMP_TYPE_LEVEL	51
#define OCI_ATTR_COMPLEXOBJECT_LEVEL		52
#define OCI_ATTR_COMPLEXOBJECT_COLL_OUTOFLINE   53

/* Only Columns */
#define OCI_ATTR_DISP_NAME      100                      /* the display name */

/*Only Stored Procs */
#define OCI_ATTR_OVERLOAD       210           /* is this position overloaded */
#define OCI_ATTR_LEVEL          211            /* level for structured types */
#define OCI_ATTR_HAS_DEFAULT    212                   /* has a default value */
#define OCI_ATTR_IOMODE         213                         /* in, out inout */
#define OCI_ATTR_RADIX          214                       /* returns a radix */
#define OCI_ATTR_NUM_ARGS       215             /* total number of arguments */

/* only named type attributes */
#define OCI_ATTR_TYPECODE                  216       /* object or collection */
#define OCI_ATTR_COLLECTION_TYPECODE       217     /* varray or nested table */
#define OCI_ATTR_VERSION                   218      /* user assigned version */
#define OCI_ATTR_IS_INCOMPLETE_TYPE        219 /* is this an incomplete type */
#define OCI_ATTR_IS_SYSTEM_TYPE            220              /* a system type */
#define OCI_ATTR_IS_PREDEFINED_TYPE        221          /* a predefined type */
#define OCI_ATTR_IS_TRANSIENT_TYPE         222           /* a transient type */
#define OCI_ATTR_IS_SYSTEM_GENERATED_TYPE  223      /* system generated type */
#define OCI_ATTR_HAS_NESTED_TABLE          224 /* contains nested table attr */
#define OCI_ATTR_HAS_LOB                   225        /* has a lob attribute */
#define OCI_ATTR_HAS_FILE                  226       /* has a file attribute */
#define OCI_ATTR_COLLECTION_ELEMENT        227 /* has a collection attribute */
#define OCI_ATTR_NUM_TYPE_ATTRS            228  /* number of attribute types */
#define OCI_ATTR_LIST_TYPE_ATTRS           229    /* list of type attributes */
#define OCI_ATTR_NUM_TYPE_METHODS          230     /* number of type methods */
#define OCI_ATTR_LIST_TYPE_METHODS         231       /* list of type methods */
#define OCI_ATTR_MAP_METHOD                232         /* map method of type */
#define OCI_ATTR_ORDER_METHOD              233       /* order method of type */

/* only collection element */
#define OCI_ATTR_NUM_ELEMS                 234         /* number of elements */

/* only type methods */
#define OCI_ATTR_ENCAPSULATION             235        /* encapsulation level */
#define OCI_ATTR_IS_SELFISH                236             /* method selfish */
#define OCI_ATTR_IS_VIRTUAL                237                    /* virtual */
#define OCI_ATTR_IS_INLINE                 238                     /* inline */
#define OCI_ATTR_IS_CONSTANT               239                   /* constant */
#define OCI_ATTR_HAS_RESULT                240                 /* has result */
#define OCI_ATTR_IS_CONSTRUCTOR            241                /* constructor */
#define OCI_ATTR_IS_DESTRUCTOR             242                 /* destructor */
#define OCI_ATTR_IS_OPERATOR               243                   /* operator */
#define OCI_ATTR_IS_MAP                    244               /* a map method */
#define OCI_ATTR_IS_ORDER                  245               /* order method */
#define OCI_ATTR_IS_RNDS                   246  /* read no data state method */
#define OCI_ATTR_IS_RNPS                   247      /* read no process state */
#define OCI_ATTR_IS_WNDS                   248 /* write no data state method */
#define OCI_ATTR_IS_WNPS                   249     /* write no process state */

/* describing public objects */
#define OCI_ATTR_DESC_PUBLIC               250              /* public object */
/*---------------------------------------------------------------------------*/

/*---------------------------OCIPasswordChange-------------------------------*/
#define OCI_AUTH         0x08        /* Change the password but do not login */


/*------------------------Other Constants------------------------------------*/
#define OCI_MAX_FNS   100                     /* max number of OCI Functions */
#define OCI_SQLSTATE_SIZE 5  
#define OCI_ERROR_MAXMSG_SIZE   1024         /* max size of an error message */
#define OCI_LOBMAXSIZE MINUB4MAXVAL                 /* maximum lob data size */
#define OCI_ROWID_LEN             23 
/*---------------------------------------------------------------------------*/

/*------------------------ Fail Over Events ---------------------------------*/
#define OCI_FO_END          0x00000001
#define OCI_FO_ABORT        0x00000002   
#define OCI_FO_REAUTH       0x00000004
#define OCI_FO_BEGIN        0x00000008 
#define OCI_FO_ERROR        0x00000010
/*---------------------------------------------------------------------------*/

/*------------------------- Fail Over Types ---------------------------------*/
#define OCI_FO_NONE           0x00000001
#define OCI_FO_SESSION        0x00000002
#define OCI_FO_SELECT         0x00000004
#define OCI_FO_TXNAL          0x00000008
/*---------------------------------------------------------------------------*/

/*-----------------------Function Codes--------------------------------------*/
#define OCI_FNCODE_INITIALIZE     1                         /* OCIInitialize */
#define OCI_FNCODE_HANDLEALLOC  2                          /* OCIHandleAlloc */
#define OCI_FNCODE_HANDLEFREE  3                            /* OCIHandleFree */
#define OCI_FNCODE_DESCRIPTORALLOC  4                  /* OCIDescriptorAlloc */
#define OCI_FNCODE_DESCRIPTORFREE  5                    /* OCIDescriptorFree */
#define OCI_FNCODE_ENVINIT   6                                 /* OCIEnvInit */
#define OCI_FNCODE_SERVERATTACH   7                       /* OCIServerAttach */
#define OCI_FNCODE_SERVERDETACH   8                       /* OCIServerDetach */
/* unused         9 */ 
#define OCI_FNCODE_SESSIONBEGIN  10                       /* OCISessionBegin */
#define OCI_FNCODE_SESSIONEND   11                          /* OCISessionEnd */
#define OCI_FNCODE_PASSWORDCHANGE   12                  /* OCIPasswordChange */
#define OCI_FNCODE_STMTPREPARE   13                        /* OCIStmtPrepare */
                                                      /* unused       14- 16 */
#define OCI_FNCODE_BINDDYNAMIC   17                        /* OCIBindDynamic */
#define OCI_FNCODE_BINDOBJECT  18                           /* OCIBindObject */
                                                                /* 19 unused */
#define OCI_FNCODE_BINDARRAYOFSTRUCT   20            /* OCIBindArrayOfStruct */
#define OCI_FNCODE_STMTEXECUTE  21                         /* OCIStmtExecute */
                                                             /* unused 22-24 */
#define OCI_FNCODE_DEFINEOBJECT  25                       /* OCIDefineObject */
#define OCI_FNCODE_DEFINEDYNAMIC   26                    /* OCIDefineDynamic */
#define OCI_FNCODE_DEFINEARRAYOFSTRUCT  27         /* OCIDefineArrayOfStruct */
#define OCI_FNCODE_STMTFETCH   28                            /* OCIStmtFetch */
#define OCI_FNCODE_STMTGETBIND   29                    /* OCIStmtGetBindInfo */
                                                            /* 30, 31 unused */
#define OCI_FNCODE_DESCRIBEANY  32                         /* OCIDescribeAny */
#define OCI_FNCODE_TRANSSTART  33                           /* OCITransStart */
#define OCI_FNCODE_TRANSDETACH  34                         /* OCITransDetach */
#define OCI_FNCODE_TRANSCOMMIT  35                         /* OCITransCommit */
                                                                /* 36 unused */
#define OCI_FNCODE_ERRORGET   37                              /* OCIErrorGet */
#define OCI_FNCODE_LOBOPENFILE  38                         /* OCILobFileOpen */
#define OCI_FNCODE_LOBCLOSEFILE  39                       /* OCILobFileClose */
                                             /* 40 was LOBCREATEFILE, unused */
                                         /* 41 was OCILobFileDelete, unused  */
#define OCI_FNCODE_LOBCOPY  42                                 /* OCILobCopy */
#define OCI_FNCODE_LOBAPPEND  43                             /* OCILobAppend */
#define OCI_FNCODE_LOBERASE  44                               /* OCILobErase */
#define OCI_FNCODE_LOBLENGTH  45                          /* OCILobGetLength */
#define OCI_FNCODE_LOBTRIM  46                                 /* OCILobTrim */
#define OCI_FNCODE_LOBREAD  47                                 /* OCILobRead */
#define OCI_FNCODE_LOBWRITE  48                               /* OCILobWrite */
                                                                /* 49 unused */
#define OCI_FNCODE_SVCCTXBREAK 50                                /* OCIBreak */
#define OCI_FNCODE_SERVERVERSION  51                     /* OCIServerVersion */
/* unused 52, 53 */
#define OCI_FNCODE_ATTRGET 54                                  /* OCIAttrGet */
#define OCI_FNCODE_ATTRSET 55                                  /* OCIAttrSet */
#define OCI_FNCODE_PARAMSET 56                                /* OCIParamSet */
#define OCI_FNCODE_PARAMGET 57                                /* OCIParamGet */
#define OCI_FNCODE_STMTGETPIECEINFO   58              /* OCIStmtGetPieceInfo */
#define OCI_FNCODE_LDATOSVCCTX 59                          /* OCILdaToSvcCtx */
                                                                /* 60 unused */
#define OCI_FNCODE_STMTSETPIECEINFO   61              /* OCIStmtSetPieceInfo */
#define OCI_FNCODE_TRANSFORGET 62                          /* OCITransForget */
#define OCI_FNCODE_TRANSPREPARE 63                        /* OCITransPrepare */
#define OCI_FNCODE_TRANSROLLBACK  64                     /* OCITransRollback */
#define OCI_FNCODE_DEFINEBYPOS 65                          /* OCIDefineByPos */
#define OCI_FNCODE_BINDBYPOS 66                              /* OCIBindByPos */
#define OCI_FNCODE_BINDBYNAME 67                            /* OCIBindByName */
#define OCI_FNCODE_LOBASSIGN  68                             /* OCILobAssign */
#define OCI_FNCODE_LOBISEQUAL  69                           /* OCILobIsEqual */
#define OCI_FNCODE_LOBISINIT  70                      /* OCILobLocatorIsInit */
/* 71 was lob locator size in beta2 */
#define OCI_FNCODE_LOBENABLEBUFFERING  71           /* OCILobEnableBuffering */
#define OCI_FNCODE_LOBCHARSETID  72                       /* OCILobCharSetID */
#define OCI_FNCODE_LOBCHARSETFORM  73                   /* OCILobCharSetForm */
#define OCI_FNCODE_LOBFILESETNAME  74                   /* OCILobFileSetName */
#define OCI_FNCODE_LOBFILEGETNAME  75                   /* OCILobFileGetName */
#define OCI_FNCODE_LOGON 76                                      /* OCILogon */
#define OCI_FNCODE_LOGOFF 77                                    /* OCILogoff */
#define OCI_FNCODE_LOBDISABLEBUFFERING 78          /* OCILobDisableBuffering */
#define OCI_FNCODE_LOBFLUSHBUFFER 79                    /* OCILobFlushBuffer */
#define OCI_FNCODE_LOBLOADFROMFILE 80                  /* OCILobLoadFromFile */


/*---------------------------------------------------------------------------*/

/*-----------------------Handle Definitions----------------------------------*/
typedef struct OCIEnv           OCIEnv;            /* OCI environment handle */
typedef struct OCIError         OCIError;                /* OCI error handle */
typedef struct OCISvcCtx        OCISvcCtx;             /* OCI service handle */
typedef struct OCIStmt          OCIStmt;             /* OCI statement handle */
typedef struct OCIBind          OCIBind;                  /* OCI bind handle */
typedef struct OCIDefine        OCIDefine;              /* OCI Define handle */
typedef struct OCIDescribe      OCIDescribe;          /* OCI Describe handle */
typedef struct OCIServer        OCIServer;              /* OCI Server handle */
typedef struct OCISession       OCISession;     /* OCI Authentication handle */
typedef struct OCIComplexObject OCIComplexObject;          /* OCI COR handle */
typedef struct OCITrans         OCITrans;          /* OCI Transaction handle */
typedef struct OCISecurity      OCISecurity;          /* OCI Security handle */

/*-----------------------Descriptor Definitions------------------------------*/
typedef struct OCISnapshot      OCISnapshot;      /* OCI snapshot descriptor */
typedef struct OCIResult        OCIResult;      /* OCI Result Set Descriptor */
typedef struct OCILobLocator    OCILobLocator; /* OCI Lob Locator descriptor */
typedef struct OCIParam         OCIParam;        /* OCI PARameter descriptor */
typedef struct OCIComplexObjectComp OCIComplexObjectComp;
                                                       /* OCI COR descriptor */
typedef struct OCIRowid OCIRowid;                      /* OCI ROWID descriptor */

/*-------------------------- AQ Descriptors ---------------------------------*/
typedef struct OCIAQEnqOptions    OCIAQEnqOptions; /* AQ Enqueue Options hdl */
typedef struct OCIAQDeqOptions    OCIAQDeqOptions; /* AQ Dequeue Options hdl */
typedef struct OCIAQMsgProperties OCIAQMsgProperties;  /* AQ Mesg Properties */
typedef struct OCIAQAgent	  OCIAQAgent;	      /* AQ Agent descriptor */
/*---------------------------------------------------------------------------*/
 
/* Lob typedefs for Pro*C */
typedef struct OCILobLocator OCIClobLocator;    /* OCI Character LOB Locator */
typedef struct OCILobLocator OCIBlobLocator;       /* OCI Binary LOB Locator */
typedef struct OCILobLocator OCIBFileLocator; /* OCI Binary LOB File Locator */
/*---------------------------------------------------------------------------*/


/*------------------------ Lob-specific Definitions -------------------------*/

/*
 * ociloff - OCI Lob OFFset
 *
 * The offset in the lob data.  The offset is specified in terms of bytes for
 * BLOBs and BFILes.  Character offsets are used for CLOBs, NCLOBs.
 * The maximum size of internal lob data is 4 gigabytes.  FILE LOB 
 * size is limited by the operating system.
 */
typedef ub4 OCILobOffset;

/*
 * ocillen - OCI Lob LENgth (of lob data)
 *
 * Specifies the length of lob data in bytes for BLOBs and BFILes and in 
 * characters for CLOBs, NCLOBs.  The maximum length of internal lob
 * data is 4 gigabytes.  The length of FILE LOBs is limited only by the
 * operating system.
 */
typedef ub4 OCILobLength;
/*
 * ocilmo - OCI Lob open MOdes
 *
 * The mode specifies the planned operations that will be performed on the
 * FILE lob data.  The FILE lob can be opened in read-only mode only.
 * 
 * In the future, we may include read/write, append and truncate modes.  Append
 * is equivalent to read/write mode except that the FILE is positioned for
 * writing to the end.  Truncate is equivalent to read/write mode except that
 * the FILE LOB data is first truncated to a length of 0 before use.
 */
enum OCILobMode
{
  OCI_LOBMODE_READONLY = 1                                      /* read-only */
};
typedef enum OCILobMode OCILobMode;

/*---------------------------------------------------------------------------*/


/*----------------------------Piece Definitions------------------------------*/

/* if ocidef.h is being included in the app, ocidef.h should precede oci.h */

/* 
 * since clients may  use oci.h, ocidef.h and ocidfn.h the following defines
 * need to be guarded, usually internal clients
 */

#ifndef OCI_FLAGS
#define OCI_FLAGS
#define OCI_ONE_PIECE 0                                         /* one piece */
#define OCI_FIRST_PIECE 1                                 /* the first piece */
#define OCI_NEXT_PIECE 2                          /* the next of many pieces */
#define OCI_LAST_PIECE 3                                   /* the last piece */
#endif
/*---------------------------------------------------------------------------*/

/*--------------------------- FILE open modes -------------------------------*/
#define OCI_FILE_READONLY 1             /* readonly mode open for FILE types */
/*---------------------------------------------------------------------------*/

/*----------------------- LOB Buffering Flush Flags -------------------------*/
#define OCI_LOB_BUFFER_FREE   1 
#define OCI_LOB_BUFFER_NOFREE 2
/*---------------------------------------------------------------------------*/

/*--------------------------- OCI Statement Types ---------------------------*/

#define  OCI_STMT_SELECT  1                              /* select statement */
#define  OCI_STMT_UPDATE  2                              /* update statement */
#define  OCI_STMT_DELETE  3                              /* delete statement */
#define  OCI_STMT_INSERT  4                              /* Insert Statement */
#define  OCI_STMT_CREATE  5                              /* create statement */
#define  OCI_STMT_DROP    6                                /* drop statement */
#define  OCI_STMT_ALTER   7                               /* alter statement */
#define  OCI_STMT_BEGIN   8                   /* begin ... (pl/sql statement)*/
#define  OCI_STMT_DECLARE 9                /* declare .. (pl/sql statement ) */
/*---------------------------------------------------------------------------*/

/*--------------------------- OCI Parameter Types ---------------------------*/
#define OCI_PTYPE_UNK           0                               /* unknown   */
#define OCI_PTYPE_TABLE		1                               /* table     */
#define OCI_PTYPE_VIEW		2                               /* view      */
#define OCI_PTYPE_PROC		3                               /* procedure */
#define OCI_PTYPE_FUNC		4                               /* function  */
#define OCI_PTYPE_PKG		5                               /* package   */
#define OCI_PTYPE_TYPE          6                       /* user-defined type */
#define OCI_PTYPE_SYN		7                               /* synonym   */
#define OCI_PTYPE_SEQ		8                               /* sequence  */
#define OCI_PTYPE_COL		9                               /* column    */
#define OCI_PTYPE_ARG		10                              /* argument  */
#define OCI_PTYPE_LIST		11                              /* list      */
#define OCI_PTYPE_TYPE_ATTR     12          /* user-defined type's attribute */
#define OCI_PTYPE_TYPE_COLL     13              /* collection type's element */
#define OCI_PTYPE_TYPE_METHOD   14             /* user-defined type's method */
#define OCI_PTYPE_TYPE_ARG      15    /* user-defined type method's argument */
#define OCI_PTYPE_TYPE_RESULT   16      /* user-defined type method's result */
/*---------------------------------------------------------------------------*/

/*----------------------------- OCI List Types ------------------------------*/
#define OCI_LTYPE_UNK           0                               /* unknown   */
#define OCI_LTYPE_COLUMN        1                             /* column list */
#define OCI_LTYPE_ARG_PROC      2                 /* procedure argument list */
#define OCI_LTYPE_ARG_FUNC      3                  /* function argument list */
#define OCI_LTYPE_SUBPRG        4                         /* subprogram list */
#define OCI_LTYPE_TYPE_ATTR     5                          /* type attribute */
#define OCI_LTYPE_TYPE_METHOD   6                             /* type method */
#define OCI_LTYPE_TYPE_ARG_PROC 7    /* type method w/o result argument list */
#define OCI_LTYPE_TYPE_ARG_FUNC 8      /* type method w/result argument list */
/*---------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------- 
                     PRIVATE TYPES AND CONSTANTS 
  ---------------------------------------------------------------------------*/
 
/* None */

/*--------------------------------------------------------------------------- 
                           PUBLIC FUNCTIONS 
  ---------------------------------------------------------------------------*/

/* see ociap.h or ocikp.h */
 
/*--------------------------------------------------------------------------- 
                          PRIVATE FUNCTIONS 
  ---------------------------------------------------------------------------*/

/* None */

/*--------------------------------------------------------------------------- 
 Short names provided for platforms which do not allow extended symbolic names 
  ---------------------------------------------------------------------------*/

#ifdef SLSHORTNAME
/* Translation of the long function/type names to short names for IBM only */
/* maybe lint will use this too */
#define OCISessionEnd              ocitac
#define OCIResultSetToStmt         ocirs2sh
#define OCISessionBegin            ociauth
#define OCIServerAttach            ociatch
#define OCIDescriptorAlloc         ocigdesc
#define OCIServerDetach            ocidtch
#define OCIDescriptorFree          ocifdesc
#define OCIServerVersion           ocivers
#define OCIDescribeAny             ocidsca
#define OCIBindDynamic             ocibda
#define OCIBindByName              ocibdn
#define OCIBindByPos               ocibdp
#define OCIErrorGet                ocigdr
#define OCIBindArrayOfStruct       ocibsa
#define OCIEnvInit                 ociinit
#define OCIBindObject              ocibndt
#define OCIHandleAlloc             ocighndl
#define OCIStmtBindByPos           ocibndp
#define OCIHandleFree              ocifhndl
#define OCIStmtBindByName          ocibndn
#define OCIAttrGet                 ocigattr
#define OCIDefineByPos             ocidfne
#define OCIAttrSet                 ocisattr
#define OCIDefineDynamic           ociddf
#define OCILdaToSvcCtx             ocild2sv
#define OCIDefineArrayOfStruct     ocidarr
#define OCIInitialize              ocipi
#define OCIDefineObject            ocidndt
#define OCIStmtExecute             ociexec
#define OCILobAppend               ocilfap
#define OCILobOpenFile             ocifopn
#define OCILobCloseFile            ocifcls
#define OCILobLocator              ocilobd
#define OCILobCopy                 ocilfcp
#define OCILobFileCreate           ocifcrt
#define OCILobFileDelete           ocifdel
#define OCILobGetLength            ocilfln
#define OCILobWrite                ocilfwr
#define OCILobRead                 ocilfrd
#define OCILobErase                ocilfer
#define OCILobTrim                 ocilftr

#define OCIStmtFetch               ocifch
#define OCIStmtGetBindInfo         ocigbp
#define OCIStmtGetPieceInfo        ocigpi
#define OCIStmtPrepare             ocireq
#define OCIStmtSetPieceInfo        ocispi
#define OCISvcCtxToLda             ocisv2ld
#define OCITransCommit             ocitxcm
#define OCITransDetach             ocitxdt
#define OCITransForget             ocitxfgt
#define OCITransPrepare            ocitxpre
#define OCITransRollback           ocitxrl
#define OCIPasswordChange          ocicpw
#define OCITransStart              ocitxst
#define OCIBreak                   ocibreak
#define OCIParamGet                ocigparm
#define OCIParamSet                ocisparm

#define OCISecurityOpenWallet           ocizwOpenWallet
#define OCISecurityCloseWallet          ocizwCloseWallet
#define OCISecurityCreateWallet         ocizwCreateWallet
#define OCISecurityDestroyWallet        ocizwDestroyWallet
#define OCISecurityStorePersona         ocizeStorePersona
#define OCISecurityOpenPersona          ocizeOpenPersona
#define OCISecurityClosePersona         ocizeClosePersona
#define OCISecurityRemovePersona        ocizeRemovePersona
#define OCISecurityCreatePersona        ocizeCreatePersona
#define OCISecuritySetProtection        ocizeSetProtection
#define OCISecurityGetProtection        ocizeGetProtection
#define OCISecurityRemoveIdentity       ociziRemoveIdentity
#define OCISecurityCreateIdentity       ociziCreateIdentity
#define OCISecurityAbortIdentity        ociziAbortIdentity
#define OCISecurityFreeIdentity         ociziFreeIdentity
#define OCISecurityStoreTrustedIdentity ociziStoreTrustedIdentity
#define OCISecuritySign                 ocizSign
#define OCISecuritySignExpansion        ocizxSignExpansion
#define OCISecurityVerify               ocizVerify
#define OCISecurityValidate             ocizValidate
#define OCISecuritySignDetached         ocizsd_SignDetached
#define OCISecuritySignDetExpansion     ocizxsd_SignDetachedExpansion
#define OCISecurityVerifyDetached       ocizved_VerifyDetached
#define OCISecurity_PKEncrypt           ocizkec_PKEncrypt
#define OCISecurityPKEncryptExpansion   ocizxkec_PKEncryptExpansion
#define OCISecurityPKDecrypt            ocizkdc_PKDecrypt
#define OCISecurityEncrypt              ocizEncrypt
#define OCISecurityEncryptExpansion     ocizxEncryptExpansion
#define OCISecurityDecrypt              ocizDecrypt
#define OCISecurityEnvelope             ocizEnvelope
#define OCISecurityDeEnvelope           ocizDeEnvelope
#define OCISecurityKeyedHash            ocizKeyedHash
#define OCISecurityKeyedHashExpansion   ocizxKeyedHashExpansion
#define OCISecurityHash                 ocizHash
#define OCISecurityHashExpansion        ocizxHashExpansion
#define OCISecuritySeedRandom           ocizSeedRandom
#define OCISecurityRandomBytes          ocizrb_RandomBytes
#define OCISecurityRandomNumber         ocizrn_RandomNumber
#define OCISecurityInitBlock            ocizibInitBlock
#define OCISecurityReuseBlock           ocizrbReuseBlock
#define OCISecurityPurgeBlock           ocizpbPurgeBlock
#define OCISecuritySetBlock             ocizsbSetBlock
#define OCISecurityGetIdentity          ocizgi_GetIdentity

/* Translation between the old and new datatypes */

#define OCISession                 ociusrh
#define OCIBind                    ocibndh
#define OCIDescribe                ocidsch
#define OCIDefine                  ocidfnh
#define OCIEnv                     ocienvh
#define OCIError                   ocierrh

#define OCILob                     ocilobd
#define OCILobLength               ocillen
#define OCILobMode                 ocilmo
#define OCILobOffset               ociloff

#define OCILobLocator              ocilobd
#define OCIBlobLocator		   ociblobl
#define OCIClobLocator		   ociclobl
#define OCIBFileLocator            ocibfilel

#define OCIParam                   ocipard
#define OCIResult                  ocirstd
#define OCISnapshot                ocisnad
#define OCIServer                  ocisrvh
#define OCIStmt                    ocistmh
#define OCISvcCtx                  ocisvch
#define OCITrans                   ocitxnh
#define OCICallbackInBind          ocibicfp
#define OCICallbackOutBind         ocibocfp
#define OCICallbackDefine          ocidcfp
#define OCICallbackLobRead         ocilrfp
#define OCICallbackLobWrite        ocilwfp
#define OCISecurity                ociossh
#define OCIComplexObject           ocicorh
#define OCIComplexObjectComp       ocicord
#define OCIRowid                   ociridd

#endif /* ifdef SLSHORTNAME */
 
#endif                                              /* OCI_ORACLE */


/* more includes */
#ifndef ORO_ORACLE
#include <oro.h>
#endif

#ifndef ORI_ORACLE
#include <ori.h>
#endif

#ifndef ORL_ORACLE
#include <orl.h>
#endif

#ifndef ORT_ORACLE
#include <ort.h>
#endif

#ifndef OCIEXTP_ORACLE
#include <ociextp.h>
#endif

#if defined(__STDC__) || defined(__cplusplus)
#include <ociapr.h>
#include <ociap.h>
#else
#include <ocikpr.h>
#include <ocikp.h>
#endif

#ifndef OCIEXTP_ORACLE
#include <ociextp.h>
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

