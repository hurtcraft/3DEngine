#-mwindows
g++ -Isrc/include -Lsrc/lib -o bin/executable *.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
.\bin\executable.exe