// ======================================================================
// == DO NOT MODIFY THIS FILE BY HAND
// ======================================================================
#include "robot.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <windows.h>
Junior_Soccer_Simulation Robot;
void Junior_Soccer_Simulation::sensor()
{

		receive_udp();
		std::string data(Robot.receive);
        if (receive_hsb == Robot.receive[0])// && teamat == Robot.receive[0])
		if (sizeof(Robot.receive) >= 10)
			{
                std::istringstream cmp(data.substr(1, 3));
                cmp >> Robot.cmp;
                std::istringstream distance_0(data.substr(4, 3));
                distance_0 >> Robot.distance_0;
                std::istringstream distance_1(data.substr(7, 3));
                distance_1 >> Robot.distance_1;
                std::istringstream distance_2(data.substr(10, 3));
                distance_2 >> Robot.distance_2;
                std::istringstream distance_3(data.substr(13, 3));
                distance_3 >> Robot.distance_3;
                std::istringstream speed(data.substr(16, 3));
                speed >> Robot.speed;
                std::istringstream line(data.substr(19, 1));
                line >> Robot.line;
                std::istringstream trafficLight(data.substr(20, 1));
                trafficLight >> Robot.trafficLight;
                std::istringstream crossWalk(data.substr(21, 3));
                crossWalk >> Robot.crossWalk;
			}
        Robot.receive[0]='n';
}
void Junior_Soccer_Simulation::send_2_robot()
{
	Robot.send[0] = 'c';
	Robot.send[1] = '0' + ((Robot.set_speed / 100) % 10);
	Robot.send[2] = '0' + (((Robot.set_speed / 10)) % 10);
	Robot.send[3] = '0' + (Robot.set_speed % 10);
	Robot.send[4] = '0' + (Robot.set_brake % 10);
	Robot.send[5] = '0' + (Robot.set_turn % 10);
	Robot.send[6] = '0' + (Robot.set_line % 10);
	send_udp();
}
////////////////////////////


///////////////////function
int read_cmp()
{
    return Robot.cmp;
}
int read_distance_0()
{
    return Robot.distance_0;
}
int read_distance_1()
{
    return Robot.distance_1;
}
int read_distance_2()
{
    return Robot.distance_2;
}
int read_distance_3()
{
    return Robot.distance_3;
}
int read_speed()
{
    return Robot.speed;
}
int read_line()
{
    return Robot.line;
}
int read_trafficLight()
{
    return Robot.trafficLight;
}
int read_crossWalk()
{
    return Robot.crossWalk;
}
void Junior_Soccer_Simulation::setSpeed(int v)
{
    Robot.send[0] = 'v';
	Robot.send[1] = '0' + ((v / 100) % 10);
	Robot.send[2] = '0' + (((v / 10)) % 10);
	Robot.send[3] = '0' + (v % 10);
    send_udp();
    /*
    Robot.set_speed = v;
    Robot.set_brake = false;
    Robot.set_line = Robot.line;
    Robot.send_2_robot();
    */
}
void brake()
{
    Robot.set_brake = true;
    Robot.set_line = Robot.line;
    Robot.send_2_robot();
}
void Junior_Soccer_Simulation::turnRight()
{
    Robot.send[0] = 'R';
    send_udp();
}
void Junior_Soccer_Simulation::turnLeft()
{
    Robot.send[0] = 'L';
    send_udp();
}
void Junior_Soccer_Simulation::setLine(int _line)
{
    Robot.send[0] = 'd';
    Robot.send[1] = '0' + (_line % 10);
    send_udp();
}
void Junior_Soccer_Simulation::brake(bool brk)
{
    Robot.send[0] = 'b';
    if(brk) Robot.send[1] = 'T';
    else    Robot.send[1] = 'F';
    send_udp();
}

void right_line()
{
    (Robot.set_line<4)?Robot.set_line++ : Robot.set_line = 3;
    Robot.set_line++;
    Robot.set_brake = false;
    Robot.send_2_robot();
}
void left_line()
{
    (Robot.set_line>-1)?Robot.set_line-- : Robot.set_line = 0;
    Robot.set_brake = false;
    Robot.send_2_robot();
}
void delay_ms(int time)
{
    Sleep(time);
}

