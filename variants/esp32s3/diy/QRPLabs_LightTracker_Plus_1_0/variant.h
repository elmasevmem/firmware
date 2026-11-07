/*

 QRP Labs LightTracker Plus v1.0
 ESP32-S3 MINI (8 MB flash, no PSRAM) + EBYTE E22-400M30S (SX1268, 433 MHz, 1 W)
 + Quectel L80 GPS + 0.96" SSD1306 128x64 I2C OLED header.

 https://shop.qrp-labs.com/aprs/lighttrackerplus

 Pins checked against:
   - lightaprs/LightTracker-Plus-1.0 (All_Modules_Test)
   - lightaprs/LightLoRaAPRS (variants/light_tracker_plus_v1/variant.h)
   - richonguzman/LoRa_APRS_Tracker (variants/QRPLabs_LightTracker_Plus_1_0)

*/

// OLED header (SSD1306 128x64, 0x3C - auto-detected on I2C)
#define I2C_SDA 3
#define I2C_SCL 4
#define HAS_SCREEN 1

// GNSS: Quectel L80 (9600 baud). Pin names are from the ESP32 side:
// ESP32 RX <- GPIO18 <- GPS TX,  ESP32 TX -> GPIO17 -> GPS RX
#define GPS_RX_PIN 18
#define GPS_TX_PIN 17
#define GPS_BAUDRATE 9600
// GPS power goes through a PNP high-side switch: LOW = GPS on, HIGH = GPS off
#define PIN_GPS_EN 33
#define GPS_EN_ACTIVE LOW

// Button (BOOT, GPIO0, active low)
#define BUTTON_PIN 0

// User LED (GPIO16, active high)
#define LED_POWER 16

// Battery sense: GPIO1 through a 560k / 100k divider -> (560 + 100) / 100 = 6.6
// Fine-tune from the app with Power > ADC multiplier override if the reading is off.
#define BATTERY_PIN 1
#define ADC_MULTIPLIER 6.6
#define ADC_REFERENCE REF_3V3
#define ADC_CHANNEL ADC_CHANNEL_0 // GPIO1 = ADC1_CH0
#define BATTERY_SENSE_RESOLUTION_BITS ADC_RESOLUTION

// SPI (LoRa)
#define LORA_SCK 12
#define LORA_MISO 13
#define LORA_MOSI 11
#define LORA_CS 10

// LoRa: EBYTE E22-400M30S (SX1268)
#define USE_SX1268
#define LORA_RESET 9
#define LORA_DIO1 5 // SX126x IRQ
#define LORA_DIO2 6 // SX126x BUSY

#define SX126X_CS LORA_CS
#define SX126X_DIO1 LORA_DIO1
#define SX126X_BUSY LORA_DIO2
#define SX126X_RESET LORA_RESET
// E22 RF switch is driven by the ESP32 (DIO2 is not wired to it)
#define SX126X_RXEN 42
#define SX126X_TXEN 14
// E22 module power switch (HIGH = on)
#define SX126X_POWER_EN 21

// E22 uses a 1.8 V TCXO on DIO3
#define SX126X_DIO3_TCXO_VOLTAGE 1.8
#define TCXO_OPTIONAL // also try XTAL if the TCXO init fails

// E22-400M30S: ~30 dBm out with the SX1268 at 22 dBm. Same PA stage as the E22-900M30S,
// so use the same gain; the app then shows the real antenna-port power.
#ifndef TX_GAIN_LORA
#define TX_GAIN_LORA 7
#endif
#ifndef SX126X_MAX_POWER
#define SX126X_MAX_POWER 22
#endif
