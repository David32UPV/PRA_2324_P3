bin/testTableEntry: TableEntry.h testTableEntry.cpp
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

bin/testHashTable: Dict.h HashTable.h TableEntry.h testHashTable.cpp
	mkdir -p bin
	g++ -o bin/testHashTable testHashTable.cpp

bin/testHashTable2: Dict.h HashTable2.h TableEntry.h testHashTable.cpp
	mkdir -p bin
	g++ -o bin/testHashTable2 testHashTable.cpp

bin/testBSTree: BSTree.h BSNode.h testBSTree.cpp
	mkdir -p bin
	g++ -o bin/testBSTree testBSTree.cpp

bin/testBSTreeDict: Dict.h BSTreeDict.h BSNode.h TableEntry.h testBSTreeDict.cpp
	mkdir -p bin
	g++ -o bin/testBSTreeDict testBSTreeDict.cpp

clean:
	rm -rf *.o *.gch bin 2>/dev/null || true
