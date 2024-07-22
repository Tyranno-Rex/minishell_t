#include "../../include/minishell.h"

// 시그널 처리 함수들

static int	_wstatus(int status)
{
	int	return_val;

	return_val = status & 0177;
	return (return_val);
}

int	wifsignaled(int status)
{
	int	return_val;

	return_val = ((_wstatus(status) != 0177) && (_wstatus(status) != 0));
	return (return_val);
}

int	wtermsig(int status)
{
	int	return_val;

	return_val = _wstatus(status);
	return (return_val);
}

int	wexitstatus(int status)
{
	int	return_val;

	return_val = ((unsigned)status >> 8) & 0xff;
	return (return_val);
}