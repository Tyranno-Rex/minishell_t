#ifndef SIGNAL_H
# define SIGNAL_H

void	    init_rl_catch_signals(void);
void        sig_handler(int signal);
void        setting_signal();
int	        wtermsig(int status);
int	        wexitstatus(int status);
int	        wifsignaled(int status);
void	    reset_signal(pid_t pid, int here_flag);

#endif