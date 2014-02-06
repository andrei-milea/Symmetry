#ifndef _WEBPAGE_H
#define _WEBPAGE_H 

#include "../logger.h"

#include <QtCore/QDebug>
#include <QWebPage>

namespace engine
{

class WebPage : public QWebPage
{
	Q_OBJECT

	public:

	WebPage(QObject* parent = 0) 
		: QWebPage(parent)
   	{}  

	virtual bool extension(Extension extension, const ExtensionOption* option = 0, 
							ExtensionReturn* output = 0)
	{

		if (extension != QWebPage::ErrorPageExtension)
			return false;


		ErrorPageExtensionOption *errorOption = (ErrorPageExtensionOption*) option;
		cLogger::getInstance().print(std::string("Error loading ") + qPrintable(errorOption->url.toString()));
		if(errorOption->domain == QWebPage::QtNetwork)
			cLogger::getInstance().print("Network error ");
		else if(errorOption->domain == QWebPage::Http)
			cLogger::getInstance().print("HTTP error ");
		else if(errorOption->domain == QWebPage::WebKit)
			cLogger::getInstance().print("WebKit error ");

		cLogger::getInstance().print(qPrintable(errorOption->errorString));

		return false;
	}

	virtual bool supportsExtension(Extension extension)const
	{
		if (extension == QWebPage::ErrorPageExtension)
		{
			return true;
		}
		return false;
	}  
};

}

#endif

