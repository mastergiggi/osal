/*
 * Copyright (c) 2023 Stefan Giggenbach (https://github.com/mastergiggi)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef OS_QUEUE_HPP
#define OS_QUEUE_HPP

#include <cassert>
#include <cstddef>
#include <deque>
#include <optional>
#include <string_view>

#include "os.hpp"
#include "os-condvar.hpp"
#include "os-mutex.hpp"

namespace OS
{

template<typename T>
class Queue
{
public:
    void create(const Size size_, const Name = "")
    {
        queue.reset(new std::deque<T>);
        mutex.create();
        condvar.create();
        maxSize = size_;
    }

    void destroy()
    {
        condvar.destroy();
        mutex.destroy();
        queue.reset(nullptr);

    }

    bool append(const T& item, const Timeout timeout = WaitMax)
    {
        assert(queue);
        bool success = false;

        LockGuard lock(mutex);

        if (size < maxSize)
        {
            queue->push_back(item);
            ++size;
            condvar.signal();
            success = true;
        }

        return success;
    }

    bool unique_append(const T&, const Timeout timeout = WaitMax);
    template<typename ...Args>
    bool append_emplace(Args && ...args, Timeout timeout = WaitMax);

    bool prepend(const T&, const Timeout timeout = WaitMax);
    bool unique_prepend(const T&, const Timeout timeout = WaitMax);
    template<typename ...Args>
    bool prepend_emplace(Args && ...args, Timeout timeout = WaitMax);

    bool peek(T&, const Timeout timeout = WaitMax);
    std::optional<T> peek(const Timeout timeout = WaitMax);

    bool get(T& item, const Timeout timeout = WaitMax)
    {
        assert(queue);
        bool success = false;

        LockGuard lock(mutex);

        if (condvar.wait([this]() { return not queue->empty(); }, lock, timeout))
        {
            item = queue->front();
            queue->pop_front();
            --size;
            success = true;
        }

        return success;
    }

    std::optional<T> get(const Timeout timeout = WaitMax);
    bool remove();

    bool full()
    {
        assert(queue);
        return not (size == maxSize);
    }

    bool empty()
    {
        assert(queue);
        return queue->empty();
    }

private:
    std::unique_ptr<std::deque<T>> queue;
    Mutex mutex;
    Condvar condvar;
    Size maxSize{ 0U };
    Size size{ 0U };
};

} // namespace OS

#endif // OS_QUEUE_HPP
