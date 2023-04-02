all: compile link execute

compile:
	g++ -c main.cpp -IC:\Users\vince\OneDrive\Documenti\libraries\SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit\SFML-2.5.1\include -DSFML_STATIC

link:
	g++ main.o -o main -LC:\Users\vince\OneDrive\Documenti\libraries\SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit\SFML-2.5.1\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

execute:
	.\main
	
clean:
	del main *.o