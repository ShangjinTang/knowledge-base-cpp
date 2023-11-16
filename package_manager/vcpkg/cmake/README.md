# vcpkg with CMake

## Install Vcpkg

```bash
git clone https://github.com/microsoft/vcpkg --depth=1
./vcpkg/bootstrap-vcpkg.sh
export VCPKG_ROOT=$(pwd)/vcpkg
# add this to init files, e.g. ~/.bashrc or ~/.zshrc
export PATH=$PATH:$VCPKG_ROOT
```

## Add Vcpkg Pacakges

```bash
# execute this under your directory to generate "vcpkg*.json" files
vcpkg new --application
vcpkg add port fmt
vcpkg add port spdlog
```

After the commands above, `vcpkg.json` file is as below:

```bash
{
    "dependencies": [
    "fmt",
    "spdlog"
    ]
}
```

### Version Control Method 1 - Baselines

Baselines define a global version floor for what versions will be considered.

This enables top-level manifests to keep the entire graph of dependencies up-to-date without needing to individually specify direct `version>=` constraints.

```bash
# init
vcpkg x-update-baseline --add-initial-baseline
# update
vcpkg x-update-baseline
```

```bash
{
    "dependencies": [
    "fmt",
    "spdlog"
    ],
    "builtin-baseline": "ac2a14f35fcd57d7a38f09af75dd5258e96dd6ac"
}
```

### Version Control Method 2 - `version>=`

Expresses a minimum version requirement, `version>=` declarations put a lower boundary on the versions that can be used to satisfy a dependency.

Use `vcpkg search <package_name>` to get current version.

```bash
{
  "dependencies": [
    {
      "name": "fmt",
      "version>=": "10.1.1"
    },
    { "name": "spdlog",
      "version>=": "1.12.0"
    }
  ]
}
```

## Build & Run (Command Line)

### Debug

```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=/home/sol/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
./build/src/main
```

### Release

```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=/home/sol/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/src/main
```
