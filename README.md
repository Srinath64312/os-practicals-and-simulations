# OS Practicals & Skilling Sessions

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/Srinath64312/os-practicals-and-simulations)
[![Build Status](https://img.shields.io/badge/GCC-15.2.0-blue.svg)](https://gcc.gnu.org/)
[![Valgrind](https://img.shields.io/badge/Valgrind-3.26-green.svg)](https://valgrind.org/)

Operating Systems and Systems Programming (OSSP) — 25CS2104E Laboratory, Skilling Sessions, and Practical Simulations Repository.

---

## 🚀 Run Live Inside GitHub (Interactive Cloud Terminal)

You can compile, run, and debug all practicals in an interactive Linux terminal **directly inside GitHub** in your browser without installing anything locally:

👉 **[Open in GitHub Codespaces](https://codespaces.new/Srinath64312/os-practicals-and-simulations)**

1. Boots a ready-to-code Ubuntu 24.04 Linux container.
2. Auto-installs GCC, Make, GDB, Valgrind and runs `make all`.
3. Run any practical directly:
   ```bash
   ./page_replacement
   ./dynamic_memory
   ./copy_lowlevel Makefile test_out.txt
   ./skilling10
   ```

---

## 📁 Repository Structure

### 🧪 Practical Sessions
- **`prog1.c`** — **Practical 1:** Command Execution using `fork()`, `execvp()`, and `wait()`.
- **`prog2.c`** — **Practical 2:** File Copy using low-level POSIX system calls (`open`, `read`, `write`, `close`).
- **`prog3.c`** — **Practical 3:** Process Lifecycle, PID/PPID inspection, and execution states.
- **`prog4.c`** — **Practical 4:** Process Synchronization comparing `wait()` and `waitpid()`.
- **`prog5.c`** — **Practical 5:** Producer-Consumer Inter-Process Communication (IPC) via Anonymous Pipes (`pipe()`).
- **`prog6_fifo_server.c`** — **Practical 6 (Part 1 - Server):** Multi-Client Server IPC using Named Pipes (FIFOs via `mkfifo`).
- **`prog6_fifo_client.c`** — **Practical 6 (Part 1 - Client):** Client that creates a dedicated return FIFO and communicates with the FIFO server.
- **`signal_handler.c`** — **Practical 6 (Part 2):** Asynchronous Event Handling using POSIX `sigaction()` capturing `SIGINT`, `SIGTERM`, and `SIGUSR1`.
- **`page_replacement.c`** — **Memory Management:** Page Replacement Algorithms Simulator (FIFO, Optimal, LRU, and MRU) with frame visualizations, page hit/fault tracking, and benchmark comparisons.
- **`prog7_linuxaddr.c`** — **Practical 7:** Understanding Linux Process Address Space (Code, Data, Static, BSS, Heap, and Stack segments) and `/proc/<PID>/maps` inspection.
- **`dynamic_memory.c`** — **Practical 8 (Part 1):** Dynamic Memory Allocation using `malloc()`, `calloc()`, `realloc()`, and `free()` with Valgrind memory leak verification.
- **`cow_demo.c`** — **Practical 8 (Part 2):** Copy-on-Write (COW) Memory Demonstration after `fork()` with per-page modification analysis.
- **`copy_lowlevel.c`** — **Practical 9 (Part 1):** Low-Level File Copy using POSIX system calls (`open`, `read`, `write`, `lseek`).
- **`copy_stdio.c`** — **Practical 9 (Part 2):** Standard C Library File Copy using buffered I/O streams (`fopen`, `fread`, `fwrite`, `fseek`, `ftell`).
- **`redirect_output.c`** — **Practical 9 (Part 3):** Standard Output Redirection to file using `dup2(fd, STDOUT_FILENO)`.
- **`redirect_input.c`** — **Practical 9 (Part 4):** Standard Input Redirection from file using `dup2(fd, STDIN_FILENO)`.

### 🛠️ Skilling Sessions (Restricted Shell Project)
- **`skilling1.c`** — **Skilling Session 1:** Shell REPL architecture and interactive input loop.
- **`skilling2.c`** — **Skilling Session 2:** User authentication gate and command whitelisting.
- **`skilling3.c`** — **Skilling Session 3:** Process synchronization with `waitpid()` and exit status macros.
- **`skilling4.c`** — **Skilling Session 4:** Shell built-in commands (`cd`, `pwd`, `env`) executed directly in the parent process.
- **`skilling5.c`** — **Skilling Session 5:** POSIX signal handling (`SIGINT` Ctrl+C interception and `SIGCHLD` zombie reaper).
- **`skilling6.c`** — **Skilling Session 6:** Complete integrated Restricted Shell with security sanitization and audit logging.
- **`skilling7.c`** — **Skilling Session 7:** Shell Pipeline Architecture using `pipe()` and `dup2()` for two-stage command pipelines.
- **`skilling8.c`** — **Skilling Session 8:** Defensive Memory Management and leak-free lifecycle for Valgrind verification.
- **`skilling10.c`** — **Skilling Session 10:** Multithreading & Concurrency using POSIX Threads (`pthread`) and Mutex synchronization.

---

## 🚀 Build and Compilation

To compile all practicals and skilling programs at once using `gcc` with `-Wall -Wextra -g`:
```bash
make
```

To run Valgrind leak checking on dynamic memory:
```bash
make check_leaks
```

To clean compiled binaries and temporary test artifacts:
```bash
make clean
```

---

## 💻 Running the Programs

### 1. Practicals 1 to 5
```bash
./prog1
./prog2
./prog3
./prog4
./prog5
```

### 2. Practical 6 (Named Pipes / FIFO Client-Server)
Open two or three terminals:

**Terminal 1 (Server):**
```bash
./prog6_fifo_server
```

**Terminal 2 (Client 1):**
```bash
./prog6_fifo_client "Hello Server from Client 1"
```

**Terminal 3 (Client 2):**
```bash
./prog6_fifo_client "Hello Server from Client 2"
```

### 3. Practical 6 (POSIX Signal Handling)
**Terminal 1:**
```bash
./signal_handler
```
**Terminal 2 (Sending signals):**
```bash
kill -SIGUSR1 <PID>    # Custom event handled
kill -SIGINT <PID>     # Interrupt handled (or press Ctrl+C in Terminal 1)
kill -SIGTERM <PID>    # Graceful shutdown
```

### 4. Page Replacement Algorithms Simulation
```bash
./page_replacement
```
Supports:
1. Built-in Handout Example 1 (FIFO demo with 3 frames)
2. Built-in Handout Example 2 (Optimal, LRU, MRU comparisons with 4 frames)
3. Custom page reference string and frame capacity input

### 5. Practical 7 (Linux Process Address Space)
```bash
./prog7_linuxaddr
```
In another terminal, inspect the active virtual mappings using the PID outputted:
```bash
cat /proc/<PID>/maps
pmap <PID>
grep -E "VmSize|VmRSS|VmData|VmStk|VmExe" /proc/<PID>/status
```

### 6. Practical 8 (Dynamic Memory & Valgrind)
**Run program:**
```bash
./dynamic_memory
```
**Run Valgrind Leak Check:**
```bash
valgrind --leak-check=full --show-leak-kinds=all ./dynamic_memory
# or simply:
make check_leaks
```

### 7. Practical 8 (Copy-on-Write Demonstration)
```bash
./cow_demo
```
Observes shared physical pages before and after child modifies 1 byte in each 4 KB page.

### 8. Skilling Sessions (Restricted Shell)
```bash
./skilling1
./skilling2
./skilling3
./skilling4
./skilling5
./skilling6
./skilling7
```
