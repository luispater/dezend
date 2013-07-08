//////
// DTXNETCS.hpp - Header file for the DTXNetClientServer class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXNETCS__
#define __DTXNETCS__

#include <dtxnetc.hpp>
#include <dtxthr.hpp>
#include <dtxlnk.hpp>


//This class is used when you want to create a client that communicates
// to a server but does not except connections like a server.  It does
// however behave like a server from the stand point of forking off under
// UNIX and running as a service under NT.  This allows you to program
// applications that sleep, wake up and send commands to server applications.

//To use this class you will need to inherit from it and simply override
// the netRun method.  Think of the netRun method as your main section of
// code.  You can set the command line arguments as globals since these are
// passed in values and there's no need to update them (thread issues).


class DTX_CLSEXPENTRY DTXNetClientServer : public DTXNetClient
{
public:
	DTXNetClientServer();
	virtual ~DTXNetClientServer();

	virtual DTX_VOID  netRun();//Overload this method!
	virtual DTX_VOID  netRunServer( DTX_PSZ pszService = NULL, DTX_BOOLEAN fService = FALSE );
};


#endif

