alias c='g++ -Wall -Wconversion -Wfatal-errors -g -std=c++20 \
	-fsanitize=undefined,address'
run() {c $1 && ./a.out < in.txt > out.txt && diff -w out.txt ans.txt}
