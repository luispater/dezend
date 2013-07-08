/*
 * Program:	RFC-822 routines (originally from SMTP)
 *
 * Author:	Mark Crispin
 *		Networks and Distributed Computing
 *		Computing & Communications
 *		University of Washington
 *		Administration Building, AG-44
 *		Seattle, WA  98195
 *		Internet: MRC@CAC.Washington.EDU
 *
 * Date:	27 July 1988
 * Last Edited:	16 April 1998
 *
 * Sponsorship:	The original version of this work was developed in the
 *		Symbolic Systems Resources Group of the Knowledge Systems
 *		Laboratory at Stanford University in 1987-88, and was funded
 *		by the Biomedical Research Technology Program of the National
 *		Institutes of Health under grant number RR-00785.
 *
 * Original version Copyright 1988 by The Leland Stanford Junior University
 * Copyright 1997 by the University of Washington
 *
 *  Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notices appear in all copies and that both the
 * above copyright notices and this permission notice appear in supporting
 * documentation, and that the name of the University of Washington or The
 * Leland Stanford Junior University not be used in advertising or publicity
 * pertaining to distribution of the software without specific, written prior
 * permission.  This software is made available "as is", and
 * THE UNIVERSITY OF WASHINGTON AND THE LELAND STANFORD JUNIOR UNIVERSITY
 * DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED, WITH REGARD TO THIS SOFTWARE,
 * INCLUDING WITHOUT LIMITATION ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE, AND IN NO EVENT SHALL THE UNIVERSITY OF
 * WASHINGTON OR THE LELAND STANFORD JUNIOR UNIVERSITY BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
 * CONTRACT, TORT (INCLUDING NEGLIGENCE) OR STRICT LIABILITY, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#define rfc822_write_address(dest,adr) \
  rfc822_write_address_full (dest,adr,NIL)


/* Function prototypes */

void rfc822_header (char *header,ENVELOPE *env,BODY *body);
void rfc822_address_line (char **header,char *type,ENVELOPE *env,ADDRESS *adr);
void rfc822_header_line (char **header,char *type,ENVELOPE *env,char *text);
char *rfc822_write_address_full (char *dest,ADDRESS *adr,char *base);
void rfc822_address (char *dest,ADDRESS *adr);
void rfc822_cat (char *dest,char *src,const char *specials);
void rfc822_write_body_header (char **header,BODY *body);
char *rfc822_default_subtype (unsigned short type);
void rfc822_parse_msg (ENVELOPE **en,BODY **bdy,char *s,unsigned long i,
		       STRING *bs,char *host,unsigned long flags);
void rfc822_parse_content (BODY *body,STRING *bs,char *h,unsigned long flags);
void rfc822_parse_content_header (BODY *body,char *name,char *s);
void rfc822_parse_parameter (PARAMETER **par,char *text);
void rfc822_parse_adrlist (ADDRESS **lst,char *string,char *host);
ADDRESS *rfc822_parse_address (ADDRESS **lst,ADDRESS *last,char **string,
			       char *defaulthost);
ADDRESS *rfc822_parse_group (ADDRESS **lst,ADDRESS *last,char **string,
			     char *defaulthost);
ADDRESS *rfc822_parse_mailbox (char **string,char *defaulthost);
long rfc822_phraseonly (char *end);
ADDRESS *rfc822_parse_routeaddr (char *string,char **ret,char *defaulthost);
ADDRESS *rfc822_parse_addrspec (char *string,char **ret,char *defaulthost);
char *rfc822_parse_phrase (char *string);
char *rfc822_parse_word (char *string,const char *delimiters);
char *rfc822_cpy (char *src);
char *rfc822_quote (char *src);
ADDRESS *rfc822_cpy_adr (ADDRESS *adr);
void rfc822_skipws (char **s);
char *rfc822_skip_comment (char **s,long trim);

typedef long (*soutr_t) (void *stream,char *string);
typedef long (*rfc822out_t) (char *t,ENVELOPE *env,BODY *body,soutr_t f,
			     void *s,long ok8bit);

long rfc822_output (char *t,ENVELOPE *env,BODY *body,soutr_t f,void *s,
		    long ok8bit);
void rfc822_encode_body_7bit (ENVELOPE *env,BODY *body);
void rfc822_encode_body_8bit (ENVELOPE *env,BODY *body);
long rfc822_output_body (BODY *body,soutr_t f,void *s);
void *rfc822_base64 (unsigned char *src,unsigned long srcl,unsigned long *len);
unsigned char *rfc822_binary (void *src,unsigned long srcl,unsigned long *len);
unsigned char *rfc822_qprint (unsigned char *src,unsigned long srcl,
			      unsigned long *len);
unsigned char *rfc822_8bit (unsigned char *src,unsigned long srcl,
			    unsigned long *len);
