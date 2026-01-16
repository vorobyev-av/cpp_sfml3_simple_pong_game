Remove-Item build -Recurse
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
pause