#ifndef POO_FUNCTIONS_H
#define POO_FUNCTIONS_H

#include <vector>
#include <iostream>
#include <memory>

using namespace std;

template<typename T>
istream &operator>>(istream &is, vector<T> &vec);

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &vec);

template<typename T>
ostream &operator<<(ostream &os, const vector<shared_ptr<T> > &vec);
//
//template<typename T>
//ostream &operator>>(ostream &os, vector<shared_ptr<T> > &vec);


#endif //POO_FUNCTIONS_H
