# Pull base image
ARG PYTHON_VERSION=3.7
FROM python:${PYTHON_VERSION}-slim-buster
ENV PROJECT_DIR="${HOME}/examples"
# Update pip and setuptools and install pipenv
RUN pip install --upgrade pip setuptools wheel && \
    pip install pipenv
WORKDIR ${PROJECT_DIR}
COPY . .
# This makes the pipenv's virtual environment in the project dir 
ENV PIPENV_VENV_IN_PROJECT=true 
RUN pipenv install python-dp pandas jupyter --skip-lock
# This `activates` the virtual env
ENV VIRTUAL_ENV=$PROJECT_DIR/.venv
ENV PATH="$VIRTUAL_ENV/bin:$PATH"

EXPOSE 8899
ENTRYPOINT ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8899","--no-browser", "--allow-root"]
