alias c='g++ -Wall -Wconversion -Wfatal-errors -g -std=c++17 \
	-fsanitize=undefined,address'
alias run='c A.cpp && ./a.out < in.txt > out.txt && diff -w out.txt ans.txt'
