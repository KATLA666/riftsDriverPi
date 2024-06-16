// ********************* Includes       ********************* //
#include "rift.h"

// ********************* Defines        ********************* //

// ********************* Types          ********************* //

// ********************* Data           ********************* //

// ********************* Prototypes     ********************* //

// ********************* Implementation ********************* //

int16_t rift_send_keep_alive(hid_device *handle)
{
  // Prepare buffer
  unsigned char buf_au8[6] = {0x93, 0x01, 0xb8, 0x0b, 0x00, 0x00};

  // Send feature report
  int16_t res_s16 = hid_send_feature_report(handle, buf_au8, sizeof(buf_au8));
  if (0 /*res_s16 < 0*/)
  {
    // Error
    wprintf(L"Sending keep alive failed with %d\n", res_s16);
    return res_s16;
  }

  return 0;
}

int16_t rift_send_enable_components(hid_device *handle, uint8_t on_u8)
{
  uint8_t buf_au8[3];

  if (on_u8)
  {
    /* Unknown report 0x07 */
    buf_au8[0] = 0x07;
    buf_au8[1] = 0xa3;
    buf_au8[2] = 0x01;
    // Send feature report
    int16_t res_s16 = hid_send_feature_report(handle, buf_au8, sizeof(buf_au8));
    if (res_s16 < 0)
    {
      // Error
      wprintf(L"Sending unkwonen report failed with %d\n", res_s16);
      return res_s16;
    }
  }

  // Prepare buffer
  buf_au8[0] = 0x14;                // Enable components command
  buf_au8[1] = on_u8 ? 0x01 : 0x00; // Flags: 1 = Display, 2 = Audio, 4 = LEDs

  // Send feature report
  int16_t res_s16 = hid_send_feature_report(handle, buf_au8, 2);
  if (res_s16 < 0)
  {
    // Error
    wprintf(L"Sending enable Device failed with %d\n", res_s16);
    return res_s16;
  }

  if (!on_u8)
  {

    buf_au8[0] = 0x08; // enable lcd
    buf_au8[1] = on_u8 ? 0x01 : 0x00;

    // Send feature report
    res_s16 = hid_send_feature_report(handle, buf_au8, 2);
    if (res_s16 < 0)
    {
      // Error
      wprintf(L"Sending enable LCD failed with %d\n", res_s16);
      return res_s16;
    }
  }

  buf_au8[0] = 0x02;
  buf_au8[1] = on_u8 ? 0x01 : 0x00;

  // Send feature report
  res_s16 = hid_send_feature_report(handle, buf_au8, 2);
  if (res_s16 < 0)
  {
    // Error
    wprintf(L"Sending enable Procimity failed with %d\n", res_s16);
    return res_s16;
  }

  return 0;
}

// EOF
