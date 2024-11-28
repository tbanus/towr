# Use the official Ubuntu 20.04 as a base image
FROM ubuntu:18.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && apt-get install -y \
    lsb-release \
    gnupg2 \
    curl \
    wget \
    git \
    build-essential \
    cmake \
    libeigen3-dev \
    coinor-libipopt-dev \
    python3-pip

# Setup ROS melodic repository
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -cs) main" > /etc/apt/sources.list.d/ros-melodic.list'
RUN curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add -

# Install ROS melodic and required packages
RUN apt-get update && apt-get install -y \
    ros-melodic-desktop-full \
    ros-melodic-ifopt \
    ros-melodic-towr-ros

# Source ROS melodic setup script
RUN echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
SHELL ["/bin/bash", "-c", "source /opt/ros/melodic/setup.bash"]

# Install additional Python dependencies
# RUN pip3 install --upgrade pip

# Attach volume
VOLUME ["/home/banus/towr:/app"]

# Set the working directory
WORKDIR /app

# Create a symlink to the TOWR project

# Build the workspace
# RUN /bin/bash -c "source /opt/ros/foxy/setup.bash && colcon build"

# Set the entrypoint
# ENTRYPOINT ["/bin/bash", "-c", "source /opt/ros/foxy/setup.bash && source /home/ros_ws/install/setup.bash && bash"]