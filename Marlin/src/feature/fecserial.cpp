
#include "../Configuration_adv.h"
#include "fecserial.h"
#include <libcorrect/correct/reed-solomon.h>

// A thin wrapper around the correct_reed_solomon struct
class Transcoder {
public:
  Transcoder();
  ~Transcoder();

  inline ssize_t encode(const uint8_t * msg, size_t msg_length, uint8_t *encoded) {
    return correct_reed_solomon_encode(rs_ptr, msg, msg_length, encode);
  }
  inline ssize_t decode(const uint8_t * encoded, size_t encoded_length, uint8_t *msg) {
    return correct_reed_solomon_decode(rs_ptr, encoded, encoded_length, msg);
  }
private:
  correct_reed_solomon * rs_ptr;
};

Transcoder::Transcoder() {
  rs_ptr = correct_read_solomon_create(correct_rs_primitive_polynomial_ccsds, 1, 1, 32);
}

Transcoder::~Transcoder() {
  correct_read_solomon_destroy(rs_ptr);
}

// Only really need a single instance of the transcoder
Transcoder & use_transcoder(int index) {
  static Transcoder transcoder;
  return transcoder;
}

Fec::Fec() : transcoder(use_transcoder()) {}

