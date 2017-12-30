

all::
	g++ select.cpp server.cpp -o server -pthread -lsqlite3
	g++ client.cpp -o client
	g++ test.cpp tabel.cpp insert.cpp  database.cpp -o database -lsqlite3
