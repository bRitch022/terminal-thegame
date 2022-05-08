# Dockerfile

FROM debian:latest

USER root
RUN apt -y update
RUN apt install -y gdb procps

# Set up directories
ENV GAMEFILES_DIR=/usr/game/gamefiles/

# Copy over the source files
RUN mkdir -p ${GAMEFILES_DIR}
COPY ./gamefiles ${GAMEFILES_DIR}
COPY ./bin ${GAMEFILES_DIR}

# Apply execute permissions to source files
RUN chmod +x ${GAMEFILES_DIR}gameStart.sh
RUN chmod +x ${GAMEFILES_DIR}Terminal

# Set up a test user
RUN adduser testuser
USER testuser

# Start the game
RUN echo ${GAMEFILES_DIR}/gameStart.sh >> ~/.bashrc
CMD [ "source", "~/.bashrc" ]