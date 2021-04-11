// ======================================================================
// == DO NOT MODIFY THIS FILE BY HAND
// ======================================================================
#include "Socket.h"
#include <stdio.h>
#include <string>
#include "Socket.h"
#include "Address.h"
#include "robot.h"
#include <cstdlib>


Socket::Socket()
{

}

Socket::~Socket()
{

}

bool Socket::Open( unsigned short port )
{
    this->handle = socket( AF_INET,
                     SOCK_DGRAM,
                     IPPROTO_UDP );

    if ( this->handle <= 0 )
    {
        printf( "failed to create socket\n" );
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( (unsigned short) port );

    if ( bind( this->handle,
               (const sockaddr*) &address,
               sizeof(sockaddr_in) ) < 0 )
    {
        printf( "failed to bind socket\n" );
        return false;
    }
    printf( "Listening on port %d\n", port );


    #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

    int nonBlocking = 1;
    if ( fcntl( this->handle,
                F_SETFL,
                O_NONBLOCK,
                nonBlocking ) == -1 )
    {
        printf( "failed to set non-blocking\n" );
        return false;
    }

    #elif PLATFORM == PLATFORM_WINDOWS

    DWORD nonBlocking = 1;
    if ( ioctlsocket( handle,
                      FIONBIO,
                      &nonBlocking ) != 0 )
    {
        printf( "failed to set non-blocking\n" );
        return false;
    }

    #endif

    return true;
}

void Socket::Close()
{
    #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    close( this->handle );
    #elif PLATFORM == PLATFORM_WINDOWS
    closesocket( this->handle );
    #endif
}

bool Socket::IsOpen() const
{
    return this->handle > 0;
}

bool Socket::Send( const Address & destination,
               const void * packet_data,
               int packet_size )
{
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl( destination.GetAddress() );
    addr.sin_port = htons( destination.GetPort() );

    int sent_bytes =
        sendto( this->handle,
                (const char*)packet_data,
                packet_size,
                0,
                (sockaddr*)&addr,
                sizeof(sockaddr_in) );

    if ( sent_bytes != packet_size )
    {
        printf( "failed to send packet\n" );
        return false;
    }

    return true;
}


int Socket::Receive( Address & sender,
                     void * packet_data,
                     int max_packet_size )
{
    #if PLATFORM == PLATFORM_WINDOWS
    typedef int socklen_t;
    #endif

    sockaddr_in from;
    socklen_t fromLength = sizeof( from );

    int bytes = recvfrom( this->handle,
                          (char*)packet_data,
                          max_packet_size,
                          0,
                          (sockaddr*)&from,
                          &fromLength );

    unsigned int from_address =
        ntohl( from.sin_addr.s_addr );

    unsigned int from_port =
        ntohs( from.sin_port );

    sender = Address(from_address, from_port);

    return bytes;
}





Socket sock;


void Junior_Soccer_Simulation::Robot_Init()
{
    InitializeSockets();
    CreateSocket();
}
bool Junior_Soccer_Simulation::InitializeSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
    WSADATA WsaData;
    return WSAStartup(MAKEWORD(2, 2),
        &WsaData)
        == NO_ERROR;
#else
    return true;
#endif
}

void Junior_Soccer_Simulation::ShutdownSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
    WSACleanup();
#endif
}


void Junior_Soccer_Simulation::CreateSocket()
{
    if (!sock.Open(Robot.port))
    {
        printf("failed to open socket!\n");
    }
}

void Junior_Soccer_Simulation::SendPacket(const char data[], const int len)
{
    sock.Send(Address(127, 0, 0, 1, Robot.sendToPort), data, len);
}

void Junior_Soccer_Simulation::ReceivePackets()
{
//    while (true)
//   {
        Address sender;
        unsigned char buffer[max_buffer_size];
        int bytes_read =
            sock.Receive(sender,
                buffer,
                sizeof(buffer));

        if (buffer > 0)
        {
            const char* packet_data = (const char*)buffer;
            memcpy(Robot.receive, buffer, sizeof Robot.receive);
            #if  print_recive_data_on_console
            printf("%d: %s\n", bytes_read, packet_data);
            #endif /// print_recive_data_on_console
        }
}

bool Junior_Soccer_Simulation::ParseCmdLine(int argc, char** argv)
{
    for (int i = 0; i < argc; i++)
    {
        std::string argStr = std::string(argv[i]);
        if (argStr == "--port" || argStr == "-p")
        {
            std::string portStr = std::string(argv[i + 1]);
            Robot.port = strtol(portStr.c_str(),0,10);
        }
        else if (argStr == "--sendto" || argStr == "-st")
        {
            std::string portStr = std::string(argv[i + 1]);
            Robot.sendToPort = strtol(portStr.c_str(),0,10);
        }
        else if (argStr == "--send" || argStr == "-s")
        {
            Robot.sending = true;
        }
    }
    return true;
}
void Junior_Soccer_Simulation::send_udp()
{
    SendPacket(Robot.send, sizeof(Robot.send));
    #if print_send_data_on_console
    printf("Sent data: %s\n", Robot.send);
    #endif // print_send_data_on_console
}
void Junior_Soccer_Simulation::receive_udp()
{
    char hsb[1]={Robot.receive_hsb};
     SendPacket(hsb, sizeof(hsb));
    ReceivePackets();
}




