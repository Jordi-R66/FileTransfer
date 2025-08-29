mkdir build

gcc -Wall -Wextra -s -O3 -m64 -std=c23 src/main.c src/definitions/*.c src/definitions/win/*.c -o build/FileTransfer -lws2_32
