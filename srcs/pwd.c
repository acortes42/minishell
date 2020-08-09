#include "../minishell.h"

int ft_pwd(abs_struct *base)
{
   char cwd[PATH_MAX];

   if (getcwd(cwd, sizeof(cwd)) != NULL) 
       printf("%s\n", cwd);
   else 
       perror("getcwd() error");
   return (1);
}