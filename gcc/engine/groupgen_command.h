#ifndef _GROUPGEN_COMMAND_H
#define _GROUPGEN_COMMAND_H

#include "command.h"
#include "group_factory.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/any.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

enum GROUP_TYPE
{
	NONE = 0,
	SYMMETRIC_GROUP,
	D8
};

class cGroupGenCommand : public cCommand
{
public:
	virtual ~cGroupGenCommand()
	{};
	virtual std::string Execute()
	{
		return "";
	};

protected:
	cGroupGenCommand(std::string &params)
		:cCommand(params),
		m_GroupType(NONE)
	{};

	virtual bool ParseParams()
	{
		using qi::uint_;
        using qi::_1;
		using qi::string;
        using phoenix::push_back;
		using phoenix::ref;
		using ascii::char_;

//					 >> char_('}') 
//					 [boost::bind(&cGroupGenCommand::AddSymmGrpGen, this, gen_vec)]

		std::vector<unsigned int> gen_vec;
		unsigned int grp_type = 0;
		bool result = qi::parse(m_Params.begin(), m_Params.end(), 
					/////////gramar
					( 
					 uint_[ref(grp_type) = _1]
					 >> char_(' ') >> char_('{')
					 //>> uint_[push_back(phoenix::ref(gen_vec), _1)] % ',')
					)
					/////////
				);
//		m_GroupType = grp_type;
		return result;
	};

	virtual unsigned int EstimateRunTime(const cEstimator &estimator)const
	{
		return 1;
	};

private:
	void AddSymmGrpGen(std::vector<unsigned int> &generator)
	{
		cPermElem perm_el(generator);
		cGroupElem< cPermElem, Multiplication> grp_elem();
		//m_Generators.push_back(grp_elem);
		generator.clear();
	};

private:
	GROUP_TYPE m_GroupType;
	std::vector<boost::any>  m_Generators;

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
            ("D8", D8);

    }
}group_type;


                /************************************************************/
                /************************************************************/
};



#endif

