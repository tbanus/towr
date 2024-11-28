docker run -it --rm \
    -e DISPLAY=$DISPLAY \
    -e XAUTHORITY=/tmp/.docker.xauth \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v $XAUTHORITY:/tmp/.docker.xauth \
    --net=host \
    towr:ros

roslaunch towr_ros towr_ros.launch