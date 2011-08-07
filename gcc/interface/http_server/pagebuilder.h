#ifndef _PAGEBULDER_H
#define _PAGEBULDER_H
#include <string>

#include <boost/lexical_cast.hpp>

namespace http_server
{

#define ID_POS 1
#define ID_SIZE 1

//macro for inserting HTML directly in C++
#define HTML(...) #__VA_ARGS__

class cPageBuilder
{

public:

	static cPageBuilder* GetInstance()
	{
		if(NULL == s_Instance)
			return new cPageBuilder;
		return s_Instance;
	};

   	std::string& GetIndexPage(const unsigned int session_id)
	{
		return m_Index_page.replace(ID_POS, ID_SIZE, boost::lexical_cast<std::string>(session_id));
	};

	const std::string GetWebglConstent(const std::string &webglcontent)const
	{
		return webglcontent;
	};

	const std::string GetPage(const cResult &result, const unsigned int ses_id)
	{
		//TODO
		return "";
	};

	const std::string GetLoadingPage(const unsigned int estimation, const unsigned int ses_id)
	{
		//TODO
		return "";
	};

	const std::string GetPlainContent(const std::string& planecontent)const
	{
		return planecontent;
	};

protected:
	cPageBuilder()
	{}; 
	cPageBuilder(const cPageBuilder &page_bld)
	{};

	static cPageBuilder *s_Instance;

private:
	//html or java script strings
	std::string m_Index_page;
	std::string m_Webgl_content;
	std::string m_Hidden_form;

};

cPageBuilder *cPageBuilder::s_Instance = NULL;

}

#endif


