
all:
	g++ test.c  -o test -lsqlite3
	g++ tabel.c -o table -lsqlite3
clean:
	
