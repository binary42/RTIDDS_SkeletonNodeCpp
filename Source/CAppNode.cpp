#include "CAppNode.h"
#include "Utility/Utils.h"

/**
 * Constructor. Accepts the command line arguments and application string represetning the app name.
 * @param		argc				int type argument count
 * @param		argv[]				ACE_TCHAR type pointer containing arguments
 * @param		appNameIn			string name of application
 */
CAppNode::CAppNode( int argc, char *argv[], std::string appNameIn ) : _appName( appNameIn )

{
	for( size_t i = 0; i < argc; ++i )
	{
		std::string temp( argv[i] );
		m_commandLineArguments.push_back( temp );
	}
	_psignalHandler = new CSignalHandler();
}

/**
 *	Destructor. Deletes the _psignalhandle pointer
 */
CAppNode::~CAppNode()
{
	SafeDelete( _psignalHandler );
}

// TODO - Override as needed
void CAppNode::PublishData(){}
void CAppNode::ReadData(){}
void CAppNode::UpdateNextExecutionTime(){}

// WaitSet related functions /////////////////////////////////////
void CSensorPublisher::InitializeWaitSet()
{
	// Set up the Guard Condition
	auto sigintHandlerCallback = [this]( DDS::Condition* conditionIn )
	{
		DDS::GuardCondition *condition = (DDS::GuardCondition*)conditionIn;

		// If the condition was set to true, quit the application
		if( condition->get_trigger_value() == true )
		{
			m_quitApplication = true;
		}
	};


	// Normally, you would register other status/read/etc conditions you'd like to handle here


	// Register callbacks in our handler map
	m_waitSetHandlers.insert( std::make_pair( m_pSigintCondition.get(), sigintHandlerCallback ) );

	// Attach the conditions to the WaitSet object
	m_pWaitSet->attach_condition( m_pSigintCondition.get() );
}

void CSensorPublisher::HandleWaitSetConditions()
{
	DDS::ConditionSeq activeConditions;
	DDS::ReturnCode_t ret;

	// Set timeout to 0, since we are using a different mechanism to drive our loop update rate.
	DDS::Duration_t timeout{ 0, 0 };

	// Wait for active conditions
	ret = m_pWaitSet->wait( activeConditions, timeout );

	if( ret != DDS::RETCODE_OK )
	{
		// Timed out. Do nothing, as we expect this to happen frequently.
	}
	else
	{
		// Some condition was triggered, so we loop through the active conditions
		for( int i = 0; i < activeConditions.length(); ++i )
		{
			try
			{
				// Call the appropriate handler for each active condition
				// Warning: Make sure you registered a callback for every status mask you enabled in the WaitSet. The try-catch will let you know if you didn't.
				m_waitSetHandlers.at( (DDS::Condition*)activeConditions[ i ] )( activeConditions[ i ] );
			}
			catch( const std::exception &e )
			{
				LOG( ERROR ) << "Exception handling WaitSet: " << e.what();
			}
		}
	}
}
