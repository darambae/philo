
# Philosophers

### Language

 - [French](./readme_fr.md)
 - [Korean](./readme_kr.md)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Important Concepts](#important-concepts)
- [Standard Functions](#standard-functions)

---

## Introduction

**philosopher** is an Ecole 42 project that explores concurrency, multithreading, and synchronization in the context of the classic "Dining Philosophers" problem. The project requires simulating philosophers sitting around a table, each alternating between eating, thinking, and sleeping, while managing shared resources (forks) with mutual exclusion to avoid deadlocks and race conditions.

---

## Features

- Simulates the Dining Philosophers problem using threads and mutexes.
- Demonstrates the use of concurrency control to manage access to shared resources.
- Ensures each philosopher can eat only when both adjacent forks are available.
- Includes error handling for thread creation and synchronization.

---

## Usage

### Basic Usage

```bash
./philosopher num_of_philos time_to_die time_to_eat time_to_sleep [num_of_times_each_philo_must_eat]
```

- `num_of_philos`: Number of philosophers and forks.
- `time_to_die`: Time (in milliseconds) a philosopher can survive without eating.
- `time_to_eat`: Time (in milliseconds) a philosopher spends eating.
- `time_to_sleep`: Time (in milliseconds) a philosopher spends sleeping.
- `num_of_times_each_philo_must_eat` (optional): Number of times each philosopher must eat before the simulation ends.

Example:

```bash
./philosopher 5 800 200 200
```

This command simulates five philosophers, each with an 800 ms time-to-die threshold, a 200 ms time-to-eat, and a 200 ms time-to-sleep period.

---

## Important Concepts

### Threads

Threads allow concurrent execution of multiple sequences of instructions within a program. In the **philosopher** project, each philosopher is represented by a separate thread. This allows each philosopher to operate independently, simulating real-world concurrency where each philosopher can think, eat, or sleep simultaneously without affecting the others.

- **pthread_create**: This function creates a new thread, allowing a function to be executed concurrently.
- **pthread_join**: This function waits for a specific thread to complete its execution, ensuring that the main program doesn't terminate before all threads have finished.

### Mutexes

A mutex (mutual exclusion) is used to prevent multiple threads from accessing a shared resource simultaneously, which could cause race conditions. In this project, mutexes are used to control access to the forks, ensuring that only one philosopher can hold each fork at a time.

- **pthread_mutex_init**: Initializes a mutex.
- **pthread_mutex_lock**: Locks a mutex, preventing other threads from accessing the shared resource until it’s unlocked.
- **pthread_mutex_unlock**: Unlocks a mutex, allowing other threads to access the resource.
- **pthread_mutex_destroy**: Destroys a mutex, freeing its resources.

---

## Standard Functions

### `usleep`

- **Usage**: `usleep(microseconds);`
- Pauses the execution of a thread for a specified number of microseconds. This function is used to simulate the time a philosopher spends eating, sleeping, or thinking.

### `gettimeofday`

- **Usage**: `gettimeofday(&tv, NULL);`
- Gets the current time, which is useful for tracking how long each philosopher has been in a particular state (e.g., eating or sleeping) and to check for starvation.

### `pthread_create`

- **Usage**: `pthread_create(&thread, NULL, function, arg);`
- Creates a new thread that starts executing the specified function. Each philosopher is represented by a thread created with this function.

### `pthread_join`

- **Usage**: `pthread_join(thread, NULL);`
- Waits for a specific thread to complete, ensuring that resources are properly freed before the program exits.

### `pthread_mutex_init`

- **Usage**: `pthread_mutex_init(&mutex, NULL);`
- Initializes a mutex that can be used to lock shared resources (forks) and prevent simultaneous access.

### `pthread_mutex_lock`

- **Usage**: `pthread_mutex_lock(&mutex);`
- Locks a mutex, blocking other threads from accessing the resource until it’s unlocked.

### `pthread_mutex_unlock`

- **Usage**: `pthread_mutex_unlock(&mutex);`
- Unlocks a mutex, allowing other threads to access the shared resource.

### `pthread_mutex_destroy`

- **Usage**: `pthread_mutex_destroy(&mutex);`
- Destroys a mutex, releasing its resources.

