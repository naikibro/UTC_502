# UTC 502 - Principes fondamentaux des Systèmes d'exploitation

Compile C code to run with thread safety handling

```sh
gcc multithreading3.c -o multithreading3 -lpthread
```

# Multi-threading

This section covers multi-threading concepts in C using the pthread library.

## Thread Safety with Mutex

The following C code demonstrates thread safety using a mutex (mutual exclusion) to protect shared resources:

[mutex example](multithreading1.c)

## Dining Philosophers Problem

The following C code simulates the dining philosophers problem using threads and mutexes:
[Dining Philosophers](multithreading2.c)

## Thread Safety with Semaphore

The following C code demonstrates thread safety using a semaphore to protect shared resources:

[semaphore example](multithreading3.c)

These code examples showcase key concepts related to processes, threads, and synchronization mechanisms. You can compile and run them to gain a better understanding of these fundamental principles in operating systems.
