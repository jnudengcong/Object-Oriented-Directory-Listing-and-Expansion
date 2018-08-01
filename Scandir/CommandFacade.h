#ifndef GUARD_CommandFacade_h
#define GUARD_CommandFacade_h

#include "Command.h"
#include "Receiver.h"
#include "Invoker.h"

class CommandFacade
{
public:
	//CommandFacade();
	CommandFacade(Receiver* rev, Invoker* inv, Command* cmd);
	~CommandFacade();
	void useCommand();

private:
	Command* _cmd;
	Receiver* _rev;
	Invoker* _inv;
};


#endif
