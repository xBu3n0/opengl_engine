make:
	g++ Main.cpp glad.c ./src/*/*.cpp -o Main -lglfw -lGL -lX11 -lGLEW -lpthread -lXrandr -lXi -ldl -lfreetype