#include <NfcTag.h>
#include <string.h>

#include <algorithm>
#include <string>

NfcTag::NfcTag(byte *uid, uint8_t uidLength, TagType tagType)
{
  _uid = new byte[uidLength];
  memcpy(_uid, uid, sizeof(byte) * uidLength);

  _uidLength   = uidLength;
  _tagType     = tagType;
  _ndefMessage = (NdefMessage *)NULL;
  _isFormatted = false;
}

NfcTag::NfcTag(byte *uid, uint8_t uidLength, TagType tagType, bool isFormatted)
{
  _uid = new byte[uidLength];
  memcpy(_uid, uid, sizeof(byte) * uidLength);

  _uidLength   = uidLength;
  _tagType     = tagType;
  _ndefMessage = (NdefMessage *)NULL;
  _isFormatted = isFormatted;
}

NfcTag::NfcTag(byte *uid, uint8_t uidLength, TagType tagType, NdefMessage &ndefMessage)
{
  _uid = new byte[uidLength];
  memcpy(_uid, uid, sizeof(byte) * uidLength);

  _uidLength   = uidLength;
  _tagType     = tagType;
  _ndefMessage = new NdefMessage(ndefMessage);
  _isFormatted = true;  // If it has a message it's formatted
}

NfcTag::NfcTag(byte          *uid,
               uint8_t        uidLength,
               TagType        tagType,
               const byte    *ndefData,
               const uint16_t ndefDataLength)
{
  _uid = new byte[uidLength];
  memcpy(_uid, uid, sizeof(byte) * uidLength);

  _uidLength   = uidLength;
  _tagType     = tagType;
  _ndefMessage = new NdefMessage(ndefData, ndefDataLength);
  _isFormatted = true;  // If it has a message it's formatted
}

NfcTag::NfcTag(const NfcTag &rhs)
{
  _uid = new byte[rhs._uidLength];
  memcpy(_uid, rhs._uid, sizeof(byte) * rhs._uidLength);

  _uidLength   = rhs._uidLength;
  _tagType     = rhs._tagType;
  _ndefMessage = rhs._ndefMessage ? new NdefMessage(*rhs._ndefMessage) : nullptr;
}

NfcTag::~NfcTag()
{
  delete _uid;
  delete _ndefMessage;
}

NfcTag &NfcTag::operator=(const NfcTag &rhs)
{
  if(this != &rhs) {
    delete _ndefMessage;
    delete _uid;

    _uid = new byte[rhs._uidLength];
    memcpy(_uid, rhs._uid, sizeof(byte) * rhs._uidLength);

    _uidLength   = rhs._uidLength;
    _tagType     = rhs._tagType;
    _ndefMessage = rhs._ndefMessage ? new NdefMessage(*rhs._ndefMessage)
                                    : nullptr;
  }
  return *this;
}

uint8_t NfcTag::getUidLength() { return _uidLength; }

void NfcTag::getUid(byte *uid, uint8_t *uidLength)
{
  memcpy(uid, _uid, _uidLength < *uidLength ? _uidLength : *uidLength);
  *uidLength = _uidLength;
}

std::string NfcTag::getUidString()
{
  std::string uidString = "";
  for(unsigned int i = 0; i < _uidLength; i++) {
    uint8_t val = ((_uid[i] & 0xF0) >> 4);
    uidString += (val >= 10) ? val + 'A' - 10 : val + '0';

    val = ((_uid[i] & 0xF));
    uidString += (val >= 10) ? val + 'A' - 10 : val + '0';
  }
  return uidString;
}

NfcTag::TagType NfcTag::getTagType() { return _tagType; }

bool NfcTag::hasNdefMessage() { return (_ndefMessage != NULL); }

NdefMessage NfcTag::getNdefMessage() { return *_ndefMessage; }

bool NfcTag::isFormatted() { return _isFormatted; }
#ifdef NDEF_USE_SERIAL

void NfcTag::print()
{
  Serial.print(F("NFC Tag - "));
  Serial.println(_tagType);
  Serial.print(F("UID "));
  Serial.println(getUidString());
  if(_ndefMessage == NULL) {
    Serial.println(F("\nNo NDEF Message"));
  } else {
    _ndefMessage->print();
  }
}
#endif
