# Created by Andres Vourakis

# This target compiles all the files and creates myAI
all:
	g++ ConnectK.cpp Move.cpp AIShell.cpp -o SyntaxErrorAI

# This target executes the ConnectK shell
play:
	java -jar ConnectK_1.8.jar

# This target executes the ConnectK shell and loads myAI
playAI:
	java -jar ConnectK_1.8.jar cpp:SyntaxErrorAI

submit: all
	cp AIShell.cpp AIShell.h Move.cpp Move.h ConnectK.cpp ./Vourakis_90269441_SyntaxErrorAI/src
	cp SyntaxErrorAI ./Vourakis_90269441_SyntaxErrorAI/bin
	cp ./writeup.pdf ./Vourakis_90269441_SyntaxErrorAI/doc 
	zip -r Vourakis_90269441_SyntaxErrorAI.zip Vourakis_90269441_SyntaxErrorAI

# This target deletes myAI
clean:
	rm -f SyntaxError
