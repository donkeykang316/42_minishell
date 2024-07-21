#include "pipe_test.h"

void	sigint_handler_child(int num);
void	sigint_handler_parent(int num);
void	sigquit_handler(int num);
void	set_signals_parent(void);
void	set_signals_child(void);

void	sigint_handler_child(int num)
{
	(void)num;
}

void	sigint_handler_parent(int num)
{
	(void)num;
    set_signals_child();
    exit(0);
}

void	sigquit_handler(int num)
{
	(void)num;
}

void	set_signals_parent(void)
{
	signal(SIGINT, sigint_handler_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_child(void)
{
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigint_handler_child);
}

int main()
{
    while (1)
    {
        set_signals_parent();
        printf("parent\n");
        sleep(1);
    }
    while (1)
    {
        set_signals_child();
        printf("child\n");
        sleep(1);
    }
}