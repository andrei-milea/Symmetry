#ifndef _SUBGROUP_H
#define _SUBGROUP_H

template<typename G>
class cSubgroup : public G
{
public:
	typedef typename G::ElementType ElemType;
	cSubgroup()
		:m_isNormal(false)
	{
	};

	cSubgroup(std::vector<ElemType> gr_vec)
		:G(gr_vec),
		m_isNormal(false)
	{};

	cSubgroup(G &group)
		:G(group),
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
