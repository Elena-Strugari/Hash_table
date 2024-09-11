#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <stdexcept> // std::runtime_error

template <typename keyT, typename valT, typename Hash = std::hash<keyT>>
class table {
public:
    size_t numElem;
    size_t capacity;
    Hash hashCode;
    const double factorIncarcare = 1.0;

    void redimensionare();

    typedef std::pair<keyT, valT> pereche;
    typedef std::list<pereche> Bloc;
    std::vector<typename Bloc::iterator> tabel;
    Bloc list;

    table(size_t initialCapacity = 10)
        : capacity(initialCapacity), numElem(0), tabel(initialCapacity, list.end()) {}

    ~table() {
        list.clear();
        tabel.clear();
    }

    class iterator;

    void insertie(const keyT& cheie, const valT& val);
    bool cautareKey(const keyT& cheie) const;
    bool cautare(const keyT& cheie, const valT& val) const;
    void stergere(const keyT& cheie);
    valT& operator[](const keyT& cheie);
    void print();

    iterator begin();
    iterator end();
};

template<typename keyT, typename valT, typename Hash>
class table<keyT, valT, Hash>::iterator {
    typename Bloc::iterator listIT;

public:
    iterator(const typename Bloc::iterator& Bit) : listIT(Bit) {}

    pereche& operator*() const {
        return *listIT;
    }

    iterator& operator++() {
        ++listIT;
        return *this;
    }

    bool operator==(const iterator& other) const {
        return listIT == other.listIT;
    }

    bool operator!=(const iterator& other) const {
        return !(*this == other);
    }
};

template<typename keyT, typename valT, typename Hash>
inline typename table<keyT, valT, Hash>::iterator table<keyT, valT, Hash>::begin() {
    return iterator(list.begin());
}

template<typename keyT, typename valT, typename Hash>
inline typename table<keyT, valT, Hash>::iterator table<keyT, valT, Hash>::end() {
    return iterator(list.end());
}

template<typename keyT, typename valT, typename Hash>
inline void table<keyT, valT, Hash>::redimensionare() {
    std::vector<pereche> old_elem(list.begin(), list.end());
    list.clear();
    tabel.clear();
    capacity *= 2;
    tabel.resize(capacity, list.end());
    numElem = 0;
    for (const auto& pair : old_elem) {
        insertie(pair.first, pair.second);
    }
    std::cout << "redimensionare" << std::endl;
}

template<typename keyT, typename valT, typename Hash>
inline void table<keyT, valT, Hash>::insertie(const keyT& cheie, const valT& val) {
    if ((double)numElem / capacity > factorIncarcare) {
        redimensionare();
    }
    size_t index = hashCode(cheie) % capacity;

    auto it = tabel[index];
    while (it != list.end()) {
        if (hashCode(it->first) % capacity == index) {
            if (it->first == cheie) {
                it->second = val;
                std::cout << "elem deja existent, s-a modificat valoarea" << std::endl;
                return;
            }
        }
        ++it;
    }
    auto inserted_it = list.insert(it, { cheie, val });
    if (tabel[index] == list.end()) {
        tabel[index] = inserted_it;
    }
    ++numElem;
}

template<typename keyT, typename valT, typename Hash>
inline bool table<keyT, valT, Hash>::cautareKey(const keyT& cheie) const {
    size_t index = hashCode(cheie) % capacity;
    auto it = tabel[index];
    while (it != list.end() && (hashCode(it->first) % capacity) == index) {
        if (it->first == cheie) {
            return true;
        }
        ++it;
    }
    return false;
}

template<typename keyT, typename valT, typename Hash>
inline bool table<keyT, valT, Hash>::cautare(const keyT& cheie, const valT& val) const {
    size_t index = hashCode(cheie) % capacity;
    auto it = tabel[index];
    while (it != list.end() && (hashCode(it->first) % capacity) == index) {
        if (it->first == cheie && it->second == val) {
            return true;
        }
        ++it;
    }
    return false;
}

template<typename keyT, typename valT, typename Hash>
inline void table<keyT, valT, Hash>::stergere(const keyT& cheie) {
    size_t index = hashCode(cheie) % capacity;
    auto it = tabel[index];
    while (it != list.end() && (hashCode(it->first) % capacity) == index) {
        if (it->first == cheie) {
            auto next_it = std::next(it);
            list.erase(it);
            --numElem;
            if (tabel[index] == it) {
                if (next_it == list.end() || hashCode(next_it->first) % capacity != index) {
                    tabel[index] = list.end();
                }
                else {
                    tabel[index] = next_it;
                }
            }
            return;
        }
        ++it;
    }
    std::cout << "Nu s-a gasit perechea ceruta" << std::endl;
}

template<typename keyT, typename valT, typename Hash>
inline valT& table<keyT, valT, Hash>::operator[](const keyT& cheie) {
    size_t index = hashCode(cheie) % capacity;
    auto it = tabel[index];
    while (it != list.end() && (hashCode(it->first) % capacity) == index) {
        if (it->first == cheie) {
            return it->second;
        }
        ++it;
    }
    insertie(cheie, valT());
    return tabel[index]->second;
}

template<typename keyT, typename valT, typename Hash>
inline void table<keyT, valT, Hash>::print() {
    if (numElem != 0) {
        std::cout << std::endl;
        std::cout << "Tabelul arata: " << std::endl;
        for (const auto& pair : list) {
            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }
    }
    else {
        std::cout << "nu se poate afisa nu are elemente" << std::endl;
    }
}
