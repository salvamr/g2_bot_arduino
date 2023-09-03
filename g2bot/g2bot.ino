#include "HID-Project.h"

#include <hidboot.h>
#include <usbhub.h>

class MouseRptParser : public HIDReportParser
{
protected:
  void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

USB Usb;
USBHub Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb);
MouseRptParser Prs;
uint8_t m[4];

bool canProxyMouse = false;

void MouseRptParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {  
  if (canProxyMouse) {
  //Glorious
  //m[0] = buf[0];
  //m[1] = buf[2];
  //m[2] = buf[4];
  //m[3] = buf[1];

  //Logitech
    m[0] = buf[0];
    m[1] = buf[1];
    m[2] = buf[2];
    m[3] = buf[3];

    G2Mouse.SendReport(m, sizeof(m));
  }
}

void setup() {
    Serial.begin( 115200 );

    Usb.Init();

    delay( 200 );

    HidMouse.SetReportParser(0, &Prs);   
    
    G2Mouse.begin();
}

void loop() {
  Usb.Task();
    
  if (Serial.available() > 1) { 
    canProxyMouse = false;
    m[1] = Serial.read();
    m[2] = Serial.read();
    G2Mouse.SendReport(m, sizeof(m));
  } else {
    canProxyMouse = true;
  }
}
