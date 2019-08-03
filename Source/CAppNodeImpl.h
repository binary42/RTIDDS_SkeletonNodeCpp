#pragma once

#include "CAppNode.h"

class CAppNodeImpl : CAppNode
{
public:
	CAppNodeImpl( int argc, char *argv[], std::string appNameIn, int domainIDIn );
	virtual ~CAppNodeImpl();

	// Methods
	void Initialize();
	virtual std::string GetName();
	virtual void Run();
	virtual void CleanUp();

	// Overrides

	//Attributes

};
