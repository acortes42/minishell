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
#### Keyboard processing
##### ANSI escape codes
https://en.m.wikipedia.org/wiki/ANSI_escape_code
##### ISO/IEC 2022
https://en.m.wikipedia.org/wiki/ISO/IEC_2022
##### C0 and C1 control codes
https://en.m.wikipedia.org/wiki/C0_and_C1_control_codes

#### Exit builtin
https://www.gnu.org/software/bash/manual/html_node/Exit-Status.html#Exit-Status -> interesting exit codes to check
https://man.cx/exit
tldp.org/LDP/abs/html/exitcodes.html -> si salimos con un código de error por encima de 255 hacemos un módulo de 256
#### Launching jobs
https://www.gnu.org/software/libc/manual/html_node/Launching-Jobs.html
##### Problems
###### wait
* Not child processes: https://stackoverflow.com/questions/1608017/no-child-process-error-from-waitpid-when-waiting-for-process-group
###### Core dump files
check man 5 core. Also check /proc/sys/kernel/core_pattern file.

### Debug
#### VSCode
Debug child thread of a fork. Set follow-fork-mode to child in the Debug console tab using the next command:
* -exec set follow-fork-mode child
Debug main thread of a fork
* -exec set follow-fork-mode parent
