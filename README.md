# Battery Status Indicator

This is a simple C program that reads the battery status of the system and turns on the Caps Lock, Num Lock, or Scroll Lock LED on the keyboard depending on the battery percentage.

## How to Use

1. Clone the repository:

    ```

    git clone https://github.com/sudo-do/battery-status-indicator.git

    ```

2. Navigate to the cloned directory:

    ```

    cd battery-status-indicator

    ```

3. Compile the program:

    ```

    make

    ```

4. Install the program:

    ```

    sudo ./install.sh

    ```

   The program will now run automatically at system startup.

5. If you want to uninstall the program, run:

    ```

    sudo ./uninstall.sh

    ```

## LED Indications

| Battery Percentage | Caps Lock LED | Num Lock LED | Scroll Lock LED |

| ------------------ | ------------- | ------------ | --------------- |

| Over 75%           | On            | Off          | Off             |

| Over 50%           | Off           | On           | Off             |

| Over 25%           | Off           | Off          | On              |

| 25% or below       | Off           | Off          | Off             |

## Dependencies

- `gcc`

- `make`

## Troubleshooting

- If the program is not running, make sure that the `install.sh` script has executable permissions. You can give it executable permissions by running:

    ```

    chmod +x install.sh

    ```

- If the LED lights are not turning on, make sure that the program has access to the keyboard device file. You can give it access by running:

    ```

    sudo chmod 666 /dev/input/event0

    ```

- If you encounter any other issues, please create an issue on the [GitHub repository(https://github.com/sudo-do/battery-status-indicator/issues) and I will do my best to help you resolve it.

