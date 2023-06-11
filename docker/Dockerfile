# Start from a base image
FROM ubuntu:latest

# unminimize
RUN	yes | unminimize

# Install necessary tools
RUN apt-get update && \
    apt-get install -y bash-completion ccache gcc gdb git make man-db python3 python3-pip universal-ctags vim xorg 

# Set the working directory
WORKDIR /usr/src/app

# Copy all the files from the host to the container
# COPY . .

# Install necessary libraries
RUN apt-get install -y libx11-dev libxext-dev libbsd-dev

# Install Python packages
RUN	python3 -m pip install norminette

# Default command to run when starting a container from this image
CMD ["bash"]

