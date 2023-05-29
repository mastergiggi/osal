/*
 * Copyright (c) 2023 Stefan Giggenbach (https://github.com/mastergiggi)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef OS_HPP
#define OS_HPP

#include <cstdint>
#include <limits>

namespace OS
{
    using Size = std::size_t;
    using Name = std::string_view;
    using Timeout = std::uint32_t;
    inline constexpr std::uint32_t WaitNone = std::numeric_limits<uint32_t>::min();
    inline constexpr std::uint32_t WaitMax = std::numeric_limits<uint32_t>::max();
}

#endif // OS_HPP
