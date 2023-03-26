#ifndef DRAWTRAJECTORY_H_
#define DRAWTRAJECTORY_H_
#pragma once
#include <pangolin/pangolin.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <unistd.h>
#include "sophus/se3.hpp"

void DrawTrajectory(std::vector<Eigen::Isometry3d,
                                Eigen::aligned_allocator<Eigen::Isometry3d>>);
void DrawTrajectory(std::vector<Sophus::SE3d,
                                Eigen::aligned_allocator<Sophus::SE3d>>);
typedef std::vector<Sophus::SE3d, Eigen::aligned_allocator<Sophus::SE3d>>
    trajectoryType;
trajectoryType readTrajectory(const std::string &path);

#endif