# modelling

## how to run it ?
```
git clone https://github.com/Gerodote/modelling
cd modelling
cmake -S . -B ./build -Dmodelling_BUILD_EXECUTABLE=1 -Dmodelling_ENABLE_VCPKG=1 -Dmodelling_ENABLE_LTO=1 -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CXX_FLAGS="-march=native"
cmake --build ./build --target all --parallel 4 
./build/bin/modelling
```
