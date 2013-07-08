/*
 * $Header: ociap.h 19-aug-97.14:17:58 tanguyen Exp $
 */

/* Copyright (c) Oracle Corporation 1996, 1997, 1998. All Rights Reserved. */ 
 
/* NOTE:  See 'header_template.doc' in the 'doc' dve under the 'forms' 
      directory for the header file template that includes instructions. 
*/
 
/* 
   NAME 
     ociap.h - Oracle Call Interface - Ansi Prototypes

   DESCRIPTION 
     defines all the OCI entry points with ANSI conformance. If you are adding
     new functions/comments here, please make sure the K&R prototypes
     comments are added in ocikp.h.

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

     OCIAQDeq() 
     OCIAQEnq() 
     OCIAttrGet() 
     OCIAttrSet() 
     OCIBindArrayOfStruct() 
     OCIBindByName() 
     OCIBindByPos() 
     OCIBindDynamic() 
     OCIBindObject() 
     OCIBreak() 
     OCIDefineArrayOfStruct() 
     OCIDefineByPos() 
     OCIDefineDynamic() 
     OCIDefineObject() 
     OCIDescribeAny() 
     OCIDescriptorAlloc() 
     OCIDescriptorFree() 
     OCIEnvInit() 
     OCIErrorGet() 
     OCIHandleAlloc() 
     OCIHandleFree() 
     OCIInitialize() 
     OCILdaToSvcCtx() 
     OCILobAppend() 
     OCILobAssign() 
     OCILobCharSetForm() 
     OCILobCharSetId() 
     OCILobCopy() 
     OCILobDisableBuffering() 
     OCILobEnableBuffering() 
     OCILobErase() 
     OCILobFileClose() 
     OCILobFileCloseAll() 
     OCILobFileExists() 
     OCILobFileGetName() 
     OCILobFileIsOpen() 
     OCILobFileOpen() 
     OCILobFileSetName() 
     OCILobFlushBuffer() 
     OCILobGetLength() 
     OCILobIsEqual() 
     OCILobLoadFromFile() 
     OCILobLocatorIsInit() 
     OCILobRead() 
     OCILobTrim() 
     OCILobWrite() 
     OCILogoff() 
     OCILogon() 
     OCIParamGet() 
     OCIParamSet() 
     OCIPasswordChange() 
     OCIServerAttach() 
     OCIServerDetach() 
     OCIServerVersion() 
     OCISessionBegin() 
     OCISessionEnd() 
     OCIStmtExecute() 
     OCIStmtFetch() 
     OCIStmtGetBindInfo() 
     OCIStmtGetPieceInfo() 
     OCIStmtPrepare() 
     OCIStmtSetPieceInfo() 
     OCISvcCtxToLda() 
     OCITransCommit() 
     OCITransDetach() 
     OCITransForget() 
     OCITransPrepare() 
     OCITransRollback() 
     OCITransStart() 

   PRIVATE FUNCTION(S)
    None.

   EXAMPLES

   NOTES
     examples in this file could be in K&R manner, since they have been 
     duplicated from ocikp.h, and the examples are for the sake of illustration

   MODIFIED   (MM/DD/YY)
   dsaha       04/15/98 - OCI Non Blocking
   dchatter    01/09/98 - update comments
   tanguyen    08/19/97 -
   cxcheng     07/30/97 - replace OCISvcCtx with OCISvcCtx
   schandra    06/25/97 - AQ OCI interface
   bnainani    07/21/97 - add prototypes for Oracle XA extensions
   esoyleme    05/13/97 - move failover callback prototype
   skmishra    05/06/97 - stdc compiler fixes
   skmishra    04/24/97 - C++ Compatibility changes
   skotsovo    04/21/97 - make lob parameter names consistent
   rwhitman    04/16/97 - Fix LOB prototypes - Olint OCI 8.0.3
   ramkrish    04/15/97 - Add free flag to OCILobFlushBuffer
   dchatter    04/10/97 - add nzt.h inclusion
   cxcheng     04/09/97 - change objnamp from CONST text* to dvoid*
   cxcheng     04/08/97 - fix prototype of OCIDescribeAny()
   skotsovo    03/31/97 - remove OCILobLocatorSize
   skotsovo    03/27/97 - add OCILobLoadFromFile
   bcchang     02/18/97 - Fix syntax error
   dchatter    01/13/97 - fix comments on LOB calls
   aroy        01/10/97 - remove ocilobfilecreate delete
   sgollapu    12/27/96 - Correct OCILogon prototype
   dchatter    01/04/97 - comments to describe the functions
   sgollapu    11/25/96 - Change OCILobFileIsExistent
   schandra    11/18/96 - Remove xa.h include
   sgollapu    11/09/96 - Change prototype of OCIDescribeAny
   dchatter    10/31/96 - delete CONST from lob write cb fn
   dchatter    10/30/96 - more changes
   dchatter    10/26/96 - lob/file long name corrections
   slari       10/16/96 - delete unused calls
   rwessman    10/29/96 - Fixed OCISecurityGetIdentity prototype
   bcchang     10/25/96 - Fix syntax error
   sgollapu    10/22/96 - Add OCILogon and OCILogoff
   rwessman    10/16/96 - Added cryptographic and digital signature functions
   sgollapu    10/10/96 - Add ocibdp and ocibdn
   rxgovind    10/07/96 - add oci file calls
   skotsovo    10/01/96 - move orl lob fnts to oci
   skotsovo    09/20/96 - in OCILobGetLength(), remove the 'isnull' parameter.
   aroy        08/29/96 - change prototype for Nchar Lob support
   dchatter    08/21/96 - OCIResultSetToStmt prototype change
   sthakur     08/14/96 - add OCIParamSet
   schandra    07/26/96 - TX OCI return values - sb4->sword
   aroy        07/17/96 - terminology change: OCILobLocator => OCILobLocator
   dchatter    07/01/96 - create ANSI prototypes
   dchatter    07/01/96 - Creation

*/

 
#ifndef OCIAP_ORACLE
# define OCIAP_ORACLE

# ifndef ORATYPES 
#  include <oratypes.h> 
# endif 
 
#ifndef OCIDFN
#include <ocidfn.h>
#endif

#ifndef NZT_ORACLE
#include <nzt.h>
#endif /* NZT_ORACLE */
 
#ifndef OCI_ORACLE
#include <oci.h>
#endif

#ifndef ORT_ORACLE
#include <ort.h>
#endif

/*---------------------------------------------------------------------------
                     PUBLIC TYPES AND CONSTANTS
  ---------------------------------------------------------------------------*/

/* defined in  oci.h */

/*---------------------------------------------------------------------------
                     PRIVATE TYPES AND CONSTANTS
  ---------------------------------------------------------------------------*/
                                                                     
/* none */

/*---------------------------------------------------------------------------
                           PUBLIC FUNCTIONS
  ---------------------------------------------------------------------------*/

/*****************************************************************************
                              DESCRIPTION
******************************************************************************
Note: the descriptions of the functions are alphabetically arranged. Please 
maintain the arrangement when adding a new function description. The actual 
prototypes are below this comment section and do not follow any alphabetical 
ordering. All references to pages, appendixes and sections are to the OCI 
Programmer's Guide Vol 1 and 2.

-------------------------------OCIAQDeq---------------------------------------

OCIAQDeq()


NAME
OCI Advanced Queuing DEQueue

PURPOSE
This call is used for an advanced queueing dequeue. 

SYNTAX
sword OCIAQDeq ( OCISvcCtx           *svch,
                 OCIError            *errh,
                 text                *queue_name,
                 OCIAQDeqOptions     *dequeue_options,
                 OCIAQMsgProperties  *message_properties,
                 OCIType             *payload_tdo,
                 dvoid               **payload,
                 dvoid               **payload_ind,
                 OCIRaw              **msgid,
                 ub4                 flags );

PARAMETERS
svch (IN)
OCI service context. 

errh (IN)
An error handle which can be passed to OCIErrorGet() for diagnostic 
information in the event of an error. 

queue_name (IN)
The target queue for the dequeue operation. 

dequeue_options (IN)
The options for the dequeue operation; stored in an OCIAQDeqOptions descriptor.
 

message_properties (OUT)
The message properties for the message; stored in an OCIAQMsgProperties 
descriptor. 

payload_tdo (IN)
The TDO (type descriptor object) of an object type. For a raw queue, this 
parameter should point to the TDO of SYS.RAW. 

payload (IN/OUT)
A pointer to a pointer to a program variable buffer that is an instance of an 
object type. For a raw queue, this parameter should point to an instance of
OCIRaw. 
Memory for the payload is dynamically allocated in the object cache. The 
application can optionally call OCIObjectFree() to deallocate the payload 
instance when it is no longer needed. If the pointer to the program variable 
buffer ( *payload) is passed as NULL, the buffer is implicitly allocated in 
the cache. The application may choose to pass NULL for payload the first time 
OCIAQDeq() is called, and let the OCI allocate the memory for the payload. It 
can then use a pointer to that previously allocated memory in subsequent calls
to OCIAQDeq(). 
The OCI provides functions which allow the user to set attributes of the 
payload, such as its text. For information about setting these attributes, 
refer to "Manipulating Object Attributes" on page 8-13. 

payload_ind (IN/OUT)
A pointer to a pointer to the program variable buffer containing the parallel 
indicator structure for the object type. 
The memory allocation rules for payload_ind are the same as those for payload,
above. 

msgid (OUT)
The message ID. 

flags (IN)
Not currently used; pass as OCI_DEFAULT. 

COMMENTS
This function is used to perform an Advanced Queueing dequeue operation using 
the OCI. Users must have the aq_user_role or privileges to execute the 
dbms_aq package in order to use this call. 

The OCI environment must be initialized in object mode (using 
OCIInitialize()) to use this call. 

For more information about OCI and Advanced Queueing, refer to "OCI and 
Advanced Queueing" on page 7-40. 

For additional information about Advanced Queueing, refer to Oracle8 
Application Developer's Guide. 

To obtain a TDO for the payload, use OCITypeByName(), or OCITypeByRef(). 

EXAMPLES
For examples demonstrating the use of OCIAQDeq(), refer to the description of 
OCIAQEnq() on page 13-11. 

RELATED FUNCTIONS
OCIAQEnq(), OCIInitialize() 



-------------------------------OCIAQEnq---------------------------------------

OCIAQEnq()

NAME
OCI Advanced Queuing ENQueue

PURPOSE

This call is used for an advanced queueing enqueue. 

SYNTAX

sword OCIAQEnq ( OCISvcCtx           *svch,
                 OCIError            *errh,
                 text                *queue_name,
                 OCIAQEnqOptions     *enqueue_options,
                 OCIAQMsgProperties  *message_properties,
                 OCIType             *payload_tdo,
                 dvoid               **payload,
                 dvoid               **payload_ind,
                 OCIRaw              **msgid,
                 ub4                 flags );

PARAMETERS

svch (IN)

OCI service context. 

errh (IN)

An error handle which can be passed to OCIErrorGet() for diagnostic 
information in the event of an error. 

queue_name (IN)

The target queue for the enqueue operation. 

enqueue_options (IN)

The options for the enqueue operation; stored in an OCIAQEnqOptions 
descriptor. 

message_properties (IN)

The message properties for the message; stored in an OCIAQMsgProperties 
descriptor. 

payload_tdo (IN)

The TDO (type descriptor object) of an object type. For a raw queue, this 
parameter should point to the TDO of SYS.RAW. 

payload (IN)

A pointer to a pointer to an instance of an object type. For a raw queue, this parameter should point to an instance of OCIRaw. 

The OCI provides functions which allow the user to set attributes of the 
payload, such as its text. For information about setting these attributes, 
refer to "Manipulating Object Attributes" on page 8-13. 

payload_ind (IN)

A pointer to a pointer to the program variable buffer containing the parallel 
indicator structure for the object type. 

msgid (OUT)

The message ID. 

flags (IN)

Not currently used; pass as OCI_DEFAULT. 

COMMENTS

This function is used to perform an Advanced Queueing enqueue operation. Users
must have the aq_user_role or privileges to execute the dbms_aq package in 
order to use this call. The OCI environment must be initialized in object 
mode (using OCIInitialize()) to use this call. 

For more information about OCI and Advanced Queueing, refer to "OCI and 
Advanced Queueing" on page 7-40. For additional information about Advanced 
Queueing, refer to Oracle8 Application Developer's Guide. 

To obtain a TDO for the payload, use OCITypeByName(), or OCITypeByRef(). 

EXAMPLES

The following four examples demonstrate the use of OCIAQEnq() and OCIAQDeq() 
in several different situations. 

These examples assume that the database is set up as illustrated in the 
section "Oracle Advanced Queueing By Example" in the advanced queueing chapter
of the Oracle8 Application Developer's Guide. 

Example 1

Enqueue and dequeue of a payload object. 

struct message
{
  OCIString   *subject;
  OCIString   *data;
};
typedef struct message message;

struct null_message
{
  OCIInd    null_adt;
  OCIInd    null_subject;
  OCIInd    null_data;
};
typedef struct null_message null_message;

int main()
{
  OCIEnv *envhp;
  OCIServer *srvhp;
  OCIError *errhp;
  OCISvcCtx *svchp;
  dvoid     *tmp;
  OCIType *mesg_tdo = (OCIType *) 0;
  message  msg;
  null_message nmsg;
  message *mesg = &msg;
  null_message *nmesg = &nmsg;
  message *deqmesg = (message *)0;
  null_message *ndeqmesg = (null_message *)0;
  
  OCIInitialize((ub4) OCI_OBJECT, (dvoid *)0,  (dvoid * (*)()) 0,
                (dvoid * (*)()) 0,  (void (*)()) 0 );
  
  OCIHandleAlloc( (dvoid *) NULL, (dvoid **) &envhp, (ub4) OCI_HTYPE_ENV,
                  52, (dvoid **) &tmp);
  
  OCIEnvInit( &envhp, (ub4) OCI_DEFAULT, 21, (dvoid **) &tmp  );
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, (ub4) OCI_HTYPE_ERROR,
                    52, (dvoid **) &tmp);
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, (ub4) OCI_HTYPE_SERVER,
                    52, (dvoid **) &tmp);
  
  OCIServerAttach( srvhp, errhp, (text *) 0, (sb4) 0, (ub4) OCI_DEFAULT);
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, (ub4) OCI_HTYPE_SVCCTX,
                  52, (dvoid **) &tmp);
  OCIAttrSet( (dvoid *) svchp, (ub4) OCI_HTYPE_SVCCTX, (dvoid *)srvhp, (ub4) 0,
                  (ub4) OCI_ATTR_SERVER, (OCIError *) errhp);
 
  OCILogon(envhp, errhp, &svchp, "AQ", strlen("AQ"), "AQ", strlen("AQ"), 0, 0);

  /o obtain TDO of message_type o/
  OCITypeByName(envhp, errhp, svchp, (CONST text *)"AQ", strlen("AQ"),
                (CONST text *)"MESSAGE_TYPE", strlen("MESSAGE_TYPE"), 
                (text *)0, 0, OCI_DURATION_SESSION, OCI_TYPEGET_ALL, &mesg_tdo);

  /o prepare the message payload o/
  mesg->subject = (OCIString *)0;
  mesg->data = (OCIString *)0;
  OCIStringAssignText(envhp, errhp, (CONST text *)"NORMAL MESSAGE",
                 strlen("NORMAL MESSAGE"), &mesg->subject);
  OCIStringAssignText(envhp, errhp,(CONST text *)"OCI ENQUEUE",
                 strlen("OCI ENQUEUE"), &mesg->data);
  nmesg->null_adt = nmesg->null_subject = nmesg->null_data = OCI_IND_NOTNULL;  

  /o enqueue into the msg_queue o/
  OCIAQEnq(svchp, errhp, (CONST text *)"msg_queue", 0, 0,
                  mesg_tdo, (dvoid **)&mesg, (dvoid **)&nmesg, 0, 0);
  OCITransCommit(svchp, errhp, (ub4) 0);

  /o dequeue from the msg_queue o/
  OCIAQDeq(svchp, errhp, (CONST text *)"msg_queue", 0, 0,
                   mesg_tdo, (dvoid **)&deqmesg, (dvoid **)&ndeqmesg, 0, 0);
  printf("Subject: %s\n", OCIStringPtr(envhp, deqmesg->subject));
  printf("Text: %s\n", OCIStringPtr(envhp, deqmesg->data));
  OCITransCommit(svchp, errhp, (ub4) 0);
}

Example 2

Enqueue and dequeue using correlation IDs. 

struct message
{
  OCIString   *subject;
  OCIString   *data;
};
typedef struct message message;

struct null_message
{
  OCIInd    null_adt;
  OCIInd    null_subject;
  OCIInd    null_data;
};
typedef struct null_message null_message;

int main()
{
  OCIEnv *envhp;
  OCIServer *srvhp;
  OCIError *errhp;
  OCISvcCtx *svchp;
  dvoid     *tmp;
  OCIType *mesg_tdo = (OCIType *) 0;
  message  msg;
  null_message nmsg;
  message *mesg = &msg;
  null_message *nmesg = &nmsg;
  message *deqmesg = (message *)0;
  null_message *ndeqmesg = (null_message *)0;
  OCIRaw*firstmsg = (OCIRaw *)0;
  OCIAQMsgProperties *msgprop = (OCIAQMsgProperties *)0;
  OCIAQDeqOptions *deqopt = (OCIAQDeqOptions *)0;
  text correlation1[30], correlation2[30];
  
  OCIInitialize((ub4) OCI_OBJECT, (dvoid *)0,  (dvoid * (*)()) 0,
                (dvoid * (*)()) 0,  (void (*)()) 0 );
  OCIHandleAlloc( (dvoid *) NULL, (dvoid **) &envhp, (ub4) OCI_HTYPE_ENV,
                 52, (dvoid **) &tmp);
  
  OCIEnvInit( &envhp, (ub4) OCI_DEFAULT, 21, (dvoid **) &tmp  );
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, (ub4) OCI_HTYPE_ERROR,
                 52, (dvoid **) &tmp);
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, (ub4) OCI_HTYPE_SERVER,
                 52, (dvoid **) &tmp);
  
  OCIServerAttach( srvhp, errhp, (text *) 0, (sb4) 0, (ub4) OCI_DEFAULT);
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, (ub4) OCI_HTYPE_SVCCTX,
                 52, (dvoid **) &tmp);
  OCIAttrSet( (dvoid *) svchp, (ub4) OCI_HTYPE_SVCCTX, (dvoid *)srvhp, (ub4) 0,
                 (ub4) OCI_ATTR_SERVER, (OCIError *) errhp);
 
  OCILogon(envhp, errhp, &svchp, "AQ", strlen("AQ"), "AQ", strlen("AQ"), 0, 0);

  /o allocate message properties descriptor o/
  OCIDescriptorAlloc(envhp, (dvoid **)&msgprop, 
                   OCI_DTYPE_AQMSG_PROPERTIES, 0, (dvoid **)0);
  strcpy(correlation1, "1st message");
  OCIAttrSet(msgprop, OCI_DTYPE_AQMSG_PROPERTIES, (dvoid *)&correlation1, 
                   strlen(correlation1), OCI_ATTR_CORRELATION, errhp);

  /o obtain TDO of message_type o/
  OCITypeByName(envhp, errhp, svchp, (CONST text *)"AQ", strlen("AQ"),
                (CONST text *)"MESSAGE_TYPE", strlen("MESSAGE_TYPE"), 
                (text *)0, 0, OCI_DURATION_SESSION, OCI_TYPEGET_ALL, &mesg_tdo);

  /o prepare the message payload o/
  mesg->subject = (OCIString *)0;
  mesg->data = (OCIString *)0;
  OCIStringAssignText(envhp, errhp, (CONST text *)"NORMAL ENQUEUE1", 
                  strlen("NORMAL ENQUEUE1"), &mesg->subject);
  OCIStringAssignText(envhp, errhp,(CONST text *)"OCI ENQUEUE",
                  strlen("OCI ENQUEUE"), &mesg->data);
  nmesg->null_adt = nmesg->null_subject = nmesg->null_data = OCI_IND_NOTNULL;  

  /o enqueue into the msg_queue, store the message id into firstmsg o/
  OCIAQEnq(svchp, errhp, (CONST text *)"msg_queue", 0, msgprop,
                   mesg_tdo, (dvoid **)&mesg, (dvoid **)&nmesg, &firstmsg, 0);

  /o enqueue into the msg_queue with a different correlation id o/
  strcpy(correlation2, "2nd message");
  OCIAttrSet(msgprop, OCI_DTYPE_AQMSG_PROPERTIES, (dvoid*)&correlation2, 
                  strlen(correlation2), OCI_ATTR_CORRELATION, errhp);
  OCIStringAssignText(envhp, errhp, (CONST text *)"NORMAL ENQUEUE2", 
                  strlen("NORMAL ENQUEUE2"), &mesg->subject);
  OCIAQEnq(svchp, errhp, (CONST text *)"msg_queue", 0, msgprop,
                  mesg_tdo, (dvoid **)&mesg, (dvoid **)&nmesg, 0, 0);

  OCITransCommit(svchp, errhp, (ub4) 0);

  /o first dequeue by correlation id "2nd message" o/
  /o allocate dequeue options descriptor and set the correlation option o/
  OCIDescriptorAlloc(envhp, (dvoid **)&deqopt, 
                   OCI_DTYPE_AQDEQ_OPTIONS, 0, (dvoid **)0);
  OCIAttrSet(deqopt, OCI_DTYPE_AQDEQ_OPTIONS, (dvoid *)correlation2, 

                   strlen(correlation2),  OCI_ATTR_CORRELATION, errhp);

  /o dequeue from the msg_queue o/
  OCIAQDeq(svchp, errhp, (CONST text *)"msg_queue", deqopt, 0,
                   mesg_tdo, (dvoid **)&deqmesg, (dvoid **)&ndeqmesg, 0, 0);
  printf("Subject: %s\n", OCIStringPtr(envhp, deqmesg->subject));
  printf("Text: %s\n", OCIStringPtr(envhp, deqmesg->data));
  OCITransCommit(svchp, errhp, (ub4) 0);

  /o second dequeue by message id o/
  OCIAttrSet(deqopt, OCI_DTYPE_AQDEQ_OPTIONS, (dvoid *)&firstmsg,    
  OCIRawSize(envhp, firstmsg), OCI_ATTR_DEQ_MSGID, errhp);
  /o clear correlation id option o/
  OCIAttrSet(deqopt, OCI_DTYPE_AQDEQ_OPTIONS, 
             (dvoid *)correlation2, 0, OCI_ATTR_CORRELATION, errhp);

  /o dequeue from the msg_queue o/
  OCIAQDeq(svchp, errhp, (CONST text *)"msg_queue", deqopt, 0,
              mesg_tdo, (dvoid **)&deqmesg, (dvoid **)&ndeqmesg, 0, 0);
  printf("Subject: %s\n", OCIStringPtr(envhp, deqmesg->subject));
  printf("Text: %s\n", OCIStringPtr(envhp, deqmesg->data));
  OCITransCommit(svchp, errhp, (ub4) 0);
}

Example 3

Enqueue and dequeue of a raw queue. 

int main()
{
  OCIEnv *envhp;
  OCIServer *srvhp;
  OCIError *errhp;
  OCISvcCtx *svchp;
  dvoid     *tmp;
  OCIType *mesg_tdo = (OCIType *) 0;
  char  msg_text[100];
  OCIRaw  *mesg = (OCIRaw *)0;
  OCIRaw*deqmesg = (OCIRaw *)0;
  OCIInd   ind = 0;
  dvoid  *indptr = (dvoid *)&ind;
  inti;
  
  OCIInitialize((ub4) OCI_OBJECT, (dvoid *)0,  (dvoid * (*)()) 0,
               (dvoid * (*)()) 0,  (void (*)()) 0 );
  OCIHandleAlloc( (dvoid *) NULL, (dvoid **) &envhp, (ub4) OCI_HTYPE_ENV,
                  52, (dvoid **) &tmp);
  
  OCIEnvInit( &envhp, (ub4) OCI_DEFAULT, 21, (dvoid **) &tmp  );
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, (ub4) OCI_HTYPE_ERROR,
                  52, (dvoid **) &tmp);
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, (ub4) OCI_HTYPE_SERVER,
                  52, (dvoid **) &tmp);
  
  OCIServerAttach( srvhp, errhp, (text *) 0, (sb4) 0, (ub4) OCI_DEFAULT);
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, (ub4) OCI_HTYPE_SVCCTX,
                  52, (dvoid **) &tmp);
  OCIAttrSet( (dvoid *) svchp, (ub4) OCI_HTYPE_SVCCTX, (dvoid *)srvhp, (ub4) 0,
                  (ub4) OCI_ATTR_SERVER, (OCIError *) errhp);
 
  OCILogon(envhp, errhp, &svchp, "AQ", strlen("AQ"), "AQ", strlen("AQ"), 0, 0);

  /o obtain the TDO of the RAW data type o/
  OCITypeByName(envhp, errhp, svchp, (CONST text *)"SYS", strlen("SYS"),
                (CONST text *)"RAW", strlen("RAW"), 
                (text *)0, 0, OCI_DURATION_SESSION, OCI_TYPEGET_ALL, &mesg_tdo);

  /o prepare the message payload o/
  strcpy(msg_text, "Enqueue to a RAW queue");
  OCIRawAssignBytes(envhp, errhp, msg_text, strlen(msg_text), &mesg);

  /o enqueue the message into raw_msg_queue o/
  OCIAQEnq(svchp, errhp, (CONST text *)"raw_msg_queue", 0, 0,
                 mesg_tdo, (dvoid **)&mesg, (dvoid **)&indptr, 0, 0);
  OCITransCommit(svchp, errhp, (ub4) 0);

  /o dequeue the same message into C variable deqmesg o/
  OCIAQDeq(svchp, errhp, (CONST text *)"raw_msg_queue", 0, 0, 
   mesg_tdo, (dvoid **)&deqmesg, (dvoid **)&indptr, 0, 0);
  for (i = 0; i < OCIRawSize(envhp, deqmesg); i++)
    printf("%c", *(OCIRawPtr(envhp, deqmesg) + i));
  OCITransCommit(svchp, errhp, (ub4) 0);
}

Example 4

Enqueue and dequeue using OCIAQAgent. 

struct message
{
  OCIString   *subject;
  OCIString   *data;
};
typedef struct message message;

struct null_message
{
  OCIInd    null_adt;
  OCIInd    null_subject;
  OCIInd    null_data;
};
typedef struct null_message null_message;

int main()
{
  OCIEnv *envhp;
  OCIServer *srvhp;
  OCIError *errhp;
  OCISvcCtx *svchp;
  dvoid     *tmp;
  OCIType *mesg_tdo = (OCIType *) 0;
  message  msg;
  null_message nmsg;
  message *mesg = &msg;
  null_message *nmesg = &nmsg;
  message *deqmesg = (message *)0;
  null_message *ndeqmesg = (null_message *)0;
  OCIAQMsgProperties *msgprop = (OCIAQMsgProperties *)0;
  OCIAQAgent *agents[2];
  OCIAQDeqOptions *deqopt = (OCIAQDeqOptions *)0;
  ub4wait = OCI_DEQ_NO_WAIT;
  ub4 navigation = OCI_DEQ_FIRST_MSG;
  
  OCIInitialize((ub4) OCI_OBJECT, (dvoid *)0,  (dvoid * (*)()) 0,
                (dvoid * (*)()) 0,  (void (*)()) 0 );
  
  OCIHandleAlloc( (dvoid *) NULL, (dvoid **) &envhp, (ub4) OCI_HTYPE_ENV,
                52, (dvoid **) &tmp);
  
  OCIEnvInit( &envhp, (ub4) OCI_DEFAULT, 21, (dvoid **) &tmp  );
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, (ub4) OCI_HTYPE_ERROR,
                   52, (dvoid **) &tmp);
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, (ub4) OCI_HTYPE_SERVER,
                   52, (dvoid **) &tmp);
  
  OCIServerAttach( srvhp, errhp, (text *) 0, (sb4) 0, (ub4) OCI_DEFAULT);
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, (ub4) OCI_HTYPE_SVCCTX,
                   52, (dvoid **) &tmp);
  
  OCIAttrSet( (dvoid *) svchp, (ub4) OCI_HTYPE_SVCCTX, (dvoid *)srvhp, (ub4) 0,
                   (ub4) OCI_ATTR_SERVER, (OCIError *) errhp);
 
  OCILogon(envhp, errhp, &svchp, "AQ", strlen("AQ"), "AQ", strlen("AQ"), 0, 0);

  /o obtain TDO of message_type o/
  OCITypeByName(envhp, errhp, svchp, (CONST text *)"AQ", strlen("AQ"),
       (CONST text *)"MESSAGE_TYPE", strlen("MESSAGE_TYPE"), 
       (text *)0, 0, OCI_DURATION_SESSION, OCI_TYPEGET_ALL, &mesg_tdo);

  /o prepare the message payload o/
  mesg->subject = (OCIString *)0;
  mesg->data = (OCIString *)0;
  OCIStringAssignText(envhp, errhp,
                    (CONST text *)"MESSAGE 1", strlen("MESSAGE 1"), 
                    &mesg->subject);
  OCIStringAssignText(envhp, errhp,
                    (CONST text *)"mesg for queue subscribers", 
                    strlen("mesg for queue subscribers"), &mesg->data);
  nmesg->null_adt = nmesg->null_subject = nmesg->null_data = OCI_IND_NOTNULL;  

  /o enqueue MESSAGE 1 for subscribers to the queue i.e. for RED and GREEN o/
  OCIAQEnq(svchp, errhp, (CONST text *)"msg_queue_multiple", 0, 0,
                       mesg_tdo, (dvoid **)&mesg, (dvoid **)&nmesg, 0, 0);

  /o enqueue MESSAGE 2 for specified recipients i.e. for RED and BLUE o/
  /o prepare message payload o/
  OCIStringAssignText(envhp, errhp,
                    (CONST text *)"MESSAGE 2", strlen("MESSAGE 2"), 
                    &mesg->subject);
  OCIStringAssignText(envhp, errhp,
                    (CONST text *)"mesg for two recipients", 
                    strlen("mesg for two recipients"), &mesg->data);

  /o allocate AQ message properties and agent descriptors o/
  OCIDescriptorAlloc(envhp, (dvoid **)&msgprop, 
                OCI_DTYPE_AQMSG_PROPERTIES, 0, (dvoid **)0);
  OCIDescriptorAlloc(envhp, (dvoid **)&agents[0], 
                  OCI_DTYPE_AQAGENT, 0, (dvoid **)0);
  OCIDescriptorAlloc(envhp, (dvoid **)&agents[1], 
                  OCI_DTYPE_AQAGENT, 0, (dvoid **)0);

  /o prepare the recipient list, RED and BLUE o/
  OCIAttrSet(agents[0], OCI_DTYPE_AQAGENT, "RED", strlen("RED"),
                     OCI_ATTR_AGENT_NAME, errhp);
  OCIAttrSet(agents[1], OCI_DTYPE_AQAGENT, "BLUE", strlen("BLUE"),
                     OCI_ATTR_AGENT_NAME, errhp);
  OCIAttrSet(msgprop, OCI_DTYPE_AQMSG_PROPERTIES, (dvoid *)agents, 2,
                      OCI_ATTR_RECIPIENT_LIST, errhp);

  OCIAQEnq(svchp, errhp, (CONST text *)"msg_queue_multiple", 0, msgprop,
                       mesg_tdo, (dvoid **)&mesg, (dvoid **)&nmesg, 0, 0);

  OCITransCommit(svchp, errhp, (ub4) 0);

  /o now dequeue the messages using different consumer names o/
  /o allocate dequeue options descriptor to set the dequeue options o/
  OCIDescriptorAlloc(envhp, (dvoid **)&deqopt, OCI_DTYPE_AQDEQ_OPTIONS, 0, 
                     (dvoid **)0);

  /o set wait parameter to NO_WAIT so that the dequeue returns immediately o/
  OCIAttrSet(deqopt, OCI_DTYPE_AQDEQ_OPTIONS, (dvoid *)&wait, 0, 
                     OCI_ATTR_WAIT, errhp);

  /o set navigation to FIRST_MESSAGE so that the dequeue resets the position o/
  /o after a new consumer_name is set in the dequeue options     o/
  OCIAttrSet(deqopt, OCI_DTYPE_AQDEQ_OPTIONS, (dvoid *)&navigation, 0, 
                     OCI_ATTR_NAVIGATION, errhp);
  
  /o dequeue from the msg_queue_multiple as consumer BLUE o/
  OCIAttrSet(deqopt, OCI_DTYPE_AQDEQ_OPTIONS, (dvoid *)"BLUE", strlen("BLUE"), 
                     OCI_ATTR_CONSUMER_NAME, errhp);
  while (OCIAQDeq(svchp, errhp, (CONST text *)"msg_queue_multiple", deqopt, 0,
 mesg_tdo, (dvoid **)&deqmesg, (dvoid **)&ndeqmesg, 0, 0) 
 == OCI_SUCCESS)
  {
    printf("Subject: %s\n", OCIStringPtr(envhp, deqmesg->subject));
    printf("Text: %s\n", OCIStringPtr(envhp, deqmesg->data));
  }
  OCITransCommit(svchp, errhp, (ub4) 0);

  /o dequeue from the msg_queue_multiple as consumer RED o/
  OCIAttrSet(deqopt, OCI_DTYPE_AQDEQ_OPTIONS, (dvoid *)"RED", strlen("RED"), 
                     OCI_ATTR_CONSUMER_NAME, errhp);
  while (OCIAQDeq(svchp, errhp, (CONST text *)"msg_queue_multiple", deqopt, 0,
                 mesg_tdo, (dvoid **)&deqmesg, (dvoid **)&ndeqmesg, 0, 0) 
 == OCI_SUCCESS)
  {
    printf("Subject: %s\n", OCIStringPtr(envhp, deqmesg->subject));
    printf("Text: %s\n", OCIStringPtr(envhp, deqmesg->data));
  }
  OCITransCommit(svchp, errhp, (ub4) 0);

  /o dequeue from the msg_queue_multiple as consumer GREEN o/
  OCIAttrSet(deqopt, OCI_DTYPE_AQDEQ_OPTIONS,(dvoid *)"GREEN",strlen("GREEN"), 
                     OCI_ATTR_CONSUMER_NAME, errhp);
  while (OCIAQDeq(svchp, errhp, (CONST text *)"msg_queue_multiple", deqopt, 0,
                 mesg_tdo, (dvoid **)&deqmesg, (dvoid **)&ndeqmesg, 0, 0) 
 == OCI_SUCCESS)
  {
    printf("Subject: %s\n", OCIStringPtr(envhp, deqmesg->subject));
    printf("Text: %s\n", OCIStringPtr(envhp, deqmesg->data));
  }
  OCITransCommit(svchp, errhp, (ub4) 0);
}

Related Functions

OCIAQDeq(), OCIInitialize() 




--------------------------------OCIAttrGet------------------------------------

OCIAttrGet()

NAME

OCI Attribute Get

PURPOSE

This call is used to get a particular attribute of a handle. 

SYNTAX

sword OCIAttrGet ( CONST dvoid    *trgthndlp,
                 ub4            trghndltyp,
                 dvoid          *attributep,
                 ub4            *sizep,
                 ub4            attrtype,
                 OCIError       *errhp );


PARAMETERS


trgthndlp (IN) - is the pointer to a handle type. 

trghndltyp (IN) - is the handle type. 

attributep (OUT) - is a pointer to the storage for an attribute value. The 
attribute value is filled in. 

sizep (OUT) - is the size of the attribute value. 
This can be passed in as NULL for most parameters as the size is well known. 
For text* parameters, a pointer to a ub4 must be passed in to get the length 
of the string. 

attrtype (IN) - is the type of attribute.

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

COMMENTS

This call is used to get a particular attribute of a handle.
See Appendix B,  "Handle Attributes",  for a list of handle types and their 
readable attributes.

RELATED FUNCTIONS

OCIAttrSet()

--------------------------------OCIAttrSet------------------------------------


OCIAttrSet()


NAME

OCI Attribute Set

PURPOSE

This call is used to set a particular attribute of a handle or a descriptor. 

SYNTAX

sword OCIAttrSet ( dvoid       *trgthndlp,
                 ub4         trghndltyp,
                 dvoid       *attributep,
                 ub4         size,
                 ub4         attrtype,
                 OCIError    *errhp );


PARAMETERS


trghndlp (IN/OUT) - the pointer to a handle type whose attribute gets 
modified. 

trghndltyp (IN/OUT) - is the handle type. 

attributep (IN) - a pointer to an attribute value. 
The attribute value is copied into the target handle. If the attribute value 
is a pointer, then only the pointer is copied, not the contents of the pointer.


size (IN) - is the size of an attribute value. This can be passed in as 0 for 
most attributes as the size is already known by the OCI library. For text*
attributes, a ub4 must be passed in set to the length of the string. 

attrtype (IN) - the type of attribute being set.

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

COMMENTS

This call is used to set a particular attribute of a handle or a descriptor. 
See Appendix B for a list of handle types and their writeable attributes.

EXAMPLE

The following code sample demonstrates OCIAttrSet() being used several times
near the beginning of an application.

int main()

{

OCIEnv *envhp;

OCIServer *srvhp;

OCIError *errhp;

OCISvcCtx *svchp;

OCIStmt *stmthp;

OCISession *usrhp;

OCIInitialize((ub4) OCI_THREADED | OCI_OBJECT, (dvoid *)0,
              (dvoid * (*)()) 0,(dvoid * (*)()) 0,  (void (*)()) 0 ); 
OCIHandleAlloc( (dvoid *) NULL, (dvoid **) &envhp, (ub4) OCI_HTYPE_ENV,
               0, (dvoid **) &tmp);

OCIEnvInit( &envhp, (ub4) OCI_DEFAULT, 0, (dvoid **) &tmp  ); 

OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, (ub4)
               OCI_HTYPE_ERROR, 0, (dvoid **) &tmp);
OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, (ub4)
               OCI_HTYPE_SERVER, 0, (dvoid **) &tmp);
OCIServerAttach( srvhp, errhp, (text *) 0, (sb4) 0, (ub4) OCI_DEFAULT); 

/o set attribute server context in the service context o/
OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp,
               (ub4) OCI_HTYPE_SVCCTX, , (dvoid **) &tmp); 
OCIAttrSet( (dvoid *) svchp, (ub4) OCI_HTYPE_SVCCTX, (dvoid *) srvhp,
           (ub4) 0, (ub4) OCI_ATTR_SERVER, (OCIError *) errhp);

/o allocate a user session handle o/
OCIHandleAlloc((dvoid *)envhp, (dvoid **)&usrhp, 
               (ub4) OCI_HTYPE_SESSION, (size_t) 0, (dvoid **) 0);
OCIAttrSet((dvoid *)usrhp, (ub4)OCI_HTYPE_SESSION, (dvoid *)"sherry", 
           (ub4)strlen("sherry"), OCI_ATTR_USERNAME, errhp);
OCIAttrSet((dvoid *)usrhp, (ub4)OCI_HTYPE_SESSION, (dvoid *)"penfield",
           (ub4)strlen("penfield"), OCI_ATTR_PASSWORD, errhp);

/o begin a new session o/
checkerr(errhp, OCISessionBegin (svchp, errhp, usrhp, OCI_CRED_RDBMS,
                                 OCI_DEFAULT));
/o populate the service context with session information for execution o/
OCIAttrSet((dvoid *)svchp, (ub4)OCI_HTYPE_SVCCTX, (dvoid *)usrhp,
           (ub4)0, OCI_ATTR_SESSION, errhp);



RELATED FUNCTIONS

OCIAttrGet()



--------------------------------OCIBindArrayOfStruct--------------------------



OCIBindArrayOfStruct()

NAME

OCI Bind for Array of Structures

PURPOSE

This call sets up the skip parameters for a static array bind.

SYNTAX

sword OCIBindArrayOfStruct ( OCIBind     *bindp,
                             OCIError    *errhp,
                             ub4         pvskip, 
                             ub4         indskip, 
                             ub4         alskip, 
                             ub4         rcskip );

PARAMETERS


bindp (IN) - the handle to a bind structure. 

errhp (IN) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

pvskip (IN) - skip parameter for the next data value. 

indskip (IN) - skip parameter for the next indicator value or structure. 

alskip (IN) - skip parameter for the next actual length value. 

rcskip (IN) - skip parameter for the next column-level return code value. 

COMMENTS

This call sets up the skip parameters necessary for a static array bind.
This call follows a call to OCIBindByName() or OCIBindByPos(). The bind 
handle returned by that initial bind call is used as a parameter for the 
OCIBindArrayOfStruct() call.
For information about skip parameters, see the section "Arrays of Structures" 
on page 5-17.

RELATED FUNCTIONS

OCIAttrGet()


--------------------------------OCIBindByName---------------------------------

OCIBindByName()

NAME

OCI Bind by Name

PURPOSE

Creates an association between a program variable and a placeholder in a SQL 
statement or PL/SQL block.

SYNTAX

sword OCIBindByName (
              OCIStmt       *stmtp, 
              OCIBind       **bindp,
              OCIError      *errhp,
              CONST text    *placeholder,
              sb4           placeh_len,
              dvoid         *valuep,
              sb4           value_sz,
              ub2           dty,
              dvoid         *indp,
              ub2           *alenp,
              ub2           *rcodep,
              ub4           maxarr_len,
              ub4           *curelep, 
              ub4           mode ); 

PARAMETERS


stmth (IN/OUT) - the statement handle to the SQL or PL/SQL statement 
being processed.

bindp (IN/OUT) - a pointer to a pointer to a bind handle which is implicitly
allocated by this call.  The bind handle maintains all the bind information for
this particular input value. The handle is feed implicitly when the statement
handle is deallocated.

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

placeholder (IN) - the placeholder attributes are specified by name if
OCIBindByName() is being called.

placeh_len (IN) - the length of the placeholder name specified in placeholder.

valuep (IN/OUT) - a pointer to a data value or an array of data values of the 
type specified in the dty parameter. An array of data values can be specified 
for mapping into a PL/SQL table or for providing data for SQL multiple-row 
operations. When an array of bind values is provided, this is called an array 
bind in OCI terms. Additional attributes of the array bind (not bind to a 
column of ARRAY type) are set up in OCIBindArrayOfStruct() call. 
For a REF, named data type  bind, the valuep parameter is used only for IN 
bind data. The pointers to OUT buffers are set in the pgvpp parameter 
initialized by OCIBindObject(). For named data type and REF binds, the bind 
values are unpickled into the Object Cache. The OCI object navigational calls 
can then be used to navigate the objects and the refs in the Object Cache.
If the OCI_DATA_AT_EXEC mode is specified in the mode parameter, valuep 
is ignored for all data types. OCIBindArrayOfStruct() cannot be used and 
OCIBindDynamic() must be invoked to provide callback functions if desired. 

value_sz (IN) - the size of a data value. In the case of an array bind, this is
the maximum size of any element possible with the actual sizes being specified
in the alenp parameter.  
If the OCI_DATA_AT_EXEC mode is specified, valuesz
defines the maximum size of the data that can be ever provided at runtime for
data types other than named data types or REFs.

dty (IN) - the data type of the value(s) being bound. Named data types 
(SQLT_NTY) and REFs (SQLT_REF) are valid only if the application has been 
initialized in object mode. For named data types, or REFs, additional calls 
must be made with the bind handle to set up the datatype-specific attributes.

indp (IN/OUT) - pointer to an indicator variable or array. For scalar data 
types, this is a pointer to sb2 or an array of sb2s. For named data types, 
this pointer is ignored and the actual pointer to the indicator structure or 
an array of indicator structures is initialized by OCIBindObject(). 
Ignored for dynamic binds.
See the section "Indicator Variables" on page 2-29 for more information about 
indicator variables.

alenp (IN/OUT) - pointer to array of actual lengths of array elements. Each 
element in alenp is the length of the data in the corresponding element in the 
bind value array before and after the execute. This parameter is ignored for 
dynamic binds.

rcodep (OUT) - pointer to array of column level return codes. This parameter 
is ignored for dynamic binds.

maxarr_len (IN) - the maximum possible number of elements of type dty in a 
PL/SQL binds. This parameter is not required for non-PL/SQL binds. If 
maxarr_len is non-zero, then either OCIBindDynamic() or 
OCIBindArrayOfStruct() can be invoked to set up additional bind attributes. 

curelep(IN/OUT) - a pointer to the actual number of elements. This parameter 
is only required for PL/SQL binds.

mode (IN) - the valid modes for this parameter are:
OCI_DEFAULT. This is default mode.
OCI_DATA_AT_EXEC. When this mode is selected, the value_sz 
parameter defines the maximum size of the data that can be ever 
provided at runtime. The application must be ready to provide the OCI 
library runtime IN data buffers at any time and any number of times. 
Runtime data is provided in one of the two ways:
callbacks using a user-defined function which must be registered 
with a subsequent call to OCIBindDynamic(). 
a polling mechanism using calls supplied by the OCI. This mode 
is assumed if no callbacks are defined.
For more information about using the OCI_DATA_AT_EXEC mode, see 
the section "Runtime Data Allocation and Piecewise Operations" on 
page 7-16.
When the allocated buffers are not required any more, they should be 
freed by the client. 

COMMENTS

This call is used to perform a basic bind operation. The bind creates an
association between the address of a program variable and a placeholder in a
SQL statement or PL/SQL block. The bind call also specifies the type of data
which is being bound, and may also indicate the method by which data will be
provided at runtime.  This function also implicitly allocates the bind handle
indicated by the bindp parameter.  Data in an OCI application can be bound to
placeholders statically or dynamically. Binding is static when all the IN bind
data and the OUT bind buffers are well-defined just before the execute. Binding
is dynamic when the IN bind data and the OUT bind buffers are provided by the
application on demand at execute time to the client library. Dynamic binding is
indicated by setting the mode parameter of this call to OCI_DATA_AT_EXEC. 

For more information about dynamic binding, see the section "Runtime Data
Allocation and Piecewise Operations" on page 5-16.

Both OCIBindByName() and OCIBindByPos() take as a parameter a bind handle,
which is implicitly allocated by the bind call A separate bind handle is
allocated for each placeholder the application is binding.  Additional bind
calls may be required to specify particular attributes necessary when binding
certain data types or handling input data in certain ways: If arrays of
structures are being utilized, OCIBindArrayOfStruct() must be called to set up
the necessary skip parameters.  If data is being provided dynamically at
runtime, and the application will be using user-defined callback functions,
OCIBindDynamic() must be called to register the callbacks.  If a named data
type is being bound, OCIBindObject() must be called to specify additional
necessary information.

RELATED FUNCTIONS

OCIBindDynamic()
OCIBindObject()
OCIBindArrayOfStruct()
OCIAttrGet()



-------------------------------OCIBindByPos-----------------------------------


OCIBindByPos()

NAME

OCI Bind by Position

PURPOSE

Creates an association between a program variable and a placeholder in a SQL 
statement or PL/SQL block.

SYNTAX

sword OCIBindByPos ( 
              OCIStmt      *stmtp, 
              OCIBind      **bindp,
              OCIError     *errhp,
              ub4          position,
              dvoid        *valuep,
              sb4          value_sz,
              ub2          dty,
              dvoid        *indp,
              ub2          *alenp,
              ub2          *rcodep,
              ub4          maxarr_len,
              ub4          *curelep, 
              ub4          mode);

PARAMETERS


stmth (IN/OUT) - the statement handle to the SQL or PL/SQL statement 
being processed.

bindp (IN/OUT) - a pointer to a pointer to a bind handle which is implicitly
allocated by this call.  The bind handle maintains all the bind information for
this particular input value. The handle is feed implicitly when the statement
handle is deallocated.

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

position (IN) - the placeholder attributes are specified by position if
ocibindp() is being called.

valuep (IN/OUT) - a pointer to a data value or an array of data values of the 
type specified in the dty parameter. An array of data values can be specified 
for mapping into a PL/SQL table or for providing data for SQL multiple-row 
operations. When an array of bind values is provided, this is called an array 
bind in OCI terms. Additional attributes of the array bind (not bind to a 
column of ARRAY type) are set up in OCIBindArrayOfStruct() call. 
For a REF, named data type  bind, the valuep parameter is used only for IN 
bind data. The pointers to OUT buffers are set in the pgvpp parameter 
initialized by OCIBindObject(). For named data type and REF binds, the bind 
values are unpickled into the Object Cache. The OCI object navigational calls 
can then be used to navigate the objects and the refs in the Object Cache.
If the OCI_DATA_AT_EXEC mode is specified in the mode parameter, valuep 
is ignored for all data types. OCIBindArrayOfStruct() cannot be used and 
OCIBindDynamic() must be invoked to provide callback functions if desired. 

value_sz (IN) - the size of a data value. In the case of an array bind, this is
the maximum size of any element possible with the actual sizes being specified
in the alenp parameter.  If the OCI_DATA_AT_EXEC mode is specified, valuesz
defines the maximum size of the data that can be ever provided at runtime for
data types other than named data types or REFs.

dty (IN) - the data type of the value(s) being bound. Named data types 
(SQLT_NTY) and REFs (SQLT_REF) are valid only if the application has been 
initialized in object mode. For named data types, or REFs, additional calls 
must be made with the bind handle to set up the datatype-specific attributes.

indp (IN/OUT) - pointer to an indicator variable or array. For scalar data 
types, this is a pointer to sb2 or an array of sb2s. For named data types, 
this pointer is ignored and the actual pointer to the indicator structure or 
an array of indicator structures is initialized by OCIBindObject(). Ignored 
for dynamic binds.
See the section "Indicator Variables" on page 2-29 for more information about 
indicator variables.

alenp (IN/OUT) - pointer to array of actual lengths of array elements. Each 
element in alenp is the length of the data in the corresponding element in the 
bind value array before and after the execute. This parameter is ignored for 
dynamic binds.

rcodep (OUT) - pointer to array of column level return codes. This parameter 
is ignored for dynamic binds.

maxarr_len (IN) - the maximum possible number of elements of type dty in a
PL/SQL binds. This parameter is not required for non-PL/SQL binds. If
maxarr_len is non-zero, then either OCIBindDynamic() or OCIBindArrayOfStruct()
can be invoked to set up additional bind attributes.

curelep(IN/OUT) - a pointer to the actual number of elements. This parameter 
is only required for PL/SQL binds.

mode (IN) - the valid modes for this parameter are: 

OCI_DEFAULT. This is default mode.

OCI_DATA_AT_EXEC. When this mode is selected, the value_sz parameter defines
the maximum size of the data that can be ever provided at runtime. The
application must be ready to provide the OCI library runtime IN data buffers at
any time and any number of times.

Runtime data is provided in one of the two ways - callbacks using a
user-defined function which must be registered with a subsequent call to
OCIBindDynamic() or a polling mechanism using calls supplied by the OCI. This
mode is assumed if no callbacks are defined.

For more information about using the OCI_DATA_AT_EXEC mode, see the section
"Runtime Data Allocation and Piecewise Operations" on page 7-16.

When the allocated buffers are not required any more, they should be 
freed by the client. 

COMMENTS

This call is used to perform a basic bind operation. The bind creates an
association between the address of a program variable and a placeholder in a
SQL statement or PL/SQL block. The bind call also specifies the type of data
which is being bound, and may also indicate the method by which data will be
provided at runtime.  This function also implicitly allocates the bind handle
indicated by the bindp parameter.  Data in an OCI application can be bound to
placeholders statically or dynamically. Binding is static when all the IN bind
data and the OUT bind buffers are well-defined just before the execute. Binding
is dynamic when the IN bind data and the OUT bind buffers are provided by the
application on demand at execute time to the client library. Dynamic binding is
indicated by setting the mode parameter of this call to OCI_DATA_AT_EXEC.

For more information about dynamic binding, see 
the section "Runtime Data Allocation and Piecewise Operations" on 
page 7-16

Both OCIBindByName() and OCIBindByPos() take as a parameter a bind handle,
which is implicitly allocated by the bind call A separate bind handle is
allocated for each placeholder the application is binding.

Additional bind calls may be required to specify particular attributes
necessary when binding certain data types or handling input data in certain
ways:

If arrays of structures are being utilized, OCIBindArrayOfStruct() must be
called to set up the necessary skip parameters.

If data is being provided dynamically at runtime, and the application will be
using user-defined callback functions, OCIBindDynamic() must be called to
register the callbacks.

If a named data type is being bound, OCIBindObject() must be called to specify
additional necessary information.

If a statement with RETURNING clause is used, a call to OCIBindDynamic() must
follow this call.

RELATED FUNCTIONS

OCIBindDynamic(), OCIBindObject(), OCIBindArrayOfStruct(), OCIAttrGet()



-------------------------------OCIBindDynamic---------------------------------

OCIBindDynamic()

NAME

OCI Bind Dynamic Attributes

PURPOSE

This call is used to register user callbacks for dynamic data allocation. 

SYNTAX

sword OCIBindDynamic( OCIBind     *bindp,
                    OCIError    *errhp,
                    dvoid       *ictxp, 
                    OCICallbackInBind         (icbfp)(/o_
                                dvoid            *ictxp,
                                OCIBind          *bindp,
                                ub4              iter, 
                                ub4              index, 
                                dvoid            **bufpp,
                                ub4              *alenp,
                                ub1              *piecep, 
                                dvoid            **indp _o/),
                    dvoid       *octxp,
                    OCICallbackOutBind         (ocbfp)(/o_
                                dvoid            *octxp,
                                OCIBind          *bindp,
                                ub4              iter, 
                                ub4              index, 
                                dvoid            **bufp, 
                                ub4              **alenpp,
                                ub1              *piecep,
                                dvoid            **indpp, 
                                ub2              **rcodepp _o/)   );

PARAMETERS

bindp (IN/OUT) - a bind handle returned by a call to OCIBindByName() or
OCIBindByPos().

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for
diagnostic information in the event of an error.

ictxp (IN) - the context pointer required by the call back function icbfp. 

icbfp (IN) - the callback function which returns a pointer to the IN bind value
or piece at run time. The callback takes in the following parameters.

ictxp (IN/OUT) - the context pointer for this callback function. 

bindp (IN) - the bind handle passed in to uniquely identify this bind variable.

iter (IN) - 1-based execute iteration value. 

index (IN) - index of the current array, for an array bind. 1 based not greater
than curele parameter of the bind call.

index (IN) - index of the current array, for an array bind. This parameter 
is 1-based, and may not be greater than curele parameter of the bind call. 

bufpp (OUT) - the pointer to the buffer. 

piecep (OUT) - which piece of the bind value. This can be one of the following
values - OCI_ONE_PIECE, OCI_FIRST_PIECE, OCI_NEXT_PIECE and OCI_LAST_PIECE.

indp (OUT) - contains the indicator value. This is apointer to either an sb2
value or a pointer to an indicator structure for binding named data types.

indszp (OUT) - contains the indicator value size. A pointer containing the size
of either an sb2 or an indicator structure pointer.

octxp (IN) - the context pointer required by the callback function ocbfp.

ocbfp (IN) - the callback function which returns a pointer to the OUT bind
value or piece at run time. The callback takes in the following parameters.

octxp (IN/OUT) - the context pointer for this call back function. 

bindp (IN) - the bind handle passed in to uniquely identify this bind 
variable. 

iter (IN) - 1-based execute iteration value. 

index (IN) - index of the current array, for an array bind. This parameter is
1-based, and must not be greater than curele parameter of the bind call.

bufpp (OUT) - a pointer to a buffer to write the bind value/piece. 

buflp (OUT) - returns the buffer size. 

alenpp (OUT) - a pointer to a storage for OCI to fill in the size of the bind
value/piece after it has been read.

piecep (IN/OUT) - which piece of the bind value. It will be set by the library
to be one of the following values - OCI_ONE_PIECE or OCI_NEXT_PIECE. The
callback function can leave it unchanged or set it to OCI_FIRST_PIECE or
OCI_LAST_PIECE. By default - OCI_ONE_PIECE.

indpp (OUT) - returns a pointer to contain the indicator value which either an
sb2 value or a pointer to an indicator structure for named data types.

indszpp (OUT) - returns a pointer to return the size of the indicator value
which is either size of an sb2 or size of an indicator structure.

rcodepp (OUT) - returns a pointer to contains the return code. 

COMMENTS

This call is used to register user-defined callback functions for providing
data for an UPDATE or INSERT if OCI_DATA_AT_EXEC mode was specified in a
previous call to OCIBindByName() or OCIBindByPos().

The callback function pointers must return OCI_CONTINUE if it the call is
successful. Any return code other than OCI_CONTINUE signals that the client
wishes to abort processing immediately.

For more information about the OCI_DATA_AT_EXEC mode, see the section "Runtime
Data Allocation and Piecewise Operations" on page 7-16.

RELATED FUNCTIONS

OCIBindByName(), OCIBindByPos()


---------------------------------OCIBindObject--------------------------------


OCIBindObject()

NAME

OCI Bind Object

PURPOSE

This function sets up additional attributes which are required for a named 
data type (object)  bind.

SYNTAX

sword OCIBindObject ( OCIBind          *bindp,
                    OCIError         *errhp, 
                    CONST OCIType    *type,
                    dvoid            **pgvpp, 
                    ub4              *pvszsp, 
                    dvoid            **indpp, 
                    ub4              *indszp, );


PARAMETERS

bindp (IN/OUT) - the bind handle returned by the call to OCIBindByName() 
or OCIBindByPos(). 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

type (IN) - points to the TDO which describes the type of the program 
variable being bound. Retrieved by calling OCITypeByName().

pgvpp (IN/OUT) - points to a pointer to the program variable buffer. For an
array, pgvpp points to an array of pointers. When the bind variable is also an
OUT variable, the OUT Named Data Type value or REF is allocated (unpickled) in
the Object Cache, and a pointer to the value or REF is returned, At the end of
execute, when all OUT values have been received, pgvpp points to an array of
pointer(s) to these newly allocated named data types in the object cache.

pgvpp is ignored if the OCI_DATA_AT_EXEC mode is set. Then the Named Data Type
buffers are requested at runtime. For static array binds, skip factors may be
specified using the OCIBindArrayOfStruct() call. The skip factors are used to
compute the address of the next pointer to the value, the indicator structure
and their sizes.

pvszsp (IN/OUT) - points to the size of the program variable. The size of the 
named data type is not required on input. For an array, pvszsp is an array of 
ub4s. On return, for OUT bind variables, this points to size(s) of the Named 
Data Types and REFs received. pvszsp is ignored if the OCI_DATA_AT_EXEC 
mode is set. Then the size of the buffer is taken at runtime.

indpp (IN/OUT) - points to a pointer to the program variable buffer containing
the parallel indicator structure. For an array, points to an array of
pointers. When the bind variable is also an OUT bind variable, memory is
allocated in the object cache, to store the unpickled OUT indicator values. At
the end of the execute when all OUT values have been received, indpp points to
the pointer(s) to these newly allocated indicator structure(s).  indpp is
ignored if the OCI_DATA_AT_EXEC mode is set. Then the indicator is requested at
runtime.

indszp (IN/OUT) - points to the size of the IN indicator structure program
variable. For an array, it is an array of sb2s. On return for OUT bind
variables, this points to size(s) of the received OUT indicator structures.
indszp is ignored if the OCI_DATA_AT_EXEC mode is set. Then the indicator size
is requested at runtime.

COMMENTS

This function sets up additional attributes which binding a named data type 
or a REF. An error will be returned if this function is called when the OCI 
environment has been initialized in non-object mode. 
This call takes as a paramter a type descriptor object (TDO) of datatype 
OCIType for the named data type being defined.  The TDO can be retrieved 
with a call to OCITypeByName().
If the OCI_DATA_AT_EXEC mode was specified in ocibindn() or ocibindp(), the 
pointers to the IN buffers are obtained either using the callback icbfp 
registered in the OCIBindDynamic() call or by the OCIStmtSetPieceInfo() call. 
The buffers are dynamically allocated for the OUT data and the pointers to 
these buffers are returned either by calling ocbfp() registered by the 
OCIBindDynamic() or by setting the pointer to the buffer in the buffer passed 
in by OCIStmtSetPieceInfo() called when OCIStmtExecute() returned 
OCI_NEED_DATA. The memory of these client library- allocated buffers must be 
freed when not in use anymore by using the OCIObjectFreee() call.

RELATED FUNCTIONS

OCIBindByName(), OCIBindByPos()





----------------------------------OCIBreak------------------------------------


OCIBreak()

NAME

OCI Break

PURPOSE

This call performs an immediate (asynchronous) abort of any currently 
executing OCI function that is associated with a server .

SYNTAX

sword OCIBreak ( dvoid      *hndlp,
                 OCIError   *errhp);


PARAMETERS

hndlp (IN) - the service context handle or the server context handle.

errhp (IN) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

COMMENTS

This call performs an immediate (asynchronous) abort of any currently executing
OCI function that is associated with a server. It is normally used to stop a
long-running OCI call being processed on the server.  This call can take either
the service context handle or the server context handle as a parameter to
identify the function to be aborted.

RELATED FUNCTIONS

------------------------------OCIDefineArrayOfStruct--------------------------


OCIDefineArrayOfStruct()

NAME

OCI Define for Array of Structures

PURPOSE

This call specifies additional attributes necessary for a static array define.

SYNTAX

sword OCIDefineArrayOfStruct ( OCIDefine   *defnp,
                             OCIError    *errhp,
                             ub4         pvskip, 
                             ub4         indskip, 
                             ub4         rlskip,
                             ub4         rcskip );


PARAMETERS

defnp (IN) - the handle to the define structure which was returned by a call to
OCIDefineByPos().

errhp (IN) - an error handle which can be passed to OCIErrorGet() for
diagnostic information in the event of an error.

pvskip (IN) - skip parameter for the next data value.

indskip (IN) - skip parameter for the next indicator location. 

rlskip (IN) - skip parameter for the next return length value.

rcskip (IN) - skip parameter for the next return code.

COMMENTS

This call specifies additional attributes necessary for an array define, used
in an array of structures (multi-row, multi-column) fetch.  For more
information about skip parameters, see the section "Skip Parameters" on page
5-18.

RELATED FUNCTIONS

OCIDefineByPos(), OCIDefineObject()


---------------------------------------OCIDefineByPos--------------------------


OCIDefineByPos()

NAME

OCI Define By Position

PURPOSE

Associates an item in a select-list with the type and output data buffer. 

SYNTAX

sb4 OCIDefineByPos ( 
              OCIStmt     *stmtp, 
              OCIDefine   **defnp,
              OCIError    *errhp,
              ub4         position,
              dvoid       *valuep,
              sb4         value_sz,
              ub2         dty,
              dvoid       *indp,
              ub2         *rlenp,
              ub2         *rcodep,
              ub4         mode );


PARAMETERS


stmtp (IN) - a handle to the requested SQL query operation.

defnp (IN/OUT) - a pointer to a pointer to a define handle which is implicitly
allocated by this call.  This handle is used to store the define information
for this column.

errhp (IN) - an error handle which can be passed to OCIErrorGet() for
diagnostic information in the event of an error.

position (IN) - the position of this value in the select list. Positions are 
1-based and are numbered from left to right. For example, in the SELECT 
statement

SELECT empno, ssn, mgrno FROM employees;

empno is at position 1, ssn is at position 2, and mgrno is at position 3.

valuep (IN/OUT) - a pointer to a buffer or an array of buffers of the type
specified in the dty parameter. A number of buffers can be specified when
results for more than one row are desired in a single fetch call.

value_sz (IN) - the size of each valuep buffer in bytes. If the data is stored
internally in VARCHAR2 format, the number of characters desired, if different
from the buffer size in bytes, may be additionally specified by the using
OCIAttrSet().  In an NLS conversion environment, a truncation error will be
generated if the number of bytes specified is insufficient to handle the number
of characters desired.

dty (IN) - the data type. Named data type (SQLT_NTY) and REF (SQLT_REF) are
valid only if the environment has been intialized with in object mode. For a
listing of datatype codes and values, refer to Chapter 3, "Datatypes".

indp (IN) - pointer to an indicator variable or array. For scalar data types, 
pointer to sb2 or an array of sb2s. Ignored for named data types. For named 
data types, a pointer to a named data type indicator structure or an array of 
named data type indicator structures is associated by a subsequent 
OCIDefineObject() call. 

See the section "Indicator Variables" on page 2-29 for more information about 
indicator variables.

rlenp (IN/OUT) - pointer to array of length of data fetched. Each element in 
rlenp is the length of the data in the corresponding element in the row after 
the fetch. 

rcodep (OUT) - pointer to array of column-level return codes

mode (IN) - the valid modes are:

OCI_DEFAULT. This is the default mode.
OCI_DYNAMIC_FETCH. For applications requiring dynamically 
allocated data at the time of fetch, this mode must be used. The user may 
additionally call OCIDefineDynamic() to set up a callback function that 
will be invoked to receive the dynamically allocated buffers and to set 
up the memory allocate/free callbacks and the context for the callbacks. 
valuep and value_sz are ignored in this mode. 

COMMENTS

This call defines an output buffer which will receive data retreived from 
Oracle. The define is a local step which is necessary when a SELECT statement 
returns data to your OCI application.

This call also implicitly allocates the define handle for the select-list item.
Defining attributes of a column for a fetch is done in one or more calls. The 
first call is to OCIDefineByPos(), which defines the minimal attributes 
required to specify the fetch. 
This call takes as a parameter a define handle, which must have been 
previously allocated with a call to OCIHandleAlloc().
Following the call to OCIDefineByPos() additional define calls may be 
necessary for certain data types or fetch modes:
A call to OCIDefineArrayOfStruct() is necessary to set up skip parameters 
for an array fetch of multiple columns.
A call to OCIDefineObject() is necessary to set up the appropriate 
attributes of a named data type fetch. In this case the data buffer pointer 
in ocidefn() is ignored.
Both OCIDefineArrayOfStruct() and OCIDefineObject() must be called 
after ocidefn() in order to fetch multiple rows with a column of named 
data types.
For a LOB define, the buffer pointer must be a lob locator of type 
OCILobLocator , allocated by the OCIDescAlloc() call. LOB locators, and not 
LOB values, are always returned for a LOB column. LOB values can then be 
fetched using OCI LOB calls on the fetched locator.
For NCHAR (fixed and varying length), the buffer pointer must point to an 
array of bytes sufficient for holding the required NCHAR characters. 
Nested table columns are defined and fetched like any other named data type. 
If the mode parameter is this call is set to OCI_DYNAMIC_FETCH, the client 
application can fetch data dynamically at runtime.
Runtime data can be provided in one of two ways:
callbacks using a user-defined function which must be registered with a 
subsequent call to OCIDefineDynamic(). When the client library needs a 
buffer to return the fetched data, the callback will be invoked and the 
runtime buffers provided will return a piece or the whole data. 
a polling mechanism using calls supplied by the OCI. This mode is 
assumed if no callbacks are defined. In this case, the fetch call returns the 
OCI_NEED_DATA error code, and a piecewise polling method is used 
to provide the data.
RELATED FUNCTIONS: For more information about using the 
OCI_DYNAMIC_FETCH mode, see the section "Runtime Data 
Allocation and Piecewise Operations" on page 5-16 of Volume 1..
For more information about the define step, see the section "Defining" 
on page 2-30.

RELATED FUNCTIONS

OCIDefineArrayOfStruct(), OCIDefineDynamic(), OCIDefineObject()


---------------------------------OCIDefineDynamic------------------------------


OCIDefineDynamic()

NAME

OCI Define Dynamic Fetch Attributes

PURPOSE

This call is used to set the additional attributes required if the 
OCI_DYNAMIC_FETCH mode was selected in OCIDefineByPos(). 

SYNTAX

sword OCIDefineDynamic( OCIDefine   *defnp,
                      OCIError    *errhp,
                      dvoid       *octxp, 
                      OCICallbackDefine (ocbfp)(/o_
                                  dvoid             *octxp,
                                  OCIDefine         *defnp,
                                  ub4               iter, 
                                  dvoid             **bufpp,
                                  ub4               **alenpp,
                                  ub1               *piecep,
                                  dvoid             **indpp,
                                  ub2               **rcodep _o/)  );


PARAMETERS


defnp (IN/OUT) - the handle to a define structure returned by a call to 
OCIDefineByPos().

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

octxp (IN) - points to a context for the callback function. 

ocbfp (IN) - points to a callback function. This is invoked at runtime to get 
a pointer to the buffer into which the fetched data or a piece of it will be 
retreived. The callback also specifies the indicator, the return code and the 
lengths of the data piece and indicator. The callback has the following 
parameters:

octxp (IN) - a context pointer passed as an argument to all the callback 
functions.

defnp (IN) - the define handle.

iter (IN) - which row of this current fetch.

bufpp (OUT) - returns a pointer to a buffer to store the column value, ie. 
*bufp points to some appropriate storage for the column value.

alenpp (OUT) - returns a pointer to the length of the buffer. *alenpp 
contains the size of the buffer after return from callback. Gets set to 
actual data size after fetch.

piecep (IN/OUT) - returns a piece value, as follows:

The IN value can be OCI_ONE_PIECE, OCI_FIRST_PIECE or OCI_NEXT_PIECE.

The OUT value can be OCI_ONE_PIECE if the IN value was OCI_ONE_PIECE.

The OUT value can be OCI_ONE_PIECE or OCI_FIRST_PIECE if the IN value was
OCI_FIRST_PIECE.

The OUT value can only be OCI_NEXT_PIECE or OCI_LAST_PIECE if the IN value was
OCI_NEXT_PIECE.

indpp (IN) - indicator variable pointer

rcodep (IN) - return code variable pointer

COMMENTS

This call is used to set the additional attributes required if the 
OCI_DYNAMIC_FETCH mode has been selected in a call to 
OCIDefineByPos(). 
When the OCI_DYNAMIC_FETCH mode is selected, buffers will be 
dynamically allocated for REF, and named data type, values to receive the 
data. The pointers to these buffers will be returned. 
If OCI_DYNAMIC_FETCH mode was selected, and the call to 
OCIDefineDynamic() is skipped, then the application can fetch data piecewise 
using OCI calls.
For more information about OCI_DYNAMIC_FETCH mode, see the section 
"Runtime Data Allocation and Piecewise Operations" on page 7-16.

RELATED FUNCTIONS

OCIDefineObject()


-------------------------------------------------------------------------------


OCIDefineObject()

NAME

OCI Define Named Data Type attributes

PURPOSE

Sets up additional attributes necessary for a Named Data Type define.

SYNTAX

sword OCIDefineObject ( OCIDefine       *defnp,
                      OCIError        *errhp,
                      CONST OCIType   *type,
                      dvoid           **pgvpp, 
                      ub4             *pvszsp, 
                      dvoid           **indpp, 
                      ub4             *indszp );


PARAMETERS


defnp (IN/OUT) - a define handle previously allocated in a call to 
OCIDefineByPos(). 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.
type (IN, optional) - points to the Type Descriptor Object (TDO) which 
describes the type of the program variable. Only used for program variables 
of type SQLT_NTY. This parameter is optional, and may be passed as NULL 
if it is not being used.

pgvpp (IN/OUT) - points to a pointer to a program variable buffer. For an 
array, pgvpp points to an array of pointers. Memory for the fetched named data 
type instance(s) is dynamically allocated in the object cache. At the end of the 
fetch when all the values have been received, pgvpp points to the pointer(s) to
these newly allocated named data type instance(s). The application must call 
OCIObjectMarkDel() to deallocate the named data type instance(s) when they 
are no longer needed. 

pvszsp (IN/OUT) - points to the size of the program variable. For an array, it 
is an array of ub4s. On return points to the size(s) of unpickled fetched 
values.

indpp (IN/OUT) - points to a pointer to the program variable buffer 
containing the parallel indicator structure. For an array, points to an array 
of pointers. Memory is allocated to store the indicator structures in the 
object cache. At the end of the fetch when all values have been received, 
indpp points to the pointer(s) to these newly allocated indicator structure(s).

indszp (IN/OUT) - points to the size(s) of the indicator structure program 
variable. For an array, it is an array of ub4s. On return points to the size(s)
of the unpickled fetched indicator values.

COMMENTS

This call sets up additional attributes necessary for a Named Data Type define.An error will be returned if this function is called when the OCI environment 
has been initialized in non-Object mode.
This call takes as a paramter a type descriptor object (TDO) of datatype 
OCIType for the named data type being defined.  The TDO can be retrieved 
with a call to OCITypeByName().
See the description of OCIInitialize() on page 13 - 43 for more information 
about initializing the OCI process environment.

RELATED FUNCTIONS

OCIDefineByPos()

-------------------------------------------------------------------------------

OCIDescribeAny()

NAME

OCI Describe Any

PURPOSE

Describes existing schema objects.

SYNTAX

sword OCIDescribeAny ( OCISvcCtx     *svchp,
                       OCIError      *errhp,
                       dvoid         *objptr,
                       ub4           objptr_len,
                       ub1           objptr_typ,
                       ub1           info_level,
		       ub1           objtype,
                       OCIDesc       *dschp );

PARAMETERS


svchp (IN)

A service context handle. 

errhp (IN/OUT)

An error handle which can be passed to OCIErrorGet() for diagnostic information
in the event of an error.

objptr (IN)

This parameter can be either 

   1.a string containing the name of the schema object to be described 
   2.a pointer to a REF to the TDO (for a type) 
   3.a pointer to a TDO (for a type). 

These cases are distinguished by passing the appropriate value for
objptr_typ. This parameter must be non-NULL.

In case 1, the string containing the object name should be in the format
<schema-name>.<object-name>. No database links are allowed.

The object name is interpreted by the following SQL rules: 

     If <schema-name> is NULL, the name refers to the object (of type table /
     view / procedure / function / package / type / synonym / sequence) with
     name described by <object-name> in the schema of the current user. When
     connected to an Oracle7 Server, the only valid types are procedure and
     function.  

     If <schema-name> is non-NULL, the name refers to the object
     with name described by <object-name>, in the schema with name described by
     <schema-name>.  objnm_len (IN)

The length of the name string pointed to by objptr. Must be non-zero if a name
is passed.  Can be zero if objptr is a pointer to a TDO or its REF.

objptr_typ (IN)

The type of object passed in objptr. Valid values are: 

     OCI_OTYPE_NAME, if objptr points to the name of a schema object 
     OCI_OTYPE_REF, if objptr is a pointer to a REF to a TDO 
     OCI_OTYPE_PTR, if objptr is a pointer to a TDO info_level (IN)

Reserved for future extensions. Pass OCI_DEFAULT. 

objtyp (IN/OUT)

The type of schema object being described. Valid values are: 

     OCI_PTYPE_TABLE, for tables 
     OCI_PTYPE_VIEW, for views 
     OCI_PTYPE_PROC, for procedures 
     OCI_PTYPE_FUNC, for functions 
     OCI_PTYPE_PKG, for packages 
     OCI_PTYPE_TYPE, for types 
     OCI_PTYPE_SYN, for synonyms 
     OCI_PTYPE_SEQ, for sequences 
     OCI_PTYPE_UNK, for unknown schema objects 

A value for this argument must be specified. If OCI_PTYPE_UNK is specified,
then the description of an object with the specified name in the current schema
is returned, if such an object exists, along with the actual type of the
object.

dschp (IN/OUT)

A describe handle that is populated with describe information about the object
after the call.  Must be non-NULL.

COMMENTS

This is a generic describe call that describes existing schema objects: tables,
views, synonyms, procedures, functions, packages, sequences, and types. This
call populates the describe handle with the object-specific attributes which
can be obtained through an OCIAttrGet() call.

An OCIParamGet() on the describe handle returns a parameter descriptor for a
specified position. Parameter positions begin with 1. Calling OCIAttrGet() on
the parameter descriptor returns the specific attributes of a stored procedure
or function parameter or a table column descriptor as the case may be.

These subsequent calls do not need an extra round trip to the server because
the entire schema object description cached on the client side by
OCIDescribeAny(). Calling OCIAttrGet() on the describe handle can also return
the total number of positions.

See Chapter 6, "Describing Schema Metadata", for more information about
describe operations.

RELATED FUNCTIONS

OCIAQEnq(), OCIParamGet() 



-------------------------------------------------------------------------------


OCIDescriptorAlloc()

NAME

OCI Descriptor or lob locators Allocate

PURPOSE

Allocates storage to hold certain data types. The descriptors can be used as
bind or define variables.

SYNTAX

sword OCIDesccriptorAlloc ( CONST dvoid   *parenth,
                            dvoid         **descpp, 
                            ub4           type,
                            size_t        xtramem_sz,
                            dvoid         **usrmempp);

PARAMETERS

parenth (IN) - an environment handle. 

descpp (OUT) - returns a descriptor or LOB locator of desired type. 

type (IN) - specifies the type of descriptor or LOB locator to be allocated. 
The specific types are:

     OCI_DTYPE_SNAP - specifies generation of snapshot descriptor of C type
     OCISnapshot 
     OCI_DTYPE_LOB - specifies generation of a LOB value type locator 
     (for a BLOB or CLOB) of C type OCILobLocator 
     OCI_DTYPE_FILE - specifies generation of a FILE value type locator of 
     C type OCILobLocator. 
     OCI_DTYPE_ROWID - specifies generation of a ROWID descriptor of C type
     OCIRowid. 
     OCI_DTYPE_COMPLEXOBJECTCOMP - specifies generation of a complex object
     retrieval descriptor of C type OCIComplexObjectComp. 
     OCI_DTYPE_AQENQ_OPTIONS - specifies generation of an advanced queueing
     enqueue options descriptor of C type OCIAQEnqOptions. 
     OCI_DTYPE_AQDEQ_OPTIONS - specifies generation of an advanced queueing
     dequeue options descriptor of C type OCIAQDeqOptions. 
     OCI_DTYPE_AQMSG_PROPERTIES - specifies generation of an advanced queueing
     message properties descriptor of C type OCIAQMsgProperties. 
     OCI_DTYPE_AQAGENT - specifies generation of an advanced queueing agent
     descriptor of C type OCIAQAgent.

xtramemsz (IN) - specifies an amount of user memory to be allocated for use by
the application.

usrmempp (OUT) - returns a pointer to the user memory of size xtramemsz 
allocated by the call for the user. 

COMMENTS

Returns a pointer to an allocated and initialized structure, corresponding to 
the type specified in type. A non-NULL descriptor or LOB locator is returned 
on success. No diagnostics are available on error.

This call returns OCI_SUCCESS if successful, or OCI_INVALID_HANDLE if an
out-of-memory error occurs.

For more information about the xtramem_sz parameter and user memory allocation,
refer to "User Memory Allocation" on page 2-12.

RELATED FUNCTIONS

OCIDescriptorFree()


-------------------------------------------------------------------------------


OCIDescriptorFree()

NAME

OCI Descriptor Free

PURPOSE

Deallocates a previously allocated descriptor.

SYNTAX

sword OCIDescriptorFree ( dvoid    *descp,
                          ub4      type);


PARAMETERS


descp (IN) - an allocated descriptor. 

type (IN) - specifies the type of storage to be freed. The specific types are: 

     OCI_DTYPE_SNAP - snapshot descriptor 
     OCI_DTYPE_LOB - a LOB value type descriptor 
     OCI_DTYPE_FILE - a FILE value type descriptor 
     OCI_DTYPE_ROWID - a ROWID descriptor 
     OCI_DTYPE_COMPLEXOBJECTCOMP - a complex object retrieval descriptor 
     OCI_DTYPE_AQENQ_OPTIONS - an AQ enqueue options descriptor 
     OCI_DTYPE_AQDEQ_OPTIONS - an AQ dequeue options descriptor 
     OCI_DTYPE_AQMSG_PROPERTIES - an AQ message properties descriptor 
     OCI_DTYPE_AQAGENT - an AQ agent descriptor 

COMMENTS

This call frees up storage associated with the descriptor, corresponding to the
type specified in type. Returns OCI_SUCCESS or OCI_INVALID_HANDLE.  All
descriptors must be explicitly deallocated. OCI will not deallocate a
descriptor if the environment handle is deallocated.

RELATED FUNCTIONS

OCIDescriptorAlloc()

-------------------------------------------------------------------------------


OCIEnvInit()

Name

OCI Environment Initialize

PURPOSE

This call initializes the OCI environment handle.

SYNTAX

sword OCIEnvInit ( OCIEnv    **envp,
                   ub4       mode,
                   size_t    xtramemsz,
                   dvoid     **usrmempp );


PARAMETERS

envpp (OUT) - a pointer to a handle to the environment. 

mode (IN) - specifies initialization of an environment mode. The only valid 
mode is OCI_DEFAULT for default mode

xtramemsz (IN) - specifies the amount of user memory to be allocated. 

usrmempp (OUT) - returns a pointer to the user memory of size xtramemsz 
allocated by the call for the user.


COMMENTS
This call allocates and initializes an OCI environment handle. No changes are
done to an already initialized handle. If OCI_ERROR or OCI_SUCCESS_WITH_INFO is
returned, the environment handle can be used to obtain ORACLE specific errors
and diagnostics.

This call is processed locally, without a server round-trip.

The environment handle can be freed using OCIHandleFree(). 

For more information about the xtramemsz parameter and user memory allocation,
refer to "User Memory Allocation" on page 2-12.

RELATED FUNCTIONS

OCIHandleAlloc(), OCIHandleFree() 




-------------------------------------------------------------------------------


OCIErrorGet()

NAME

OCI Error Get diagnostic records

PURPOSE

Returns an error message in the buffer provided and an ORACLE error.

SYNTAX

sword OCIErrorGet ( dvoid      *hndlp, 
                    ub4        recordno,
                    text       *sqlstate,
                    ub4        *errcodep, 
                    text       *bufp,
                    ub4        bufsiz,
                    ub4        type );


PARAMETERS

hndlp (IN) - the error handle, in most cases, or the environment handle (for 
errors on OCIEnvInit(), OCIHandleAlloc()).

recordno (IN) - indicates the status record from which the application seeks 
info. Starts from 1. 

sqlstate (OUT) - Not supported in Version 8.0.

errcodep (OUT) - an ORACLE Error is returned.

bufp (OUT) - the error message text is returned.

bufsiz (IN) - the size of the buffer provide to get the error message.

type (IN) - the type of the handle.

COMMENTS

Returns an error message in the buffer provided and an ORACLE error. 
Currently does not support SQL state. This call can be called a multiple 
number of times if there are more than one diagnostic record for an error.

The error handle is originally allocated with a call to OCIHandleAlloc().

EXAMPLE

The following sample code demonstrates how you can use OCIErrorGet() in an
error-handling routine. This routine prints out the type of status code
returned by an OCI function, and if an error occurred, OCIErrorGet() retrieves
the text of the message, which is printed.

static void checkerr(errhp, status)

OCIError *errhp;

sword status;

{

  text errbuf[512];

  ub4 buflen;

  ub4 errcode;


switch (status)

  {

  case OCI_SUCCESS:

    break;

  case OCI_SUCCESS_WITH_INFO:

    printf("ErrorOCI_SUCCESS_WITH_INFO\n");

    break;

  case OCI_NEED_DATA:

    printf("ErrorOCI_NEED_DATA\n");

    break;

  case OCI_NO_DATA:

    printf("ErrorOCI_NO_DATA\n");

    break;

  case OCI_ERROR:

    OCIErrorGet ((dvoid *) errhp, (ub4) 1, (text *) NULL, &errcode,

            errbuf, (ub4) sizeof(errbuf), (ub4) OCI_HTYPE_ERROR);

    printf("Error%s\n", errbuf);

    break;

  case OCI_INVALID_HANDLE:

    printf("ErrorOCI_INVALID_HANDLE\n");

    break;

  case OCI_STILL_EXECUTING:

    printf("ErrorOCI_STILL_EXECUTE\n");

    break;

  case OCI_CONTINUE:

    printf("ErrorOCI_CONTINUE\n");

    break;

  default:

    break;

  }

}

RELATED FUNCTIONS

OCIHandleAlloc()




-------------------------------------------------------------------------------



OCIHandleAlloc()

NAME

OCI Handle Allocate 

PURPOSE

This call returns a pointer to an allocated and initialized handle.

SYNTAX

sword OCIHandleAlloc ( CONST dvoid   *parenth,
                       dvoid         **hndlpp, 
                       ub4           type, 
                       size_t        xtramem_sz,
                       dvoid         **usrmempp);


PARAMETERS


parenth (IN) - an environment or a statement handle. 

hndlpp (OUT) - returns a handle to a handle type. 

type (IN) - specifies the type of handle to be allocated. The specific types 
are: 

     OCI_HTYPE_ERROR - specifies generation of an error report handle of C type
     OCIError 
     OCI_HTYPE_SVCCTX - specifies generation of a service context handle of C 
     type OCISvcCtx 
     OCI_HTYPE_STMT - specifies generation of a statement (application request)
     handle of C type OCIStmt 
     OCI_HTYPE_DESCRIBE - specifies generation of a select list description 
     handle of C type OCIDescribe 
     OCI_HTYPE_SERVER - specifies generation of a server context handle of C 
     type OCIServer 
     OCI_HTYPE_SESSION - specifies generation of a user session handle of C 
     type OCISession 
     OCI_HTYPE_TRANS - specifies generation of a transaction context handle 
     of C type OCITrans 
     OCI_HTYPE_COMPLEXOBJECT - specifies generation of a complex object 
     retrieval handle of C type OCIComplexObject 
     OCI_HTYPE_SECURITY - specifies generation of a security handle of C type
     OCISecurity


xtramem_sz (IN) - specifies an amount of user memory to be allocated.

usrmempp (OUT) - returns a pointer to the user memory of size xtramemsz 
allocated by the call for the user. 

COMMENTS

Returns a pointer to an allocated and initialized structure, corresponding to 
the type specified in type. A non-NULL handle is returned on success. Bind 
handle and define handles are allocated with respect to a statement handle. All
other handles are allocated with respect to an environment handle which is 
passed in as a parent handle.

No diagnostics are available on error. This call returns OCI_SUCCESS if 
successful, or OCI_INVALID_HANDLE if an out-of-memory error occurs.

Handles must be allocated using OCIHandleAlloc() before they can be passed 
into an OCI call.

To allocate and initialize an environment handle, call OCIEnvInit(). 

     See Also: For more information about using the xtramem_sz parameter for
     user memory allocation, refer to "User Memory Allocation" on page 2-12.

EXAMPLE

The following sample code shows OCIHandleAlloc() being used to allocate a
variety of handles at the beginning of an application:

OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, (ub4) 
               OCI_HTYPE_ERROR, 0, (dvoid **) &tmp);
OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, (ub4) 
               OCI_HTYPE_SERVER, 0, (dvoid **) &tmp);
OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, (ub4) 
               OCI_HTYPE_SVCCTX, 0, (dvoid **) &tmp);

RELATED FUNCTIONS

OCIHandleFree(), OCIEnvInit()


-------------------------------------------------------------------------------


OCIHandleFree()

NAME

OCI Handle Free

PURPOSE

This call explicitly deallocates a handle.

SYNTAX

sword OCIHandleFree ( dvoid     *hndlp,
                      ub4       type);


PARAMETERS


hndlp (IN) - an opaque pointer to some storage.

type (IN) - specifies the type of storage to be allocated. The specific types are:
OCI_HTYPE_ENV - an environment handle
OCI_HTYPE_ERROR - an error report handle
OCI_HTYPE_SVCCTX - a service context handle
OCI_HTYPE_STMT - a statement (application request) handle
OCI_HTYPE_BIND - a bind information handle
OCI_HTYPE_DEFINE - a column definition handle
OCI_HTYPE_DESCRIBE  - a select list description handle
OCI_HTYPE_SERVER - a server handle
OCI_HTYPE_SESSION - a user authentication handle
OCI_HTYPE_TRANS - a transaction handle
OCI_HTYPE_COMPLEXOBJECT - a complex object retrieval handle
OCI_HTYPE_SECURITY - a security handle

COMMENTS

This call frees up storage associated with a handle, corresponding to the type 
specified in the type parameter.
This call returns either OCI_SUCCESS or OCI_INVALID_HANDLE.
All handles must be explicitly deallocated. OCI will not deallocate a child 
handle if the parent is deallocated.

RELATED FUNCTIONS

OCIHandleAlloc()



-------------------------------------------------------------------------------

OCIInitialize()

NAME

OCI Process Initialize

PURPOSE

Initializes the OCI process environment.

SYNTAX

sword OCIInitialize ( ub4           mode,
                    CONST dvoid   *ctxp, 
                    CONST dvoid   *(*malocfp) 
                                  ( dvoid *ctxp,
                                    size_t size ),
                    CONST dvoid   *(*ralocfp)
                                  ( dvoid *ctxp,
                                    dvoid *memp,
                                    size_t newsize ),
                    CONST void    (*mfreefp)
                                  ( dvoid *ctxp,
                                    dvoid *memptr ));


PARAMETERS


mode (IN) - specifies initialization of the mode. The valid modes are:
  OCI_DEFAULT - default mode.
  OCI_THREADED - threaded environment. In this mode, internal data 
  structures are protected from concurrent accesses by multiple threads. 
  OCI_OBJECT - will use navigational object interface. 

ctxp (IN) - user defined context for the memory call back routines. 

malocfp (IN) - user-defined memory allocation function. If mode is 
OCI_THREADED, this memory allocation routine must be thread safe.
  ctxp - context pointer for the user-defined memory allocation function.
  size - size of memory to be allocated by the user-defined memory 
         allocation function

ralocfp (IN) - user-defined memory re-allocation function. If mode is 
OCI_THREADED, this memory allocation routine must be thread safe.
  ctxp - context pointer for the user-defined memory reallocation 
         function.
  memp - pointer to memory block
  newsize - new size of memory to be allocated

mfreefp (IN) - user-defined memory free function. If mode is 
OCI_THREADED, this memory free routine must be thread safe.
  ctxp - context pointer for the user-defined memory free function.
  memptr - pointer to memory to be freed


EXAMPLE
See the description of OCIStmtPrepare() on page 13-96 for an example showing 
the use of OCIInitialize().

COMMENTS

This call initializes the OCI process environment.
OCIInitialize() must be invoked before any other OCI call. 

RELATED FUNCTIONS
OCIEnvInit()





-------------------------------------------------------------------------------

OCILdaToSvcCtx()

NAME

OCI toggle version 7 Lda_Def to SerVice context handle

PURPOSE

Converts a V7 Lda_Def to a V8 service context handle.

SYNTAX

sword OCILdaToSvcCtx ( OCISvcCtx  **svchpp,
                       OCIError   *errhp,
                       Lda_Def    *ldap );


PARAMETERS

svchpp (IN/OUT) - the service context handle. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

ldap (IN/OUT) - the V7 logon data area returned by OCISvcCtxToLda() from 
this service context.

COMMENTS

Converts a V7 Lda_Def to a V8 service context handle. The action of this call 
can be reversed by passing the resulting service context handle to the 
OCISvcCtxToLda() function.

If the Service context has been converted to an Lda_Def, only Oracle7 calls may
be used. It is illegal to make Oracle8 OCI calls without first resetting the
Lda_Def to a service context.

The OCI_ATTR_IN_V8_MODE attribute of the server handle or service context
handle enables an application to determine whether the application is currently
in Oracle7 mode or Oracle8 mode. See Appendix B, "Handle and Descriptor
Attributes", for more information.

RELATED FUNCTIONS

OCISvcCtxToLda()



-------------------------------------------------------------------------------

OCILobAppend()


NAME

OCI Lob APpend

PURPOSE

Appends a LOB value at the end of another LOB. 

SYNTAX
sword OCILobAppend ( OCISvcCtx        *svchp,
                     OCIError         *errhp,
                     OCILobLocator    *dst_locp,
                     OCILobLocator    *src_locp );


PARAMETERS

svchp (IN) - the service context handle. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

dst_locp (IN/OUT) - a locator uniquely referencing the destination LOB. 

src_locp (IN/OUT) - a locator uniquely referencing the source LOB. 


COMMENTS

Appends a LOB value at the end of LOB. The data is 
copied from the source to the destination at the end of the destination. The 
source and the destination must already exist. The destination LOB is 
extended to accommodate the newly written data.

It is an error to extend the destination LOB beyond the maximum length 
allowed or to try to copy from a NULL LOB. 

Both the source and the destination LOB locators must be of the same type
(i.e., they must both be BLOBs or both be CLOBs). LOB buffering must not be
enabled for either type of locator.

This function does not accept a FILE locator as the source or the destination. 

RELATED FUNCTIONS

OCILobTrim()
OCIErrorGet()
OCILobWrite()
OCILobCopy()


-------------------------------------------------------------------------------

OCILobAssign()


NAME

OCI Lob ASsiGn



PURPOSE

Assigns one LOB/FILE locator to another.


SYNTAX
sword OCILobAssign ( OCIEnv                *envhp, 
                     OCIError              *errhp, 
                     CONST OCILobLocator   *src_locp, 
                     OCILobLocator         **dst_locpp );



PARAMETERS

envhp (IN/OUT) - OCI environment handle initialized in object mode.

errhp (IN/OUT) - The OCI error handle. If there is an error, it is recorded 
in errhp and this function returns OCI_ERROR. Diagnostic information can be 
obtained by calling OCIErrorGet().

src_locp (IN) - LOB locator to copy from.

dst_locpp (IN/OUT) - LOB locator to copy to.  The caller must allocate space 
for the OCILobLocator by calling OCIDescriptorAlloc().

COMMENTS

Assign source locator to destination locator. After the assignment, both
locators refer to the same LOB value. For internal LOBs, the source locator's
LOB value gets copied to the destination locator's LOB value only when the
destination locator gets stored in the table.  Therefore, issuing a flush of
the object containing the destination locator will copy the LOB value.

For FILEs, only the locator that refers to the file is copied to the table. The
OS file itself is not copied.

It is an error to assign a FILE locator to an internal LOB locator, and vice
versa.

If the source locator is for an internal LOB that was enabled for buffering,
and the source locator has been used to modify the LOB data through the LOB
buffering subsystem, and the buffers have not been flushed since the write,
then the source locator may not be assigned to the destination locator. This is
because only one locator per LOB may modify the LOB data through the LOB
buffering subsystem.

The value of the input destination locator must either be NULL, or it must have
already been allocated with a call to OCIDescriptorAlloc(). For example, assume
the following declarations:

OCILobLocator         *source_loc = (OCILobLocator *) 0;
OCILobLocator         *dest_loc = (OCILobLocator *) 0;


An application could allocate the source_loc locator as follows: 

if (OCIDescriptorAlloc((dvoid *) envhp, (dvoid **) &source_loc,
                       (ub4) OCI_DTYPE_LOB, (size_t) 0, (dvoid **) 0))
    handle_error;


Assume that it then selects a LOB from a table into the source_loc in order to
initialize it. The application could then do one of the following to assign the
value of source_loc to dest_loc:

   1.Pass in NULL for the value of the destination locator and let 
     OCILobAssign() allocate space for dest_loc and copy the source into it: 

     if (OCILobAssign(envhp, errhp, source_loc, &dest_loc)) 
             handle_error;


   2.Allocate dest_loc, and pass the preallocated destination locator to
     OCILobAssign(): 

     if (OCIDescriptorAlloc((dvoid *) envhp, (dvoid **) &dest_loc,

             (ub4)OCI_DTYPE_LOB, (size_t) 0, (dvoid **) 0))
             handle_error;
     if (OCILobAssign(envhp, errhp, source_loc, &dest_loc)) 
             handle_error;


RELATED FUNCTIONS
OCIErrorGet(), OCILobIsEqual(), OCILobLocatorIsInit(), OCILobEnableBuffering() 



-------------------------------------------------------------------------------

OCILobCharSetForm()

NAME
OCI Lob Get Character Set Form

PURPOSE
Gets the LOB locator's character set form, if any.

SYNTAX
sword OCILobCharSetForm ( OCIEnv                    *envhp, 
                          OCIError                  *errhp, 
                          CONST OCILobLocator       *locp, 
                          ub1                       *csfrm );

PARAMETERS

envhp (IN/OUT) - OCI environment handle initialized in object mode.

errhp (IN/OUT) - error handle. The OCI error handle. If there is an error, it 
is recorded in err and this function returns OCI_ERROR. Diagnostic 
information can be obtained by calling OCIErrorGet().

locp (IN) - LOB locator for which to get the character set form.

csfrm(OUT) - character set form of the input LOB locator.  If the input 
locator is for a BLOB or a BFILE, csfrm is set to 0 since there is no concept 
of a character set for binary LOBs/FILEs.  The caller must allocate space for 
the csfrm (ub1) and not write into the space.

COMMENTS

Returns the character set form of the input LOB locator in the csfrm output
parameter. This function makes sense only for character LOBs (i.e., CLOBs and
NCLOBs).

RELATED FUNCTIONS

OCIErrorGet(), OCILobCharSetId(), OCILobLocatorIsInit() 


-------------------------------------------------------------------------------

OCILobCharSetId()

NAME
OCI Lob get Character Set Identifier

PURPOSE
Gets the LOB locator's character set ID, if any.

SYNTAX
sword OCILobCharSetId ( OCIEnv                    *envhp, 
                        OCIError                  *errhp, 
                        CONST OCILobLocator       *locp, 
                        ub2                       *csid );

PARAMETERS

envhp (IN/OUT) - OCI environment handle initialized in object mode.

errhp (IN/OUT) - error handle. The OCI error handle. If there is an error, it 
is recorded in err and this function returns OCI_ERROR. Diagnostic 
information can be obtained by calling OCIErrorGet().

locp (IN) - LOB locator for which to get the character set ID.

csid (OUT) - character set ID of the input LOB locator.  If the input locator 
is for a BLOB or a BFILE, csid is set to 0 since there is no concept of a 
character set for binary LOBs/FILEs.  The caller must allocate space for the 
character set id of type ub2 and not write into the space.

COMMENTS

Returns the character set ID of the input LOB locator in the csid output parameter. 

This function makes sense only for character LOBs (i.e., CLOBs, NCLOBs). 

RELATED FUNCTIONS
OCIErrorGet(), OCILobCharSetForm(), OCILobLocatorIsInit() 


-------------------------------------------------------------------------------

OCILobCopy()

NAME
OCI Lob Copy

PURPOSE
Copies a portion of a LOB value into another LOB value.

SYNTAX
sword OCILobCopy ( OCISvcCtx        *svchp,
                   OCIError         *errhp,
                   OCILobLocator    *dst_locp,
                   OCILobLocator    *src_locp,
                   ub4              amount,
                   ub4              dst_offset,
                   ub4              src_offset );

PARAMETERS

svchp (IN) - the service context handle. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

dst_locp (IN/OUT) - a locator uniquely referencing the destination LOB. 

src_locp (IN/OUT) - a locator uniquely referencing the source LOB. 

amount (IN) - the number of character or bytes, as appropriate, to be copied.

dst_offset (IN) - this is the absolute offset for the destination LOB. 
For character LOBs it is the number of characters from the beginning of the 
LOB at which to begin writing. For binary LOBs it is the number of bytes from 
the beginning of the lob from which to begin reading. The offset starts at 1.

src_offset (IN) - this is the absolute offset for the source LOB. 
For character LOBs it is the number of characters from the beginning of the 
LOB, for binary LOBs it is the number of bytes. Starts at 1.

COMMENTS

Copies all or a portion of an internal LOB value into another internal LOB as
specified. The data is copied from the source to the destination. The source
(src_locp) and the destination (dst_locp) LOBs must already exist.

If the data already exists at the destination's start position, it is
overwritten with the source data. If the destination's start position is beyond
the end of the current data, zero-byte fillers (for BLOBs) or spaces (for
CLOBs) are written into the destination LOB from the end of the current data to
the beginning of the newly written data from the source. The destination LOB is
extended to accommodate the newly written data if it extends beyond the current
length of the destination LOB. It is an error to extend the destination LOB
beyond the maximum length allowed (i.e., 4 gigabytes) or to try to copy from a
NULL LOB.

Both the source and the destination LOB locators must be of the same type
(i.e., they must both be BLOBs or both be CLOBs). LOB buffering must not be
enabled for either locator.

This function does not accept a FILE locator as the source or the destination. 

The amount parameter indicates the maximum amount to copy. If the end of the
source LOB is reached before the specified amount is copied, the operation
terminates without error. This makes it possible to copy from a starting offset
to the end of the LOB without first needing to determine the length of the LOB.

Note: You can call OCILobGetLength() to determine the length of the source LOB.

RELATED FUNCTIONS

OCIErrorGet(), OCILobAppend(), OCILobTrim(), OCILobWrite() 

-------------------------------------------------------------------------------


OCILobDisableBuffering()

NAME
OCI Lob Disable Buffering

PURPOSE
Disable lob buffering for the input locator.

SYNTAX
sword OCILobDisableBuffering ( OCISvcCtx      *svchp,
                               OCIError       *errhp,
                               OCILobLocator  *locp);

PARAMETERS

svchp (IN) - the service context handle. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

locp (IN/OUT) - a locator uniquely referencing the LOB. 


COMMENTS

Disable lob buffering for the input locator.  The next time data is
read/written from/to the lob through the input locator, the lob
buffering subsystem is *not* used.  Note that this call does *not*
implicitly flush the changes made in the buffering subsystem.  The 
user must explicitly call OCILobFlushBuffer() to do this.

This function does not accept a FILE locator. 

RELATED FUNCTIONS
OCILobEnableBuffering()
OCIErrorGet()
OCILobFlushBuffer()


-------------------------------------------------------------------------------

OCILobEnableBuffering()

NAME

OCI Lob Enable Buffering

PURPOSE

Enable lob buffering for the input locator.

SYNTAX
sword OCILobEnableBuffering ( OCISvcCtx      *svchp,
                              OCIError       *errhp,
                              OCILobLocator  *locp);

PARAMETERS

svchp (IN) - the service context handle. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

locp (IN/OUT) - a locator uniquely referencing the LOB. 

COMMENTS

Enable lob buffering for the input locator.  The next time data is
read/written from/to the lob through the input locator, the lob
buffering subsystem is used.  

Once lob buffering is enabled for a locator, if that locator is passed to one
of the following routines, an error is returned: OCILobCopy, OCILobAppend,
OCILobErase, OCILobGetLength, OCILobTrim or OCILobLoadFromFile().

This function does not accept a FILE locator.


RELATED FUNCTIONS
OCILobDisableBuffering()
OCIErrorGet()
OCILobWrite()
OCILobRead()
OCILobFlushBuffer()


-------------------------------------------------------------------------------


OCILobErase()


NAME

OCI Lob ERase

PURPOSE

Erases a specified portion of the LOB data starting at a specified offset.

SYNTAX
sword OCILobErase ( OCISvcCtx       *svchp,
                    OCIError        *errhp,
                    OCILobLocator   *locp,
                    ub4             *amount,
                    ub4             offset );

PARAMETERS

svchp (IN) - the service context handle.

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

locp (IN/OUT) - the LOB for which to erase a section of data.

amount (IN/OUT) - On IN, the number of characters/bytes to erase. On OUT, 
the actual number of characters/bytes erased.

offset (IN) - absolute offset from the beginning of the LOB data from which 
to start erasing data. Starts at 1.

COMMENTS

Erases a specified portion of the internal LOB data starting at a specified
offset. The actual number of characters/bytes erased is returned. The actual
number of characters/bytes and the requested number of characters/bytes will
differ if the end of the LOB value is reached before erasing the requested
number of characters/bytes.

     Note: For BLOBs, erasing means that zero-byte fillers overwrite the
     existing LOB value. For CLOBs, erasing means that spaces overwrite the
     existing LOB value.

If the LOB is NULL, this routine will indicate that 0 characters/bytes were
erased.

This function is valid only for internal LOBs; FILEs are not allowed. 

RELATED FUNCTIONS
OCIErrorGet(), OCILobRead(), OCILobWrite()



-------------------------------------------------------------------------------

OCILobFileClose()

NAME
OCI Lob File Close

PURPOSE
Closes a previously opened FILE.

SYNTAX
sword OCILobFileClose ( OCISvcCtx            *svchp,
                        OCIError             *errhp,
                        OCILobLocator        *filep );

PARAMETERS

svchp (IN) - the service context handle.

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

filep (IN/OUT) - a pointer to a FILE locator to be closed.

COMMENTS

Closes a previously opened FILE. It is an error if this function is called for
an internal LOB.  No error is returned if the FILE exists but is not opened.

This function is only meaningful the first time it is called for a particular
FILE locator.  Subsequent calls to this function using the same FILE locator
have no effect.

     See Also: For more information about FILEs, refer to the description of
     BFILEs in the Oracle8 Application Developer's Guide.

RELATED FUNCTIONS
OCIErrorGet(), OCILobFileOpen(), OCILobFileCloseAll(), OCILobFileIsOpen(),
OCILobFileExists()


-------------------------------------------------------------------------------


OCILobFileCloseAll()

NAME
OCI LOB FILE Close All

PURPOSE
Closes all open FILEs on a given service context.

SYNTAX
sword OCILobFileCLoseAll ( OCISvcCtx *svchp, 
                           OCIError  *errhp );

PARAMETERS

svchp (IN) - the service context handle.

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

COMMENTS

Closes all open FILEs on a given service context.

It is an error to call this function for an internal LOB.

     See Also: For more information about FILEs, refer to the description of
     BFILEs in the Oracle8 Application Developer's Guide.

RELATED FUNCTIONS
OCILobFileClose(), OCIErrorGet(), OCILobFileOpen(), OCILobFileIsOpen(),
OCILobFileExists()


-------------------------------------------------------------------------------

OCILobFileExists()

NAME
OCI LOB FILE exists

PURPOSE
Tests to see if the FILE exists on the server

SYNTAX
sword OCILobFileExists ( OCISvcCtx     *svchp,
                         OCIError      *errhp,
                         OCILobLocator *filep,
                         boolean       *flag );

PARAMETERS

svchp (IN) - the OCI service context handle.

errhp (IN/OUT) - error handle. The OCI error handle. If there is an error, 
it is recorded in err and this function returns OCI_ERROR. Diagnostic 
information can be obtained by calling OCIErrorGet().

filep (IN) - pointer to the FILE locator that refers to the file.

flag (OUT) - returns TRUE if the FILE exists; FALSE if it does not.

COMMENTS

Checks to see if the FILE exists on the server's file system.

It is an error to call this function for an internal LOB.

     See Also: For more information about FILEs, refer to the description of
     BFILEs in the Oracle8 Application Developer's Guide.

RELATED FUNCTIONS 
OCIErrorGet, OCILobFileClose(), OCILobFileCloseAll(), OCILobFileIsOpen()


-------------------------------------------------------------------------------


OCILobFileGetName()

NAME
OCI LOB FILE Get file Name

PURPOSE
Gets the FILE locator's directory alias and file name.

SYNTAX
sword OCILobFileGetName ( OCIEnv                   *envhp,
                          OCIError                 *errhp, 
                          CONST OCILobLocator      *filep, 
                          text                     *dir_alias,
                          ub2                      *d_length, 
                          text                     *filename, 
                          ub2                      *f_length );

PARAMETERS

envhp (IN/OUT) - OCI environment handle initialized in object mode.

errhp (IN/OUT) -The OCI error handle. If there is an error, it is recorded in 
errhp and this function returns OCI_ERROR. Diagnostic information can be 
obtained by calling OCIErrorGet().

filep (IN) - FILE locator for which to get the directory alias and file name.

dir_alias (OUT) - buffer into which the directory alias name is placed. The 
caller must allocate enough space for the directory alias name and must not 
write into the space.

d_length (IN/OUT)                 
        - IN: length of the input dir_alias string;
        - OUT: length of the returned dir_alias string.

filename (OUT) - buffer into which the file name is placed. The caller must 
allocate enough space for the file name and must not write into the space.

f_length (IN/OUT) 
        - IN: length of the input filename string;
         - OUT: lenght of the returned filename string.

COMMENTS

Returns the directory alias and file name associated with this FILE locator. 

It is an error to call this function for an internal LOB. 

     See Also: For more information about FILEs, refer to the description of
     BFILEs in the Oracle8 Application Developer's Guide.

RELATED FUNCTIONS

OCILobFileSetName(), OCIErrorGet() 


-------------------------------------------------------------------------------

OCILobFileIsOpen()

NAME
OCI LOB FILE Is Open

PURPOSE
Tests to see if the FILE is open

SYNTAX
sword OCILobFileIsOpen ( OCISvcCtx *svchp,
                         OCIError  *errhp,
                         OCILobLocator *filep,
                         boolean       *flag );

PARAMETERS

svchp (IN) - the OCI service context handle.

errhp (IN/OUT) - error handle. The OCI error handle. If there is an error, it 
is recorded in err and this function returns OCI_ERROR. Diagnostic 
information can be obtained by calling OCIErrorGet().

filep (IN) - pointer to the FILE locator being examined. If the input file 
locator was never passed to OCILobFileOpen(), the file is considered not to 
be opened by this locator. However, a different locator may have opened the 
file. More than one file opens can be performed on the same file using 
different locators.

flag (OUT) - returns TRUE if the FILE is opened using this locator; FALSE if 
it is not. 

COMMENTS

Checks to see if a file on the server was opened with the filep FILE locator. 

It is an error to call this function for an internal LOB.

If the input FILE locator was never passed to the OCILobFileOpen() command, the
file is considered not to be opened by this locator. However, a different
locator may have the file open. Openness is associated with a particular
locator.

     See Also: For more information about FILEs, refer to the description of
     BFILEs in the Oracle8 Application Developer's Guide.

RELATED FUNCTIONS

OCIErrorGet(), OCILobFileClose(), OCILobFileCloseAll() 


-------------------------------------------------------------------------------

OCILobFileOpen()

NAME
OCI LOB FILE open

PURPOSE
Opens a FILE for read-only access

SYNTAX
sword OCILobFileOpen ( OCISvcCtx            *svchp,
                       OCIError             *errhp,
                       OCILobLocator        *filep,
                       ub1                  mode );

PARAMETERS 

svchp (IN) - the service context handle. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

filep (IN/OUT) - the FILE to open. Error if the locator does not refer to a 
FILE. 

mode (IN) - mode in which to open the file. The only valid mode is 
read-only - OCI_FILE_READONLY. 

COMMENTS

Opens a FILE. The FILE can be opened for read-only access. FILEs may not be
written through Oracle. It is an error to call this function for an internal
LOB.

This function is only meaningful the first time it is called for a particular
FILE locator.  Subsequent calls to this function using the same FILE locator
have no effect.

     See Also: For more information about FILEs, refer to the description of
     BFILEs in the Oracle8 Application Developer's Guide.

RELATED FUNCTIONS

OCILobFileClose(), OCIErrorGet(), OCILobFileIsOpen(), OCILobFileSetName() 


-------------------------------------------------------------------------------

OCILobFileSetName()

NAME
OCI Lob File Set NaMe

PURPOSE
Sets directory alias and file name in the FILE locator.

SYNTAX
sword OCILobFileSetName ( OCIEnv             *envhp,
                          OCIError           *errhp,
                          OCILobLocator      **filepp,
                          text               *dir_alias,
                          ub2                d_length, 
                          text               *filename, 
                          ub2                f_length );
PARAMETERS

envhp (IN/OUT) - OCI environment handle initialized in object mode.

errhp (IN/OUT) - The OCI error handle. If there is an error, it is recorded 
in errhp and this function returns OCI_ERROR. Diagnostic information can be 
obtained by calling OCIErrorGet().

filepp (IN/OUT) - FILE locator for which to set the directory alias name.
The caller must have already allocated space for the locator by calling
OCIDescriptorAlloc().

dir_alias (IN) - buffer that contains the directory alias name to set in the 
locator.

d_length (IN) - length of the input dir_alias parameter.

filename (IN) - buffer that contains the file name is placed.

f_length (IN) - length of the input filename parameter.

COMMENTS

Sets the directory alias and file name in the FILE locator. 

It is an error to call this function for an internal LOB. 

     See Also: For more information about FILEs, refer to the description of
     BFILEs in the Oracle8 Application Developer's Guide.

RELATED FUNCTIONS

OCILobFileGetName(), OCIErrorGet() 

-------------------------------------------------------------------------------


OCILobFlushBuffer()

NAME
OCI Lob Flush all Buffers for this lob.

PURPOSE
Flush/write all buffers for this lob to the server.


SYNTAX
sword OCILobFlushBuffer ( OCISvcCtx       *svchp,
                          OCIError        *errhp,
                          OCILobLocator   *locp,
                          ub4              flag);

PARAMETERS

svchp (IN/OUT) - the service context handle. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

locp (IN/OUT) - a locator uniquely referencing the LOB. 

flag    (IN)     - to indicate if the buffer resources need to be freed
                   after a flush. Default value is OCI_LOB_BUFFER_NOFREE.
                   Set it to OCI_LOB_BUFFER_FREE if you want the buffer
                   resources to be freed.

COMMENTS 

Flushes to the server, changes made to the buffering subsystem that are
associated with the LOB referenced by the input locator. This routine will
actually write the data in the buffer to the LOB in the database. LOB buffering
must have already been enabled for the input LOB locator.

The flush operation, by default, does not free the buffer resources for
reallocation to another buffered LOB operation. However, if you want to free
the buffer explicitly, you can set the flag parameter to OCI_LOB_BUFFER_FREE.

The effects of freeing the buffer are mostly transparent to the user, except
that the next access to the same range in the LOB involves a round-trip to the
server, and also the cost of acquiring buffer resources and initializing it
with the data read from the LOB. This option is intended for the following
situations:

     If the client environment has low on-board memory.  

     If the client application intends to read the buffer value after the flush
     and knows in advance that the current value in the buffer is the desired
     value. In this case there is no need to reread the data from the server.

RELATED FUNCTIONS

OCILobEnableBuffering(), OCIErrorGet(), OCILobWrite(), OCILobRead(),
OCILobDisableBuffering() 


-------------------------------------------------------------------------------

OCILobGetLength()

NAME

OCI Lob/File Length

PURPOSE
Gets the length of a LOB/FILE. 


SYNTAX
sword OCILobGetLength ( OCISvcCtx      *svchp,
                        OCIError       *errhp,
                        OCILobLocator  *locp,
                        ub4            *lenp );



PARAMETERS

svchp (IN) - the service context handle.

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

locp (IN/OUT) - a LOB locator that uniquely references the LOB. For internal
LOBs, this locator must be a locator that was obtained from the server 
specified by svchp. For FILEs, this locator can be initialized by a Select or
OCILobFileSetName.

lenp (OUT) - On output, it is the length of the LOB if not NULL - for 
character LOBs it is the number of characters, for binary LOBs it is the 
number of bytes in the LOB.

COMMENTS

Gets the length of a LOB/FILE. If the LOB/FILE is NULL, the length is 
undefined.

The length of a FILE includes the EOF, if it exists. 

The length is expressed in terms of bytes for BLOBs and BFILEs, and in terms of
characters for CLOBs. The length of an empty internal LOB is zero.

     Note: Any zero-byte or space fillers in the LOB written by previous calls
     to OCILobErase() or OCILobWrite() are also included in the length count.

RELATED FUNCTIONS
OCIErrorGet, OCIFileSetName


-------------------------------------------------------------------------------

OCILobIsEqual()


NAME

OCI Lob Is Equal

PURPOSE
Compares two LOB locators for equality.

SYNTAX
sword OCILobIsEqual ( OCIEnv                  *envhp,
                      CONST OCILobLocator     *x,
                      CONST OCILobLocator     *y,
                      boolean                 *is_equal );

PARAMETERS

envhp (IN) - the OCI environment handle.

x (IN) - LOB locator to compare.

y (IN) - LOB locator to compare.

is_equal (OUT) - TRUE, if the LOB locators are equal; FALSE if they are not.

COMMENTS

Compares the given LOB/FILE locators for equality. Two LOB/FILE locators are
equal if and only if they both refer to the same LOB/FILE value.

Two NULL locators are considered not equal by this function. 

RELATED FUNCTIONS

OCILobAssign(), OCILobLocatorIsInit() 


-------------------------------------------------------------------------------

OCILobLoadFromFile()

NAME
OCI Lob Load From File

PURPOSE
Load/copy all or a portion of the file into an internal LOB.

SYNTAX
sword OCILobLoadFromFile ( OCISvcCtx        *svchp,
                           OCIError         *errhp,
                           OCILobLocator    *dst_locp,
                           OCILobLocator    *src_filep,
                           ub4              amount,
                           ub4              dst_offset,
                           ub4              src_offset );

PARAMETERS

svchp (IN) - the service context handle. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

dst_locp (IN/OUT) - a locator uniquely referencing the destination internal 
LOB which may be of type blob, clob, or nclob. 

src_filep (IN/OUT) - a locator uniquely referencing the source BFILE. 

amount (IN) - the number of bytes to be copied.

dst_offset (IN) - this is the absolute offset for the destination LOB. 
For character LOBs it is the number of characters from the beginning of the 
LOB at which to begin writing. For binary LOBs it is the number of bytes from 
the beginning of the lob from which to begin reading. The offset starts at 1.

src_offset (IN) - this is the absolute offset for the source BFILE.  It is 
the number of bytes from the beginning of the LOB.  The offset starts at 1.

COMMENTS 

Loads/copies a portion or all of a FILE value into an internal LOB as
specified. The data is copied from the source FILE to the destination internal
LOB (BLOB/CLOB). No character set conversions are performed when copying the
FILE data to a CLOB/NCLOB. Therefore, the FILE data must already be in the same
character set as the CLOB/NCLOB in the database.  No error checking is
performed to verify this.

The source (src_locp) and the destination (dst_locp) LOBs must already
exist. If the data already exists at the destination's start position, it is
overwritten with the source data. If the destination's start position is beyond
the end of the current data, zero-byte fillers (for BLOBs) or spaces (for
CLOBs) are written into the destination LOB from the end of the data to the
beginning of the newly written data from the source. The destination LOB is
extended to accommodate the newly written data if it extends beyond the current
length of the destination LOB.

It is an error to extend the destination LOB beyond the maximum length allowed
(4 gigabytes) or to try to copy from a NULL FILE.

The amount parameter indicates the maximum amount to load. If the end of the
source FILE is reached before the specified amount is loaded, the operation
terminates without error. This makes it possible to load from a starting offset
to the end of the FILE without first needing to determine the length of the
file.

RELATED FUNCTIONS 
OCIErrorGet(), OCILobAppend(), OCILobWrite(), OCILobTrim(), OCILobCopy(),
OCILobGetLength() 



-------------------------------------------------------------------------------


OCILobLocatorIsInit()

NAME
OCI LOB locator is initialized?

PURPOSE
Tests to see if a given LOB locator is initialized.

SYNTAX
sword OCILobLocatorIsInit ( OCIEnv   *envhp,
                            OCIError *errhp,
                            CONST OCILobLocator *locp,
                            boolean *is_initialized );

PARAMETERS

envhp (IN/OUT) - OCI environment handle initialized in object mode.

errhp (IN/OUT) - error handle. The OCI error handle. If there is an error, it 
is recorded in err and this function returns OCI_ERROR. Diagnostic 
information can be obtained by calling OCIErrorGet().

locp (IN) - the LOB locator being tested

is_initialized (OUT) - returns TRUE if the given LOB locator is initialized; 
FALSE if it is not.

COMMENTS

Tests to see if a given LOB/FILE locator is initialized. 

Internal LOB locators can be initialized by one of the following methods:

     SELECTing a non-NULL LOB into the locator, pinning an object that contains
     a non-NULL LOB attribute via OCIObjectPin() setting the locator to empty
     via OCIAttrSet() (see "LOB Locator Attributes" on page B-25 for more
     information.)

FILE locators can be initialized by one of the following methods:

     SELECTing a non-NULL FILE into the locator pinning an object that contains
     a non-NULL FILE attribute via OCIObjectPin() calling OCILobFileSetName()

RELATED FUNCTIONS
OCIErrorGet(), OCILobIsEqual() 




-------------------------------------------------------------------------------

OCILobRead()

NAME
OCI Lob/File ReaD

PURPOSE
Reads a portion of a LOB/FILE as specified by the call into a buffer. 

SYNTAX
sword OCILobRead ( OCISvcCtx       *svchp,
                   OCIError        *errhp,
                   OCILobLocator   *locp,
                   ub4             offset,
                   ub4             *amtp,
                   dvoid           *bufp,
                   ub4             bufl,
                   dvoid           *ctxp,  
                   OCICallbackLobRead (cbfp)
                                   (
                                    dvoid         *ctxp,
                                    CONST dvoid   *bufp,
                                    ub4           len,
                                    ub1           piece )
                   ub2             csid,
                   ub1             csfrm );

PARAMETERS

svchp (IN/OUT) - the service context handle. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

locp (IN/OUT) - a LOB locator that uniquely references a LOB. 

offset (IN) - On input, it is the absolute offset, for character LOBs in the 
number of characters from the beginning of the LOB, for binary LOBs it is the 
number of bytes. Starts from 1.

amtp (IN/OUT) - On input, the number of character or bytes to be read. On 
output, the actual number of bytes or characters read. 
If the amount of bytes to be read is larger than the buffer length it is 
assumed that the LOB is being read in a streamed mode. On input if this value 
is 0, then the data shall be read in streamed mode from the LOB until the end 
of LOB. If the data is read in pieces, *amtp always contains the length of 
the last piece read.  If a callback function is defined, then this callback 
function will be invoked each time bufl bytes are read off the pipe. Each 
piece will be written into bufp.
If the callback function is not defined, then OCI_NEED_DATA error code will 
be returned. The application must invoke the LOB read over and over again to 
read more pieces of the LOB until the OCI_NEED_DATA error code is not 
returned. The buffer pointer and the length can be different in each call 
if the pieces are being read into different sizes and location. 

bufp (IN) - the pointer to a buffer into which the piece will be read. The 
length of the allocated memory is assumed to be bufl. 

bufl (IN) - the length of the buffer in octets. 

ctxp (IN) - the context for the call back function. Can be NULL.

cbfp (IN) - a callback that may be registered to be called for each piece. If 
this is NULL, then OCI_NEED_DATA will be returned for each piece. 
The callback function must return OCI_CONTINUE for the read to continue. 
If any other error code is returned, the LOB read is aborted. 
  
  ctxp (IN) - the context for the call back function. Can be NULL.
  
  bufp (IN) - a buffer pointer for the piece.
  
  len (IN) - the length of length of current piece in bufp.
  
  piece (IN) - which piece - OCI_FIRST_PIECE, OCI_NEXT_PIECE or 
               OCI_LAST_PIECE.
csid (IN) - the character set ID of the buffer data
csfrm (IN) - the character set form of the buffer data

COMMENTS

Reads a portion of a LOB/FILE as specified by the call into a buffer. It is an
error to try to read from a NULL LOB/FILE.

     Note: When reading or writing LOBs, the character set form (csfrm)
     specified should match the form of the locator itself.

For FILEs, the OS file must already exist on the server, and it must have been
opened via OCILobFileOpen() using the input locator. Oracle must have
permission to read the OS file, and the user must have read permission on the
directory object.

When using the polling mode for OCILobRead(), the first call needs to specify
values for offset and amtp, but on subsequent polling calls to OCILobRead(),
the user need not specify these values.

     See Also: For more information about FILEs, refer to the description of
     BFILEs in the Oracle8 Application Developer's Guide.

     For a code sample showing the use of LOB reads and writes, refer to
     "Example 5, CLOB/BLOB Operations" on page D-76.

     For general information about piecewise OCI operations, refer to "Run Time
     Data Allocation and Piecewise Operations" on page 7-16.

RELATED FUNCTIONS
OCIErrorGet(), OCILobWrite(), OCILobFileSetName() 


-------------------------------------------------------------------------------


OCILobTrim()

NAME

OCI Lob  Trim

PURPOSE

Trims the lob value to a shorter length

SYNTAX
sword OCILobTrim ( OCISvcCtx       *svchp,
                 OCIError        *errhp,
                 OCILobLocator   *locp,
                 ub4             newlen );

PARAMETERS

svchp (IN) - the service context handle. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

locp (IN/OUT) - a LOB locator that uniquely references the LOB. This locator 
must be a locator that was obtained from the server specified by svchp. 

newlen (IN) - the new length of the LOB data, which must be less than or equal
to the current length. 


COMMENTS
Truncates LOB data to a specified shorter length. 

The function returns an error if newlen is greater than the current LOB length. 
This function is valid only for internal LOBs. FILEs are not allowed. 

RELATED FUNCTIONS
OCIErrorGet, OCILobWrite, OCiLobErase, OCILobAppend, OCILobCopy


-------------------------------------------------------------------------------

OCILobWrite()

NAME

OCI Lob Write

PURPOSE

Writes a buffer into a LOB

SYNTAX
sword OCILobWrite ( OCISvcCtx       *svchp,
                    OCIError        *errhp,
                    OCILobLocator   *locp,
                    ub4             offset,
                    ub4             *amtp,
                    dvoid           *bufp, 
                    ub4             buflen,
                    ub1             piece,
                    dvoid           *ctxp,  
                    OCICallbackLobWrite   (cbfp)
                                    (
                                    dvoid    *ctxp,
                                    dvoid    *bufp,
                                    ub4      *lenp,
                                    ub1      *piecep ) 
                    ub2             csid
                    ub1             csfrm );



PARAMETERS

svchp (IN/OUT) - the service context handle. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

locp (IN/OUT) - a LOB locator that uniquely references a LOB. 

offset (IN) - On input, it is the absolute offset, for character LOBs in 
the number of characters from the beginning of the LOB, for binary LOBs it 
is the number of bytes. Starts at 1.

bufp (IN) - the pointer to a buffer from which the piece will be written. The 
length of the allocated memory is assumed to be the value passed in bufl. 
Even if the data is being written in pieces, bufp must contain the first 
piece of the LOB when this call is invoked.

bufl (IN) - the length of the buffer in bytes.
Note: This parameter assumes an 8-bit byte. If your platform uses a 
longer byte, the value of bufl must be adjusted accordingly.

piece (IN) - which piece of the buffer is being written. The default value for
this parameter is OCI_ONE_PIECE, indicating the buffer will be written in a 
single piece.
The following other values are also possible for piecewise or callback mode: 
OCI_FIRST_PIECE, OCI_NEXT_PIECE and OCI_LAST_PIECE.

amtp (IN/OUT) - On input, takes the number of character or bytes to be 
written. On output, returns the actual number of bytes or characters written. 
If the data is written in pieces, *amtp will contain the total length of the 
pieces written at the end of the call (last piece written) and is undefined in
between. 
(Note it is different from the piecewise read case)

ctxp (IN) - the context for the call back function. Can be NULL.

cbfp (IN) - a callback that may be registered to be called for each piece in 
a piecewise write. If this is NULL, the standard polling method will be used.
The callback function must return OCI_CONTINUE for the write to continue. 
If any other error code is returned, the LOB write is aborted. The 
callback takes the following parameters:
  
  ctxp (IN) - the context for the call back function. Can be NULL.

  bufp (IN/OUT) - a buffer pointer for the piece.

  lenp (IN/OUT) - the length of the buffer (in octets) and the length of 
  current piece in bufp (out octets).
  
piecep (OUT) - which piece - OCI_NEXT_PIECE or OCI_LAST_PIECE.
csid (IN) - the character set ID of the buffer data
csfrm (IN) - the character set form of the buffer data

COMMENTS

Writes a buffer into a LOB as specified. If LOB data already exists it is
overwritten with the data stored in the buffer.

The buffer can be written to the LOB in a single piece with this call, or it
can be provided piecewise using callbacks or a standard polling method.

     Note: When reading or writing LOBs, the character set form (csfrm)
     specified should match the form of the locator itself.

When using the polling mode for OCILobWrite(), the first call needs to specify
values for offset and amtp, but on subsequent polling calls to OCILobWrite(),
the user need not specify these values.

If the value of the piece parameter is OCI_FIRST_PIECE, data may need to be
provided through callbacks or polling.

If a callback function is defined in the cbfp parameter, then this callback
function will be invoked to get the next piece after a piece is written to the
pipe. Each piece will be written from bufp.

If no callback function is defined, then OCILobWrite() returns the
OCI_NEED_DATA error code. The application must call OCILobWrite() again to
write more pieces of the LOB. In this mode, the buffer pointer and the length
can be different in each call if the pieces are of different sizes and from
different locations.

A piece value of OCI_LAST_PIECE terminates the piecewise write, regardless of
whether the polling or callback method is used.

If the amount of data passed to Oracle (through either input mechanism) is less
than the amount specified by the amtp parameter, an ORA-22993 error is
returned.

This function is valid for internal LOBs only. FILEs are not allowed, since
they are read-only.

     See Also: For a code sample showing the use of LOB reads and writes, refer
     to "Example 5, CLOB/BLOB Operations" on page D-76.

     For general information about piecewise OCI operations, refer to "Run Time
     Data Allocation and Piecewise Operations" on page 7-16.

RELATED FUNCTIONS
OCIErrorGet(), OCILobRead(), OCILobAppend(), OCILobCopy() 


-------------------------------------------------------------------------------


OCILogoff()

NAME

OCI simplified Logoff

PURPOSE

This function is used to terminate a session created with OCILogon().

SYNTAX

sword OCILogoff ( OCISvcCtx      *svchp
                  OCIError       *errhp );


PARAMETERS

svchp (IN) - the service context handle which was used in the call to 
OCILogon().

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

COMMENTS

This call is used to terminate a session and connection which were created with
OCILogon().  This call implicitly deallocates the server, user session, and
service context handles.

     Note: For more information on logging on and off in an application, refer
     to the section "Application Initialization, Connection, and Session
     Creation" on page 2-18.

RELATED FUNCTIONS

OCILogon() 


-------------------------------------------------------------------------------

OCILogon()

NAME

OCI Service Context Logon

PURPOSE

This function is used to create a simple logon session.

SYNTAX
sword OCILogon ( OCIEnv          *envhp,
                       OCIError        *errhp,
                       OCISvcCtx       *svchp,
                       CONST text      *username,
                       ub4             uname_len,
                       CONST text      *password,
                       ub4             passwd_len,
                       CONST text      *dbname,
                       ub4             dbname_len );

PARAMETERS

envhp (IN) - the OCI environment handle.

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

svchp (OUT) - the service context pointer.

username (IN) - the username.

uname_len (IN) - the length of username.

password (IN) - the user's password.

passwd_len (IN) - the length of password.

dbname (IN) - the name of the database to connect to.

dbname_len (IN) - the length of dbname.

COMMENTS

This function is used to create a simple logon session for an application.

     Note: Users requiring more complex sessions (e.g., TP monitor
     applications) should refer to the section "Application Initialization,
     Connection, and Session Creation" on page 2-18.

This call allocates the error and service context handles which are passed to
it.

This call also implicitly allocates server and user session handles associated
with the session. These handles can be retrieved by calling OCIAQEnq() on the
service context handle.

RELATED FUNCTIONS

OCILogoff() 

-------------------------------------------------------------------------------


OCIParamGet()

NAME

OCI Get Parameter

PURPOSE

Returns a descriptor of a parameter specified by position in the describe
handle or statement handle.

SYNTAX
sword OCIParamGet ( CONST dvoid *hndlp,
                    ub4         htype,
                    OCIError    *errhp,
                    dvoid    **parmdpp,
                    ub4         pos );


PARAMETERS

hndlp (IN) - a statement handle or describe handle. The OCIParamGet() 
function will return a parameter descriptor for this handle. 

htype (IN) - the type of the handle passed in the handle parameter. Valid 
types are OCI_HTYPE_DESCRIBE, for a describe handle OCI_HTYPE_STMT, for a 
statement handle

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

parmdpp (OUT) - a descriptor of the parameter at the position given in the pos 
parameter.

pos (IN) - position number in the statement handle or describe handle. A 
parameter descriptor will be returned for this position.
Note: OCI_NO_DATA may be returned if there are no parameter 
descriptors for this position. 

COMMENTS

This call returns a descriptor of a parameter specified by position in the 
describe handle or statement handle. Parameter descriptors are always 
allocated internally by the OCI library. They are read-only.

OCI_NO_DATA may be returned if there are no parameter descriptors for this 
position. 

See Appendix B for more detailed information about parameter descriptor 
attributes.

RELATED FUNCTIONS
OCIAttrGet(), OCIAttrSet()


-------------------------------------------------------------------------------


OCIParamSet()

NAME

OCI Parameter Set in handle

PURPOSE

Used to set a complex object retrieval descriptor into a complex object 

retrieval handle.

SYNTAX
sword   OCIParamSet ( dvoid *hndlp,
                       ub4 htyp,
                      OCIError *errhp,
                      CONST dvoid *dscp,
                      ub4 dtyp,
                      ub4 pos );

PARAMETERS

hndlp (IN/OUT) - handle pointer.

htype (IN) - handle type.

errhp (IN/OUT) - error handle.

dscp (IN) - complex object retrieval descriptor pointer.

dtyp (IN) - 

pos (IN) - position number.

COMMENTS

This call sets a given complex object retrieval descriptor into a complex
object retrieval handle.

The handle must have been previously allocated using OCIHandleAlloc(), and the
descriptor must have been previously allocated using
OCIDescriptorAlloc(). Attributes of the descriptor are set using OCIAttrSet().

For more information about complex object retrieval, see "Complex Object
Retrieval" on page 8-21.

RELATED FUNCTIONS
OCIParamGet() 


-------------------------------------------------------------------------------

OCIPasswordChange()

NAME

OCI Change PassWord

PURPOSE
This call allows the password of an account to be changed.

SYNTAX
sword OCIPasswordChange ( OCISvcCtx     *svchp,
                        OCIError      *errhp,
                        CONST text    *user_name,
                        ub4           usernm_len,
                        CONST text    *opasswd,
                        ub4           opasswd_len,
                        CONST text    *npasswd,
                        sb4           npasswd_len,
                        ub4           mode);

PARAMETERS

svchp (IN/OUT) - a handle to a service context. The service context handle 
must be initialized and have a server context handle associated with it.

errhp (IN) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

user_name (IN) - specifies the user name. It points to a character string, 
whose length is specified in usernm_len. This parameter must be NULL if the 
service context has been initialized with an authentication handle.

usernm_len (IN) - the length of the user name string specified in user_name. 
For a valid user name string, usernm_len must be non-zero.

opasswd (IN) - specifies the user's old password. It points to a character 
string, whose length is specified in opasswd_len .

opasswd_len (IN) - the length of the old password string specified in opasswd. 
For a valid password string, opasswd_len must be non-zero.

npasswd (IN) - specifies the user's new password. It points to a character 
string, whose length is specified in npasswd_len which must be non-zero for a 
valid password string. If the password complexity verification routine is 
specified in the user's profile to verify the new password's complexity, the 
new password must meet the complexity requirements of the verification 
function.

npasswd_len (IN)  - then length of the new password string specified in 
npasswd. For a valid password string, npasswd_len must be non-zero.

mode (IN) - pass as OCI_DEFAULT.

COMMENTS

This call allows the password of an account to be changed. This call is similar
to OCISessionBegin() with the following differences:

     If the user session is already established, it authenticates the account
     using the old password and then changes the password to the new password

     If the user session is not established, it establishes a user session and
     authenticates the account using the old password, then changes the
     password to the new password.

This call is useful when the password of an account is expired and
OCISessionBegin() returns an error or warning which indicates that the password
has expired.

RELATED FUNCTIONS
OCISessionBegin()


----------------------------------OCIReset------------------------------------


OCIReset()
Name
OCI Reset
Purpose
Resets the interrupted asynchronous operation and protocol. Must be called
if a OCIBreak call had been issued while a non-blocking operation was in
progress.
Syntax
sword OCIReset ( dvoid      *hndlp,
                 OCIError   *errhp);
Comments
This call is called in non-blocking mode ONLY. Resets the interrupted
asynchronous operation and protocol. Must be called if a OCIBreak call 
had been issued while a non-blocking operation was in progress. 
Parameters
hndlp (IN) - the service context handle or the server context handle.
errhp (IN) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.
Related Functions

-------------------------------------------------------------------------------


OCIServerAttach()

NAME

OCI Attach to server

PURPOSE

Creates an access path to a data source for OCI operations.

SYNTAX

sword OCIServerAttach ( OCIServer    *srvhp,
                        OCIError     *errhp,
                        CONST text   *dblink,
                        sb4          dblink_len,
                        ub4          mode);


PARAMETERS

This call initializes a server context handle, which must have been previously 
allocated with a call to OCIHandleAlloc().
The server context handle initialized by this call can be associated with a 
service context through a call to OCIAttrSet(). Once that association has been 
made, OCI operations can be performed against the server.
If an application is operating against multiple servers, multiple server 
context handles can be maintained. OCI operations are performed against 
whichever server context is currently associated with the service context.
Parameters

srvhp (IN/OUT) - an uninitialized server context handle, which gets 
initialized by this call. Passing in an initialized server handle causes an 
error. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

dblink (IN) - specifies the database (server) to use. This parameter points to
a character string which specifies a connect string or a service point. If the 
connect string is NULL, then this call attaches to the default host. The length
of connstr is specified in connstr_len. The connstr pointer may be freed by the
caller on return.

dblink_len (IN) - the length of the string pointed to by connstr. For a valid 
connect string name or alias, connstr_len must be non-zero.

mode (IN) - specifies the various modes of operation.  For release 8.0, pass as
OCI_DEFAULT - in this mode, calls made to the server on this server context 
are made in blocking mode. 

COMMENTS

This call is used to create an association between an OCI application and a
particular server.

This call initializes a server context handle, which must have been previously
allocated with a call to OCIHandleAlloc().

The server context handle initialized by this call can be associated with a
service context through a call to OCIAttrSet(). Once that association has been
made, OCI operations can be performed against the server.

If an application is operating against multiple servers, multiple server
context handles can be maintained. OCI operations are performed against
whichever server context is currently associated with the service context.

EXAMPLE

The following example demonstrates the use of OCIServerAttach(). This code
segment allocates the server handle, makes the attach call, allocates the
service context handle, and then sets the server context into it.

OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, (ub4) 
          OCI_HTYPE_SERVER, 0, (dvoid **) &tmp);
OCIServerAttach( srvhp, errhp, (text *) 0, (sb4) 0, (ub4) OCI_DEFAULT);
OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, (ub4) 
          OCI_HTYPE_SVCCTX, 0, (dvoid **) &tmp);

/o set attribute server context in the service context o/
OCIAttrSet( (dvoid *) svchp, (ub4) OCI_HTYPE_SVCCTX, (dvoid *) srvhp, 
          (ub4) 0, (ub4) OCI_ATTR_SERVER, (OCIError *) errhp);

RELATED FUNCTIONS
OCIServerDetach() 


-------------------------------------------------------------------------------


OCIServerDetach()

NAME

OCI Detach server

PURPOSE

Deletes an access to a data source for OCI operations.

SYNTAX

sword OCIServerDetach ( OCIServer   *svrhp,
                        OCIError    *errhp,
                        ub4         mode); 


PARAMETERS


srvhp (IN) - a handle to an initialized server context, which gets reset to 
uninitialized state. The handle is not de-allocated. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

mode (IN) - specifies the various modes of operation. The only valid mode is 
OCI_DEFAULT for the default mode. 

COMMENTS

This call deletes an access to data source for OCI operations, which was 
established by a call to OCIServerAttach(). 

RELATED FUNCTIONS
OCIServerAttach()


-------------------------------------------------------------------------------

OCIServerVersion()

NAME

OCI VERSion

PURPOSE

Returns the version string of the Oracle server.

SYNTAX

sword OCIServerVersion ( dvoid        *hndlp, 
                       OCIError     *errhp, 
                       text         *bufp,
                       ub4          bufsz
                       ub1          hndltype );


PARAMETERS


hndlp (IN) - the service context handle or the server context handle.

errhp (IN) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

bufp (IN) - the buffer in which the version information is returned.

bufsz (IN) - the length of the buffer.

hndltype (IN) - the type of handle passed to the function.

COMMENTS

This call returns the version string of the Oracle server. 
For example, the following might be returned as the version string if your 
application is running against a 7.3.2 server:
Oracle7 Server Release 7.3.2.0.0 - Production Release
PL/SQL Release 2.3.2.0.0 - Production
CORE Version 3.5.2.0.0 - Production
TNS for SEQUENT DYNIX/ptx: Version 2.3.2.0.0 - Production
NLSRTL Version 3.2.2.0.0 - Production


RELATED FUNCTIONS



-------------------------------------------------------------------------------


OCISessionBegin()

NAME

OCI Session Begin and authenticate user

PURPOSE

Creates a user authentication and begins a user session for a given server.

SYNTAX

sword OCISessionBegin ( OCISvcCtx     *svchp,
                      OCIError      *errhp,
                      OCISession    *usrhp,
                      ub4           credt,
                      ub4           mode);



PARAMETERS


svchp (IN) - a handle to a service context. There must be a valid server 
handle set in svchp.

errhp (IN) - an error handle to the retrieve diagnostic information.

usrhp (IN/OUT) - a handle to an authentication context, which is initialized 
by this call.

credt (IN) - specifies the type of credentials to use for authentication. 
Valid values for credt are:

  OCI_CRED_RDBMS - authenticate using a database username and 
                   password pair as credentials. The attributes 
                   OCI_ATTR_USERNAME and OCI_ATTR_PASSWORD should be set 
                   on the authentication context before this call.
  OCI_CRED_EXT -   authenticate using external credentials. No username
                   or password is provided.

mode (IN) - specifies the various modes of operation. Valid modes are:

  OCI_DEFAULT - in this mode, the authentication context returned may 
                only ever be set with the same server context specified 
                in svchp. This establishes the primary authentication context.
  OCI_MIGRATE - in this mode, the new authentication context may be 
                set in a service handle with a different server handle. 
                This mode establishes the user authentication context. 
  OCI_SYSDBA -  in this mode, the user is authenticated for SYSDBA 
                access.
  OCI_SYSOPER - in this mode, the user is authenticated for SYSOPER 
                access.
  OCI_PRELIM_AUTH - this mode may only be used with OCI_SYSDBA 
                or OCI_SYSOPER to authenticate for certain administration 
                tasks.

COMMENTS

The OCISessionBegin() call is used to authenticate a user against the server
set in the service context handle.

For Oracle8, OCISessionBegin() must be called for any given server handle
before requests can be made against it. Also, OCISessionBegin() only supports
authenticating the user for access to the Oracle server specified by the server
handle in the service context. In other words, after OCIServerAttach() is
called to initialize a server handle, OCISessionBegin() must be called to
authenticate the user for that given server.

When OCISessionBegin() is called for the first time for a given server handle,
the user session may not be created in migratable (OCI_MIGRATE) mode.

After OCISessionBegin() has been called for a server handle, the application
may call OCISessionBegin() again to initialize another user session handle with
different (or the same) credentials and different (or the same) operation
modes. If an application wants to authenticate a user in OCI_MIGRATE mode, the
service handle must already be associated with a non-migratable user
handle. The user ID of that user handle becomes the ownership ID of the
migratable user session. Every migratable session must have a non-migratable
parent session.

If the OCI_MIGRATE mode is not specified, then the user session context can
only ever be used with the same server handle set in svchp. If OCI_MIGRATE mode
is specified, then the user authentication may be set with different server
handles. However, the user session context may only be used with server handles
which resolve to the same database instance.  Security checking is done during
session switching. A process or circuit is allowed to switch to a migratable
session only if the ownership ID of the session matches the user ID of a
non-migratable session currently connected to that same process or circuit,
unless it is the creator of the session.

OCI_SYSDBA, OCI_SYSOPER, and OCI_PRELIM_AUTH may only be used with a primary
user session context.

To provide credentials for a call to OCISessionBegin(), one of two methods are
supported.  The first is to provide a valid username and password pair for
database authentication in the user session handle passed to
OCISessionBegin(). This involves using OCIAttrSet() to set the
OCI_ATTR_USERNAME and OCI_ATTR_PASSWORD attributes on the user session handle.
Then OCISessionBegin() is called with OCI_CRED_RDBMS.

     Note: When the user session handle is terminated using OCISessionEnd(),
     the username and password attributes remain unchanged and thus can be
     re-used in a future call to OCISessionBegin(). Otherwise, they must be
     reset to new values before the next OCISessionBegin() call.

The second type of credentials supported are external credentials. No
attributes need to be set on the user session handle before calling
OCISessionBegin(). The credential type is OCI_CRED_EXT. This is equivalent to
the Oracle7 `connect /' syntax. If values have been set for OCI_ATTR_USERNAME
and OCI_ATTR_PASSWORD, then these are ignored if OCI_CRED_EXT is used.

EXAMPLE

The following example demonstrates the use of OCISessionBegin(). This code
segment allocates the user session handle, sets the username and password
attributes, calls OCISessionBegin(), and then sets the user session into the
service context.

/o allocate a user session handle o/
OCIHandleAlloc((dvoid *)envhp, (dvoid **)&usrhp, (ub4) 
          OCI_HTYPE_SESSION, (size_t) 0, (dvoid **) 0);
OCIAttrSet((dvoid *)usrhp, (ub4)OCI_HTYPE_SESSION, (dvoid *)"jessica", 
          (ub4)strlen("jessica"), OCI_ATTR_USERNAME, errhp);
OCIAttrSet((dvoid *)usrhp, (ub4)OCI_HTYPE_SESSION, (dvoid *)"doogie", 
          (ub4)strlen("doogie"), OCI_ATTR_PASSWORD, errhp); 
checkerr(errhp, OCISessionBegin (svchp, errhp, usrhp, OCI_CRED_RDBMS, 
          OCI_DEFAULT)); 
OCIAttrSet((dvoid *)svchp, (ub4)OCI_HTYPE_SVCCTX, (dvoid *)usrhp, 
          (ub4)0, OCI_ATTR_SESSION, errhp);


RELATED FUNCTIONS

OCISessionEnd()


-------------------------------------------------------------------------------

OCISessionEnd()

Name

OCI Terminate user Authentication Context

PURPOSE

Terminates a user authentication context created by OCISessionBegin()

SYNTAX

sword OCISessionEnd ( OCISvcCtx       *svchp,
                      OCIError        *errhp,
                      OCISession      *usrhp,
                      ub4             mode);

PARAMETERS

svchp (IN/OUT) - the service context handle. There must be a valid server 
handle and user authentication handle associated with svchp.

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

usrhp (IN) - de-authenticate this user. If this parameter is passed as NULL,
the user in the service context handle is de-authenticated.

mode (IN) - the only valid mode is OCI_DEFAULT.

COMMENTS

The user security context associated with the service context is invalidated 
by this call. Storage for the authentication context is not freed. The 
transaction specified by the service context is implicitly committed. The 
transaction handle, if explicitly allocated, may be freed if not being used.

Resources allocated on the server for this user are freed.
The authentication handle may be reused in a new call to OCISessionBegin().

RELATED FUNCTIONS
OCISessionBegin()


-------------------------------------------------------------------------------


OCIStmtExecute()

NAME

OCI EXECute

PURPOSE

This call associates an application request with a server.

SYNTAX

sword OCIStmtExecute ( OCISvcCtx           *svchp,
                       OCIStmt             *stmtp,
                       OCIError            *errhp,
                       ub4                 iters,
                       ub4                 rowoff,
                       CONST OCISnapshot   *snap_in,
                       OCISnapshot         *snap_out,
                       ub4                 mode );


PARAMETERS

svchp (IN/OUT) - service context handle. 

stmtp (IN/OUT) - an statement handle - defines the statement and the 
associated data to be executed at the server. It is invalid to pass in a 
statement handle that has bind of data types only supported in release 8.0 
when srvchp points to an Oracle7 server. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. If the statement is being 
batched and it is successful, then this handle will contain this particular 
statement execution specific errors returned from the server when the batch is 
flushed.

iters (IN) - the number of times this statement is executed for non-Select 
statements. For Select statements, if iters is non-zero, then defines must 
have been done for the statement handle. The execution fetches iters rows into 
these predefined buffers and prefetches more rows depending upon the prefetch 
row count. This function returns an error if iters=0 for non-SELECT 
statements.

rowoff (IN) - the index from which the data in an array bind is relevant for 
this multiple row execution. 

snap_in (IN) - this parameter is optional. if supplied, must point to a 
snapshot descriptor of type OCI_DTYPE_SNAP.  The contents of this descriptor 
must be obtained from the snap_out parameter of a previous call.  The 
descriptor is ignored if the SQL is not a SELECT.  This facility allows 
multiple service contexts to ORACLE to see the same consistent snapshot of the 
database's committed data.  However, uncommitted data in one context is not 
visible to another context even using the same snapshot.

snap_out (OUT) - this parameter optional. if supplied, must point to a 
descriptor of type OCI_DTYPE_SNAP. This descriptor is filled in with an 
opaque representation which is the current ORACLE "system change 
number" suitable as a snap_in input to a subsequent call to OCIStmtExecute().  
This descriptor should not be used any longer than necessary in order to avoid 
"snapshot too old" errors. 

mode (IN) - The modes are:

     OCI_DEFAULT - Calling OCIStmtExecute() in this mode executes the
     statement. It also implicitly returns describe information about the
     select-list.  

     OCI_DESCRIBE_ONLY - This mode is for users who wish to
     describe a query prior to execution. Calling OCIStmtExecute() in this mode
     does not execute the statement, but it does return the select-list
     description. To maximize performance, it is recommended that applications
     execute the statement in default mode and use the implicit describe which
     accompanies the execution.  

     OCI_COMMIT_ON_SUCCESS - When a statement is
     executed in this mode, the current transaction is committed after
     execution, provided that execution completes successfully.
     
     OCI_EXACT_FETCH - Used when the application knows in advance exactly how
     many rows it will be fetching. This mode turns prefetching off for Oracle8
     mode, and requires that defines be done before the execute call. Using
     this mode cancels the cursor after the desired rows are fetched and may
     result in reduced server-side resource usage.  COMMENTS

COMMENTS

This function  is used to execute a prepared SQL statement.
Using an execute call, the application associates a request with a server. On 
success, OCI_SUCCESS is returned.

If a SELECT statement is executed, the description of the select list follows 
implicitly as a response. This description is buffered on the client side for 
describes, fetches and define type conversions. Hence it is optimal to 
describe a select list only after an execute. 

Also for SELECT statements, some results are available implicitly. Rows will 
be received and buffered at the end of the execute. For queries with small row 
count, a prefetch causes memory to be released in the server if the end of 
fetch is reached, an optimization that may result in memory usage reduction. 
Set attribute call has been defined to set the number of rows to be prefetched
per result set.

For SELECT statements, at the end of the execute, the statement handle 
implicitly maintains a reference to the service context on which it is 
executed. It is the user's responsibility to maintain the integrity of the 
service context. If the attributes of a service context is changed for 
executing some operations on this service context, the service context must 
be restored to have the same attributes, that a statement was executed with, 
prior to a fetch on the statement handle. The implicit reference is maintained 
until the statement handle is freed or the fetch is cancelled or an end of 
fetch condition is reached.

Note: If output variables are defined for a SELECT statement before a 
call to OCIStmtExecute(), the number of rows specified by iters will be 
fetched directly into the defined output buffers and additional rows 
equivalent to the prefetch count will be prefetched. If there are no 
additional rows, then the fetch is complete without calling 
OCIStmtFetch().

The execute call will return errors if the statement has bind data types that 
are not supported in an Oracle7 server.

RELATED FUNCTIONS
OCIStmtPrepare()


-------------------------------------------------------------------------------

OCIStmtFetch()

NAME

OCI Fetch

PURPOSE

Fetches rows from a query.

SYNTAX

sword OCIStmtFetch ( OCIStmt     *stmtp,
                     OCIError    *errhp, 
                     ub4         nrows,
                     ub2         orientation,
                     ub4         mode);


PARAMETERS

stmtp (IN) - a statement (application request) handle.

errhp (IN) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

nrows (IN) - number of rows to be fetched from the current position.

orientation (IN) - for release 8.0, the only acceptable value is 
OCI_FETCH_NEXT, which is also the default value. 

mode (IN) - for release 8.0, beta-1, the following mode is defined.

OCI_DEFAULT - default mode

OCI_EOF_FETCH - indicates that it is the last fetch from the result set. 
If nrows is non-zero, setting this mode effectively cancels fetching after 
retrieving nrows, otherwise it cancels fetching immediately. 

COMMENTS

The fetch call is a local call, if prefetched rows suffice. However, this is 
transparent to the application. If LOB columns are being read, LOB locators 
are fetched for subsequent LOB operations to be performed on these locators. 
Prefetching is turned off if LONG columns are involved. 

A fetch with nrows set to 0 rows effectively cancels the fetch for this 
statement.

RELATED FUNCTIONS
OCIAttrGet()


-------------------------------------------------------------------------------

OCIStmtGetBindInfo()

NAME

OCI Get Bind Parameters

PURPOSE

Gets the bind and indicator variable names.

SYNTAX

sword OCIStmtGetBindInfo ( OCIStmt      *stmtp,
                           OCIError     *errhp,
                           ub4          size,
                           ub4          startloc,
                           sb4          *found,
                           text         *bvnp[],
                           ub1          bvnl[],
                           text         *invp[],
                           ub1          inpl[],
                           ub1          dupl[],
                           OCIBind      *hndl[] );

PARAMETERS

stmtp (IN) - the statement handle.

errhp (IN) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

size (IN) - the number of elements in each array.

startloc (IN) - position of the  bind variable at which to start getting  bind 
information.

found (IN) - abs(found) gives the total number of bind variables in the 
statement irrespective of the start position. Positive value if the number of 
bind variables returned is less than the size provided, otherwise negative.

bvnp (OUT) - array of pointers to hold bind variable names.

bvnl (OUT) - array to hold the length of the each bvnp element.

invp (OUT) - array of pointers to hold indicator variable names.

inpl (OUT) - array of pointers to hold the length of the each invp element.

dupl (OUT) - an array whose element value is 0 or 1 depending on whether the 
bind position is duplicate of another.

hndl  (OUT) - an array which returns the bind handle if binds have been done 
for the bind position. No handle is returned for duplicates.

COMMENTS

Gets the bind and indicator variable names. It returns the information for all 
the bind variables (even the duplicate ones) and sets the found parameter to 
the total number of bind variables and not just the number of distinct bind 
variables.

The statement must have been prepared with a call to OCIStmtPrepare() prior 
to this call. 

This call is processed locally.

RELATED FUNCTIONS

OCIStmtPrepare()


-------------------------------------------------------------------------------

OCIStmtGetPieceInfo()

Name

OCI Get Piece Information

PURPOSE

Returns piece information for a piecewise operation.

SYNTAX

sword OCIStmtGetPieceInfo( CONST OCIStmt  *stmtp,
                           OCIError       *errhp,
                           dvoid          **hndlpp,
                           ub4            *typep,
                           ub1            *in_outp,
                           ub4            *iterp, 
                           ub4            *idxp,
                           ub1            *piecep );

PARAMETERS

stmtp (IN) - the statement when executed returned OCI_NEED_DATA. 

errhp (OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

hndlpp (OUT) - returns a pointer to the bind or define handle of the bind or 
define whose runtime data is required or is being provided.

typep (OUT) - the type of the handle pointed to by hndlpp: OCI_HTYPE_BIND 
(for a bind handle) or OCI_HTYPE_DEFINE (for a define handle).

in_outp (OUT) - returns OCI_PARAM_IN if the data is required for an IN bind 
value. Returns OCI_PARAM_OUT if the data is available as an OUT bind 
variable or a define position value.

iterp (OUT) - returns the row number of a multiple row operation.

idxp (OUT) - the index of an array element of a PL/SQL array bind operation.

piecep (OUT) - returns one of the following defined values - 
OCI_ONE_PIECE, OCI_FIRST_PIECE, OCI_NEXT_PIECE and 
OCI_LAST_PIECE. The default value is always OCI_ONE_PIECE. 

COMMENTS

When an execute/fetch call returns OCI_NEED_DATA to get/return a 
dynamic bind/define value or piece, OCIStmtGetPieceInfo() returns the 
relevant information: bind/define handle, iteration or index number and 
which piece.
See the section "Runtime Data Allocation and Piecewise Operations" on page 
7-16 for more information about using OCIStmtGetPieceInfo().

RELATED FUNCTIONS

OCIAttrGet(), OCIAttrGet(), OCIStmtExecute(), OCIStmtFetch(), 
OCIStmtSetPieceInfo()


-------------------------------------------------------------------------------


OCIStmtPrepare()

NAME

OCI Statement Request

PURPOSE

This call defines the SQL/PLSQL statement to be executed.

SYNTAX

sword OCIStmtPrepare ( OCIStmt      *stmtp,
                       OCIError     *errhp,
                       CONST text   *stmt, 
                       ub4          stmt_len,
                       ub4          language,
                       ub4          mode);


PARAMETERS

stmtp (IN) - a statement handle.

errhp (IN) - an error handle to retrieve diagnostic information.

stmt (IN) - SQL or PL/SQL statement to be executed. Must be a null-
terminated string. The pointer to the text of the statement must be available 
as long as the statement is executed.

stmt_len (IN) - length of the statement. Must not be zero.

language (IN) - V7, V8, or native syntax. Possible values are:
OCI_V7_SYNTAX - V7 ORACLE parsing syntax
OCI_V8_SYNTAX - V8 ORACLE parsing syntax
OCI_NTV_SYNTAX - syntax depending upon the version of the server. 

mode (IN) - the only defined mode is OCI_DEFAULT for default mode. 

COMMENTS

This call is used to prepare a SQL or PL/SQL statement for execution. The 
OCIStmtPrepare() call defines an application request. 

This is a purely local call. Data values for this statement initialized in 
subsequent bind calls will be stored in a bind handle which will hang off this 
statement handle.

This call does not create an association between this statement handle and any 

RELATED FUNCTIONS

OCIAttrGet(), OCIStmtExecute()

-------------------------------------------------------------------------------

OCIStmtSetPieceInfo()

NAME

OCI Set Piece Information

PURPOSE

Sets piece information for a piecewise operation.

SYNTAX

sword OCIStmtSetPieceInfo ( dvoid             *hndlp,
                            ub4               type,
                            OCIError          *errhp,
                            CONST dvoid       *bufp,
                            ub4               *alenp, 
                            ub1               piece,
                            CONST dvoid       *indp, 
                            ub2               *rcodep ); 


PARAMETERS

hndlp (IN/OUT) - the bind/define handle.

type (IN) - type of the handle. 

errhp (OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

bufp (IN/OUT) - bufp is a pointer to a storage containing the data value or 
the piece when it is an IN bind variable, otherwise bufp is a pointer to 
storage for getting a piece or a value for OUT binds and define variables. For
named data types or REFs, a pointer to the object or REF is returned.

alenp (IN/OUT) - the length of the piece or the value. 

piece (IN) - the piece parameter. The following are valid values: 
OCI_ONE_PIECE, OCI_FIRST_PIECE, OCI_NEXT_PIECE, or 
OCI_LAST_PIECE. 
The default value is OCI_ONE_PIECE. This parameter is used for IN bind 
variables only.

indp (IN/OUT) - indicator. A pointer to a sb2 value or pointer to an indicator 
structure for named data types (SQLT_NTY) and REFs (SQLT_REF), i.e., *indp 
is either an sb2 or a dvoid * depending upon the data type.

rcodep (IN/OUT) - return code. 

COMMENTS

When an execute call returns OCI_NEED_DATA to get a dynamic IN/OUT 
bind value or piece, OCIStmtSetPieceInfo() sets the piece information: the 
buffer, the length, the indicator and which piece is currently being processed.

For more information about using OCIStmtSetPieceInfo() see the section 
"Runtime Data Allocation and Piecewise Operations" on page 7-16.

RELATED FUNCTIONS

OCIAttrGet(), OCIAttrGet(), OCIStmtExecute(), OCIStmtFetch(), 
OCIStmtGetPieceInfo()


-------------------------------------------------------------------------------

OCISvcCtxToLda()

NAME

OCI toggle SerVice context handle to Version 7 Lda_Def

PURPOSE

Toggles between a V8 service context handle and a V7 Lda_Def.

SYNTAX

sword OCISvcCtxToLda ( OCISvcCtx    *srvhp,
                       OCIError     *errhp,
                       Lda_Def      *ldap );


PARAMETERS

svchp (IN/OUT) - the service context handle. 

errhp (IN/OUT) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error. 

ldap (IN/OUT) - a Logon Data Area for V7-style OCI calls which is initialized 
by this call. 

COMMENTS

Toggles between an Oracle8 service context handle and an Oracle7 Lda_Def.

This function can only be called after a service context has been properly 
initialized.

Once the service context has been translated to an Lda_Def, it can be used in 
release 7.x OCI calls (e.g., obindps(), ofen()).

Note: If there are multiple service contexts which share the same server 
handle, only one can be in V7 mode at any time.

The action of this call can be reversed by passing the resulting Lda_Def to 
the OCILdaToSvcCtx() function.

The OCI_ATTR_IN_V8_MODE attribute of the server handle or service context
handle enables an application to determine whether the application is currently
in Oracle7 mode or Oracle8 mode. See Appendix B, "Handle and Descriptor
Attributes", for more information.

RELATED FUNCTIONS
OCILdaToSvcCtx()


-------------------------------------------------------------------------------

OCITransCommit()

NAME

OCI TX (transaction) CoMmit

PURPOSE

Commits the transaction associated with a specified service context.

SYNTAX

sword OCITransCommit ( OCISvcCtx    *srvcp,
                       OCIError     *errhp,
                       ub4          flags );


PARAMETERS

srvcp (IN) - the service context handle.

errhp (IN) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

flags (IN) -see the "COMMENTS" section above.

COMMENTS

The transaction currently associated with the service context is committed. If
it is a global transaction that the server cannot commit, this call
additionally retrieves the state of the transaction from the database to be
returned to the user in the error handle.

If the application has defined multiple transactions, this function operates on
the transaction currently associated with the service context. If the
application is working with only the implicit local transaction created when
database changes are made, that implicit transaction is committed.

If the application is running in the object mode, then the modified or updated
objects in the object cache for this transaction are also flushed and
committed.

The flags parameter is used for one-phase commit optimization in global
transactions. If the transaction is non-distributed, the flags parameter is
ignored, and OCI_DEFAULT can be passed as its value. OCI applications managing
global transactions should pass a value of OCI_TRANS_TWOPHASE to the flags
parameter for a two-phase commit. The default is one-phase commit.

Under normal circumstances, OCITransCommit() returns with a status indicating
that the transaction has either been committed or rolled back. With global
transactions, it is possible that the transaction is now in-doubt (i.e.,
neither committed nor aborted). In this case, OCITransCommit() attempts to
retrieve the status of the transaction from the server. The status is returned.

EXAMPLE

The following example demonstrates the use of a simple local transaction, as
described in the section "Simple Local Transactions" on page 7-4.

int main()
{
  OCIEnv *envhp;
  OCIServer *srvhp;
  OCIError *errhp;
  OCISvcCtx *svchp;
  OCIStmt *stmthp;
  dvoid     *tmp;
  text sqlstmt[128];

  OCIInitialize((ub4) OCI_OBJECT, (dvoid *)0,  (dvoid * (*)()) 0,
             (dvoid * (*)()) 0,  (void (*)()) 0 );
  
  OCIHandleAlloc( (dvoid *) NULL, (dvoid **) &envhp, (ub4) OCI_HTYPE_ENV,
             0, (dvoid **) &tmp);
  
  OCIEnvInit( &envhp, (ub4) OCI_DEFAULT, 21, (dvoid **) &tmp  );
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, (ub4) OCI_HTYPE_ERROR,
                52, (dvoid **) &tmp);
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, (ub4) OCI_HTYPE_SERVER,
                52, (dvoid **) &tmp);
  
  OCIServerAttach( srvhp, errhp, (text *) 0, (sb4) 0, (ub4) OCI_DEFAULT);
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, (ub4) OCI_HTYPE_SVCCTX,
                52, (dvoid **) &tmp);

  OCIHandleAlloc((dvoid *)envhp, (dvoid **)&stmthp, OCI_HTYPE_STMT, 0, 0);

  OCIAttrSet((dvoid *)svchp, OCI_HTYPE_SVCCTX, (dvoid *)srvhp, 0,
                  OCI_ATTR_SERVER, errhp);

  OCILogon(envhp, errhp, &svchp, "SCOTT", strlen("SCOTT"),
           "TIGER", strlen("TIGER"), 0, 0);

  /o update scott.emp empno=7902, increment salary o/
  sprintf((char *)sqlstmt, "UPDATE EMP SET SAL = SAL + 1 WHERE EMPNO = 7902");
  OCIStmtPrepare(stmthp, errhp, sqlstmt, strlen(sqlstmt), OCI_NTV_SYNTAX, 0);
  OCIStmtExecute(svchp, stmthp, errhp, 1, 0, 0, 0, 0);
  OCITransCommit(svchp, errhp, (ub4) 0);

  /o update scott.emp empno=7902, increment salary again, but rollback o/
  OCIStmtExecute(svchp, stmthp, errhp, 1, 0, 0, 0, 0);
  OCITransRollback(svchp, errhp, (ub4) 0);
}

RELATED FUNCTIONS
OCITransRollback() 


_______________________________________________________________________________


OCITransDetach()

NAME

OCI TX (transaction) DeTach

PURPOSE

Detaches a transaction.

SYNTAX

sword OCITransDetach ( OCISvcCtx    *srvcp,
                       OCIError     *errhp,
                       ub4          flags);


PARAMETERS

srvcp (IN) - the service context handle. 

errhp (IN) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

flags (IN) - you must pass a value of OCI_DEFAULT for this parameter.

COMMENTS

Detaches a global transaction from the service context handle. The transaction
currently attached to the service context handle becomes inactive at the end of
this call. The transaction may be resumed later by calling OCITransStart(),
specifying a flags value of OCI_TRANS_RESUME.

When a transaction is detached, the value which was specified in the timeout
parameter of OCITransStart() when the transaction was started is used to
determine the amount of time the branch can remain inactive before being
deleted by the server's PMON process.

     Note: The transaction can be resumed by a different process than the one
     that detached it, provided that the transaction has the same
     authorization.

     If this function is called before a transaction is actually started, this
     function is a no-op.

RELATED FUNCTIONS
OCITransStart() 


-------------------------------------------------------------------------------


OCITransForget()

NAME

OCI TX (transaction) Forget

PURPOSE

Causes the server to forget a heuristically completed global transaction.

SYNTAX

sword OCITransForget ( OCISvcCtx     *svchp, 
                       OCIError      *errhp,
                       ub4           flags);



PARAMETERS

srvcp (IN) - the service context handle - the transaction is rolled back.

errhp (IN) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

flags (IN) - you must pass OCI_DEFAULT for this parameter.

COMMENTS

Forgets a heuristically completed global transaction. The server deletes the 
status of the transaction from the system's pending transaction table.

The XID of the transaction to be forgotten is set as an attribute of the 
transaction handle (OCI_ATTR_XID).

RELATED FUNCTIONS
OCITransCommit(), OCITransRollback()


-------------------------------------------------------------------------------


OCITransPrepare()

NAME

OCI TX (transaction) Prepare

PURPOSE

Prepares a transaction for commit.

SYNTAX
sword OCITransPrepare ( OCISvcCtx    *svchp, 
                      OCIError     *errhp,
                      ub4          flags);



PARAMETERS

srvcp (IN) - the service context handle. 

errhp (IN) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

flags (IN) - you must pass OCI_DEFAULT for this parameter.

COMMENTS

Prepares the specified global transaction for commit.

This call is valid only for distributed transactions.

The call returns OCI_SUCCESS_WITH_INFO if the transaction has not made 
any changes. The error handle will indicate that the transaction is read-only. 
The flag parameter is not currently used. 

RELATED FUNCTIONS
OCITransCommit(), OCITransForget()


-------------------------------------------------------------------------------


OCITransRollback()

NAME

OCI TX (transaction) RoLlback

PURPOSE

Rolls back the current transaction.

SYNTAX
sword OCITransRollback ( dvoid        *svchp, 
                         OCIError     *errhp,
                         ub4          flags );

PARAMETERS

svchp (IN) - a service context handle. The transaction currently set in the 
service context handle is rolled back.

errhp (IN) - an error handle which can be passed to OCIErrorGet() for 
diagnostic information in the event of an error.

flags (IN) - you must pass a value of OCI_DEFAULT for this parameter.

COMMENTS

The current transaction- defined as the set of statements executed since the 
last OCITransCommit() or since OCISessionBegin()-is rolled back.

If the application is running under object mode then the modified or updated 
objects in the object cache for this transaction are also rolled back.

An error is returned if an attempt is made to roll back a global transaction 
that is not currently active.

RELATED FUNCTIONS
OCITransCommit()


-------------------------------------------------------------------------------

OCITransStart()

NAME

OCI TX (transaction) STart

PURPOSE

Sets the beginning of a transaction.

SYNTAX
sword OCITransStart ( OCISvcCtx    *svchp, 
                      OCIError     *errhp, 
                      uword        timeout,
                      ub4          flags);


PARAMETERS

svchp (IN/OUT) - the service context handle. The transaction context in the 
service context handle is initialized at the end of the call if the flag 
specified a new transaction to be started.

errhp (IN/OUT) - The OCI error handle. If there is an error, it is recorded in 
err and this function returns OCI_ERROR. Diagnostic information can be 
obtained by calling OCIErrorGet().

timeout (IN) - the time, in seconds, to wait for a transaction to become 
available for resumption when OCI_TRANS_RESUME is specified. When 
OCI_TRANS_NEW is specified, this value is stored and may be used later by 
OCITransDetach().

flags (IN) - specifies whether a new transaction is being started or an 
existing transaction is being resumed. Also specifies serializiability or 
read-only status. More than a single value can be specified. By default, 
a read/write transaction is started. The flag values are:

  OCI_TRANS_NEW - starts a new transaction branch. By default starts a 
                  tightly coupled and migratable branch.
  OCI_TRANS_TIGHT - explicitly specifies a tightly coupled branch
  OCI_TRANS_LOOSE - specifies a loosely coupled branch
  OCI_TRANS_RESUME - resumes an existing transaction branch. 
  OCI_TRANS_READONLY - start a readonly transaction
  OCI_TRANS_SERIALIZABLE - start a serializable transaction

COMMENTS

This function sets the beginning of a global or serializable transaction. The 
transaction context currently associated with the service context handle is 
initialized at the end of the call if the flags parameter specifies that a new 
transaction should be started.

The XID of the transaction is set as an attribute of the transaction handle 
(OCI_ATTR_XID)

EXAMPLES

The following examples demonstrate the use of OCI transactional calls for
manipulating global transactions.

Example 1

This example shows a single session operating on different branches. This
concept is illustrated by Figure 7-2, "Session Operating on Multiple Branches"
.

int main()
{
  OCIEnv *envhp;
  OCIServer *srvhp;
  OCIError *errhp;
  OCISvcCtx *svchp;
  OCISession *usrhp;
  OCIStmt *stmthp1, *stmthp2;
  OCITrans *txnhp1, *txnhp2;
  dvoid     *tmp;
  XID gxid;
  text sqlstmt[128];

  OCIInitialize((ub4) OCI_OBJECT, (dvoid *)0,  (dvoid * (*)()) 0,
             (dvoid * (*)()) 0,  (void (*)()) 0 );
  
  OCIHandleAlloc( (dvoid *) NULL, (dvoid **) &envhp, (ub4) OCI_HTYPE_ENV,
             0, (dvoid **) &tmp);
  
  OCIEnvInit( &envhp, (ub4) OCI_DEFAULT, 21, (dvoid **) &tmp  );
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, (ub4) OCI_HTYPE_ERROR,
                52, (dvoid **) &tmp);
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, (ub4) OCI_HTYPE_SERVER,
                52, (dvoid **) &tmp);
  
  OCIServerAttach( srvhp, errhp, (text *) 0, (sb4) 0, (ub4) OCI_DEFAULT);
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, (ub4) OCI_HTYPE_SVCCTX,
                52, (dvoid **) &tmp);

  OCIHandleAlloc((dvoid *)envhp, (dvoid **)&stmthp1, OCI_HTYPE_STMT, 0, 0);
  OCIHandleAlloc((dvoid *)envhp, (dvoid **)&stmthp2, OCI_HTYPE_STMT, 0, 0);

  OCIAttrSet((dvoid *)svchp, OCI_HTYPE_SVCCTX, (dvoid *)srvhp, 0,
                  OCI_ATTR_SERVER, errhp);

  /o set the external name and internal name in server handle o/
  OCIAttrSet((dvoid *)srvhp, OCI_HTYPE_SERVER, (dvoid *) "demo", 0,
                  OCI_ATTR_EXTERNAL_NAME, errhp);
  OCIAttrSet((dvoid *)srvhp, OCI_HTYPE_SERVER, (dvoid *) "txn demo", 0,
                          OCI_ATTR_INTERNAL_NAME, errhp);

  /o allocate a user context handle o/
  OCIHandleAlloc((dvoid *)envhp, (dvoid **)&usrhp, (ub4) OCI_HTYPE_SESSION,
                (size_t) 0, (dvoid **) 0);
  
  OCIAttrSet((dvoid *)usrhp, (ub4)OCI_HTYPE_SESSION, (dvoid *)"scott", 
             (ub4)strlen("scott"), OCI_ATTR_USERNAME, errhp);
  OCIAttrSet((dvoid *)usrhp, (ub4)OCI_HTYPE_SESSION, (dvoid *)"tiger", 
             (ub4)strlen("tiger"),OCI_ATTR_PASSWORD, errhp);
  
  OCISessionBegin (svchp, errhp, usrhp, OCI_CRED_RDBMS, 0);
  
  OCIAttrSet((dvoid *)svchp, (ub4)OCI_HTYPE_SVCCTX,
                (dvoid *)usrhp, (ub4)0, OCI_ATTR_SESSION, errhp);

  /o allocate transaction handle 1 and set it in the service handle o/
  OCIHandleAlloc((dvoid *)envhp, (dvoid **)&txnhp1,  OCI_HTYPE_TRANS, 0, 0);
  OCIAttrSet((dvoid *)svchp, OCI_HTYPE_SVCCTX, (dvoid *)txnhp1, 0,
                          OCI_ATTR_TRANS, errhp);

  /o start a transaction with global transaction id = [1000, 123, 1] o/
  gxid.formatID = 1000; /o format id = 1000 o/
  gxid.gtrid_length = 3; /o gtrid = 123 o/
  gxid.data[0] = 1; gxid.data[1] = 2; gxid.data[2] = 3;
  gxid.bqual_length = 1; /o bqual = 1 o/
  gxid.data[3] = 1;

  OCIAttrSet((dvoid *)txnhp1, OCI_HTYPE_TRANS, (dvoid *)&gxid, sizeof(XID),
                          OCI_ATTR_XID, errhp);

  /o start global transaction 1 with 60 second time to live when detached o/
  OCITransStart(svchp, errhp, 60, OCI_TRANS_NEW);

  /o update scott.emp empno=7902, increment salary o/
  sprintf((char *)sqlstmt, "UPDATE EMP SET SAL = SAL + 1 WHERE EMPNO = 7902");
  OCIStmtPrepare(stmthp1, errhp, sqlstmt, strlen(sqlstmt), OCI_NTV_SYNTAX, 0);
  OCIStmtExecute(svchp, stmthp1, errhp, 1, 0, 0, 0, 0);

  /o detach the transaction o/
  OCITransDetach(svchp, errhp, 0);

  /o allocate transaction handle 2 and set it in the service handle o/
  OCIHandleAlloc((dvoid *)envhp, (dvoid **)&txnhp2,  OCI_HTYPE_TRANS, 0, 0);
  OCIAttrSet((dvoid *)svchp, OCI_HTYPE_SVCCTX, (dvoid *)txnhp2, 0,
                          OCI_ATTR_TRANS, errhp);

  /o start a transaction with global transaction id = [1000, 124, 1] o/
  gxid.formatID = 1000; /o format id = 1000 o/
  gxid.gtrid_length = 3; /o gtrid = 124 o/
  gxid.data[0] = 1; gxid.data[1] = 2; gxid.data[2] = 4;
  gxid.bqual_length = 1; /o bqual = 1 o/
  gxid.data[3] = 1; 

  OCIAttrSet((dvoid *)txnhp2, OCI_HTYPE_TRANS, (dvoid *)&gxid, sizeof(XID),
                          OCI_ATTR_XID, errhp);

  /o start global transaction 2 with 90 second time to live when detached o/
  OCITransStart(svchp, errhp, 90, OCI_TRANS_NEW);

  /o update scott.emp empno=7934, increment salary o/
  sprintf((char *)sqlstmt, "UPDATE EMP SET SAL = SAL + 1 WHERE EMPNO = 7934");
  OCIStmtPrepare(stmthp2, errhp, sqlstmt, strlen(sqlstmt), OCI_NTV_SYNTAX, 0);
  OCIStmtExecute(svchp, stmthp2, errhp, 1, 0, 0, 0, 0);

  /o detach the transaction o/
  OCITransDetach(svchp, errhp, 0);

  /o Resume transaction 1, increment salary and commit it o/
  /o Set transaction handle 1 into the service handle o/
  OCIAttrSet((dvoid *)svchp, OCI_HTYPE_SVCCTX, (dvoid *)txnhp1, 0,
                          OCI_ATTR_TRANS, errhp);

  /o attach to transaction 1, wait for 10 seconds if the transaction is busy o/
  /o The wait is clearly not required in this example because no other      o/
  /o process/thread is using the transaction. It is only for illustration    o/
  OCITransStart(svchp, errhp, 10, OCI_TRANS_RESUME);
  OCIStmtExecute(svchp, stmthp1, errhp, 1, 0, 0, 0, 0);
  OCITransCommit(svchp, errhp, (ub4) 0);

  /o attach to transaction 2 and commit it o/
  /o set transaction handle2 into the service handle o/
  OCIAttrSet((dvoid *)svchp, OCI_HTYPE_SVCCTX, (dvoid *)txnhp2, 0,
                          OCI_ATTR_TRANS, errhp);
  OCITransCommit(svchp, errhp, (ub4) 0);
}
Example 2


This example demonstrates a single session operating on multiple branches that share the
same transaction. 

int main()
{
  OCIEnv *envhp;
  OCIServer *srvhp;
  OCIError *errhp;
  OCISvcCtx *svchp;
  OCISession *usrhp;
  OCIStmt *stmthp;
  OCITrans *txnhp1, *txnhp2;
  dvoid     *tmp;
  XID gxid;
  text sqlstmt[128];

  OCIInitialize((ub4) OCI_OBJECT, (dvoid *)0,  (dvoid * (*)()) 0,
             (dvoid * (*)()) 0,  (void (*)()) 0 );
  
  OCIHandleAlloc( (dvoid *) NULL, (dvoid **) &envhp, (ub4) OCI_HTYPE_ENV,
             0, (dvoid **) &tmp);
  
  OCIEnvInit( &envhp, (ub4) OCI_DEFAULT, 21, (dvoid **) &tmp  );
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, (ub4) OCI_HTYPE_ERROR,
                52, (dvoid **) &tmp);
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, (ub4) OCI_HTYPE_SERVER,
                52, (dvoid **) &tmp);
  
  OCIServerAttach( srvhp, errhp, (text *) 0, (sb4) 0, (ub4) OCI_DEFAULT);
  
  OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, (ub4) OCI_HTYPE_SVCCTX,
                52, (dvoid **) &tmp);

  OCIHandleAlloc((dvoid *)envhp, (dvoid **)&stmthp, OCI_HTYPE_STMT, 0, 0);

  OCIAttrSet((dvoid *)svchp, OCI_HTYPE_SVCCTX, (dvoid *)srvhp, 0,
                  OCI_ATTR_SERVER, errhp);

  /o set the external name and internal name in server handle o/
  OCIAttrSet((dvoid *)srvhp, OCI_HTYPE_SERVER, (dvoid *) "demo", 0,
                  OCI_ATTR_EXTERNAL_NAME, errhp);
  OCIAttrSet((dvoid *)srvhp, OCI_HTYPE_SERVER, (dvoid *) "txn demo2", 0,
                          OCI_ATTR_INTERNAL_NAME, errhp);

  /o allocate a user context handle o/
  OCIHandleAlloc((dvoid *)envhp, (dvoid **)&usrhp, (ub4) OCI_HTYPE_SESSION,
                (size_t) 0, (dvoid **) 0);
  
  OCIAttrSet((dvoid *)usrhp, (ub4)OCI_HTYPE_SESSION, (dvoid *)"scott", 
             (ub4)strlen("scott"), OCI_ATTR_USERNAME, errhp);
  OCIAttrSet((dvoid *)usrhp, (ub4)OCI_HTYPE_SESSION, (dvoid *)"tiger", 
             (ub4)strlen("tiger"),OCI_ATTR_PASSWORD, errhp);
  
  OCISessionBegin (svchp, errhp, usrhp, OCI_CRED_RDBMS, 0);
  
  OCIAttrSet((dvoid *)svchp, (ub4)OCI_HTYPE_SVCCTX,
                (dvoid *)usrhp, (ub4)0, OCI_ATTR_SESSION, errhp);

  /o allocate transaction handle 1 and set it in the service handle o/
  OCIHandleAlloc((dvoid *)envhp, (dvoid **)&txnhp1,  OCI_HTYPE_TRANS, 0, 0);
  OCIAttrSet((dvoid *)svchp, OCI_HTYPE_SVCCTX, (dvoid *)txnhp1, 0,
                          OCI_ATTR_TRANS, errhp);

  /o start a transaction with global transaction id = [1000, 123, 1] o/
  gxid.formatID = 1000; /o format id = 1000 o/
  gxid.gtrid_length = 3; /o gtrid = 123 o/
  gxid.data[0] = 1; gxid.data[1] = 2; gxid.data[2] = 3;
  gxid.bqual_length = 1; /o bqual = 1 o/
  gxid.data[3] = 1;

  OCIAttrSet((dvoid *)txnhp1, OCI_HTYPE_TRANS, (dvoid *)&gxid, sizeof(XID),
                          OCI_ATTR_XID, errhp);

  /o start global transaction 1 with 60 second time to live when detached o/
  OCITransStart(svchp, errhp, 60, OCI_TRANS_NEW);

  /o update scott.emp empno=7902, increment salary o/
  sprintf((char *)sqlstmt, "UPDATE EMP SET SAL = SAL + 1 WHERE EMPNO = 7902");
  OCIStmtPrepare(stmthp, errhp, sqlstmt, strlen(sqlstmt), OCI_NTV_SYNTAX, 0);
  OCIStmtExecute(svchp, stmthp, errhp, 1, 0, 0, 0, 0);

  /o detach the transaction o/
  OCITransDetach(svchp, errhp, 0);

  /o allocate transaction handle 2 and set it in the service handle o/
  OCIHandleAlloc((dvoid *)envhp, (dvoid **)&txnhp2,  OCI_HTYPE_TRANS, 0, 0);
  OCIAttrSet((dvoid *)svchp, OCI_HTYPE_SVCCTX, (dvoid *)txnhp2, 0,
                          OCI_ATTR_TRANS, errhp);
            
  /o start a transaction with global transaction id = [1000, 123, 2] o/
  /o The global transaction will be tightly coupled with earlier transaction o/
  /o There is not much practical value in doing this but the example o/
  /o illustrates the use of tightly-coupled transaction branches o/
  /o In a practical case the second transaction that tightly couples with o/
  /o the first can be executed from a different process/thread o/

  gxid.formatID = 1000; /o format id = 1000 o/
  gxid.gtrid_length = 3; /o gtrid = 123 o/
  gxid.data[0] = 1; gxid.data[1] = 2; gxid.data[2] = 3;
  gxid.bqual_length = 1; /o bqual = 2 o/
  gxid.data[3] = 2; 

  OCIAttrSet((dvoid *)txnhp2, OCI_HTYPE_TRANS, (dvoid *)&gxid, sizeof(XID),
                          OCI_ATTR_XID, errhp);

  /o start global transaction 2 with 90 second time to live when detached o/
  OCITransStart(svchp, errhp, 90, OCI_TRANS_NEW);

  /o update scott.emp empno=7902, increment salary o/
  /o This is possible even if the earlier transaction has locked this row o/
  /o because the two global transactions are tightly coupled o/
  OCIStmtExecute(svchp, stmthp, errhp, 1, 0, 0, 0, 0);

  /o detach the transaction o/
  OCITransDetach(svchp, errhp, 0);

  /o Resume transaction 1 and prepare it. This will return o/
  /o OCI_SUCCESS_WITH_INFO because all branches except the last branch o/
  /o are treated as read-only transactions for tightly-coupled transactions o/ 

  OCIAttrSet((dvoid *)svchp, OCI_HTYPE_SVCCTX, (dvoid *)txnhp1, 0,
                          OCI_ATTR_TRANS, errhp);
  if (OCITransPrepare(svchp, errhp, (ub4) 0) == OCI_SUCCESS_WITH_INFO)
  {
    text errbuf[512];
    ub4 buflen;
    sb4 errcode;

    OCIErrorGet ((dvoid *) errhp, (ub4) 1, (text *) NULL, &errcode,
    errbuf, (ub4) sizeof(errbuf), (ub4) OCI_HTYPE_ERROR);
    printf("OCITransPrepare - %s\n", errbuf);
  }

  /o attach to transaction 2 and commit it o/
  /o set transaction handle2 into the service handle o/
  OCIAttrSet((dvoid *)svchp, OCI_HTYPE_SVCCTX, (dvoid *)txnhp2, 0,
                          OCI_ATTR_TRANS, errhp);
  OCITransCommit(svchp, errhp, (ub4) 0);
}

RELATED FUNCTIONS

OCITransDetach()
______________________________________________________________________________


******************************************************************************/


/*****************************************************************************
                         ACTUAL PROTOTYPE DECLARATIONS
******************************************************************************/
/*-----------------------Dynamic Callback Function Pointers------------------*/
 
 
typedef sb4 (*OCICallbackInBind)(dvoid *ictxp, OCIBind *bindp, ub4 iter,
                                  ub4 index, dvoid **bufpp, ub4 *alenp,
                                  ub1 *piecep, dvoid **indp);
 
typedef sb4 (*OCICallbackOutBind)(dvoid *octxp, OCIBind *bindp, ub4 iter,
                                 ub4 index, dvoid **bufpp, ub4 **alenp,
                                 ub1 *piecep, dvoid **indp,
                                 ub2 **rcodep);
 
typedef sb4 (*OCICallbackDefine)(dvoid *octxp, OCIDefine *defnp, ub4 iter,
                                 dvoid **bufpp, ub4 **alenp, ub1 *piecep,
                                 dvoid **indp, ub2 **rcodep);

typedef sb4 (*OCICallbackLobRead)(dvoid *ctxp, CONST dvoid *bufp,
                                             ub4 len, ub1 piece);
/*
 * Called multiple times when the data is being read from the pipe
 * ctxp (IN) - is the context passed in by the user in OCILobRead call
 * bufp (IN) - the buffer containing the read data
 * len  (IN) - the length of the data in the buffer that is relevant
 * piece (IN) - one of the following, OCI_FIRST_PIECE, OCI_NEXT_PIECE
 */

typedef sb4 (*OCICallbackLobWrite)(dvoid *ctxp, dvoid *bufp, 
                                          ub4 *lenp, ub1 *piece);

/*
 * Called multiple times when the data is being written to the pipe
 * ctxp (IN) - is the context passed in by the user in OCILobRead call

 * bufp (IN/OUT) - the buffer into which the data to be written is copied
 * lenp  (OUT) - the length of the data in the buffer that is relevant
 * piece (OUT) - one of the following, OCI_NEXT_PIECE or OCI_LAST_PIECE
 */
/*--------------------------Failover Callback & Structure -------------------*/

typedef sb4 (*OCICallbackFailover)(dvoid *svcctx, dvoid *envctx,
                                   dvoid *fo_ctx, ub4 fo_type,
                                   ub4 fo_event);
/* Called at failover time if client has registered it. */typedef struct

{
  OCICallbackFailover callback_function;
  dvoid *fo_ctx;
} 
OCIFocbkStruct;



/*****************************************************************************
                         ACTUAL PROTOTYPE DECLARATIONS
                         OF FUNCTIONS PREVIOUSLY DESCRIBED
******************************************************************************/

sword   OCIInitialize   (ub4 mode, dvoid *ctxp, 
                 dvoid *(*malocfp)(dvoid *ctxp, size_t size),
                 dvoid *(*ralocfp)(dvoid *ctxp, dvoid *memptr, size_t newsize),
                 void   (*mfreefp)(dvoid *ctxp, dvoid *memptr) );

sword   OCIHandleAlloc(CONST dvoid *parenth, dvoid **hndlpp, ub4 type, 
                       size_t xtramem_sz, dvoid **usrmempp);

sword   OCIHandleFree(dvoid *hndlp, ub4 type);


sword   OCIDescriptorAlloc(CONST dvoid *parenth, dvoid **descpp, ub4 type,
                     size_t xtramem_sz, dvoid **usrmempp);

sword   OCIDescriptorFree(dvoid *descp, ub4 type);

sword   OCIEnvInit (OCIEnv **envp, ub4 mode, 
                    size_t xtramem_sz, dvoid **usrmempp);

sword   OCIServerAttach  (OCIServer *srvhp, OCIError *errhp,
                          CONST text *dblink, sb4 dblink_len, ub4 mode);

sword   OCIServerDetach  (OCIServer *srvhp, OCIError *errhp, ub4 mode);

sword   OCISessionBegin  (OCISvcCtx *svchp, OCIError *errhp, OCISession *usrhp,
                          ub4 credt, ub4 mode);

sword   OCISessionEnd   (OCISvcCtx *svchp, OCIError *errhp, OCISession *usrhp, 
                         ub4 mode);

sword   OCILogon (OCIEnv *envhp, OCIError *errhp, OCISvcCtx **svchp, 
		  CONST text *username, ub4 uname_len, 
		  CONST text *password, ub4 passwd_len, 
		  CONST text *dbname, ub4 dbname_len);

sword   OCILogoff (OCISvcCtx *svchp, OCIError *errhp);


sword   OCIPasswordChange   (OCISvcCtx *svchp, OCIError *errhp, 
                             CONST text *user_name, ub4 usernm_len, 
                             CONST text *opasswd, ub4 opasswd_len, 
                             CONST text *npasswd, ub4 npasswd_len, ub4 mode);

sword   OCIStmtPrepare   (OCIStmt *stmtp, OCIError *errhp, CONST text *stmt,
                          ub4 stmt_len, ub4 language, ub4 mode);

sword   OCIBindByPos  (OCIStmt *stmtp, OCIBind **bindp, OCIError *errhp,
		       ub4 position, dvoid *valuep, sb4 value_sz,
		       ub2 dty, dvoid *indp, ub2 *alenp, ub2 *rcodep,
		       ub4 maxarr_len, ub4 *curelep, ub4 mode);

sword   OCIBindByName   (OCIStmt *stmtp, OCIBind **bindp, OCIError *errhp,
			 CONST text *placeholder, sb4 placeh_len, 
                         dvoid *valuep, sb4 value_sz, ub2 dty, 
                         dvoid *indp, ub2 *alenp, ub2 *rcodep, 
                         ub4 maxarr_len, ub4 *curelep, ub4 mode);

sword   OCIBindObject  (OCIBind *bindp, OCIError *errhp, CONST OCIType *type, 
			dvoid **pgvpp, ub4 *pvszsp, dvoid **indpp, 
			ub4 *indszp);

sword   OCIBindDynamic   (OCIBind *bindp, OCIError *errhp, dvoid *ictxp,
			  OCICallbackInBind icbfp, dvoid *octxp,
			  OCICallbackOutBind ocbfp);

sword   OCIBindArrayOfStruct   (OCIBind *bindp, OCIError *errhp, 
                                ub4 pvskip, ub4 indskip,
                                ub4 alskip, ub4 rcskip);

sword   OCIStmtGetPieceInfo   (OCIStmt *stmtp, OCIError *errhp, 
                               dvoid **hndlpp, ub4 *typep,
                               ub1 *in_outp, ub4 *iterp, ub4 *idxp, 
                               ub1 *piecep);

sword   OCIStmtSetPieceInfo   (dvoid *hndlp, ub4 type, OCIError *errhp, 
                               CONST dvoid *bufp, ub4 *alenp, ub1 piece, 
                               CONST dvoid *indp, ub2 *rcodep);

sword   OCIStmtExecute  (OCISvcCtx *svchp, OCIStmt *stmtp, OCIError *errhp, 
                         ub4 iters, ub4 rowoff, CONST OCISnapshot *snap_in, 
                         OCISnapshot *snap_out, ub4 mode);

sword   OCIDefineByPos  (OCIStmt *stmtp, OCIDefine **defnp, OCIError *errhp,
			 ub4 position, dvoid *valuep, sb4 value_sz, ub2 dty,
			 dvoid *indp, ub2 *rlenp, ub2 *rcodep, ub4 mode);

sword   OCIDefineObject  (OCIDefine *defnp, OCIError *errhp, 
                          CONST OCIType *type, dvoid **pgvpp, 
                          ub4 *pvszsp, dvoid **indpp, ub4 *indszp);

sword   OCIDefineDynamic   (OCIDefine *defnp, OCIError *errhp, dvoid *octxp,
                            OCICallbackDefine ocbfp);

sword   OCIDefineArrayOfStruct  (OCIDefine *defnp, OCIError *errhp, ub4 pvskip,
                                 ub4 indskip, ub4 rlskip, ub4 rcskip);

sword   OCIStmtFetch   (OCIStmt *stmtp, OCIError *errhp, ub4 nrows, 
                        ub2 orientation, ub4 mode);

sword   OCIStmtGetBindInfo   (OCIStmt *stmtp, OCIError *errhp, ub4 size, 
                              ub4 startloc,
                              sb4 *found, text *bvnp[], ub1 bvnl[],
                              text *invp[], ub1 inpl[], ub1 dupl[],
                              OCIBind *hndl[]);

sword   OCIDescribeAny  (OCISvcCtx *svchp, OCIError *errhp, 
                         dvoid *objptr, 
                         ub4 objnm_len, ub1 objptr_typ, ub1 info_level,
			 ub1 objtyp, OCIDescribe *dschp);

sword   OCIParamGet (CONST dvoid *hndlp, ub4 htype, OCIError *errhp, 
                     dvoid **parmdpp, ub4 pos);

sword   OCIParamSet(dvoid *hdlp, ub4 htyp, OCIError *errhp, CONST dvoid *dscp,
                    ub4 dtyp, ub4 pos);

sword   OCITransStart  (OCISvcCtx *svchp, OCIError *errhp, 
                        uword timeout, ub4 flags );

sword   OCITransDetach  (OCISvcCtx *svchp, OCIError *errhp, ub4 flags );

sword   OCITransCommit  (OCISvcCtx *svchp, OCIError *errhp, ub4 flags);

sword   OCITransRollback  (OCISvcCtx *svchp, OCIError *errhp, ub4 flags);

sword   OCITransPrepare (OCISvcCtx *svchp, OCIError *errhp, ub4 flags);

sword   OCITransForget (OCISvcCtx *svchp, OCIError *errhp, ub4 flags);

sword   OCIErrorGet   (dvoid *hndlp, ub4 recordno, text *sqlstate,
                       sb4 *errcodep, text *bufp, ub4 bufsiz, ub4 type);

sword   OCILobAppend  (OCISvcCtx *svchp, OCIError *errhp, 
                       OCILobLocator *dst_locp,
                       OCILobLocator *src_locp);

sword   OCILobAssign (OCIEnv *envhp, OCIError *errhp, 
                      CONST OCILobLocator *src_locp, 
                      OCILobLocator **dst_locpp);

sword   OCILobCharSetForm (OCIEnv *envhp, OCIError *errhp, 
                           CONST OCILobLocator *locp, ub1 *csfrm);

sword   OCILobCharSetId (OCIEnv *envhp, OCIError *errhp, 
                         CONST OCILobLocator *locp, ub2 *csid);

sword   OCILobCopy (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *dst_locp,
                    OCILobLocator *src_locp, ub4 amount, ub4 dst_offset, 
                    ub4 src_offset);

sword   OCILobDisableBuffering (OCISvcCtx      *svchp,
                                OCIError       *errhp,
                                OCILobLocator  *locp);

sword   OCILobEnableBuffering (OCISvcCtx      *svchp,
                               OCIError       *errhp,
                               OCILobLocator  *locp);

sword   OCILobErase (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp,
                      ub4 *amount, ub4 offset);

sword   OCILobFileClose (OCISvcCtx *svchp, OCIError *errhp, 
                         OCILobLocator *filep);

sword   OCILobFileCloseAll (OCISvcCtx *svchp, OCIError *errhp);

sword   OCILobFileExists (OCISvcCtx *svchp, OCIError *errhp, 
			  OCILobLocator *filep,
			  boolean *flag);

sword   OCILobFileGetName (OCIEnv *envhp, OCIError *errhp, 
                           CONST OCILobLocator *filep, 
                           text *dir_alias, ub2 *d_length, 
                           text *filename, ub2 *f_length);

sword   OCILobFileIsOpen (OCISvcCtx *svchp, OCIError *errhp, 
                          OCILobLocator *filep,
                          boolean *flag);

sword   OCILobFileOpen (OCISvcCtx *svchp, OCIError *errhp, 
                        OCILobLocator *filep,
                        ub1 mode);

sword   OCILobFileSetName (OCIEnv *envhp, OCIError *errhp, 
                           OCILobLocator **filepp, 
                           CONST text *dir_alias, ub2 d_length, 
                           CONST text *filename, ub2 f_length);

sword   OCILobFlushBuffer (OCISvcCtx       *svchp,
                           OCIError        *errhp,
                           OCILobLocator   *locp,
                           ub4              flag);

sword   OCILobGetLength  (OCISvcCtx *svchp, OCIError *errhp, 
                          OCILobLocator *locp,
                          ub4 *lenp);

sword   OCILobIsEqual  (OCIEnv *envhp, CONST OCILobLocator *x, 
                        CONST OCILobLocator *y, 
                        boolean *is_equal);

sword   OCILobLoadFromFile (OCISvcCtx *svchp, OCIError *errhp, 
                            OCILobLocator *dst_locp,
       	                    OCILobLocator *src_filep, 
                            ub4 amount, ub4 dst_offset, 
                            ub4 src_offset);

sword   OCILobLocatorIsInit (OCIEnv *envhp, OCIError *errhp, 
                             CONST OCILobLocator *locp, 
                             boolean *is_initialized);

sword   OCILobRead  (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp,
                     ub4 *amtp, ub4 offset, dvoid *bufp, ub4 bufl, 
                     dvoid *ctxp, sb4 (*cbfp)(dvoid *ctxp, 
                                              CONST dvoid *bufp, 
                                              ub4 len, 
                                              ub1 piece),
                     ub2 csid, ub1 csfrm);

sword   OCILobTrim  (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp,
                     ub4 newlen);

sword   OCILobWrite  (OCISvcCtx *svchp, OCIError *errhp, OCILobLocator *locp,
                      ub4 *amtp, ub4 offset, dvoid *bufp, ub4 buflen, 
                      ub1 piece, dvoid *ctxp, 
                      sb4 (*cbfp)(dvoid *ctxp, 
                                  dvoid *bufp, 
                                  ub4 *len, 
                                  ub1 *piece),
                      ub2 csid, ub1 csfrm);

sword   OCIBreak (dvoid *hndlp, OCIError *errhp);

sword   OCIReset (dvoid *hndlp, OCIError *errhp);

sword   OCIServerVersion  (dvoid *hndlp, OCIError *errhp, text *bufp, 
                           ub4 bufsz,
                           ub1 hndltype);


sword   OCIAttrGet (CONST dvoid *trgthndlp, ub4 trghndltyp, 
                    dvoid *attributep, ub4 *sizep, ub4 attrtype, 
                    OCIError *errhp);

sword   OCIAttrSet (dvoid *trgthndlp, ub4 trghndltyp, dvoid *attributep,
                    ub4 size, ub4 attrtype, OCIError *errhp);

sword   OCISvcCtxToLda (OCISvcCtx *svchp, OCIError *errhp, Lda_Def *ldap);

sword   OCILdaToSvcCtx (OCISvcCtx **svchpp, OCIError *errhp, Lda_Def *ldap);

sword   OCIResultSetToStmt (OCIResult *rsetdp, OCIError *errhp);


/*
 ** Initialize the security package
 */
sword   OCISecurityInitialize (OCISecurity *sechandle, OCIError *error_handle);

sword   OCISecurityTerminate (OCISecurity *sechandle, OCIError *error_handle);

sword OCISecurityOpenWallet(OCISecurity *osshandle,
                            OCIError *error_handle,
                            size_t wrllen,
                            text *wallet_resource_locator,
                            size_t pwdlen,
                            text *password,
                            nzttWallet *wallet);

sword OCISecurityCloseWallet(OCISecurity *osshandle,
                             OCIError *error_handle,
                             nzttWallet *wallet);

sword OCISecurityCreateWallet(OCISecurity *osshandle,
                              OCIError *error_handle,
                              size_t wrllen,
                              text *wallet_resource_locator,
                              size_t pwdlen,
                              text *password,
                              nzttWallet *wallet);

sword OCISecurityDestroyWallet(OCISecurity *osshandle,
                               OCIError *error_handle,
                               size_t wrllen,
                               text *wallet_resource_locator,
                               size_t pwdlen,
                               text *password);

sword OCISecurityStorePersona(OCISecurity *osshandle,
                              OCIError *error_handle,
                              nzttPersona **persona,
                              nzttWallet *wallet);

sword OCISecurityOpenPersona(OCISecurity *osshandle,
                             OCIError *error_handle,
                             nzttPersona *persona);

sword OCISecurityClosePersona(OCISecurity *osshandle,
                              OCIError *error_handle,
                              nzttPersona *persona);

sword OCISecurityRemovePersona(OCISecurity *osshandle,
                               OCIError *error_handle,
                               nzttPersona **persona);

sword OCISecurityCreatePersona(OCISecurity *osshandle,
                               OCIError *error_handle,
                               nzttIdentType identity_type,
                               nzttCipherType cipher_type,
                               nzttPersonaDesc *desc,
                               nzttPersona **persona);

sword OCISecuritySetProtection(OCISecurity *osshandle,
                               OCIError *error_handle,
                               nzttPersona *persona,
                               nzttcef crypto_engine_function,
                               nztttdufmt data_unit_format,
                               nzttProtInfo *protection_info);

sword OCISecurityGetProtection(OCISecurity *osshandle,
                               OCIError *error_handle,
                               nzttPersona *persona,
                               nzttcef crypto_engine_function,
                               nztttdufmt * data_unit_format_ptr,
                               nzttProtInfo *protection_info);

sword OCISecurityRemoveIdentity(OCISecurity *osshandle,
                                OCIError *error_handle,
                                nzttIdentity **identity_ptr);

sword OCISecurityCreateIdentity(OCISecurity *osshandle,
                                OCIError *error_handle,
                                nzttIdentType type,
                                nzttIdentityDesc *desc,
                                nzttIdentity **identity_ptr);

sword OCISecurityAbortIdentity(OCISecurity *osshandle,
                               OCIError *error_handle,
                               nzttIdentity **identity_ptr);

sword OCISecurityFreeIdentity(OCISecurity *osshandle,
			      OCIError *error_handle,
			      nzttIdentity **identity_ptr);


sword OCISecurityStoreTrustedIdentity(OCISecurity *osshandle,
                                      OCIError *error_handle,
                                      nzttIdentity **identity_ptr,
                                      nzttPersona *persona);

sword OCISecuritySign(OCISecurity *osshandle,
                      OCIError *error_handle,
                      nzttPersona *persona,
                      nzttces signature_state,
                      size_t input_length,
                      ub1 *input,
                      nzttBufferBlock *buffer_block);

sword OCISecuritySignExpansion(OCISecurity *osshandle,
                               OCIError *error_handle,
                               nzttPersona *persona,
                               size_t inputlen,
                               size_t *signature_length);

sword OCISecurityVerify(OCISecurity *osshandle,
                        OCIError *error_handle,
                        nzttPersona *persona,
                        nzttces signature_state,
                        size_t siglen,
                        ub1 *signature,
                        nzttBufferBlock *extracted_message,
                        boolean *verified,
                        boolean *validated,
                        nzttIdentity **signing_party_identity);

sword OCISecurityValidate(OCISecurity *osshandle,
                          OCIError *error_handle,
                          nzttPersona *persona,
                          nzttIdentity *identity,
                          boolean *validated);

sword OCISecuritySignDetached(OCISecurity *osshandle,
                              OCIError *error_handle,
                              nzttPersona *persona,
                              nzttces signature_state,
                              size_t input_length,
                              ub1 * input,
                              nzttBufferBlock *signature);

sword OCISecuritySignDetExpansion(OCISecurity *osshandle,
                                  OCIError *error_handle,
                                  nzttPersona *persona,
                                  size_t input_length,
                                  size_t *required_buffer_length);

sword OCISecurityVerifyDetached(OCISecurity *osshandle,
                                OCIError *error_handle,
                                nzttPersona *persona,
                                nzttces signature_state,
                                size_t data_length,
                                ub1 *data,
                                size_t siglen,
                                ub1 *signature,
                                boolean *verified,
                                boolean *validated,
                                nzttIdentity **signing_party_identity);

sword OCISecurity_PKEncrypt(OCISecurity *osshandle,
                            OCIError *error_handle,
                            nzttPersona *persona,
                            size_t number_of_recipients,
                            nzttIdentity *recipient_list,
                            nzttces encryption_state,
                            size_t input_length,
                            ub1 *input,
                            nzttBufferBlock *encrypted_data);

sword OCISecurityPKEncryptExpansion(OCISecurity *osshandle,
                                    OCIError *error_handle,
                                    nzttPersona *persona,
                                    size_t number_recipients,
                                    size_t input_length,
                                    size_t *buffer_length_required);

sword OCISecurityPKDecrypt(OCISecurity *osshandle,
                           OCIError *error_handle,
                           nzttPersona *persona,
                           nzttces encryption_state,
                           size_t input_length,
                           ub1 *input,
                           nzttBufferBlock *encrypted_data);

sword OCISecurityEncrypt(OCISecurity *osshandle,
                         OCIError *error_handle,
                         nzttPersona *persona,
                         nzttces encryption_state,
                         size_t input_length,
                         ub1 *input,
                         nzttBufferBlock *encrypted_data);

sword OCISecurityEncryptExpansion(OCISecurity *osshandle,
                                  OCIError *error_handle,
                                  nzttPersona *persona,
                                  size_t input_length,
                                  size_t *encrypted_data_length);

sword OCISecurityDecrypt(OCISecurity *osshandle,
                         OCIError *error_handle,
                         nzttPersona *persona,
                         nzttces decryption_state,
                         size_t input_length,
                         ub1 *input,
                         nzttBufferBlock *decrypted_data);

sword OCISecurityEnvelope(OCISecurity *osshandle,
                          OCIError *error_handle,
                          nzttPersona *persona,
                          size_t number_of_recipients,
                          nzttIdentity *identity,
                          nzttces encryption_state,
                          size_t input_length,
                          ub1 *input,
                          nzttBufferBlock *enveloped_data);

sword OCISecurityDeEnvelope(OCISecurity *osshandle,
                            OCIError *error_handle,
                            nzttPersona *persona,
                            nzttces decryption_state,
                            size_t input_length,
                            ub1 *input,
                            nzttBufferBlock *output_message,
                            boolean *verified,
                            boolean *validated,
                            nzttIdentity **sender_identity);

sword OCISecurityKeyedHash(OCISecurity *osshandle,
                           OCIError *error_handle,
                           nzttPersona *persona,
                           nzttces hash_state,
                           size_t input_length,
                           ub1 *input,
                           nzttBufferBlock *keyed_hash);

sword OCISecurityKeyedHashExpansion(OCISecurity *osshandle,
                                    OCIError *error_handle,
                                    nzttPersona *persona,
                                    size_t input_length,
                                    size_t *required_buffer_length);

sword OCISecurityHash(OCISecurity *osshandle,
                      OCIError *error_handle,
                      nzttPersona *persona,
                      nzttces hash_state,
                      size_t input,
                      ub1 *input_length,
                      nzttBufferBlock *hash);

sword OCISecurityHashExpansion(OCISecurity *osshandle,
                               OCIError *error_handle,
                               nzttPersona *persona,
                               size_t input_length,
                               size_t *required_buffer_length);

sword OCISecuritySeedRandom(OCISecurity *osshandle,
                            OCIError *error_handle,
                            nzttPersona *persona,
                            size_t seed_length,
                            ub1 *seed);

sword OCISecurityRandomBytes(OCISecurity *osshandle,
                             OCIError *error_handle,
                             nzttPersona *persona,
                             size_t number_of_bytes_desired,
                             nzttBufferBlock *random_bytes);

sword OCISecurityRandomNumber(OCISecurity *osshandle,
                              OCIError *error_handle,
                              nzttPersona *persona,
                              uword *random_number_ptr);

sword OCISecurityInitBlock(OCISecurity *osshandle,
                           OCIError *error_handle,
                           nzttBufferBlock *buffer_block);

sword OCISecurityReuseBlock(OCISecurity *osshandle,
                            OCIError *error_handle,
                            nzttBufferBlock *buffer_block);

sword OCISecurityPurgeBlock(OCISecurity *osshandle,
                            OCIError *error_handle,
                            nzttBufferBlock *buffer_block);

sword OCISecuritySetBlock(OCISecurity *osshandle,
                          OCIError *error_handle,
                          uword flags_to_set,
                          size_t buffer_length,
                          size_t used_buffer_length,
                          ub1 *buffer,
                          nzttBufferBlock *buffer_block);

sword OCISecurityGetIdentity(OCISecurity   *osshandle,
                             OCIError      *error_handle,
                             size_t         namelen,
                             text          *distinguished_name,
                             nzttIdentity **identity);

sword OCIAQEnq(OCISvcCtx *svchp, OCIError *errhp, text *queue_name,
		 OCIAQEnqOptions *enqopt, OCIAQMsgProperties *msgprop,
		 OCIType *payload_tdo, dvoid **payload, dvoid **payload_ind, 
		 OCIRaw **msgid, ub4 flags); 

sword OCIAQDeq(OCISvcCtx *svchp, OCIError *errhp, text *queue_name,
		 OCIAQDeqOptions *deqopt, OCIAQMsgProperties *msgprop,
		 OCIType *payload_tdo, dvoid **payload, dvoid **payload_ind, 
		 OCIRaw **msgid, ub4 flags); 


/*-------------------------- Extensions to XA interface ---------------------*/

/* ------------------------- xaosvch ----------------------------------------*/
/*
   NAME
     xaosvch  -  XA Oracle get SerViCe Handle
   DESCRIPTION
     Given a database name return the service handle that is used by the
     XA library
   NOTE
     This macro has been provided for backward compatibilty with 8.0.2
*/
OCISvcCtx *xaosvch(text *dbname);

/* ------------------------- xaoSvcCtx --------------------------------------*/
/*
   NAME
     xaoSvcCtx  -  XA Oracle get SerViCe ConTeXt
   DESCRIPTION
     Given a database name return the service handle that is used by the
     XA library
   NOTE
     This routine has been provided for APs to get access to the service
     handle that XA library uses. Without this routine APs must use SQLLIB
     routine sqlld2 to get access to the Logon data area registered by the
     XA library
*/
OCISvcCtx *xaoSvcCtx(text *dbname);

/* ------------------------- xaoEnv -----------------------------------------*/
/*
   NAME
     xaoEnv  -  XA Oracle get ENvironment Handle
   DESCRIPTION
     Given a database name return the environment handle that is used by the
     XA library
   NOTE
     This routine has been provided for APs to get access to the environment
     handle that XA library uses. Without this routine APs must use SQLLIB
     routine sqlld2 to get access to the Logon data area registered by the
     XA library
*/
OCIEnv *xaoEnv(text *dbname);

/* ------------------------- xaosterr ---------------------------------------*/
/*
   NAME
     xaosterr  -  XA Oracle get xa STart ERRor code
   DESCRIPTION
     Given an oracle error code return the XA error code
 */
int xaosterr(OCISvcCtx *svch, sb4 error);
/*-------------------------- End Extensions ---------------------------------*/

/*---------------------------------------------------------------------------
                          PRIVATE FUNCTIONS
  ---------------------------------------------------------------------------*/

            /* the following functions are depracated and should not be used */

sword   OCIStmtBindByPos  (OCIStmt *stmtp, OCIBind *bindp, OCIError *errhp,
                  ub4 position, dvoid *valuep, sb4 value_sz,
                  ub2 dty, dvoid *indp, ub2 *alenp, ub2 *rcodep,
                  ub4 maxarr_len, ub4 *curelep, ub4 mode);


sword   OCIStmtBindByName  (OCIStmt *stmtp, OCIBind *bindp, OCIError *errhp,
                  CONST text *placeholder, sb4 placeh_len, dvoid *valuep, 
                  sb4 value_sz, ub2 dty, dvoid *indp, ub2 *alenp, 
                  ub2 *rcodep, ub4 maxarr_len, ub4 *curelep, ub4 mode);

sword   ocidefn  (OCIStmt *stmtp, OCIDefine *defnp, OCIError *errhp,
                  ub4 position, dvoid *valuep, sb4 value_sz, ub2 dty,
                  dvoid *indp, ub2 *rlenp, ub2 *rcodep, ub4 mode);


#endif                                                       /* OCIAP_ORACLE */
