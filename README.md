## Minishell (project collaboration with [Maciej Domnik](https://github.com/mdomnik))
Minishell is an intermediate project at 42 that involves creating a simple shell, similar to the Unix shell, from scratch. The goal is to develop a basic command-line interpreter that can execute commands, manage processes, and handle input/output redirection.

### Key features of the Minishell project include:

- **Prompt Display:** Displaying a command prompt where users can type commands.
- **Command Parsing:** Reading and parsing user input to identify commands and arguments.
- **Execution of Commands:** Implementing built-in commands (like cd, echo, exit, etc.) and handling the execution of external programs using fork() and execve().
- **Pipes and Redirection:** Implementing support for pipelines (|), input (<), and output (>) redirections, allowing the combination of multiple commands and redirection of data streams.
- **Signal Handling:** Managing signals to handle user interruptions (like Ctrl+C, Ctrl+D, etc.) and ensuring the shell remains responsive.
- **Environment Variables:** Managing environment variables and allowing their use and modification within the shell.
<br>
The Minishell project challenges students to delve deep into the Unix process model, inter-process communication, and system calls. By building their own shell, students not only gain a thorough understanding of how command-line interfaces work, but they also learn to manage processes and resources efficiently. This project emphasizes team collaboration, as students work together to address various edge cases and integrate different components. It serves as an excellent exercise in systems programming and provides a strong foundation for understanding more complex operating system concepts.
