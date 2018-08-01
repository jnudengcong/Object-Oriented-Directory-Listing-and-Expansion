#ifndef GUARD_Invoker_h
#define GUARD_Invoker_h

#include "Command.h"

class Invoker
{
private:
	Command* _cmd;

public:
	void setCommand(Command* cmd);
	void action();
};

#endif
