#if !defined(_ANDROIDACCESSORY_H_)
#define _ANDROIDACCESSORY_H_

#include <adk.h>

#ifndef USB_NAK_LIMIT
#define USB_NAK_LIMIT 32000
#endif


class AndroidAccessory : ADK
{
    USB Usb;
    
public:
    AndroidAccessory(const char *manufacturer,
                     const char *model,
                     const char *description,
                     const char *version,
                     const char *uri,
                     const char *serial);

    void powerOn(void);

    bool isConnected(void);
    int read(void *buff, int len, unsigned int nakLimit = USB_NAK_LIMIT);
    int write(void *buff, int len);
};

#endif