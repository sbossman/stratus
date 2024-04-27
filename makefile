compile:
	g++ -o ./build/stratus.exe ./src/*.cpp
run:
	./build/stratus.exe siteMake.txt ./input/ ./output/
comprun:
	g++ -o ./build/stratus.exe ./src/*.cpp
	./build/stratus.exe siteMake.txt ./input/ ./output/
