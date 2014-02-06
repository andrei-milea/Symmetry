#ifndef _PAGEBULDER_H
#define _PAGEBULDER_H

#include <string>

#include <boost/lexical_cast.hpp>
#include <fstream>
#include <sstream>
#include <map>

namespace http_server
{

/*!
  builds the html pages and the html content served to the browser -- singleton
*/
class cPageBuilder
{

public:

	static cPageBuilder* GetInstance();


	void SetPaths(const std::string& web_pages_path, const std::string& presentations_path);

	const std::string& GetWebPagesPath()const	{	return m_WebPagesPath;	}

	const std::string& GetPresPath()const	{	return m_PresentationsPath;	}

	const std::string& GetResError()const	{	return m_ResError;	}

	const std::string& GetIndexPage(const std::size_t session_id);

	const std::string& GetPresPage(const std::size_t session_id);

	const std::string& GetPageResource(const std::string& resource)const;

	const std::string GetLoadingPage(const std::size_t estimation, const std::size_t ses_id)const;

	const std::string& GetPlainContent(const std::string& planecontent)const;

	void LoadWebPages(const std::string& path);

protected:
	cPageBuilder();

	cPageBuilder(const cPageBuilder &page_bld)=delete;
	cPageBuilder(const cPageBuilder &&page_bld)=delete;
	cPageBuilder& operator=(const cPageBuilder &page_bld)=delete;
	cPageBuilder& operator=(const cPageBuilder &&page_bld)=delete;

private:
	static cPageBuilder *s_Instance;
	std::map<std::string, std::string> m_Resources;
	std::string m_ResError;
	std::string m_WebPagesPath;
	std::string m_PresentationsPath;
};


}//namespace http_server

#endif


