#ifndef DRAWTRAJECTORY_H_
#define DRAWTRAJECTORY_H_

#include <pangolin/pangolin.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <unistd.h>

void DrawTrajectory(std::vector<Eigen::Isometry3d,
                                Eigen::aligned_allocator<Eigen::Isometry3d>>);

#endif