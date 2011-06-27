#include "session.h"


cSession::cSession()
	:m_SessionId(0),
	m_State(0)
{};

cSession::cSession(unsigned int ses_id)
	:m_SessionId(ses_id),
	m_State(0)
{};

cSession::~cSession
{};

const string cSession::RunCommand()
{
	
};



