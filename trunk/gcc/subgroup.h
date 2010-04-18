#ifndef _SUBGROUP_H
#define _SUBGROUP_H

template<typename G>
class cSubGroup : public G
{
	BOOL isNormal()const;
};

#endif
