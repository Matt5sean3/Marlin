/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

/**
 * Forward Error Correction (FEC) for Serial
 * 
 * 3D Printers are intrinsically noisy in an electrical sense, while the
 * Marlin firmware has conventionally compensated for this noise through
 * retransmission. However, past a certain point this retransmission
 * can easily become excessive when using noisier connections. This
 * especially becomes the case if the limits of serial transmission speed
 * are pushed.
 *
 * The technology of error correcting codes allows us to compensate for these
 * inadequate connections with the use of additional computation. While this
 * technique would almost certainly be too computationally costly on older
 * microcontrollers and control boards, most current control boards have the
 * computation to spare and even the potential for higher speed connections.
 *
 * In particular, Reed-Solomon codes are chosen for their long history of use
 * and their tunability to allow choosing additional gain for particularly
 * problematic connections.
 */
#pragma once

#include "../core/serial_hook.h"

class Transcoder;

class Fec {
public:
  Fec();

  void enqueue(uint8_t);
  // Encode and write the current block
  void encode();

private:

  uint8_t encoded_incoming_buffer[256];
  uint8_t incoming_buffer[sizeof(encoded_incoming_buffer) - 32];

  uint8_t encoded_outgoing_buffer[256];
  uint8_t outgoing_buffer[sizeof(encoded_outgoing_buffer) - 32];

  Transcoder & transcoder;
};

Transcoder & use_transcoder();

template<typename SerialT>
struct FecSerial : public SerialBase <FecSerial < SerialT >> {
  typedef SerialBase< FecSerial<SerialT> > BaseClassT;

  Fec fec;
  SerialT & out;

  void write(uint8_t c) {
    fec.enqueue(c);
  }

  void msgDone() const {
    out.msgDone();
  }

  void flush() {
    out.flush();
  }

  void begin(const long baudRate) {
    out.begin(baudRate);
  }

  void end() {
    out.end();
  }

  int available(serial_index_t index = 0) const {
    // Check the incoming stream for available data
    int bytes_available = out.available();
    for(int bytes_available = out.available(), i = 0; i < bytes_available; ++i) {
      out.read();
    }
    // Check if the FEC has decoded data available
    // available changes around
    return out.available();
  }

  int read(serial_index_t index = 0) {
  }

  void read() {
  }

  FecSerial(const bool e, SerialT & out) :
      BaseClassT(e),
      out(out) {}
};


