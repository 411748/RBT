//Nick Braun
//5/19/2024
//RBT - Red Black Tree Program that uses the RBT functionality and gives users an option to add manually, from file, print, search, or remove.
//main.cpp

//includes
#include <iostream>
#include "tree.h"
#include <cstring>
#include <fstream>

using namespace std;

int main() {
  //creating rbt
  RedBlackTree tree;
  //keep running until user quits
  int running = 1;
  char choice[3];

  while(running) {
    //displaying options
    cout << "Select an option:" << endl;
    cout << "A: Add numbers manually" << endl;
    cout << "AF: Add numbers from file" << endl;
    cout << "P: Print tree" << endl;
    cout << "Q: Quit" << endl;
    cout << "S: Search for a number" << endl;
    cout << "R: Remove a number" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    //user adding manually
     if(strcmp(choice, "A") == 0) {
      int count;
      cout << "Enter how many numbers you want to add: " << endl;
      cin >> count;
      cout << "Enter " << count << " numbers separated by spaces: ";
      for(int i = 0; i < count; i++) {
        int num;
        cin >> num;
        tree.add(num);
      }
      //user adding from file
    } else if (strcmp(choice, "AF") == 0) {
      int numCount;
      cout << "Enter the number of numbers you want to add from file: ";
      cin >> numCount;
      ifstream file("numbers.txt");
      int num;
      for(int i = 0; i < numCount && file >> num; i++) {
        tree.add(num);
      }
      file.close();
      //user printing
    } else if (strcmp(choice, "P") == 0) {
      tree.print();
      //user searching
    } else if(strcmp(choice, "S") == 0) {
      int num;
      cout << "Enter the number to search for: ";
      cin >> num;
      if(tree.search(num)) {
	cout << num << " is in the tree" << endl;
      } else {
	cout << num << " is not in the tree" << endl;
      }
      //user removing
    } else if(strcmp(choice, "R") == 0) {
       int num;
       cout << "Enter the number to remove: ";
       cin >> num;
       tree.remove(num);
       //user quitting
    } else if(strcmp(choice, "Q") == 0) {
      running = 0;
    } else {
      cout << "Invalid choice. Please try again." << endl;
    }
  }
  return 0;
}
