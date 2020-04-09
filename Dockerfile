# Pull base image.
FROM python:3.6-slim-buster

# Set environment variables.
ENV HOME /root
ENV PATH "/root/bin:${PATH}"

# Define working directory.
WORKDIR /root

# Install.
RUN \
    apt-get update && \
    apt-get -y install software-properties-common \
    sudo \
    wget \
    unzip \
    gcc \
    g++ \
    build-essential \
    python3-distutils \
    pkg-config \
    zip \
    zlib1g-dev \
    git && \
    wget https://github.com/bazelbuild/bazel/releases/download/2.1.0/bazel-2.1.0-installer-linux-x86_64.sh && \
    chmod +x bazel-2.1.0-installer-linux-x86_64.sh && \
    ./bazel-2.1.0-installer-linux-x86_64.sh --user && \
    export PATH="$PATH:$HOME/bin" && \
    rm bazel-2.1.0-installer-linux-x86_64.sh

# get third-party dependencies
WORKDIR /tmp/third_party

RUN git clone https://github.com/google/differential-privacy.git && \
    git clone https://github.com/pybind/pybind11_bazel.git

WORKDIR /root/PyDP
COPY . /root/PyDP

RUN cp -r /tmp/third_party/* /root/PyDP/third_party

RUN \
    bash build_PyDP.sh && \
    python3 setup.py sdist bdist_wheel && \
    pip install dist/pydp-0.1.0-py2.py3-none-any.whl && \
    pip install -r requirements_dev.txt

# Define default command.
CMD ["bash"]
