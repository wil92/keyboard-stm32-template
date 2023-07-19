//
// Created by Guillermo on 25.05.23.
//

#include "gtest/gtest.h"
#include "keyboard.cpp"

TEST (DelTest, isModifierKeyFunction) {
    ASSERT_TRUE(isModifierKey(0x80));
    ASSERT_TRUE(isModifierKey(0x81));
    ASSERT_TRUE(isModifierKey(0x82));
    ASSERT_TRUE(isModifierKey(0x83));
    ASSERT_TRUE(isModifierKey(0x84));
    ASSERT_TRUE(isModifierKey(0x85));
    ASSERT_TRUE(isModifierKey(0x86));
    ASSERT_TRUE(isModifierKey(0x87));

    ASSERT_FALSE(isModifierKey(0x100));
    ASSERT_FALSE(isModifierKey(0x79));
    ASSERT_FALSE(isModifierKey(0x88));
    ASSERT_FALSE(isModifierKey(0x90));
    ASSERT_FALSE(isModifierKey(0x0));
    ASSERT_FALSE(isModifierKey(0x20));
}

TEST (DelTest, CheckKeysFunction) {

    reportSent = 0;
    checkKeys();
    ASSERT_TRUE(reportSent);

    ASSERT_EQ (pressedKeysMap.size, 2);

    ASSERT_EQ (pressedKeysMap.k[0], 0);
    ASSERT_EQ (pressedKeysMap.d[0], 0x53);
    ASSERT_EQ (pressedKeysMap.k[1], 108);
    ASSERT_EQ (pressedKeysMap.d[1], 0x61);

    ASSERT_EQ (keyBoardHIDsub[KEYCODE1], 0x53);
    ASSERT_EQ (keyBoardHIDsub[KEYCODE2], 0x61);

    // recall with the same keys pressed
    reportSent = 0;
    checkKeys();
    ASSERT_TRUE(reportSent);

    // call a second time and remove and add new keys
    timeReadPin = 1;
    reportSent = 0;
    checkKeys();
    ASSERT_TRUE(reportSent);

    ASSERT_EQ (pressedKeysMap.size, 2);

    ASSERT_EQ (pressedKeysMap.k[0], 323);
    ASSERT_EQ (pressedKeysMap.d[0], 0x5B);
    ASSERT_EQ (pressedKeysMap.k[1], 429);
    ASSERT_EQ (pressedKeysMap.d[1], 0x5D);

    ASSERT_EQ (keyBoardHIDsub[KEYCODE1], 0x5B);
    ASSERT_EQ (keyBoardHIDsub[KEYCODE2], 0x5D);

    // recall with the same keys pressed
    reportSent = 0;
    checkKeys();
    ASSERT_TRUE(reportSent);

    // validate with all the keys pressed at the same time (the max is 10 keys)
    timeReadPin = 2;
    reportSent = 0;
    checkKeys();
    ASSERT_TRUE(reportSent);

    ASSERT_EQ (pressedKeysMap.size, MAX_SIZE);

    // call thirst time with empty keys
    timeReadPin = 3;
    reportSent = 0;
    checkKeys();
    ASSERT_TRUE(reportSent);

    ASSERT_EQ (pressedKeysMap.size, 0);

    ASSERT_EQ (keyBoardHIDsub[KEYCODE1], 0);
    ASSERT_EQ (keyBoardHIDsub[KEYCODE2], 0);
    ASSERT_EQ (keyBoardHIDsub[KEYCODE3], 0);
    ASSERT_EQ (keyBoardHIDsub[KEYCODE4], 0);
    ASSERT_EQ (keyBoardHIDsub[KEYCODE5], 0);
    ASSERT_EQ (keyBoardHIDsub[KEYCODE6], 0);

    // recall with the same keys pressed
    reportSent = 0;
    checkKeys();
    ASSERT_TRUE(reportSent);
}
