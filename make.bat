mkdir build
cd build

gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_addr.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_bbt.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_be_ioctl.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_be_lba.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_bounds.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_buf.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_cli.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_cmd.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_dev.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_geo.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_lba.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_spec.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_vblk.c
gcc -Wall -fPIC -O3 -std=c11 -c ../src/nvm_ver.c

gcc -shared -Wall -fPIC -O3 -std=c11 -o liblightnvm.dll *.o
copy liblightnvm.dll ..\test\

cd ..
cd test

gcc -Wall -fPIC -O3 -std=c11 -o test.exe test.c -L./ -lliblightnvm
