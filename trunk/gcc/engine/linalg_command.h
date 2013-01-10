#ifndef _LINALG_COMMAND_H
#define _LINALG_COMMAND_H

#include "command.h"

#include <boost/numeric/ublas/matrix.hpp>

namespace engine
{

class cLinAlgCommand : public cCommand
{
public:
	cLinAlgCommand()
	{
	};
	virtual ~cLinAlgCommand()	{};

	const boost::numeric::ublas::matrix<double>& GetResult()const
	{
		return m_MatrixResult;
	};

protected:
	boost::numeric::ublas::matrix<double> m_MatrixResult;
};

}

#endif

