/*
 * Copyright (c) 2023 Stefan Giggenbach (https://github.com/mastergiggi)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PIMPL_IMPL_HPP
#define PIMPL_IMPL_HPP

#include <utility>

template<typename T>
pimpl<T>::pimpl()
    : handle{ new T{} }
{
}

template<typename T>
template<typename ...Args>
pimpl<T>::pimpl(Args && ...args)
    : handle{ new T{ std::forward<Args> (args)... } }
{
}

template<typename T>
pimpl<T>::~pimpl()
{
}

template<typename T>
T* pimpl<T>::operator->()
{
    return handle.get();
}

template<typename T>
T& pimpl<T>::operator*()
{
    return *handle.get();
}

#endif // PIMPL_IMPL_HPP
