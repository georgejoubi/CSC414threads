# CSC414Threads

# Using Git and Github

1. Click on clone or download button then click on the right of the link to copy it
1. Open GitHub desktop and log in using your username/password
1. Select File->clone repository
1. Select your github repository and set the local directory
At this point you have a local copy of the files. Working with the files
depends on which IDE you use so it is up to you to import the files into an IDE.
Below i give instructions for Visual Studio C++ 2019 community edition, it is free so
you can save yourself the hassle and use it.

1. Open visual studio and select continue without code (bottom right)
1. Select File->New->Project from existing code. In the project file location select the directory
where you have cloned the github repository.
1. Type a project name then next
1. Project type select console application

Now you can make the necessary changes to the code (see below). When you are done use
github Desktop to commit your work. A commit saves a snapshot of the work you have done 
so far so it doesn't hurt to commit often. When you are satisfied with your work submit
it by  PUSHing the changes back to the server.

# Project

The project is in three parts. Each part has a few questions that you have to answer
and an implementation you have to code. Write the answer in the __place indicated in this file__.

## Part 1
Read the code in example1.cpp. It creates four threads: two to run the function doit
and the other two to run a function object. The four threads run concurrently with two
threads run doit() incrementing/decrementing the global variable _y_ and two threads
run function objects incrementing/decrementing the local variable _x_. From the output
you can see that there is data corruption since both _x_ and _y_ should be 0. To fix
this problem uncomment the line with ``` #define SYNC ```.
### Question
  
We learned that a mutex _m_ is locked with a wait(m), (in C++ it is ``` m.lock() ```) and
unlocked with signal(m) (in C++ it is ``` m.unlock() ```).
How is this done in example.cpp? What is a ``` lock_guard ``` ?. Write your answer here
by editing this file (no more that a few lines)

#### Answer

In the example code, we are using a mutex to give exclusive access to our common data which is x and y.
The lock_guard gives lets us create a lock on the mutex which is unlocked for us when the object is destroyed.
First, the lock_guard acts as a wait or a lock on the mutex, and tries to acquire access on it. When it does get
access it enters the code block we want and when the code is done the lock_guard is destroyed.
This happens when we get out of the scope of the function, the lock_guard destructor gets called and the mutex
is released. 

## Part 2

### Question

What is the difference between ``` std::mutex ``` and ``` std::shared_mutex ```?
Write your answer below
#### Answer

The std::shared_mutex acts very similar to a regular mutex except it has the option to give multiple threads access
to the shared resources at the same time. For example, there is no harm in multiple threads reading the resources,
however we only want one thread to write exclusively. We can do this by creating a shared_lock on the threads that 
read the data, thus giving access to all reader threads at the same time, however we give a unique_lock on the
threads that we want to have exclusive access, which in this example are writing threads, and this gives access
to only one thread while letting the others wait.

### Implementation

Implement the readers writers solution we discussed in class. Use **readersWriters.cpp** 
as a start. Do not **remove** any code just **add** synchronization code to fix the access
problem. As you might have guessed you need to use ``` std::shared_mutex ``` here.

## Part 3

### Question

Describe condition variables in C++ and how they used (a few lines)

#### Answer

Condition variables are a class in the c++ standard library used to block and resume threads based on a certain
condition. Condition variables need a mutex to work on, we pass the mutex to the condition variable object and it
will lock it when we call the wait on it. It will unblock the mutex when we call the notify function on it from
a different thread. We also pass it a condition called a predicate, which will be checked when the condition variable
is notified from a different thread. It will check the predicate, if it is true then the mutex will be locked and
the thread will proceed. If the predicate is false it will block and wait for another notify.

### Implementation 

Read the file **waitForOthers.cpp**. We have multiple threads running the **same** code
in function ``` void thread(std::string s) ```. Each thread runs through two parts: 
the first it prints "phase 1" and in the second it prints its name followed by 'done'.
Without synchronization these two phases can be interleaved among all threads as you 
can see by running this program. Use condition variables and mutex to synchronize theses 
threads as follows: no thread can start phase two until all threads have completed phase 1.
In terms of output, since we run 10  threads you must guarantee that there are 10 'phase 1' printouts before any 'done' printout.
The order in which threads print 'phase one' or 'done' does not matter as long as all print
'phase 1' before **any** of them prints 'done'.



