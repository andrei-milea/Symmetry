#ifndef _WEBPAGE_H
#define _WEBPAGE_H 


#include <QtCore/QDebug>
#include <QWebPage>
#include <iostream>

class WebPage : public QWebPage
{
	Q_OBJECT

	public:

	WebPage(QObject* parent = 0) : QWebPage(parent) {}  

	virtual bool extension(Extension extension, const ExtensionOption* option = 0, 
							ExtensionReturn* output = 0)
	{
		if (extension != QWebPage::ErrorPageExtension)
			return false;

		ErrorPageExtensionOption *errorOption = (ErrorPageExtensionOption*) option;
		std::cout << "Error loading " << qPrintable(errorOption->url.toString())  << std::endl;
		if(errorOption->domain == QWebPage::QtNetwork)
			std::cout << "Network error (" << errorOption->error << "): ";
		else if(errorOption->domain == QWebPage::Http)
			std::cout << "HTTP error (" << errorOption->error << "): ";
		else if(errorOption->domain == QWebPage::WebKit)
			std::cout << "WebKit error (" << errorOption->error << "): ";

		std::cout << qPrintable(errorOption->errorString) << std::endl;

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

#endif

