# Pull base image
ARG PYTHON_VERSION=3.9
FROM python:${PYTHON_VERSION}-slim-buster

# must be redefined after FROM
ARG PYTHON_VERSION=$PYTHON_VERSION
ARG BAZELISK_VERSION=v1.8.1
ARG BAZELISK_BINARY=bazelisk-linux-amd64
ARG BAZELISK_DOWNLOAD_URL=https://github.com/bazelbuild/bazelisk/releases/download/

# Set environment variables
ENV HOME=/root
ENV PROJECT_DIR="${HOME}/PyDP"
ENV PATH="/root/bin:${PATH}"
ENV DP_SHA="5e7cf28bf55ebac52fc65419364388c33ebc01a4"

# Define working directory
WORKDIR ${HOME}

# Install apt-get packages
RUN apt-get update && \
    apt-get -y install \
    sudo \
    wget \
    zip \
    git \
    software-properties-common \
    gcc \
    g++ \
    clang-format \
    build-essential \
    python3-distutils \
    pkg-config \
    zlib1g-dev

# Download and Install Bazelisk
RUN wget "${BAZELISK_DOWNLOAD_URL}/${BAZELISK_VERSION}/${BAZELISK_BINARY}" && \
    chmod +x ${BAZELISK_BINARY}

RUN ./${BAZELISK_BINARY} --version

# Update pip and setuptools and install poetry
RUN pip install --upgrade pip setuptools wheel && \
    pip install poetry

# Change working dir
WORKDIR ${PROJECT_DIR}

# Copy local source over
COPY . ${PROJECT_DIR}

# Get google dp dependency
RUN mkdir -p third_party && \
    cd third_party && \
    git clone https://github.com/google/differential-privacy.git && \
    cd differential-privacy && \
    git checkout ${DP_SHA}

# Remove unused java code
RUN rm -rf third_party/differential-privacy/java && \
    rm -rf third_party/differential-privacy/examples/java

RUN sed -i -e 's/@com_google_cc_differential_privacy//g' third_party/differential-privacy/cc/algorithms/BUILD

# This makes poetry's virtual environment in the project dir
RUN poetry config virtualenvs.in-project true

# Build the bindings using Bazel and create a python wheel
RUN poetry env use ${PYTHON_VERSION} && \
    ${HOME}/${BAZELISK_BINARY} build --config linux src/python:pydp  --verbose_failures

RUN cp -f ./bazel-bin/src/bindings/_pydp.so ./pydp && \
    rm -rf dist/ && \
    poetry run python setup.py bdist_wheel && \
    poetry add dist/*.whl

# This `activates` the virtual env
ENV VIRTUAL_ENV=$PROJECT_DIR/.venv
ENV PATH="$VIRTUAL_ENV/bin:$PATH"
# Default entrypoint
CMD ["/bin/bash"]
