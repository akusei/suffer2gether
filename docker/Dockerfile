FROM ubuntu:latest

ENV PATH="${PATH}:/usr/local/cmake/bin"


RUN apt-get update && apt-get -qy install build-essential curl zig unzip && \
    cd /tmp && \
    curl -sS -L -O https://github.com/Kitware/CMake/releases/download/v4.3.3/cmake-4.3.3-linux-x86_64.tar.gz && \
    tar -zxvf ./cmake-4.3.3-linux-x86_64.tar.gz && \
    mkdir -p /usr/local/cmake && \
    mv ./cmake-4.3.3-linux-x86_64/* /usr/local/cmake/ && \
    curl -sS -L -O https://github.com/ninja-build/ninja/releases/download/v1.13.2/ninja-linux.zip && \
    unzip -d /usr/local/bin ./ninja-linux.zip


VOLUME /workspace

WORKDIR /workspace
