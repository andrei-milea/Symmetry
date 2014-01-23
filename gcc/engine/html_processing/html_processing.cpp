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
#include <iostream>
#include <cassert>

	
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
		m_WebPage.setViewportSize(m_WebPage.mainFrame()->contentsSize());
		QWebElement slide_div = m_WebPage.mainFrame()->findFirstElement("div#slide_id_1");
		QRect geom = slide_div.geometry();
		QImage img(geom.width(), geom.height(), QImage::Format_RGB32);
		QPainter painter(&img);
		slide_div.render(&painter);
		painter.end();
		img = img.scaledToHeight(128);
		QByteArray ba;
		QBuffer buffer(&ba);
		buffer.open(QIODevice::WriteOnly);
		if(false == img.save(&buffer, "JPEG", 30))
			std::cout << "saving image failed";
		QByteArray base64data = buffer.buffer().toBase64();
		m_ResultStr = std::string(base64data.data(), (size_t)buffer.buffer().size());

		QString img_path = "/root/projects/symmetry/absalg/gcc/interface/presentations/pres.jpg";
		if(false == img.save(img_path, "JPEG", 100))
			std::cout << "saving image failed";
	}
	else
	{
		std::cout << "Error processing html";
	}

	emit finished();
}

void HtmlProc::renderImgs(bool ok)
{
	if(ok)
	{
		QWebElementCollection slide_divs = m_WebPage.mainFrame()->findAllElements("*.slide_div");
		m_WebPage.setViewportSize(m_WebPage.mainFrame()->contentsSize());
		for(QWebElementCollection::iterator it = slide_divs.begin(); it != slide_divs.end(); it++)
		{
			QRect geom = (*it).geometry();
			QImage img(geom.width(), geom.height(), QImage::Format_ARGB32);
			QPainter painter(&img);
			(*it).render(&painter);
			painter.end();
//			QString img_path = "/root/projects/symmetry/absalg/gcc/interface/presentations/pres.jpg";
//			if(false == img.save(img_path, "JPEG", 100))
//				std::cout << "saving image failed";
		}
	}
	else
	{
		std::cout << "Error processing html";
	}

	emit finished();
}

void HtmlProc::renderPDF(bool ok)
{
	if(ok)
	{
		QPrinter printer(QPrinter::HighResolution);
		printer.setOutputFormat(QPrinter::PdfFormat);
		QString pdf_path = "/root/projects/symmetry/absalg/gcc/interface/presentations/pres.pdf";
		printer.setOutputFileName(pdf_path);

		m_WebPage.mainFrame()->print(&printer);
	}
	else
	{
		std::cout << "Error processing html";
	}

	emit finished();
}



