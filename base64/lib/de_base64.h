#ifndef BASE64_DE_BASE64_H
#define BASE64_DE_BASE64_H
#define BUFF_SIZE 18 //As in base64 from GNU

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * Функция декодирования
 * @param inp 4 1-байтовых символа в int
 * @param out 3 1-байтовых символа в массиве из 3-х char
 * @return Количество незначащих(=) сиволов в потоке (в конце).
 */
int decode(const unsigned int *inp, unsigned char *out);
/**
 *
 * @param inp
 * @param out
 */
void encode(const unsigned int *inp, unsigned int *out);
/**
 *
 * @param input
 * @param output
 */
void encode_file(FILE *input, FILE *output);

void decode_file(FILE *input, FILE *output);

#endif //BASE64_DE_BASE64_H
