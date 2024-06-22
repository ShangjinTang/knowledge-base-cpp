# ZeroMQ Demo

This project demostrates messaging with [ZeroMQ](https://zeromq.org/get-started/) with [ProtoBuf](https://github.com/protocolbuffers/protobuf).

Message Route:

1. client --(serialized request `Message`)-> server
2. client <-(serialized response `Message`)-- server

## ProtoBuf

Install `protoc` with corresponding version in `.tool-versions`.

```bash
cd ./proto/message/v1
# C++: generate message.pb.h and message.pb.cc
protoc --cpp_out=. message.proto
# Python: generate message_pb2.py
protoc --python_out=. message.proto
```

After proto generated, move them to C++/Python sources.

## Server (C++)

Use `conan` with `pipx`:

```bash
cd ./server_cpp
python3 -m pip install pipx
pipx ensurepath
pipx install conan
./compile_run.sh
```

## Client (Python)

Use `python` with `poetry`:

```bash
cd ./client_py
poetry init
poetry run python main.py
```
