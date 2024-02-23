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

typedef struct s_echos {
	char	**echos;
}	t_echos;

// echo.c
char	*ft_get_env(const char *env);

// utils.c
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t	i);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_count_words_arr(char **arr);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);

// split
char	**ft_split(char const *str, char c);

// builtins
int		ft_pwd(void);
int		ft_cd(char *path);

// free
void	ft_free_arr(char **tokens);

#endif
