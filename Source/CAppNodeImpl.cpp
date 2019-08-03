#include "CAppNodeImpl.h"
#include "Utility/Utils.h"

/**
 * Constructor
 */
CAppNodeImpl::CAppNodeImpl( int argc, char *argv[], std::string appNameIn, int domainIDIn ):
	CAppNode( argc, argv, appNameIn ){
	for( int i = 0; i < _argCount; ++i)
	{
		_pargVect[i] = argv[i];
	}
}

/**
 * Destructor
 */
CAppNodeImpl::~CAppNodeImpl(){

}

/**
 * Void method that initializes all components of the node. Edit as needed.
 */
void CAppNodeImpl::Initialize(){
	// Setup signal handler for ctrl-c
	_psignalHandler->SetupSignalHandlers();

	// Init all DDS related components
	InitializeWaitSet();
}

/**
 * Returns the name of the application.
 * @return		_appname		string type
 */
std::string CAppNodeImpl::GetName(){
	return _appName;
}

/**
 * Main execution method. Application specific code goes here. Calls HandleWaiCondition()
 */
void CAppNodeImpl::Run(){
	while( !_psignalHandler->GotExitSignal() )
	{
		HandleWaitSetConditions();
		// TODO - stuff with data
	}

	LOG(INFO)<< "Application terminated.";
}
