/******************************************************************************
**
** Source File Name: SQLUVEND
**
** (C) COPYRIGHT International Business Machines Corp. 1987, 1997
** All Rights Reserved
** Licensed Materials - Property of IBM
**
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
**
** Function = Include File defining:
**              - Interface to vendor devices.
**              - Structures required by vendor interfaces.
**              - Defined symbols and return codes to be
**                returned from vendor interfaces.
**
*******************************************************************************/
#ifndef _H_SQLUVEND
#define _H_SQLUVEND

#ifdef __cplusplus
extern "C" {
#endif

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

/******************************************************/
/* This include file is to be used by backup vendors. */
/******************************************************/


#define SQLUV_OK               0   /* Operation is successful */
#define SQLUV_LINK_EXIST       1   /* Session activated previously */
#define SQLUV_COMM_ERROR       2   /* Communication error with device */
#define SQLUV_INV_VERSION      3   /* The DB2 and vendor products are incompatible */
#define SQLUV_INV_ACTION       4   /* Invalid action is requested */
#define SQLUV_NO_DEV_AVAIL     5   /* No device is available for use at the moment */
#define SQLUV_OBJ_NOT_FOUND    6   /* Object specified cannot be found */
#define SQLUV_OBJS_FOUND       7   /* More than 1 object matches specification is found */
#define SQLUV_INV_USERID       8   /* Invalid userid specified */
#define SQLUV_INV_PASSWORD     9   /* Invalid password provided */
#define SQLUV_INV_OPTIONS      10  /* Invalid options specified */
#define SQLUV_INIT_FAILED      11  /* Initialization failed */
#define SQLUV_INV_DEV_HANDLE   12  /* Invalid device handle */
#define SQLUV_BUFF_SIZE        13  /* Invalid buffer size specified */
#define SQLUV_END_OF_DATA      14  /* NOT USED */
#define SQLUV_END_OF_TAPE      15  /* End of tape reached. Requires attention */
#define SQLUV_DATA_RESEND      16  /* Device requested to have last buffer sent again */
#define SQLUV_COMMIT_FAILED    17  /* Commit request failed */
#define SQLUV_DEV_ERROR        18  /* Device error */
#define SQLUV_WARNING          19  /* Warning. see return code */
#define SQLUV_LINK_NOT_EXIST   20  /* Session not activated previously */
#define SQLUV_MORE_DATA        21  /* More data to come */
#define SQLUV_ENDOFMEDIA_NO_DATA   22  /* End of media encountered with no data */
#define SQLUV_ENDOFMEDIA           23  /* ENd of media encountered */
#define SQLUV_MAX_LINK_GRANT   24  /* Max no. of link established */
#define SQLUV_IO_ERROR         25  /* I/O error encountered */
#define SQLUV_DELETE_FAILED    26  /* Delete object fails */
#define SQLUV_INV_BKUP_FNAME   27  /* Invalid backup filename provided */
#define SQLUV_NOT_ENOUGH_SPACE 28  /* insufficient space for estimated database size */
#define SQLUV_ABORT_FAILED     29  /* Abort request failed */

#define SQLUV_COMMIT           0
#define SQLUV_ABORT            1
#define SQLUV_TERMINATE        2    /* For use by ADSM only */

#define SQLUV_COMMENT_LEN     30

typedef struct Return_code
{
        long int   return_code;  /* return code from the vendor function  */
        char       description[SQLUV_COMMENT_LEN];
        /* descriptive message                   */
        void       *reserve;     /* reserve for future use                */
} Return_code;


typedef  struct list_entry
{
    int       entry_len;        /* including null terminator */
    char     *pentry;
} list_entry;

typedef   struct sqlu_gen_list
{
    int                    num_of_entries;
    struct list_entry     *entry;
} sqlu_gen_list;

/* calling action values
*/
#define SQLUV_WRITE       'W'  /* to write */
#define SQLUV_READ        'R'  /* to read  */

typedef struct DB2_info
{
  char     *DB2_id;            /* DB2_id                            */
  char     *version;           /* Current DB2 version               */
  char     *release;           /* Current DB2 release               */
  char     *level;             /* Current DB2 level                 */
  char     *action;            /* Caller action                     */
  char     *filename;          /* file to read or write.            */
  char     *server_id;         /* Unique name identifying db server */
  char     *db2instance;       /* db2insance id                     */
  char     *type;              /* When action is SQLUV_WRITE,       */
                               /*  0 - full database backup         */
                               /*  3 - datapool level backup        */
                               /* When action is SQLUV_READ,        */
                               /*  0 - full restore                 */
                               /*  4 - online tablespace restore    */
                               /*  5 - history file restore         */
                               /*  6 - tablespace table restore     */
                               /*  7 - history file and tablespace  */
  char     *dbname;            /* Database alias to be backed up or */
                               /*   recovered                       */
  char     *alias;             /* Database alias to be backed up or recovered */
  char     *timestamp;         /* Timestamp to identify the backup image */
  char     *sequence;          /* Sequence number within a backup        */

  struct sqlu_gen_list         /* List of objects in the backup     */
                  *obj_list;
  long      max_bytes_per_txn; /* Transfer buffer size want to use  */
  char     *image_filename;    /* Not used.                         */
  void     *reserve;           /* Reserved for future use           */
  char     *nodename;          /* name of node at which the backup  */
                               /* was generated                     */
  char     *password;          /* password for the node at which the */
                               /* backup was generated              */
  char     *owner;             /* backup originator ID              */
  char     *mcNameP;           /* Management Class                  */
  char      nodeNum;           /* Node number.                      */
} DB2_info ;



typedef struct Vendor_info
{
  char     *vendor_id;         /* An identifier for the vendor      */
  char     *version;           /* Current version                   */
  char     *release;           /* Current release                   */
  char     *level;             /* Current level                     */
  char     *server_id;         /* Unique name identifying db server */
  long      max_bytes_per_txn; /* Vendor supports max bytes / transfer*/
  long      num_objects_in_backup;   /* no. of objects found in backup*/
  void     *reserve;           /* Reserve for future use.           */
} Vendor_info;



typedef struct Init_input
{
   struct DB2_info  *DB2_session;   /* DB2 Identifier for session.  */
   unsigned short   size_options;   /* size of options field.       */
   unsigned long    size_HI_order;  /* High order 32 bits of DB size*/
   unsigned long    size_LOW_order; /* Low order 32 bits of DB size */
   void             *options;       /* options passed in by user.   */
   void             *reserve;       /* reserve for future use.      */
   char             *prompt_lvl;    /* Prompt level                 */
   unsigned short   num_sessions;   /* Number of sessions           */
} Init_input;


typedef struct Init_output
{
   struct Vendor_info * vendor_session; /* Vendor id for the session */
   void               * pVendorCB;      /* vendor control block      */
   void               * reserve;        /* reserve for future use.   */
} Init_output ;

typedef struct Data
{
   long   obj_num;                 /* indicate which obj to be read */
                                   /* It is useful for restore.     */
   long   buff_size;               /* buffer size to be used        */
   long   actual_buff_size;        /* actual bytes read or written  */
   void   *dataptr;                /* Pointer to the data buffer    */
   void   *reserve;                /* reserve for future use        */
} Data;




/* To initialize or link to the device. */
int sqluvint ( struct Init_input   *,
               struct Init_output  *,
               struct Return_code  *);


/* To read data from initialized device. */
int sqluvget ( void *             ,
               struct Data         *,
               struct Return_code  *);


/* To write data to the initialized device. */
int sqluvput ( void *             ,
               struct Data         *,
               struct Return_code  *);


/* To end or unlink the device and free all its related resources. */
int sqluvend ( long int  ,
               void *    ,
               struct Init_output  *,
               struct Return_code  *);


/* To delete a committed session. */
int sqluvdel ( struct Init_input   *,
               struct Init_output  *,
               struct Return_code  *);

#if (defined(DB2OS2) || defined(DB2NT) || defined(DB2WIN))
#pragma pack()
#elif (defined(DB2MAC))
#pragma align
#elif (defined(DB2HP) || defined(DB2SNI))

#elif (defined(DB2AIX) || defined(DB2SUN))
#pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif

#endif
