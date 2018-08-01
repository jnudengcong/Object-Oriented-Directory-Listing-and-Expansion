#include "Invoker.h"

void Invoker::setCommand(Command* cmd)
{
	_cmd = cmd;
}

void Invoker::action()
{
	_cmd->execute();
}