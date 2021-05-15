FROM ubuntu:latest

MAINTAINER Masoud Zayyni <zayyani.1740829@studenti.uniroma1.it>

# Export DISPLAY, so a XServer can display OMEdit
ARG DEBIAN_FRONTEND=noninteractive
ENV DISPLAY=host.docker.internal:0.0

# Install wget, gnupg, lsb-release
RUN apt-get update \
    && apt install -y wget gnupg lsb-release

# Get the OpenModelica stable version
RUN for deb in deb deb-src; do echo "$deb http://build.openmodelica.org/apt `lsb_release -cs` stable"; done | tee /etc/apt/sources.list.d/openmodelica.list
RUN wget -q http://build.openmodelica.org/apt/openmodelica.asc -O- | apt-key add -

# Install OpenModelica
RUN apt-get update \
    && apt install -y openmodelica

# INSTALL OPENMODELICA LIBRARIES (LIKE ALL OF THEM)
RUN apt-get install -y omlib-modelica-4.0.0

# Install dependencies for python worker
RUN apt-get install -y python3 python3-pip
RUN pip3 install redis

# Clean apt cache files
RUN apt-get clean && rm -rf /var/lib/apt/lists/*

# Add non-root user for security
RUN useradd -m -s /bin/bash openmodelicausers
USER openmodelicausers
ENV HOME /home/openmodelicausers
ENV USER openmodelicausers
WORKDIR $HOME

# Copy worker code
COPY worker.py /home/openmodelicausers/worker.py

# Return omc version
CMD ["python3", "/home/openmodelicausers/worker.py"]
