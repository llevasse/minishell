1 : save entrée standard.
2 : pipe/fork/dup2(fd[1] , 1)
3 : close pipe() ans child
4 : execute puis dup2(stdin_fileno, fd[0])
5 : close(tmp_fd) puis execve.