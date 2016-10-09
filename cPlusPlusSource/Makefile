# Created by Andres Vourakis

# This target compiles all the files and creates myAI
all:
	g++ ConnectK.cpp Move.cpp AIShell.cpp -o myAI

# This target executes the ConnectK shell
play:
	java -jar ConnectK_1.8.jar

# This target executes the ConnectK shell and loads myAI
playAI:
	java -jar ConnectK_1.8.jar cpp:myAI

submit: all
	cp AIShell.cpp AIShell.h Move.cpp Move.h ConnectK.cpp ./Vourakis_90269441_SyntaxErrorAI/src
	cp myAI ./Vourakis_90269441_SyntaxErrorAI/bin
	zip -r Vourakis_90269441_SyntaxErrorAI.zip Vourakis_90269441_SyntaxErrorAI

# This target deletes myAI
clean:
	rm -f myAI
