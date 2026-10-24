#!/bin/bash
# Q19 (a, b, c) : create a FIFO using the mknod / mkfifo commands and compare them with strace
# Q19 (d) -> 19d.c  (mknod system call)      Q19 (e) -> 19e.c  (mkfifo library function)

rm -f fifo_mknod_cmd fifo_mkfifo_cmd

echo "a. mknod command"
mknod fifo_mknod_cmd p            # 'p' = FIFO (pipe) type
ls -l fifo_mknod_cmd

echo "b. mkfifo command"
mkfifo fifo_mkfifo_cmd
ls -l fifo_mkfifo_cmd

echo "c. strace : which one is better ?"
rm -f fifo_mknod_cmd fifo_mkfifo_cmd
strace mknod  fifo_mknod_cmd p 2>&1 | grep -E "mknod|mkfifo"
strace mkfifo fifo_mkfifo_cmd  2>&1 | grep -E "mknod|mkfifo"
# Both end up in the same kernel call (mknod / mknodat with S_IFIFO).
# mkfifo is the better choice : it is POSIX, needs no type letter ('p'),
# is less error-prone and is dedicated to FIFOs, whereas mknod is a generic
# (and mostly privileged) tool for creating any special file.
rm -f fifo_mknod_cmd fifo_mkfifo_cmd
