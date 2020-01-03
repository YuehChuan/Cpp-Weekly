cc       := clang++
cxxflag   = -Wall -Wextra -Werror
cxxflag  += -g -O2
cxxflag  += -std=c++17
cxxflags += -fsanitize=address
ldflags  := -lasan
target   := console_app.out
main     := client.cpp

compile: $(target)

$(target): $(main)
	$(cc) $(cxxflag) -I./ -o $@ $< $(ldflags) -Dtest_suite=main

execute: $(target)
	./$<

clean:
	rm -f *.out

fmt:
	find . -type f -iname "*.cpp" -o -iname "*.hpp" | xargs clang-format -style=file -i

.PHONY: compile $(target) execute clean fmt
