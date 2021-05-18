#include "de_base64.h"

const unsigned char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

int decode(const unsigned int *inp, unsigned char *out) {
    unsigned int in = *inp;

    int eqsymb = 0;
    for (int i = 0; i < 4; ++i) {
        unsigned char temp = (unsigned char)((in  & (0xFF << i*8)) >> i*8);
        if (temp >= 97 && temp <= 122) { //Строчной алфавит
            temp -= 71;
            goto next;
        }
        if (temp >= 65 && temp <= 90) { //Прописной алфавит
            temp -= 65;
            goto next;
        }
        if (temp >= 48 && temp <= 57) { //Цифры
            temp += 4;
            goto next;
        }
        if (temp == '+') {
            temp = 62;
            goto next;
        }
        if (temp == '/') {
            temp = 63;
            goto next;
        }
        if (temp == '=') {
            ++eqsymb;
            temp = 0;
        }
        next:
        in &= ~(0xFF << i * 8);
        in |= temp << i * 8;
    }
    //fkn little-endian * 2
    *out = (unsigned char)((0x3F & in) << 2 | (0x3000 & in) >> 12);
    *(out + 1) = (unsigned char)((in & 0xF00) >> 4 | (in & 0x3C0000) >> 18);
    *(out + 2) = (unsigned char)((in & 0x30000) >> 10 | (in & 0x3F000000) >> 24);
    return eqsymb;
}

void encode(const unsigned int *inp, unsigned int *out) {
    *out = alphabet[(*inp & 0xFC) >> 2] | \
                alphabet[((*inp & 0x3) << 4) | ((*inp & 0xF000) >> 12)] << 8 | \
                alphabet[((*inp & 0x0F00) >> 6) | ((*inp & 0xC00000) >> 22)] << 16 | \
                alphabet[(*inp & 0x3F0000) >> 16] << 24;
}

void encode_file(FILE *input, FILE *output) {
    assert(input != NULL && output != NULL);
    const char nextLine = '\n';
    unsigned int *buffer = malloc(sizeof(int) * BUFF_SIZE);
    unsigned int *r_buffer = malloc(sizeof(int) * BUFF_SIZE);
    size_t i = 0;
    int end_flag = 0;
    while (!end_flag) {
        for (i = 0; (i < BUFF_SIZE) && !end_flag; ++i) {
            buffer[i] = 0;
            size_t byte = fread(&buffer[i], sizeof(char), 3, input);
            if (byte == 0) { //Топорно, но работает
                end_flag = 1;
                break;
            }
            if (byte < 3) {
                end_flag = 1;
            }
            encode(buffer + i, r_buffer + i);
        }
        fwrite(r_buffer, sizeof(int), i, output);
        fwrite(&nextLine, sizeof(char), 1, output); //Перевод строки
    }
    unsigned int temp = r_buffer[--i];
    size_t pointer = ftell(output);
    if ((temp & 0xFF000000) == 0x41000000) {
        temp &= 0x00FFFFFF;
        temp |= 0x3D000000; //Корректирующие равно. Закоментировать строку для UTF-7
        fseek(output, pointer - 2*sizeof(char), SEEK_SET);
        fwrite("=", sizeof(char), 1, output);
    }
    if ((temp & 0xFF0000) == 0x410000) {
        fseek(output, pointer - 3*sizeof(char), SEEK_SET);
        fwrite("=", sizeof(char), 1, output);
    }
    free(buffer);
    free(r_buffer);
}

void decode_file(FILE *input, FILE *output) {
    assert(input != NULL && output != NULL);
    unsigned int *buffer = malloc(sizeof(int) * BUFF_SIZE);
    unsigned char *r_buffer = malloc(sizeof(char) * 3 * BUFF_SIZE);
    int end_flag = 0;
    size_t readed = 0;
    int eqsymb = 0;
    while (!end_flag) {
        readed = fread(buffer, sizeof(int), BUFF_SIZE, input);
        if (readed == 0) {
            //end_flag = 1;
            break;
        }
        if (readed < BUFF_SIZE) {
            end_flag = 1;
        }
        for (int j = 0; j < readed; ++j) {
            eqsymb = decode(buffer + j, r_buffer + j * 3);
        }
        fwrite(r_buffer, sizeof(char), readed * 3, output);
        fseek(input, sizeof(char),SEEK_CUR);
    }
    fseek(output, ftell(output) - sizeof(char)*readed*3, SEEK_SET);
    fwrite(r_buffer, sizeof(char),readed*3-eqsymb,output);
    free(buffer);
    free(r_buffer);
}

