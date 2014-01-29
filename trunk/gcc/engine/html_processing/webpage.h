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

		cLogger Log(LOG_SEV_ERROR);

		ErrorPageExtensionOption *errorOption = (ErrorPageExtensionOption*) option;
		Log << "Error loading " << qPrintable(errorOption->url.toString());
		if(errorOption->domain == QWebPage::QtNetwork)
			Log << "Network error (" << errorOption->error << "): ";
		else if(errorOption->domain == QWebPage::Http)
			Log << "HTTP error (" << errorOption->error << "): ";
		else if(errorOption->domain == QWebPage::WebKit)
			Log << "WebKit error (" << errorOption->error << "): ";

		Log << qPrintable(errorOption->errorString);

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

