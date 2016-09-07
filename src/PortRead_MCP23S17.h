#ifndef PORTREAD_MCP23S17_H
#define PORTREAD_MCP23S17_H
#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>
#include <PortReadInterface.h>
#include "PortIOE.h"
#include "Scanner_IOE.h"

/* One MCP23S17 I/O expander port connected to matrix columns.

Instantiation todo
 ------------
readPins parameter is port's bitwise pin configuration
    1=configure as input (for pins connected to column)
    0=configure as output (for LED or not connected to a column)

Example instantiation for column port 0, with pins 2 and 3 connected to columns:
    PortIOE port0(0, 0);
    PortRead_MCP23S17 colPort0(port0, 2<<0 | 1<<3 );
Example instantiation for column port 1, with pins 2 and 3 connected to columns:
    PortIOE port1(1, 0);
    PortRead_MCP23S17 colPort1(port1, 2<<0 | 1<<3 );

readPins are read from pin 0 on up.

*/
class PortRead_MCP23S17 : public PortReadInterface
{
    private:
        PortIOE& port;
        const uint8_t readPins;                 //bitwise, 1 means internal pull-up resistor enabled
    public:
        PortRead_MCP23S17(PortIOE& port, const uint8_t readPins) : port(port), readPins(readPins) {}
        void begin(const uint8_t strobeOn);
        virtual uint8_t read();
};
#endif