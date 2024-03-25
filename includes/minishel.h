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

# define CWD_SIZE 1024

typedef struct s_shell {
	char			*prompt;
	char			**tokens;
	char			*path;
	// char			*built_in;
	// int				has_redirections;
	char			**envp;
	// int				s_quotes;
	// int				d_quotes;
	int				fd_in;
	int				fd_out;
	int				fd_err;
	struct s_cmds	*cmds;
	// struct s_env	*env;
}	t_shell;

typedef struct s_cmds {
	char			*token;
	// char			*delimiter;
	int				s_quotes;
	int				d_quotes;
	struct s_cmds	*next_cmd;
}	t_cmds;

typedef struct s_env {
	char			*var_name;
	int				*var_value;
	struct s_env	*next_node;
}	t_env;


// split
char	**ft_split(char const *str, char c);

// lib
char	*ft_strjoin(char const *s1, char const *s2);

// main
char	**ft_get_paths(char	**envp);
char	*ft_get_builtin_name(t_shell *shell);

#endif
