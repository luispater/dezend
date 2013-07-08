/* DISABLE check_long_lines */
/*
  $Header: /netrcs/RCS/oracle/network/tns/defs/RCS/tnsapi.h,v 1.5 1996/04/02 00:02:48 mhill Exp $
*/
/* ENABLE check_long_lines */

/* Copyright (c) 1995, 1996 by Oracle Corporation.  All rights reserved. */

/*

NAME
  tnsapi.h

DESCRIPTION
  SQL*Net Open API functions.

FUNCTIONS
  tnsopen()    -   open a TNS handle
  tnsclose()   -   close a TNS handle
  tnssend()    -   send data over TNS handle
  tnsrecv()    -   receive data over TNS handle
  tnscontrol() -   issue a control command on a TNS handle


NOTES
  These functions provides transparent access to the underlying session 
  implementation SQL*NET.

*/

#ifndef TNSAPI
#define TNSAPI

enum tnsapiopcode {
/* TNS API operations */
  TNSAPIOOPEN,                
  TNSAPIOCLOSE,               
  TNSAPIOSEND,                
  TNSAPIORECV,
  TNSAPICTL,
  TNSAPICNONBLOCKING,
  TNSAPICBLOCKING
};

/* TNS API error codes */
/* More will be added as actual coding and testing starts */
/* DISABLE check_naming */
/* DISABLE check_str_mem */
enum tnsapierrcode {
  TNSAPIEBASE = 20000,

  SDFAIL_TNSAPIE = TNSAPIEBASE+2,
/*
 * SDFAIL_TNSAPIE: The underlying "send" command failed in tnssend().
 */

  RECVFAIL_TNSAPIE = TNSAPIEBASE+3,
/*
 * RECVFAIL_TNSAPIE: The underlying "receive" command failed in tnsrecv().
 */

  INVSVROP_TNSAPIE = TNSAPIEBASE+4,
/*
 * INVSVROP_TNSAPIE: Operation is invalid as the server.
 */

  INVCLIOP_TNSAPIE = TNSAPIEBASE+5,
/*
 * INVCLIOP_TNSAPIE: Operation is invalid as the client.
 */

  HDLUNINI_TNSAPIE = TNSAPIEBASE+6,
/*
 * HDLUNINI_TNSAPIE: The connection should be initialized by 
 * calling tnsopen(). 
 */

  INHFAIL_TNSAPIE = TNSAPIEBASE+7,
/*
 * INHFAIL_TNSAPIE: server failed in inheriting the connection from
 * the listener.
 */

  ACPTFAIL_TNSAPIE = TNSAPIEBASE+8,
/*
 * ACPTFAIL_TNSAPIE: server failed in accepting the connection request
 * from the client
 */

  NULHDL_TNSAPIE = TNSAPIEBASE+9,
/*
 * NULHDL_TNSAPIE: a null handle is passed into the tnsxxx calls, which
 * is not allowed
 */

  INVOP_TNSAPIE = TNSAPIEBASE+10,
/*
 * INVOP_TNSAPIE: invalid operation code is passed into tnsapi() call
 */

  MALFAIL_TNSAPIE = TNSAPIEBASE+11,
/*
 * MALFAIL_TNSAPIE: a malloc failed in TNS API calls
 */

  NLINIFAIL_TNSAPIE = TNSAPIEBASE+12,
/*
 * NLINIFAIL_TNSAPIE: failed in NL initialization 
 */

  NMTOOLONG_TNSAPIE = TNSAPIEBASE+13,
/*
 * NMTOOLONG_TNSAPIE: service name too long
 */

  CONFAIL_TNSAPIE = TNSAPIEBASE+14,
/*
 * CONFAIL_TNSAPIE: client connect request failed
 */

  LSNFAIL_TNSAPIE = TNSAPIEBASE+15,
/*
 * LSNFAIL_TNSAPIE: server failed to listen for connect request
 */

  ANSFAIL_TNSAPIE = TNSAPIEBASE+16,
/*
 * ANSFAIL_TNSAPIE: server failed to answer connect request
 */

  NMRESFAIL_TNSAPIE = TNSAPIEBASE+17,
/*
 * NMRESFAIL_TNSAPIE: failed to resolve service name
 */

  WOULDBLOCK_TNSAPIE = TNSAPIEBASE+18,
/*
 * WOULDBLOCK_TNSAPIE: operation would block
 */

  CTLFAIL_TNSAPIE = TNSAPIEBASE+19,
/*
 * CTLFAIL_TNSAPIE: control call failed
 */

  TNSAPIE_ERROR = TNSAPIEBASE+20,
/*
 * TNSAPIE_ERROR: generic TNS error occured
 */

  INVCTL_TNSAPIE = TNSAPIEBASE+21
/*
 * INVCTL_TNSAPIE: invalid operation requested in control call
 */
 
};
/* ENABLE check_str_mem */

int tnsopen(/*_ void **handlep, const char *name _*/);
/*
 * Operation
 *   TNSOPEN
 *
 * Description
 *   Initialize TNSAPI per-connection handle. This function must be the
 *   first TNS call that a user makes.
 *
 *   Name contains a service name in the same format as those in 
 *   configuration files in the case of a client. In the case of a server,
 *   name is a NULL.
 *
 * Synopsis
 *   int tnsopen(handlep, name)
 *   void **handlep;
 *   const char *name;
 *
 * Paramters
 *   handlep (IN/OUT) - Address to receive TNS connection handle
 *   name    (IN)     - service name
 *      
 * Requires
 *   The handlep paramter must not be NULL
 *
 * Returns
 *   Upon successful completion a zero value is returned. Otherwise, a
 *   positive TNS API error is returned, which is defined in this header 
 *   file. 
 */
 
int tnsclose(/*_ void **handlep _*/);
/*
 * Operation:
 *  TNSCLOSE
 *
 * Description
 *  Shut down the connection. This function must be called by the user
 *  to close the connection and release the handle properly.
 *
 * Synopsis
 *   int tnsclose(handlep)
 *   void **handlep;
 *
 * Paramters
 *   handlep(IN/OUT) - Address of a pointer to a TNS connection handle    
 * 
 * Requires
 *   The handlep paramter must not be NULL
 *  
 * Returns
 *   Upon successful completion a zero value is returned, and *handlep
 *   is set to NULL. Otherwise, a positive TNS API error number  is 
 *   returned, which is defined in this header file. 
 */


int tnssend(/*_ void *handle, const void *data, size_t *length _*/);
/*
 * Operation
 *   TNSSEND
 *
 * Description
 *   Send data to the TNS handle.
 *
 *   In the first call to tnssend() on the client side, connection is
 *   first established before data is sent to the handle.  The client must 
 *   first call tnssend() after tnsopen() to establish a connection to the 
 *   server. It is an error if server calls tnssend() after calling 
 *   tnsopen().
 *
 * Synopsis
 *   int tnssend(handle, data, length)
 *   void *handle;
 *   const void *data;
 *   size_t *length;
 *
 * Paramters
 *   handle(IN/OUT) - pointer to TNS connection handle returned by 
 *                    tnsopen() 
 *   data(IN)   -     pointer to data to be sent
 *   length(IN/OUT) - pointer to the length of data to be sent in bytes
 *                    and the actual number of bytes written on return.
 *
 * Requires
 *   The paramters must not be NULL
 * 
 * Returns
 *   Upon successful completion a zero value is returned, and the actual 
 *   number of bytes written is returned as the value pointed to by the
 *   length paramter. Otherwise, a positive TNS API error number is 
 *   returned, which is defined in this header file. 
 */


int tnsrecv(/*_ void *handle, void *data, size_t *length _*/);
/*
 * Operation
 *   TNSRECV
 *
 * Description
 *   Receive data from the TNS handle
 *  
 *   In the first call to tnsrecv() on the server side, connection is 
 *   first established before data is received from the handle. The server
 *   must first call tnsrecv() after tnsopen() to accept the connection
 *   from the client. 
 *
 * Synopsis
 *   int tnsrecv(handle, data, length)
 *   void *handle;
 *   void *data;
 *   size_t *length;
 *
 * Paramters
 *   handle(IN/OUT) - pointer to TNS connection handle returned by 
 *                    tnsopen()
 *   data(IN/OUT)   - pointer to buffer to receive data
 *   length(IN/OUT) - pointer to the length of buffer to receive data
 *                    and actual number of bytes received on return
 *
 * Requires
 *   All paramters must not be NULL
 *  
 * Returns
 *   Upon successful completion a zero value is returned, and the actual 
 *   number of bytes received is returned as the value pointed to by the
 *   length paramter. Otherwise, a positive TNS API error number is 
 *   returned, which is defined in this header file.
 */

int tnscontrol(/*_ void *handle, int cmd _*/);
/*
 * Operation
 *   TNSCONTROL
 *
 * Description
 *   Set an option on a connection handle.
 * 
 * Synopsis
 *   int tnscontrol(handle, cmd)
 *   void *handle;
 *   int cmd;
 * 
 * Parameters
 *   handle(IN) - pointer to TNS connection handle as returned by tnsopen().
 *   cmd(IN) - option to apply to the connection.  Currently supported 
 *             values are:
 *     TNSAPICNONBLOCKING - set connection into nonblocking mode
 *     TNSAPICBLOCKING - set connection into blocking mode
 * 
 * Requires
 *   handle must not be NULL, and cmd must be one of the supported commands.
 * 
 * Returns
 *   0 if option is successfully set
 *   CTLFAIL_TNSAPIE if a TNS error occurs while performing the control call
 */
  

/*
 * Public macro interfaces 
 */
#define tnsopen(handlep, name) tnsapi(TNSAPIOOPEN, handlep, name)
#define tnsclose(handlep) tnsapi(TNSAPIOCLOSE, handlep)
#define tnssend(handle, data, length) tnsapi(TNSAPIOSEND, handle, data, length)
#define tnsrecv(handle, data, length) tnsapi(TNSAPIORECV, handle, data, length)
#define tnscontrol(handle, cmd) tnsapi(TNSAPICTL, handle, cmd)

/* ENABLE check_naming */

#endif /* TNSAPI */
