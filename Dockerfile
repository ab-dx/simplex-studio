FROM ubuntu:24.04

RUN apt-get update && apt-get install -y gcc make build-essential

WORKDIR /app

COPY assembler ./assembler
COPY web_server ./web_server

RUN cd assembler && make asm emu
RUN cd web_server && make server

WORKDIR /app/web_server

EXPOSE 8080

ENTRYPOINT ["./build/target/server"]
