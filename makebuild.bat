mkdir build
cd build
cmake -G "Visual Studio 15 2017 Win64" -DOPENSSL_ROOT_DIR=/c/OpenSSL-Win64 -DOPENSSL_LIBRARIES=/c/OpenSSL-Win64/lib -DOPENSSL_INCLUDE_DIR=/c/OpenSSL-Win64/include ..
cd ..
