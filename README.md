# Minishell_t

## Overview
Minishell_t is a project completed as part of the curriculum at 42 Ecole. This repository contains the implementation of a custom shell, similar to bash, that supports various built-in commands and shell functionalities.

## Repository Structure

### Root Directory
- **indivi**: Contains individual projects by Eunjeong and Minjinki in their respective folders.
- **project**: Contains the main Minishell project developed collaboratively.
- **en.subject-Minishell.pdf**: The subject PDF detailing the project requirements.
- **README.md**: The file you are currently reading.

### `project` Directory Structure
```
project
├── include
└── src
    ├── BUILTIN
    ├── ENV
    ├── LIBFT
    ├── MAIN
    ├── PARSE
    ├── PIPE
    ├── SIGNAL
    └── UTILS
        └── pipe
```
- **include**: Header files.
- **src**: Source files categorized by functionality.
  - **BUILTIN**: Built-in command implementations (cd, echo, env, export, pwd, unset, exit).
  - **ENV**: Environment variable management.
  - **LIBFT**: Custom library functions.
  - **MAIN**: Main execution files.
  - **PARSE**: Command parsing logic.
  - **PIPE**: Pipe handling.
  - **SIGNAL**: Signal handling.
  - **UTILS**: Utility functions, including additional pipe-related utilities.

## Project Details

### Global Variable
The project uses a single global variable, `t_glob`, which is a structure defined in `structs.h`. Note that the use of a global structure for this purpose has been deprecated in newer guidelines.

### Implemented Features
Minishell_t implements the following built-in commands:
- `cd`
- `echo`
- `env`
- `export`
- `pwd`
- `unset`
- `exit`

Additionally, it supports shell functionalities such as:
- Pipe handling (`|`)
- Signal management
- Redirection (`<`, `>`, `>>`)

## Getting Started
To run the Minishell project, navigate to the `project` directory and follow the instructions provided in the Makefile to compile and execute the shell.

## Authors
- **Eunjeong**
- **Minjinki**

For more detailed information, refer to the `en.subject-Minishell.pdf` provided in the root directory.


## Project Crawling

PROJECT_NAME : minishell_t
PROJECT_DESCRIPTION : Minishell_t is a project completed as part of the curriculum at 42 Ecole. This repository contains the implementation of a custom shell, similar to bash, that supports various built-in commands and shell functionalities.
PROJECT_URL : 'https://github.com/Tyranno-Rex/minishell_t.git'
PROJECT_COMPLETION_STATUS : TRUE
PROJECT_MULTI : FALSE
PROJECT_SUBPROJECT : NONE
PROJECT_CATEGORY : 'implement', 'os', 'teamTask'