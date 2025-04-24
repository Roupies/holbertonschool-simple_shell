# 🐚 simple_shell

A minimalist command-line interpreter written in C that mimics basic UNIX shell behavior.  
Developed as part of the **Holberton School** curriculum.

---

## 📑 Table of Contents

1. [Introduction]  
2. [Installatio]
3. [Prerequisites] 
4. [Usage Examples]  
5. [Man Page]
6. [Testing] 
7. [Flowchart]  
8. [License] 
9. [Contribution]

---

## 1. 📘 Description

This shell displays a prompt (`$`), reads user input, searches the command in the `PATH`, and executes the command if found. It works in both interactive (line-by-line) and non-interactive (e.g., script) modes.

### Features:
- Displays a prompt (`$`)
- Reads input using `getline`
- Tokenizes the command line
- Searches for commands in the `PATH`
- Executes commands using `execve`
- Handles Ctrl+D to exit
- Prints an error if the command is not found

---

## 2. ⚙️ Installation

*   How to clone:

Step 1: Clone a repository, Git creates a local copy of it

git clone 

Step 2: Set the push.autoSetupRemote option

After clonning the repository, I can set this option to simplif future git push commands whan creating new branches

git config --global push.autoSetupRemote true

Step 3: Create a branch and push it

Create a new branch and push it for the first time, Git will automatically link that branch to the corresponding remote branch without requiring you to use --set-upstream.

git checkout -b my-new-branch (Olivia) git push

*   How to compile:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

---

## 3.   Requierement

Ubuntu 20.x (the environment used for development)

GCC (GNU Compiler Collection) for compiling the C code

Git for version control and collaboration

---

## 4.   Usage Exemples

* Exécution du shell:

./hsh

* Commandes supportée:

$ ls
$ /bin/ls
$ echo Hello
$ cat shell.h

Pour quitter : utilisez Ctrl+D (EOF) ou la commande exit.

---

## 5. Man Page


---

## 6. Flowchart


---

## 7. Testing

$ ./hsh
$ ls
README.md   hsh     parser.c      shell.h         string_utils1.c
executor.c  main.c  path_utils.c  string_utils.c  string_utils2.c
# (Check that output lists files in the current directory)

$ echo Hello, Shell!
Hello, Shell!
# (Ensure the shell can print user input correctly)

$ /bin/ls
README.md   hsh     parser.c      shell.h         string_utils1.c
executor.c  main.c  path_utils.c  string_utils.c  string_utils2.c
# (Direct path execution should work the same as with `ls` command)

$ fauxcmd
./hsh: fauxcmd: not found
# (The shell should properly handle unknown commands)

$ ls -l /tmp
total 24
drwx------ 2 root root 4096 Apr 24 09:46 snap-private-tmp
drwx------ 3 root root 4096 Apr 24 10:11 systemd-private-926a1793d4ff40c9934a77cefd6d78c5-polkit.service-zmOuGi
drwx------ 3 root root 4096 Apr 24 09:47 systemd-private-926a1793d4ff40c9934a77cefd6d78c5-systemd-logind.service-flwzrM
drwx------ 3 root root 4096 Apr 24 09:46 systemd-private-926a1793d4ff40c9934a77cefd6d78c5-systemd-resolved.service-SwneRt
drwx------ 3 root root 4096 Apr 24 09:46 systemd-private-926a1793d4ff40c9934a77cefd6d78c5-systemd-timesyncd.service-E5xVMw
drwx------ 3 root root 4096 Apr 24 09:47 systemd-private-926a1793d4ff40c9934a77cefd6d78c5-wsl-pro.service-KOA21N
# (Ensure the `ls -l` command works correctly)

$ ^C
# (User interrupts the shell using Ctrl+C)

$ (Press Ctrl+D)
# (Shell should exit gracefully when Ctrl+D is pressed)

$ ./hsh
$ exit
# (Shell should exit gracefully when `exit` is typed)
 
