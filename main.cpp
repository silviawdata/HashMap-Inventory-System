/*
 * Name: Silvia Williams
 * Description: THis program reads a menu from a file 
 * and stores the items in a hash. It allows the user to
 * place orders, updates item quantities, and calculates 
 * the total cost. 
 * Input: Menu file and user input for item selection and quantity
 * Output: Menu display, updated quantities, and final order total. 
 *
 */

 //libraries for input/output, file handling, and formatting
 // vecto used to store keys for iterations throughout the code. 
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "hashMap.h"

using namespace std;

////////////  MAIN FUNCTION  //////////////////////////////
// controls program flow for menu ordering system
int main()
{
  // create hash map to store menu items
  hashMap<string, menuType> KrustyKrabMenu;
  ifstream inFile;
  string filename;

  // prompt strings for user interaction
  string Menu = "Enter Krusty Krab Menu: ";
  string ErrorMSG = "Error is opening file: ";
  string HurryMSG1 = "Hurry up and order something: ";
  string HowMuchMSG = "How much of this stuff do you want? ";
  string HowMuchMSG2 = "How of this stuff do you want? ";
  string HurryMSG2 = "Ahem...can we please move this order along?\n";
  string OrderCompletedMSG = "Will this complete your order...barnaclehead? ";
  string foodOnlyMSG = "We serve food here...\n";
  string totalMSG = "Order Total ";

  // prompts user for file name and provides an error check/ edge case
  // for file opening. Repeats until file is successfully opened. 
  do
  {
    cout << Menu << endl;
    getline(cin, filename);

    inFile.open(filename);

    if (!inFile.is_open())
    {
      cout << ErrorMSG << filename << endl;
    }
    inFile.clear();
  } while (!inFile.is_open());

 // variables for reading and parsing KrustyKrabMenu file
 // stores item name, price, and queantitiy
  string header;
  string line;
  int comaLocation = 0;

  string GrubName;
  double GrubPrice = 0.0;
  int GrubQuantity = 0;

  // stores keys for iterating through has map
  vector<string> keys;

  // skips header line in file
  getline(inFile, header);

  //reads each line from file and parses menu data
  // extracts name, price, and quantity using coma locations
  // inserts item into hash map and stores keys
  while (getline(inFile, line))
  {

    comaLocation = line.find(",");
    GrubName = line.substr(0, comaLocation);
    line = line.substr(comaLocation + 1, line.length());

    comaLocation = line.find(",");
    GrubPrice = stod(line.substr(0, comaLocation));
    line = line.substr(comaLocation + 1, line.length());

    GrubQuantity = stoi(line);

    menuType GrubItem(GrubName, GrubPrice, GrubQuantity);
    KrustyKrabMenu.insert(GrubName, GrubItem);
    keys.push_back(GrubName);
  }

  inFile.close(); // closes file

  // variable for user ordering and tracking total
  // stores item name, quantity, and total cost
  // controls ordering loop and menu printing
  string OrderName;
  int OrderCount = 0;
  double TotalOrder = 0.0;
  char complete;
  bool ordering = true;
  bool printMenu = true;

  // main ordering while loop
  // prints menu items that still have quantity available
  while (ordering)
  {
    //prints menu items with available quantity
    // formats output for name, price, and quantity
    if (printMenu)
    {
      //nested for loop for menu printing
      for (size_t i = 0; i < keys.size(); i++)
      {
        menuType item = KrustyKrabMenu.getValue(keys[i]);

        if (item.getQuantity() > 0)
        {

          cout << left << setw(35) << keys[i]
               << right << setw(8) << fixed << setprecision(2) << item.getPrice()
               << right << setw(10) << item.getQuantity() << endl;
        }
      }
      cout << endl;
    }
    // checks if there are any items still have quantity available
    // breaks out of loop if all items are sold out
    bool hasItems = false;

    for (size_t i = 0; i < keys.size(); i++)
    {
      int newQuantity = KrustyKrabMenu.getValue(keys[i]).getQuantity();

      if (newQuantity > 0)
      {
        hasItems = true;
        break;
      }
    }
    //prompts user for item name and reads input 
    // exits loop if input fails
    if (!hasItems)
    {

      break;
    }

    cout << HurryMSG1 << endl;

    if (!getline(cin, OrderName))
    {

      break;
    }

    //create copy of input for processing
    string tempInput = OrderName;

    // converts user input to lowercase comparison
    for (size_t i = 0; i < tempInput.length(); i++)
    {

      if (tempInput[i] >= 'A' && tempInput[i] <= 'Z')
      {
        // adding 32 to convert letters from upper case to lower case
        tempInput[i] = tempInput[i] + 32;
      }
    }

    // variables to keep track if a match is found 
    // and store the matched menu item
    bool matchFound = false;
    string matchedKey;

        
    // checks is user input matches any menu item
    // converts each key to lowercase for comparison
    // stores matched key if found
    for (size_t i = 0; i < keys.size(); i++)
    {

      string tempKey = keys[i];

      for (size_t j = 0; j < tempKey.length(); j++)
      {

        if (tempKey[j] >= 'A' && tempKey[j] <= 'Z')
        {

          tempKey[j] = tempKey[j] + 32;
        }
      }

      if (tempKey == tempInput)
      {
        matchedKey = keys[i];
        matchFound = true;
        break;
      }
    }
   
    // if not matching item is found, display error message
    // skip rest of loop and prompt user again
    if (!matchFound)
    {
      cout << foodOnlyMSG << endl;
      printMenu = false;
      continue;
    }
    // resets menu printing and use matched key
    printMenu = true;

    //set order name to matched menu item
    OrderName = matchedKey;

    //retrieve selected item from hash map
    menuType currentItem = KrustyKrabMenu.getValue(OrderName);

    // if item is out of stock, display message and skip
    if (currentItem.getQuantity() == 0)
    {

      cout << foodOnlyMSG << endl;
      printMenu = false;
      continue;
    }
  
    //boolean for the first quantity prompt 
    bool firstPromp = true;

    while (true)
    {

    if(firstPromp){

    //first prompt for quantity 
    cout << HowMuchMSG << endl;
    cout << endl;
    firstPromp = false;

    }else{

      //retry quantitiy prompt
      cout << HowMuchMSG2 << endl;
      cout << endl;
    }
      
    cin >> OrderCount;

      if (!cin)
      {
        //stop ordering if input fails
        ordering = false;
        break;
      }

      if (OrderCount <= currentItem.getQuantity())
      {
        //valid quantity entered
        break;
      }

      //quantity too large, ask again
      cout << HurryMSG2 << endl;
    }

    // stop outer loop if input failed
    if (!ordering)
    {

      break;
    }

    cin.ignore(1000, '\n');

    // update total calculation
    TotalOrder = TotalOrder + (currentItem.getPrice() * OrderCount);

    //update item quantity and store changes in hash map
    currentItem.updateQuantity(OrderCount);
    KrustyKrabMenu.update(OrderName, currentItem);

    // prints order completion prompt
    cout << OrderCompletedMSG << endl;
    cin >> complete;
    cin.ignore(1000, '\n');

    // stop ordering if user is finished
    if (complete == 'Y' || complete == 'y')
    {
      // flag false;
      ordering = false;
    }
  }
  //prints final order total
  cout << endl;
  cout << totalMSG << fixed << setprecision(2) << TotalOrder << endl;

  return 0;
}

