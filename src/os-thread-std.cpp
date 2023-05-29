/*
 * Copyright (c) 2023 Stefan Giggenbach (https://github.com/mastergiggi)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cassert>
#include <chrono>
#include <memory>
#include <thread>

#include "os-thread.hpp"
#include "pimpl-impl.hpp"

class OS::Thread::impl
{
public:
    void create(Function function, Param param)
    {
        thread.reset(new std::thread(function, param));
    }

    void destroy()
    {
        thread.reset(nullptr);
    }

    void join()
    {
        assert(thread);
        thread->join();
    }

private:
    std::unique_ptr<std::thread> thread;
};

OS::Thread::Thread() = default;
OS::Thread::~Thread() = default;

void OS::Thread::create(Function function, Param param, const Config&)
{
    handle->create(function, param);
}

void OS::Thread::destroy()
{
    handle->destroy();
}

void OS::Thread::join()
{
    handle->join();
}

void OS::Thread::suspend()
{
    // suspend is not supported!
    assert(false);
}

void OS::Thread::resume()
{
    // resume is not supported!
    assert(false);
}

void OS::Thread::sleep(const Timeout timeout)
{
    std::this_thread::sleep_for(std::chrono::seconds(timeout));
}

void OS::Thread::msleep(const Timeout timeout)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
}

void OS::Thread::usleep(const Timeout timeout)
{
    std::this_thread::sleep_for(std::chrono::microseconds(timeout));
}

void OS::Thread::yield()
{
    std::this_thread::yield();
}
