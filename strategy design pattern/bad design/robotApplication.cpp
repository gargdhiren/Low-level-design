#include<iostream>
using namespace std;

class Robot{
    public:
    
    virtual void walk(){
        cout<<"This robot can walk"<<endl;
    }

    virtual void projection(){
        cout<<"This is how robot looks"<<endl;
    }
};

class WorkerRobot:public Robot{
    public:

    void projection(){
        cout<<"This is a worker robot. And I look like worker";
    }
};


//This robot need flyingMethod
class flyingRobot:public Robot{
    public:
    virtual void fly(){
        cout<<"This robot can fly"<<endl;
    }

    virtual void projection(){
        cout<<"This robot has wings.";
    }
};

// inheritence to solve the problem. All the robots that can fly to inherit from flying robot. But this is endless loop.
class flyingTalkingRobot:public flyingRobot{
    public:
    virtual void talk(){
        cout<<"This robot can talk.";
    }

    virtual void projection(){
        cout<<"This robot has wings and mouth.";
    }
};

int main(){
    flyingTalkingRobot *robot=new flyingTalkingRobot();

    robot->fly();
    robot->projection();
    cout<<"\nThis is a bad design. We need to use strategy design pattern to solve this problem."<<endl;

    return 0;
};