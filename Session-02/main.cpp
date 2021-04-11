#include "./smart car/robot.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    Robot.Robot_Init();
    Robot.setLine(1);
    while(Robot.crossWalk == 0) Robot.sensor();
    /// Path 1
    while(true)
    {
        Robot.sensor();
        if(Robot.crossWalk < 10)
        {
            Robot.setSpeed(0);
            Robot.brake(true);
            break;
        }
        else
        {
            Robot.brake(false);
            Robot.setSpeed(5);
        }
    }
    delay_ms(1000);
    Robot.sensor();
    while(Robot.trafficLight == 2)
        Robot.sensor();
    Robot.setSpeed(10);
    Robot.brake(false);
    delay_ms(1000);    /// Distance
    while(Robot.crossWalk < 20)
    {
        Robot.sensor();
        Robot.setSpeed(10);
        Robot.turnRight();
    }

    Robot.brake(true);
    delay_ms(1000);
    cout<<"Passed Intersection 1"<<endl;



}
