#ifndef GUARD_Command_h
#define GUARD_Command_h

class Command
{
protected:
	Command() {};

public:
	virtual ~Command() {};
	virtual void execute() = 0;
};

#endif
