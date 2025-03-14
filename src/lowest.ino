// // Turns the 'PRG' button into the power button, long press is off 
// #define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"
// #include <heltec_unofficial.h>

// #define PAUSE               10

// #define FREQUENCY           866.3       // for Europe
// // Allowed values are 7.8, 10.4, 15.6, 20.8, 31.25, 41.7, 62.5, 125.0, 250.0 and 500.0 kHz.
// #define BANDWIDTH           500

// // Number from 5 to 12. Higher means slower but higher "processor gain",
// // meaning (in nutshell) longer range and more robust against interference. 
// #define SPREADING_FACTOR    12

// // Transmit power in dBm. 0 dBm = 1 mW, enough for tabletop-testing. This value can be
// // set anywhere between -9 dBm (0.125 mW) to 22 dBm (158 mW). Transmit without an antenna can damage your hardware.
// // Max ERP allowed in EU is 25mW ~14dBm
// #define TRANSMIT_POWER      0

// String rxdata;
// volatile bool rxFlag = false;
// long counter = 0;
// uint64_t last_tx = 0;
// uint64_t tx_time;
// uint64_t minimum_pause;

// void printInfo(){
//   both.printf("Frequency: %.2f MHz\n", FREQUENCY);
//   both.printf("Bandwidth: %.1f kHz\n", BANDWIDTH);
//   both.printf("Spreading Factor: %i\n", SPREADING_FACTOR);
//   both.printf("TX power: %i dBm\n", TRANSMIT_POWER);
// }


// void setup() {
//   heltec_setup();
//   both.println("Radio init");
//   RADIOLIB_OR_HALT(radio.begin());
//   // Set the callback function for received packets
//   // Set radio parameters
  
//   radio.setDio1Action(rx);
//   RADIOLIB_OR_HALT(radio.setFrequency(FREQUENCY));  
//   RADIOLIB_OR_HALT(radio.setBandwidth(BANDWIDTH));
//   RADIOLIB_OR_HALT(radio.setSpreadingFactor(SPREADING_FACTOR));
//   RADIOLIB_OR_HALT(radio.setOutputPower(TRANSMIT_POWER));

//   printInfo();

//   // Start receiving
//   RADIOLIB_OR_HALT(radio.startReceive(RADIOLIB_SX126X_RX_TIMEOUT_INF));
// }

// void loop() {
//   heltec_loop();
  
//   bool tx_legal = millis() > last_tx + minimum_pause;
//   // Transmit a packet every PAUSE seconds or when the button is pressed
//   if ((PAUSE && tx_legal && millis() - last_tx > (PAUSE * 1000)) || button.isSingleClick()) {
//     // In case of button click, tell user to wait
//     if (!tx_legal) {
//       both.printf("Legal limit, wait %i sec.\n", (int)((minimum_pause - (millis() - last_tx)) / 1000) + 1);
//       return;
//     }
//     both.printf("TX [%s] ", String(counter).c_str());
//     radio.clearDio1Action();
//     heltec_led(50); // 50% brightness is plenty for this LED
//     tx_time = millis();
//     RADIOLIB(radio.transmit((String("Hello")+String(counter++)).c_str()));
//     tx_time = millis() - tx_time;
//     heltec_led(0);
//     if (_radiolib_status == RADIOLIB_ERR_NONE) {
//       both.printf("OK (%i ms)\n", (int)tx_time);
//     } else {
//       both.printf("fail (%i)\n", _radiolib_status);
//     }
//     // Maximum 1% duty cycle
//     minimum_pause = tx_time * 100;
//     last_tx = millis();
//     radio.setDio1Action(rx);
//     RADIOLIB_OR_HALT(radio.startReceive(RADIOLIB_SX126X_RX_TIMEOUT_INF));
//   }

//   // If a packet was received, display it and the RSSI and SNR
//   if (rxFlag) {
//     rxFlag = false;
//     radio.readData(rxdata);
//     if (_radiolib_status == RADIOLIB_ERR_NONE) {
//       both.printf("RX [%s]\n", rxdata.c_str());
//       both.printf("  RSSI: %.2f dBm\n", radio.getRSSI());
//       both.printf("  SNR: %.2f dB\n", radio.getSNR());
//     }
//     RADIOLIB_OR_HALT(radio.startReceive(RADIOLIB_SX126X_RX_TIMEOUT_INF));
//   }
// }

// // Can't do Serial or display things here, takes too much time for the interrupt
// void rx() {
//   rxFlag = true;
// }
