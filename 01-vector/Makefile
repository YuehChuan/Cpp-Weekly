cc       := clang++
cxxflag   = -Wall -Wextra -Werror
cxxflag  += -g -O2
cxxflag  += -std=c++17
cxxflag  += -fsanitize=address
target   := console_app.out
main     := client.cpp
dir_doc  := doc
browser  := firefox-developer-edition

compile: $(target)

$(target): $(main)
	$(cc) $(cxxflag) -I./ -o $@ $< -Dtest_suite=main

execute: $(target)
	./$<

doc: $(dir_doc)/Doxyfile
	doxygen $<
	$(browser) $(dir_doc)/html/index.html

clean:
	rm -f *.out && rm -rf $(dir_doc)/html && rm -rf $(dir_doc)/latex

fmt:
	find . -type f -iname "*.cpp" -o -iname "*.hpp" | xargs clang-format -style=file -i

tidy: $(shell find . -type f -iname "*.cpp" -o -iname "*.hpp")
	clang-tidy -fix $? -- -std=c++17 -I./

.PHONY: compile $(target) execute doc clean fmt tidy
