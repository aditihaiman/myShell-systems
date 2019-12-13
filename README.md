# myShell-systems

Features:
      Forks and executes commands.
      Parses multiple commands on one line.
      Redirects using <, >.
      Exits shell.
      Changes directories.




Bugs:
- sometimes, the program doesn't exit immediately after typing "exit", but only after typing "exit" multiple times (but this doesn't always happen)
- when you type cd, it doesn't go to the home directory but typing "cd /" will


Files and Functions:
main.c
      Handles all code and functions to create and execute the shell.
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
      Returns: A backup file for stdin.

      ????????????
      ======================*/

      /*============== int redirect_stdout( char * filename ); ============
      Inputs: char * filename
      Returns: A backup file for stdin.

      This function creates a file and redirects stdout into that file,
      returning a backup stdout file.
      ======================*/

      /*============== int main(); ============


      ======================*/
