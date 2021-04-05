#! /bin/sh

echo "$0: Creating build directory..."
[ -d ./build ] && cd ./build || mkdir ./build; cd ./build

echo "$: Generating build files..."
cmake .. -G Ninja

echo "$0: Compiling..."
ninja

echo "$0: Done! Built binary is in \`build/\`"
cd ..
