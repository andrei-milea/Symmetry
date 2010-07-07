#ifndef _SUBGROUP_H
#define _SUBGROUP_H

template<typename G>
class cSubgroup : public G
{
public:
	cSubgroup()
		:m_isNormal(false)
	{
	};

	cSubgroup(std::vector<typename G::ElementType> &gr_vec)
		:G(gr_vec),
		m_isNormal(false)
	{};

	~cSubgroup()
	{};

	bool isNormal()const;
	void isNormal(const bool normal)
	{
		m_isNormal = normal;
	};

private:
	bool m_isNormal;
};

#endif
