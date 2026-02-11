all:
	gcc -o sim.exe sim.c -I"C:\raylib_mingw\include" "C:\raylib_mingw\lib\libraylib.a" -lopengl32 -lgdi32 -lwinmm