#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
struct Element {
Element* next = nullptr;
char data;
Element(char c) : data(c) {}
};
struct Set {
Element* first = nullptr;
Element* last = nullptr;
int cardinality = 0;
};
void add_lSet(Set* s, char c) {
if (s->cardinality == 0) {
Element* el = new Element(c);
s->last = s->first = el;
s->cardinality++;
} else {
for (Element* el = s->first; el; el = el->next) {
if (el->data == c) return;
}
Element* el = new Element(c);
s->last->next = el;
s->last = el;
s->cardinality++;
}
}
Set create_lSet(const char* str) {
Set set;
for (int i = 0; str[i]; ++i) {
add_lSet(&set, str[i]);
}
return set;
}
void print_lSet(Set* s) {
for (Element* el = s->first; el; el = el->next) {
cout << el->data << ' ';
}
cout << '\n';
}
bool contain(Set* s, char symbol) {
for (Element* el = s->first; el; el = el->next) {
if (el->data == symbol) return true;
}
return false;
}
void generate_random_set(char* set, int maxlen) {
Set tempSet;
int k = 0;
while (k < maxlen) {
char c = 'a' + rand() % 26;
if (!contain(&tempSet, c)) {
set[k++] = c;
add_lSet(&tempSet, c);
}
}
set[k] = '\0';
}
void calculate_resulting_set(Set* setA, Set* setB, Set* setC, Set* setD, Set* setE) {
setE->first = nullptr;
setE->cardinality = 0;
// Add letters from A that are not in B and C
for (Element* elA = setA->first; elA != nullptr; elA = elA->next) {
if (!contain(setB, elA->data) && !contain(setC, elA->data)) {
add_lSet(setE, elA->data);
}
}
// Add letters from B that are not in C
for (Element* elB = setB->first; elB != nullptr; elB = elB->next) {
if (!contain(setC, elB->data)) {
add_lSet(setE, elB->data);
}
}
// Add all letters from D
for (Element* elD = setD->first; elD != nullptr; elD = elD->next) {
add_lSet(setE, elD->data);
}
}
int* create_bSet(Set* s) {
int* bSet = new int[26]();
for (Element* el = s->first; el; el = el->next) {
if (el->data >= 'a' && el->data <= 'z') {
bSet[el->data - 'a'] = 1;
}
}
return bSet;
}
int create_wSet(Set* s) {
int wSet = 0;
for (Element* el = s->first; el; el = el->next) {
if (el->data >= 'a' && el->data <= 'z') {
wSet |= (1 << (el->data - 'a'));
}
}
return wSet;
}
int main() {
srand(static_cast<unsigned>(time(0)));
const int Nmax = 10;
char A[Nmax + 1], B[Nmax + 1], C[Nmax + 1], D[Nmax + 1];
while (true) {
int choice;
cin >> choice;
cout << "Do you want to input sets A, B, C, and D manually? (1 - Yes, 0 - No): ";
if (choice) {
cout << "Enter set A: ";
cin >> A;
cout << "Enter set B: ";
cin >> B;
cout << "Enter set C: ";
cin >> C;
cout << "Enter set D: ";
cin >> D;
} else {
generate_random_set(A, 5);
generate_random_set(B, 5);
generate_random_set(C, 3);
generate_random_set(D, 3);
cout << "Generated set A: " << A << '\n';
cout << "Generated set B: " << B << '\n';
cout << "Generated set C: " << C << '\n';
cout << "Generated set D: " << D << '\n';
}
Set setA = create_lSet(A);
Set setB = create_lSet(B);
Set setC = create_lSet(C);
Set setD = create_lSet(D);
Set setE;
calculate_resulting_set(&setA, &setB, &setC, &setD, &setE);
cout << "Resulting set (letters in A but not in B and C, plus all from D): ";
print_lSet(&setE);
// Array representation
auto startArray = chrono::high_resolution_clock::now();
char* arrayE = new char[setE.cardinality + 1];
int index = 0;
for (Element* el = setE.first; el; el = el->next) {
arrayE[index++] = el->data;
}
arrayE[index] = '\0';
cout << "Array representation: {";
for (int i = 0; arrayE[i] != '\0'; i++) {
cout << arrayE[i];
if (arrayE[i + 1] != '\0') {
cout << ", ";
}
}
cout << "} \n";
delete[] arrayE;
auto endArray = chrono::high_resolution_clock::now();
cout << "Elapsed time for array representation: "
<< chrono::duration<double>(endArray - startArray).count() << " seconds\n";
// List representation
auto startList = chrono::high_resolution_clock::now();
cout << "List representation: ";
print_lSet(&setE);
auto endList = chrono::high_resolution_clock::now();
cout << "Elapsed time for list representation: "
<< chrono::duration<double>(endList - startList).count() << " seconds\n";
// Bit array representation
auto startBit = chrono::high_resolution_clock::now();
int* bE = create_bSet(&setE);
cout << "Bit array representation (letters): ";
for (int i = 0; i < 26; ++i) {
if (bE[i] == 1) {
cout << static_cast<char>('a' + i) << " "; // Печать соответствующей буквы
}
}
cout << '\n';
delete[] bE;
auto endBit = chrono::high_resolution_clock::now();
cout << "Elapsed time for bit array representation: "
<< chrono::duration<double>(endBit - startBit).count() << " seconds\n";
// Word representation
auto startWord = chrono::high_resolution_clock::now();
int wE = create_wSet(&setE);
cout << "Word representation (letters): ";
for (int i = 0; i < 26; ++i) {
if (wE & (1 << i)) {
cout << static_cast<char>('a' + i) << " "; // Печать соответствующей буквы
}
}
cout << '\n';
auto endWord = chrono::high_resolution_clock::now();
cout << "Elapsed time for word representation: "
<< chrono::duration<double>(endWord - startWord).count() << " seconds\n";
cout << "Do you want to run another test? (1 - Yes, 0 - No): ";
int continueChoice;
cin >> continueChoice;
if (continueChoice == 0) break;
}
return 0;
}
