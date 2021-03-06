#ifndef _GROUP_GEN_PARSER_H
#define _GROUP_GEN_PARSER_H

#include "command.h"
#include "group_factory.h"
#include "logger.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/any.hpp>
#include <exception>

namespace engine
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

enum GROUP_TYPE
{
    NONE = 0,
    SYMMETRIC_GROUP,
	CYCLIC_GROUP,
	DIHEDRAL_GROUP
};

/*!
  param parser for commands based on generation of group elements from a set of generators
  implements the parsing of generators using BOOST SPIRIT
*/

class cParamGrpGenParser
{
public:
	GROUP_TYPE GetGroupType()const
	{
		return m_GroupType;
	};

	const std::vector<boost::any>& GetGenerators()const
	{
		return m_Generators;
	};

	cParamGrpGenParser(const std::string &params)
		 :m_GroupType(NONE),
		  m_Params(params)
	{
	};

	void ParseParams()
	{
		using qi::uint_;
		using qi::_1;
		using qi::string;
		using phoenix::push_back;
		using phoenix::ref;
		using ascii::char_;

		unsigned int grp_type = 0;
		std::vector<std::size_t> Gen_vec;
		AddGrpGen add_grp_gen(&Gen_vec, &m_Generators);

		std::string::iterator iter = m_Params.begin();
		bool result = qi::parse(iter, m_Params.end(),
		                        /////////gramar
		                        (
		                            group_type[ref(grp_type) = _1] >>
		                            *(char_('(')
		                              >> uint_[push_back(phoenix::ref(Gen_vec), _1)] % ','
		                              >> char_(')') [add_grp_gen])
		                        )
		                        /////////
		                       );
		m_GroupType = static_cast<GROUP_TYPE>(grp_type);
		assert(iter == m_Params.end());
		if(m_Generators.empty() || false == result)
		{
			throw std::runtime_error(CONTEXT_STR + " Invalid (or missing) command parameters");
		}
	};

private:
	class AddGrpGen
	{
	public:
		AddGrpGen(std::vector<std::size_t> *gen_vec, std::vector<boost::any> *generators)
			:m_Gen_vec(gen_vec),
			 m_Generators(generators)	{};

		void operator()(char const& i, qi::unused_type, qi::unused_type)const
		{
			cPermElem perm_el(*m_Gen_vec);
			SymmGrpElem grp_elem(perm_el);
			m_Generators->push_back(grp_elem);
			m_Gen_vec->clear();
		};

	private:
		mutable std::vector<std::size_t> *m_Gen_vec;
		mutable std::vector<boost::any>  *m_Generators;
	};

protected:
	GROUP_TYPE m_GroupType;
	std::vector<boost::any>  m_Generators;
	std::string m_Params;

protected:

	/************************************************************/
	/****************GroupGen command PARSER TOOLS***************/
	/************************************************************/

	/***********group gen command GRAMMAR RULES************/
//COMMAND_TYPE = GET_ELEMENTS | GET_NORMALIZER | GET_CENTER | GET_CENTRALIZER
//GENi = { > uint_ >> *("," > int_) }
//GENERATORS = *GENi
//COMMAND = COMMAND_TYPE >> GROUP_TYPE >> (GENERATORS);


//group type parsing symbol tables
	struct group_type_: qi::symbols<char, GROUP_TYPE>
	{
		group_type_()
		{
			add
			("SYMMETRIC_GROUP", SYMMETRIC_GROUP)
			("CYCLIC_GROUP", CYCLIC_GROUP)
			("DIHEDRAL_GROUP", DIHEDRAL_GROUP);

		}
	} group_type;
};

}


#endif

