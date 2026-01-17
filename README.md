*This project has been created as part of the 42 curriculum by ycakmakc*

# Philosophers

*"Where thinking is infinite, but spaghetti is scarce."*

## Description
Basically, this project is a simulation of philosophers, represented as a stack of data structures, fighting for survival. To eat the food in front of them, they strictly need **two forks**, but the cruel reality is that there is only one fork per philosopher.

The main goal is to orchestrate this dining table in such an organized way that we prevent the philosophers from dying of starvation—specifically by avoiding the dreaded **deadlock** problem. Here, we aim to bring order to a chaotic environment by splitting the process into **threads**. To achieve this, we utilize the project's core learning outcomes: **pthreads** to transform the process into separate execution units, and **mutexes**, which act as our **"chaos regulators"** to synchronize access to shared resources.

## Instructions

### Compilation
To compile the project, clone the repository and run the `make` command:

```bash
git clone <repo_src> philo
cd philo
make
```
### Execution
Run the program with the following arguments:

./philo 10 400 100 100 3

### Arguments

**number_of_philosophers:** Represents the number of philosophers and forks.

**time_to_die:** Represents the time (in ms) a philosopher can live without eating.

**time_to_eat:** Represents the time (in ms) it takes for a philosopher to eat.

**time_to_sleep:** Represents the time (in ms) a philosopher spends sleeping.

**rfn:** Number of times each philosopher must eat before the simulation stops.

## Resources
### References
[IEEE POSIX Threads (pthreads) Documentation](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html) - Official documentation for thread management.

[The Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) - Detailed explanation of the concurrency problem.

[Valgrind / Helgrind User Manual](https://valgrind.org/docs/manual/hg-manual.html) - Guide for detecting thread errors.

### AI Usage
This project utilized AI assistance (Gemini) for the following tasks:

Debugging & Error Analysis: Interpreting Helgrind logs to identify and resolve data races and lock order violations.

Refactoring: Restructuring code logic (e.g., splitting functions) to strictly adhere to the 42 Norminette standards (25 lines per function, 5 functions per file).

Concept Explanation: Clarifying complex threading concepts such as mutex deadlocks and correct join procedures.

Documentation: Generating templates for commit messages and this README file structure.

The core logic, thread implementation, and resource management strategies were implemented by the student, with AI serving as a tutor and code reviewer.

# THANKS FOR REVIEWING 🙏

![School](https://img.shields.io/badge/School-42-black)
![Language](https://img.shields.io/badge/language-C-blue)
![Norminette](https://img.shields.io/badge/Norminette-Pass-success)
```text
___________________________________________$$s
_________________________$____$$s___________s$$s
_________________________s$$$$s$$$$$$s________$$$___s$
_______________s$$$$$$$$s___s$$$$ss$$$$s________$$$__$$
________________________s$$$s__$$$$$s_$$$s___s$__s$$s_$$
__________s$$$$$$$$$$$$$$$$$$$$sss$$$$s_$$$s__$$$__s$$s$
_____s$$$$$$$$$s_____s$$$$$$$$$$$$$$h$$$__$$$s__$$___$$$s
___s$$$$$s_____________________ss$$$$$$$$s_s$$$s$$$__s$$$
__________________________s$$$s____s$$$$$$$$s$$$$$$$__$$$
_________s$$$$$$$$$$$$$$$s$$$$$$$$$$s$$$$$$$$$ss$$$$s_$$$
_____________________s$$$$$$$$$$s$$$s____s$$$$$$__$$$__$$
________________s$$$$$$$$$$$$$$$$$$$$$$s_____s$$$s_$$__$$
________s$$$$$$$$$$$$$$$$$$$$$$$s$s__s$$$$$$s___$$s_$s$$$
_____s$$$$$s$$$$$$$$$$$$$$s____$$s$$$$$$$$$$$$$s____$$$$s
___s$$$$__s$$$$$$$$$s_____s$$$$$s$$$$$$$$$$$$$$$$$s__$$$
___s$___$$$$$$______s$$$$$$$s_s$$$$$$$$$$$$$$$$$$$$$____$$$
______s$$$s___s$$$$$$$$$$$___$$$$$$$$$$$$$$$$$$$$$$$$s$$$$$$$s
_____$$$__s$$$$$$$$$$$$$$__$$$$$$$$$$$$$$$$$$$$s$s$_$$$$$$$$$$$
____$$$_$$$$$$i$$$$$s_$$__$$$$$$$$$$$$$$$$$$$ss$$$s$$$$$$$$s$$s
___$$__$$$__s$$$$ss__$$_$$$$$$$$$$$$$$$$$$$$s$$$$$_$$$$e$$s$
__$$_s$$___$$$$s_$$_$$s$$$$$$$$$$$$$$$$$$$$s$$$$$s_$$$$$$s$
_s$s$$$___$$$$_s$$__$$__$$$$$$$$$$$$$$$$$$_$$$$$$$_s_$$$
_$$s$s__s$$$__$$____s$$__$$$$$$$$$$$$$$$$$_$$$$$$$$__$$$
$$_$___$$$$_s$$__$$__$$$s__s$$$$$$$$$$$$$$_$$$$$$$$$$$$s
$$____$$$s_$$$__$$$_$_s$$$$s___s$s$$$$$$$$_$$$$$$$$s$$$
$____$$$__$$sss$$$$__$_s$$$$$$$$$$s$s$$$$$___s$$$$s$$$s
____$$$_s$$$_$s$$$$s_s$__$$$$$$___s$$s_$$$s___s$$$_$$$
____$$_s$$$_$$_s$$$$$_s$$___$$$$$________$_____$$$s$$s
___s$$_$$$__$$__$$$$$$$$$$s____s$$$$$_________s$$$$$$
___$$$s$$$__$$___$$ss$$$$$$$$s____s$$$$$s______$$$$$$
___$s$$$$$_s$$__s_$$$_s$$$$$$$$$$s___s$$$$$$$s___sss
___$$$$$$$_$$$__$s_$$$$s__s$$$$$$$$$s___$$$$$$$s
__s$$$$$$$_$$$s_s$__$$$$$$s__s$$$$$$$$$s__$__$$$$s
__$_$$$$s$_s$$$__$$__$$$$$$$$s__$$s$$$$$$$_____$$$$
____s$$$_$$_$$$___$$__$s$$$$$$$$_s__s$$$s$$$____$$$$
_____$$$__$_$$$$___$$_ss_$$$$$$$$$____$$$$_s$____$$$s
_____$$$s_$_s$$$s__$$$____s$$$$$$$$$___s$$$______$$$$
_____s$$$_ss_$$$$___$$s____$$$$$$$$$$___$$$$_____s$$$
______$k$__$__$$$$__s$$____$$$$$$$h$$____$$$$_____$$s
______$$$______$$$s__$$$___$$_$$$$$$$$___s$$$$____$$
_______$$s______$$$__s$$$___$_s$$$$$s____s$$$$____$s
_______$$$_______$$$_s$$_$__$__$$$$$s____s$$$$___$$
________$$_______s$$__$$_______$$$$$s____$$$$$___$s
________$$________s$$_$$______s$$$$$_____$$_$$___$
___________________$$_$$s_____$$$$$_____$$s_$s
____________________$$s$$_____$$$$_____s$$__$
____________________s$_$$____$$$s_____s$$
_____________________$_$$___$$$______s$$
_______________________$$__s$$______$$$
________________________$__$$______$$$
________________________$_$$s____$$$s
__________________________$$___s$$s
__________________________$$__$$s
