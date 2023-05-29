# Operating System Abstraction Layer

## Introduction

The main goal of this project is to use the pimpl-idiom to hide implementation
details in the header file located declartions. The disclosure of these details
is one of the biggest drawbacks of C++ and can heavily impact the architecture
and layering of the software system in a negative way.

Beside some other techniques like using forward declarations and references or
using interfaces by declaring pure virtual base classes, the pimpl-idiom is a
straight forward solution, which has it's roots in opaque pointers already used
in object oriented programming with the language C.

The pimpl implementation I use is heavily inspired by Herb Sutter's blog:
https://herbsutter.com/gotw/_100/
https://herbsutter.com/gotw/_101/

I want to implement an operating system abstraction layer using this idiom and
port it for various embedded (real-time) operating systems like FreeRTOS, MS
Azure RTOS and the Zephyr project's RTOS kernel.

## Implementation and usage

Currently I am developing a prototype using the C++17 thread support library,
providing the most basic OS resources

* Threads
* Mutexes
* Semaphores
* Conditional variables, which are already used implementing
* Queues

Every OS resource is represented by a class, which provides the interface and
hides the details using the pimpl-idiom. The resource itself is not created
during the construction of each class but during the create() call, which must
be called before every other method.
