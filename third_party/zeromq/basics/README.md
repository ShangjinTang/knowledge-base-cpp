# ZeroMQ Demo

This project demostrates messaging with [ZeroMQ](https://zeromq.org/get-started/).

Message Route:

1. client --(request 'Hello')-> server
2. client <-(response 'World')-- server

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
