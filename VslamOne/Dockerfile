# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# Get the base Ubuntu image from Docker Hub
FROM ubuntu:20.04
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
# FROM debian:latest
ENV TZ=US \
    DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install tzdata

RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y \
    cmake sudo ninja-build \
    libeigen3-dev
ENV PROJECT_DIR=/VslamOne
ENV LD_LIBRARY_PATH /usr/local/bin
WORKDIR ${PROJECT_DIR}/lib

# These commands copy your files into the specified directory in the image
# and set that as the working location
RUN apt-get update && \
    apt-get install -y \
    libglew-dev \
    libpython2.7-dev \
    libboost-dev \
    libboost-thread-dev \
    libxi-dev \
    libxmu-dev \
    libglu1-mesa-dev \
    libjpeg-dev \
    cmake \
    build-essential \ 
    libgl1-mesa-dev \
    libglew-dev \
    git \
    software-properties-common\
    liblapack-dev\
    libsuitesparse-dev\
    libcxsparse3\
    libgflags-dev\
    libgoogle-glog-dev\
    libgtest-dev\
    # qt5-qmake\
    # qt5-default\
    libqglviewer-dev-qt5
    # libcholmod3

# Clone Pangolin from Github and build it
RUN git clone https://github.com/stevenlovegrove/Pangolin.git
RUN cd Pangolin && git checkout tags/v0.6
RUN cd Pangolin && mkdir build && cd build && \
    cmake .. && \
    cmake --build . && sudo make install && ldconfig

RUN git clone https://github.com/fmtlib/fmt.git
RUN cd fmt &&  mkdir build && cd build && \
    cmake .. && \
    cmake --build . && sudo make install

RUN git clone  https://github.com/strasdat/Sophus.git
# RUN cd Sophus && git checkout tags/v0.9.5
RUN cd Sophus && mkdir build && cd build && \
    cmake ..  -DUSE_BASIC_LOGGING=ON -DBUILD_SOPHUS_TESTS=OFF -DBUILD_SOPHUS_EXAMPLES=OFF && \
    make && sudo make install

RUN git clone https://github.com/RainerKuemmerle/g2o.git
RUN cd g2o && mkdir build && cd build && \
    cmake .. && \
    cmake --build . && sudo make install  && ldconfig

RUN git clone --recursive https://github.com/ceres-solver/ceres-solver
RUN cd ceres-solver && mkdir build && cd build && \
    cmake .. && \
    cmake --build . && sudo make install 

RUN sudo add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main" && \
    sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 40976EAF437D05B5 && \
    sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 3B4FE6ACC0B21F32 && \
    apt-get update && apt-get -f install -y \
    build-essential cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libvtk7-dev libpng-dev \
    gfortran libopenmpi-dev libopenmpi3 libcoarrays-dev libcoarrays-openmpi-dev \
    libtiff-dev libopenexr-dev libtbb-dev

RUN git clone https://github.com/opencv/opencv.git && \
    cd opencv && \
    git checkout 4.2.0 && \
    mkdir build && \
    cd build && \
    cmake \
    -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_C_EXAMPLES=ON \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D WITH_TBB=ON \
    -D WITH_V4L=ON \
    -D WITH_QT=OFF \
    -D WITH_OPENGL=ON \
    -D BUILD_EXAMPLES=ON .. && \
    make -j$(nproc) && \
    make install && \
    cd ../.. && \
    rm -rf opencv

CMD ["/bin/bash"]
LABEL Name=vslam Version=0.0.1
