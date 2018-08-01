#include "CommandFacade.h"
#include "ConcreteCommand.h"

//CommandFacade::CommandFacade()
//{
//	_rev = new Receiver();
//	_inv = new Invoker();
//	_cmd = new ConcreteCommand(_rev);
//}

CommandFacade::CommandFacade(Receiver * rev, Invoker * inv, Command * cmd)
{
	_rev = rev;
	_inv = inv;
	_cmd = cmd;
}

CommandFacade::~CommandFacade()
{
	delete _rev;
	delete _inv;
	delete _cmd;
}

void CommandFacade::useCommand()
{
	_inv->setCommand(_cmd);
	_inv->action();
}
