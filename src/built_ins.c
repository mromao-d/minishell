#include "../includes/minishel.h"

// changes directory. Returns zero on success
// int	ft_chdir(char *dir, t_env *env)
// {
// 	;
// }


// frees t_cmds structure
void	ft_free_cmds(t_cmds *cmds)
{
	t_cmds	*node;
	t_cmds	*nxt_node;

	node = cmds;
	while (node) {
		nxt_node = node->next_cmd;
		free(node->token);
		free(node);
		node = nxt_node;
	}
	return ;
}

// finds the executable path in the operating system executables
// returns zero if success
int	ft_find_path(t_shell *shell)
{
	char	**splited;
	char	**tmp_split;
	char	*tmp;
	t_env	*env;
	int		out;
	t_cmds	*rmv;

	// if (shell->path)
	// 	return (1);
	rmv = shell->cmds;
	if (strcmp(rmv->token, "<") == 0)
		rmv = rmv->next_cmd->next_cmd;
	env = shell->env;
	while (env && strcmp(env->var_name, "PATH") != 0)
		env = env->next_node;
	splited = ft_split(env->var_value, ':');
	tmp_split = splited;
	out = 1;
	while (*tmp_split) {
		shell->path = ft_strjoin(*tmp_split, "/");
		tmp = shell->path;
		shell->path = ft_strjoin(tmp, rmv->token);
		if (!access(shell->path, F_OK)) {
			free(tmp);
			out = 0;
			break ;
		}
		free(tmp);
		free(shell->path);
		shell->path = NULL;
		tmp_split++;
	}
	ft_free_arr(splited);
	return (out);
}

// validates if token node has any kind of redirection
int	ft_contais_redir(char *cmd)
{
	if ((strcmp(cmd, "<") == 0) || (strcmp(cmd, "<<") == 0) || (strcmp(cmd, ">") == 0) || (strcmp(cmd, ">>") == 0))
		return (1);
	return (0);
}


// redirects input
// returns zero on success
void	ft_redir_input(t_shell *shell)
{
	t_cmds	*head;
	t_cmds	*next;
	
	head = shell->cmds;
	next = head->next_cmd;
	shell->cmds = shell->cmds->next_cmd->next_cmd;
	free(head->token);
	free(head);
	shell->fd_in = open(next->token, O_RDONLY);
	if (shell->fd_in < 0) {
		perror (next->token);
		return ;
	}
	free(next->token);
	free(next);
	return ;
}

int	ft_2d_arr_new(t_shell *shell)
{
	int		i;
	t_cmds	*head;

	head = shell->cmds;
	i = 0;
	while (head) {
		if (strcmp(head->token, "<") == 0) {
			close (shell->fd_in);
			if (head->next_cmd)
				head = head->next_cmd;
			else {
				perror ("syntax error near unexected token 'newline'!	->	please add file to redirect input");
				return (1);
			}
			shell->fd_in = open(head->token, O_RDONLY);
			if (shell->fd_in < 0) {
				perror (head->token);
				return (1);
			}
		}
		else if (strcmp(head->token, ">") == 0) {
			close (shell->fd_out);
			if (head->next_cmd)
				head = head->next_cmd;
			else {
				perror ("syntax error near unexected token 'newline'!	please add file to redirect output");
				return (1);
			}
			shell->fd_out = open(head->token, O_WRONLY | O_CREAT | O_TRUNC);
			if (shell->fd_out < 0) {
				perror (head->token);
				return (1);
			}
			// dup2(shell->fd_out, STDOUT_FILENO);
		}
		else
			i++;
		head = head->next_cmd;
	}
	shell->tokens = calloc(sizeof(char *), i + 1);
	// i = 1;
	i = 0;
	head = shell->cmds;
	while (head) {
		if ((strcmp(head->token, "<") != 0) && (strcmp(head->token, ">") != 0)) {
			shell->tokens[i++] = strdup(head->token);
			// i++;
		}
		else
			if (head->next_cmd)
				head = head->next_cmd;
		head = head->next_cmd;
	}
	shell->tokens[i] = NULL;
	return (0);
}

// executes the executables with execve
// void	ft_execve(t_shell *shell, char *token)
void	ft_execve_(t_shell *shell)
{
	int	fd[2];
	int	pid;

	if (ft_2d_arr_new(shell)) {
		perror ("ft_2d_arr_new");
		return ;
	}
	if (pipe(fd) < 0) {
		perror ("pipe error on ft_execve!\n");
		exit (1);
	}
	pid = fork();
	if (pid < 0) {
		perror ("fork error on ft_execve\n");
		exit (2);
	}
	if (pid == 0) {
		dup2(shell->fd_in, STDIN_FILENO);
		dup2(shell->fd_out, STDOUT_FILENO);
		close (shell->fd_in);
		close (shell->fd_out);
		close (fd[0]);
		close (fd[1]);
		execve(shell->path, shell->tokens, NULL);
	}
	else {
		close (fd[1]);
		close(shell->fd_in);
		close(shell->fd_out);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
	return ;
}

