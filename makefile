CPP=g++
EXEC=dico_jap_fra
LDFLAGS= -lXm -lXt -lX11
CXXFLAGS= -Wall
SRC= src/str_list_ctrl.cpp src/traduit.cpp src/to_struct.cpp src/widget.cpp src/dico_jap_fra.cpp
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) -o $@ $^ $(LDFLAGS)

src/str_list_ctrl.o: src/str_list_ctrl.cpp src/str_list_ctrl.h
	$(CPP) -o $@ -c $< $(CXXFLAGS)

src/traduit.o: src/traduit.cpp src/traduit.h src/str_list_ctrl.h
	$(CPP) -o $@ -c $< $(CXXFLAGS)

src/to_struct.o: src/to_struct.cpp src/to_struct.h src/str_list_ctrl.h
	$(CPP) -o $@ -c $< $(CXXFLAGS)

src/widget.o: src/widget.cpp src/widget.h
	$(CPP) -o $@ -c $< $(CXXFLAGS)

src/dico_jap_fra.o: src/dico_jap_fra.cpp src/dico_jap_fra.h src/to_struct.h src/traduit.h
	$(CPP) -o $@ -c $< $(CXXFLAGS)

# pour forcer clean/cleanall même s'il existe un fichier de même nom
.PHONY: clean cleanall

clean:
	rm -rf src/*.o

cleanall: clean
	rm -rf $(EXEC)


