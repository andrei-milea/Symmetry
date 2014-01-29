#ifndef _HTML_PROCESSING_H
#define _HTML_PROCESSING_H 

#include "webpage.h"
#include <string>
#include <vector>

namespace engine
{

#define IMG 1
#define IMGS 2 
#define PDF 3 

class HtmlProc : public QObject
{
	Q_OBJECT

public:
	HtmlProc(QObject *parent, const std::string& html, const std::string &base_url, int option);
	const std::string &getResultStr()const
	{
		return m_ResultStr;
	}
	const std::vector<std::string> &getResultVec()const
	{
		return m_ResultVec;
	}

public slots:
	void run();

private slots:
	void renderImgs(bool ok);
	void renderImg(bool ok);
	void renderPDF(bool ok);

private:
	WebPage m_WebPage;
	std::string m_HTML;
	std::string m_BaseUrl;
	std::string m_ResultStr;
	std::vector<std::string> m_ResultVec;
	int m_Option;

signals:
	void finished();
};

}

#endif

