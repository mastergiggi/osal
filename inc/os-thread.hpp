/*
 * Copyright (c) 2023 Stefan Giggenbach (https://github.com/mastergiggi)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef OS_THREAD_HPP
#define OS_THREAD_HPP

#include <cstddef>
#include <functional>
#include <string_view>

#include "os.hpp"
#include "pimpl.hpp"

namespace OS
{

class Thread
{
public:
    using StackSize = std::size_t;
    using Priority = std::uint32_t;

    struct Config
    {
        StackSize stackSize;
        Priority prio;
        Name name;
    };

    using Param = void*;
    using Function = std::function<void(Param)>;

    Thread();
    ~Thread();

    void create(Function, Param, const Config&);
    void destroy();

    void join();
    void suspend();
    void resume();

    static void sleep(const Timeout timeout);
    static void msleep(const Timeout timeout);
    static void usleep(const Timeout timeout);

    static void yield();

private:
    class impl;
    pimpl<impl> handle;
};

} // namespace OS

#endif // OS_THREAD_HPP
