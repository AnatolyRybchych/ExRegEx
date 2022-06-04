out     := ExRegEx.exe

objects	:= ./build/obj/main.o

build: $(objects)
	gcc -o $(out) $^

run: build
	./$(out)

build/obj/%.o: src/%.c
	@mkdir -p ./build/obj
	gcc -c -o $@ $<


.PHONY: build run