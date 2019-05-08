# (Unnamed) RPG Game #

## Compiling, Testing & Deploying ##

You can pass two arguments to the built executable.  
An argument is considered `true` if:

* The first character is either a '`t`' or a '`T`'
* The argument is a number and is *NOT* a zero(`0`)

If the first argument is `true`, **Debug Mode** is activated.  
In Debug Mode, verbose explanation of what the program is doing is printed to the standard output, which is most of the time the terminal window.

The second argument requires Debug Mode to be active, it colors the printed messages.  
This is useful for terminals that do not support ASCII escape sequences.

### Requirements ###

To build the game you will need the following things:

* [**GNU Compiler Collection**](https://gcc.gnu.org)
	- To compile *FOR* a Windows machine, you will need [**MinGW-w64**](https://mingw-w64.org).  
	  Make sure that the Windows API headers are at the right location. Change the `WINAPI_H_LOC` macro in the Makefile to wherever you have your headers.
* [**GNU Make**](https://www.gnu.org/software/make)
* [**Python3.6**](https://www.python.org/downloads/release/python-367) built and installed from source(since we need the header and library files)
	- We specifically use **Python3.6.7** but generally, any **Python3** version will work.
* **Python** [**Pygame**](https://www.pygame.org)

It's generally not recommended to try and built it when you're *ON* a Windows machine, since the files are written for a GNU/Linux environment.

### Testing ###

Call the `test` target from the `Makefile` to compile the code by writing `make test` or just `make` in the console.  
A directory `bin` will be created at the root of the repository with the compiled C++ object files and an executable file.  
The name of the executable is based on which operating system is being build for.

| Operating System |      ID      |      Executable Name      |
| :--------------- | :----------: | :-----------------------: |
| GNU/Linux        | `gnu_linux`  |   `rpg-game_gnu_linux`    |
| Windows(32 bit)  |  `win_i686`  |  `rpg-game_win_i686.exe`  |
| Windows(64 bit)  | `win_x86_64` | `rpg-game_win_x86_64.exe` |

By default, the GNU/Linux system is chosen to build for.  
You can change this by changing the `OS` macro in the Makefile.  
This is done by passing the argument `OS=<os>` down when calling `make` where `<os>` needs to be placed with the operating system ID.

### Deploying ###

When you call the `deploy` rule, with `make deploy`, a `.tar.gz` archive will be created in a new `deploy` directory.  
The name of the archive is also based on the operating system.

| Operating System |      ID      |         Archive Name         |
| :--------------- | :----------: | :--------------------------: |
| GNU/Linux        | `gnu_linux`  | `rpg-game_gnu_linux.tar.gz`  |
| Windows(32 bit)  |  `win_i686`  |  `rpg-game_win_i686.tar.gz`  |
| Windows(64 bit)  | `win_x86_64` | `rpg-game_win_x86_64.tar.gz` |

### Cleanup ###

Cleanup is done by calling the `clean` rule.
The `bin` and `deploy` directories along with all their contents will be removed.

### Footnote ###

If you're compiling the game very often and don't want to always change the target operating system by passing it down with the `make` command, you can write an `init.mk` file with this statement.
