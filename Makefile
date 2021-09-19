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


bin/keyboard.exe: $(OBJ_MENU)/menu.o $(OBJ_KEYBOARD)/keyboard.o $(OBJ_KEYBOARD)/game.o $(OBJ_MENU)/levels.o
	$(CXX) -o bin/keyboard.exe $(OBJ_KEYBOARD)/keyboard.o $(OBJ_MENU)/menu.o $(OBJ_MENU)/levels.o $(OBJ_KEYBOARD)/game.o -DSFML_STATIC $(INCLUDE) -L $(SFML_PATH) $(SFML_LIBS)

$(OBJ_KEYBOARD)/keyboard.o: $(SRC_KEYBOARD)/keyboard.cpp
	$(CXX) $(CPPFLAGS) -c -o $(OBJ_KEYBOARD)/keyboard.o $(SRC_KEYBOARD)/keyboard.cpp -DSFML_STATIC $(INCLUDE) -L $(SFML_PATH) $(SFML_LIBS)

$(OBJ_MENU)/menu.o: $(SRC_MENU)/menu.cpp
	$(CXX) $(CPPFLAGS) -c -o $(OBJ_MENU)/menu.o $(SRC_MENU)/menu.cpp -DSFML_STATIC $(INCLUDE) -L $(SFML_PATH) $(SFML_LIBS)

$(OBJ_KEYBOARD)/game.o: $(SRC_KEYBOARD)/game.cpp
	$(CXX) $(CPPFLAGS) -c -o $(OBJ_KEYBOARD)/game.o $(SRC_KEYBOARD)/game.cpp -DSFML_STATIC $(INCLUDE) -L $(SFML_PATH) $(SFML_LIBS)

$(OBJ_MENU)/levels.o: $(SRC_MENU)/levels.cpp
	$(CXX) $(CPPFLAGS) -c -o $(OBJ_MENU)/levels.o $(SRC_MENU)/levels.cpp -DSFML_STATIC $(INCLUDE) -L $(SFML_PATH) $(SFML_LIBS)

$(OBJ_MENU)/menu.a: $(OBJ_MENU)/levels.o $(OBJ_MENU)/menu.o
		ar rcs $@ $^

$(OBJ_KEYBOARD)/keyboard.a: $(OBJ_KEYBOARD)/keyboard.o $(OBJ_KEYBOARD)/game.o $(OBJ_MENU)/levels.o $(OBJ_MENU)/menu.o
		ar rcs $@ $^

test: bin/test.exe

bin/test.exe: $(OBJ_MENU)/menu.a $(OBJ_KEYBOARD)/keyboard.a obj/test/test.o
	$(CXX) $(INCLUDE) -Wall -Werror -o bin/test obj/test/test.o $(OBJ_MENU)/menu.a $(OBJ_KEYBOARD)/keyboard.a -DSFML_STATIC $(INCLUDE) -L $(SFML_PATH) $(SFML_LIBS)

obj/test/test.o: test/test.cpp 
	$(CXX) $(INCLUDE) -I thirdparty/catch $(CPPFLAGS) -c -o obj/test/test.o test/test.cpp -DSFML_STATIC $(INCLUDE) -L $(SFML_PATH) $(SFML_LIBS)

-include keyboard.d menu.d game.d levels.d test.d