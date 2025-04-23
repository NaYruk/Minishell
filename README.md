# 42 Project Minishell 👋

> Minishell is a 42 school project. In this project we need to recreate a simple Shell
> Based in Bash, and we also need to implemente some "Builtins".
> A Builtin is a reproduction of real command in a Shell.
> We need to recreate : cd, pwd, unset, export, echo, env, exit.

### [Homepage](https://github.com/NaYruk/Minishell)

## Correction :

Validated : **22/04/2025**
Grade : ✅ **101%** ✅

## Compile :

On Linux :
- Need to install the readline Library DEBIAN/UBUNTU : `sudo apt install libreadline-dev`
- Just do `make` and `./minishell`

On MacOS :
- Need to install the readline Libary : `brew install readline`
- Need to add the library in the Makefile :
	For example :
	- add : `-I/opt/homebrew/opt/readline/include`, in INCLUDE =
	- add : `-L/opt/homebrew/opt/readline/lib -lreadline -o` in `@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(NAME)`
- Just do `make` and `./minishell`

The valgrind.supp file is here for delete the readline valgrind error.
The readline function have some leaks, this is not to manage in minishell.
you can activate the valgrind.supp file with : `--suppressions=valgrind.supp --gen-suppressions=all`

# A prompt will be appear, you can enjoy in this beautiful Shell !
> Precision : This is not the real bash comportement, this is a simple reproduction.

## Author

👤 **NaYruk and Mcotonea Mulhouse 42 Students**

* Github: [@NaYruk](https://github.com/NaYruk)
* Github: [@Mcotonea](https://github.com/mcotonea42)