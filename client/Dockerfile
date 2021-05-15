FROM python:3.9

MAINTAINER Masoud Zayyni <zayyani.1740829@studenti.uniroma1.it>

ENV FLASK_APP=server.py
ENV FLASK_RUN_HOST=0.0.0.0

# Install redis-server and disable protected mode
RUN apt-get update && apt-get install -y redis-server

# Install python requirements
RUN pip install flask redis

COPY . /code
WORKDIR /code

CMD ["/bin/bash", "/code/entrypoint.sh"]

EXPOSE 5000
