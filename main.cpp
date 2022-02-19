#include <iostream>
#include <iomanip>
#include <string.h>
#include <cassert>
using namespace std;

void one(long number);
void two(long number);
void pass() { cout << "You pass :)\n"; }
void fail() { cout << "You've failed :(\n"; }
const char * passMessage = ":)";
const char * failMessage = ":(";

/**********************************************
 * MAIN : The top of the callstack.
 **********************************************/
int main()
{
   char text[8] = "*MAIN**";
   long number = 123456;
   void (*pointerFunction)() = fail;
   const char * message = failMessage;

  // Ensure that variables have not changed
  assert(strcmp(text, "*MAIN**") == 0);
  assert(number == 123456);
  assert(message == failMessage);
  assert(*pointerFunction == fail);
  
   // display the initial values of the local variables
   cout << "main() : " << (void *)main << endl;
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   // call the other functions
   one(number + 111111);     // 234567

   // display the new values of the local variables
   cout << "main() - after\n";
   cout << "\ttext:             " << text              << endl;
   cout << "\tnumber:           " << number            << endl;
   cout << "\tmessage:          " << message           << endl;
   cout << "\tfunction pointer: ";
   pointerFunction();

   return 0;
}

/************************************************
 * CONVERT TO STRING
 * Convert the data from p into a human-readable string
 * by removing all the unprintable characters and replacing
 * them with a dot
 ***********************************************/
string displayCharArray(const char * p)
{
   string output;
   for (int i = 0; i < 8; i++)
       output += string(" ") + (p[i] >= ' ' && p[i] <= 'z' ? p[i] : '.');
   return output;
}

/**********************************************
 * ONE : The next item on the call stack
 **********************************************/
void one(long number)               // 234567
{
   char text[8] = "**ONE**";
  assert(string(text) == "**ONE**");

   cout << "one() : " << (void *)one << endl;
   cout << "\tmessage: " << (void *)failMessage << endl;
   cout << "\tfail():  " << (void *)fail        << endl;

   two(number + 111111);    // 345678
}

/**********************************************
 * TWO : The bottom of the call stack
 **********************************************/
void two(long number)              // 345678
{
   // start your display of the stack from this point
   long bow = number + 111111;     // 456789
   char text[8] = "**TWO**";
   long * pLong = NULL;
   char * pChar = NULL;
   assert(string(text) == "**TWO**");
   assert(bow == number + 111111);
   assert(pLong == NULL);
   assert(pChar == NULL);
   // header for our table. Use these setw() offsets in your table
   cout << '[' << setw(2) << 'i' << ']'
        << setw(15) << "address"
        << setw(20) << "hexadecimal"
        << setw(20) << "decimal"
        << setw(18) << "characters"
        << endl;
   cout << "----+"
        << "---------------+"
        << "-------------------+"
        << "-------------------+"
        << "-----------------+\n";
   char * position;
   for (long i = 50; i >= -4; i--)   // You may need to change 24 to another number
   {
      ////////////////////////////////////////////////
      // Insert code here to display the callstack
      position = (char*)((char*) & bow + 8 * i);
     
      cout << '[' << setw(2) << i << ']'
           << setw(15) << (void*)position
           << setw(20) << std::hex << std::showbase << *(long*)position
           << setw(20) << std::dec << *(long*)position
           << setw(18) << displayCharArray(position) << std::endl;
      // 
      ////////////////////////////////////////////////
   }

   ////////////////////////////////////////////////
   // Insert code here to change the variables in main()

    const char * variables = (char *)&bow;
    
    
    // change text in main() to "*main**"
    /////////////////////////////////////////////////////////////////////////////
    
    while (string(variables) != "*MAIN**") 
      variables++;

    assert(string(variables) == "*MAIN**");
    cout << "\nChanging the value of *MAIN** to *main** at address: " 
         << (void*)variables << endl;
  
    // replacement text
    char replacetext[8] = "*main**";
    char * newText = (char*)variables;
  
    // changing value for main
    cout << "New value for *MAIN** is now: ";
    for(int i = 0; i < 7; i++){
      newText[i] = replacetext[i];  
      cout << newText[i];
    }
    cout << endl;
    
    
    // change number in main() to 654321
    /////////////////////////////////////////////////////////////////////////////

    long * varlong = (long *)&bow;
    while(*varlong != 123456)
      varlong++;

    assert(*varlong == 123456);
    cout << "\nChanging the value of 123456 to 654321 at address: " 
         << (void*)varlong << endl;
  
    // replacement number
    *varlong = 654321;
    // changing value for main
    cout << "New value for 123456 is now: " 
         << *varlong << endl; 

  // change pointerFunction in main() to point to pass
  /////////////////////////////////////////////////////////////////////////////

  long * varPF = (long *)&bow;
  while(*varPF != (long)fail)
    varPF++;

  assert(*varPF == (long)fail);
  cout << "\nChanging the value of fail to pass at address: " 
       << (void*)varPF << endl;

  // replacement of fail to pass
  *varPF = (long)pass;
  
  // changing value for main
  cout << "New value for fail is now: " 
       << *varPF << endl; 

  /////////////////////////////////////////////////////////////////////////////
  // change message in main() to point to passMessage

  long * varMessage = (long *)&bow;
  while(*varMessage != (long)failMessage)
    varMessage++;
  assert(*varMessage == (long)failMessage);
  cout << "\nChanging the value of failMessage to passMessage at address: " 
       << (void*)varMessage << endl;

  // replacement of fail to pass
  *varMessage = (long)passMessage;
  
  // changing value for main
  cout << "New value for failMessage is now: " 
       << *varMessage << endl;
  
  //
  ////////////////////////////////////////////////
}
