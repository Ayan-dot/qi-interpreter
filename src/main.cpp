#include "main.h"

int main(int argc, char *argv[]) {
    if (argc != 2)
        err("invalid arg count");
    token::init();

    fstream stream((std::string(argv[1])));
    lexer tokenizer(stream);
    std::vector <token> tokens = tokenizer.tokenize();

    interpreter runtime(tokens);
    runtime.execute();

    return 0;
}