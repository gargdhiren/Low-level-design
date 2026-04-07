#include<bits/stdc++.h>
using namespace std;

class WalkBehaviour{
    public:
    virtual void walk()=0;
};

class SlowWalkBehaviour:public WalkBehaviour{
    public:
    void walk() override{
        cout<<"This robot walks slow."<<endl;
    }
};

class FastWalkBehaviour:public WalkBehaviour{
    public:
    void walk() override{
        cout<<"This robot walks fast."<<endl;
    }
};


class TalkBehaviour{
    public:
    virtual void talk()=0;
};

class QuietTalkBehaviour:public TalkBehaviour{
    public:
    void talk() override{
        cout<<"This robot is quiet it does not talk."<<endl;
    }
};

class LoudTalkBehaviour:public TalkBehaviour{
    public:
    void talk() override{
        cout<<"This robot talks loudly."<<endl;
    }
};

class Robot{
    WalkBehaviour *w;
    TalkBehaviour *t;

    public:
    Robot(WalkBehaviour *w,TalkBehaviour *t){
        this->w=w;
        this->t=t;
    }

    void walk(){
        w->walk();
    }

    void talk(){
        t->talk();
    }

    virtual void projection(){
        cout<<"This is how robot looks"<<endl;
    }
};

int main(){
    Robot *robot=new Robot(new FastWalkBehaviour(),new LoudTalkBehaviour());
    Robot *robot1=new Robot(new SlowWalkBehaviour(),new QuietTalkBehaviour());

    robot->walk();
    robot->talk();

    cout<<"*****Second robot*****"<<endl;

    robot1->walk();
    robot1->talk();

    return 0;
}


