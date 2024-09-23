
# cLog - Lightweight Logging Module in C

`cLog` is a simple, lightweight, and configurable logging module for C applications. It enables developers to log messages with various severity levels such as `INFO`, `WARNING`, `ERROR`, and `CRITICAL`. The module provides an easy-to-use interface for initializing, printing log messages, and adjusting the log level threshold dynamically.

## Features

- Supports different logging levels: `INFO`, `WARNING`, `ERROR`, `CRITICAL`
- Enables or disables logging globally
- Configurable log level threshold for filtering logs
- Flexible log output with user-defined print callbacks
- Small footprint and easy integration into embedded systems
- Logging can be disabled entirely at compile time with `ENABLE_LOGGING`

## How It Works

The `cLog` module is designed around a central configuration structure that holds the logging state, level threshold, and a user-defined print callback function.

The main components are:
- **Log Initialization**: Sets up the logging module by defining a print callback and log level threshold.
- **Log Levels**: Only logs at or above the configured threshold level are printed.
- **Log Output**: The user defines where and how logs are printed via a callback function.
- **Dynamic Configuration**: The logging threshold can be adjusted at runtime, and logging can be enabled or disabled as needed.

## Usage

### 1. Include the header file

Include the `log.h` file in your project where you want to use the logging module:

```c
#include "log.h"
```

### 2. Initialize the logger

Call `LOG_INIT()` to initialize the logging system with a print callback function and a log level threshold.

```c
LOG_INIT(MyPrintFunction, LOG_LEVEL_WARNING);
```

- `MyPrintFunction`: User-defined function for handling log output. This function should take a message and print it to the desired output (e.g., console, file, etc.).
- `LOG_LEVEL_WARNING`: Set the minimum level of messages to be printed. Only `WARNING` and more severe messages (e.g., `ERROR`, `CRITICAL`) will be logged.

### 3. Logging messages

Use `LOG_PRINT()` to log messages with different severity levels.

```c
LOG_PRINT(LOG_LEVEL_INFO, "This is an info message.");
LOG_PRINT(LOG_LEVEL_ERROR, "This is an error message: %d", errorCode);
```

### 4. Adjusting log level threshold

You can change the log level threshold at runtime using `LOG_SET_LEVEL_THRESHOLD()`:

```c
LOG_SET_LEVEL_THRESHOLD(LOG_LEVEL_ERROR); // Only ERROR and CRITICAL will be logged
```

### 5. Enable or disable logging
  ```c
  LOG_DISABLE(); // Disable log here
  /* Do some processing where we don't want to save the log messages */
  LOG_ENABLE(); // Enable the log again
  ```
## Example

```c
#include "log.h"

void MyPrintFunction(const char* msg, int length) {
    printf("%s\n", msg);
}

int main() {
    LOG_INIT(MyPrintFunction, LOG_LEVEL_WARNING);

    LOG_PRINT(LOG_LEVEL_INFO, "This message won't be printed because the log level is set to WARNING.");
    LOG_PRINT(LOG_LEVEL_ERROR, "This is an error message.");

    LOG_SET_LEVEL_THRESHOLD(LOG_LEVEL_INFO);
    LOG_PRINT(LOG_LEVEL_INFO, "This is an info message after changing the threshold.");

    LOG_DISABLE();
    LOG_PRINT(LOG_LEVEL_ERROR, "This message won't be printed because logging is disabled.");

    return 0;
}
```

## Compile-time Configuration

To enable or disable logging at compile time, you can define or undefine `ENABLE_LOGGING` in your build configuration or in the source code.

```c
#define ENABLE_LOGGING
```

If `ENABLE_LOGGING` is undefined, all logging functionality will be excluded from the compiled binary.

---