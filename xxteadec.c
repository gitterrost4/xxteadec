#include <stdio.h>
#include <string.h>
#include <argp.h>
#include <xxtea.h>

struct arguments
{
  char *args[3];
  char *outputFile;
  int skip;
  char *key; 
  char *inputFile;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */

  struct arguments *arguments = state->input;

  switch (key)
    {
    case 's':
      arguments->skip = atoi(arg);
      break;
    case 'k':
      arguments->key = arg;
      break;
    case 'o':
      arguments->outputFile = arg;
      break;
    case 'i':
      arguments->inputFile = arg;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 3)
        /* Too many arguments. */
        argp_usage (state);

      arguments->args[state->arg_num] = arg;

      break;

    case ARGP_KEY_END:
      if (state->arg_num < 3)
        /* Not enough arguments. */
        argp_usage (state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static char doc[] =
  "xxteadec -- decrypt xxtea encrypted files";

static char args_doc[] = "INPUT_FILE KEY OUTPUT_FILE";

static struct argp_option options[] = {
  {"skip",  's', "NUM",      0,  "Skip this many bytes in the input file before decrypting. Default 0" },
  { 0 }
};
static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char *argv[]) {
    
    struct arguments arguments; 
  
    arguments.skip = 0;
    
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    const char *key = arguments.args[1];
    const char *fileName = arguments.args[0];
    const char *outFileName = arguments.args[2];
    const int seek = arguments.skip;
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
