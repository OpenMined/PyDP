# Pull base image.
FROM python:3.6-slim-buster

# Set environment variables.
ENV HOME /root
ENV PATH "/root/bin:${PATH}"

# Define working directory.
WORKDIR /root/PyDP

COPY . /root/PyDP

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
                       git && \
    bash ext_source_setup && \
    bash prereqs && \
    bash build_PyDP.sh && \
    python3 setup.py sdist bdist_wheel && \
    pip install dist/pydp-0.1.0-py2.py3-none-any.whl && \
    pip install -r requirements_dev.txt


# Define default command.
CMD ["bash"]
