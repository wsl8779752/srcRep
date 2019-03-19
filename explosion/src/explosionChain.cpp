#include "explosionChain.hpp" 
#include "kdl/chain.hpp" 
#include <iostream>
#include <kdl/frames_io.hpp>
namespace KDL{
    Chain* ExpYuede(){
        Chain *expYuede = new Chain;
        //设置关节参数，选项依次为旋转轴，减速比，直线结构的offset，电机惯量，
        //阻尼（滑动摩擦系数），刚度
        expYuede->addSegment(Segment(Joint(Joint::RotZ,-62111,0,200e-6,1.48e-3,0), 
                    Frame::DH(0.0,M_PI_2,0.0,0.0), //a alpha  d theta;
                    //m,cog from origin,惯性张量擦书 
                    RigidBodyInertia(0,Vector::Zero(),RotationalInertia(0,0.35,0,0,0,0)))); 

        expYuede->addSegment(Segment(Joint(Joint::RotZ,107.815,0,200e-6,0.817e-3,0), 
                    Frame::DH(0.4318,0.0,0.0,0.0),
                    RigidBodyInertia(17.4,Vector(-.3638,.006,.2275),RotationalInertia(0.13,0.524,0.539,0,0,0))));

        expYuede->addSegment(Segment(Joint(Joint::RotZ,-53.7063,0,200e-6,1.38e-3,0),
                    Frame::DH(0.0203,-M_PI_2,0.15005,0.0),
                    RigidBodyInertia(4.8,Vector(-.0203,-.0141,.070),RotationalInertia(0.066,0.086,0.0125,0,0,0))));

        expYuede->addSegment(Segment(Joint(Joint::RotZ,76.0364,0,33e-6,71.2e-6,0),
                    Frame::DH(0.0,M_PI_2,0.4318,0.0),
                    RigidBodyInertia(0.82,Vector(0,.019,0),RotationalInertia(1.8e-3,1.3e-3,1.8e-3,0,0,0))));

        expYuede->addSegment(Segment(Joint(Joint::RotZ,71.923,0,33e-6,82.6e-6,0),
                    Frame::DH(0.0,-M_PI_2,0.0,0.0),
                    RigidBodyInertia(0.34,Vector::Zero(),RotationalInertia(.3e-3,.4e-3,.3e-3,0,0,0))));

        expYuede->addSegment(Segment(Joint(Joint::RotZ,76.686,0,33e-6,36.7e-6,0),
                    Frame::DH(0.0,0.0,0.0,0.0),
                    RigidBodyInertia(0.09,Vector(0,0,.032),RotationalInertia(.15e-3,0.15e-3,.04e-3,0,0,0))));

        return expYuede;
    }
}
