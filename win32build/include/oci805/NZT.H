/* DISABLE check_long_lines */

/* Copyright (c) Oracle Corporation 1996, 1997.  All Rights Reserved. */

/*
 * $Header: nzt.h 05-sep-97.18:18:05 ascott Exp $ 
 */

/* 
 * NAME
 *    nzt.h
 * 
 * DESCRIPTION
 *    Toolkit public declarations.
 *    
 * PUBLIC FUNCTIONS
 *    nztwOpenWallet           - Open a wallet based on a WRL and pwd.
 *    nztwCloseWallet          - Close a wallet.
 * +  nztwCreateWallet         - Create a new wallet.
 * +  nztwDestroyWallet        - Destroy an existing wallet.
 *    nztwRetrievePersonaCopy  - Retieve a copy of a particular persona.
 * +  nzteStorePersona         - Store a persona in the wallet.
 *    nzteOpenPersona          - Open a persona.
 *    nzteClosePersona         - Close a persona.
 * +  nzteRemovePersona        - Remove a persona from a wallet.
 * +  nzteCreatePersona        - Create a persona.
 * +  nzteSetProtection        - Modify the protection set in a persona.
 * +  nzteGetProtection        - Get the protection set in a persona
 *    nztePriKey               - Get the Private Key (X509 Only)
 *    nzteMyCert               - Get the Certificate (X509 only)
 *    nzteX509CreatePersona    - Create a persona given an X509 Certificate.
 * +  nztiRemoveIdentity       - Remove an identity from a persona.
 *    nztiCreateIdentity       - Create an identity.
 *    nztiDuplicateIdentity    - Create a complete copy of an identity.
 *    nztiAbortIdentity        - Discard an unstored identity.
 * +  nztiStoreTrustedIdentity - Store an identity with associated trust.
 *    nztSign                  - Generate an attached signature.
 * +  nztxSignExpansion        - Determine size of signature.
 *    nztVerify                - Verify an attached signature.               
 *    nztValidate              - Validate an identity.                       
 *    nztsd_SignDetached       - Generate a detached signature.
 * +  nztxsd_SignDetachedExpansion - Determine size of detached signature.
 *    nztved_VerifyDetached    - Verify a detached signature.                 
 * +  nztEncrypt               - Symmetric key encryption.   
 * +  nztxEncryptExpansion     - Determine the tdu length for encryption.
 * +  nztDecrypt               - Symmetric key decryption.                   
 * +  nztEnvelope              - Sign then encrypt data for recipient(s).    
 * +  nztDeEnvelope            - Reverse nztEnvelope.                        
 * +  nztKeyedHash             - Generate keyed hash.                        
 * +  nztxKeyedHashExpansion   - Determine size of TDU for keyed hash.
 *    nztHash                  - Generate hash.   
 * +  nztxHashExpansion        - Determine the size of the TDU for a hash.
 *    nztSeedRandom            - See the random number generator.
 *    nztrb_RandomBytes        - Generate a series of random bytes.          
 *    nztrn_RandomNumber       - Generate a random number.                   
 *    nztbbInitBlock           - Initialize a buffer block.                  
 *    nztbbReuseBlock          - Reuse a buffer block.           
 *    nztbbSizeBlock           - Find the size of the buffer block.
 *    nztbbGrowBlock           - Grow initialized buffer block by 'inc' bytes.
 *    nztbbPurgeBlock          - Purge the memory used within a buffer block.
 *    nztbbSetBlock            - Set block to known state.
 *    nztkec_PKEncrypt         - Encrypt data then encrypt key for recipient.
 *    nztkdc_PKDecrypt         - Decrypt PKEncrypt'ed data.                  
 *    nztific_FreeIdentityContent - Free the contents of an identity.
 *    nztifdn                  - Create an identity from a distinguished name
 *
 * NOTE: the '+' indicates that these functions are UNSUPPORTED at this time.
 * 
 * NOTES
 *    
 * MODIFIED
 *    ascott     09/05/97 - update identity: create, destroy, duplicate
 *    ascott     08/21/97 - add GetCert and GetPriKey
 *    ascott     08/07/97 - add other WRL settings
 *    asriniva   03/25/97 - Add ANSI prototypes
 *    rwessman   03/19/97 - Added prototypes for nztific_FreeIdentityContent()
 *    asriniva   03/11/97 - Fix olint errors
 *    sdange     02/28/97 - Removed inclusion of nz0decl.h
 *    sdange     02/18/97 - Moved nzt specific declarations from nz0decl.h
 *    asriniva   01/21/97 - Remove prototypes.
 *    asriniva   10/31/96 - Include oratypes.h
 *    asriniva   10/15/96 - Declare buffer block helper functions
 *    asriniva   10/08/96 - First pass at wallet open/close
 *    asriniva   10/04/96 - Add random number seed function
 *    asriniva   10/03/96 - Reorder parameters in nztbbSetBlock
 *    asriniva   10/03/96 - Keep editing.
 *    asriniva   10/03/96 - Continued edits.
 *    asriniva   10/02/96 - Continue editing.
 *    asriniva   09/26/96 -
 */
   
/* ENABLE check_long_lines */

#ifndef NZT_ORACLE
#define NZT_ORACLE

#ifndef ORATYPES
# include <oratypes.h>
#endif /* ORATYPES */

#ifndef NZERROR_ORACLE
# include <nzerror.h>         /* NZ error type */
#endif /* NZERROR_ORACLE */

/***************************************/
/* PUBLIC CONSTANTS, MACROS, AND TYPES */
/***************************************/

/*
 * Wallet Resource Locator Type Strings
 *
 * WRL TYPE        PARAMETERS      BEHAVIOR
 * ========        ==========      =====================================
 * default:          <none>        Uses directory defined by the parameter
 *                                 SNZD_DEFAULT_FILE_DIRECTORY which in 
 *                                 unix is "$HOME/oracle/oss"
 * 
 * file:            file path      example: file:/home/ascott/certificate.oss
 * 
 * sqlnet:           <none>        In this case, the directory path will be 
 *                                 retrieved from the sqlnet.ora file under
 *                                 the oss.source.my_wallet parameter.
 * 
 */
#define NZT_DEFAULT_WRL    ((text *)"default:")
#define NZT_SQLNET_WRL     ((text *)"sqlnet:")
#define NZT_FILE_WRL       ((text *)"file:")
#define NZT_NO_PASSWORD    ((text *)"")

enum nzttwrl 
{
   NZTTWRL_DEFAULT = 1,    /* Default, use SNZD_DEFAULT_FILE_DIRECTORY */
   NZTTWRL_SQLNET,         /* Use oss.source.my_wallet in sqlnet.ora file */
   NZTTWRL_FILE            /* Find the wallet in this directory */
};
typedef enum nzttwrl nzttwrl;

#ifndef NZ0DECL_ORACLE
   /*
    * With the elimination of nz0decl.h from public, we need this
    * redundant typedef.
    */
   typedef struct nzctx nzctx;
#endif /* NZ0DECL_ORACLE */

/* Moved from nz0decl.h */

typedef struct nzttIdentity nzttIdentity;
typedef struct nzttIdentityPrivate nzttIdentityPrivate;
typedef struct nzttPersona nzttPersona;
typedef struct nzttPersonaPrivate nzttPersonaPrivate;
typedef struct nzttWallet nzttWallet;
typedef struct nzttWalletPrivate nzttWalletPrivate;

/*
 * Crypto Engine State
 *
 * Once the crypto engine (CE) has been initialized for a particular
 * cipher, it is either at the initial state, or it is continuing to
 * use the cipher.  NZTCES_END is used to change the state back to
 * initialized and flush any remaining output.  NZTTCES_RESET can be
 * used to change the state back to initialized and throw away any
 * remaining output.
 */
enum nzttces 
{
   NZTTCES_CONTINUE = 1,    /* Continue processing input */
   NZTTCES_END,             /* End processing input */
   NZTTCES_RESET            /* Reset processing and skip generating output */
};
typedef enum nzttces nzttces;

/*
 * Crypto Engine Functions
 *
 * List of crypto engine categories; used to index into protection
 * vector.
 */
enum nzttcef
{
   NZTTCEF_DETACHEDSIGNATURE = 1,   /* Signature, detached from content */
   NZTTCEF_SIGNATURE,               /* Signature combined with content */
   NZTTCEF_ENVELOPING,              /* Signature and encryption with content */
   NZTTCEF_PKENCRYPTION,            /* Encryption for one or more recipients */
   NZTTCEF_ENCRYPTION,              /* Symmetric encryption */
   NZTTCEF_KEYEDHASH,               /* Keyed hash/checkusm */
   NZTTCEF_HASH,                    /* Hash/checsum */
   NZTTCEF_RANDOM,                  /* Random byte generation */

   NZTTCEF_LAST                     /* Used for array size */
};
typedef enum nzttcef nzttcef;

/*
 * Identity type.
 */
enum nzttIdentType 
{
   NZTTIDENTTYPE_X509v1 = 1,        /* X.509v1 */
   NZTTIDENTTYPE_X509v3,            /* X.509v3 */
   NZTTIDENTTYPE_SYMMETRIC          /* Symmetric */
};
typedef enum nzttIdentType nzttIdentType;

/*
 * Cipher Types
 *
 * List of all cryptographic algorithms, some of which may not be
 * available.
 */
enum nzttCipherType 
{
   NZTTCIPHERTYPE_RSA = 1,          /* RSA public key */
   NZTTCIPHERTYPE_DES,              /* DES */
   NZTTCIPHERTYPE_RC4,              /* RC4 */
   NZTTCIPHERTYPE_MD5DES,           /* DES encrypted MD5 with salt (PBE) */
   NZTTCIPHERTYPE_MD5RC2,           /* RC2 encrypted MD5 with salt (PBE) */
   NZTTCIPHERTYPE_MD5,              /* MD5 */
   NZTTCIPHERTYPE_SHA               /* SHA */
};
typedef enum nzttCipherType nzttCipherType;

/*
 * TDU Formats
 *
 * List of possible toolkit data unit (TDU) formats.  Depending on the
 * function and cipher used some may be not be available.
 */
enum nztttdufmt
{
   NZTTTDUFMT_PKCS7 = 1,            /* PKCS7 format */
   NZTTTDUFMT_RSAPAD,               /* RSA padded format */
   NZTTTDUFMT_ORACLEv1,             /* Oracle v1 format */

   NZTTTDUFMT_LAST                  /* Used for array size */
};
typedef enum nztttdufmt nztttdufmt;

/*
 * Validate State
 *
 * Possible validation states an identity can be in.
 */
enum nzttValState
{
   NZTTVALSTATE_NONE = 1,        /* Needs to be validated */
   NZTTVALSTATE_GOOD,            /* Validated */
   NZTTVALSTATE_REVOKED          /* Failed to validate */
};
typedef enum nzttValState nzttValState;

/*
 * Personas and identities have unique id's that are represented with
 * 128 bits.
 */
typedef ub1 nzttID[16];

/*
 * Timestamp as 32 bit quantity in UTC.
 */
typedef ub1 nzttTStamp[4];

/*
 * Buffer Block
 *
 * A function that needs to fill (and possibly grow) an output buffer
 * uses an output parameter block to describe each buffer.
 *
 * The flags_nzttBufferBlock member tells the function whether the
 * buffer can be grown or not.  If flags_nzttBufferBlock is 0, then
 * the buffer will be realloc'ed automatically.  
 *
 * The buflen_nzttBufferBLock member is set to the length of the
 * buffer before the function is called and will be the length of the
 * buffer when the function is finished.  If buflen_nzttBufferBlock is
 * 0, then the initial pointer stored in pobj_nzttBufferBlock is
 * ignored.
 *
 * The objlen_nzttBufferBlock member is set to the length of the
 * object stored in the buffer when the function is finished.  If the
 * initial buffer had a non-0 length, then it is possible that the
 * object length is shorter than the buffer length.
 *
 * The pobj_nzttBufferBlock member is a pointer to the output object.
 */
struct nzttBufferBlock
{
# define NZT_NO_AUTO_REALLOC     0x1

   uword flags_nzttBufferBlock;     /* Flags */
   size_t buflen_nzttBufferBlock;   /* Total length of buffer */
   size_t usedlen_nzttBufferBlock;  /* Length of used buffer part */
   ub1 *buffer_nzttBufferBlock;     /* Pointer to buffer */
};
typedef struct nzttBufferBlock nzttBufferBlock;

/*
 * Wallet.
 */
struct nzttWallet
{
   size_t npersona_nzttWallet;            /* Number of personas */
   nzttPersona *list_nzttWallet;          /* List of personas in wallet */
   nzttWalletPrivate *private_nzttWallet; /* Private wallet information */
};

/*
 * The wallet contains, one or more personas.  A persona always
 * contains its private key and its identity.  It may also contain
 * other 3rd party identites.  All identities qualified with trust
 * where the qualifier can indicate anything from untrusted to trusted
 * for specific operations.
 */

/*
 * Persona
 *
 * Structure containing information about a persona.
 */
struct nzttPersona
{
   nzttIdentity *myidentity_nzttPersona;     /* My identity */
   size_t nidents_nzttPersona;               /* Number of trusted identities */
   nzttIdentity *list_nzttPersona;           /* List of trusted identities */
   nzttPersonaPrivate *private_nzttPersona;  /* Opaque part of persona */
};

/*
 * Identity
 *
 * Structure containing information about an identity.
 */
struct nzttIdentity
{
   size_t aliaslen_nzttIdentity;   /* Length of alias */
   text *alias_nzttIdentity;       /* Alias */
   size_t commentlen_nzttIdentity;    /* Length of comment */
   text *comment_nzttIdentity;        /* Comment  */
   nzttIdentityPrivate *private_nzttIdentity;   /* Opaque part of identity */
};

struct nzttPKCS7ProtInfo
{
   nzttCipherType mictype_nzttPKCS7ProtInfo;    /* Hash cipher */
   nzttCipherType symmtype_nzttPKCS7ProtInfo;   /* Symmetric cipher */
   size_t keylen_nzttPKCS7ProtInfo;             /* Length of key to use */
};
typedef struct nzttPKCS7ProtInfo nzttPKCS7ProtInfo;

/*
 * Protection Information.
 *
 * Information specific to a type of protection.
 */
union nzttProtInfo
{
   nzttPKCS7ProtInfo pkcs7_nzttProtInfo;
};
typedef union nzttProtInfo nzttProtInfo;

/*
 * A description of a persona so that the toolkit can create one.  A
 * persona can be symmetric or asymmetric and both contain an
 * identity.  The identity for an asymmetric persona will be the
 * certificate and the identity for the symmetric persona will be
 * descriptive information about the persona.  In either case, an
 * identity will have been created before the persona is created.
 *
 * A persona can be stored separately from the wallet that references
 * it.  By default, a persona is stored with the wallet (it inherits
 * with WRL used to open the wallet).  If a WRL is specified, then it
 * is used to store the actuall persona and the wallet will have a
 * reference to it.
 */
struct nzttPersonaDesc
{
   size_t privlen_nzttPersonaDesc;        /* Length of private info (key)*/
   ub1 *priv_nzttPersonaDesc;             /* Private information */
   size_t prllen_nzttPersonaDesc;         /* Length of PRL */
   text *prl_nzttPersonaDesc;             /* PRL for storage */
   size_t aliaslen_nzttPersonaDesc;       /* Length of alias */
   text *alias_nzttPersonaDesc;           /* Alias */
   size_t longlen_nzttPersonaDesc;        /* Length of longer description*/
   text *long_nzttPersonaDesc;            /* Longer persona description */
};
typedef struct nzttPersonaDesc nzttPersonaDesc;

/*
 * A description of an identity so that the toolkit can create one.
 * Since an identity can be symmetric or asymmetric, the asymmetric
 * identity information will not be used when a symmetric identity is
 * created.  This means the publen_nzttIdentityDesc and
 * pub_nzttIdentityDesc members will not be used when creating a
 * symmetric identity.
 */
struct nzttIdentityDesc
{
   size_t publen_nzttIdentityDesc;        /* Length of identity */
   ub1 *pub_nzttIdentityDesc;             /* Type specific identity */
   size_t aliaslen_nzttIdentityDesc;      /* Length of alias */
   text *alias_nzttIdentityDesc;          /* Alias */
   size_t longlen_nzttIdentityDesc;       /* Length of longer description */
   text *long_nzttIdentityDesc;           /* Longer description */
   size_t quallen_nzttIdentityDesc;       /* Length of trust qualifier */
   text *trustqual_nzttIdentityDesc;      /* Trust qualifier */
};
typedef struct nzttIdentityDesc nzttIdentityDesc;


/********************************/
/* PUBLIC FUNCTION DECLARATIONS */
/********************************/

/*---------------------- nztwOpenWallet ----------------------*/

/*
 * NAME
 *    nztwOpenWallet - Open a wallet based on a wallet Resource Locator (WRL).
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context. 
 *    wrllen   {IN}     Length of WRL.
 *    wrl      {IN}     WRL.
 *    pwdlen   {IN}     Length of password.
 *    pwd      {IN}     Password.
 *    wallet   {IN/OUT} Initialized wallet structure.   
 * 
 * NOTES
 *    The syntax for a WRL is <Wallet Type>:<Wallet Type Parameters>.
 *
 *    Wallet Type       Wallet Type Parameters.
 *    -----------       ----------------------
 *    File              Pathname (e.g. "file:/home/asriniva/.Owallet")
 *    Oracle            Connect string (e.g. "oracle:scott/tiger@oss")
 *
 *    There are also defaults.  If the WRL is NZT_DEFAULT_WRL, then
 *    the platform specific WRL default is used.  If only the wallet
 *    type is specified, then the WRL type specific default is used
 *    (e.g. "oracle:")
 *
 *    There is an implication with Oracle that should be stated: An
 *    Oracle based wallet can be implemented in a user's private space
 *    or in world readable space.
 *
 *    When the wallet is opened, the password is verified by hashing
 *    it and comparing against the password hash stored with the
 *    wallet.  The list of personas (and their associated identities)
 *    is built and stored into the wallet structure.
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_RIO_OPEN     RIO could not open wallet (see network trace file).
 *    NZERROR_TK_PASSWORD  Password verification failed.
 *    NZERROR_TK_WRLTYPE   WRL type is not known.
 *    NZERROR_TK_WRLPARM   WRL parm does not match type.
 */
#ifdef __STDC__
nzerror nztwOpenWallet(nzctx *, size_t, text *, size_t, text *, 
                           nzttWallet *);
#else
nzerror nztwOpenWallet(/*_ nzctx *, size_t, text *, size_t, text *, 
                           nzttWallet * _*/);
#endif /* __STDC __*/

/*---------------------- nztwCloseWallet ----------------------*/

/*
 * NAME
 *    nztwCloseWallet - Close a wallet
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    wallet   {IN/OUT} Wallet.
 * 
 * NOTES
 *    Closing a wallet also closes all personas associated with that
 *    wallet.  It does not cause a persona to automatically be saved
 *    if it has changed.  The implication is that a persona can be
 *    modified by an application but if it is not explicitly saved it
 *    reverts back to what was in the wallet.
 *
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_RIO_CLOSE    RIO could not close wallet (see network trace file).
 */
#ifdef __STDC__
nzerror nztwCloseWallet(nzctx *, nzttWallet *);
#else
nzerror nztwCloseWallet(/*_ nzctx *, nzttWallet * _*/);
#endif /* __STDC__ */

/*--------------------- nztwCreateWallet ---------------------*/

/*
 * NAME
 *    nztwCreateWallet - Create a new wallet.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    wrllen   {IN}     Length of wallet resource locator.
 *    wrl      {IN}     WRL.
 *    pwdlen   {IN}     Length of password (see notes below).
 *    pwd      {IN}     Password.
 *    wallet   {IN/OUT} Wallet. 
 * 
 * NOTES
 *    It is an error to try to create a wallet that already exists.
 *    The previously existing wallet must be destroyed first.
 *
 *    The wallet itself is not encrypted.  Rather, all the personas in
 *    the wallet are encrypted under the same password.  A hash of the
 *    password is stored in the wallet.
 *
 *    Upon success, an empty open wallet is stored in the wallet
 *    parameter.
 *    
 * RETURNS
 *    NZERROR_OK                 Sucess.
 *    NZERROR_TK_WALLET_EXISTS   Wallet already exists.
 *    NZERROR_RIO_OPEN           RIO could not create wallet (see trace file).
 */
#ifdef __STDC__
nzerror nztwCreateWallet(nzctx *, size_t, text *, size_t, text *, 
                             nzttWallet *);
#else
nzerror nztwCreateWallet(/*_ nzctx *, size_t, text *, size_t, text *, 
                             nzttWallet * _*/);
#endif /* __STDC__ */


/*--------------------- nztwDestroyWallet ---------------------*/

/*
 * NAME
 *    nztwDestroyWallet - Destroy an existing wallet.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    wrllen   {IN}     Length of wallet resource locator.
 *    wrl      {IN}     WRL.
 *    pwdlen   {IN}     Length of password.
 *    pwd      {IN}     Password.
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_PASSWORD  Password verification failed.
 *    NZERROR_RIO_OPEN     RIO could not open wallet (see trace file).
 *    NZERROR_RIO_DELETE   Delete failed (see trace file).
 */
#ifdef __STDC__
nzerror nztwDestroyWallet(nzctx *, size_t, text *, size_t, text *);
#else
nzerror nztwDestroyWallet(/*_ nzctx *, size_t, text *, size_t, text * _*/);
#endif /* __STDC __*/

/*---------------------- nztwRetrievePersonaCopy ----------------------*/

/*
 * NAME
 *    nztwRetrievePersonaCopy - Retrieves a persona based from wallet
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context. 
 *    wallet   {IN}     Wallet.
 *    index    {IN}     Which wallet index to remove (first persona is zero).
 *    persona  {OUT}    Persona found.
 * 
 * NOTES
 *    Retrieves a persona from the wallet based on the index number passed
 *    in.  This persona is a COPY of the one stored in the wallet, therefore
 *    it is perfectly fine for the wallet to be closed after this call is 
 *    made.
 *
 *    The caller is responsible for disposing of the persona when completed.
 *
 * RETURNS
 *    NZERROR_OK           Success.
 */
#ifdef __STDC__
nzerror nztwRetrievePersonaCopy(nzctx *, nzttWallet *, ub4, nzttPersona **);
#else
nzerror nztwRetrievePersonaCopy(/*_ nzctx *, nzttWallet *, ub4, 
                           nzttPersona ** _*/);
#endif /* __STDC __*/

/*--------------------- nzteStorePersona ---------------------*/

/*
 * NAME
 *    nzteStorePersona - Store an open persona in a wallet.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context. 
 *    persona  {IN/OUT} Persona.
 *    wallet   {IN/OUT} Wallet.
 * 
 * NOTES
 *    If the open persona is not associated with any wallet (it was
 *    created via the nzteClosePersona function), then storing the
 *    persona creates that association.  The wallet will also have an
 *    updated persona list that reflects this association.
 *
 *    If the open persona was associated with wallet 'A' (it was
 *    opened via the nztwOpenWallet function), and is stored back into
 *    wallet 'A', then then the old persona is overwritten by the new
 *    persona if the password can be verified.  Recall that all
 *    personas have a unique identity id.  If that id changes then
 *    storing the persona will put a new persona in the wallet.
 *
 *    If the open persona was associated with wallet 'A' and is stored
 *    into wallet 'B', and if wallet 'B' does not contain a persona
 *    with that unique identity id, then the persona will be copied
 *    into wallet 'B', wallet 'B''s persona list will be updated, and
 *    the persona structure will be updated to be associated with
 *    wallet 'B'.  If wallet 'B' already contained the persona, it
 *    would be overwritten by the new persona.
 *
 *    The persona parameter is doubly indirect so that at the
 *    conclusion of the function call, the pointer can be directed to
 *    the persona in the wallet.
 *
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_PASSWORD  Password verification failed.
 *    NZERROR_RIO_STORE    Store failed (see network trace file).
 */
#ifdef __STDC__
nzerror nzteStorePersona(nzctx *, nzttPersona **, nzttWallet *);
#else
nzerror nzteStorePersona(/*_ nzctx *, nzttPersona **, nzttWallet * _*/);
#endif /* __STDC __*/

/*---------------------- nzteOpenPersona ----------------------*/

/*
 * NAME
 *    nzteOpenPersona - Open a persona.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context. 
 *    persona  {IN/OUT} Persona.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_PASSWORD  Password failed to decrypt persona.
 *    NZERROR_TK_BADPRL    Persona resource locator did not work.
 *    NZERROR_RIO_OPEN     Could not open persona (see network trace file).
 */
#ifdef __STDC__
nzerror nzteOpenPersona(nzctx *, nzttPersona *);
#else
nzerror nzteOpenPersona(/*_ nzctx *, nzttPersona * _*/);
#endif /* __STDC __*/

/*--------------------- nzteClosePersona ---------------------*/

/*
 * NAME
 *    nzteClosePersona - Close a persona.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN/OUT} Persona.
 * 
 * NOTES
 *    Closing a persona does not store the persona, it simply releases
 *    the memory associated with the crypto engine.
 *    
 * RETURNS
 *    NZERROR_OK        Success.
 */
#ifdef __STDC__
nzerror nzteClosePersona(nzctx *, nzttPersona *);
#else
nzerror nzteClosePersona(/*_ nzctx *, nzttPersona * _*/);
#endif /* __STDC __*/

/*--------------------- nzteRemovePersona ---------------------*/

/*
 * NAME
 *    nzteRemovePersona - Remove a persona from the wallet.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN/OUT} Persona.
 * 
 * NOTES
 *    The password is verified before trying to remove the persona.
 *    
 *    If the persona is open, it is closed.  The persona is removed
 *    from the wallet list and the persona pointer is set to NULL.
 *    
 *    A double indirect pointer to the persona is required so that the
 *    persona pointer can be set to NULL upon completion.
 *
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_PASSWORD  Password verification failed.
 *    NZERROR_RIO_DELETE   Delete failed.
 */
#ifdef __STDC__
nzerror nzteRemovePersona(nzctx *, nzttPersona **);
#else
nzerror nzteRemovePersona(/*_ nzctx *, nzttPersona ** _*/);
#endif /* __STDC __*/

/*--------------------- nzteCreatePersona ---------------------*/

/*
 * NAME
 *    nzteCreatePersona - Create a persona.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    itype    {IN}     Identity type.
 *    ctype    {IN}     Cipher type.
 *    desc     {IN}     Persona description.
 *    persona  {OUT}    Persona.
 * 
 * NOTES
 *    The resulting persona is created in the open state, but it will
 *    not be associated with a wallet.
 *    
 *    The memory for the persona is allocated by the function.
 *
 * RETURNS
 *    NZERROR_OK        Success.
 *    NZERROR_TK_TYPE   Unsupported itype/ctype combination.
 *    NZERROR_TK_PARMS  Error in persona description.
 */
#ifdef __STDC__
nzerror nzteCreatePersona(nzctx *, nzttIdentType, nzttCipherType, 
                              nzttPersonaDesc *, nzttPersona **);
#else
nzerror nzteCreatePersona(/*_ nzctx *, nzttIdentType, nzttCipherType, 
                              nzttPersonaDesc *, nzttPersona ** _*/);
#endif /* __STDC __*/

/*--------------------- nzteSetProtection ---------------------*/

/*
 * NAME
 *    nzteSetProtection - Set the protection type for a CE function.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN/OUT} Persona.
 *    func     {IN}     CE function.
 *    tdufmt   {IN}     TDU Format.
 *    protinfo {IN}     Protection information specific to this format.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK              Success.
 *    NZERROR_TK_PROTECTION   Unsupported protection.
 *    NZERROR_TK_PARMS        Error in protection info.
 */
#ifdef __STDC__
nzerror nzteSetProtection(nzctx *, nzttPersona *, nzttcef, nztttdufmt,
                              nzttProtInfo *);
#else
nzerror nzteSetProtection(/*_ nzctx *, nzttPersona *, nzttcef, nztttdufmt,
                              nzttProtInfo * _*/);
#endif /* __STDC __*/

/*--------------------- nzteGetProtection ---------------------*/

/*
 * NAME
 *    nzteGetProtection - Get the protection type for a CE function.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN}     Persona.
 *    func     {IN}     CE function.
 *    tdufmt   {OUT}    TDU format.
 *    protinfo {OUT}    Protection information.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK        Success.
 */
#ifdef __STDC__
nzerror nzteGetProtection(nzctx *, nzttPersona *, nzttcef, nztttdufmt *,
                              nzttProtInfo *);
#else
nzerror nzteGetProtection(/*_ nzctx *, nzttPersona *, nzttcef, nztttdufmt *,
                              nzttProtInfo * _*/);
#endif /* __STDC __*/

/*--------------------- nztePriKey ---------------------*/

/*
 * NAME
 *    nztePriKey - Get the decrypted Private Key for the Persona
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN}     Persona.
 *    vkey     {OUT}    Private Key [B_KEY_OBJ]
 *    vkey_len {OUT}    Private Key Length
 * 
 * NOTES
 *    This funiction will only work for X.509 based persona which contain
 *    a private key.  
 *    A copy of the private key is returned to the caller so that they do not 
 *    have to worry about the key changeing "underneath them".
 *    Memory will be allocated for the vkey and therefore, the CALLER
 *    will be responsible for freeing this memory.
 *
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_NO_MEMORY    ossctx is null.
 *    NZERROR_TK_BADPRL    Persona resource locator did not work.
 */
#ifdef __STDC__
nzerror nztePriKey(nzctx *, nzttPersona *, ub1 **, size_t *);
#else
nzerror nztePriKey(/*_ nzctx *, nzttPersona *, ub1 **, size_t * _*/);
#endif /* __STDC __*/

/*--------------------- nzteMyCert ---------------------*/

/*
 * NAME
 *    nzteMyCert - Get the X.509 Certificate for a persona
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN}     Persona.
 *    cert     {OUT}    X.509 Certificate [BER encoded]
 *    cert_len {OUT}    Certificate length
 * 
 * NOTES
 *    This funiction will only work for X.509 based persona which contain
 *    a certificate for the self identity. 
 *    A copy of the certificate is returned to the caller so that they do not 
 *    have to worry about the certificate changeing "underneath them".
 *    Memory will be allocated for the cert and therefore, the CALLER
 *    will be responsible for freeing this memory.
 *
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_NO_MEMORY    ossctx is null.
 */
#ifdef __STDC__
nzerror nzteMyCert(nzctx *, nzttPersona *, ub1 **, size_t *);
#else
nzerror nzteMyCert(/*_ nzctx *, nzttPersona *, ub1 **, size_t * _*/);
#endif /* __STDC __*/

/*--------------------- nzteX509CreatePersona ---------------------*/

/*
 * NAME
 *    nzteX509CreatePersona - Given a BER X.509 cert, create a persona
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    cert     {IN}     X.509 Certificate [BER encoded]
 *    cert_len {IN}     Certificate length
 *    persona  {OUT}    Persona.
 * 
 * NOTES
 *    Memory will be allocated for the persona and therefore, the CALLER
 *    will be responsible for freeing this memory.
 *
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_NO_MEMORY    ossctx is null.
 */
#ifdef __STDC__
nzerror nzteX509CreatePersona(nzctx *, ub1 *, size_t, nzttPersona **);
#else
nzerror nzteX509CreatePersona(/*_ nzctx *, ub1 *, size_t, nzttPersona ** _*/);
#endif /* __STDC __*/

/*-------------------- nztiRemoveIdentity --------------------*/

/*
 * NAME
 *    nztiRemoveIdentity - Remove an identity from an open persona.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context. 
 *    identity {IN/OUT}     Identity.
 * 
 * NOTES
 *    If the persona is not stored, this identity will still be in the
 *    persona stored in the wallet.
 *    
 *    The identity parameter is doubly indirect so that at the
 *    conclusion of the function, the pointer can be set to NULL.
 *
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_NOTFOUND  Identity not found.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 */
#ifdef __STDC__
nzerror nztiRemoveIdentity(nzctx *, nzttIdentity **);
#else
nzerror nztiRemoveIdentity(/*_ nzctx *, nzttIdentity ** _*/);
#endif /* __STDC __*/

/*-------------------- nztiCreateIdentity --------------------*/

/*
 * NAME
 *    nztiCreateIdentity - Create an identity.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    itype    {IN}     Identity type.
 *    desc     {IN}     Description of identity.
 *    identity {IN/OUT} Identity.
 * 
 * NOTES
 *    Memory is only allocated for the identity structure.  The elements in
 *    the description struct are not copied.  Rather their pointers are copied
 *    into the identity structure.  Therefore, the caller should not free
 *    the elements referenced by the desc.  These elements will be freed
 *    when the nztiDestroyIdentity is called.
 *    
 * RETURNS
 *    NZERROR_OK        Success.
 *    NZERROR_PARMS     Error in description.
 */
#ifdef __STDC__
nzerror nztiCreateIdentity(nzctx *, nzttIdentType, nzttIdentityDesc *,
                               nzttIdentity **);
#else
nzerror nztiCreateIdentity(/*_ nzctx *, nzttIdentType, nzttIdentityDesc *,
                               nzttIdentity ** _*/);
#endif /* __STDC __*/

/*-------------------- nztiDuplicateIdentity --------------------*/

/*
 * NAME
 *    nztiDuplicateIdentity - Duplicate an identity.
 * 
 * PARAMETERS
 *    osscntxt     {IN}     OSS context.
 *    identity     {IN}     Target Identity.
 *    new_identity {IN}     New Identity.
 * 
 * NOTES
 *    Memory for the identity is allocated inside the function, and all
 *    internal identity elements as well.
 *    
 * RETURNS
 *    NZERROR_OK        Success.
 *    NZERROR_TK_NOTFOUND  Identity not found.
 *    NZERROR_PARMS     Error in description.
 */
#ifdef __STDC__
nzerror nztiDuplicateIdentity(nzctx *, nzttIdentity *, 
                              nzttIdentity **);
#else
nzerror nztiDuplicateIdentity(/*_ nzctx *, nzttIdentity *, 
                              nzttIdentity ** _*/);
#endif /* __STDC __*/

/*--------------------- nztiAbortIdentity ---------------------*/

/*
 * NAME
 *    nztiAbortIdentity - Abort an unassociated identity.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    identity {IN/OUT} Identity.
 * 
 * NOTES
 *    It is an error to try to abort an identity that can be
 *    referenced through a persona.
 *    
 *    The identity pointer is set to NULL at the conclusion.
 * 
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_CANTABORT    Identity is associated with persona.
 */
#ifdef __STDC__
nzerror nztiAbortIdentity(nzctx *, nzttIdentity **);
#else
nzerror nztiAbortIdentity(/*_ nzctx *, nzttIdentity ** _*/);
#endif /* __STDC __*/

/*----------------- nztiStoreTrustedIdentity -----------------*/

/*
 * NAME
 *    nztiStoreTrustedIdentity - Store an identity into a persona.
 * 
 * PARAMETERS
 *    osscntxt {IN}     Success.
 *    identity {IN/OUT} Identity.
 *    persona  {IN/OUT} Persona.    
 * 
 * NOTES
 *    The identity is not saved with the persona in the wallet until
 *    the persona is stored.
 *    
 *    The identity parameter is double indirect so that it can point
 *    into the persona at the conclusion of the call.
 *
 * RETURNS
 *    NZERROR_OK     Success.
 */
#ifdef __STDC__
nzerror nztiStoreTrustedIdentity(nzctx *, nzttIdentity **,
                                     nzttPersona *);
#else
nzerror nztiStoreTrustedIdentity(/*_ nzctx *, nzttIdentity **,
                                     nzttPersona * _*/);
#endif /* __STDC __*/

/*----------------- nztifdn -----------------*/

/*
 * NAME
 *    nztifdn - create an Identity From a Distinguished Name
 * 
 * PARAMETERS
 *    osscntxt           {IN}  OSS context.
 *    length             {IN}  Length of the distinguished name
 *    distinguished_name {IN}  distinguished name string
 *    ppidentity         {OUT} created identity
 * 
 * NOTES
 *    Given a distinguished name, return the identity that corresponds to it.
 *
 * RETURNS
 *    NZERROR_OK     Success.
 */
#ifdef __STDC__
nzerror nztifdn(nzctx         *ossctx,
                    size_t         length,
                    text          *distinguished_name,
                    nzttIdentity **ppidentity);
#else
nzerror nztifdn(/*_ nzctx         *ossctx,
                    size_t         length,
                    text          *distinguished_name,
                    nzttIdentity **ppidentity _*/);
#endif /* __STDC __*/

/*---------------- nztific_FreeIdentityContent ----------------*/

/*
 * NAME
 *     nztific_FreeIdentityContent - free the contents of an identity.
 * 
 * PARAMETERS
 *    osscntxt         {IN}     OSS context.
 *    identity         {IN/OUT} freed identity
 * 
 * NOTES
 *    Free a created identity.
 *
 * RETURNS
 *    NZERROR_OK     Success.
 */
/*
 * Free the identity content.
 */
#ifdef __STDC__
nzerror nztific_FreeIdentityContent(nzctx *ossctx,
                                        nzttIdentity *identity);
#else
nzerror nztific_FreeIdentityContent(/*_ nzctx *ossctx,
                                        nzttIdentity *identity _*/);
#endif /* __STDC __*/


/*-------------------------- nztSign --------------------------*/

/*
 * NAME
 *    nztSign - Create an attached signature.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN}     Open persona acting as signer.
 *    state    {IN}     State of signature.
 *    inlen    {IN}     Length of this input part.
 *    in       {IN}     This input part.
 *    tdubuf   {IN/OUT} TDU buffer.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_CANTGROW  Needed to grow output buffer but could not.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztSign(nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                    nzttBufferBlock *);
#else
nzerror nztSign(/*_ nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                    nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*--------------------- nztxSignExpansion ---------------------*/

/*
 * NAME
 *    nztxSignExpansion - Determine the size of the attached signature buffer.
 * 
 * PARAMETERS
 *    osscntxt {IN}  OSS context.
 *    persona  {IN}  Persona.
 *    inlen    {IN}  Length of input.
 *    tdulen   {OUT} Buffer needed for signature.
 *
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztxSignExpansion(nzctx *, nzttPersona *, size_t, size_t *);
#else
nzerror nztxSignExpansion(/*_ nzctx *, nzttPersona *, size_t, size_t * _*/);
#endif /* __STDC __*/

/*------------------------- nztVerify -------------------------*/

/*
 * NAME
 *    nztVerify - Verify an attached signature.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN}     Persona.
 *    state    {IN}     State of verification.
 *    intdulen {IN}     TDU length.
 *    intdu    {IN}     TDU.
 *    out      {IN/OUT} Extracted message.
 *    verified {OUT}    TRUE if signature verified.
 *    validated{OUT}    TRUE if signing identity validated.
 *    identity {OUT} Identity of signing party.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_CANTGROW  Needed to grow outptu buffer but could not.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztVerify(nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                      nzttBufferBlock *, boolean *, boolean *,
                      nzttIdentity **);
#else
nzerror nztVerify(/*_ nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                      nzttBufferBlock *, boolean *, boolean *,
                      nzttIdentity ** _*/);
#endif /* __STDC __*/

/*------------------------ nztValidate ------------------------*/

/*
 * NAME
 *    nztValidate - Validate an identity.
 * 
 * PARAMETERS
 *    osscntxt {IN}  OSS context.
 *    persona  {IN}  Persona.
 *    identity {IN}  Identity.
 *    validated{OUT} TRUE if identity was validated.  
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztValidate(nzctx *, nzttPersona *, nzttIdentity *, boolean *);
#else
nzerror nztValidate(/*_ nzctx *, nzttPersona *, nzttIdentity *, boolean * _*/);
#endif /* __STDC __*/

/*-------------------- nztsd_SignDetached --------------------*/

/*
 * NAME
 *    nztsd_SignDetached - Generate a detached signature.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN}     Persona.
 *    state    {IN}     State of signature.
 *    inlen    {IN}     Length of this input part.
 *    in       {IN}     This input part.
 *    tdubuf   {IN/OUT} TDU buffer.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_CANTGROW  Needed to grow output buffer but could not.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztsd_SignDetached(nzctx *, nzttPersona *, nzttces, size_t, ub1 *, 
                               nzttBufferBlock *);
#else
nzerror nztsd_SignDetached(/*_ nzctx *, nzttPersona *, nzttces, size_t, ub1 *, 
                               nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*--------------- nztxsd_SignDetachedExpansion ---------------*/

/*
 * NAME
 *    nztxsd_SignDetachedExpansion - Determine the size of buffer needed.
 * 
 * PARAMETERS
 *    osscntxt {IN}  OSS context.
 *    persona  {IN}  Persona.
 *    inlen    {IN}  Length of input.
 *    tdulen   {OUT} Buffer needed for signature.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztxsd_SignDetachedExpansion(nzctx *, nzttPersona *, size_t,
                                         size_t *);
#else
nzerror nztxsd_SignDetachedExpansion(/*_ nzctx *, nzttPersona *, size_t,
                                         size_t * _*/);
#endif /* __STDC __*/

/*------------------- nztved_VerifyDetached -------------------*/

/*
 * NAME
 *    nztved_VerifyDetached - Verify a detached signature.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN}     Persona.
 *    state    {IN}     State of verification.
 *    inlen    {IN}     Length of data.
 *    in       {IN}     Data.
 *    intdulen {IN}     Input TDU length.
 *    tdu      {IN}     Input TDU.
 *    verified {OUT}    TRUE if signature verified.
 *    validated{OUT}    TRUE if signing identity validated.
 *    identity {OUT} Identity of signing party.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztved_VerifyDetached(nzctx *, nzttPersona *, nzttces, size_t, 
                                  ub1 *, size_t, ub1 *, boolean *, boolean *, 
                                  nzttIdentity **);
#else
nzerror nztved_VerifyDetached(/*_ nzctx *, nzttPersona *, nzttces, size_t, 
                                  ub1 *, size_t, ub1 *, boolean *, boolean *, 
                                  nzttIdentity ** _*/);
#endif /* __STDC __*/

/*--------------------- nztkec_PKEncrypt ---------------------*/

/*
 * NAME
 *    nztkec_PKEncrypt - Encrypt data symmetrically, encrypt key asymmetrically
 * 
 * PARAMETERS
 *    osscntxt    {IN}     OSS context.
 *    persona     {IN}     Persona.
 *    nrecipients {IN}     Number of recipients for this encryption.
 *    recipients  {IN}     List of recipients.
 *    state       {IN}     State of encryption.
 *    inlen       {IN}     Length of this input part.
 *    in          {IN}     This input part.
 *    tdubuf      {IN/OUT} TDU buffer.
 * 
 * NOTES
 *    There is a limitation of 1 recipient (nrecipients = 1) at this
 *    time.
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_CANTGROW  Needed to grow output buffer but could not.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztkec_PKEncrypt(nzctx *, nzttPersona *, size_t, nzttIdentity *, 
                             nzttces, size_t, ub1 *, nzttBufferBlock *);
#else
nzerror nztkec_PKEncrypt(/*_ nzctx *, nzttPersona *, size_t, nzttIdentity *, 
                             nzttces, size_t, ub1 *, nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*---------------- nztxkec_PKEncryptExpansion ----------------*/

/*
 * NAME
 *    nztxkec_PKEncryptExpansion - Determine the buffer needed for PKEncrypt
 * 
 * PARAMETERS
 *    osscntxt    {IN}     OSS context. 
 *    persona     {IN}     Persona.
 *    nrecipients {IN}     Number of recipients.
 *    inlen       {IN}     Length of input.
 *    tdulen      {out}    Length of buffer need.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztxkec_PKEncryptExpansion(nzctx *, nzttPersona *, size_t, size_t,
                                       size_t *);
#else
nzerror nztxkec_PKEncryptExpansion(/*_ nzctx *, nzttPersona *, size_t, size_t,
                                       size_t * _*/);
#endif /* __STDC __*/

/*--------------------- nztkdc_PKDecrypt ---------------------*/

/*
 * NAME
 *    nztkdc_PKDecrypt - Decrypt a PKEncrypted message.
 * 
 * PARAMETERS
 *    osscntxt    {IN}     OSS context.
 *    persona     {IN}     Persona.
 *    state       {IN}     State of encryption.
 *    inlen       {IN}     Length of this input part.
 *    in          {IN}     This input part.
 *    tdubuf      {IN/OUT} TDU buffer.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_CANTGROW  Needed to grow output buffer but could not.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztkdc_PKDecrypt(nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                             nzttBufferBlock *);
#else
nzerror nztkdc_PKDecrypt(/*_ nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                             nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*------------------------ nztEncrypt ------------------------*/

/*
 * NAME
 *    nztEncrypt - Symmetrically encrypt
 * 
 * PARAMETERS
 *    osscntxt    {IN}     OSS context.
 *    persona     {IN}     Persona.
 *    inlen       {IN}     Length of this input part.
 *    in          {IN}     This input part.
 *    tdubuf      {IN/OUT} TDU buffer.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_CANTGROW  Needed to grow TDU buffer but could not.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztEncrypt(nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                       nzttBufferBlock *);
#else
nzerror nztEncrypt(/*_ nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                       nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*------------------- nztxEncryptExpansion -------------------*/

/*
 * NAME
 *    nztxEncryptExpansion - Determine the size of the TDU to encrypt.
 * 
 * PARAMETERS
 *    osscntxt    {IN}  OSS context.
 *    persona     {IN}  Persona.
 *    inlen       {IN}  Length of this input part.
 *    tdulen      {OUT} Length of TDU.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztxEncryptExpansion(nzctx *, nzttPersona *, size_t, size_t *);
#else
nzerror nztxEncryptExpansion(/*_ nzctx *, nzttPersona *, size_t, size_t * _*/);
#endif /* __STDC __*/

/*------------------------ nztDecrypt ------------------------*/

/*
 * NAME
 *    nztDecrypt - Decrypt an Encrypted message.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN}     Persona.
 *    state    {IN}     State of decryption.
 *    inlen    {IN}     Length of this input part.
 *    in       {IN}     This input part.
 *    out      {IN/OUT} Cleartext message.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_CANTGROW  Needed to grow TDU buffer but could not.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztDecrypt(nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                       nzttBufferBlock *);
#else
nzerror nztDecrypt(/*_ nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                       nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*------------------------ nztEnvelope ------------------------*/

/*
 * NAME
 *    nztEnvelope - Sign and PKEncrypt a message.
 * 
 * PARAMETERS
 *    osscntxt    {IN}     OSS context.
 *    persona     {IN}     Persona.
 *    nrecipients {IN}     Number of recipients for this encryption.
 *    recipients  {IN}     List of recipients.
 *    state       {IN}     State of encryption.
 *    inlen       {IN}     Length of this input part.
 *    in          {IN}     This input part.
 *    tdubuf      {IN/OUT} TDU buffer.
 *
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_CANTGROW  Needed to grow output buffer but could not.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztEnvelope(nzctx *, nzttPersona *, size_t, nzttIdentity *,
                        nzttces, size_t, ub1 *, nzttBufferBlock *);
#else
nzerror nztEnvelope(/*_ nzctx *, nzttPersona *, size_t, nzttIdentity *,
                        nzttces, size_t, ub1 *, nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*----------------------- nztDeEnvelope -----------------------*/

/*
 * NAME
 *    nztDeEnvelope - PKDecrypt and verify a message.
 * 
 * PARAMETERS
 *    osscntxt    {IN}     OSS context.
 *    persona     {IN}     Persona.
 *    state       {IN}     State of encryption.
 *    inlen       {IN}     Length of this input part.
 *    in          {IN}     This input part.
 *    out         {OUT}    Message from TDU.
 *    verified    {OUT}    TRUE if verified.
 *    validated   {OUT}    TRUE if validated.
 *    sender      {OUT}    Identity of sender.
 *
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_CANTGROW  Needed to grow TDU buffer but could not.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztDeEnvelope(nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                          nzttBufferBlock *, boolean *, boolean *,
                          nzttIdentity **);
#else
nzerror nztDeEnvelope(/*_ nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                          nzttBufferBlock *, boolean *, boolean *,
                          nzttIdentity ** _*/);
#endif /* __STDC __*/

/*----------------------- nztKeyedHash -----------------------*/

/*
 * NAME
 *    nztKeyedHash - Generate a keyed hash.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN}     Persona.
 *    state    {IN}     State of hash.
 *    inlen    {IN}     Length of this input.
 *    in       {IN}     This input.
 *    tdu      {IN/OUT} Output tdu.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_CANTGROW  Needed to grow TDU buffer but could not.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztKeyedHash(nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                         nzttBufferBlock *);
#else
nzerror nztKeyedHash(/*_ nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                         nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*------------------ nztxKeyedHashExpansion ------------------*/

/*
 * NAME
 *    nztxKeyedHashExpansion - Determine the space needed for a keyed hash.
 * 
 * PARAMETERS
 *    osscntxt {IN}  OSS context.
 *    persona  {IN}  Persona.
 *    inlen    {IN}  Length of this input.
 *    tdulen   {OUT} TDU length.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztxKeyedHashExpansion(nzctx *, nzttPersona *, size_t, 
                                   size_t *);
#else
nzerror nztxKeyedHashExpansion(/*_ nzctx *, nzttPersona *, size_t, 
                                   size_t * _*/);
#endif /* __STDC __*/

/*-------------------------- nztHash --------------------------*/

/*
 * NAME
 *    nztHash - Generate a hash.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN}     Persona.
 *    state    {IN}     State of hash.
 *    inlen    {IN}     Length of this input.
 *    in       {IN}     This input.
 *    tdu      {IN/OUT} Output tdu.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_CANTGROW  Needed to grow TDU buffer but could not.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztHash(nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                    nzttBufferBlock *);
#else
nzerror nztHash(/*_ nzctx *, nzttPersona *, nzttces, size_t, ub1 *,
                    nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*--------------------- nztxHashExpansion ---------------------*/

/*
 * NAME
 *    nztxHashExpansion - Determine the size of the TDU for a hash.
 * 
 * PARAMETERS
 *    osscntxt {IN}  OSS context.
 *    persona  {IN}  Persona.
 *    inlen    {IN}  Length of this input.
 *    tdulen   {OUT} TDU length.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztxHashExpansion(nzctx *, nzttPersona *, size_t, size_t *);
#else
nzerror nztxHashExpansion(/*_ nzctx *, nzttPersona *, size_t, size_t * _*/);
#endif /* __STDC __*/

/*----------------------- nztSeedRandom -----------------------*/

/*
 * NAME
 *    nztSeedRandom - Seed the random function
 * 
 * PARAMETERS
 *    osscntxt {IN}  OSS context.
 *    persona  {IN}  Persona.
 *    seedlen  {IN}  Length of seed.
 *    seed     {IN}  Seed.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztSeedRandom(nzctx *, nzttPersona *, size_t, ub1 *);
#else
nzerror nztSeedRandom(/*_ nzctx *, nzttPersona *, size_t, ub1 * _*/);
#endif /* __STDC __*/

/*--------------------- nztrb_RandomBytes ---------------------*/

/*
 * NAME
 *    nztrb_RandomBytes - Generate a buffer random bytes.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN}     Persona.
 *    nbytes   {IN}     Number of bytes desired.
 *    out      {IN/OUT} Buffer block for bytes.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_CANTGROW  Needed to grow TDU buffer but could not.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztrb_RandomBytes(nzctx *, nzttPersona *, size_t, 
                              nzttBufferBlock *);
#else
nzerror nztrb_RandomBytes(/*_ nzctx *, nzttPersona *, size_t, 
                              nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*-------------------- nztrn_RandomNumber --------------------*/

/*
 * NAME
 *    nztrn_RandomNumber - Generate a random number
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    persona  {IN}     Persona.
 *    num      {OUT}    Number.
 * 
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK           Success.
 *    NZERROR_TK_NOTOPEN   Persona is not open.
 *    NZERROR_TK_NOTSUPP   Function not supported with persona.
 */
#ifdef __STDC__
nzerror nztrn_RandomNumber(nzctx *, nzttPersona *, uword *);
#else
nzerror nztrn_RandomNumber(/*_ nzctx *, nzttPersona *, uword * _*/);
#endif /* __STDC __*/

/*---------------------- nztbbInitBlock ----------------------*/

/*
 * NAME
 *    nztbbInitBlock - Initialize a buffer block.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    block    {IN/OUT} Buffer block.
 * 
 * NOTES
 *    The buffer block is initialized to be empty (all members are set
 *    to 0/NULL).  Such a block will be allocated memory as needed.
 *    
 * RETURNS
 *    NZERROR_OK        Success.
 */
#ifdef __STDC__
nzerror nztbbInitBlock(nzctx *, nzttBufferBlock *);
#else
nzerror nztbbInitBlock(/*_ nzctx *, nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*---------------------- nztbbReuseBlock ----------------------*/

/*
 * NAME
 *    nztbbReuseBlock - Reuse an already initialized and possibly used block.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    block    {IN/OUT} Buffer block.
 * 
 * NOTES
 *    This function simply sets the used length member of the buffer
 *    block to 0.  If the block already has memory allocated to it,
 *    this will cause it to be reused.
 *    
 * RETURNS
 *    NZERROR_OK        Success.
 */
#ifdef __STDC__
nzerror nztbbReuseBlock(nzctx *, nzttBufferBlock *);
#else
nzerror nztbbReuseBlock(/*_ nzctx *, nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*---------------------- nztbbSizeBlock ----------------------*/

/*
 * NAME
 *    nztbbSizeBlock - Size an initialized block to a particular size.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    len      {IN}     Minimum number of unused bytes desired.
 *    block    {IN/OUT} Buffer block.
 *
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK        Success.
 */
#ifdef __STDC__
nzerror nztbbSizeBlock(nzctx *, size_t, nzttBufferBlock *);
#else
nzerror nztbbSizeBlock(/*_ nzctx *, size_t, nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*----------------------- nztbbGrowBlock -----------------------*/

/*
 * NAME
 *    nzbbGrowBlock - Increase the size of the buffer block.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    inc      {IN}     Number of bytes to increase.
 *    block    {IN/OUT} Buffer block.
 *
 * NOTES
 *    
 * RETURNS
 *    NZERROR_OK        Success.
 */
#ifdef __STDC__
nzerror nztbbGrowBlock(nzctx *, size_t, nzttBufferBlock *);
#else
nzerror nztbbGrowBlock(/*_ nzctx *, size_t, nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*---------------------- nztbbPurgeBlock ----------------------*/

/*
 * NAME
 *    nztbbPurgeBlock - Purge a buffer block of its memory.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    block    {IN/OUT} Buffer block.
 * 
 * NOTES
 *    The memory used by the buffer block as the buffer is released.
 *    The buffer block itself is not affected.
 *    
 * RETURNS
 *    NZERROR_OK        Success.
 */
#ifdef __STDC__
nzerror nztbbPurgeBlock(nzctx *, nzttBufferBlock *);
#else
nzerror nztbbPurgeBlock(/*_ nzctx *, nzttBufferBlock * _*/);
#endif /* __STDC __*/

/*----------------------- nztbbSetBlock -----------------------*/

/*
 * NAME
 *    nztbbSetBlock - Set a buffer block to a known state.
 * 
 * PARAMETERS
 *    osscntxt {IN}     OSS context.
 *    flags    {IN}     Flags to set.
 *    buflen   {IN}     Length of buffer.
 *    usedlen  {IN}     Used length.
 *    buffer   {IN}     Buffer.
 *    block    {IN/OUT} Buffer block
 * 
 * NOTES
 *    If buflen > 0, objlen == 0, and obj == NULL, then buflen bytes
 *    of memory is allocated and a pointer is stored in the buffer
 *    block.
 *
 *    The buffer parameter remains unchanged.
 *    
 * RETURNS
 *    NZERROR_OK        Success.
 */
#ifdef __STDC__
nzerror nztbbSetBlock(nzctx *,  uword, size_t, size_t, ub1 *, 
                          nzttBufferBlock *);
#else
nzerror nztbbSetBlock(/*_ nzctx *,  uword, size_t, size_t, ub1 *, 
                          nzttBufferBlock * _*/);
#endif /* __STDC __*/

#endif /* NZT_ORACLE */
