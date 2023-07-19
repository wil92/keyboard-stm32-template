# STM32 Keyboard code

This project has the necesary code for a keyboard using an STM32 board

## Dependencies

- cmake
- clion (optional)

## Using the code

The code is divided in two: *map.cpp* and *keyboard.cpp*. The *map.cpp* is just a simple code to store and query data
used by the main logic. The *keyboard.cpp* is where the main logic is, and it handler the keys press events and send
the information to the PC via USB.

To use the code, you only need to copy the information between the next comment:

```
// KEYBOARD BEGIN
...
// KEYBOARD END
```

And that code need to be pasted in the stm32cubeide new project in the next comment:

```
/* USER CODE BEGIN 4 */
extern USBD_HandleTypeDef hUsbDeviceFS;

... HERE

/* USER CODE END 4 */
```

Noticed that you also need to add the line of code `extern USBD_HandleTypeDef hUsbDeviceFS;`.

The next step is to copy the *map.cpp* file to the stm32cubeide project in the same folder that the
*main.cpp* is (./Core/Src/main.cpp)

### Adapt code to my keyboard grid

Usually the keyboards have a lot of keys and is not possible to connect them to each pin in the stm32 chip, this is why
we use a grid to maximize the inputs we can get. To adapt the grid you are using in your keyboard to this code, you need
to update the code between the comment: `// GRID BEGIN` and `// GRID END`.

**Adapt my grid**

TBD

## Tests

```
tbd
```
