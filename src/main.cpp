#include "main.h"

inline void info(std::string s) {
    std::cout << "[info] " << s << std::endl;
}

// Entry point for the executable based on the command line. To run
// a qi file, place the executable in your folder and run:
//     $ ./qi filename.qi
int main(int argc, char *argv[]) {
    // Validate arguments
    if (argc != 2)
        throw_error("invalid arguments");
    token::init();

    info("reading file");
    file_stream _file_stream = file_stream(std::string(argv[1]));

    info("tokenizing with lexer");
    lexer _lexer(_file_stream);
    std::vector<token> tokens = _lexer.tokenize();

    info("creating AST");
    ast_node ast = ast_node(tokens);

    return 0;
}
