#ifndef _PAGEBULDER_H
#define _PAGEBULDER_H
#include <string>

#include <boost/lexical_cast.hpp>

#define ID_POS
#define ID_SIZE

class cPageBuilder
{

public:
   cPageBuilder()
	{}; 
   
	std::string& GetIndexPage(const unsigned int session_id)
	{
		return m_Index_page.replace(ID_POS, ID_SIZE, boost::lexical_cast<string> session_id);
	};

	const std::string GetWebglConstent(const string &webglcontent)const
	{
		return webglcontent;
	};


	const std::string GetPlainContent(const string& planecontent)const
	{
		return planecontent;
	};
  
private:
	//html or java script strings
	std::string m_Index_page = 
	const std::string m_Webgl_content = 
	const std::string m_Hidden_form = 

};

#endif


