#ifndef _PAGEBULDER_H
#define _PAGEBULDER_H

#include <string>

#include <boost/lexical_cast.hpp>
#include <fstream>
#include <sstream>
#include <map>

namespace engine
{
	class cCommand;
};

namespace http_server
{

/*!
  builds the html pages and the html content server to the browser
*/
class cPageBuilder
{

public:

	static cPageBuilder* GetInstance();

	static std::string ResError;

	const std::string& GetIndexPage(const std::size_t session_id);

	const std::string& GetPageResource(const std::string& resource)const;

	const std::string GetPage(boost::shared_ptr<engine::cCommand> pCommand, const std::size_t ses_id)const;

	const std::string GetLoadingPage(const std::size_t estimation, const std::size_t ses_id)const;

	const std::string GetPlainContent(const std::string& planecontent)const;

protected:
	cPageBuilder();
	cPageBuilder(const cPageBuilder &page_bld)
	{};

private:
	static cPageBuilder *s_Instance;
	std::size_t m_IdPosition;
	std::size_t m_IdSize;
	std::map<std::string, std::string> m_Resources;
};


}

#endif


