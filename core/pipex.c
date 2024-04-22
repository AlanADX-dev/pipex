#include "pipex.h"

void    ft_check_errors(int argc, int *fd)
{
    if (argc != 5)
        ft_error("Error : usage = file1 cmd1 cmd2 file2\n");
    if (pipe(fd) < 0)
        ft_error("Error : pipe error\n");
}

char    *ft_pathfinder(char *cmd, char **envp)
{
    pid_t   path_pid;
    char    *res;
    char    *path[2];
    int     fd[2];

    path[0] = "which";
    path[1] = cmd;
    path[2] = NULL;
    if (pipe(fd) == -1)
        ft_error("Error : Pipe error\n");
    path_pid = fork();
    if (path_pid == -1)
        ft_error("Error : Fork error\n");
    if (path_pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execve("/usr/bin/which", path, envp);
    }
    waitpid(path_pid, NULL, 0);
    close(fd[1]);
    res = ft_gnl(fd[0]);
    close(fd[0]);
    return (res);
}

void    ft_cmd1(char **argv, char **envp, int *fd)
{
    char    *path;
    char    **cmd;
    int     infile;

    infile = open(argv[1], O_RDONLY, 0777);
    if (infile < 0)
        ft_error("Error : Infile open error\n");
    dup2(infile, 0);
    dup2(fd[1], 1);
    close(fd[0]);
    cmd = ft_split(argv[2], ' ');
    path = ft_pathfinder(cmd[0], envp);
    if (execve(path, cmd, envp) == -1)
	{
		close(fd[1]);
		close(infile);
		ft_freeargs(cmd);
		free(path);
		ft_error("ERROR : First command not found\n");
	}
}

void    ft_cmd2(char **argv, char **envp, int *fd)
{
    char    *path;
    char    **cmd;
    int     outfile;

    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (outfile < 0)
        ft_error("Error : Oufile open error\n");
    dup2(fd[0], 0);
    dup2(outfile, 1);
    close(fd[1]);
    cmd = ft_split(argv[3], ' ');
    path = ft_pathfinder(cmd[0], envp);
    printf("%s", path);
    if (execve(path, cmd, envp) == -1)
    {
        close(fd[0]);
        close(outfile);
        ft_freeargs(cmd);
        free(path);
        ft_error("Error : Second command not found\n");
    }
}

int     main(int argc, char **argv, char **envp)
{
    int     fd[2];
    pid_t   pid;

    ft_check_errors(argc, fd);
    pid = fork();
    if (pid == -1)
        ft_error("Error : fork error");
    if (pid == 0)
        ft_cmd1(argv, envp, fd);
    waitpid(pid, NULL, 0);
    pid = fork();
    if (pid == -1)
        ft_error("Error : fork error");
    if (pid == 0)
        ft_cmd2(argv, envp, fd);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid, NULL, 0);
    return (0);
}