# Created by Andres Vourakis

# This target compiles all the files and creates myAI
all:
	g++ -std=c++11 -pthread ConnectK.cpp Move.cpp AIShell.cpp -o SyntaxErrorAI

# This target make a copy of the compiled AI with the extension exe
exe:
	cp SyntaxErrorAI SyntaxErrorAI.exe

# This target executes the ConnectK shell
play:
	java -jar ConnectK_1.8.jar

# This target executes the ConnectK shell and loads myAI
playAI:
	java -jar ConnectK_1.8.jar cpp:SyntaxErrorAI

submit: all
	cp AIShell.cpp AIShell.h Move.cpp Move.h ConnectK.cpp ./Vourakis_90269441_SyntaxErrorAI/src
	cp SyntaxErrorAI ./Vourakis_90269441_SyntaxErrorAI/bin
	mv ./writeup.pdf ./Vourakis_90269441_SyntaxErrorAI/doc 
	zip -r Vourakis_90269441_SyntaxErrorAI.zip Vourakis_90269441_SyntaxErrorAI

# This target deletes myAI
clean:
	rm -f SyntaxError
