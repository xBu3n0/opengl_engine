make:
	g++ Main.cpp glad.c ./src/*/*.cpp ./src/*/*/*.cpp -o Main -lglfw -lGL -lX11 -lXrandr -lXi -ldl -lfreetype -std=c++20