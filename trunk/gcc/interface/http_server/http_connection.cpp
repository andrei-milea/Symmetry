
#include "http_connection.h"
#include <iostream>
#include <boost/bind.hpp>

#include "http_request.h"
#include "http_response.h"


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
                cResponse response(m_ResponseBuf);
                response.BuildResponse(OK, "<html>test</html>");

                boost::asio::async_write(m_Socket, m_ResponseBuf,
                    boost::bind(&cHttpConnection::HandleWriteResponse, shared_from_this(),
                    boost::asio::placeholders::error));
                
            }
			else
			{
				_request.GetSessionId();
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
