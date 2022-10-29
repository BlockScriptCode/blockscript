#include <stdio.h>
#include <stdlib.h>
#include "bs.h"
#include "bs_lex.h"
#include "bs_error.h"

static char* read_file(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        FILE_ERROR(COULD_NOT_OPEN_FILE, path);
        exit(74);
    }
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    char* buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        FILE_ERROR(NOT_ENOUGH_MEMORY_FILE, path);
        exit(74);
    }
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize) {
        FILE_ERROR(COULD_NOT_READ_FILE, path);
        exit(74);
    }
    
    buffer[bytesRead] = '\0';
    fclose(file);
    return buffer;
}


int main(int argc, const char* argv[]) {
        if (argc == 1) {
            // repl();
        } else if (argc == 2) {
            char * source = read_file(argv[1]);
            bs_lex_init(source);
            bs_token token = next_token();
            while(token.type != TK_EOF) {
                printf("Line: %d, Token: %2d, Value: %.*s, Length: %d\n", token.line, token.type, token.length, token.start, token.length);
                token = next_token();
            }
        } else {
            USAGE_ERROR();
            exit(64);
        }
        return 0;
}