lexer: lexer.o printToken.o
		g++ -o lexer lexer.o printToken.o

lexer.o: lexer.cpp headers/globals.h
		g++ -c -w lexer.cpp

printToken.o: headers/printToken.cpp headers/globals.h
	    g++ -c -w headers/printToken.cpp

clean: 
		rm -f *.o lexer main parser