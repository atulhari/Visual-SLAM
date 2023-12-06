# xauth_list=$(xauth nlist $DISLAY)
# if [ ! -z "$xauth_list" ]; then
#     xauth nlist $DISLAY | sed -e 's/^..../ffff/'  | xauth -f /tmp/.docker.xauth nmerge - 
# fi

# docker run --rm -it \
#  -e DISLAY=$DISLAY \
#  -e XAUTORITY=$/tmp/.docker.xauth \
#  -v /tm/.x11-uniix

docker run -v E:\Projects2023\Visual-SLAM\VslamOne -c "mkdir VslamOneDeployed && cd VslamOneDeployed && cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .. && make -j12"
