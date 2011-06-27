
#include "http_connection.h"
#include "http_request.h"
#include "http_response.h"
#include "html_js_parts.h"
#include "../../engine/session.h"

#include <iostream>
#include <boost/bind.hpp>

void cHttpConnection::HandleClient()
{
    //read
    boost::asio::async_read_until(m_Socket, m_RequestBuf, "\r\n",
        boost::bind(&cHttpConnection::HandleRequest, shared_from_this(),
			boost::asio::placeholders::error));
};


void cHttpConnection::HandleRequest(const boost::system::error_code& error)
{
    if(!error)
    {
        std::istream is(&m_RequestBuf);
        cRequest _request(is);
        _request.ParseRequest();
        switch(_request.GetMethod())
        {
        case GET_M:
            if(_request.GetResource() == "/")
            {
				//add new session
				unsigned int ses_id = cHttpConnection::GetRandUniqueId();
				cSession session(ses_id);
				m_Sessions.push_back(session);

				//send response
                cResponse response(m_ResponseBuf);
				const std::string index_page = cPageBuilder::GetInstance().GetIndexPage(ses_id);
                response.BuildResponse(OK, index_page);

                boost::asio::async_write(m_Socket, m_ResponseBuf,
                    boost::bind(&cHttpConnection::HandleWriteResponse, shared_from_this(),
                    boost::asio::placeholders::error));
            }
			else
			{
                cResponse response(m_ResponseBuf);
				unsigned int ses_id = _request.GetSessionId()
				if(m_Sessions.find(ses_id) != m_Sessions::end())
				{
					const std::string res = m_Sessions[ses_id].Execute(_request.GetCommand());
					response.BuildResponse(OK, cPageBuilder::GetInstance().GetPage(res, ses_id));
				}
				else
				{
					//add new session
					cSession session(ses_id);
					m_Sessions.push_back(session);

					const std::string index_page  = cPageBuilder::GetInstance().GetIndexPage(
						ses_id);
                	response.BuildResponse(OK, index_page);
				}
				boost::asio::async_write(m_Socket, m_ResponseBuf,
               		boost::bind(&cHttpConnection::HandleWriteResponse, shared_from_this(),
                   	boost::asio::placeholders::error));
			}
            break;
        case POST_M:
            break;
        case HEAD_M:
            break;
        case PUT_M:
            break;
        case OPTIONS_M:
            break;
        case DELETE_M:
            break;
        case TRACE_M:
            break;
        case CONNECT_M:
            break;
        default:
            break;

        }
    }
    else
    {
        std::cout<<"error : "<<error<<"\n";
    }
};

void cHttpConnection::HandleWriteResponse(const boost::system::error_code& error)
{
    if(error)
    {
        std::cout<<"error : "<<error<<"\n";
    }
};
