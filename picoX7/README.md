# Hardware config picoX7

Hardware config to support a MIDI synthesizer with DAC, 16x2 LCD and 2x7
segment LED.

![Prototype](docs/breadboard_v0.04.jpg)

[Schematic](docs/schematic_v0.05.pdf) for the above.

## Config variations

| Config | Supported targets | Description |
|------------|--------|-------------|
| I2S_DAC | rpipico, rpipico2 | Generic I2S DAC |
| PWM_DAC | rpipico, rpipico2 | Pulse Width Modulation DAC |
| WAVESHARE_REV2_1| rpipico, rpipico2 | WAVESHARE I2S DAC (piggy back) |
| PIMORONI_PICO_AUDIO | rpipico, rpipico2 | Pimoroni pico audio I2S DAC (piggy back) |
| PIMORONI_VGA_DEMO | rpipico | Pimoroni VGA demo board |
| NATIVE | native | |

## Pin out

### I2S_DAC
```
                   +-----------+
(Debug) TX UART <- |  1     40 | <> vbus +5v
                   |  2     39 | <> vsys
            gnd ## |  3     38 | ## gnd
                   |  4     37 | <- 3v3-en
                   |  5     36 | -> 3v3
                   |  6     35 | <- adc-vref
                   |  7     34 | -> I2S LRCLK
            gnd ## |  8     33 | ## agnd
                   |  9     32 | -> I2S SCLK
                   | 10     31 | -> I2S SD
                   | 11     30 | <- run
                   | 12     29 |    
            gnd ## | 13     28 | ## gnd
                   | 14     27 | <- UART RX (MIDI in)
                   | 15     26 |    
                   | 16     25 | -> I2C SCL (16x2 LCD)
                   | 17     24 | -> I2C SDA (16x2 LCD)
            gnd ## | 18     23 | ## gnd
                   | 19     22 | -> 7-SEG LED clk
                   | 20     21 | -> 7-SEG LED data
                   +-----------+
```
### PWM_DAC
```
                   +-----------+
(Debug) TX UART <- |  1     40 | <> vbus +5v
                   |  2     39 | <> vsys
            gnd ## |  3     38 | ## gnd
                   |  4     37 | <- 3v3-en
                   |  5     36 | -> 3v3
                   |  6     35 | <- adc-vref
                   |  7     34 |    
            gnd ## |  8     33 | ## agnd
                   |  9     32 |    
                   | 10     31 | -> PWM (audio)
                   | 11     30 | <- run
                   | 12     29 |    
            gnd ## | 13     28 | ## gnd
                   | 14     27 | <- UART RX (MIDI in)
                   | 15     26 |    
                   | 16     25 | -> I2C SCL (16x2 LCD)
                   | 17     24 | -> I2C SDA (16x2 LCD)
            gnd ## | 18     23 | ## gnd
                   | 19     22 | -> 7-SEG LED clk
                   | 20     21 | -> 7-SEG LED data
                   +-----------+
```
### WAVESHARE_REV2_1
```
                   +-----------+
(Debug) TX UART <- |  1     40 | <> vbus +5v
                   |  2     39 | <> vsys
            gnd ## |  3     38 | ## gnd
                   |  4     37 | <- 3v3-en
                   |  5     36 | -> 3v3
                   |  6     35 | <- adc-vref
                   |  7     34 | -> I2S SCLK
            gnd ## |  8     33 | ## agnd
                   |  9     32 | -> I2S LRCLK
                   | 10     31 | -> I2S MCLK
                   | 11     30 | <- run
                   | 12     29 | -> I2S SD
            gnd ## | 13     28 | ## gnd
                   | 14     27 | <- UART RX (MIDI in)
                   | 15     26 |    
                   | 16     25 | -> I2C SCL (16x2 LCD)
                   | 17     24 | -> I2C SDA (16x2 LCD)
            gnd ## | 18     23 | ## gnd
                   | 19     22 | -> 7-SEG LED clk
                   | 20     21 | -> 7-SEG LED data
                   +-----------+
```
### PIMORONI_PICO_AUDIO
```
                   +-----------+
(Debug) TX UART <- |  1     40 | <> vbus +5v
                   |  2     39 | <> vsys
            gnd ## |  3     38 | ## gnd
                   |  4     37 | <- 3v3-en
                   |  5     36 | -> 3v3
                   |  6     35 | <- adc-vref
                   |  7     34 |    
            gnd ## |  8     33 | ## agnd
                   |  9     32 |    
                   | 10     31 |    
                   | 11     30 | <- run
         I2S SD <- | 12     29 |    
            gnd ## | 13     28 | ## gnd
       I2S SCLK <- | 14     27 | <- UART RX (MIDI in)
      I2S LRCLK <- | 15     26 |    
                   | 16     25 | -> I2C SCL (16x2 LCD)
                   | 17     24 | -> I2C SDA (16x2 LCD)
            gnd ## | 18     23 | ## gnd
                   | 19     22 | -> 7-SEG LED clk
                   | 20     21 | -> 7-SEG LED data
                   +-----------+
```
### PIMORONI_VGA_DEMO
```
                   +-----------+
(Debug) TX UART <- |  1     40 |    
                   |  2     39 | <> vsys
            gnd ## |  3     38 | ## gnd
                   |  4     37 | <- 3v3-en
                   |  5     36 | -> 3v3
                   |  6     35 | <- adc-vref
                   |  7     34 | -> I2S LRCLK
            gnd ## |  8     33 | ## agnd
                   |  9     32 | -> I2S SCLK
                   | 10     31 | -> I2S SD
                   | 11     30 | <- run
                   | 12     29 |    
            gnd ## | 13     28 | ## gnd
                   | 14     27 |    
                   | 15     26 |    
                   | 16     25 |    
                   | 17     24 |    
            gnd ## | 18     23 | ## gnd
                   | 19     22 |    
                   | 20     21 |    
                   +-----------+
```
