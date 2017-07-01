mkdir build
cd build

gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_addr.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_bbt.c
gcc -Wall -fPIC -O3 -std=c1x -c ../src/nvm_be_ioctl.c


