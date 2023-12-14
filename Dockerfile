# Pull base image
FROM debian:buster-slim
ARG DEBIAN_FRONTEND=noninteractive

# Install any needed packages
RUN apt-get update && apt-get install -y \
    g++ \
    libpq-dev \
    libpqxx-dev \
    postgresql-client

# Set the working directory to /app
WORKDIR /app

# Copy the source files from the src directory into the container at /app
COPY src/ .


# Compile 
RUN g++ -o task_tracker main.cpp DatabaseInterface.cpp Task.cpp TaskManager.cpp \
    -I/usr/include/postgresql \
    -lpqxx -lpq -std=c++17

# Set the path to find the libraries 
ENV LD_LIBRARY_PATH=/usr/local/lib:/usr/lib

# Set default environment variables
ENV DB_USER=default_user
ENV DB_PASSWORD=default_password
ENV DB_HOST=host.docker.internal
ENV DB_PORT=5432
ENV DB_NAME=task_tracker_db

# Run
CMD ["./task_tracker"]