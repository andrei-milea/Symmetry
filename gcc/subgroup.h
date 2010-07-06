#ifndef _SUBGROUP_H
#define _SUBGROUP_H

template<typename G>
class cSubgroup : public G
{
public:
	cSubgroup()
	{
	};
	~cSubgroup()
	{};

	BOOL isNormal()const;
};

#endif
