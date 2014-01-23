
#ifndef _HTML_PROCESSING_INC_H
#define _HTML_PROCESSING_INC_H 

#include <string>
#include <vector>

class QApplication;

class cHtmlProcApp
{
public:
	static cHtmlProcApp *GetInstance();
	std::string html_to_img(const std::string &html, const std::string &base_url);
	std::vector<std::string> html_to_imgs(const std::string &html, const std::string &base_url);
	std::string html_to_pdf(const std::string &html, const std::string &base_url);
	

private:
	cHtmlProcApp();
	cHtmlProcApp(const cHtmlProcApp&);
	const cHtmlProcApp &operator=(const cHtmlProcApp&);

private:
	static cHtmlProcApp *sInst;
	QApplication *m_App;
};

#endif
