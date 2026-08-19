# DiceCard

A buisiness-card-sized, battery-powered electronic dice roller :D 
Its build around the **ATtiny1614-SSN**, 10 LEDs, and a single button. 

## Instructions
1. Press to wake
2. short-press to pick a die
3. hold to roll
It goes back to sleep when it's done.


<img width="1014" height="639" alt="boardfront" src="https://github.com/user-attachments/assets/e66938d3-7356-4e5e-a1fc-8640e06ae9ea" />

<img width="1220" height="747" alt="boardback" src="https://github.com/user-attachments/assets/955553ec-70cc-4c78-a53f-e06d7adb40eb" />


## Features

- 7 selectable dice  **d2, d4, d6, d8, d10**, plus two special modes:
  - **"1" -> d20**: two chained d10 rolls, LED-animated, you sum the results
  - **"9" -> d100**: tens-digit roll + units-digit roll (flat 1-100)
  - Deep sleep (power-down) between uses -> wakes only on button press
  - Only a single button

## Bill of materials (BOM)
| Amount | Part                        | Notes                                             | Price          | Links                                                                                                                                                                                                                                                                                                       |   |   |   |   |   |
|--------|-----------------------------|---------------------------------------------------|----------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---|---|---|---|---|
| 1x     | ATtiny1614                  |                                                   | 1,05€          | https://www.reichelt.de/de/de/shop/produkt/8-bit-attiny_avr-risc_mikrocontroller_16_kb_20_mhz_soic-14-335590#closemodal                                                                                                                                                                                     |   |   |   |   |   |
| 1x     | Cap 0805, 1 µF              |                                                   | 0,08€          | https://www.reichelt.de/de/de/shop/produkt/mlcc_0805_1_f_16_v_x7r_-10_h1_25_mm-429214                                                                                                                                                                                                                       |   |   |   |   |   |
| 10x    | LED, SMD 0603 Red           |                                                   | 0,07€          | https://www.reichelt.de/de/de/shop/produkt/led_smd_0603_rot_56_mcd_100_-231657                                                                                                                                                                                                                              |   |   |   |   |   |
| 10x    | Resistor, SMD 0402 2,2 kOhm |                                                   | 0,02€          | https://www.reichelt.de/de/de/shop/produkt/smd-widerstand_0402_2_2_kohm_63_mw_1_-182934                                                                                                                                                                                                                     |   |   |   |   |   |
| 1x     | Cap 1206 100nF              |                                                   | 0,04€          | https://www.reichelt.de/de/de/shop/produkt/mlcc_1206_100_nf_100_v_-10_x7r-409241                                                                                                                                                                                                                            |   |   |   |   |   |
| 1x     | Battery Holder Ø 20 mm      |                                                   | 0,67€          | https://www.reichelt.de/de/de/shop/produkt/knopfzellenclip_fuer_20_mm_smd-74686                                                                                                                                                                                                                             |   |   |   |   |   |
| 1x     | UDPI-Programming Board      | IF NEEDED. ONLY ONE. YOU DONT NEED THEM PER BOARD | 7,50€          | https://www.berrybase.de/adafruit-updi-friend-3v-5v-stromversorgung-ch340e-chip-usb-c-3v-5v-1k-rueckkopplungswiderstand?gad_source=1&gad_campaignid=22696911352&gbraid=0AAAAADSQJK6ArylTule_RzYSf8CoHO8D9&gclid=CjwKCAjwqJXUBhBNEiwA8BgG7k4nVT0fIzVh1WPstvDr96SSSF5Iflz-FT8h6PRQLShXnonjbpDu8xoCaoEQAvD_BwE |   |   |   |   |   |
| 1x     | PCB                         |                                                   | ~4€            |                                                                                                                                                                                                                                                                                                             |   |   |   |   |   |
| Total  | ----------                  | ----------                                        | 6,74€ (+7,50€) |                                                                                                                                                                                                                                                                                                             |   |   |   |   |   |



## Pin Map
| Silkscreen label | ATtiny1614 pin | Function |
|---|---|---|
| D1 | PA2 | LED |
| D2 | PA3 | LED |
| D3 | PA4 | LED |
| D4 | PA5 | LED |
| D5 | PA6 | LED |
| D6 | PA7 | LED |
| D7 | PB3 | LED |
| D8 | PB2 | LED |
| D9 | PB1 | LED |
| D10 | PB0 | LED |
| — | PA1 | Button (to GND, internal pull-up) |
| — | PA0 | UPDI (programming only) |
| — | VCC | CR2032 + |
| — | GND | CR2032 − |

<img width="1053" height="552" alt="Schematic" src="https://github.com/user-attachments/assets/d1a617bf-ae9d-4d2a-aaf3-e017c43914b7" />
