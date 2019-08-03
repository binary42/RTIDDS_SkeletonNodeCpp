#pragma once

// Signal Handling
#include "Utility/CSignalException.h"
#include <iostream>

class CAppNode
{
public:
	CAppNode( int argc, char *argv[], std::string appNameIn );
	virtual ~CAppNode();

	// Methods - interface - pure virtual
	virtual std::string GetName() 					= 0;
	virtual void CleanUp() 							= 0;
	virtual void Run() 								= 0;

	// TODO - Override in CAppNodeImpl class
	virtual void PublishData();
	virtual void ReadData();
	virtual void UpdateNextExecutionTime();

	// Attributes
	std::vector<std::string> 						m_commandLineArguments;

protected:
	// Methods
	void InitializeWaitSet();
	void HandleWaitSetConditions();

	// Attributes
	std::string										_appName;
	CSignalHandler									*_psignalHandler;
};
