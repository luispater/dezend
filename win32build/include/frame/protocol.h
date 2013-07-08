/*
   PROPRIETARY SOURCE CODE OF NETSCAPE COMMUNICATIONS CORPORATION.

   Copyright (c) 1994, 1995, 1996, and 1997 Netscape Communications
   Corporation.  All rights reserved.

   Use of this Source Code is subject to the terms of the applicable
   license agreement from Netscape Communications Corporation.
*/

/*
 * protocol.h: Switch which protocol we're speaking. 
 * 
 * Currently only HTTP, but expected to include MTP in the future.
 * 
 * Rob McCool
 */


#if defined(MCC_HTTPD) || defined(MCC_PROXY) || defined(MCC_BATMAN) || defined(MCC_NEWS)
#include "http.h"
#endif
