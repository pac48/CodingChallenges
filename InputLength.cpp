#include<iostream>

using namespace std;

int main(int argc, char* argv[]){
    char* string = argv[1];
    if (argc != 2){
        cout << "Usage: requires one comamnd line argment." << endl;
        return 0;
    }

    char character ='a';
    int i = 0;
    while (character != 0){
        cout << string[i] << ": "<< int(string[i]) << endl;
        character = string[i];
        i++;
    }
     cout <<"Length of input is: " << i-1 <<endl;

    return 0;
}
