make:
	g++ Main.cpp glad.c ./src/*/*.cpp ./src/*/*/*.cpp -O3 -o Main -lglfw -lGL -lX11 -lXrandr -lXi -ldl -lfreetype -std=c++20