%.o : %.c *.h
	gcc -c $< -std=c99 -Wall -Werror
app.exe: main.o operations.o input.o
	gcc -o app.exe main.o operations.o input.o
clean:
	rm *.o *.exe
