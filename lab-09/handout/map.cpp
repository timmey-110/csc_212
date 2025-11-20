#include "map.h"

Map::Map() {
    // TODO: Initialize an empty binary search tree.
}

Map::~Map() {
    // TODO: Deallocate dynamically allocated memory. Use `destroy(Node*)`.
}

Map::Node *Map::insert(Node *root, int key, int value) {
    // TODO: Insert the key-value pair (`key`, `value`) into the binary search tree rooted by `root`. If the binary
    // search tree already contains the key `key`, do nothing.
}

Map::Node *Map::erase(Node *root, int key) {
    // TODO: Erase the key-value pair with key `key` from the binary search tree rooted by `root`. If the binary search
    // tree does not contain the key `key`, do nothing.
}

Map::Node *Map::find(Node *root, int key) {
    // TODO: Find the key-value pair with key `key` in the binary search tree rooted by `root`. If the binary search
    // tree does not contain the key `key`, return `nullptr`.
}

void Map::destroy(Node *root) {
    // TODO: Deallocate the binary search tree rooted by `root`.
}


void Map::insert(int key, int value) {
    // TODO: Insert the key-value pair (`key`, `value`) into the binary search tree. If the binary search tree already
    // contains the key `key`, do nothing. Use `insert(Node*, int, int)`.
}

void Map::erase(int key) {
    // TODO: Erase the key-value pair with key `key` from the binary search tree. If the binary search tree does not
    // contain the key `key`, do nothing. Use `erase(Node*, int)`.
}

int &Map::operator[](int key) {
    // TODO: Return the value in the key-value pair with key `key` in the binary search tree. If the binary search tree
    // does not contain the key `key`, insert the key-value pair (`key`, 0) and return the associated value. Use
    // `find(Node*, int)` and `insert(Node*, int, int)`.
}

size_t Map::size() const {
    // TODO: Return the number of elements in the binary search tree.
}
