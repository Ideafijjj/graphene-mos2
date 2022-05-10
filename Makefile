all: graphene_mos.x

graphene_mos.x: main.cpp relaxation.hpp relaxation.cpp

COMPFLAGS = -g -fsanitize=leak -fsanitize=address -fsanitize=leak 

%.x: %.cpp
	g++ $(COMPFLAGS) $< -o $@ 

graphene_mos.x: main.cpp relaxation.hpp relaxation.cpp
	g++ $(COMPFLAGS) main.cpp relaxation.hpp relaxation.cpp -o graphene_mos.x

format: main.cpp relaxation.hpp relaxation.cpp
	clang-format -i main.cpp relaxation.hpp relaxation.cpp

clean:
	rm -f a.out *.x *.gch  
