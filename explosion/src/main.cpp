#include "explosionChain.hpp" 
#include <iostream> 
#include <kdl/chainfksolverpos_recursive.hpp> 
#include <kdl/frames_io.hpp> 
int main(int argc, char *argv[])
{
    KDL::Chain *p = KDL::ExpYuede(); //定义一个悦得机器人 
    KDL::ChainFkSolverPos_recursive fksolver(*p);//定义一个机器人正动力学解对象
    unsigned int nj = p->getNrOfJoints(); //获取机器人的关节数目
    KDL::JntArray myinput(nj);  //定义一个关节空间量，长度是越的机器人的关节数
    for (unsigned int i = 0; i < nj; ++i) { //从外部读入关节量
        std::cin>>myinput.data(i); 
    } 
    KDL::Frame pos_goal; //定义一个se(3)量pos_goal
    fksolver.JntToCart(myinput,pos_goal,6);//调用fksolver结算，结果存放到pos_goal
    std::cout<<"pos "<<pos_goal.p[0]<<"\n"<<pos_goal.p[1]<<"\n"<<pos_goal.p[2]<<
        "\n"<<"rotation "<<pos_goal.M<<std::endl;
    delete p;
}
