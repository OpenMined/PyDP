# Pull base image
ARG PYTHON_VERSION=3.7
FROM python:${PYTHON_VERSION}-slim-buster

# must be redefined after FROM
ARG PYTHON_VERSION=$PYTHON_VERSION
ARG BAZEL_VERSION=3.2.0
ARG BAZEL_INSTALLER=bazel-${BAZEL_VERSION}-installer-linux-x86_64.sh
ARG BAZEL_DOWNLOAD_URL=https://github.com/bazelbuild/bazel/releases/download

# Set environment variables
ENV HOME=/root
ENV PROJECT_DIR="${HOME}/PyDP"
ENV PATH="/root/bin:${PATH}"
ENV DP_SHA="1b1dc6639173c0a13613189ec21851604a4c7335"

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
    build-essential \
    python3-distutils \
    pkg-config \
    zlib1g-dev

# Download and Install Bazel
RUN wget ${BAZEL_DOWNLOAD_URL}/${BAZEL_VERSION}/${BAZEL_INSTALLER} && \
    chmod +x ${BAZEL_INSTALLER} && ./${BAZEL_INSTALLER} --user && rm ${BAZEL_INSTALLER}

# Update pip and setuptools and install pipenv
RUN pip install --upgrade pip setuptools wheel && \
    pip install pipenv

# Change working dir
WORKDIR ${PROJECT_DIR}

# Copy local source over
COPY . ${PROJECT_DIR}

# This makes the pipenv's virtual environment in the project dir
ENV PIPENV_VENV_IN_PROJECT=true

# Build the bindings using Bazel and create a python wheel
RUN pipenv --python ${PYTHON_VERSION} && \
    mkdir -p third_party && \
    rm -f third_party/differential-privacy && \
    run ln -s $(bazel info output_base)/external/com_google_differential_privacy third_party && \
    pipenv run bazel build src/python:bindings_test  --verbose_failures

RUN cp -f ./bazel-bin/src/bindings/_pydp.so ./pydp && \
    rm -rf dist/ && \
    pipenv run python setup.py bdist_wheel && \
    pipenv install dist/*.whl

# This `activates` the virtual env
ENV VIRTUAL_ENV=$PROJECT_DIR/.venv
ENV PATH="$VIRTUAL_ENV/bin:$PATH"
# Default entrypoint
CMD ["/bin/bash"]
