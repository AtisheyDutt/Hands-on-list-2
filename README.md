# System Software-II : Hands-on List II - Solutions

File names follow the question number (sub-parts: a, b, c ...).
Build everything with `make` (or one file: `gcc -Wall -pthread -o 8a 8a.c`). `make clean` removes binaries.

| Q | Files | Notes |
|---|-------|-------|
| 1 | 1a.c 1b.c 1c.c | ITIMER_REAL / VIRTUAL / PROF, 10 s + 10 us interval, fires 3 times (VIRTUAL/PROF need ~30 s of CPU time) |
| 2 | 2.c | getrlimit |
| 3 | 3.c | setrlimit (RLIMIT_NOFILE soft limit -> 512) |
| 4 | 4.c | rdtsc (x86 time stamp counter), 100 x getppid |
| 5 | 5.c | sysconf |
| 6, 7 | 6.c 7.c | pthreads (need `-pthread`) |
| 8 | 8a-8g.c | signal(): SIGSEGV, SIGINT, SIGFPE, alarm, setitimer REAL/VIRTUAL/PROF |
| 9 | 9.c | ignore then restore SIGINT with signal() |
| 10 | 10a-10c.c | sigaction(): SIGSEGV, SIGINT, SIGFPE |
| 11 | 11.c | ignore then restore SIGINT with sigaction() |
| 12 | 12.c | orphan: child sends SIGKILL to parent |
| 13 | 13a.c 13b.c | Run `./13a`, then `./13b <pid>`. **SIGSTOP cannot be caught** (signal/sigaction give EINVAL, process just stops; `kill -CONT <pid>` resumes) |
| 14-16 | 14.c 15.c 16.c | pipe, parent->child, two-way (two pipes) |
| 17 | 17a.c 17b.c 17c.c | `ls -l \| wc` using dup / dup2 / fcntl(F_DUPFD) |
| 18 | 18.c | `ls -l \| grep ^d \| wc` with dup2 only; first number printed = number of directories |
| 19 | 19.sh 19d.c 19e.c | a,b,c = shell script (mknod, mkfifo, strace comparison); d = mknod() syscall; e = mkfifo() |
| 20 | 20a.c 20b.c | FIFO one way (a = writer, b = reader) |
| 21 | 21a.c 21b.c | FIFO two way with two FIFOs (start 21a first, then 21b) |
| 22 | 22.c | select() with 10 s timeout on a FIFO (`echo hi > myfifo22` from another terminal) |
| 23 | 23.c | max open files + pipe capacity (F_GETPIPE_SZ and measured) |
| 24-29 | 24.c 25.c 26.c 27a.c 27b.c 28.c 29.c | System V message queue (key from ftok(".", 'q')) |
| 30 | 30.c | shared memory: write, SHM_RDONLY overwrite test (SIGSEGV), detach, remove |
| 31 | 31a.c 31b.c | binary (1) and counting (5) System V semaphores |
| 32 | 32a.c 32b.c 32c.c 32d.c | ticket number, protect shared memory, counting semaphore (2 resources), remove semaphores |
| 33 | 33a.c 33b.c | TCP server (port 5000) / client `./33b <server-ip>` |
| 34 | 34a.c 34b.c 34c.c | concurrent echo server with fork (a) and pthread_create (b), port 5001; client = 34c |

Tested on Linux x86-64 with gcc. Q4 uses x86 `rdtsc`.
Q19c answer: both commands end in the same mknod syscall, but `mkfifo` is better (POSIX, dedicated to FIFOs, no type letter, no privileges needed).
