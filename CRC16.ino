uint16_t generator = 0x3d65;
uint16_t crctable16[256];
uint16_t crc_xmodem_update (uint16_t crc, uint8_t data)
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
uint16_t Compute_CRC16(byte bytes[], int size)
{
  uint16_t crc = 0;
  for (int i = 0; i < size; i++)
  {
    byte b = bytes[i];
    /* XOR-in next input byte into MSB of crc, that's our new intermediate divident */
    byte pos = (byte)( (crc >> 8) ^ b); /* equal: ((crc ^ (b << 8)) >> 8) */
    /* Shift out the MSB used for division per lookuptable and XOR with the remainder */
    crc = (uint16_t)((crc << 8) ^ (uint16_t)(crctable16[pos]));
  }
  return crc;
}
void setup() {
  for (int divident = 0; divident < 256; divident++) {
    uint16_t d = divident;
    uint16_t curByte = (d << 8); /* move divident byte into MSB of 16Bit CRC */
    curByte = crc_xmodem_update(0x1337, divident);
    crctable16[divident] = curByte;
  }
  // put your setup code here, to run once:
  Serial.begin(9600);
}
void loop() {
  Serial.print("crc16 for 0x01: ");
  Serial.println(crctable16[0x01], HEX);
  Serial.print("crc16 for 0x02: ");
  Serial.println(crctable16[0x02], HEX);
  Serial.print("crc16 for 0x10: ");
  Serial.println(crctable16[0x10], HEX);
  Serial.print("crc16 for 0xff: ");
  Serial.println(crctable16[0xff], HEX);
  Serial.print("crc16 for 0x03: ");
  Serial.println(crctable16[0x03], HEX);
  // put your main code here, to run repeatedly:
  //  Serial.print("crc16 for 0x1338: ");
  //  byte msg[] = {0x13, 0x37};
  //  Serial.println(Compute_CRC16(msg), HEX);
  Serial.print("crc16 for 0x02 array: ");
  byte  msg1[] = {0x02};
  Serial.println(Compute_CRC16(msg1, sizeof(msg1)), HEX);
  //  Serial.print("crc16 for 0x01: ");
  //  byte msg2[] = {1};
  //  Serial.println(Compute_CRC16(msg2), HEX);
  //  Serial.print("crc16 for 0x10: ");
  //  byte msg3[] = {0x10};
  //  Serial.println(Compute_CRC16(msg3), HEX);
  //  byte msg4[] = {0x00, 0x01};
  //  Serial.print("crc16 for 0x0001: ");
  //
  //  Serial.println(Compute_CRC16(msg4), HEX);
}
