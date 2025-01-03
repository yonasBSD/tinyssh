#ifndef crypto_kem_sntrup761_H
#define crypto_kem_sntrup761_H

#include "haslibntruprime.h"
#ifndef HASLIBNTRUPRIME

#define crypto_kem_sntrup761_tinyssh_SECRETKEYBYTES 1763
#define crypto_kem_sntrup761_tinyssh_PUBLICKEYBYTES 1158
#define crypto_kem_sntrup761_tinyssh_CIPHERTEXTBYTES 1039
#define crypto_kem_sntrup761_tinyssh_BYTES 32
extern int crypto_kem_sntrup761_tinyssh_keypair(unsigned char *,
                                                unsigned char *);
extern int crypto_kem_sntrup761_tinyssh_enc(unsigned char *, unsigned char *,
                                            const unsigned char *);
extern int crypto_kem_sntrup761_tinyssh_dec(unsigned char *,
                                            const unsigned char *,
                                            const unsigned char *);

#define crypto_kem_sntrup761_keypair crypto_kem_sntrup761_tinyssh_keypair
#define crypto_kem_sntrup761_enc crypto_kem_sntrup761_tinyssh_enc
#define crypto_kem_sntrup761_dec crypto_kem_sntrup761_tinyssh_dec
#define crypto_kem_sntrup761_SECRETKEYBYTES                                    \
    crypto_kem_sntrup761_tinyssh_SECRETKEYBYTES
#define crypto_kem_sntrup761_PUBLICKEYBYTES                                    \
    crypto_kem_sntrup761_tinyssh_PUBLICKEYBYTES
#define crypto_kem_sntrup761_CIPHERTEXTBYTES                                   \
    crypto_kem_sntrup761_tinyssh_CIPHERTEXTBYTES
#define crypto_kem_sntrup761_BYTES crypto_kem_sntrup761_tinyssh_BYTES
#define crypto_kem_sntrup761_IMPLEMENTATION "tinyssh"
#define crypto_kem_sntrup761_VERSION "-"

#else

#include <ntruprime.h>
#define crypto_kem_sntrup761_libntruprime_SECRETKEYBYTES                       \
    sntrup761_SECRETKEYBYTES
#define crypto_kem_sntrup761_libntruprime_PUBLICKEYBYTES                       \
    sntrup761_PUBLICKEYBYTES
#define crypto_kem_sntrup761_libntruprime_CIPHERTEXTBYTES                      \
    sntrup761_CIPHERTEXTBYTES
#define crypto_kem_sntrup761_libntruprime_BYTES sntrup761_BYTES
extern int crypto_kem_sntrup761_libntruprime_keypair(unsigned char *,
                                                     unsigned char *);
extern int crypto_kem_sntrup761_libntruprime_enc(unsigned char *,
                                                 unsigned char *,
                                                 const unsigned char *);
extern int crypto_kem_sntrup761_libntruprime_dec(unsigned char *,
                                                 const unsigned char *,
                                                 const unsigned char *);

#define crypto_kem_sntrup761_keypair crypto_kem_sntrup761_libntruprime_keypair
#define crypto_kem_sntrup761_enc crypto_kem_sntrup761_libntruprime_enc
#define crypto_kem_sntrup761_dec crypto_kem_sntrup761_libntruprime_dec
#define crypto_kem_sntrup761_SECRETKEYBYTES                                    \
    crypto_kem_sntrup761_libntruprime_SECRETKEYBYTES
#define crypto_kem_sntrup761_PUBLICKEYBYTES                                    \
    crypto_kem_sntrup761_libntruprime_PUBLICKEYBYTES
#define crypto_kem_sntrup761_CIPHERTEXTBYTES                                   \
    crypto_kem_sntrup761_libntruprime_CIPHERTEXTBYTES
#define crypto_kem_sntrup761_BYTES crypto_kem_sntrup761_libntruprime_BYTES
#define crypto_kem_sntrup761_IMPLEMENTATION "libntruprime"
#define crypto_kem_sntrup761_VERSION "-"

#endif

#endif
