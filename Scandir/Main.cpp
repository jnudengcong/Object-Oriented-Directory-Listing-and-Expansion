#include <iostream>
#include <string>
#include "Pattern.h"
#include "CommandFacade.h"
#include "ConcreteCommand.h"

using namespace std;

int main()
{
	Receiver* rev = new Receiver();
	ConcreteCommand* cmd = new ConcreteCommand(rev);
	Invoker* inv = new Invoker();

	CommandFacade cf(rev, inv, cmd);
	cf.useCommand();

	return 0;
}