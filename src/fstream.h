/*
 * fstream.h contains:
 *   - Declarations for the file stream reader
 */

#ifndef QI_INTERPRETER_FSTREAM_H
#define QI_INTERPRETER_FSTREAM_H

#include <cstdlib>
#include <fstream>
#include <string>

#include "util.h"

/// the filestream is implemented as a singly-linked list, made up of
/// nodes with its val and the next node
class fstream_node {
public:
    char val;
    fstream_node *next;

    fstream_node();

    explicit fstream_node(char _val);
};

/// fstream is the filestream with methods to interface with the
/// linked list made from `fstream_node`
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
