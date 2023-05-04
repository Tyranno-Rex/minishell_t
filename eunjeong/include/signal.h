#ifndef SIGNAL_H
# define SIGNAL_H

void	init_rl_catch_signals(void);
void    sig_handler(int signal);
void    setting_signal();

#endif