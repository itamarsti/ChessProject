SDL_FLAGS = -I/usr/local/lib/sdl_2.0.5/include/SDL2
C_FLAGS= -c -Werror -std=c99 -pedantic-errors -Wall -g -lm `sdl-config --cflags` `sdl-config --libs` -D_REENTRANT ($SDL_FLAGS)

SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

O_FILES= chessprog.o SPArrayList.o settingParser.o boardFuncs.o settingFlow.o gameParser.o gameCommands.o gameFlow.o alphaBetaMinMax.o mainWindowGUI.o settingsWindowGUI.o loadWindowGUI.o gameWindowGUI.o GUI.o 
H_Files = chessProg.h SPArrayList.h settingParser.h boardFuncs.h settingFlow.h gameParser.h gameCommands.h gameFlow.h alphaBetaMinMax.h mainWindowGUI.h settingsWindowGUI.h loadWindowGUI.h gameWindowGUI.h GUI.h 

all: chessprog

clean:
	rm chessprog $(O_FILES)

chessprog $(O_FILES)
    gcc -o $(O_FILES) $(C_FLAGS) $(SDL_LIB)


SPArrayList.o: SPArrayList.c SPArrayList.h
    gcc -c $(C_FLAGS) SPArrayList.c

settingParser.o: settingParser.c settingParser.h
    gcc -c $(C_FLAGS) settingParser.c

gameParser.o: gameParser.c gameParser.h
    gcc -c $(C_FLAGS) gameParser.c


boardFuncs.o: boardFuncs.c boardFuncs.h SPArrayList.h settingParser.h
    gcc -c $(C_FLAGS) boardFuncs.c
    

gameCommands.o: gameCommands.c gameCommands.h SPArrayList.h boardFuncs.h gameParser.h
    gcc -c $(C_FLAGS) gameCommands.c

settingFlow.o: settingFlow.c settingFlow.h boardFuncs.h gameParser.h
    gcc -c $(C_FLAGS) settingFlow.c
    
    
gameFlow.o: gameFlow.c gameFlow.h gameCommands.h gameParser.h boardFuncs.h settingParser.h
    gcc -c $(C_FLAGS) gameFlow.c


alphaBetaMinMax.o: alphaBetaMinMax.c alphaBetaMinMax.h gameCommands.h gameParser.h boardFuncs.h
    gcc -c $(C_FLAGS) alphaBetaMinMax.c


mainWindowGUI.o: mainWindowGUI.c mainWindowGUI.h boardFuncs.h
    gcc -c $(C_FLAGS) mainWindowGUI.c

settingsWindowGUI.o: settingsWindowGUI.c settingsWindowGUI.h boardFuncs.h
    gcc -c $(C_FLAGS) settingsWindowGUI.c
    
    
loadWindowGUI.o: loadWindowGUI.c loadWindowGUI.h boardFuncs.h
    gcc -c $(C_FLAGS) loadWindowGUI.c
    
    
gameWindowGUI.o: gameWindowGUI.c gameWindowGUI.h gameCommands.h gameParser.h boardFuncs.h
    gcc -c $(C_FLAGS) gameWindowGUI.c

GUI.o: GUI.c GUI.h gameCommands.h gameParser.h boardFuncs.h mainWindowGUI.h settingsWindowGUI.h loadWindowGUI.h gameWindowGUI.h alphaBetaMinMax.h
    gcc -c $(C_FLAGS) GUI.c


chessprog.o: chessprog.c chessprog.h GUI.h boardFuncs.h gameFlow.h gameCommands.h settingFlow.h
    gcc -c $(C_FLAGS) chessprog.c

