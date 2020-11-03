all: 
	g++ grimoire_val_check.cpp -o gvc
	g++ generate_grimoire.cpp -o generate
	./generate

run: 
	./gvc < test.in