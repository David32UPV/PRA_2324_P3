bin/testTableEntry: TableEntry.h testTableEntry.cpp
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

bin/testHashTable: Dict.h HashTable.h TableEntry.h testHashTable.cpp
	mkdir -p bin
	g++ -o bin/testHashTable testHashTable.cpp

bin/testBSTree: BSTree.h BSNode.h testBSTree.cpp
	mkdir -p bin
	g++ -o bin/testBSTree testBSTree.cpp

clean:
	rm -rf *.o *.gch bin 2>/dev/null || true
