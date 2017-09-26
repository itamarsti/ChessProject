CC = gcc
O_FILES= chessprog.o SPArrayList.o settingParser.o boardFuncs.o settingFlow.o gameParser.o gameCommands.o gameFlow.o alphaBetaMinMax.o mainWindowGUI.o settingsWindowGUI.o loadWindowGUI.o gameWindowGUI.o GUI.o

H_Files = chessProg.h SPArrayList.h settingParser.h boardFuncs.h settingFlow.h gameParser.h gameCommands.h gameFlow.h alphaBetaMinMax.h mainWindowGUI.h settingsWindowGUI.h loadWindowGUI.h gameWindowGUI.h GUI.h

EXEC = chessprog
COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main -lm
#SDL_COMP_FLAG = -I/usr/include/SDL2 -D_REENTRANT
#SDL_LIB = -L/usr/lib/x86_64-linux-gnu -Wl,-rpath,/usr/lib/x86_64-linux-gnu -Wl,--enable-new-dtags -lSDL2 -lSDL2main -lm

    
    
all: $(O_FILES)
	$(CC) $(O_FILES) $(SDL_LIB) -o $(EXEC)

clean:
	rm -f $(EXEC) $(O_FILES)

$(EXEC): $(O_FILES)
	$(CC) $(O_FILES) $(SDL_LIB) -o $@


SPArrayList.o: SPArrayList.c SPArrayList.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

settingParser.o: settingParser.c settingParser.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

gameParser.o: gameParser.c gameParser.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c


boardFuncs.o: boardFuncs.c boardFuncs.h SPArrayList.h settingParser.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
    

gameCommands.o: gameCommands.c gameCommands.h SPArrayList.h boardFuncs.h gameParser.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

settingFlow.o: settingFlow.c settingFlow.h boardFuncs.h gameParser.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
    
    
gameFlow.o: gameFlow.c gameFlow.h gameCommands.h gameParser.h boardFuncs.h settingParser.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c


alphaBetaMinMax.o: alphaBetaMinMax.c alphaBetaMinMax.h gameCommands.h gameParser.h boardFuncs.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c


mainWindowGUI.o: mainWindowGUI.c mainWindowGUI.h boardFuncs.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

settingsWindowGUI.o: settingsWindowGUI.c settingsWindowGUI.h boardFuncs.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
    
    
loadWindowGUI.o: loadWindowGUI.c loadWindowGUI.h boardFuncs.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
    
    
gameWindowGUI.o: gameWindowGUI.c gameWindowGUI.h gameCommands.h gameParser.h boardFuncs.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

GUI.o: GUI.c GUI.h gameCommands.h gameParser.h boardFuncs.h mainWindowGUI.h settingsWindowGUI.h loadWindowGUI.h gameWindowGUI.h alphaBetaMinMax.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c


chessprog.o: chessprog.c chessprog.h GUI.h boardFuncs.h gameFlow.h gameCommands.h settingFlow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
