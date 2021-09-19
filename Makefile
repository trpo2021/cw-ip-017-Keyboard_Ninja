CXX = g++
CPPFLAGS = -Wall -Werror -MP -MMD
SFML_LIBS = -lsfml-window -lsfml-system -lopengl32 -lwinmm -lgdi32 -lsfml-graphics -lfreetype  
SFML_PATH = thirdparty/SFML/lib
SFML_INC = thirdparty/SFML/include
SFML_TYPE = SFML_STATIC

INCLUDE = -I $(SFML_INC)


bin/keyboard.exe: obj/src/keyboard/keyboard.o
	$(CXX) -o bin/keyboard.exe obj/src/keyboard/keyboard.o -DSFML_STATIC -I $(SFML_INC) -L $(SFML_PATH) $(SFML_LIBS)

obj/src/keyboard/keyboard.o: src/keyboard/keyboard.cpp
	$(CXX) $(CPPFLAGS) -c -o obj/src/keyboard/keyboard.o src/keyboard/keyboard.cpp -DSFML_STATIC -I $(SFML_INC) -L $(SFML_PATH) $(SFML_LIBS)