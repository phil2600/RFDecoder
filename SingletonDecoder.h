//#pragma once
#ifndef _SINGLETONDECODER_H_
# define _SINGLETONDECODER_H_

# include "OregonDecoderV2.h"

class SingletonDecoder
{
private:
  SingletonDecoder ()
    : _value (0) { }
  ~SingletonDecoder () { }

public:
  void setValue (OregonDecoderV2* decoder);
  OregonDecoderV2* getValue ();

  // Fonctions de création et destruction du singleton
  static SingletonDecoder *getInstance ();

  static void kill ();


private:
  OregonDecoderV2* _value;
  static SingletonDecoder *_singleton;
};

// Initialisation du singleton à NULL
//SingletonDecoder *SingletonDecoder::_singleton = NULL;

#endif
