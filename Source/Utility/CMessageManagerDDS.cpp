#include "CMessageManagerDDS.h"

CMessageManagerDDS::CMessageManagerDDS(){
	LOG(INFO) << "Initializing the MessageManager...";

	// Load application and QoS library files
	LoadXMLProfiles();

	// Get the participant factory
	auto factory = DDS::DomainParticipanFactory::get_instance();

	// TODO - register type support for generated types. Type names defined in AppLibrary.xml
	// factory->register_type_support();

	// TODO - Create a participant using the profile in AppLibrary.xm
	// _pParticipant = factory->create_participant_from_config("...")

	// TODO - Fetch pointers for convient DDS entity access

	LOG(INFO) << "MessageManager initialized.";
}

CMessageManagerDDS::~CMessageManagerDDS(){
	LOG(INFO)<< "Cleaning up the MessageManager";

	// TODO - Delete DDS entities
	// TODO - Delete the participant

	LOG(INFO)<< "Manager cleaned.";
}

void CMessageManagerDDS::LoadXMLProfiles(){
	LOG(INFO)<< "Loading XML profiles.";

	std::vector<std::string> profilePaths;

	// QoS
	profilePaths.push_back("DDS/XML/Qos/RTIUserProfiles.xml");
	profilePaths.push_back("DDS/XML/Qos/UserProfiles.xml");

	// Application
	profilePaths.puch_back("DDS/XML/Application/AppLibrary.xml");

	// Update the factory profiles
	SetupFactoryProfiles(profilePaths);

	LOG(INFO)<< "Loaded all profiles.";
}

void CMesssagemanager::SetupFactoryProfiles(const std::vector<std::string> &profilePathIn){
	// Get the factory instance
	auto factory = DD::DomainParticipanFactory::get_instance();

	// Get the curent QoS setting
	DDS::DomainParticipantFactoryQos factoryQos;
	factory->get_qos(factoryQos);

	// Resize for new files
	factoryQos.profile.url_profile.ensure_length(static_cast<DDS::Long>(profilePathsIn.size()),
			static_cast<DDS::Long>(profilePathsIn.size()));

	// Copy paths
	for(size_t i = 0; i < profilePathsIn.size(); i++){
		factoryQos.profile.url_profile[i] = DDS::String_dup(profilePathsIn[i].c_str());
	}

	// Set the new qis
	factory->set_qos(factoryQos);
}
