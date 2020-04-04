#include <iostream> 
#include <fstream>
#include "HashTable.h"
#include <string>

using namespace std;

void removeChar(char s[], char g);

int main() {
    ofstream output;
    output.open("output1.txt");
    ifstream infile("phonebook.txt");
    if (!infile) {
        cout << "File could not be opened." << endl;
        return 1;
    }

    HashTable temp = HashTable();

    string input;

    while (getline(infile,input))
    {
        if (infile.eof()) break;
  
        temp.insert(input);

    }
    output << temp;
    
}

/*

int main() {
    
	string st = "(425) 285-9940";
    
    int hashValue = 1;
    int temp = 0;
    for (int i = 0; i < st.size(); i++) {
         temp = int(st[i]);
         if (temp != 0) {
             hashValue *= temp;
         }
         else {
             hashValue += 11;
         }
    }
    if (hashValue < 0) {
        hashValue *= -1;
    }
    cout << hashValue % 4177;






    /*
    st.erase(0, 1);
    st.erase(3, 2);
    st.erase(6, 1);

    int temp = stoi(st);
    cout << temp << endl;

    *
}
*/
void removeChar(char s[], char g)
{
    int i, j;
    for (i = 0; s[i] != 0; ++i)
    {
        while (s[i] == g)
        {
            j = i;
            while (s[j] != 0)
            {
                s[j] = s[j + 1];
                ++j;
            }
        }
    }
}