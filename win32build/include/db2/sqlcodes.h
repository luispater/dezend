/******************************************************************************
** 
** Source File Name: SQLCODES
** 
** (C) COPYRIGHT International Business Machines Corp. 1987, 1997
** All Rights Reserved
** Licensed Materials - Property of IBM
** 
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
** 
** Function: Include File defining:
**             Labels for SQLCODES
** 
** Operating System:  Windows NT
** 
*******************************************************************************/
#ifndef SQL_H_SQLCODES
#define SQL_H_SQLCODES

#ifdef __cplusplus
extern "C" {
#endif


#include "sqlsystm.h"                  /* System dependent defines  */

/* SQL Return Codes in SQLCODE                                                */

#ifndef   SQL_RC_OK
#define SQL_RC_OK              0       /* successful execution                */
#endif

/* ------------ warnings ------------                                         */
#define SQL_RC_W012            12      /* correlation without qualification   */
#define SQL_RC_W020            20      /* unsupported bind/prep options       */
#define SQL_RC_W100            100     /* eof                                 */
#define SQL_RC_W139            139     /* duplicate column conistraint        */
#define SQL_RC_W143            143     /* invalid syntax ignored              */
#define SQL_RC_W217            217     /* explain mode incompatible           */
#define SQL_RC_W236            236     /* not enough sqlvars, none filled in  */
#define SQL_RC_W237            237     /* distinct type: not enough sqlvars,  */
                                       /* some filled in                      */
#define SQL_RC_W238            238     /* LOB type: not enough sqlvars, none  */
                                       /* filled in                           */
#define SQL_RC_W239            239     /* distinct type: not enough sqlvars,  */
                                       /* none filled in                      */
#define SQL_RC_W280            280     /* new view replaced old               */
#define SQL_RC_W347            347     /* possible infinite loop              */
#define SQL_RC_W403            403     /* alias target is not defined         */
#define SQL_RC_W434            434     /* clause value has been replaced      */
#define SQL_RC_W437            437     /* Sub-optimal query                   */
#define SQL_RC_W445            445     /* Function has truncated value        */
#define SQL_RC_W447            447     /* Create UDF contains redundant keyw  */
#define SQL_RC_W462            462     /* UDF returns a warning sqlstate      */
#define SQL_RC_W466            466     /* one or more results sets for        */
                                       /* stored procedure                    */
#define SQL_RC_W467            467     /* Another result set exists for a     */
                                       /* stored procedure                    */
#define SQL_RC_W474            474     /* DDL:could truncate value at         */
                                       /* runtime                             */
#define SQL_RC_W477            477     /* DDL:could truncate value at         */
                                       /* runtime                             */
#define SQL_RC_W541            541     /* duplicate referential constraint    */
#define SQL_RC_W570            570     /* some privileges were not granted    */
#define SQL_RC_W595            595     /* Isolation level escalated           */
#define SQL_RC_W598            598     /* existing index used                 */
#define SQL_RC_W599            599     /* compare func not created for lstr   */
#define SQL_RC_W605            605     /* index already exists                */
#define SQL_RC_W965            965     /* unknown SQL warning another         */
                                       /* product                             */
#define SQL_RC_W997            997     /* XA informational message            */
#define SQL_RC_W1138           1138    /* already existing index was          */
                                       /* migrated                            */
#define SQL_RC_W1165           1165    /* value not within host variable      */
                                       /* data type range                     */
#define SQL_RC_W1166           1166    /* Division by zero                    */
#define SQL_RC_W1167           1167    /* Arithmetic overflow or arithmetic   */
                                       /* exception                           */
#define SQL_RC_W1251           1251    /* XA no data to return from recover   */
#define SQL_RC_W1440           1440    /* WITH GRANT OPTION ignored           */
#define SQL_RC_ERR_DB_TERM     1475    /* system error on DB termination      */
#define SQL_RC_W1479           1479    /* Invalid cursor position             */
#define SQL_RC_W1530           1530    /* value of DEGREE ignored             */
#define SQL_RC_W1580           1580    /* Trailing blanks are truncated       */
#define SQLM_RC_NOT_SET        1615    /* Event monitor state not changed     */
#define SQL_RC_W1625           1625    /* Monitor: No conversion from source  */
                                       /* cp to target cp                     */
#define SQL_RC_W1626           1626    /* Monitor: code page conversion       */
                                       /* overflow                            */
#define SQL_RC_W1758           1758    /* containers not designated for       */
                                       /* specific nodes are not used         */
#define SQL_RC_W1759           1759    /* Redistribute required to change     */
                                       /* data partitioning                   */
#define SQL_RC_W1821           1821    /* LOB value retrieved may have been   */
                                       /* changed                             */
#define SQL_RC_W1824           1824    /* base tables of UNION ALL may be     */
                                       /* same table                          */

/* ------------ errors ------------                                           */
#define SQL_RC_E007            -7      /* illegal character                   */
#define SQL_RC_E010            -10     /* string constant not terminated      */
#define SQL_RC_E013            -13     /* cursor or statement name = ""       */
#define SQL_RC_E029            -29     /* INTO clause required                */
#define SQL_RC_E051            -51     /* reserved                            */
#define SQL_RC_E084            -84     /* bad SQL statement                   */

#define SQL_RC_E101            -101    /* statement too long                  */
#define SQL_RC_E102            -102    /* string constant too long            */
#define SQL_RC_E103            -103    /* invalid numeric literal             */
#define SQL_RC_E104            -104    /* invalid character/token             */
#define SQL_RC_E105            -105    /* invalid string constant             */
#define SQL_RC_E107            -107    /* name too long                       */
#define SQL_RC_E108            -108    /* name has too many qualifiers        */
#define SQL_RC_E109            -109    /* clause not permitted                */
#define SQL_RC_E110            -110    /* invalid hex constant                */
#define SQL_RC_E111            -111    /* no column name                      */
#define SQL_RC_E112            -112    /* operand is SQL function             */
#define SQL_RC_E117            -117    /* wrong nbr of insert values          */
#define SQL_RC_E118            -118    /* object table in from clause         */
#define SQL_RC_E119            -119    /* column not in group by              */
#define SQL_RC_E120            -120    /* clause includes SQL fn              */
#define SQL_RC_E121            -121    /* dup column name                     */
#define SQL_RC_E122            -122    /* no group by                         */
#define SQL_RC_NOTCONST        -123    /* parameter must be constant          */
#define SQL_RC_E125            -125    /* no result column                    */
#define SQL_RC_E127            -127    /* dup distinct                        */
#define SQL_RC_E129            -129    /* too many table names                */
#define SQL_RC_INVESC          -130    /* invalid escape character            */
#define SQL_RC_E131            -131    /* incompatible data for like          */
#define SQL_RC_E132            -132    /* like predicate invalid              */
#define SQL_RC_E134            -134    /* improper use of long string         */
#define SQL_RC_E137            -137    /* length of concat too long           */
#define SQL_RC_E138            -138    /* substr arg out of range             */
#define SQL_RC_E142            -142    /* syntax not supported                */
#define SQL_RC_E146            -146    /* unsupported ANSI syntax             */
#define SQL_RC_E150            -150    /* view not updatable                  */
#define SQL_RC_E151            -151    /* column not updatable                */
#define SQL_RC_E153            -153    /* no column list                      */
#define SQL_RC_E155            -155    /* trigger trans tbl not modifiable    */
#define SQL_RC_E156            -156    /* command not allowed on view         */
#define SQL_RC_E157            -157    /* view name in foreign key            */
#define SQL_RC_E158            -158    /* nbr of columns does not match       */
#define SQL_RC_E159            -159    /* drop view on table                  */
#define SQL_RC_E160            -160    /* with check not allowed on view      */
#define SQL_RC_E161            -161    /* with check violation                */
#define SQL_RC_E170            -170    /* nbr of arguments invalid            */
#define SQL_RC_E171            -171    /* argument invalid                    */
#define SQL_RC_E172            -172    /* function name invalid               */
#define SQL_RC_E176            -176    /* translate scalar argument invalid   */
#define SQL_RC_E180            -180    /* datetime syntax invalid             */
#define SQL_RC_E181            -181    /* datetime value invalid              */
#define SQL_RC_E182            -182    /* datetime arithmetic invalid         */
#define SQL_RC_E183            -183    /* datetime arithmetic out of range    */
#define SQL_RC_DTMEREG         -187    /* datetime register is invalid        */
#define SQL_RC_DBCSTRUNC       -191    /* truncated DBCS character found      */
#define SQL_RC_E193            -193    /* NOT NULL needs DEFAULT              */
#define SQL_RC_E197            -197    /* no qualified columns in ORDER BY    */
#define SQL_RC_E198            -198    /* no statement text                   */
#define SQL_RC_E199            -199    /* illegal use of reserved word        */

#define SQL_RC_E203            -203    /* ambiguous column reference          */
#define SQL_RC_E204            -204    /* undefined name                      */
#define SQL_RC_E205            -205    /* not a column                        */
#define SQL_RC_E206            -206    /* not a column of referenced tables   */
#define SQL_RC_E207            -207    /* cannot orderby column name w/union  */
#define SQL_RC_E208            -208    /* column not part of result table     */
#define SQL_RC_E212            -212    /* duplicate table designator          */
#define SQL_RC_E219            -219    /* required explain table not exist    */
#define SQL_RC_E214            -214    /* bad expression in group/by or       */
                                       /* order by                            */
#define SQL_RC_E216            -216    /* number of elements does not match   */
#define SQL_RC_E220            -220    /* explain table has improper def      */
#define SQL_RC_E257            -257    /* raw device containers not allowed   */
#define SQL_RC_E258            -258    /* cannot add container to pool        */
#define SQL_RC_E259            -259    /* container map too big               */
#define SQL_RC_E260            -260    /* partition key has long field        */
#define SQL_RC_E261            -261    /* node in use, cannot drop            */
#define SQL_RC_E262            -262    /* multinode table without part key    */
#define SQL_RC_E263            -263    /* invalid node range                  */
#define SQL_RC_E264            -264    /* multinode tbl, cannot drop part     */
#define SQL_RC_E265            -265    /* duplicate node name/number          */
#define SQL_RC_E266            -266    /* node not defined                    */
#define SQL_RC_E268            -268    /* operatn not done because rebalance  */
#define SQL_RC_E269            -269    /* too many nodegroups                 */
#define SQL_RC_E270            -270    /* function not supported              */
#define SQL_RC_E271            -271    /* Index file missing or invalid       */
#define SQL_RC_E276            -276    /* database in restore pending state   */
#define SQL_RC_E279            -279    /* connection terminated during        */
                                       /* COMMIT                              */
#define SQL_RC_E281            -281    /* cannot add containers to            */
                                       /* tablespace                          */
#define SQL_RC_E282            -282    /* cannot drop tblspace, tbl conflict  */
#define SQL_RC_E283            -283    /* cannot drop only temp tablespace    */
#define SQL_RC_E284            -284    /* invalid tablespace type for clause  */
#define SQL_RC_E285            -285    /* all table parts must be in tblspce  */
#define SQL_RC_E286            -286    /* need default tblspce for new        */
                                       /* tables                              */
#define SQL_RC_E287            -287    /* SYSCATSPACE not for user objects    */
#define SQL_RC_E288            -288    /* long tablespace cannot use system   */
#define SQL_RC_E289            -289    /* cannot allocate new pages in        */
                                       /* tablespace                          */
#define SQL_RC_E290            -290    /* access to tablespace not allowed    */
#define SQL_RC_E291            -291    /* invalid state transition            */
#define SQL_RC_E292            -292    /* cannot create internal db file      */
#define SQL_RC_E293            -293    /* error accessing container           */
#define SQL_RC_E294            -294    /* container already in use            */
#define SQL_RC_E295            -295    /* container names too long            */
#define SQL_RC_E296            -296    /* tablespace limit exceeded           */
#define SQL_RC_E297            -297    /* container pathname too long         */
#define SQL_RC_E298            -298    /* bad container pathname              */
#define SQL_RC_E299            -299    /* container already added             */

#define SQL_RC_E301            -301    /* host variable has invalid type      */
#define SQL_RC_E302            -302    /* host variable value too large       */
#define SQL_RC_E303            -303    /* data types not comparable           */
#define SQL_RC_E304            -304    /* value not in range of host var      */
#define SQL_RC_E305            -305    /* host var cannot be null             */
#define SQL_RC_E308            -308    /* host var limit reached              */
#define SQL_RC_E309            -309    /* host var should not be null         */
#define SQL_RC_E311            -311    /* length of host var is negative      */
#define SQL_RC_E312            -312    /* unusable host variable              */
#define SQL_RC_E313            -313    /* wrong nbr of host variables         */
#define SQL_RC_E332            -332    /* no conversn source-cp to target-cp  */
#define SQL_RC_E334            -334    /* converion overflow                  */
#define SQL_RC_E338            -338    /* ON clause not valid for Outer Join  */
#define SQL_RC_E340            -340    /* duplicate common table expression   */
#define SQL_RC_E341            -341    /* cyclic ref between comm tbl exp     */
#define SQL_RC_E342            -342    /* comm tbl exp use UNION ALL          */
#define SQL_RC_E343            -343    /* col names required                  */
#define SQL_RC_E344            -344    /* columns must match exactly          */
#define SQL_RC_E345            -345    /* cannot use GROUP BY or HAVING here  */
#define SQL_RC_E346            -346    /* invalid reference to comm tbl exp   */
#define SQL_RC_E350            -350    /* LOB col cannot be idx, key, constr  */
#define SQL_RC_E351            -351    /* LOB col cannot be selected by DRDA  */
#define SQL_RC_E352            -352    /* LOB col cannot be inserted by DRDA  */
#define SQL_RC_E355            -355    /* LOB col cannot be logged            */

#define SQL_RC_E401            -401    /* operands not comparable             */
#define SQL_RC_E402            -402    /* invalid type for arithmetic op      */
#define SQL_RC_E403            -403    /* alias object undefined              */
#define SQL_RC_E404            -404    /* update/insert string too long       */
#define SQL_RC_E405            -405    /* numeric literal out of range        */
#define SQL_RC_E406            -406    /* derived value out of range          */
#define SQL_RC_E407            -407    /* column cannot be null               */
#define SQL_RC_E408            -408    /* invalid data type for column        */
#define SQL_RC_E409            -409    /* invalid operand for count           */
#define SQL_RC_E410            -410    /* float literal too long              */
#define SQL_RC_E412            -412    /* multiple columns in subquery        */
#define SQL_RC_E413            -413    /* overflow during data conversion     */
#define SQL_RC_E415            -415    /* incompatible data types for union   */
#define SQL_RC_E416            -416    /* long string in union                */
#define SQL_RC_E417            -417    /* invalid use of parameter markers    */
#define SQL_RC_E418            -418    /* parameter marker in select clause   */
#define SQL_RC_E419            -419    /* division produced negative scale    */
#define SQL_RC_E420            -420    /* invalid character in input string   */
#define SQL_RC_E421            -421    /* diff number of columns for union    */
#define SQL_RC_E423            -423    /* Invalid handle                      */
#define SQL_RC_E426            -426    /* dynamic COMMIT not valid            */
#define SQL_RC_E427            -427    /* dynamic ROLLBACK not valid          */
#define SQL_RC_E428            -428    /* DISCONNECT in unit of work          */
                                       /* notallow                            */
#define SQL_RC_E429            -429    /* Handle table full                   */
#define SQL_RC_E430            -430    /* UDF abnormal end                    */
#define SQL_RC_E431            -431    /* UDF interrupted                     */
#define SQL_RC_E432            -432    /* Parameter marker cannot have udf    */
                                       /* nm                                  */
#define SQL_RC_E433            -433    /* Value is too long                   */
#define SQL_RC_E435            -435    /* Inv SQLSTATE in RAISE_ERROR         */
#define SQL_RC_E436            -436    /* C language char string missing NUL  */
#define SQL_RC_E438            -438    /* App raised error                    */
#define SQL_RC_E439            -439    /* Error in UDF                        */
#define SQL_RC_E440            -440    /* No function with compatible arg     */
#define SQL_RC_E441            -441    /* Invalid use of DISTINCT with        */
                                       /* scalar                              */
#define SQL_RC_E442            -442    /* Error refering function in DML      */
#define SQL_RC_E443            -443    /* UDF returns error sqlstate          */
#define SQL_RC_E444            -444    /* Unable to access UDF function       */
#define SQL_RC_E448            -448    /* Exceed max number of parameters     */
#define SQL_RC_E449            -449    /* Invalid EXTERNAL NAME format        */
#define SQL_RC_E450            -450    /* UDF generates too long result       */
                                       /* value                               */
#define SQL_RC_E451            -451    /* DDL: invalid type for external UDF  */
#define SQL_RC_E452            -452    /* Hostvar file inaccessible           */
#define SQL_RC_E453            -453    /* Error in RETURNS and CAST FROM      */
#define SQL_RC_E454            -454    /* Duplicate UDF name and signature    */
#define SQL_RC_E455            -455    /* Diff schema for UDF name &          */
                                       /* specific                            */
#define SQL_RC_E456            -456    /* Duplicate specific name             */
#define SQL_RC_E457            -457    /* Name reserved for system use        */
#define SQL_RC_E458            -458    /* DDL refers UDF signature not found  */
#define SQL_RC_E459            -459    /* AS CAST use error                   */
#define SQL_RC_E461            -461    /* invalid CAST                        */
#define SQL_RC_E463            -463    /* UDF returns an invalid sqlstate     */
#define SQL_RC_E465            -465    /* Unable to start fenced UDF          */
#define SQL_RC_E473            -473    /* reserved object name                */
#define SQL_RC_E475            -475    /* Result type of source is different  */
#define SQL_RC_E476            -476    /* Reference to function is not        */
                                       /* unique                              */
#define SQL_RC_E478            -478    /* other obj depends on this obj       */
#define SQL_RC_E481            -481    /* GROUP BY: element nested in         */
                                       /* element                             */
#define SQL_RC_E483            -483    /* Parm num not match with source      */
#define SQL_RC_E486            -486    /* Boolean type is system used only    */
#define SQL_RC_E487            -487    /* Attempt to excute an SQL statement  */
#define SQL_RC_E489            -489    /* Inv BOOLEAN in select list result   */
#define SQL_RC_E491            -491    /* DDL: missing reqired clause         */
#define SQL_RC_E492            -492    /* DDL: miss match with source type    */
#define SQL_RC_E493            -493    /* UDF returned bad date/time value    */

#define SQL_RC_E501            -501    /* cursor not open (fetch/close)       */
#define SQL_RC_E502            -502    /* cursor already open                 */
#define SQL_RC_E503            -503    /* column not in update clause         */
#define SQL_RC_E504            -504    /* cursor name not defined             */
#define SQL_RC_E507            -507    /* cursor not open (update/delete)     */
#define SQL_RC_E508            -508    /* cursor not on a row                 */
#define SQL_RC_E509            -509    /* table not same as for cursor        */
#define SQL_RC_E510            -510    /* table cannot be modified            */
#define SQL_RC_E511            -511    /* for update not allowed              */
#define SQL_RC_E514            -514    /* cursor not prepared                 */
#define SQL_RC_E516            -516    /* describe not a prepared statement   */
#define SQL_RC_E517            -517    /* prepared statment not a select      */
#define SQL_RC_E518            -518    /* execute not a prepared statement    */
#define SQL_RC_E519            -519    /* statement has an open cursor        */
#define SQL_RC_E528            -528    /* duplicate primary/unique key        */
#define SQL_RC_E530            -530    /* invalid foreign key value           */
#define SQL_RC_E531            -531    /* cannot update primary key           */
#define SQL_RC_E532            -532    /* delete is restricted                */
#define SQL_RC_E533            -533    /* multi-row insert not allowed        */
#define SQL_RC_E534            -534    /* multi-row update of pk              */
#define SQL_RC_E535            -535    /* multi-row delete not allowed        */
#define SQL_RC_E536            -536    /* descendent in subquery              */
#define SQL_RC_E537            -537    /* dup column in key def               */
#define SQL_RC_E538            -538    /* foreign key does not match pk       */
#define SQL_RC_E539            -539    /* table does not have primary key     */
#define SQL_RC_E541            -541    /* duplicate referential constraint    */
#define SQL_RC_E542            -542    /* pk column cannot allow nulls        */
#define SQL_RC_E543            -543    /* restricted row delete               */
#define SQL_RC_E544            -544    /* check contraint violated            */
#define SQL_RC_E545            -545    /* check contraint not satisfied       */
#define SQL_RC_E546            -546    /* check contraint invalid             */
#define SQL_RC_E548            -548    /* check contraint invalid             */
#define SQL_RC_E551            -551    /* authorization error w/obj insert    */
#define SQL_RC_E552            -552    /* auth error w/o obj ins              */
#define SQL_RC_E553            -553    /* SYSIBM qualifier                    */
#define SQL_RC_E554            -554    /* cannot grant privilege to self      */
#define SQL_RC_E555            -555    /* cannot revoke privilege from self   */
#define SQL_RC_E556            -556    /* revoke stmt denied--priv not held   */
#define SQL_RC_E557            -557    /* invalid combination of privileges   */
#define SQL_RC_E558            -558    /* revoke stmt denied--has CONTROL     */
#define SQL_RC_E562            -562    /* privilege not allowed for public    */
#define SQL_RC_E567            -567    /* invalid authorization id            */
#define SQL_RC_E569            -569    /* user/group ambiguity                */
#define SQL_RC_E572            -572    /* Inoperative package                 */
#define SQL_RC_E573            -573    /* contraint col not primary key       */
#define SQL_RC_E574            -574    /* DEFAULT invalid for column          */
#define SQL_RC_E575            -575    /* view is inoperative                 */
#define SQL_RC_E576            -576    /* Repetitive alias chain              */
#define SQL_RC_E580            -580    /* Result of CASE expr cannot be NULL  */
#define SQL_RC_E581            -581    /* Data types of CASE expr incompat    */
#define SQL_RC_E582            -582    /* Inv predicate in CASE expr          */
#define SQL_RC_E583            -583    /* Variant or ext action function      */
#define SQL_RC_E584            -584    /* Inv use of NULL or DEFAULT          */
#define SQL_RC_E585            -585    /* Duplicate schema name               */
#define SQL_RC_E586            -586    /* Too many schema names               */
#define SQL_RC_E600            -600    /* udf - dup func signature            */
#define SQL_RC_E601            -601    /* duplicate table/view name           */
#define SQL_RC_E602            -602    /* too many columns in index           */
#define SQL_RC_E603            -603    /* cannot create unique index          */
#define SQL_RC_E604            -604    /* invalid length, precision, scale    */
#define SQL_RC_E607            -607    /* op not allowed on system tables     */
#define SQL_RC_E612            -612    /* duplicate column name               */
#define SQL_RC_E613            -613    /* primary key too long                */
#define SQL_RC_E614            -614    /* index key too long                  */
#define SQL_RC_E624            -624    /* table already has primary key       */
#define SQL_RC_E628            -628    /* DDL: multiple/conflict keywords     */
#define SQL_RC_E629            -629    /* foreign key is not nullable         */
#define SQL_RC_E631            -631    /* foreign key is too long             */
#define SQL_RC_E632            -632    /* delete rule restriction             */
#define SQL_RC_E633            -633    /* delete rule is restricted           */
#define SQL_RC_E634            -634    /* delete rule cannot be CASCADE       */
#define SQL_RC_E637            -637    /* dup pk or drop pk clause            */
#define SQL_RC_E638            -638    /* no column definitions               */
#define SQL_RC_E644            -644    /* invalid keyword value               */
#define SQL_RC_E658            -658    /* object cannot be explicitely        */
                                       /* dropped                             */
#define SQL_RC_E659            -659    /* architectural size limit of object  */
#define SQL_RC_E667            -667    /* ref constraint does not hold        */
#define SQL_RC_E668            -668    /* table in CHECK PENDING state        */
#define SQL_RC_E669            -669    /* cannot drop primary key             */
#define SQL_RC_E670            -670    /* row length too large                */
#define SQL_RC_E673            -673    /* primary key not unique              */
#define SQL_RC_E680            -680    /* too many columns for table          */
#define SQL_RC_E683            -683    /* incompatible column constraint      */
#define SQL_RC_E696            -696    /* invalid trigger definition          */
#define SQL_RC_E697            -697    /* invalid correlation name use        */

#define SQL_RC_E707            -707    /* object uses reserved name           */
#define SQL_RC_INV_REPL        -713    /* invalid replace value for sp reg    */
#define SQL_RC_E723            -723    /* trigger error                       */
#define SQL_RC_E724            -724    /* max level of cascading              */
#define SQL_RC_E727            -727    /* Invalid implicit PREP or REBIND     */
#define SQL_RC_E750            -750    /* Table cannot be renamed             */
#define SQL_RC_E751            -751    /* Invalid triggered statement         */
#define SQL_RC_E752            -752    /* Inoperative package                 */

#define SQL_RC_E801            -801    /* divide by zero                      */
#define SQL_RC_E802            -802    /* arith overflow or divide by zero    */
#define SQL_RC_E803            -803    /* distinct violation                  */
#define SQL_RC_E804            -804    /* bad input parameters                */
#define SQL_RC_E805            -805    /* program not bound                   */
#define SQL_RC_E808            -808    /* inconsistent connect semantics      */
#define SQL_RC_E811            -811    /* more than one row/value             */
#define SQL_RC_E818            -818    /* time stamp conflict                 */
#define SQL_RC_E822            -822    /* invalid address in sqlda            */
#define SQL_RC_E840            -840    /* too many items in list              */
#define SQL_RC_E842            -842    /* connection already exists           */
#define SQL_RC_E843            -843    /* connection does not exist           */
#define SQL_RC_E847            -847    /* can't change connection settings    */
#define SQL_RC_E859            -859    /* TM not for 2 phase commit apps      */
#define SQL_RC_E865            -865    /* inv TM_DATABASE value               */
#define SQL_RC_E866            -866    /* connect redirect failed             */
#define SQL_RC_E868            -868    /* connection already exists           */

#define SQL_RC_E901            -901    /* non-fatal system error              */
#define SQL_RC_E902            -902    /* fatal error                         */
#define SQL_RC_E903            -903    /* commit failed, rollback             */
#define SQL_RC_E904            -904    /* resource unavailable                */
#define SQL_RC_E905            -905    /* resource limit exceeded             */
#define SQL_RC_E906            -906    /* function disabled                   */
#define SQL_RC_E908            -908    /* BIND operation not allowed          */
#define SQL_RC_E909            -909    /* object deleted                      */
#define SQL_RC_E910            -910    /* drop pending                        */
#define SQL_RC_E911            -911    /* deadlock                            */
#define SQL_RC_E912            -912    /* too many lock requests              */
#define SQL_RC_E913            -913    /* dist env rollback                   */
#define SQL_RC_E917            -917    /* remote rebind from DRDA failed      */
#define SQL_RC_E918            -918    /* ROLLBACK required                   */
#define SQL_RC_E920            -920    /* reject DB connection to SA REQ      */
#define SQL_RC_E925            -925    /* COMMIT not allowed                  */
#define SQL_RC_E926            -926    /* ROLLBACK not allowed                */
#define SQL_RC_E930            -930    /* insufficient storage                */
#define SQL_RC_INODE           -931    /* all inodes used, system limit       */
#define SQL_RC_E950            -950    /* cursors active on dropped object    */
#define SQL_RC_E951            -951    /* table in use - alter disallowed     */
#define SQL_RC_E952            -952    /* user cancel                         */
#define SQL_RC_E953            -953    /* agent heap too small                */
#define SQL_RC_E954            -954    /* application heap too small          */
#define SQL_RC_E955            -955    /* sort heap error                     */
#define SQL_RC_E956            -956    /* database heap too small             */
#define SQL_RC_E957            -957    /* requestor comm heap too small       */
#define SQL_RC_E958            -958    /* max number of files open            */
#define SQL_RC_E959            -959    /* server comm heap too small          */
#define SQL_RC_E960            -960    /* max nbr of files in database        */
#define SQL_RC_E961            -961    /* rqstr remote svcs heap too small    */
#define SQL_RC_E962            -962    /* svr remote svcs heap too small      */
#define SQL_RC_E964            -964    /* log file full                       */
#define SQL_RC_E966            -966    /* error opening sqlcode mapping file  */
#define SQL_RC_E967            -967    /* format error in sqlcode map file    */
#define SQL_RC_E968            -968    /* disk full                           */
#define SQL_RC_E969            -969    /* unknown sql error another product   */
#define SQL_RC_E970            -970    /* read-only file                      */

#define SQL_RC_E972_DB2AIX     -10019  /* incorrect diskette                  */
#define SQL_RC_E972_DB2OS2     -972    /* incorrect diskette                  */
#define SQL_RC_E972            SQL_RC_E972_DB2OS2 /* incorrect diskette       */

#define SQL_RC_E973            -973    /* out of memory error                 */

#define SQL_RC_E974_DB2AIX     -10019  /* drive locked                        */
#define SQL_RC_E974_DB2OS2     -974    /* drive locked                        */
#define SQL_RC_E974            SQL_RC_E974_DB2OS2 /* drive locked             */

#define SQL_RC_QBACK           -975    /* quiesce backup                      */

#define SQL_RC_E976_DB2AIX     -10019  /* diskette door open                  */
#define SQL_RC_E976_DB2OS2     -976    /* diskette door open                  */
#define SQL_RC_E976            SQL_RC_E976_DB2OS2 /* diskette door open       */

#define SQL_RC_E977            -977    /* unknown commit state                */
#define SQL_RC_E978_DB2AIX     -10019  /* diskette write-protected            */
#define SQL_RC_E978_DB2OS2     -978    /* diskette write-protected            */
#define SQL_RC_E978            SQL_RC_E978_DB2OS2 /* diskette write           */
                                       /* protected                           */

#define SQL_RC_E979            -979    /* commit failed with SYNCPOINT NONE   */
#define SQL_RC_E980            -980    /* disk error                          */
#define SQL_RC_E982            -982    /* disk error on temp file             */
#define SQL_RC_E984            -984    /* unsuccessful commit or rollback     */
#define SQL_RC_E985            -985    /* file error - catalog file bad       */
#define SQL_RC_E986            -986    /* file error - file renamed           */
#define SQL_RC_E987            -987    /* application shared memory cannot    */
                                       /* be allocated                        */
#define SQL_RC_E990            -990    /* index structure limit error         */
#define SQL_RC_E992            -992    /* release number incompatible         */
#define SQL_RC_E994            -994    /* reserved                            */
#define SQL_RC_E996            -996    /* error freeing pages in DMS          */
                                       /* tablespace                          */
#define SQL_RC_E998            -998    /* General XA error                    */

#define SQL_RC_E1007           -1007   /* error finding pages in DMS          */
                                       /* tablespace                          */
#define SQL_RC_E1008           -1008   /* invalid tablespace id               */
#define SQL_RC_E1164           -1164   /* invalid SQLDA or host variables     */
#define SQL_RC_E1180           -1180   /* UDF caused an OLE error             */
#define SQL_RC_E1181           -1181   /* UDF raised an exception             */

#define SQL_RC_E1216           -1216   /* invalid use of graphic data         */
#define SQL_RC_E1217           -1217   /* REAL data type not supported        */
#define SQL_RC_E1219           -1219   /* out of private memory               */
#define SQL_RC_E1226           -1226   /* max number of agents started        */
#define SQL_RC_E1227           -1227   /* Updatale cat values inv             */
#define SQL_RC_E1229           -1229   /* System error rollback               */
#define SQL_RC_W1244           1244    /* Disconn at next commit              */
#define SQL_RC_E1245           -1245   /* Max client connects                 */
#define SQL_RC_E1247           -1247   /* XA TM uses syncpoint 2              */
#define SQL_RC_E1248           -1248   /* db not defined with TM              */
#define SQL_RC_E1290           -1290   /* DB2CLIENTCOMM env var inv           */
#define SQL_RC_E1291           -1291   /* direcory services error             */
#define SQL_RC_E1293           -1293   /* global dir error                    */
#define SQL_RC_E1294           -1294   /* global dir path invalid             */
#define SQL_RC_E1295           -1295   /* global dir router invalid           */

#define SQL_RC_E1339           -1339   /* Not Atomic Compound SQL error(s)    */

#define SQL_RC_E1419           -1419   /* package not executable              */
#define SQL_RC_E1420           -1420   /* too many concat operators           */
#define SQL_RC_E1421           -1421   /* MBCS conversion error               */
#define SQL_RC_E1422           -1422   /* Container wrong size                */
#define SQL_RC_E1423           -1423   /* no blobs for dwn lvl cl             */
#define SQL_RC_E1424           -1424   /* too many transition tbles           */

#define SQL_RC_E1462           -1462   /* only valid for sync mgr connection  */

#define SQL_RC_E1750           -1750   /* foreign keys not allowed for        */
                                       /* tables created not logged           */
                                       /* initially                           */
#define SQL_RC_E1751           -1751   /* nodegroups must have at least one   */
                                       /* node                                */
#define SQL_RC_E1752           -1752   /* tablespace not created in the       */
                                       /* correct nodegroup                   */
#define SQL_RC_E1753           -1753   /* a node does not have the complete   */
                                       /* temporary tablespaces               */
#define SQL_RC_E1754           -1754   /* all tablespace in CREATE TABLE      */
                                       /* must be in the same nodegroup       */
#define SQL_RC_E1756           -1756   /* more than one clause specifies      */
                                       /* containers without ON NODES clause  */
#define SQL_RC_E1757           -1757   /* missing USING clause without ON     */
                                       /* NODES clause                        */
#define SQL_RC_E1760           -1760   /* missing clause for create stored    */
                                       /* procedure                           */
#define SQL_RC_E1761           -1761   /* nodegroup not defined for buffer    */
                                       /* pool                                */

#define SQL_RC_E1820           -1820   /* Action on LOB value failed          */
#define SQL_RC_E1822           -1822   /* Unexpected error from data source   */
#define SQL_RC_E1823           -1823   /* No data type mapping exists for     */
                                       /* server                              */
#define SQL_RC_E1825           -1825   /* Statement cannot be handled by      */
                                       /* Datajoiner                          */
#define SQL_RC_E1826           -1826   /* Invalid value for system catalog    */
                                       /* column                              */
#define SQL_RC_E1827           -1827   /* user mapping undefined              */
#define SQL_RC_E1828           -1828   /* server option undefined             */

#define SQL_RC_NO_TCPIP        -1468   /* TCPIP not running                   */
#define SQL_RC_NODE_INVALID    -1469   /* invalid node                        */
#define SQL_RC_DB2NODE_INVALID -1470   /* DB2NODE env var invalid             */
#define SQL_RC_LOG_MISMATCH    -1471   /* nodes out of sync                   */
#define SQL_RC_TIMEDIFF_CA     -1472   /* connect fail, system clocks out of  */
                                       /* sync                                */
#define SQL_RC_TIMEDIFF_CO     -1473   /* commit fail, system clocks out of   */
                                       /* sync                                */
#define SQL_RC_TIMEDIFF_W      -1474   /* transaction OK, system clocks out   */
                                       /* of sync                             */
#define SQL_RC_E1476           -1476   /* rollback on table error             */
#define SQL_RC_E1477           -1477   /* table not accessible                */

#define SQL_RC_E1590           -1590   /* LONG not allowed on devices         */
#define SQL_RC_E3600           -3600   /* Table not in check pend state       */
#define SQL_RC_W3601           3601    /* Auto Check pending state            */
#define SQL_RC_W3602           3602    /* Constraint violation moved          */
#define SQL_RC_E3603           -3603   /* Constraint Violations               */
#define SQL_RC_E3604           -3604   /* Invalid Exception Table             */
#define SQL_RC_E3605           -3605   /* Exception Table same as Check       */
                                       /* Table                               */
#define SQL_RC_E3606           -3606   /* # check & exception tables not      */
                                       /* match                               */
#define SQL_RC_E3608           -3608   /* Parent in Check Pending state       */

#define SQL_RC_E4300           -4300   /* Java support not installed          */
#define SQL_RC_E4301           -4301   /* Java startup, comm, shutdown        */
                                       /* failed                              */
#define SQL_RC_E4302           -4302   /* Java unclassified exception         */
#define SQL_RC_E4303           -4303   /* Java could not parse class!method   */
#define SQL_RC_E4304           -4304   /* Java could not instantiate class    */
#define SQL_RC_E4305           -4305   /* Java internal error code            */
#define SQL_RC_E4306           -4306   /* Java cannot call method             */
#define SQL_RC_E4307           -4307   /* Java method call problems           */

#define SQL_RC_E5051           -5051   /* Invalid qualifier specified in      */
                                       /* CREATE SCHEMA                       */

#define SQL_RC_E6040           -6040   /* Insufficient FCM buffers            */
#define SQL_RC_E6041           -6041   /* Insufficient FCM connection         */
                                       /* entries                             */
#define SQL_RC_E6042           -6042   /* Insufficient FCM message anchors    */
#define SQL_RC_E6043           -6043   /* Insufficient FCM request blocks     */
#define SQL_RC_E6071           -6071   /* New node requires stop and start    */

#define SQL_RC_E8100           -8100   /* Page number too high                */
#define SQL_RC_E8101           -8101   /* Segment in error                    */

#define SQL_RC_E20005          -20005  /* internal object limit exceeded      */

#define SQL_RC_E30000          -30000  /* Distribution protocol error, no     */
                                       /* disconnect                          */
#define SQL_RC_E30020          -30020  /* Distribution protocol error,        */
                                       /* disconnect                          */
#define SQL_RC_E30021          -30021  /* Distribution compatibility error    */
#define SQL_RC_E30040          -30040  /* Distribution memory allocation err  */
#define SQL_RC_E30041          -30041  /* Distribution memory allocation      */
                                       /* err, disconnect                     */
#define SQL_RC_E30050          -30050  /* Invalid command while bind in prog  */
#define SQL_RC_E30051          -30051  /* Bind not active                     */
#define SQL_RC_E30053          -30053  /* Bind Owner authorization failure    */
#define SQL_RC_E30060          -30060  /* RDB authorization failure           */
#define SQL_RC_E30061          -30061  /* RDB not found                       */
#define SQL_RC_E30070          -30070  /* Distribution command error          */
#define SQL_RC_E30071          -30071  /* Distribution object error           */
#define SQL_RC_E30072          -30072  /* Distribution parameter error        */
#define SQL_RC_E30073          -30073  /* Distribution parameter value error  */
#define SQL_RC_E30074          -30074  /* Distribution reply error            */
#define SQL_RC_E30080          -30080  /* Communication error                 */
#define SQL_RC_E30081          -30081  /* Communication error                 */
#define SQL_RC_E30082          -30082  /* Security error                      */
#define SQL_RC_E30090          -30090  /* Remote operation invalid            */
#define SQL_RC_W30101          30101   /* Rebind options ignored              */
#define SQL_RC_W30102          30102   /* Connection disabled                 */

/* Database Monitor SQLCODES                                                  */

#define SQLM_RC_BAD_PATH       -1612   /* bad path specified for event        */
                                       /* monitor                             */
#define SQLM_RC_BAD_OPTION     -1613   /* bad OPTION specified for event      */
                                       /* monitor                             */
#define SQLM_RC_IO_ERROR       -1614   /* I/O error on activating event       */
                                       /* monitor                             */
#define SQLM_RC_NOT_ACTIVATED  -1616   /* Event monitor not activated         */
#define SQLM_RC_EVMON_FULL     -1617   /* Event monitor data files are full   */
#define SQLM_RC_PATH_IN_USE    -1618   /* Event monitor path is in use        */
#define SQLM_RC_CANNOT_DROP    -1619   /* Cannot drop active event monitor    */
#define SQLM_RC_MUST_COMMIT    -1621   /* Must commit to use event monitor    */
#define SQLM_RC_BAD_STATE      -1622   /* Invalid state                       */

#ifdef __cplusplus 
}
#endif

#endif /* SQL_H_SQLCODES */
