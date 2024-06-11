# CHEPP

A simple shell written in c++, hence chell(shell with s=c, l=p like cpp)

## REQUIREMENTS

None to execute :)

## BUILD STEPS

- Clone the repo:

```bash
git clone https://www.github.com/mohamedarish/chepp.git
```

Start Development :D

- To build:

```bash
make
```

- To execute:

```bash
make run
```

or

```bash
./target/chepp
```

## TODOS

- \[x\] Implement the shell prompt
- \[x\] Implement a directory structure
- \[x\] Implement cd command \[NOTE: Use SYSTEM CALLS chdir() ;) WINK WINK\]
- \[x\] Implement pwd command (This is very easy) \[NOTE: JUST USE THE INBUILT pwd COMMAND\]
- \[x\] Find a way to execute commands
- \[x\] Terminal API using ncurses.
- \[ \] Move cursor and take input using ncurses.
- \[ \] Print output using ncurses.
- \[ \] Track cursor position for ease of use and editing commands.
- \[ \] Inlcude path variables to automatically search for commands from them and execute
- \[ \] Implement a tree for autocomplete suggestions
- \[ \] Find a way to find the height and width of the terminal
- \[ \] Implement a way to include a right side prompt
- \[x\] Find a way to implement an interactive terminal
- \[ \] Implement a chepprc file
- \[ \] Make a chepp scripting language
- \[ \] Come up with a cool name for chepp scripting
- \[ \] Implement a formatter and linter for chepp scripting
