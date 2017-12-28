
all::
	g++ server.cpp -o server -pthread
	g++ client.cpp -o client
	g++ test.cpp -o test -lsqlite3
	g++ tabel.cpp -o table -lsqlite3
	g++ insert.cpp -o insert -lsqlite3

