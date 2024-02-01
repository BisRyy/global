main: clean lexer.o parser.o printToken.o error.o
		g++ -o global lexer.o parser.o printToken.o error.o main.cpp
		echo "COMPILATION SUCCESSFUL"

lexer: lexer.o printToken.o
		g++ -o lexer lexer.o printToken.o src/tokens.cpp

parser: clean lexer.o printToken.o
		g++ -o parser lexer.o printToken.o src/parser.cpp

parser.o: src/parser.cpp headers/globals.h
		g++ -c -w src/parser.cpp

lexer.o: src/lexer.cpp headers/globals.h
		g++ -c -w src/lexer.cpp
error.o: src/error.cpp headers/globals.h
		g++ -c -w src/error.cpp

printToken.o: headers/printToken.cpp headers/globals.h
	    g++ -c -w headers/printToken.cpp

clean:
		rm -f *.o lexer main parser tests/*.out