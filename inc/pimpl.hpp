/*
 * Copyright (c) 2023 Stefan Giggenbach (https://github.com/mastergiggi)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PIMPL_HPP
#define PIMPL_HPP

#include <memory>

template<typename T>
class pimpl
{
public:
    pimpl();
    template<typename ...Args>
    pimpl(Args&& ...);
    ~pimpl();
    T* operator->();
    T& operator*();

private:
    std::unique_ptr<T> handle;
};

#endif // PIMPL_HPP
