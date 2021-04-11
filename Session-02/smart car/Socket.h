// ======================================================================
// == DO NOT MODIFY THIS FILE BY HAND
// ======================================================================
//
// Sokcet.h - #version 1.1
//
// Copyright (c) 2021-2020 JuniorCup
//
// Distributed under the Iran Robotic Academy Software License
// See accompanying file at
// http://www.iranroboticacademy.com/
//
// The documentation can be found at the library's page:
// http://juniorcup.ir/
//
// =================================================================================================
// =================================================================================================
// =================================================================================================
//
// - C++ Code Write by Mohammad Hossein Zolfaghari
// - Simulation Write by Farhan daemi
// - socketWriter class - thanks to Luke Mekuls for allowing the direct reuse (AKA copy/paste)
//
// =================================================================================================
// =================================================================================================
// =================================================================================================
#ifndef SOCKET_H
#define SOCKET_H

// platform detection

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM PLATFORM_MAC
#else
#define PLATFORM PLATFORM_UNIX
#endif

#if PLATFORM == PLATFORM_WINDOWS

#include <winsock2.h>

#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

#endif

#if PLATFORM == PLATFORM_WINDOWS
#pragma comment( lib, "wsock32.lib" )
#endif

#include <stdio.h>
#include "Address.h"

class Socket
{
public:

    Socket();
    ~Socket();
    bool Open(unsigned short port);
    void Close();
    bool IsOpen() const;
    bool Send(const Address& destination,
        const void* data,
        int size);
    int Receive(Address& sender,
        void* data,
        int size);

private:
    int handle;
};

#endif
