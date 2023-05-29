
/*
 * Copyright (c) 2023 Stefan Giggenbach (https://github.com/mastergiggi)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "os-mutex.hpp"
#include "os-mutex-std.hpp"
#include "pimpl-impl.hpp"

OS::Mutex::Mutex() = default;
OS::Mutex::~Mutex() = default;

void OS::Mutex::create(const Type)
{
    handle->create();
}

void OS::Mutex::destroy()
{
    handle->destroy();
}

bool OS::Mutex::lock(const Timeout timeout)
{
    return handle->lock(timeout);
}

void OS::Mutex::unlock()
{
    handle->unlock();
}

OS::LockGuard::LockGuard(Mutex& mutex)
    : handle(*(mutex.handle->mutex))
{
}

OS::LockGuard::~LockGuard() = default;
