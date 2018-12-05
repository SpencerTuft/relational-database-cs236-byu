FROM ubuntu:latest

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install g++ valgrind pmccabe -y
RUN echo "Install complete"
