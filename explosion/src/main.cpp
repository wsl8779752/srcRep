#include "explosionChain.hpp" 
#include <iostream> 
#include <kdl/chainfksolverpos_recursive.hpp> 
#include <kdl/frames_io.hpp> 
int main(int argc, char *argv[])
{
    KDL::Chain *p = KDL::ExpYuede(); 
    KDL::ChainFkSolverPos_recursive fksolver(*p)  ;
    KDL::JntArray myinput(6);
    KDL::Frame pos_goal;
    fksolver.JntToCart(myinput,pos_goal,6);
    std::cout<<"pos "<<pos_goal.p[0]<<"\n"<<pos_goal.p[1]<<"\n"<<pos_goal.p[2]<<
        "\n"<<"rotation "<<pos_goal.M<<std::endl;
}
