# MyShell — Custom Linux Shell in C

A custom UNIX shell built from scratch in C demonstrating
core OS process management and IPC concepts.

## Features
- Custom colored prompt with current directory
- Execute any Linux command
- Built-in commands: cd, pwd, exit, help, history, clear
- Pipe support: ls | grep .c
- Command history (last 10 commands)

## How To Compile
```
make
```

## How To Run
```
./myshell
```

## Built-in Commands
| Command   | Description              |
|-----------|--------------------------|
| cd [dir]  | Change directory         |
| pwd       | Print current directory  |
| history   | Show last 10 commands    |
| clear     | Clear screen             |
| help      | Show help                |
| exit      | Exit shell               |

## Example Usage
```
myshell:~$ ls
myshell:~$ cd /tmp
myshell:/tmp$ ls | grep test
myshell:/tmp$ history
myshell:/tmp$ exit
```
