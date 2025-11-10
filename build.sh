mkdir build
cmake -S . -B build
cmake --build build -j8
cp ./build/physics_engine ./physics_engine
