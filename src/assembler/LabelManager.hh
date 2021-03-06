#ifndef LABEL_MANAGER_H
#define LABEL_MANAGER_H


#include <stdint.h>
#include <utility>
#include <map>
#include <vector>

#include "danylib/danylib.hh"


using namespace std;


/**
 * since these are often used to refer to labels, this makes it a little more clear
 */
typedef uint32_t Label;


/**
 * pairs an address's value with the label pointers that will eventually point to it
 */
typedef struct
{
  Label value;
  vector<uint8_t *> pointers;
}
Address;


/**
 * manages labels by storing their address and pointers to the variables that should point
 * to them.
 * Enables you to register pointers to variables that should contain address values that
 * correspond with various label strings. When you get the values associated with labels
 * they can be added at any time. At the end you can call fillPointers() to put the data
 * in where it belongs
 */
class LabelManager
{
public:
  /**
   * registers a pointer to a block of bytes that will be filled with a given label's
   * address at a later time.
   * token is the token that this pointer is associated with, and labelPtr is the pointer
   * to the bytes that will be given the value
   */
  void registerPointer(char * token,uint8_t * labelPtr);

  /**
   * tell the label manager the address of a certain label.
   * Associates an address with a specific token
   */
  void registerLabel(char * token,Label address);

  /**
   * put the address of all the labels into all their pointers.
   * Iterates over every pointer to a label pointer that has been registered, and
   * puts the value of the label into them
   */
  void fillPointers();

private:
  /**
   * links the label's name tokens to their address objects containing their value and
   * pointers to them.
   */
  map<char *,Address,danylib_cmpstrptr> labels;
};


#endif
