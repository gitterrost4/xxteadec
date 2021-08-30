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
    size_t len;
    //unsigned char *encrypt_data = xxtea_encrypt(text, strlen(text), key, &len);
    char *decrypt_data = xxtea_decrypt(text, fsize, key, &len);
    printf("%d\n",fsize);
    printf("%d\n",strlen(decrypt_data));
    printf(decrypt_data);
    //free(encrypt_data);
    FILE *outf = fopen(outFileName, "wb");
    fwrite(decrypt_data,len,1,outf);
    free(decrypt_data);
    return 0;
}
