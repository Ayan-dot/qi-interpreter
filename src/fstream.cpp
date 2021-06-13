#include "fstream.h"

fstream_node::fstream_node() {
    val = '\0';
    next = nullptr;
}

fstream_node::fstream_node(char _val) {
    val = _val;
    next = nullptr;
}

fstream::fstream() {
    file = nullptr;
}

fstream::fstream(std::string file_name) {
    if (file_name.size() <= 3 || file_name.substr(file_name.size() - 3) != ".qi")
        err("invalid file name");

    std::ifstream f(file_name);
    if (!f.good())
        err("file does not exist");

    file = new fstream_node();
    char curr;
    fstream_node *dummy = file;

    while (f.good()) {
        curr = (char) f.get();
        dummy->next = new fstream_node(curr);
        dummy = dummy->next;
    }

    f.close();
}

char fstream::curr() const {
    return file ? file->val : '\0';
}

char fstream::next() const {
    return file->next ? file->next->val : '\0';
}

void fstream::move() {
    if (file->next) {
        fstream_node *prev = file;
        delete prev;
        file = file->next;
    } else
        err("interpreter error; no characters in stream");
}
