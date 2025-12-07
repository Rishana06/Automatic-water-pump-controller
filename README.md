# Smart Water Level Monitoring System

## Overview

An intelligent water tank monitoring system using an HC-SR04 ultrasonic sensor to measure water level in real-time. The system calculates water level percentage, displays readings via Serial Monitor, and activates an LED warning when water drops below 30% capacity.

![Real-time System Visualization](image1.png)  
*Figure 1: Water level monitoring system with ultrasonic sensor and LED alert*

## Features

- Contactless ultrasonic measurement (±3mm accuracy)
- Real-time percentage calculation
- LED alert when water drops below 30%
- Tank full detection
- Updates every 500ms
- Adjustable for different tank sizes

## How It Works

![System Workflow Diagram](image2.png)  
*Figure 2: Complete measurement and calculation logic flow*

### Ultrasonic Distance Measurement

The HC-SR04 sensor uses sound waves to measure distance:

1. Send 10μs HIGH pulse on Trig pin
2. Sensor emits 8 ultrasonic bursts at 40kHz
3. Sound waves bounce off water surface and return
4. Measure time between emission and reception
5. Calculate: `Distance (cm) = Duration × 0.034 / 2`

### Water Level Calculation

```cpp
// Given measurements
TANK_HEIGHT = 72cm      // Total height from sensor to tank bottom
MIN_LEVEL = 2cm         // Minimum measurable level

// Calculate water level
distance = duration × 0.034 / 2
level = TANK_HEIGHT - distance
percent = ((level - MIN_LEVEL) × 100) / (TANK_HEIGHT - MIN_LEVEL)
```

### Example

```
Tank Height: 72cm
Distance: 29cm
Water Level = 72 - 29 = 43cm
Percentage = ((43 - 2) × 100) / 70 = 58.57%
```

## Hardware Requirements

### Components

- **Microcontroller**: ESP32, Arduino Uno, or Arduino Nano
- **HC-SR04 Ultrasonic Sensor** (5V, 2-400cm range)
- **LED** (Red recommended) + 220Ω resistor
- **Jumper wires** and mounting hardware

![Hardware Setup](image3.png)  
*Figure 3: Sensor installation and wiring diagram*

### Pin Configuration

| Component | GPIO Pin | Description |
|-----------|----------|-------------|
| HC-SR04 Trig | 18 | Trigger pulse output |
| HC-SR04 Echo | 19 | Echo pulse input |
| LED | 25 | Low water alert |

## Circuit Connections

```
HC-SR04 Sensor
VCC  → 5V
Trig → GPIO 18
Echo → GPIO 19
GND  → GND

LED Connection
GPIO 25 → 220Ω Resistor → LED (+) → LED (-) → GND
```

**Note for ESP32**: Use voltage divider (1kΩ and 2kΩ) on Echo pin to reduce 5V to 3.3V.

## Installation

### Software Setup

1. Install Arduino IDE (1.8.x or newer)
2. Select your board (Arduino Uno/Nano or ESP32)
3. Select Port
4. Upload code
5. Open Serial Monitor (9600 baud)

### Physical Installation

1. **Mount sensor at top center of tank**
   - Point straight down (perpendicular to water)
   - Distance to tank bottom = 72cm (adjust `TANK_HEIGHT` if different)
   - Minimum 5cm clearance from walls

2. **Calibrate tank**
   - Measure actual tank height
   - Update `TANK_HEIGHT` in code
   - Set `MIN_LEVEL` for minimum safe water level

3. **Install LED**
   - Mount in visible location
   - Verify polarity (longer leg = positive)

## Usage

### Serial Monitor Output

```
Water level: 43
Percentage of water: 60
─────────────────────
Water level: 20
Percentage of water: 25
[LED ON - Low Water Alert]
```

### Status Indicators

| Percentage | LED State | Action |
|------------|-----------|--------|
| 100% | OFF | Stop filling |
| 31-99% | OFF | Normal |
| 0-30% | **ON** | ⚠️ Refill needed |

## Configuration

```cpp
// Adjust for your tank
const int TANK_HEIGHT = 72;  // cm - sensor to tank bottom
const int MIN_LEVEL = 2;     // cm - minimum level

// Change warning threshold
if(percent <= 30) {  // Change 30 to desired %
  digitalWrite(LED, HIGH);
}
```

### Different Tank Sizes

```cpp
// Small (30cm)
const int TANK_HEIGHT = 30;
const int MIN_LEVEL = 1;

// Large (200cm)
const int TANK_HEIGHT = 200;
const int MIN_LEVEL = 5;
```

## Troubleshooting

| Issue | Solution |
|-------|----------|
| Reading shows 0 or negative | Mount sensor higher, check TANK_HEIGHT |
| Erratic readings | Adjust sensor to point straight down |
| No echo detected | Check Trig/Echo connections (GPIO 18/19) |
| Percentage over 100% | Measure and update TANK_HEIGHT |
| LED doesn't light | Verify GPIO 25 and LED polarity |
| Fluctuating readings | Average multiple readings |

## Advanced Features

### Smoothing Algorithm

```cpp
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int total = 0;

void loop() {
  total = total - readings[readIndex];
  readings[readIndex] = distance;
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  int average = total / numReadings;
  level = TANK_HEIGHT - average;
}
```

### Temperature Compensation

```cpp
float temperature = 25.0;  // From temp sensor
float speedOfSound = 331.4 + (0.606 * temperature);
float adjustedDistance = (duration * speedOfSound) / 20000;
```

## Applications

- **Residential**: Overhead tanks, underground sumps, swimming pools
- **Agricultural**: Irrigation tanks, livestock troughs, fish ponds
- **Industrial**: Chemical tanks, cooling towers, boiler feed tanks
- **Smart Buildings**: Automated pump control, leak detection

## Cost Analysis

| Component | Cost (USD) |
|-----------|-----------|
| HC-SR04 Sensor | $2-4 |
| ESP32/Arduino | $5-15 |
| LED + Resistor | $0.50 |
| Wires & Mounting | $2-5 |
| **Total** | **$10-25** |

## Resources

- [HC-SR04 Datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)
- [Arduino pulseIn() Reference](https://www.arduino.cc/reference/en/language/functions/advanced-io/pulsein/)

---

**Version**: 1.0  
**Last Updated**: December 2025  
**Accuracy**: ±3mm with proper installation  
**Tank Capacity**: Configurable (2cm - 400cm range)