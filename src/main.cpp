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

    file_stream _file_stream = file_stream(std::string(argv[1]));
    lexer _lexer(_file_stream);
    std::vector<token> tokens = _lexer.tokenize();
    ast_node ast = ast_node(tokens);
    ast.print();

    return 0;
}
