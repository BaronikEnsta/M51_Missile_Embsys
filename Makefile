all :
	gcc ./src/client.c -o ./bin/client
	gcc ./src/server.c -o ./bin/server
arm: 
	./cross-compiler/arm-linux-gcc ./src/server.c -o ./bin/server-arm

debug:
	gcc -g -Wall ./src/client.c -o ./bin/client
	gcc -g -Wall ./src/server.c -o ./bin/server
