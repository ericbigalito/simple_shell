#include "shell.h"

void display(char **argv, char **env)
{
	int i, stat = 0;
	char *command, *path, *str = NULL;
	size_t n = 0;
	ssize_t ret;
	char *av[] = {NULL, NULL};
	char *ev[] = {NULL};
	pid_t m_child;
	char *tok;
	
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("$ ");
		ret = getline(&str, &n, stdin);
		if (ret == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		if (str[ret - 1] == '\n')
			str[ret - 1] = '\0';
		i = 0;
		tok = strtok(str, " ");
		while (tok != NULL && i < 10)
		{
			av[i] = tok;
			tok = strtok(NULL, " ");
			i++;
		}
		av[i] = NULL;
		if (av[0] == NULL)
			continue;
		if (strcmp(str, "exit") == 0)
		{
			free(str);
			break;
		}
		if (i >= 1)
		{
			command = av[0];
			path = findpath(command);
			if (path == NULL)
			{
				perror("NOT FOUND");
				free(str);
				str = NULL;
				continue;
			}
			i++;
		}
		m_child = fork();
		if (m_child == -1)
		{
			free(str);
			free(path);
			exit(EXIT_FAILURE);
		}
		if (m_child == 0)
		{
			if(execve(path, av, ev) == -1)
			{
				perror("ERROR");
				free(str);
				free(path);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&stat);
		}
		free(path);
	
	free(str);
	str = NULL;
	}
}

	
