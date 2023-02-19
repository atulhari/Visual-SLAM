# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# Get the base Ubuntu image from Docker Hub
# FROM ubuntu:latest
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM gcc:latest

RUN apt-get update && apt-get install -y cmake \
libeigen3-dev

# These commands copy your files into the specified directory in the image
# and set that as the working location
ENV PROJECT_DIR = /VslamOne
WORKDIR ${PROJECT_DIR}

# Copy the CMakeLists.txt file to the working directory
COPY CMakeLists.txt .

# Copy the include and src folders to the working directory
COPY include/ include/
COPY src/ src/

RUN mkdir VslamOneDeployed && cd VslamOneDeployed && cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..

# ENTRYPOINT [ "/bin/bash" ]

RUN cd VslamOneDeployed && make
# CMD ["./VslamOneDeployed/target/slamIntro"]
CMD ["./VslamOneDeployed/target/eigenMatrix"]

LABEL Name=vslam Version=0.0.1
