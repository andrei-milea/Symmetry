#ifndef _PAGEBULDER_H
#define _PAGEBULDER_H
#include <string>

#include <boost/lexical_cast.hpp>
#include <fstream>
#include <sstream>
#include <map>


namespace engine
{
class cResult;
}

namespace http_server
{

class cPageBuilder
{

public:

	static cPageBuilder* GetInstance();

	static std::string ResError;

	const std::string& GetIndexPage(const unsigned int session_id);

	const std::string& GetPageResource(const std::string& resource)const;

	const std::string GetPage(const engine::cResult &result, const unsigned int ses_id)const;

	const std::string GetLoadingPage(const unsigned int estimation, const unsigned int ses_id)const;

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


