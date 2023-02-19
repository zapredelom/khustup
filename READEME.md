
# Khustup

project for experiments around whiteboards

## build

### create vrtualenv

```bash
    python -m venv  virtualenv  # create virtualenv
```

### activate virtualenv

#### on mac/linux

```bash
    source virtualenv/bin/activate  # activate virtualenv
```

#### on windows

```powershell
    .\virtualenv\Scripts\activate.ps1  # activate virtualenv
```

### install requirements

```bash
    pip install -r ./.devconoteiner/requirements.txt  # install requirements
```

### install conan dependenceis

```bash
    mkdir build
    cd build
    conan install ..  # install conan dependencies
```

### buid with cmake

```bash
    cmake ..  # configure cmake
    cmake --build .  # build
    ```
