// tabs = 4
//========================================================================
// COPYRIGHT NOTICE:
//				Copyright (C) 1995, Robert B. Denny, Pasadena, California
//				All Rights Reserved
// PROPRIETARY RIGHTS NOTICE: 
//				This source code is the property of Robert B. Denny of
//				Pasadena, California, and is furnished under license only.
//========================================================================
// TITLE:		WSAPI.H
//
// FACILITY:	WebSite Server for Windows NT and Windows 95
//
// ABSTRACT:	Definitions for WebSite Extension API (WSAPI)
//
// ENVIRONMENT:	WebSite 1.1 or later, WSAPI 0.1 (experimental)
//				Microsoft Windows Windows NT 3.5x, Windows 95
//				Developed under Microsoft Visual C++ Version 2.2
//
// AUTHOR:		Robert B. Denny
//
// Edit Log:
//
// When			Who		What
//----------	---		--------------------------------------------------
// 25-Aug-95	rbd		Initial edit
// 07-Sep-95	rbd		Remove useless routines, add new ones, rev minor
// 09-Sep-95	rbd		Name changes, rev minor version to 3
// 11-Sep-95	rbd		Add user_1, user_2, and S-HTTP fields to TCTX 
//						rev minor version to 4.
// 19-Sep-95	rbd		Exposed RNG functions
// 26-Sep-95	rbd		Add port number to TCTX, define CONST to supress
//						in C++, add C++ wrappers, change name of socket
// 28-Sep-95	rbd		Export S-HTTP cert/key initializer callback, add
//						new S-HTTP op-code for request header cleanup.
//						Add CN and certificate for this identity to TCTX
//						Rev minor to 6.
// 11-Oct-95	rbd		Comment changes, change interface to url_to_file()
//						Rev minor to 7.
// 13-Oct-95	rbd		Expose evaluate_access(), rev to 8.
// 17-Oct-95	rbd		Add tp->params for byte range support. Rev to 9.
// 09-Nov-95	rbd		Add keep_alive to TCTX, rev 11
// 12-Nov-95	rbd		Enlarge content type/encoding in TCB/TCTX -> rev12
// 16-Nov-95	rbd		New byte ranging, changes to TCTX -> rev 13
// 02-Dec-95	rbd		Promote User-Agent to TCTX -> rev 14
// 15-Dec-95	rbd		Expand tp->params, tp->request_range to MAX size.
//						Adobe Amber generates large range requests. ->15
// 16-Feb-96	rbd		VC++ 4.0 -> 16
// 17-Feb-96	rbd		Back to Rev15 for SHTTP DLL
// 07-Mar-96	rbd		Add form decoder stuff
// 12-Mar-96	rbd		Exposed the MD5 routines. Version now 1.0
// 13-Apr-96	rbd		New get_server_variable(), Version 1.1
// 03-Sep-96	rbd		Rev WSAPI to 1.2 (bug fixes only)
// 04-Jun-97	rbd		New SECOPT bits, release for VC++ 5 and WebSite 2
//						No change to WSAPI itself, remains at 1.2
//========================================================================
#if !defined _WSAPI_H_
#define _WSAPI_H_ 1

#include <time.h>

#if defined __cplusplus
#undef CONST
#define CONST
extern "C" {
#else
#define CONST const
#endif

// ===============
// VERSION CONTROL
// ===============		 |--->(in fact, don't edit this file at all!)
//			-----------------------------
// WARNING! DO NOT EDIT THESE DEFINITIONS! USE THEM IN THE
// CALL TO bind_wcgi(). IF YOU COMPILE YOUR HOOK WITH THIS
// HEADER FILE, IT HAS THE WSAPI VERSION INDICATED BELOW
//
#define MAJOR_VERSION	1
#define MINOR_VERSION	2

// ------
// Limits
// ------
#define MAX_TYPE_LEN	64				// Longest postproc content type
#define MAX_PROC_DLLS	32				// Max # postprocessors
#define MAX_NAME_LEN	64				// Longest CGI DLL name
#define MAX_CGI_DLLS	32				// MAX # CGI DLLs
#define SML_STRING_LEN 	64				// Small string buffer
#define MED_STRING_LEN	256				// Medium string buffer				
#define MAX_STRING_LEN	1024			// Big string buffer
#define HUGE_STRING_LEN 8192			// Very large string buffer
#define MAX_EXT_HEADERS 100				// Max extra request or CGI/1.1 headers


//-------------------
//	HTTP Result Codes
//-------------------
#define DOCUMENT_FOLLOWS	200
#define CREATED				201
#define ACCEPTED			202
#define PARTIAL_INFORMATION	203
#define NO_RESPONSE			204
#define DELETED				205
#define MODIFIED			206
#define MOVED				301
#define REDIRECT			302
#define USE_LOCAL_COPY		304
#define BAD_REQUEST			400
#define AUTH_REQUIRED		401
#define FORBIDDEN			403
#define NOT_FOUND			404
#define SERVER_ERROR		500
#define NOT_IMPLEMENTED		501

//--------------------
//	Supported methods
//--------------------
//
// Numeric method codes used in some interfaces
//
#define M_GET		0 
#define M_PUT		1
#define M_POST		2
#define	M_DELETE	3
#define	M_LINK		4
#define	M_UNLINK	5
#define	M_ANY		255

//---------------
//	Object types
//---------------
//
// Returned by url_to_file()
//
#define REDIRECT_URL	-1
#define STD_DOCUMENT	0
#define SCRIPT_DOS		1		// Used as intfc parameter to exec_cgi_script
#define SCRIPT_WIN		2		// Used as intfc parameter to exec_cgi_script
#define SCRIPT_SHELL	4		// Used as intfc parameter to exec_cgi_script

// --------------------------------
// Authentication Hook Return Codes
// --------------------------------
#define AUTH_REJECT		0		// Reject username/password
#define AUTH_ACCEPT		1		// Accept username/password
#define AUTH_INTERNAL	2		// Use internal authentication

//---------------------
//	Access option codes
//---------------------
#define SECOPT_OR_CLASS_USERS	0x00000001	// "OR" logic for class/user access
#define SECOPT_SSL_ONLY			0x00000002	// Accessible via SSL only
#define	SECOPT_NO_BROWSE		0x00000004	// Disable directory browsing
#define SECOPT_NO_EXEC			0x00000008	// Disable any exec (API/CGI)
#define SECOPT_IMPERSONATE		0x00000010	// Run in user/anon security context (NT only)
#define SECOPT_ALLOW_NTLM		0x00000020	// Permit NTLM authentication (NT only)

// ====================
// S-HTTP REQUEST CODES
// ====================
//
// Used in TCB to tell Terisa hook what to do
//
#define SHTTP_HANDLE_SECURE_METHOD		1
#define SHTTP_PROCESS_REQUEST_HEADERS	2
#define	SHTTP_HANDLE_SECURE_RESPONSE	3
#define SHTTP_TRANSACTION_CLEANUP		4

// -----------
// FATAL Macro
// -----------
//
// Use this when you need to "bail out". It will generate
// an exception that will cause the server to alert and
// disable your hook DLL. Use it for "serious" errors that
// could compromise the DLL or the server. For "normal"
// errors, call the server-exported die() function or use
// the ABORT macro.
//
#define FATAL			RaiseException(0xE1000001, 0, 0, NULL)

// -----------
// ABORT Macro
// -----------
//
// Use this when you need to silently end the current request.
// Calling this will end the request, sending a TCP "reset"
// packet to the browser. It will not cause your DLL to be
// disabled.
//
#define ABORT			RaiseException(0xE100000F, 0, 0, NULL)

// ------------------------------------
// Message Digest 5 (MD5, see RFC 1321)
// ------------------------------------
typedef struct {
	DWORD hash[4];
	DWORD bytes[2];
	DWORD input[16];
} MD5Context;

// ------------
// Form decoder
// ------------
typedef void *FORM_CTX;					// Decoding context handle
typedef struct {						// Field descriptor
	char name[MED_STRING_LEN];			// Field name
	BYTE *data;							// -> field data
	DWORD len;							// Field data length
	char ctype[MED_STRING_LEN];			// File content-type
	char xftype[MED_STRING_LEN];		// File content-transfer-encoding
	char fname[MED_STRING_LEN];			// Client's file name (file fields)
}FIELD, *PFIELD;

// -------------------------
// Extra header info in TCTX
// -------------------------
typedef struct {
	char *key;
	char *value;
} xhdr;

//---------------------
//	Transaction Context
//---------------------
//
// This is the structure that holds all of the public
// per-transaction data
//
typedef struct 
{
	CONST void *link;					// Don't even THINK about this one
	//
	// Server Configuration
	//
	CONST HWND _hMainWnd;				// Server's Main window
	CONST BOOL bService;				// TRUE if running as NT service
	CONST BOOL bTraceHook;				// TRUE if want hook tracing
	CONST char *temp_path;				// Path to server's temp directory
	CONST char *server_version;			// Server's version string for headers
	//
	// Low-level
	//
	CONST SOCKET hSocket;				// Client socket handle
	CONST DWORD dwPort;					// IP port for this request
	CONST DWORD dwThreadID;				// Current Thread ID
	CONST DWORD dwStartTicks;			// SystemTicks at thread start
	CONST BOOL bSSL;					// TRUE = Running on SSL
	//
	// Remote (client) identity
	//
	CONST char *remote_host;			// Client's host name or NULL if not found
	CONST char *remote_ip;				// Clients IP address (dotted quad)
	CONST char *remote_name;			// Client's host name if found, else IP address
	//
	// Local (server) identity
	//
	CONST char *local_name;				// Local (server) identity for multi-home
	CONST char *url_prefix;				// Multi-home URL prefix
	CONST char *local_CN;				// Local (server) cert Common Name (CN)
	CONST BYTE *cert;					// Local (server) cert for this identity
	CONST DWORD cert_len;				// Length of local cert
	//
	// HTTP Request info - may be changed by pre/post processor
	//
	CONST char http_request[MED_STRING_LEN];// HTTP raw request line (1st 256 chars)
	BOOL http_09;						// TRUE if HTTP/0.9 request
	char method[SML_STRING_LEN];		// HTTP method
	char url[MAX_STRING_LEN];			// HTTP URL (decoded)
	char params[MAX_STRING_LEN];		// HTTP URL Parameters (';' delimited)
	char args[MAX_STRING_LEN];			// HTTP arguments
	char http_accept[MAX_STRING_LEN];	// HTTP "Accept" line
	char if_mod_since[SML_STRING_LEN];	// HTTP "If-Modified-Since"
	char request_range[MAX_STRING_LEN];	// HTTP "Request-Range"
	char unl_mod_since[SML_STRING_LEN];	// HTTP "Unless-Modified-Since"
	char referer[MAX_STRING_LEN];		// HTTP "Referer"
	char from[MED_STRING_LEN];			// HTTP "From"
	char user_agent[MED_STRING_LEN];	// HTTP "User-Agent"
	BOOL keep_alive;					// TRUE if request has Connection: Keep-Alive
	//
	// Access Control & Authentication	(HTTP "Authorization")
	//
	char auth_line[MED_STRING_LEN];		// "Authorization" line
	char *auth_type;					// "Authorization" type (strdup'd)
	char *auth_name;					// "Authorization" Realm (strdup'd)
	char user[SML_STRING_LEN];			// User name
	char pass[SML_STRING_LEN];			// Password
	DWORD allow_options;				// Access options (SECOPT_ constants)
	//
	// Request content (if any), response content
	//
	long content_length;					// HTTP "Content-Length"
	char content_type[MED_STRING_LEN];		// HTTP "Content-Type"
	char content_encoding[MED_STRING_LEN];	// HTTP "Content-Encoding"
	char location[MAX_STRING_LEN];			// HTTP "Location"
	char last_modified[SML_STRING_LEN];		// HTTP "Last-Modified"
	//
	// Response status line
	//
	char rsp_status[SML_STRING_LEN];		// e.g., HTTP/1.0 200 OK
	//
	// Extra header tuples.
	//
	long num_req_xhdr;						// Number of request extra headers
	xhdr req_xhdr[MAX_EXT_HEADERS];			// Extra headers in request.
	long num_rsp_xhdr;						// Number of response extra headers
	xhdr rsp_xhdr[MAX_EXT_HEADERS];			// Extra headers for response.
	//
	// Authentication Info
	//
	char user_to_check[SML_STRING_LEN];	// Server checks this username
	//
	// Open file for response (postprocessing hooks only!)
	//
	HANDLE hOutFile;
	//
	// Results (use only for logging!)
	//
	CONST int http_status;				// HTTP/1.0 status code of trans.
	CONST long bytes;					// #bytes sent, excluding header
	//
	// User contexts
	//
	DWORD user_1;
	DWORD user_2;
	//
	// S-HTTP support - RESERVED! DO NOT TOUCH!
	//
	BOOL bSHTTP;						// TRUE = Is SHTTP transaction
	DWORD dwCryptRequest;				// Terisa hook op-code (see defs above)
	VOID *TerisaCtx;					// Toolkit context pointer
	HANDLE hUnwrappedReq;				// Handle of unwrapped request in file
	HANDLE hUnwrappedRsp;				// Handle of unwrapped response in file
} TCTX;

// =========================
// SERVER_EXPORTED FUNCTIONS
// =========================
//
//
// Version binding
//
BOOL bind_wsapi(WORD major, WORD minor, BOOL strict);
//
// URL <--> filespace mapping
//
int url_to_file(char *pathname, BOOL do_index, TCTX *tp);
void file_to_url(char *pathname, TCTX *tp);
//
// Other URL operations
//
void construct_url(char *d, char *s, TCTX *tp);
BOOL normalize_url(char *path);
void unescape_url(char *url);
void escape_url(char *url, TCTX *tp);
void plus_to_space(char *str);
void space_to_plus(char *str);
void evaluate_access(char *url, TCTX *tp);
//
// Content type
//
char *get_content_type(char *fn, TCTX *tp);
void set_content_type(char *fn, TCTX *tp);
//
// Response
//
void exec_cgi(char *m, char *file, char *args, int intfc, TCTX *tp);
void exec_cgi_to_file(char *m, char *file, char *args, int intfc, TCTX *tp);
void process_get(char *m, char *url, char *args, TCTX *tp);
void send_http_header(TCTX *tp, BOOL do_xhdr);
void do_imagemap(int method, char *map_name, char *coords, TCTX *tp);
//
// HTTP error handler (use above result code #defs)
//
void die(int http_status, char *string, TCTX *tp);
//
// Network I/O
//
void nputs(char *buf, TCTX *tp);
void nwrite(char *buf, int n, TCTX *tp);
void nwritef(HANDLE hFile, DWORD dwStartPos, DWORD dwCount, TCTX *tp);
void nflush(TCTX *tp);
void ngets(char *buf, int max, TCTX *tp);
void nread(char *buf, long nreq, TCTX *tp);
void nreadf(HANDLE hFile, long nreq, TCTX *tp);
//
// Registry access
//
HKEY OpenRegKey(char *pszKey);
char *GetRegString(char *name, HKEY hKey);
DWORD GetRegBin(char *name, HKEY hKey);
//
// Form decoder
//
FORM_CTX open_form_decoder(BYTE *cont, DWORD clen, TCTX *tp);
void close_form_decoder(FORM_CTX ctx, TCTX *TP);
PFIELD decode_next_field(FORM_CTX ctx, TCTX *tp);
//
// Cryptographically Strong Random Number Generator
//
void TrueRandAddNoise(DWORD data);
DWORD TrueRandEntropy(void);
BYTE TrueRandGetByte(void);
void TrueRandGetBytes(BYTE *buf, DWORD len);
//
// MD5 Support
//
void MD5Init(MD5Context *context);
void MD5Update(MD5Context *context, BYTE *buf, DWORD len);
void MD5Final(BYTE digest[16], MD5Context *context);
//
// Utilities
//
BOOL later_than(char *t1, char *t2);
char *http_timestr(time_t t, char *buf, int len);
char *http_nt_timestr(LPSYSTEMTIME pst, char *buf, int len);
void get_temp_name(char *buf);
void DbgDump (BYTE *buf, WORD len, char *label);
void wsapi_log_event(HINSTANCE hInstance, char *message);
void *wsapi_malloc(long size, TCTX *tp);
void *wsapi_realloc(void *ptr, long size, TCTX *tp);
char *wsapi_strdup(char *str, TCTX *tp);
void wsapi_free(void *ptr);
BOOL get_server_variable(char *name, char *buf, DWORD size, TCTX *tp);
//
// S-HTTP only - Security initializer callback
//
void init_sec(BOOL(*get_cert_key)(char *cn, BYTE **cert, DWORD *cert_len,
				BYTE **key, DWORD *key_len));

#ifdef __cplusplus
}
#endif

#endif 	// defined _WSAPI_H_
