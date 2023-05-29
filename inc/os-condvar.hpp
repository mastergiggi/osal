/*
 * Copyright (c) 2023 Stefan Giggenbach (https://github.com/mastergiggi)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef OS_CONDVAR_HPP
#define OS_CONDVAR_HPP

#include <functional>
#include <string_view>

#include "os.hpp"
#include "os-mutex.hpp"
#include "pimpl.hpp"

namespace OS
{

class Condvar
{
public:
    using Predicate = std::function<bool()>;

    Condvar();
    ~Condvar();

    void create();
    void destroy();

    void signal();
    void broadcast();
    bool wait(const Predicate, LockGuard&, const Timeout timeout = WaitMax);

private:
    class impl;
    pimpl<impl> handle;
};

} // namespace OS

#endif // OS_CONDVAR_HPP
