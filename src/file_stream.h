#ifndef QI_FILE_STREAM_H
#define QI_FILE_STREAM_H

#include <cstdlib>
#include <fstream>
#include <string>

#include "error.h"

struct file_stream_node {
    char val;
    file_stream_node* next;

    file_stream_node();
    explicit file_stream_node(char _val);
};


class file_stream {
private:
    file_stream_node* file;

public:
    file_stream();
    explicit file_stream(std::string file_name);
    char curr() const;
    char next() const;
    void move();
};

#endif //QI_FILE_STREAM_H
