#include "explosionChain.hpp" 
#include <iostream> 
#include "kdl/chainfksolverpos_recursive.hpp" 
#include "kdl/frames_io.hpp" 
#include "kdl/models.hpp" 
int main(int argc, char *argv[])
{
    KDL::Chain *p = KDL::ExpYuede(); 
    KDL::Chain chain;
	chain = KDL::Puma560();
    KDL::ChainFkSolverPos_recursive fksolver(*p)  ;
    KDL::ChainFkSolverPos_recursive fksolverPuma560(chain)  ;
    KDL::Frame pos_goal;
    unsigned int nj = p->getNrOfJoints(); //获取机器人的关节数目
    KDL::JntArray myinput(nj);  //定义一个关节空间量，长度是机器人的关节数
    for (unsigned int i = 0; i < nj; ++i) { //从外部读入关节量
        std::cin>>myinput.data(i); 
    } 
    
    fksolver.JntToCart(myinput,pos_goal,nj);
    std::cout<<"pos "<<pos_goal.p[0]<<"\n"<<pos_goal.p[1]<<"\n"<<pos_goal.p[2]<<
        "\n"<<"rotation "<<pos_goal.M<<std::endl;
     
    fksolverPuma560.JntToCart(myinput,pos_goal,nj);
    std::cout<<"pos "<<pos_goal.p[0]<<"\n"<<pos_goal.p[1]<<"\n"<<pos_goal.p[2]<<
        "\n"<<"rotation "<<pos_goal.M<<std::endl;
    delete p;

}
