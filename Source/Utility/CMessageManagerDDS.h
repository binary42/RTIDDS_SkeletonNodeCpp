#pragma once

#include "Utility.h"
#include <ndds/ndds_cpp.h>
#include <ndds/ndds_namespace_cpp.h>

// TODO - Add DDS message support types here.

class CMessageManagerDDS{
public:
	// Attributes
	// TODO - Add reader and writer type objects here.

	// Methods
	CMessagemanager();
	virtual ~CMessageManager();

private:
	// Attributes
	DDS::DomainParticipant *_pParticipant;

	void LoadXMLProfiles();
	void SetupFactoryProfiles(const std::vector<std::string> &profilePathIn);
};
