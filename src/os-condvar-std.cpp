/*
 * Copyright (c) 2023 Stefan Giggenbach (https://github.com/mastergiggi)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cassert>
#include <chrono>
#include <memory>
#include <condition_variable>

#include "os-condvar.hpp"
#include "os-mutex-std.hpp"
#include "pimpl-impl.hpp"

class OS::Condvar::impl
{
public:
    void create()
    {
        condvar.reset(new std::condition_variable());
    }

    void destroy()
    {
        condvar.reset(nullptr);
    }

    void signal()
    {
        assert(condvar);
        condvar->notify_one();
    }

    void broadcast()
    {
        assert(condvar);
        condvar->notify_all();
    }

    bool wait(const Predicate predicate, LockGuard& lock, const Timeout timeout)
    {
        assert(condvar);
        return condvar->wait_for(lock.handle->getLock(), std::chrono::milliseconds(timeout), predicate);
    }

private:
    std::unique_ptr<std::condition_variable> condvar;
};

OS::Condvar::Condvar() = default;
OS::Condvar::~Condvar() = default;

void OS::Condvar::create()
{
    handle->create();
}

void OS::Condvar::destroy()
{
    handle->destroy();
}

void OS::Condvar::signal()
{
    handle->signal();
}

void OS::Condvar::broadcast()
{
    handle->broadcast();
}

bool OS::Condvar::wait(const Predicate predicate, LockGuard& lock, const Timeout timeout)
{
    return handle->wait(predicate, lock, timeout);
}
