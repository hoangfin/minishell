# Minishell

Welcome to **Minishell**! 🐚  
This project is a minimalist shell implementation inspired by Bash, created as part of the École 42 curriculum. It is a fully functional shell that mimics the behavior of a Unix terminal, allowing users to execute commands, manage files, and interact with their environment efficiently.

## Why Minishell?

Minishell is a deep dive into system programming, focusing on process management, inter-process communication, and command-line interfaces. This project is not just about building a shell—it’s about understanding how operating systems work at their core and gaining hands-on experience with essential concepts like:

- **Forking and Processes**
- **File Descriptors and Redirections**
- **Signal Handling**
- **Environment Variables and Path Resolution**

The project challenges you to think critically, solve complex problems, and write clean, efficient C code.

## Features

Minishell replicates many features of a standard Unix shell, including:

- **Command Execution:**  
  Execute external programs from absolute or relative paths, with support for searching `$PATH`.

- **Built-in Commands:**  
  Implementations of shell built-ins like:
  - `echo` with options
  - `cd` for directory navigation
  - `pwd` to display the current directory
  - `export` and `unset` to manage environment variables
  - `env` to list environment variables
  - `exit` to quit the shell

- **Pipes and Redirections:**  
  Supports:
  - Piping commands (`|`)
  - Input redirection (`<`)
  - Output redirection (`>`, `>>`)

- **Environment Variable Expansion:**  
  Handles `$VAR` expansions to access environment variables dynamically.

- **Signal Handling:**  
  Graceful response to:
  - `Ctrl+C` (Interrupt)
  - `Ctrl+D` (End-of-file)
  - `Ctrl+\` (Quit)

- **Command History:**  
  Utilize the GNU Readline library for command-line editing and history.

## Getting Started

To run Minishell locally:

1. **Clone the Repository:**
   ```bash
   git clone --recurse-submodules https://github.com/hoangfin/minishell.git
2. **Navigate to the Project Directory:**
   ```bash
   cd minishell
3. **Build the Project:**
   ```bash
   make
4. **Run Minishell:**
   ```bash
    ./minishell

## Prerequisites

Before building and running Minishell, make sure you have the following:

- **C Compiler:**  
  A C compiler such as GCC or Clang with support for C99 or higher.

- **GNU Readline Library:**  
  This library is required for command-line editing and history functionality. You can install it using your system’s package manager:

  - **For Ubuntu/Debian:**
    ```bash
    sudo apt-get install libreadline-dev
    ```
  - **For macOS (using Homebrew):**
    ```bash
    brew install readline
    ```
  - **For Arch Linux:**
    ```bash
    sudo pacman -S readline
    ```

Thank you for visiting the project! I hope you find Minishell as enjoyable to work on as it was to create. Happy coding! 🚀

