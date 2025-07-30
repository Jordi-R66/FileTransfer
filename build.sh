mkdir -p build

gcc -Wall -Wextra -s -O3 -m64 -std=c17 src/main.c src/definitions/*.c src/definitions/*/*.c -o build/FileTransfer
# x86_64-w64-mingw32-gcc -Wall -s -O3 -m64 -std=c17 src/main.c src/definitions/*.c src/definitions/*/*.c -o build/FileTransfer -lws2_32
