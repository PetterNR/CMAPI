/*
  This file is for Niederreiter encryption
*/

#ifndef ENCRYPT_H
#define ENCRYPT_H
#define encrypt CRYPTO_NAMESPACE(encrypt)

void encrypt(unsigned char *, const unsigned char *, unsigned char *);
void encrypt2(unsigned char *, const unsigned char *, const unsigned char *);
void gen_e(unsigned char *e);

#endif

