gcc -g -O0 -std=c11 -Wall -Wextra -fno-omit-frame-pointer -fsanitize=undefined,address main_c.c -o main_c

go build main_go.go
