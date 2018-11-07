%.o : %.c *.h
	gcc -c $< -std=c99
app.exe: main.o input.o
	gcc -o app.exe main.o input.o
clean:
	rm *.o *.exe
