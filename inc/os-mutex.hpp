/*
 * Copyright (c) 2023 Stefan Giggenbach (https://github.com/mastergiggi)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef OS_MUTEX_HPP
#define OS_MUTEX_HPP

#include <string_view>

#include "os.hpp"
#include "pimpl.hpp"

namespace OS
{

class Mutex
{
friend class LockGuard;
public:
    enum Type
    {
        Standard,
        Recursive
    };

    Mutex();
    ~Mutex();

    void create(const Type type = Standard);
    void destroy();

    bool lock(const Timeout timeout = WaitMax);
    void unlock();

private:
    class impl;
    pimpl<impl> handle;
};

class LockGuard
{
friend class Condvar;
public:
    LockGuard(Mutex& mutex_);
    ~LockGuard();

    LockGuard() = delete;
    LockGuard(LockGuard&) = delete;
    LockGuard& operator=(LockGuard&) = delete;
    LockGuard(LockGuard&&) = delete;
    LockGuard & operator=(LockGuard&&) = delete;

private:
    class impl;
    pimpl<impl> handle;
};

} // namespace OS

#endif // OS_MUTEX_HPP
