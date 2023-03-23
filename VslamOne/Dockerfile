# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# Get the base Ubuntu image from Docker Hub
# FROM ubuntu:20.04
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM gcc:latest

RUN apt-get update && apt-get install -y cmake sudo ninja-build \
    libeigen3-dev
ENV PROJECT_DIR=/VslamOne
ENV LD_LIBRARY_PATH /usr/local/bin
WORKDIR ${PROJECT_DIR}

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
    git

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
# Copy the CMakeLists.txt file to the working directory
COPY CMakeLists.txt .

COPY data/ data/
# Copy the include and src folders to the working directory
COPY include/ include/
COPY src/ src/

RUN mkdir VslamOneDeployed
RUN cd VslamOneDeployed && cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .. && make -j12

# ENTRYPOINT [ "/bin/bash" ]

# RUN cd VslamOneDeployed && make
# # CMD ["./VslamOneDeployed/target/slamIntro"]
# # CMD ["./VslamOneDeployed/target/eigenMatrix"]
# # CMD ["./VslamOneDeployed/target/eigenGeometry"]
# # CMD ["./VslamOneDeployed/target/coordinateTransform"]
# #CMD ["./VslamOneDeployed/target/plotTrajectory"]
CMD ["/bin/bash"]
LABEL Name=vslam Version=0.0.1
