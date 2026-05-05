# ESP32 BLE Gamepad Manager

Desktop configuration tool for the ESP32 BLE Gamepad project.

The application connects to the gamepad over USB serial and sends runtime configuration commands to the ESP32 firmware. It is intended for calibration and tuning without reflashing the firmware.

## Features

- Detects available USB serial ports
- Connects to the ESP32 over serial
- Starts analogue stick calibration
- Updates analogue stick deadzone
- Updates motion sensitivity

## Requirements

- Linux
- Qt 5 or Qt 6
- Qt SerialPort
- CMake
- Flatpak and flatpak-builder
- ESP32 BLE Gamepad running the matching firmware

## Flatpak build, install and run

```bash
flatpak-builder --user --install --force-clean build-dir io.github.det_exe.ESP32_BLE_Gamepad_Manager.yml
flatpak run io.github.det_exe.ESP32_BLE_Gamepad_Manager
```

## Usage

1. Connect the gamepad to the computer over USB.
2. Launch Gamepad Manager.
3. Select the detected serial port.
4. Click **Connect to Port**.
5. Use the calibration, deadzone and motion sensitivity controls as required.

## Serial commands

The application sends the following commands to the firmware:

 `c` | Start analogue stick calibration |
 `d <value>` | Set analogue stick deadzone |
 `s <value>` | Set motion sensitivity |

## Notes

Calibration prompts are currently printed by the firmware over serial rather than displayed directly in the GUI.

