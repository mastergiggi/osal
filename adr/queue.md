# OS::Queue

## Status

proposed

## Context

To provide threadsafe transport of information from one thread to another a FIFO
like queue shall be implemented.

The queue shall be used with any user defined data and most important smart
pointers to dynamic allocated objects.

At the same time the queue shall hide all implementation details from the user.

## Decision

To provide a generic queue class, C++ templates are used. This results in a pub-
lic implementation located in the header file using STL's std::dequeue with the
Mutex and Condvar classes to hide the implementation details of the operating
system synchronization. The std::dequeue was preferred over the std::queue to
provide a fixed size during construction and to prepend data in front of the
queue.


## Consequences

The dependency from conditional variables to mutexes in generell and the de-
pendency to mutex locks in the C++ thread support library results in a strong
coupling of these implementations. Therefore friend class declaration chains

Condvar --- is friend of ---> LockGuard       --- is friend of ---> Mutex
\
Condvar --- is friend of ---> LockGuard::impl --- is freind of ---> Mutex::impl

are used to fullfill the strong coupling of the thread support library by hiding
all these details from the user.
