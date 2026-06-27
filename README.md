# LightControl

STM32F103C8T6 light control project migrated from a Keil Standard Peripheral Library project to a VS Code + STM32 HAL + CMake workflow.

## Hardware

- MCU: STM32F103C8T6
- ADC: PA0 / ADC1_IN0, labeled `ADC_Light`
- PWM output: PA1 / TIM2_CH2, labeled `TIM_Led`
- UART: USART1, 9600 baud, PA9 TX / PA10 RX
- OLED software I2C pins: PB7 SCL, PB8 SDA

## Features

- Automatic mode: reads ADC and maps the 12-bit value to PWM duty cycle 0-100.
- Manual mode: UART command `A` toggles mode, `+` and `-` adjust PWM, `0` turns PWM off, `S` prints current status.
- OLED displays current mode, ADC value, and PWM value.

## Build

This project was generated for the STM32Cube VS Code/CMake toolchain.

```powershell
cmake --preset Debug
cmake --build --preset Debug
```

Build outputs are generated under `build/` and are intentionally ignored by Git.

## Notes

- `LightControl.ioc` is the STM32CubeMX configuration source.
- `STM32 标准库到 HAL 移植对照笔记.txt` records the migration notes from Standard Peripheral Library to HAL.
