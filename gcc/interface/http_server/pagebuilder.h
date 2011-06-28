#ifndef _PAGEBULDER_H
#define _PAGEBULDER_H
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>


#define ID_POS
#define ID_SIZE

class cPageBuilder
{

public:
	static cPageBuilder& GetInstance()
	{
		if(NULL == s_Instance)
		{
		  	boost::mutex::scoped_lock lock(m_Mutex);
			if(NULL == s_Instance)	
				s_Instance = new cPageBuilder;
		}
		return (*cPageBuilder);
	};

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
	cPageBuilder()
	{};
	cPageBuilder(const cPageBuilder& bld)
	{};
	cPageBuilder& operator=(cPageBuilder& bld)
	{};
private:
	static cPageBuilder *s_Instance;
	interprocess_mutex m_Mutex;
	
	//html or java script strings
	std::string m_Index_page = 
	const std::string m_Webgl_content = 
	const std::string m_Hidden_form = 

};

cPageBuilder::s_Instance = NULL;

#endif


