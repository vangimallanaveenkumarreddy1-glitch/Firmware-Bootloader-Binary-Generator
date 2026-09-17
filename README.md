#  Firmware Bootloader & Binary Generator

 

A C-based firmware simulation tool that generates binary firmware images for three device types (Smart Phone, Microwave, Car), loads them back, validates integrity, and boots the device with structured data display. Includes interactive settings modification for each device.

---

## 📑 Table of Contents

| # | Section | Description |
|---|---|---|
| 1 | [Overview](#1--overview) | What the project does |
| 2 | [Features](#2--features) | Key capabilities |
| 3 | [Project Structure](#3--project-structure) | File layout |
| 4 | [Tech Stack](#4--tech-stack) | Languages & tools |
| 5 | [Supported Devices](#5--supported-devices) | 3 device types |
| 6 | [Device Specifications](#6--device-specifications) | Fields & structs |
| 7 | [How It Works](#7--how-it-works) | Workflow diagram |
| 8 | [Installation & Build](#8--installation--build) | Setup steps |
| 9 | [Usage](#9--usage) | Running the program |
| 10 | [Menu System](#10--menu-system) | Navigation map |
| 11 | [Binary File Format](#11--binary-file-format) | firmware.bin layout |
| 12 | [Data Structures](#12--data-structures) | Struct reference |
| 13 | [Function Reference](#13--function-reference) | All functions |
| 14 | [Validation Rules](#14--validation-rules) | Firmware checks |
| 15 | [Sample Session](#15--sample-session) | Full walkthrough |
| 16 | [Known Limitations](#16--known-limitations) | Current constraints |
| 17 | [Roadmap](#17--roadmap) | Planned improvements |
| 18 | [License](#18--license) | MIT License |
| 19 | [Author](#19--author) | Credits |

---

## 1. 🔍 Overview

**Firmware Bootloader & Binary Generator** simulates the firmware lifecycle of embedded devices in C:

1. **Configure** device settings (name, brightness, temperature, tyre pressure, etc.)
2. **Serialize** settings into a binary file (`firmware.bin`)
3. **Load** the binary back into memory
4. **Validate** integrity (size, type match, character score)
5. **Boot** the device with a formatted display of its firmware contents

It demonstrates real-world embedded concepts: memory layout, `fread`/`fwrite`, struct packing, pointer casting, and firmware validation.

---

## 2. ✨ Features

| Feature | Description | Status |
|---|---|---|
| 🧱 Binary Serialization | Structs written to `firmware.bin` via `fwrite` | ✅ |
| 📥 Firmware Loading | Read binary back into memory buffer | ✅ |
| ✅ Validation | Size check, type match, character score | ✅ |
| 🚀 Boot Simulation | Structured device-specific boot output | ✅ |
| ⚙️ Settings Editor | Change each field interactively per device | ✅ |
| 🖥️ Multi-Device Menu | Smart Phone, Microwave, Car | ✅ |
| 🧩 Modular Code | Split across `header.h`, `main.c`, `bin.c`, `bin.h`, `menu.c` | ✅ |
| 🎨 Console Output | Emoji and ASCII formatting for readability | ✅ |

---

## 3. 📁 Project Structure

| File | Purpose | Approx. Lines |
|---|---|---|
| `bin.h` | Prototype for binary creation | ~8 |
| `bin.c` | Firmware binary generation (`fwrite`) | ~50 |
| `header.h` | Structs, macros, all prototypes | ~50 |
| `main.c` | Display, load, validate, boot, edit logic | ~350 |
| `menu.c` | Main menu & device navigation | ~100 |
| `firmware.bin` | Generated output file | — |
| `README.md` | This documentation | — |

```
.
├── bin.h
├── bin.c
├── header.h
├── main.c
├── menu.c
├── firmware.bin      (auto-generated)
└── README.md
```

---

## 4. 🛠️ Tech Stack

| Category | Technology |
|---|---|
| **Language** | C (C99 or later) |
| **Compiler** | GCC / Clang / MSVC |
| **Libraries** | `stdio.h`, `stdlib.h`, `string.h`, `unistd.h` |
| **File Format** | Raw binary (`.bin`) |
| **Build System** | Manual `gcc` / Makefile |
| **Platform** | Linux, WSL, macOS |

---

## 5. 📱 Supported Devices

| # | Device | Description | Firmware Size |
|---|---|---|---|
| 1 | **Smart Phone** | Mobile device with brightness & storage | `sizeof(Phone)` |
| 2 | **Microwave** | Oven with temp, child lock & timer | `sizeof(Mcw)` |
| 3 | **Car** | Vehicle with odometer, tyre pressure & fuel | `sizeof(Car)` |

---

## 6. 📊 Device Specifications

### Smart Phone (`Phone`)

| Field | Type | Size | Example | Description |
|---|---|---|---|---|
| `name` | `char[30]` | 30 B | `"Android"` | Device name |
| `brit` | `int` | 4 B | `30` | Brightness (0–100) |
| `storage` | `int` | 4 B | `78` | Storage in GB |
| `date` | `char[10]` | 10 B | `"01-09-2026"` | Build date |
| `sim` | `char[30]` | 30 B | `"jio"` | SIM provider |

### Microwave (`Mcw`)

| Field | Type | Size | Example | Description |
|---|---|---|---|---|
| `name` | `char[30]` | 30 B | `"Philips"` | Brand |
| `heat` | `int` | 4 B | `24` | Temperature (°C) |
| `lock` | `int` | 4 B | `0` | Child lock (0/1) |
| `date` | `char[10]` | 10 B | `"01-09-2026"` | Build date |
| `mode` | `char[30]` | 30 B | `"Auto"` | Cooking mode |
| `timer` | `int` | 4 B | `50` | Timer (seconds) |

### Car (`Car`)

| Field | Type | Size | Example | Description |
|---|---|---|---|---|
| `name` | `char[30]` | 30 B | `"TATA"` | Brand |
| `odo` | `char[10]` | 10 B | `"1200"` | Odometer (KM) |
| `pres` | `int` | 4 B | `300` | Tyre pressure (PSI) |
| `date` | `char[10]` | 10 B | `"01-09-2026"` | Build date |
| `fuel` | `char[30]` | 30 B | `"60"` | Fuel level (%) |
| `mode` | `char[30]` | 30 B | `"Auto"` | Driving mode |

---

## 7. ⚙️ How It Works

```
┌─────────────────────┐
│  Configure Device   │  (edit fields)
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│  Serialize Struct   │  fwrite(&type, 1, sizeof, fp)
│  → firmware.bin     │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│  Load Binary        │  fread into firmware.data[4096]
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│  Validate Firmware  │  size, type, char score
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│  Boot Device        │  cast to struct, print fields
└─────────────────────┘
```

---

## 8. 🚀 Installation & Build

### Prerequisites

| Requirement | Version | Notes |
|---|---|---|
| C Compiler | GCC 7+ / Clang 10+ | C99 standard |
| OS | Linux / WSL / macOS | Needs `<unistd.h>` for `sleep()` |
| Terminal | UTF-8 capable | For emoji output |

### Build Commands

| Method | Command |
|---|---|
| **Single-line build** | `gcc menu.c main.c bin.c -o bootloader` |
| **With warnings** | `gcc -Wall -Wextra -std=c11 menu.c main.c bin.c -o bootloader` |
| **Debug build** | `gcc -g -fsanitize=address menu.c main.c bin.c -o bootloader` |
| **Using Makefile** | `make` |
| **Clean** | `rm -f *.o bootloader firmware.bin` |

---

## 9. 🖥️ Usage

| Step | Action |
|---|---|
| 1 | Run `./bootloader` |
| 2 | Select device (1–4) |
| 3 | Choose operation (1–5) |
| 4 | Generate → Load → Validate → Boot |
| 5 | Exit through menus |

```bash
./bootloader
```

---

## 10. 🧭 Menu System

### Main Menu

| Option | Action |
|---|---|
| 1 | Smart Phone |
| 2 | Microwave |
| 3 | Car |
| 4 | Exit Program |

### Device Sub-Menu

| Option | Action | Requires Binary |
|---|---|---|
| 1 | Show Values | — |
| 2 | Convert Settings to Binary | — |
| 3 | Load Settings (Load + Validate + Boot) | ✅ |
| 4 | Change Values | — |
| 5 | Exit to Main Menu | — |

---

## 11. 💾 Binary File Format

The firmware file `firmware.bin` stores a **raw memory dump** of the selected struct.

### Smart Phone Example

| Offset | Size | Field | Bytes |
|---|---|---|---|
| 0 | 30 | `name` | ASCII string + null padding |
| 30 | 4 | `brit` | Little-endian `int` |
| 34 | 4 | `storage` | Little-endian `int` |
| 38 | 10 | `date` | ASCII string |
| 48 | 30 | `sim` | ASCII string |
| **Total** | **78 B** | | |

> **Note:** Total size depends on struct padding and alignment — check with `sizeof(Phone)`. The program prints the exact byte count after creation.

---

## 12. 🧱 Data Structures

```c
typedef struct phone {
    char name[30];
    int  brit;
    int  storage;
    char date[10];
    char sim[30];
} Phone;

typedef struct car {
    char name[30];
    char odo[10];
    int  pres;
    char date[10];
    char fuel[30];
    char mode[30];
} Car;

typedef struct MW {
    char name[30];
    int  heat;
    int  lock;
    char date[10];
    char mode[30];
    int  timer;
} Mcw;

typedef struct all {
    Phone phone;
    Car   car;
    Mcw   MW;
} Type;

typedef struct firmware {
    char          file[100];      // Expected device type
    unsigned char data[4096];     // Raw binary buffer
    int           size;           // Bytes read
    int           valid;          // 0 = invalid, 1 = valid
} firmware;
```

---

## 13. 🔧 Function Reference

| Function | Signature | Returns | Purpose |
|---|---|---|---|
| `creat_bin` | `void creat_bin(Type*, char*)` | — | Serialize struct → `firmware.bin` |
| `disp_phone` | `void disp_phone(Phone*)` | — | Pretty-print phone data |
| `disp_mic` | `void disp_mic(Mcw*)` | — | Pretty-print microwave data |
| `disp_car` | `void disp_car(Car*)` | — | Pretty-print car data |
| `loadfirmware` | `void loadfirmware(firmware*, char*)` | — | Read `.bin` into buffer + null-terminate strings |
| `validate` | `void validate(firmware*, char*)` | — | Check size, type, char score |
| `boot` | `void boot(firmware*, char*)` | — | Cast buffer → struct, print boot screen |
| `change_phone_data` | `void change_phone_data(Phone*)` | — | Interactive field editor |
| `change_microwave_data` | `void change_microwave_data(Mcw*)` | — | Interactive field editor |
| `change_car_data` | `void change_car_data(Car*)` | — | Interactive field editor |

---

## 14. ✅ Validation Rules

The `validate()` function applies **three checks**:

| # | Check | Fail Condition | Result |
|---|---|---|---|
| 1 | Size Non-Zero | `fw->size == 0` | Invalid — no firmware loaded |
| 2 | Type Match | `strcmp(fw->file, type) != 0` | Invalid — firmware from another device |
| 3 | Min Size | `fw->size < sizeof(struct)` | Invalid — truncated data |
| 4 | Char Score | `< 50%` printable chars or `\0` | Invalid — corrupted firmware |

If all pass → `fw->valid = 1`, ready to boot.

---

## 15. 📸 Sample Session

```
=======================================================================

                            BOOTLOADER

=======================================================================

Select Meachine
---------------------
1. Smart Phone
2. Microwave
3. Car
4. Exit

Enter your choice : 1

        Smart Phone
-----------------------

1. Show Values
2. Convert setting to binary
3. Load Settings
4. Change Values
5. Exit

Eter your choice : 1

---------- Phone Data ----------

Device Name : Android
Sim Card : jio
Brightness level : 30
Storage : 78
Date : 01-09-2026

Eter your choice : 2

Created firmware.bin.... (78 bytes)

Eter your choice : 3

Firmware loading.......
  Cleaned phone data strings

## Firmware lodded sucessfully..

# Validating firmware...........

## Firmware validated successfully!
   Device Type: Smart Phone
   File Size: 78 bytes
   Validation Score: 96.2 %

# Booting...........

=====================================================================
                             BOOTING FIRMWARE
=======================================================================
  Device Type: Smart Phone
  Firmware Size: 78 bytes
  Boot Status: INITIALIZING...

SMART PHONE FIRMWARE DETAILS
-------------------------------
Device Name      : Android
SIM Card         : jio
Brightness Level : 30 %
Storage          : 78 GB
Date             : 01-09-2026
----------------------------------------

Phone initialized successfully!!!!!!!!

==========================================================
                         BOOT COMPLETE
===========================================================
```

---

## 16. ⚠️ Known Limitations

| # | Issue | Impact | Workaround |
|---|---|---|---|
| 1 | Fixed `data[4096]` buffer | Max firmware size | Increase array if needed |
| 2 | Only last-created device binary persists | Overwritten on new creation | Save separately |
| 3 | Struct padding varies by platform | Portability of `.bin` | Use `#pragma pack(1)` |
| 4 | No checksum/CRC | Silent corruption possible | Add CRC32 check |
| 5 | `scanf` without width limit | Buffer overflow risk | Use `fgets` + `sscanf` |
| 6 | Manual string null-termination | Easy to forget on new fields | Automate in loader |
| 7 | `date[10]` cannot hold `YYYY-MM-DD\0` | Truncates with NUL in C std format | Use `date[11]` |

---

## 17. 🚧 Roadmap

| Version | Feature | Status |
|---|---|---|
| 1.1 | CRC32 checksum in binary | 📋 Planned |
| 1.2 | `#pragma pack(1)` for portability | 📋 Planned |
| 1.3 | Export firmware as hex dump | 📋 Planned |
| 1.4 | Load firmware from external path | 📋 Planned |
| 1.5 | Support for multiple saved binaries | 📋 Planned |
| 2.0 | Add versioning header to `.bin` | 🔮 Future |
| 2.1 | Simulated OTA update flow | 🔮 Future |

---

## 18. 📜 License

This project is licensed under the **MIT License**.

```
MIT License

Copyright (c) 2024 Naveen Reddy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```

---

## 19. 👤 Author

| Field | Info |
|---|---|
| **Name** | VANGIMALLA NAVEEN KUMAR REDDY |
| **Role** | C Developer / Student |
| **Location** | India |
| **Project** | Firmware Bootloader & Binary Generator |
| **Year** | 2026 |

---

⭐ **If you found this useful, give it a star!**
