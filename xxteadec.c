#include <stdio.h>
#include <string.h>
#include <xxtea.h>

int main(int argc, char *argv[]) {
    const char *key = argv[1];
    const char *fileName = argv[3];
    const char *outFileName = argv[4];
    const int seek = atoi(argv[2]);
    FILE *f = fopen(fileName, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f)-seek;
    fseek(f, seek, SEEK_SET);  /* same as rewind(f); */

    char *text = malloc(fsize + 1);
    fread(text, 1, fsize, f);
    fclose(f);

    text[fsize] = 0;
    size_t len=0;
    char *decrypt_data="";
    //unsigned char *encrypt_data = xxtea_encrypt(text, strlen(text), key, &len);
    decrypt_data = xxtea_decrypt(text, fsize, key, &len);
    //free(encrypt_data);
    if(len == 0) {
      fprintf( stderr, "Input file does not seem to be encrypted with xxtea, or the key is wrong.\n");
      return 1;
    }
    FILE *outf = fopen(outFileName, "wb");
    fwrite(decrypt_data,len,1,outf);
    fclose(outf);
    free(decrypt_data);
    return 0;
}
