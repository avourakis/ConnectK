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

# This target deletes myAI
clean:
	rm -f myAI
