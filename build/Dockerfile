# Dockerfile

# Start with debian as our base image -- later, we may need to check version compatibility, but for now, just use latest
FROM debian:latest

EXPOSE 22

RUN apt -y update
RUN apt install -y g++ make

# Set up directories
ENV SRC_DIR=/game/src/
ENV JSON_DIR=/game/json/
ENV CLI_DIR=/game/cli/
ENV TEST_DIR=/game/test/

# Copy over our source files
CMD mkdir -p ${SRC_DIR}
COPY ./src ${SRC_DIR}

CMD mkdir -p ${JSON_DIR}
COPY ./json ${JSON_DIR}

CMD mkdir -p ${CLI_DIR}
COPY ./cli ${CLI_DIR}

CMD mkdir -p ${TEST_DIR}
COPY ./test ${TEST_DIR}

WORKDIR /game
COPY ./Makefile .

RUN make
