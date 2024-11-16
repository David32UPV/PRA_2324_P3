bin/testTableEntry: TableEntry.h testTableEntry.cpp
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

bin/testHashTable: Dict.h HashTable.h TableEntry.h testHashTable.cpp
	mkdir -p bin
	g++ -o bin/testHashTable testHashTable.cpp

clean:
	rm -rf *.o *.gch bin 2>/dev/null || true
