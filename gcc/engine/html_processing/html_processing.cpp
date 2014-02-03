#include "html_processing.h"

#include <QWebFrame>
#include <QFile>
#include <QPrinter>
#include <QPainter>
#include <QImage>
#include <QWebElement>
#include <QWebElementCollection>
#include <QBuffer>
#include <QByteArray>
#include <QTextDocument>
#include <QTextCursor>


namespace engine
{
	
HtmlProc::HtmlProc(QObject *parent, const std::string& html, const std::string &base_url, int option)
	:QObject(parent),
	m_HTML(html),
	m_BaseUrl(base_url),
	m_Option(option)
{}


void HtmlProc::run()
{
		if(IMG == m_Option)
			connect(&m_WebPage, SIGNAL(loadFinished(bool)), this, SLOT(renderImg(bool)));
		else if(IMGS == m_Option)
			connect(&m_WebPage, SIGNAL(loadFinished(bool)), this, SLOT(renderImgs(bool)));
		else if(PDF == m_Option)
			connect(&m_WebPage, SIGNAL(loadFinished(bool)), this, SLOT(renderPDF(bool)));
		else
			assert(false);
		m_WebPage.mainFrame()->setHtml(QString::fromStdString(m_HTML), QUrl::fromLocalFile(QString::fromStdString(m_BaseUrl + "/")));
}

void HtmlProc::renderImg(bool ok)
{
	if(ok)
	{
		m_WebPage.mainFrame()->evaluateJavaScript("makeVisible()");
		m_WebPage.setViewportSize(m_WebPage.mainFrame()->contentsSize());
		QWebElement slide_div = m_WebPage.mainFrame()->findFirstElement("div#slide_id_1");
		slide_div.setStyleProperty("display", "block");
		QRect geom = slide_div.geometry();
		QImage img(geom.width(), geom.height(), QImage::Format_ARGB32);
		QPainter painter(&img);
		slide_div.render(&painter);
		painter.end();
		img = img.scaledToHeight(180, Qt::SmoothTransformation);
		QByteArray ba;
		QBuffer buffer(&ba);
		buffer.open(QIODevice::WriteOnly);
		if(false == img.save(&buffer, "PNG", 100))
		{
			cLogger Log(LOG_SEV_ERROR);
			Log << CONTEXT_STR + "saving image failed";
			emit finished();
			return;
		}
		QByteArray base64data = buffer.buffer().toBase64();
		size_t buffer_size = base64data.size();
		m_ResultStr = std::string(base64data.data(), buffer_size);
	}
	else
	{
		cLogger Log(LOG_SEV_ERROR);
		Log << CONTEXT_STR + "failed to load html";
	}

	emit finished();
}

void HtmlProc::renderImgs(bool ok)
{
	if(ok)
	{
		m_WebPage.mainFrame()->evaluateJavaScript("makeVisible()");
		m_WebPage.setViewportSize(m_WebPage.mainFrame()->contentsSize());
		QWebElementCollection slide_divs = m_WebPage.mainFrame()->findAllElements("*.slide_div");
		for(QWebElementCollection::iterator it = slide_divs.begin(); it != slide_divs.end(); it++)
		{
			//(*it).setStyleProperty("display", "block");
			QRect geom = (*it).geometry();
			QImage img(geom.width(), geom.height(), QImage::Format_ARGB32);
			QPainter painter(&img);
			(*it).render(&painter);
			painter.end();

			//img = img.scaled(512, 512, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			//img = img.scaledToHeight(512, Qt::SmoothTransformation);
			QByteArray ba;
			QBuffer buffer(&ba);
			buffer.open(QIODevice::WriteOnly);
			if(false == img.save(&buffer, "PNG", 100))
			{
				cLogger Log(LOG_SEV_ERROR);
				Log << CONTEXT_STR + "saving image failed";
				break;
			}
			QByteArray base64data = buffer.buffer().toBase64();
			size_t buffer_size = base64data.size();
			std::string slide_str(base64data.data(), buffer_size);
			m_ResultVec.push_back(slide_str);
		}
	}
	else
	{

		cLogger Log(LOG_SEV_ERROR);
		Log << CONTEXT_STR + "failed to load html";
	}

	emit finished();
}

void HtmlProc::renderPDF(bool ok)
{
	if(ok)
	{
		m_WebPage.setViewportSize(m_WebPage.mainFrame()->contentsSize());
		m_WebPage.mainFrame()->evaluateJavaScript("makeVisible()");
		QPrinter printer(QPrinter::HighResolution);
		//printer.setPageMargins(0.1, 0.1, 0.1, 0.1, QPrinter::Inch);
		printer.setPaperSize(QSizeF(7.5, 5.5), QPrinter::Inch);
		printer.setOutputFormat(QPrinter::PdfFormat);
		QString pdf_path = "/root/projects/symmetry/absalg/gcc/interface/presentations/pres.pdf";
		printer.setOutputFileName(pdf_path);
		m_WebPage.mainFrame()->print(&printer);
		QFile file(pdf_path);
		if(!file.open(QIODevice::ReadOnly))
		{
			cLogger Log(LOG_SEV_ERROR);
			Log << CONTEXT_STR + "failed to open pdf file";
			emit finished();
			return;
		}
		QByteArray blob = file.readAll().toBase64();
		m_ResultStr = std::string(blob.data(), blob.size());

	}
	else
	{
		cLogger Log(LOG_SEV_ERROR);
		Log << CONTEXT_STR + "failed to load html";
	}

	emit finished();
}

}

