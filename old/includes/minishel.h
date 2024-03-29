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
	char			*promt;
	char			**tokens;
	int				has_redirections;
	char			**envp;
	int				s_quotes;
	int				d_quotes;
	int				in;
	int				out;
	int				err;
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
	struct s_env	*next;
}	t_env;

// main.c
int		ft_validate_quotes(char *arg);
int		ft_execv(const char *path, char *const *argv);

// getenv.c
char	*ft_get_env(const char *env);

// lib.c
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t	i);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_count_words_arr(char **arr);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strcpy_v2(char *dest, const char *src);
void	ft_bzero(void *s, size_t n);

// split
char	**ft_split(char const *str, char c);

// builtins
void	ft_deal_built_ins(t_shell *shell);
int		ft_echo(char *prompt);
int		ft_pwd(void);
int		ft_cd(char *path);
int		ft_env(char **envp);

// free
void	ft_free_arr(char **tokens);

// redirections
void	ft_redirect_input(t_shell *shell);
// void	ft_redirect_input(void);
int		ft_has_redirections(t_shell *shell);

// exec.c
int		ft_deal_execs(t_shell *shell);
int		ft_execve(const char *path, char *const arg[], char *const envp[]);

// utils.c
t_shell	*ft_shell(char *prompt);
void	ft_free_shell(t_shell *shell);
void	ft_print_arr(t_shell *shell);

#endif
