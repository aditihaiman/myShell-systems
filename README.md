# myShell-systems

Features:
- Forks and executes basic shell commands including cd, rm, cat, ls, etc.
- Parses multiple commands on one line.
- Redirects using <, >.
- Executes pipe using |.
- Changes directories.
- Exits shell.

Bugs:
- sometimes, the program doesn't exit immediately after typing "exit", but only after typing "exit" multiple times (but this doesn't always happen)
- when you type cd, it doesn't go to the home directory but typing "cd /" will
- commands like "ls" or commands using ";" only work without spaces in between/after them. For example "ls" works but "ls " doesn't, and "ls;cd .." works but "ls ; cd .." doesn't


Files and Functions:

      main.c: Handles all code and functions to create and execute the shell.

      /*============== char **parse_args( char * line );=================
      Inputs: char * line
      Returns: Array of strings with the parsed line.

      The input is a line containing multiple words separated by a space;
      this function will parse the line with a space as the delimiter.
      ======================*/

      /*============== char **parse_mult_args( char * line ); ===========
      Inputs: char * line
      Returns: Array of strings with the parsed input.

      If a line contains multiple commands separated by a semicolon,
      this function will parse the line with a semicolon as the delimiter.
      ======================*/

      /*============== int redirect_stdin( char * filename ); ============
      Inputs: char * filename
      Returns: The file descriptor of the backup for stdin.

      This function creates a file and redirects stdin to that file.
      ======================*/

      /*============== int redirect_stdout( char * filename ); ============
      Inputs: char * filename
      Returns: The file descriptor of the backup for stdout.

      This function creates a file and redirects stdout into that file.
      ======================*/

      /*============== int main(); ============
      Executes shell and shell commands.

      ======================*/
=======
