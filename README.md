# Philosophers Problem Project

This project addresses the famous Dining Philosophers Problem using both multithreading and multiprocessing techniques in C. The Dining Philosophers Problem is a classic synchronization problem in computer science.

## Table of Contents
- [Project Overview](#project-overview)
- [Technologies Used](#technologies-used)
- [Dining Philosophers Problem Explanation](#dining-philosophers-problem-explanation)
- [Solution Approaches](#solution-approaches)
  - [Using Threads with Mutexes](#using-threads-with-mutexes)
  - [Using Processes with Semaphores](#using-processes-with-semaphores)
- [Installation](#installation)
- [Usage](#usage)
  - [Multithreading Version](#multithreading-version)
  - [Multiprocessing Version](#multiprocessing-version)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Project Overview

The Dining Philosophers Problem simulates a scenario where a group of philosophers sit at a table with a fork between each pair. Philosophers alternate between thinking and eating. To eat, a philosopher must pick up the two forks on either side. This project implements the solution using:
- Multithreading with mutexes
- Multiprocessing with semaphores

## Technologies Used

- C programming language
- POSIX threads for multithreading
- POSIX processes for multiprocessing
- Mutexes for synchronization in the multithreading version
- Semaphores for synchronization in the multiprocessing version

## Dining Philosophers Problem Explanation

The Dining Philosophers Problem is a concurrency problem where five philosophers sit around a circular table. Each philosopher has a plate of spaghetti and needs two forks to eat it. The philosophers spend their time alternately thinking and eating. However, there are only five forks available, and each philosopher needs two forks to eat, leading to potential deadlock and starvation issues.

## Solution Approaches

### Using Threads with Mutexes

In the multithreading version, each philosopher is represented as a thread. Mutexes are used to control access to the forks. Each fork is associated with a mutex, and a philosopher must lock the mutex for the left and right forks before eating. This ensures that no two philosophers can pick up the same fork simultaneously.

#### Key Points:
- Each fork is protected by a mutex.
- Philosophers attempt to pick up the left and right forks (locking the corresponding mutexes).
- After eating, philosophers put down the forks (unlocking the mutexes).

### Using Processes with Semaphores

In the multiprocessing version, each philosopher is represented as a separate process. Semaphores are used to control access to the forks. A philosopher must wait on the semaphore for the left and right forks before eating. This ensures mutual exclusion and prevents deadlock.

#### Key Points:
- Each fork is protected by a semaphore.
- Philosophers attempt to pick up the left and right forks from a table with forks that are (unlike for threads) positioned at random.
- After eating, philosophers put down the forks (posting the semaphores).

