build:
	mkdir build
	g++ src/main.cpp -o build/tic_tac_toe -lGL -lGLU -lglut
clean:
	rm -rf build


