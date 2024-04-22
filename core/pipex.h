#ifndef PIPEX_H
# define PIPEX_h

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>

int         main(int argc, char **argv, char **envp);
int         ft_strlen(char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);
char    *ft_pathfinder(char *cmd, char **envp);
char	**ft_split(char *s, char c);
char    *ft_gnl(int fd);
void    ft_freeargs(char **cmd);
void    ft_error(char *msg);
void    ft_check_errors(int argc, int *fd);
void    ft_cmd1(char **argv, char **envp, int *fd);
void    ft_cmd2(char **argv, char **envp, int *fd);
void	ft_putstr(char *str);
size_t	ft_wordcount(char *s, char c);
size_t	ft_wordlen(char *s, char c);

#endif