/*
 * Copyright 2023 Guillermo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DEL_CPP
#define DEL_CPP

#include <cstdint>
#include <cstring>


// -------------------------------------------
// ---------STRUCTURAL CODE-------------------
// -------------------------------------------
typedef struct _USBD_HandleTypeDef { // NOLINT(bugprone-reserved-identifier)
    uint8_t id;
} USBD_HandleTypeDef;
USBD_HandleTypeDef hUsbDeviceFS = USBD_HandleTypeDef();

typedef struct {
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint32_t LCKR;
} GPIO_TypeDef;

#define GPIOB ((GPIO_TypeDef *)0x00000C00UL)
#define GPIOA ((GPIO_TypeDef *)0x00000D00UL)

#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */

typedef enum {
    GPIO_PIN_RESET = 0u,
    GPIO_PIN_SET
} GPIO_PinState;

void setKeyBoardKeys();

uint16_t pin;
GPIO_PinState state;
int timeReadPin = 0;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"

void HAL_GPIO_WritePin(GPIO_TypeDef *a, uint16_t b, GPIO_PinState c) {
#pragma clang diagnostic pop
    pin = b;
    state = c;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"

bool HAL_GPIO_ReadPin(GPIO_TypeDef *a, uint16_t b) {
#pragma clang diagnostic pop
    if (timeReadPin == 0) {
        return (state == GPIO_PIN_SET && pin == GPIO_PIN_8 && b == GPIO_PIN_3)
               || (state == GPIO_PIN_SET && pin == GPIO_PIN_7 && b == GPIO_PIN_1);
    } else if (timeReadPin == 1) {
        return (state == GPIO_PIN_SET && pin == GPIO_PIN_4 && b == GPIO_PIN_1)
               || (state == GPIO_PIN_SET && pin == GPIO_PIN_5 && b == GPIO_PIN_0);
    } else if (timeReadPin == 2) {
        return true;
    } else {
        return false;
    }
}

int reportSent = 0;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"

uint8_t USBD_HID_SendReport(USBD_HandleTypeDef *pdev,
                            uint8_t *report,
                            uint16_t len) {
#pragma clang diagnostic pop
    reportSent = 1;
    return 0;
}

// -------------------------------------------
// ---------STRUCTURAL CODE-------------------
// -------------------------------------------


// KEYBOARD BEGIN
#define MODIFIER 0
#define RESERVED 1
#define KEYCODE1 2
#define KEYCODE2 3
#define KEYCODE3 4
#define KEYCODE4 5
#define KEYCODE5 6
#define KEYCODE6 7

#define OUTPUT_PINS 5
#define INPUT_PINS 4
#define base 107
#define MAX_SIZE 10

// MAP STUFF BEGIN
typedef struct Map {
    int k[MAX_SIZE];
    int d[MAX_SIZE];
    int size;
} Map;

int has(Map *m, int kk) {
    for (int i = 0; i < m->size; i++) {
        if (m->k[i] == kk) {
            return 1;
        }
    }
    return 0;
}

void insert(Map *m, int kk, int dd) {
    if (m->size < MAX_SIZE) {
        m->k[m->size] = kk;
        m->d[m->size] = dd;
        m->size++;
    }
}

void erase(Map *m, int kk) {
    for (int i = 0; i < m->size; i++) {
        if (m->k[i] == kk) {
            for (int j = i; j < m->size - 1; j++) {
                m->k[j] = m->k[j + 1];
                m->d[j] = m->d[j + 1];
            }
            m->size--;
            return;
        }
    }
}
// MAP STUFF END

Map pressedKeysMap;
uint8_t keyBoardHIDsub[8];

bool isModifierKey(int k) {
    // modifier keys
    return 0x80 <= k && k <= 0x87;
//	0x80 KEY_LEFT_CTRL
//	0x81 KEY_LEFT_SHIFT
//	0x82 KEY_LEFT_ALT
//	0x83 KEY_LEFT_GUI
//	0x84 KEY_RIGHT_CTRL
//	0x85 KEY_RIGHT_SHIFT
//	0x86 KEY_RIGHT_ALT
//	0x87 KEY_RIGHT_GUI
}

// GRID BEGIN
GPIO_TypeDef *outputPins_GPIOx[OUTPUT_PINS] = {GPIOB, GPIOB, GPIOB, GPIOB,
                                               GPIOB};
uint16_t outputPins_GPIO_Pin[OUTPUT_PINS] = {GPIO_PIN_8, GPIO_PIN_7,
                                             GPIO_PIN_6,
                                             GPIO_PIN_5, GPIO_PIN_4};

GPIO_TypeDef *inputPins_GPIOx[INPUT_PINS] = {GPIOB, GPIOB, GPIOB, GPIOA};
uint16_t inputPins_GPIO_Pin[INPUT_PINS] = {GPIO_PIN_3, GPIO_PIN_1, GPIO_PIN_0,
                                           GPIO_PIN_15};

uint8_t keyMapping[OUTPUT_PINS][INPUT_PINS] = {{0x53, 0x60, 0x5E, 0x62},
                                               {
                                                0x54, 0x61, 0x59, 0x63},
                                               {0x55, 0x57, 0x5A, 0x00},
                                               {0x56, 0x5C,
                                                            0x5B, 0x00},
                                               {0x5F, 0x5D, 0x28, 0x00}};
// GRID END

void checkKeys() {
    Map newPressedKeysMap;
    newPressedKeysMap.size = 0;

    for (int i = 0; i < OUTPUT_PINS; i++) {
        HAL_GPIO_WritePin(outputPins_GPIOx[i], outputPins_GPIO_Pin[i],
                          GPIO_PIN_SET);
        for (int j = 0; j < INPUT_PINS; j++) {
            if (HAL_GPIO_ReadPin(inputPins_GPIOx[j], inputPins_GPIO_Pin[j])) {
                // add key to the pressed keys
                insert(&newPressedKeysMap, i * base + j, keyMapping[i][j]);
            }
        }
        HAL_GPIO_WritePin(outputPins_GPIOx[i], outputPins_GPIO_Pin[i],
                          GPIO_PIN_RESET);
    }

    // check un-pressed keys
    int toRemove[MAX_SIZE], toRemoveCount = 0;
    for (int i = 0; i < pressedKeysMap.size; i++) {
        if (!has(&newPressedKeysMap, pressedKeysMap.k[i])) {
            toRemove[toRemoveCount++] = pressedKeysMap.k[i];
        }
    }
    for (int i = 0; i < toRemoveCount; i++) {
        erase(&pressedKeysMap, toRemove[i]);
    }

    // check pressed keys
    for (int i = 0; i < newPressedKeysMap.size; i++) {
        if (!has(&pressedKeysMap, newPressedKeysMap.k[i])) {
            insert(&pressedKeysMap, newPressedKeysMap.k[i],
                   newPressedKeysMap.d[i]);
        }
    }

    // update keyBoardHIDsub
    setKeyBoardKeys();

    // send keyBoardHIDsub if there is changes
    USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t * ) & keyBoardHIDsub,
                        sizeof(keyBoardHIDsub));
}

void setKeyBoardKeys() {
    memset(keyBoardHIDsub, 0, sizeof(keyBoardHIDsub));

    int mofifierKeys = 0, modifierKey;
    for (int i = 0; i < pressedKeysMap.size; i++) {
        if (isModifierKey(pressedKeysMap.k[i])) {
            mofifierKeys++;
            modifierKey = pressedKeysMap.d[i];
        }
    }

    if (mofifierKeys == 1) {
        keyBoardHIDsub[MODIFIER] = modifierKey;
    }

    for (int j = 0, i = KEYCODE1; j < pressedKeysMap.size && i <= KEYCODE6; j++) {
        if ((mofifierKeys == 1 && pressedKeysMap.d[j] != modifierKey)
            || mofifierKeys != 1) {
            keyBoardHIDsub[i++] = pressedKeysMap.d[j];
        }
    }
}
// KEYBOARD END

#endif //DEL_CPP
