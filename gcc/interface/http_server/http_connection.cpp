
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
        if(false == _request.ParseRequest())
		{
			std::string request_str;
			is>>request_str;
			throw std::runtime_error(CONTEXT_STR + "failed to parse request :" + request_str);
		}
        switch(_request.GetMethod())
        {
        case GET_M:
            if(_request.GetResource() == "/")
            {
				//add new session
				unsigned int ses_id = cHttpConnection::GetRandUniqueId();
				cSession session(ses_id);
				s_Sessions.push_back(session);

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
				if(s_Sessions.find(ses_id) != s_Sessions::end())
				{
					if(s_Sessions[ses_id].GetState() == STATE_FREE)
					{
						cCommand *command = new cCommand(_request.GetCommand(), s_Sessions[ses_id].GetResult());
						int runtime_estimation = command.EstimateRunTime(s_Estimator);

						if( runtime_estimation <= 360/*seconds*/)
						{
							s_Sessions[ses_id].RunCommand(command);
							response.BuildResponse(OK, cPageBuilder::GetInstance().GetPage(Result, ses_id));
						}
						else
						{
							s_Sessions[ses_id].ScheduleCommand(command);
							response.BuildResponse(OK, cPageBuilder::GetInstance().GetLoadingPage(runtime_estimation, ses_id));
						}
					}
					else if(s_Sessions[ses_id].GetState() == STATE_RESULT_PENDING)
					{
						response.BuildResponse(OK, cPageBuilder::GetInstance().GetPage(Result, ses_id));
					}
					else if(s_Sessions[ses_id].GetState() == STATE_RESULT_PENDING)
					{

						response.BuildResponse(OK, cPageBuilder::GetInstance().GetReLoadingPage(runtime_estimation, ses_id));
					}

					boost::asio::async_write(m_Socket, m_ResponseBuf,
						boost::bind(&cHttpConnection::HandleWriteResponse, shared_from_this(),
						boost::asio::placeholders::error));
				}
				else
				{
					//add new session
					cSession session(ses_id);
					s_Sessions.push_back(session);

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
		throw std::runtime_error(CONTEXT_STR + error.message());
    }
};

void cHttpConnection::HandleWriteResponse(const boost::system::error_code& error)
{
    if(error)
    {
		throw std::runtime_error(CONTEXT_STR + error.message());
    }
};
