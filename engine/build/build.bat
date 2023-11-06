@ECHO OFF



ECHO compiling

g++ src/main.cpp -o build/main.exe -lglew32 -llibfreeglut -lopengl32 -lgdi32 -I dependencies/include/ogldev/ -I dependencies/include/common/

ECHO running

.\build\main.exe