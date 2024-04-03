# ifndef MINISHEL_H
#define MINISHEL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <bsd/string.h>

# define CWD_SIZE 1024

typedef struct s_shell {
	char			*prompt;
	char			**tokens;
	char			*path;
	// char			*built_in;
	int				has_redirections;
	int				fd_in;
	int				fd_out;
	struct s_cmds	*cmds;
	struct s_env	*env;
}	t_shell;

typedef struct s_cmds {
	// char			*promt;
	char			*token;
	// char			*delimiter;
	int				s_quotes;
	int				d_quotes;
	struct s_cmds	*next_cmd;
}	t_cmds;

typedef struct s_env {
	int				order;
	char			*var_name;
	char			*var_value;
	struct s_env	*next_node;
}	t_env;


// split
char	**ft_split(char const *str, char c);

// lib
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_inv_strchr(const char *s, int c);

// main
char	**ft_get_paths(char	**envp);
char	*ft_get_builtin_name(t_shell *shell);
void	ft_print_arr(char **arr);
void	ft_print_cmds(t_cmds *cmds);
void	ft_free_arr(char **arr);
t_env	*ft_init_env(char **envp);
void	ft_init_cmds(t_shell *shell);


// built_ins
int		ft_find_path(t_shell *shell);
// void	ft_execve(t_shell *shell, char *token);
void	ft_execve_(t_shell *shell);
void	ft_simple_redirect(t_shell *shell);
void	ft_simple_redirect_new(t_shell *shell);

#endif
