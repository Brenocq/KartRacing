#!/bin/bash
set -e

mkdir -p build
cd build
rm -rf vcpkg.linux
git clone https://github.com/Microsoft/vcpkg.git vcpkg.linux
cd vcpkg.linux
git checkout 2020.07
./bootstrap-vcpkg.sh

./vcpkg install \
	glew:x64-linux \
	glfw3:x64-linux \
	glm:x64-linux \
	stb:x64-linux \
	nlohmann-json:x64-linux
