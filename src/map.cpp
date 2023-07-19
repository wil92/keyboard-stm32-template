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

#ifndef MAP_CPP
#define MAP_CPP

// REMOVE THIS CODE AFTER COPY FILE
inline int ccc = 0;

inline int HAL_GetTick() {
    return ccc++;
}
// REMOVE THIS CODE AFTER COPY FILE

#define MAX_SIZE 10

struct Map {

    int k[MAX_SIZE];
    int d[MAX_SIZE];
    int size = 0;

    bool has(int kk) {
        for (int i = 0; i < size; i++) {
            if (k[i] == kk) {
                return 1;
            }
        }
        return 0;
    }

    void insert(int kk, int dd) {
        if (size < MAX_SIZE) {
            k[size] = kk;
            d[size] = dd;
            size++;
        }
    }

    void erase(int kk) {
        for (int i = 0; i < size; i++) {
            if (k[i] == kk) {
                for (int j = i; j < size - 1; j++) {
                    k[j] = k[j + 1];
                    d[j] = d[j + 1];
                }
                size--;
                return;
            }
        }
    }
};

#endif //MAP_CPP
