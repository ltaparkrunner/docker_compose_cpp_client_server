# client/Dockerfile
FROM gcc:latest
WORKDIR /app
COPY client.cpp .
RUN g++ -o client client.cpp
CMD ["./client"]
