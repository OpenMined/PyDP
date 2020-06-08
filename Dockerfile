# Pull base image.
ARG python_version
FROM python:${python_version}-slim-buster

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
# TODO: peg this dependency to particular version. Can pass args in for latest or stable etc
RUN git clone https://github.com/google/differential-privacy.git 
RUN pip3 install pipenv

WORKDIR /root/PyDP
COPY . /root/PyDP

RUN rm -rf third_party/differential-privacy/ && \
    cp -r /tmp/third_party/* /root/PyDP/third_party

RUN rm -rf third_party/differential-privacy/java && \ 
    rm -rf third_party/differential-privacy/examples/java

# build the bindings using Bazel and create a fresh wheel file after deleting the old one in dist folder.
RUN \
    pipenv run bazel build src/python:bindings_test  --verbose_failures && \
    cp -f ./bazel-bin/src/bindings/pydp.so ./pydp && \
    rm -rf dist/ && \
    pipenv run python setup.py bdist_wheel && \
    pipenv install dist/*.whl

# Define default command.
CMD ["bash"]
