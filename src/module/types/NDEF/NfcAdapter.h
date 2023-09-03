#ifndef NfcAdapter_h
#define NfcAdapter_h
#if 0
#include <Ndef.h>
#include <NfcTag.h>

// Drivers
#include <MifareClassic.h>
#include <MifareUltralight.h>

//#define NDEF_DEBUG 1

class NfcAdapter
{
public:
  NfcAdapter(MFRC522 *);

  ~NfcAdapter(void);
  void   begin(bool verbose = true);
  bool   tagPresent();  // tagAvailable
  NfcTag read();
  bool   write(NdefMessage &ndefMessage);
  // erase tag by writing an empty NDEF record
  bool erase();
  // format a tag as NDEF
  bool format();
  // reset tag back to factory state
  bool clean();
  void haltTag();

private:
  MFRC522        *shield;
  NfcTag::TagType guessTagType();
};

#endif

#endif