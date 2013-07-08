/* p_port.h
 * Copyright (C) 1997-98 Thomas Merz. All rights reserved.
 *
 * PDFlib portability stuff
 */

#ifndef P_PORT_H
#define P_PORT_H

/* ---------------------- Windows -------------------*/
#ifdef _WIN32
#ifndef WIN32
#define WIN32
#endif
#define bool int
#define PDF_HAS_BOOL
#endif

#ifdef WIN32
#define NEED_GETOPT
#define READMODE	"rb"
#define WRITEMODE	"wb"
#endif

/* ---------------------- MS-DOS -------------------*/
#ifdef DOS
#define NEED_GETOPT
#define READMODE	"rb"
#define WRITEMODE	"wb"
#endif

/* ---------------------- Macintosh -------------------*/
#ifdef MAC
#define NEED_GETOPT
#define READMODE	"rb"
#define WRITEMODE	"wb"
#define PATHSEP		":"
#endif

/* ---------------------- NeXT -------------------*/

#ifdef NeXT
#endif

/* ---------------------- Defaults -------------------*/
/* Note: the defaults section is essentially the POSIX section
 * since this is my main development platform
 */

#ifndef WRITEMODE
#define WRITEMODE	"w"
#endif

#ifndef READMODE
#define READMODE	"r"
#endif

#ifndef PATHSEP
#define PATHSEP		"/"
#endif

/*
 * Define PI if we don't have it already
 * This is the case for Watcom 10.6, for example.
 */
#ifndef M_PI
#define M_PI        3.14159265358979323846      /* pi */
#endif

#ifdef NEED_GETOPT
extern int getopt(int nargc, char **nargv, char * ostr);
extern char *optarg;
extern int optind;
#endif

/* The dreaded boolean type is introduced in so many places.
 * The PDF_HAS_BOOL define is a humble attempt to handle this situation.
 */

#ifndef PDF_HAS_BOOL
typedef int bool;
#endif

#endif			/* P_PORT_H */
