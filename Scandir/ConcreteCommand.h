#ifndef GUARD_ConcreteCommand_h
#define GUARD_ConcreteCommand_h

#include "Command.h"
#include "Receiver.h"

class ConcreteCommand : public Command
{
protected:
	Receiver* _receiver;

public:
	ConcreteCommand(Receiver* re) :_receiver(re)
	{

	}
	~ConcreteCommand()
	{

	}
	void execute();
};

#endif
