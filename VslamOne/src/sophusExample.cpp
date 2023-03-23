#include <cmath>
#include <iostream>
#include "sophus/se3.hpp"
#include <Eigen/Core>
#include <Eigen/Geometry>

int main(int argc, char **argv)
{
    // This code is an example of how to use the sophus library 
    // Sophus can be constructed from a Rotation matrix or a quaternion

    // creating a rotation matrix from a vector with 90degree along the z axis.
    Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI/2,Eigen::Vector3d(0,0,1)).toRotationMatrix();
    // creating a quaternion
    Eigen::Quaterniond q(R);

    // A sophus can be made from either a rotation matrix
    Sophus::SO3d SO3_R(R);
    // or a quaternion matrix 
    Sophus::SO3d SO3_q(q);

    // And both are equivallent
    std::cout<<"Sophus from Rotaion matrix:"<<SO3_R.matrix()<<std::endl;
    std::cout<<"Sophus from quaternion:"<<SO3_q.matrix()<<std::endl;

    // To get the lie Algebra we take the log 
    Eigen::Vector3d so3 = SO3_R.log();
    std::cout<<"Vector so3="<<so3.transpose()<<std::endl;


    // To get a  skew-symmetric matrix from vector we can do hat
    std::cout<<"Skew symmetric matrix="<<Sophus::SO3d::hat(so3)<<std::endl;

    // To go from matrix to vector you could use vee hat 
    std::cout<<"Matrix to vec"<<Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose()<<std::endl;

    // Applying pertubation
    Eigen::Vector3d update_so3(1e-4,0,0);
    Sophus::SO3d SO3_updated = Sophus::SO3d::exp(update_so3)*SO3_R;
    std::cout<<"The pertubed so3="<<SO3_updated.matrix()<<std::endl;
    
    std::cout<<"******************************"<<std::endl;

    // Doing the same for SE3 
   // TO DO





}