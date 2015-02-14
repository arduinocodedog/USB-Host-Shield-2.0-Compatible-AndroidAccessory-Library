#include <AndroidAccessory.h>

AndroidAccessory::AndroidAccessory(const char *manufacturer,
                                   const char *model,
                                   const char *description,
                                   const char *version,
                                   const char *uri,
                                   const char *serial)
                : ADK(&Usb,
                      manufacturer,
                      model,
                      description,
                      version,
                      uri,
                      serial)
{
}

void AndroidAccessory::powerOn(void)
{
    if (Usb.Init() == -1) {
        Serial.println("AndroidAcessory powerOn: USB Initialization failed...HALTED!");
        while (1);
    }
}

bool AndroidAccessory::isConnected(void)
{
    Usb.Task();
    
    if (!isReady()) {
        Serial.println("AndroidAccessory isConnected: false!");
        return false;
    }
    
    return true;
}

int AndroidAccessory::read(void *buff, int len, unsigned int nakLimit)
{
    uint16_t rcvlen = len;
    uint8_t rcode = RcvData(&rcvlen, (uint8_t*)buff);
    if (rcode & ( rcode != hrNAK )) {
        Serial.print("AndroidAccessory read: ");
        Serial.println(rcode);
    }
    return (int) rcvlen;
}

int AndroidAccessory::write(void *buff, int len)
{
    uint8_t rcode = SndData((uint16_t)len, (uint8_t*)buff);
    if (rcode) {
        Serial.print("AndroidAccessory write: ");
        Serial.println(rcode);
    }
    return len;
}
