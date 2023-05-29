/*
 * Copyright (c) 2023 Stefan Giggenbach (https://github.com/mastergiggi)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cassert>
#include <cstdlib>
#include <iostream>

#include "os-thread.hpp"
#include "os-queue.hpp"

constexpr OS::Thread::Config threadConfig =
{
    0,
    0,
    ""
};

constexpr OS::Timeout SendDelay = 1000;
constexpr OS::Timeout ReceiveDelay = 2000;
constexpr OS::Timeout ReceiveTimeoutMs = 2000;
constexpr OS::Size QueueSize = 5;
constexpr int NumItems = 10;
OS::Queue<int> myQueue;

void send(OS::Thread::Param)
{
    for (int item = 0; item < NumItems; ++item)
    {
        OS::Thread::msleep(SendDelay);

        if (myQueue.append(item))
        {
            std::cout << "Append item " << item << " to queue..." << std::endl;
        }
        else
        {
            std::cout << "Append item to queue failed!" << std::endl;
        }
    }
}

void receive(OS::Thread::Param)
{
    int item;
    OS::Thread::msleep(ReceiveDelay);

    while (myQueue.get(item, ReceiveTimeoutMs))
    {
        OS::Thread::msleep(ReceiveDelay);
        std::cout << "Get item " << item << " from queue" << std::endl;
    }

    std::cout << "Get from queue timeout" << std::endl;
}

int main(int, char**)
{
    OS::Thread sender;
    OS::Thread receiver;

    myQueue.create(QueueSize);
    sender.create(send, nullptr, threadConfig);
    receiver.create(receive, nullptr, threadConfig);

    sender.join();
    receiver.join();

    return EXIT_SUCCESS;
}
