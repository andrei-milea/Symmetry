#include "group_factory.h"

namespace engine
{

cGroupFactory::s_Instance = NULL;

static cGroupFactory& cGroupFactory::GetInstance()
{
	if(NULL == s_Instance)
	{
		boost::mutex::scoped_lock lock(cGroupFactory::s_Mutex);
		if(NULL == s_Instance)
			s_Instance = new cGroupFactory;
	}
	return (*s_Instance);
}


SymmGrp* cGroupFactory::GetSymmGrp(SymmGrpGenerators &generators)
{
	boost::mutex::scoped_lock lock(cGroupFactory::s_Mutex);
	std::vector< std::pair<SymmGrp*, bool> *>::iterator it;
	for(it = m_SymmGrps.begin(); it != m_SymmGrps.end(); it++)
	{
		if(false == (*it)->second)
		{
			(*it)->first->SetGeneratorsSet(generators);
			return (*it)->first;
		}
	}

	//if no free group is found create new one and add it to the vector
	SymmGrp *symm_grp = new SymmGrp(generators);
	std::pair<SymmGrp*, bool> *grp_entry = new std::pair<SymmGrp*, bool>();
	grp_entry->first = symm_grp;
	grp_entry->second = m_SymmGrps.size() + 1;
	m_SymmGrps.push_back(grp_entry);
}



void cGroupFactory::ReleaseSymmGrp(SymmGrp *group)
{
	boost::mutex::scoped_lock lock(cGroupFactory::s_Mutex);
	std::vector< std::pair<SymmGrp*, bool> *>::iterator it;
	for(it = m_SymmGrps.begin(); it != m_SymmGrps.end(); it++)
	{
		if(group == (*it)->first)
		{
			(*it)->first->ClearGenerators();
			(*it)->second = false;
		}
	}
}

void cGroupFactory::CleanUp()
{
	boost::mutex::scoped_lock lock(cGroupFactory::s_Mutex);
	m_SymmGrps.clear();
}

}


