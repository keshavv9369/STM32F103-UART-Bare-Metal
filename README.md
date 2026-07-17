<div align="center">

# STM32F103 UART Bare-Metal

**Minimal UART transmit firmware for the STM32F103C8T6, running entirely on the default 8 MHz clock**

[![MCU](https://img.shields.io/badge/MCU-STM32F103C8T6-03234B?style=flat-square&logo=stmicroelectronics&logoColor=white)](https://www.st.com/en/microcontrollers-microprocessors/stm32f103c8.html)
[![Peripheral](https://img.shields.io/badge/Peripheral-USART-informational?style=flat-square)](#)
[![Clock](https://img.shields.io/badge/Clock-8%20MHz%20HSI%20(default)-informational?style=flat-square)](#)
[![IDE](https://img.shields.io/badge/IDE-STM32CubeIDE%20%7C%20IAR%20EWARM-03234B?style=flat-square)](#)
[![Language](https://img.shields.io/badge/Language-C-A8B9CC?style=flat-square&logo=c&logoColor=white)](#)
[![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)](#license)

</div>

---

## Overview

A deliberately minimal UART project for the **STM32F103C8T6** ("Blue Pill"): bring up
USART1 and transmit a message, with **no clock tree configuration at all**. The MCU
runs on its raw default clock — no PLL, no RCC reconfiguration — so this doubles as
the simplest possible starting point for UART on this chip: if this works, the
peripheral wiring and basic setup are sound before any clock-speed tuning enters
the picture.

The project is named `Send_hello` internally — its entire job is to get a "hello"
message out over the wire and confirm it arrives.

## Table of Contents

- [Design Notes](#design-notes)
- [Hardware](#hardware)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Roadmap](#roadmap)
- [License](#license)

---

## Design Notes

- **Clock:** No PLL, no RCC configuration of any kind. The MCU runs on its
  **default 8 MHz internal (HSI) clock** as-is out of reset. This keeps the example
  as close to bare-metal as possible and removes clock-tree bugs as a variable when
  debugging UART itself.
- **Peripheral:** USART1 is initialized and used purely for transmission — sending
  a fixed "hello" style message out over TX.
- **Two toolchains, one project:** the repo includes both an **STM32CubeIDE**
  project and an **IAR EWARM** project pointing at the same source, so it can be
  built and flashed from either environment.

## Hardware

| Item | Detail |
|---|---|
| MCU | STM32F103C8T6 (64 KB Flash / 20 KB RAM — "Blue Pill") |
| Clock | 8 MHz HSI, default / unconfigured — no PLL |
| UART | USART1, TX only, baud rate: *(fill in)* |
| Debug probe | ST-Link (SWD) |

> No external clock source, crystal configuration, or RCC setup required — this
> runs on whatever the chip does out of the box.

## Project Structure

```
.
├── Core/                     # Application code: main.c, USART1 setup, TX logic
├── Drivers/                  # STM32 HAL / CMSIS device drivers
├── Debug/                    # Build output (STM32CubeIDE)
├── EWARM/                    # IAR Embedded Workbench project files
├── Send_hello.ioc            # STM32CubeMX peripheral configuration
├── STM32F103C8TX_FLASH.ld    # Linker script
└── .project / .cproject / .mxproject   # STM32CubeIDE project files
```

## Getting Started

### Requirements
- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) **or**
  [IAR Embedded Workbench for ARM](https://www.iar.com/products/architectures/arm/iar-embedded-workbench-for-arm/)
- STM32F103C8T6 board + ST-Link programmer
- A serial terminal (PuTTY, minicom, Tera Term, etc.)

### Build & Flash

```
1. Clone the repo
2. Open Send_hello in STM32CubeIDE, or open the EWARM project in IAR
3. Build
4. Flash over SWD via ST-Link
5. Connect a USB-to-serial adapter to USART1 TX/RX
   → Open a terminal at <baud rate — fill in>
6. Reset the board
```

You should see the "hello" message appear in the terminal on every reset —
confirming USART1 is transmitting correctly on the unconfigured default clock.

## Roadmap

- [ ] Document exact USART1 baud rate and pin mapping
- [ ] Add RX handling (currently TX-only)
- [ ] Add a PLL-configured variant to compare against the raw 8 MHz baseline

## License

MIT — see [LICENSE](LICENSE) for details.

---

<div align="center">
<sub>Built and maintained by <a href="https://github.com/keshavv9369">keshavv9369</a></sub>
</div>
