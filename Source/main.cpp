/**
 * Main program entry.
 */

#include "CAppNodeImpl.h"
#include "Utility/Utils.h"

#define ELOG_CONFIG_PATH "Config/log.conf"

// Specify domain application belongs and name.
#define DOMAIN_ID 0
#define APP_NAME "AppNode"

INITIALIZE_EASYLOGGINGPP

void InitializeLogger( CAppNodeImpl *applicationIn )
{
	// Load logger config file
	el::Configurations logConfig( ELOG_CONFIG_PATH );

	// Set configuration
	el::Loggers::reconfigureAllLoggers( logConfig );

	LOG( INFO ) << "<-------------------------------->";
	LOG( INFO ) << "<--------" << applicationIn->GetName();
	LOG( INFO ) << "<-------------------------------->";
}

int main( int argc, char *argv[] )
{
	CAppNodeImpl test( argc, argv, APP_NAME, DOMAIN_ID );

	std::unique_ptr<CAppNodeImpl> application(&test);

	try
	{
		application->Initialize();

		application->Run();

	}catch( std::exception &excpt )
	{
		LOG( ERROR ) << "Exception starting application: " << application->GetName() << " " << excpt.what();

		// Clean up
		application->CleanUp();
	}

	return 0;
}
