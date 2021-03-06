
#include "html_processing_inc.h"
#include "html_processing.h"

#include <QTimer>
#include <QApplication>

namespace engine
{

cHtmlProcApp* cHtmlProcApp::sInst = NULL;

cHtmlProcApp *cHtmlProcApp::GetInstance()
{
	//TODO make it thread safe
	if(cHtmlProcApp::sInst == NULL)
		cHtmlProcApp::sInst = new cHtmlProcApp;
	return cHtmlProcApp::sInst;
}

cHtmlProcApp::cHtmlProcApp()
	:m_App(NULL)
{
	char *argv[] = {const_cast<char *>("program name"), const_cast<char *>("arg"), NULL};
	int argc = sizeof(argv) / sizeof(char*) - 1;
	m_App = new QApplication(argc, argv);
}

cHtmlProcApp::~cHtmlProcApp()
{
	if(m_App != NULL)
		delete m_App;
}


std::string cHtmlProcApp::html_encode(const std::string &html)const
{
	QString encoded;
	for(size_t idx = 0; idx < html.size(); ++idx)
	{
		char ch = html.at(idx);
		if((unsigned short)ch > 255)
		{
			short val = (short)ch;
			encoded += QString("&#%1;").arg((unsigned char)val);
		}
		else
			encoded += ch;
	}
	return encoded.toStdString();
}

std::string cHtmlProcApp::html_to_img(const std::string &html, const std::string &base_url)
{
	HtmlProc html_proc(m_App, html, base_url, IMG);
	QObject::connect(&html_proc, SIGNAL(finished()), m_App, SLOT(quit()));
	QTimer::singleShot(0, &html_proc, SLOT(run()));
	m_App->exec();
	return html_proc.getResultStr();
}

std::vector<std::string> cHtmlProcApp::html_to_imgs(const std::string &html, const std::string &base_url)
{
	HtmlProc html_proc(m_App, html, base_url, IMGS);
	QObject::connect(&html_proc, SIGNAL(finished()), m_App, SLOT(quit()));
	QTimer::singleShot(0, &html_proc, SLOT(run()));
	m_App->exec();
	return html_proc.getResultVec();
}

std::string cHtmlProcApp::html_to_pdf(const std::string &html, const std::string &base_url)
{
	HtmlProc html_proc(m_App, html, base_url, PDF);
	QObject::connect(&html_proc, SIGNAL(finished()), m_App, SLOT(quit()));
	QTimer::singleShot(0, &html_proc, SLOT(run()));
	m_App->exec();
	return html_proc.getResultStr();
}

}

