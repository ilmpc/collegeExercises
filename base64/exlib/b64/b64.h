

#ifndef BASE64_B64_H
#define BASE64_B64_H

void lencodeblock(unsigned char *in, unsigned char *out, int len);

int lencode(FILE *infile, FILE *outfile, int linesize);

void ldecodeblock(unsigned char *in, unsigned char *out);

int ldecode(FILE *infile, FILE *outfile);

#endif //BASE64_B64_H
