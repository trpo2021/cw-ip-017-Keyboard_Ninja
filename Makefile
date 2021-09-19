CXX = g++
CPPFLAGS = -Wall -Werror -MP -MMD

SRC_KEYBOARD = src/keyboard
SRC_MENU = src/menu

OBJ_KEYBOARD = obj/src/keyboard
OBJ_MENU = obj/src/menu

SFML_LIBS = -lsfml-window -lsfml-system -lsfml-graphics -lfreetype  
SFML_PATH = thirdparty/SFML/lib
SFML_INC = thirdparty/SFML/include
SFML_TYPE = SFML_STATIC

INCLUDE = -I $(SFML_INC) -I $(SRC_MENU) -I $(SRC_KEYBOARD)


bin/keyboard.exe: $(OBJ_MENU)/menu.o $(OBJ_KEYBOARD)/keyboard.o
	$(CXX) -o bin/keyboard.exe $(OBJ_KEYBOARD)/keyboard.o $(OBJ_MENU)/menu.o -DSFML_STATIC $(INCLUDE) -L $(SFML_PATH) $(SFML_LIBS)

$(OBJ_KEYBOARD)/keyboard.o: $(SRC_KEYBOARD)/keyboard.cpp
	$(CXX) $(CPPFLAGS) -c -o $(OBJ_KEYBOARD)/keyboard.o $(SRC_KEYBOARD)/keyboard.cpp -DSFML_STATIC $(INCLUDE) -L $(SFML_PATH) $(SFML_LIBS)


$(OBJ_MENU)/menu.o: $(SRC_MENU)/menu.cpp
	$(CXX) $(CPPFLAGS) -c -o $(OBJ_MENU)/menu.o $(SRC_MENU)/menu.cpp -DSFML_STATIC $(INCLUDE) -L $(SFML_PATH) $(SFML_LIBS)

-include keyboard.d menu.d