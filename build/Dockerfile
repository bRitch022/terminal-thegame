# Dockerfile

# Start with debian as our base image -- later, we may need to check version compatibility, but for now, just use latest
FROM debian:latest

EXPOSE 22

RUN apt -y update
RUN apt install -y g++ make scp

# Copy over our gamefiles
CMD mkdir -p /game/gamesrc/
CMD mkdir -p /game/json/
CMD mkdir -p /game/cli/
CMD mkdir -p /game/test/

WORKDIR /game/gamesrc/
COPY ./gamesrc .

WORKDIR /game/json/
COPY ./json .

WORKDIR /game/cli/
COPY ./cli .

WORKDIR /game/test
COPY ./test .

WORKDIR /game
COPY ./Makefile .

RUN make

RUN scp -r /game/build/bin/* britchie@172.24.21.117:/home/britchie/repos-wd/cli-game-wd/build/bin
