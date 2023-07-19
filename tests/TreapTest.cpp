//
// Created by Guillermo on 25.05.23.
//

#include "gtest/gtest.h"
#include "map.cpp"

TEST (TreadTest, InsertValues) {

    struct Map treap;

    treap.insert(1, 2);
    treap.insert(2, 3);
    treap.insert(4, 12);
    treap.insert(7, 45);

    ASSERT_EQ (treap.size, 4);

    ASSERT_EQ (treap.k[0], 1);ASSERT_EQ (treap.d[0], 2);
    ASSERT_EQ (treap.k[1], 2);ASSERT_EQ (treap.d[1], 3);
    ASSERT_EQ (treap.k[2], 4);ASSERT_EQ (treap.d[2], 12);
    ASSERT_EQ (treap.k[3], 7);ASSERT_EQ (treap.d[3], 45);
}

TEST (TreadTest, RemoveValues) {

    struct Map treap;

    treap.insert(1, 2);
    treap.insert(2, 3);
    treap.insert(4, 12);
    treap.insert(7, 45);

    treap.erase(2);
    treap.erase(4);

    treap.insert(3, 98);
    treap.insert(5, 21);

    ASSERT_EQ (treap.size, 4);

    ASSERT_EQ (treap.k[0], 1);ASSERT_EQ (treap.d[0], 2);
    ASSERT_EQ (treap.k[1], 7);ASSERT_EQ (treap.d[1], 45);
    ASSERT_EQ (treap.k[2], 3);ASSERT_EQ (treap.d[2], 98);
    ASSERT_EQ (treap.k[3], 5);ASSERT_EQ (treap.d[3], 21);
}

TEST (TreadTest, InsertValuesToLimit) {

    struct Map treap;

    for (int i = 0; i < 20; ++i) {
        treap.insert(7, 45);
    }

    ASSERT_EQ (treap.size, MAX_SIZE);
}
