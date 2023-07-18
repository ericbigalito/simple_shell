#include "shell.h"

char *findpath(char *command)
{
	char *env_path, *tok, path[320];

	env_path = getenv("PATH");
	tok = strtok(env_path, ":");

	while (tok != NULL)
	{
		snprintf(path, sizeof(path), "%s/%s", tok, command);
		if (access(path, X_OK) == 0)
		{
			return strdup(path);
		}
		tok = strtok(NULL, ":");
	}
	return (NULL);
}
