uint16_t crctable16[256];
uint16_t crc_generator (uint16_t crc, uint8_t data)//crc is the initial value
{
  int i;
  crc = crc ^ ((uint16_t)data << 8);
  for (i = 0; i < 8; i++)
  {
    if (crc & 0x8000)
      crc = (crc << 1) ^ 0x3d65;
    else
      crc <<= 1;
  }
  return crc;
}
void setup() {
  // put your setup code here, to run once:
for (int divident = 0; divident < 256; divident++) {
    uint16_t d = divident;
    uint16_t curByte = (d << 8); /* move divident byte into MSB of 16Bit CRC */
    curByte = crc_generator(0x1337, divident);
    crctable16[divident] = curByte;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
