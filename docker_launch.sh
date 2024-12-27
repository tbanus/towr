docker run -it --rm \
    -e DISPLAY=$DISPLAY \
    -e XAUTHORITY=/tmp/.docker.xauth \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v $XAUTHORITY:/tmp/.docker.xauth \
    -v /home/$USER/towr_ws/towr:/app \
    --net=host \
    towr:1205

# roslaunch towr_ros towr_ros.launch