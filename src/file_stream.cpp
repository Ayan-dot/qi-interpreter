#include "file_stream.h"

file_stream_node::file_stream_node() {
    val = '\0';
    next = nullptr;
}

file_stream_node::file_stream_node(char _val) {
    val = _val;
    next = nullptr;
}

file_stream::file_stream() {
    file = nullptr;
}

file_stream::file_stream(std::string file_name) {
    if (file_name.size() <= 3 || file_name.substr(file_name.size() - 3) != ".qi")
        throw_error("invalid file name");

    std::ifstream f(file_name);
    if (!f.good())
        throw_error("file does not exist");

    file = new file_stream_node();
    char curr;
    file_stream_node* dummy = file;

    while (f.good()) {
        curr = (char)f.get();
        dummy->next = new file_stream_node(curr);
        dummy = dummy->next;
    }

    f.close();
}

char file_stream::curr() const {
    return file ? file->val : '\0';
}

char file_stream::next() const {
    return file->next ? file->next->val : '\0';
}

void file_stream::move() {
    if (file->next) {
        file_stream_node* prev = file;
        delete prev;
        file = file->next;
    }
    else
        throw_error("interpreter error; no characters in stream");
}
