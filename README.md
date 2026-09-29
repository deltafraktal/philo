*This project has been created as part of the 42 curriculum by dgeara.*

# Philosophers

## Description

Philosophers is a 42 project that introduces **concurrent programming** through a classic computer science problem: the Dining Philosophers.

Several philosophers sit around a round table. Each philosopher alternates between three states: **eating**, **sleeping**, and **thinking**. To eat, a philosopher must pick up the two forks placed on either side of them — but each fork can only be held by one philosopher at a time.

The challenge is to keep every philosopher alive, avoiding:
- **Deadlocks** — everyone is waiting and no one can proceed
- **Data races** — multiple threads reading/writing shared data without protection
- **Starvation** — a philosopher never gets to eat and eventually dies

Each philosopher is a **thread**, each fork is protected by a **mutex**, and a monitor thread watches for deaths and meal quotas.

---

## Key Concepts

### Threads

A thread is an independent execution path inside a program. Multiple threads run concurrently and share the same memory.

In this project, each philosopher lives in its own thread, running the same loop independently:

```
take forks → eat → drop forks → sleep → think → repeat
```

Threads are created with `pthread_create` and the main thread waits for them with `pthread_join` before cleaning up.

### Mutexes

A mutex is a lock that ensures only one thread can access a shared resource at a time. If a thread tries to lock a mutex that is already held, it waits until it is released.

```
Thread A locks mutex  →  Thread B waits
Thread A unlocks      →  Thread B can proceed
```

Mutexes are used here to protect:
- **Forks** — only one philosopher can hold a fork at a time
- **Shared data** — last meal time, meal count, simulation state
- **Output** — so printed messages don't overlap

### Data Races

A data race happens when two or more threads access the same variable at the same time, and at least one of them writes to it, without any mutex protecting the access. The result is unpredictable.

Every shared variable in this project is read and written only while holding the appropriate mutex.

### Deadlocks

If every philosopher picks up their left fork first, they all hold one fork and wait forever for the second — no one can proceed. This is a deadlock.

To prevent this, odd and even philosophers pick up their forks in opposite order, breaking the symmetry.

### The Monitor

The monitor runs in the main thread and checks two things in a loop:
1. Has any philosopher exceeded `time_to_die` without eating? → print `died`, stop the simulation
2. Have all philosophers reached the optional meal quota? → stop the simulation

---

## Instructions

### Compilation

```bash
make
```

This produces the `philo` binary. Standard Makefile rules are available:

```bash
make clean    # remove object files
make fclean   # remove object files + binary
make re       # fclean + make
```

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

All time values are in **milliseconds**. The last argument is optional.

### Arguments

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Time in ms before a philosopher dies without eating |
| `time_to_eat` | Time in ms a philosopher spends eating |
| `time_to_sleep` | Time in ms a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | *(optional)* Simulation ends when all reach this count |

### Examples

```bash
# 5 philosophers, no meal quota
./philo 5 800 200 200

# Stops once every philosopher has eaten at least 7 times
./philo 5 800 200 200 7

# Single philosopher — can never eat (only one fork), dies after time_to_die
./philo 1 200 100 100
```

### Output format

```
timestamp_in_ms philosopher_id has taken a fork
timestamp_in_ms philosopher_id is eating
timestamp_in_ms philosopher_id is sleeping
timestamp_in_ms philosopher_id is thinking
timestamp_in_ms philosopher_id died
```

---

## Useful Tests

Check for memory leaks:
```bash
valgrind --leak-check=full ./philo 5 800 200 200 3
```

Check for data races:
```bash
valgrind --tool=helgrind ./philo 5 800 200 200 3
```

Trigger a death (a philosopher should die, and no message should appear after `died`):
```bash
./philo 4 310 200 100
```

Stress test with many threads:
```bash
./philo 200 800 200 200 2
```

---

## Resources

### Threads and Mutexes
- [POSIX Threads Programming — LLNL](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_create documentation](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [pthread_mutex_lock documentation](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [Code Vault — Threads playlist (YouTube)](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)

### The Problem
- [The Dining Philosophers by Oceano (YouTube)](https://www.youtube.com/watch?v=NbwbQQB7xNQ)
- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

### AI Usage

Claude (Anthropic) was used during this project as a learning tool, specifically to:
- Progressively explain threads, mutexes, deadlocks, and data races with concrete examples
- Suggest relevant test scenarios and help interpret their results
- Help verify edge cases (single philosopher, partial thread creation failure, mutex unlock on error paths)