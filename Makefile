all:
	gcc -o sim.exe sim.c -I"C:\raylib\include" "C:\raylib\lib\libraylib.a" -lopengl32 -lgdi32 -lwinmm