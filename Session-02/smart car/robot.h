// robot.h - #version 1.1
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
#ifndef ROBOT_H
#define ROBOT_H


#define max_buffer_size 40
#define print_send_data_on_console false
#define print_recive_data_on_console false
class Junior_Soccer_Simulation
{
public:
    ////settings
    int port = 3000;
    int sendToPort = 8000;
    bool sending = true;
    char send[30];
    char receive_hsb = 's';
    char receive[max_buffer_size];
    ///////////

    ////sensor
    int cmp, distance_0, distance_1, distance_2, distance_3, speed, line, trafficLight, crossWalk;
    ////////////

    /////////////Robot
    void sensor(int Robot_ID);
    void sensor(void);
    void send_2_robot(void);
    //////////////////

    /////simulation
    void Robot_Init(void);
    bool InitializeSockets();
    void ShutdownSockets(void);
    void CreateSocket(void);
    void SendPacket(const char data[], const int len);
    void ReceivePackets(void);
    bool ParseCmdLine(int argc, char** argv);
    void send_udp(void);
    void receive_udp();
    ////////////////
    void setSpeed(int v);
    void turnRight(void);
    void turnLeft(void);
    void setLine(int _line);
    void brake(bool brk);
    ////
    int set_line,set_speed,set_turn,set_brake;
    ////

private:

};
extern Junior_Soccer_Simulation Robot;


///////////////function
int read_cmp(void);
int read_distance_0(void);
int read_distance_1(void);
int read_distance_2(void);
int read_distance_3(void);
int read_speed(void);
int read_line(void);
int read_trafficLight(void);
int read_crossWalk(void);
////////////control function
void brake(void);

void right_line(void);
void left_line(void);
void delay_ms(int time);



#endif
