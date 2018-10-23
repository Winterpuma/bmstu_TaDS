%.o : %.c *.h
	gcc -c $< -std=c99
app.exe: main.o structures.o input.o sort.o
	gcc -o app.exe main.o structures.o input.o sort.o
clean:
	rm *.o *.exe
