mkdir -p build
cd build

module load GCC/9.3.0
module load CMake/3.16.4

cmake ..
make

cd ..
