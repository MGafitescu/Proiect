

all::
	g++ server.cpp -o server -pthread
	g++ client.cpp -o client
	g++ test.cpp tabel.cpp insert.cpp  database.cpp -o database -lsqlite3
