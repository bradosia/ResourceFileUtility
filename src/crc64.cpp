/* Redis uses the CRC64 variant with "Jones" coefficients and init value of 0.
 *
 * Specification of this CRC64 variant follows:
 * Name: crc-64-jones
 * Width: 64 bites
 * Poly: 0xad93d23594c935a9
 * Reflected In: True
 * Xor_In: 0xffffffffffffffff
 * Reflected_Out: True
 * Xor_Out: 0x0
 * Check("123456789"): 0xe9c6d914c4b8d9ca
 *
 * Copyright (c) 2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE. */

#include "crc64.h"

uint64_t hashExt::crc64(uint64_t crc, const unsigned char *s, uint64_t l) {
    uint64_t j;

    for (j = 0; j < l; j++) {
    	uint8_t byte = s[j];
        crc = crc64_tab[(uint8_t)crc ^ byte] ^ (crc >> 8);
    }
    return crc;
}

uint64_t hashExt::crc64(uint64_t crc, std::istream& streamIn, uint64_t l) {
    uint64_t j;
    uint8_t byte[1];
    for (j = 0; j < l; j++) {
    	streamIn.seekg(j, std::ios::beg);
    	streamIn.read((char*)byte, 1);
    	crc = crc64_tab[(uint8_t)crc ^ *byte] ^ (crc >> 8);
    }
    return crc;
}