#include "ConcreteCommand.h"
#include "Receiver.h"

void ConcreteCommand::execute()
{
	_receiver->select();
}
