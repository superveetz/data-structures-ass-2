#include <catch/include/catch.hpp>

#include "HashTable.hpp"

using namespace std;

SCENARIO( "Testing HashTable Class To Ensure Proper Output", "[hashtable]" ) {
    HashTable* hashTable = new HashTable(13);
    REQUIRE(hashTable->tableSize == 13);

    GIVEN( "An empty hash table") {
        WHEN("Adding elements") {
            REQUIRE(hashTable->add(4) == true);
            REQUIRE(hashTable->add(5) == true);
            THEN ("adding the same element should return false") {
                REQUIRE(hashTable->add(4) == false);
                REQUIRE(hashTable->add(5) == false);
            }
        }

        WHEN("Removing elements") {
            REQUIRE(hashTable->add(4) == true);
            REQUIRE(hashTable->add(5) == true);

            THEN ("removing values that exist return true") {
                REQUIRE(hashTable->remove(4) == true);
                REQUIRE(hashTable->remove(5) == true);
            }

            AND_THEN ("remove elements that don't exist return false") {
                REQUIRE(hashTable->remove(99) == false);
            }
        }

        WHEN("Finding elements") {
            REQUIRE(hashTable->add(4) == true);
            REQUIRE(hashTable->add(5) == true);

            THEN ("finding these values should not return -1") {
                REQUIRE(hashTable->find(4) != -1);
                REQUIRE(hashTable->find(5) != -1);
            }

            AND_THEN ("finding values that don't exist returns -1") {
                REQUIRE(hashTable->find(99) == -1);
            }
        }
    }

    GIVEN( "Assignment 2, Question 4") {
        WHEN("Asked to store the following elements in the table: {1, 5, 21, 26, 39, 14, 15, 16, 17, 18, 19, 20, 111, 145, 146") {
            REQUIRE(hashTable->add(1) == true);
            REQUIRE(hashTable->add(5) == true);
            REQUIRE(hashTable->add(21) == true);
            REQUIRE(hashTable->add(26) == true);
            REQUIRE(hashTable->add(39) == true);
            REQUIRE(hashTable->add(14) == true);
            REQUIRE(hashTable->add(15) == true);
            REQUIRE(hashTable->add(16) == true);
            REQUIRE(hashTable->add(17) == true);
            REQUIRE(hashTable->add(18) == true);
            REQUIRE(hashTable->add(19) == true);
            REQUIRE(hashTable->add(20) == true);
            REQUIRE(hashTable->add(111) == true);
            REQUIRE(hashTable->add(145) == true);
            REQUIRE(hashTable->add(146) == true);

            THEN ("we should be able to find each of these elements") {
                REQUIRE(hashTable->find(1) != -1);
                REQUIRE(hashTable->find(5) != -1);
                REQUIRE(hashTable->find(21) != -1);
                REQUIRE(hashTable->find(26) != -1);
                REQUIRE(hashTable->find(39) != -1);
                REQUIRE(hashTable->find(14) != -1);
                REQUIRE(hashTable->find(15) != -1);
                REQUIRE(hashTable->find(16) != -1);
                REQUIRE(hashTable->find(17) != -1);
                REQUIRE(hashTable->find(18) != -1);
                REQUIRE(hashTable->find(19) != -1);
                REQUIRE(hashTable->find(20) != -1);
                REQUIRE(hashTable->find(111) != -1);
                REQUIRE(hashTable->find(145) != -1);
                REQUIRE(hashTable->find(146) != -1);
            }

            AND_THEN("we should be able to remove them as well") {
                REQUIRE(hashTable->remove(1) == true);
                REQUIRE(hashTable->remove(5) == true);
                REQUIRE(hashTable->remove(21) == true);
                REQUIRE(hashTable->remove(26) == true);
                REQUIRE(hashTable->remove(39) == true);
                REQUIRE(hashTable->remove(14) == true);
                REQUIRE(hashTable->remove(15) == true);
                REQUIRE(hashTable->remove(16) == true);
                REQUIRE(hashTable->remove(17) == true);
                REQUIRE(hashTable->remove(18) == true);
                REQUIRE(hashTable->remove(19) == true);
                REQUIRE(hashTable->remove(20) == true);
                REQUIRE(hashTable->remove(111) == true);
                REQUIRE(hashTable->remove(145) == true);
                REQUIRE(hashTable->remove(146) == true);
            }
        }
    }
}