out     := ExRegEx.exe

objects	:= ./build/obj/main.o
objects	+= ./build/obj/ex_regex.o
objects	+= ./build/obj/ex_intrinsic.o

build: $(objects)
	gcc -o $(out) $^

run: build
	./$(out)

build/obj/%.o: src/%.c
	@mkdir -p ./build/obj
	gcc -c -o $@ $<


.PHONY: build run