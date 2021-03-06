#ifndef _GROUP_FACTORY
#define _GROUP_FACTORY

#include <utility>
#include <algorithm>
#include <boost/thread.hpp>

#include "../lib/group.h"
#include "../lib/cayley_graph.h"


/*!
 singleton class used to facilitate creation of groups
 contains a pool of groups for optimization
*/
class cGroupFactory
{
public://methods
	static cGroupFactory& GetInstance();

	SymmGrp* GetSymmGrp(SymmGrpElem &generators);
	void ReleaseSymmGrp(SymmGrp *group);
	void CleanUp();


private://methods
	cGroupFactory()
	{};
	cGroupFactory(const cGroupFactory& grpfact)
	{};
	cGroupFactory& operator=(cGroupFactory& grpfact)
	{
		return *this;
	};

private://members
	static boost::mutex s_Mutex;
	std::vector< std::pair<SymmGrp*, bool> *> m_SymmGrps;

private://static member
	static cGroupFactory* s_Instance;
};




#endif


