mkdir build

gcc -Wall -s -O3 -m64 -std=c17 src/main.c src/definitions/*.c -o build/FileTransfer -lws2_32
