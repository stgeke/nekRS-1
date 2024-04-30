FROM ubuntu:20.04

RUN apt -y update && apt install -y mpich libmpich-dev cmake

RUN useradd -ms /bin/bash nekrs
USER nekrs
WORKDIR /home/nekrs

ENV NEKRS_HOME: "/home/nekrs/.local/nekrs" \
    MPICH_FC: "gfortran" \
    NEKRS_EXAMPLES: "/home/nekrs/.local/nekrs/examples" \
    ENABLE_CUDA: "0" \
    ENABLE_HIP: "0" \
    NEKRS_COMPILER_FLAGS: "-O2 -march=x86-64-v3" \
    OCCA_CXXFLAGS: "-O2" \
    NEKRS_OCCA_MODE_DEFAULT: "SERIAL" \
    NRSCONFIG_NOBUILD: "1" \
    RUNNER_ARCH: "X64"

COPY . /home/nekrs/build/nekrs

RUN CC=mpicc CXX=mpic++ FC=mpif77 ./nrsconfig -DENABLE_CVODE=ON -DCMAKE_INSTALL_PREFIX=${{ env.NEKRS_HOME }} && \
    cmake --build build --target install -j 2