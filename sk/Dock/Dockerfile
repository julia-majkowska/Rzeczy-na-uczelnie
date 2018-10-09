# Use an official Python runtime as a parent image
FROM gcc:4.9

WORKDIR /app
# Copy the current directory contents into the container at /app
ADD . /app

# Make port 80 available to the world outside this container
EXPOSE 54321

# Define environment variable
ENV NAME World

RUN make
CMD ["./router", "3 \
127.0.0.1/32 dist 5 \
10.0.0.1/8 dist 2 \
255.255.255.0/8 dist 5"]