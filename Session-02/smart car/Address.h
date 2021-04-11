// ======================================================================
// == DO NOT MODIFY THIS FILE BY HAND
// ======================================================================
//
// Address.h - #version 1.1
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
//
// =================================================================================================
// =================================================================================================
// =================================================================================================
#ifndef ADDRESS_H
#define ADDRESS_H

class Address
{
public:

    Address();
    Address(unsigned char a,
        unsigned char b,
        unsigned char c,
        unsigned char d,
        unsigned short port);
    Address(unsigned int address,
        unsigned short port);
    unsigned int GetAddress() const;
    unsigned short GetPort() const;

    // unsigned char GetA() const;
    // unsigned char GetB() const;
    // unsigned char GetC() const;
    // unsigned char GetD() const;

private:
    void init(unsigned int address, unsigned short port);
    unsigned int address;
    unsigned short port;
};

#endif
