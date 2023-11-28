FROM gcc:13

ARG DEFAULT_USERNAME=abc
ARG DEFAULT_UID=1000
ARG DEFAULT_GID=1000
ARG DEFAULT_DIRECTORY=/workspace

ENV VCPKG_ROOT=/tmp/vcpkg

# Set apt mirrors to GARR Italy network for better performance
RUN sed -i "s/deb.debian.org/debian.mirror.garr.it/g" /etc/apt/sources.list.d/debian.sources

# Install extra development dependencies
RUN apt-get --yes update && \
    export DEBIAN_FRONTEND=noninteractive && \
    apt-get --no-install-recommends --yes install \
      git \
      ca-certificates \
      curl zip unzip tar \
      gdb \
      valgrind \
      pkg-config \
      cmake \
      ninja-build \
      make \
      doxygen \
      graphviz \
      cppcheck \
      clang-15 \
      clang-tidy-15 \
      clang-format-15 \
      gcovr \
      passwd && \
    groupadd -g ${DEFAULT_GID} ${DEFAULT_USERNAME} && \
    useradd -m -g ${DEFAULT_GID} -u ${DEFAULT_UID} ${DEFAULT_USERNAME} && \
    mkdir ${DEFAULT_DIRECTORY} && chown ${DEFAULT_USERNAME}:${DEFAULT_USERNAME} ${DEFAULT_DIRECTORY} && \
    apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

RUN cd /usr/bin && ln -s clang-tidy-15 clang-tidy && \
    ln -s clang-format-15 clang-format && \
    ln -s clang-15 clang && \
    ln -s clang++-15 clang++

RUN mkdir ${VCPKG_ROOT} && chown ${DEFAULT_UID}:${DEFAULT_GID} ${VCPKG_ROOT}

USER ${DEFAULT_USERNAME}

RUN git clone https://github.com/microsoft/vcpkg ${VCPKG_ROOT} && \
    ${VCPKG_ROOT}/bootstrap-vcpkg.sh -disableMetrics

WORKDIR ${DEFAULT_DIRECTORY}