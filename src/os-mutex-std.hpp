/*
 * Copyright (c) 2023 Stefan Giggenbach
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cassert>
#include <chrono>
#include <mutex>

class OS::Mutex::impl
{
friend class LockGuard;

public:
    void create()
    {
        mutex.reset(new std::mutex());
    }

    void destroy()
    {
        mutex.reset(nullptr);
    }

    bool lock(const Timeout timeout)
    {
        assert(mutex);
        assert(timeout == WaitMax);
        mutex->lock();
        return true;
    }

    void unlock()
    {
        assert(mutex);
        mutex->unlock();
    }

private:
    std::unique_ptr<std::mutex> mutex;
};

class OS::LockGuard::impl
{
friend class Condvar;

public:
    impl(std::mutex& mutex)
        : lock(mutex)
    {
    }

    ~impl() = default;

private:
    std::unique_lock<std::mutex>& getLock()
    {
        assert(lock);
        return lock;
    }

    std::unique_lock<std::mutex> lock;
};
