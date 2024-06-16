#include "../../inc/minishell.h"

extern int	exit_status;

void	less(t_parser *parser)
{
	int		fd;

	fd = 0;
	if (parser->next->token[0])
	{
		while (parser->next->operator == LESS)
		{
			if (access(parser->next->token[0], F_OK) == -1)
				less_nofile_exit();
			parser = parser->next;
		}
		while (parser->next->operator == LESS)
		{
			if (access(parser->next->token[0], F_OK) == -1)
				less_nofile_exit();
			parser = parser->next;
		}
		if (parser->next->token_count > 2
			&& parser->next->token[1])
			less_multi_file(parser, fd);
		else if (access(parser->next->token[0], F_OK) == 0)
			less_one_file(parser, fd);
		else
			less_invalid_input(parser->next->token[0]);
	}
}

void	heredoc(t_parser *parser)
{
	char	*buff;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (strcmp_ms(buff, parser->next->token[0]))
			break ;
		ft_putendl_fd(buff, fd[1]);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buff);
}

void	ft_open(char *token, int option)
{
	if (open(token, O_WRONLY | option | O_CREAT, 0666) == -1)
	{
		perror(" ");
		exit(EXIT_FAILURE);
	}
}

void	redir_output(t_parser *parser)
{
	close(STDOUT_FILENO);
	while (parser->next->operator == GREAT
		|| parser->next->operator == APPEND)
	{
		if (parser->operator == GREAT)
			ft_open(parser->next->token[0], O_TRUNC);
		else if (parser->operator == APPEND)
			ft_open(parser->next->token[0], O_APPEND);
		parser = parser->next;
		close(STDOUT_FILENO);
	}
	if (parser->operator == GREAT)
		ft_open(parser->next->token[0], O_TRUNC);
	else if (parser->operator == APPEND)
		ft_open(parser->next->token[0], O_APPEND);
}

t_parser	*pipe_check(t_parser *parser)
{
	while (parser)
	{
		if (parser->operator == PIPE)
			return (parser);
		parser = parser->next;
	}
	return (NULL);
}

bool	pipe_redir_check(t_parser *parser)
{
	t_parser	*temp;

	temp = parser;
	while (temp)
	{
		if (temp->operator != NONE)
			return (false);
		temp = temp->next;
	}
	return (true);
}

void	redir_exe(t_shell *shell, t_parser *parser)
{
	t_parser	*temp;

	temp = parser;
	if (parser->operator == LESS)
		less(parser);
	else if (parser->operator == HEREDOC)
		heredoc(parser);
	else
		redir_output(parser);
	temp->operator = NONE;
	while (parser->operator != NONE && parser->operator != PIPE)
		parser = parser->next;
	if (!pipe_redir_check(parser) && fork() == 0)
		exec_cmd(shell, temp);
	else if (parser->operator == NONE)
		exec_cmd(shell, temp);
	else
		pipe_exe(shell, parser);
}

void	test_left_side(t_parser *parser, t_shell *shell, int pipe_fd[2])
{
	close(STDOUT_FILENO);
	dup(pipe_fd[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	test_exec_cmd(shell, parser);
}

t_parser	*test_right_side(t_parser *parser, t_shell *shell, int pipe_fd[2])
{
	close(STDIN_FILENO);
	dup(pipe_fd[0]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	test_exec_cmd(shell, parser);
}

t_parser	*test_pipe_exe(t_shell *shell, t_parser *parser)
{
	pid_t	child_pid;
	int		pipe_fd[2];
	int		status;

	parser->operator = NONE;
	if (pipe(pipe_fd) == -1)
		exit_shell(shell, PIPE_ERR, EXIT_FAILURE);
	child_pid = fork();
	if (child_pid == -1)
		exit_shell(shell, FORK_ERR, EXIT_FAILURE);
	if (child_pid == 0)
		left_side(parser, shell, pipe_fd);
    parser = right_side(parser->next, shell, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(child_pid, &status, 0);
	exit_status = status / 256;
    return (parser);
}

bool	is_valid_id(char *token)
{
	size_t	i;

	i = 0;
	if (strcmp_ms(token, "="))
		return (false);
	while (token[i] && token[i] != '=')
	{
		if (ft_isdigit(token[i]) || token[i] == '!' || token[i] == '@'
			|| token[i] == '{' || token[i] == '}' || token[i] == '-')
			return (false);
		i++;
	}
	return (true);
}

bool	builtin(t_shell *shell, t_parser *parser)
{
	if (strcmp_ms(parser->token[0], "exit"))
		cmd_exit(shell, parser);
	else if (strcmp_ms(parser->token[0], "cd"))
		exit_status = cmd_cd(shell, parser);
	else if (strcmp_ms(parser->token[0], "env"))
		exit_status = cmd_env(shell);
	else if (strcmp_ms(parser->token[0], "echo"))
		exit_status = cmd_echo(parser);
	else if (strcmp_ms(parser->token[0], "pwd"))
		exit_status = cmd_pwd();
	else if (strcmp_ms(parser->token[0], "unset"))
		exit_status = cmd_unset(shell, parser);
	else if (strcmp_ms(parser->token[0], "export"))
		exit_status = cmd_export(shell, parser);
	else if (ft_strchr(parser->token[0], '=')
		&& is_valid_id(parser->token[0]))
		exit_status = save_user_vars(parser->token[0],
				&shell->envp_lst, false);
	else
		return (false);
	return (true);
}

void	find_path(t_shell *shell, t_parser *parser)
{
	char		*bin_path;
	char		**paths;

	bin_path = parser->token[0];
	paths = get_paths(shell->envp_lst);
	bin_path = get_bin_path(parser->token[0], paths);
	if (!bin_path)
	{
		err_cmd(parser->token[0]);
		exit_path(paths, NULL, 127);
	}
	if (execve(bin_path, parser->token, shell->envp) == -1)
	{
		free(bin_path);
		exit_path(paths, parser->token[0], 127);
	}
	free(bin_path);
	exit_path(paths, NULL, EXIT_SUCCESS);
	return ;
}

void	single_exe(t_shell *shell, t_parser *parser)
{
	if (builtin(shell, parser))
		return ;
	find_path(shell, parser);
}


t_parser	*test_exec_cmd(t_shell *shell, t_parser *parser)
{
	signal(SIGINT, child_signals);
	if (parser->operator == PIPE)
		parser = test_pipe_exe(shell, parser);
	else if (parser->operator == NONE)
		single_exe(shell, parser);
	else
		redir_exe(shell, parser);
	exit(exit_status);
}
