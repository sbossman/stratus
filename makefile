compile:
	g++ -o ./build/stratus.exe ./src/*.cpp
run:
	./build/stratus.exe siteMake.txt ./input/ ./output/
comprun:
	g++ -o ./build/stratus.exe ./src/*.cpp
	./build/stratus.exe siteMake.txt ./input/ ./output/
transfer:
	g++ -o ./build/stratus.exe ./src/*.cpp
	./build/stratus.exe siteMake.txt ./input/ ./output/
	scp ./output/* bossmans@thunder.cise.ufl.edu:public_html
