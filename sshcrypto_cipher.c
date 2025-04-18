/*
20140207
20241210 - reformated using clang-format
Jan Mojzis
Public domain.
*/

#include "crypto.h"
#include "stringparser.h"
#include "e.h"
#include "log.h"
#include "bug.h"
#include "str.h"
#include "byte.h"
#include "packet.h"
#include "sshcrypto.h"

struct sshcrypto_cipher sshcrypto_ciphers[] = {
    {
        "chacha20-poly1305@openssh.com",
        crypto_stream_chacha20_xor,
        crypto_onetimeauth_poly1305,
        crypto_stream_chacha20_KEYBYTES * 2,
        8,
        crypto_onetimeauth_poly1305_BYTES,
        chachapoly_packet_put,
        chachapoly_packet_get,
        sshcrypto_TYPENEWCRYPTO | sshcrypto_TYPEPQCRYPTO,
        0,
    },
    {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    },
};

const char *sshcrypto_cipher_name = 0;
int (*sshcrypto_stream_xor)(unsigned char *, const unsigned char *,
                            unsigned long long, const unsigned char *,
                            const unsigned char *) = 0;
int (*sshcrypto_auth)(unsigned char *, const unsigned char *,
                      unsigned long long, const unsigned char *) = 0;
long long sshcrypto_stream_keybytes = 0;
long long sshcrypto_cipher_blockbytes = 0;
long long sshcrypto_auth_bytes = 0;
void (*sshcrypto_packet_put)(struct buf *) = 0;
int (*sshcrypto_packet_get)(struct buf *) = 0;

int sshcrypto_cipher_select(const unsigned char *buf, long long len) {

    long long i, pos = 0;
    const unsigned char *x;
    long long xlen;

    if (sshcrypto_cipher_name) return 1;

    if (buf[len] != 0) bug_proto();
    log_d2("kex: client: cipher algorithms: ", (const char *) buf);

    for (;;) {
        pos = stringparser(buf, len, pos, &x, &xlen);
        if (!pos) break;

        for (i = 0; sshcrypto_ciphers[i].name; ++i) {
            if (!sshcrypto_ciphers[i].flagenabled) continue;
            if (str_equaln((const char *) x, xlen, sshcrypto_ciphers[i].name)) {
                sshcrypto_cipher_name = sshcrypto_ciphers[i].name;
                sshcrypto_stream_xor = sshcrypto_ciphers[i].stream_xor;
                sshcrypto_auth = sshcrypto_ciphers[i].auth;
                sshcrypto_stream_keybytes =
                    sshcrypto_ciphers[i].stream_keybytes;
                sshcrypto_cipher_blockbytes =
                    sshcrypto_ciphers[i].cipher_blockbytes;
                sshcrypto_auth_bytes = sshcrypto_ciphers[i].auth_bytes;
                sshcrypto_packet_get = sshcrypto_ciphers[i].packet_get;
                sshcrypto_packet_put = sshcrypto_ciphers[i].packet_put;
                log_d2("kex: cipher selected: ", sshcrypto_ciphers[i].name);
                return 1;
            }
        }
    }
    log_d2("kex: cipher not available ", (const char *) buf);
    errno = EPROTO;
    return 0;
}

int sshcrypto_cipher_macselect(const unsigned char *buf, long long len) {

    if (buf[len] != 0) bug_proto();
    log_d2("kex: client: mac algorithms: ", (const char *) buf);
    log_d1("kex: mac selected: hmac-sha2-256 (ignored for "
           "chacha20-poly1305@openssh.com)");
    return 1;
}

void sshcrypto_cipher_put(struct buf *b) {

    crypto_uint32 len = 0;
    long long i, j, start;

    j = 0;
    for (i = 0; sshcrypto_ciphers[i].name; ++i) {
        if (!sshcrypto_ciphers[i].flagenabled) continue;
        if (j++) ++len;
        len += str_len(sshcrypto_ciphers[i].name);
    }

    buf_putnum32(b, len);
    start = b->len;

    j = 0;
    for (i = 0; sshcrypto_ciphers[i].name; ++i) {
        if (!sshcrypto_ciphers[i].flagenabled) continue;
        if (j++) buf_puts(b, ",");
        buf_puts(b, sshcrypto_ciphers[i].name);
    }
    b->buf[b->len] = 0;
    log_d2("kex: server: cipher algorithms: ", (char *) b->buf + start);
}

/*
XXX some clients doesn't accept empty mac,
we send hmac-sha2-256
(for chacha20-poly1305@openssh.com is hmac-sha2-256 string ignored)
*/
void sshcrypto_cipher_macput(struct buf *b) {

    buf_putstring(b, "hmac-sha2-256");
    log_d1("kex: server: mac algorithms: hmac-sha2-256");
}
