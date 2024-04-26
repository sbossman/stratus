compile:
	g++ -o ./build/stratus.exe ./src/*.cpp
runexample:
	./build/stratus.exe siteMake.txt ./input/ ./output/