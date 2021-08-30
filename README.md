# xxteadecrypt
## How to build
```
git clone https://github.com/gitterrost4/xxteadec.git
cd xxteadec
cmake .
make
make install
```

## Usage
```
Usage: xxteadec [OPTION...] INPUT_FILE KEY OUTPUT_FILE
xxteadec -- decrypt xxtea encrypted files

  -s, --skip=NUM             Skip this many bytes in the input file before
                             decrypting. Default 0
  -?, --help                 Give this help list
      --usage                Give a short usage message

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.
```
