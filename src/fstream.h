#ifndef QI_INTERPRETER_FSTREAM_H
#define QI_INTERPRETER_FSTREAM_H


#include <cstdlib>
#include <fstream>
#include <string>

#include "util.h"

class fstream_node {
public:
    char val;
    fstream_node *next;

    fstream_node();

    explicit fstream_node(char _val);
};


class fstream {
private:
    fstream_node *file;

public:
    fstream();

    explicit fstream(std::string file_name);

    char curr() const;

    char next() const;

    void move();
};


#endif //QI_INTERPRETER_FSTREAM_H