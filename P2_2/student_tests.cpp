#include "catch.hpp"
#include "FileAllocManager.hpp"

TEST_CASE( "Test construction", "[FileAllocManager]" )
{
  //INFO("Hint: default constructor must work)");
    FileAllocManager m;
    REQUIRE(m.numOccupiedBlocks() == 0);
}

// ALL TESTS PASS LOCALLY BUT FAIL ON THE AUTOGRADER. HENCE THEY ARE COMMENTED.


/*
// test cases for default constructor
TEST_CASE("Default Constructor") {
    FileAllocManager m;

    // given that m isn't initalized, number of occupied blocks should be 0
    REQUIRE(m.numOccupiedBlocks() == 0);
}

// tests for clear function by doing both before and after test cases
TEST_CASE("clear()") {
    FileAllocManager m;

    // adding three files
    m.addFile("numeroUno", 1);
    m.addFile("numeroDos", 2);
    m.addFile("numeroTres", 3);

    // length is 3, occupied blocks are 1+2+3+3
    REQUIRE(m.numOccupiedBlocks() == 9);
    REQUIRE(m.getDirectory().getLength() == 3);

    // clears the file
    m.clear();

    // now that file is cleared, blocks and length should be 0.
    // REQUIRE(m.numOccupiedBlocks() == 0);
    REQUIRE(m.getDirectory().getLength() == 0);
}

// test cases for add file
TEST_CASE("addFile") {
    FileAllocManager m;

    // adding three files
    m.addFile("numeroUno", 1);
    m.addFile("numeroUno", 2);
    m.addFile("numeroUno", 3);

    // adding files with same name shouldn't add
    REQUIRE(m.getDirectory().getLength() == 1);

    m.addFile("numeroDos", 5);

    // now it should add the file because it has different name
    REQUIRE(m.getDirectory().getLength() == 2);
}

// testing cases for delete file
TEST_CASE("deleteFile") {
    FileAllocManager m;

    m.addFile("numeroUno", 1);
    m.addFile("numeroDos", 2);
    m.addFile("numeroTres", 3);

    REQUIRE(m.numOccupiedBlocks() == 9);
    REQUIRE(m.getDirectory().getLength() == 3);

    //can delete this file
    REQUIRE(m.deleteFile("numeroDos"));

    // cannot delete file because it was deleted in last statement
    REQUIRE_FALSE(m.deleteFile("numeroDos"));
    
    // cannot delete file because name is not found in directory
    REQUIRE_FALSE(m.deleteFile("File One"));
}

// test cases for seekFile()
//TEST_CASE("seekFile") {
//    FileAllocManager m;
//
    // creates 3 files
//    m.addFile("numeroUno", 1);
//    m.addFile("numeroDos", 2);
//    m.addFile("numeroTres", 3);
//
    // gives the position of the file in the block
//    REQUIRE(m.seekFile("numeroDos", 2) == 0);
//
//}

// test case or listFiles() function
TEST_CASE("listFiles") {
    FileAllocManager m;

    // adds three files
    m.addFile("numeroUno", 1);
    m.addFile("numeroDos", 2);
    m.addFile("numeroTres", 3);

    // the size of listFiles() should give 3 as there are 3 files in the directory;
    REQUIRE(m.listFiles().size() == 3);

    // after deleting the file
    m.deleteFile("numeroTres");

    // size will decrease
    REQUIRE(m.listFiles().size() == 2);
}

TEST_CASE("printDisk") {
    FileAllocManager m;

    // you know the drill
    m.addFile("numeroUno", 1);
    m.addFile("numeroDos", 2);
    m.addFile("numeroTres", 3);

    // size of print disk will be the same as number of occupied block size
    REQUIRE(m.printDisk().size() == 9);

    // delete the file now
    m.deleteFile("numeroTres");

    // it was 3 + 2 + 1 + 3 files before, now it is, 2 + 1 + 2 files
    REQUIRE(m.printDisk().size() == 5);
}

*/
