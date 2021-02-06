# minishell

## User manual
The user won't need any instruction :) . Use built-in command: help

## Develop
### Docs
#### Minishell implementation
* Summary: https://www.gnu.org/software/libc/manual/html_node/Missing-Pieces.html
* The beginning: https://www.gnu.org/software/libc/manual/html_node/Implementing-a-Shell.html
#### Ctrl-d
https://www.gnu.org/software/bash/manual/html_node/Bash-Variables.html#index-IGNOREEOF
#### Redirections
https://www.gnu.org/software/bash/manual/html_node/Redirections.html
https://tldp.org/LDP/abs/html/io-redirection.html
#### Quotings
https://www.gnu.org/software/bash/manual/html_node/Quoting.html
https://www.gnu.org/software/bash/manual/html_node/Special-Parameters.html -  Special parameters
#### Shell parameter expansion
https://www.gnu.org/software/bash/manual/html_node/Shell-Parameter-Expansion.html
#### Exit builtin
https://www.gnu.org/software/bash/manual/html_node/Exit-Status.html#Exit-Status -> interesting exit codes to check
https://man.cx/exit
#### Launching jobs
https://www.gnu.org/software/libc/manual/html_node/Launching-Jobs.html
### Debug
#### VSCode
Debug child thread of a fork. Set follow-fork-mode to child in the Debug console tab using the next command:
* -exec set follow-fork-mode child
