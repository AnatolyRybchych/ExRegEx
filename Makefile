out     := ExRegEx.exe

objects	:= ./build/obj/main.o
objects	+= ./build/obj/ex_regex.o
objects	+= ./build/obj/filter.o
objects	+= ./build/obj/filters.o
objects	+= ./build/obj/proc_data.o
objects	+= ./build/obj/match.o

build: $(objects)
	gcc -o $(out) $^

run: build
	./$(out)

build/obj/%.o: src/%.c
	@mkdir -p ./build/obj
	gcc -c -o $@ $<


.PHONY: build run