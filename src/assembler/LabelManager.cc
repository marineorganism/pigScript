#include "LabelManager.hh"

#include <stdint.h>
#include <map>
#include <vector>


using namespace std;


void LabelManager::registerPointer(char * token,uint32_t * labelPtr)
{
  labels[token].pointers.push_back(labelPtr);
}


void LabelManager::registerLabel(char * token,uint32_t address)
{
  labels[token].value = address;
}


void LabelManager::fillPointers()
{
  //iterate over all of the labels
  for (map<uint8_t *,Address,danylib_cmpstrptr>::iterator labelIterator = labels.begin();
       labelIterator != labels.end();
       ++labelIterator)
  {
    //get the stuff that is being iterated over
    uint32_t address = labelIterator->second.value;
    vector<uint32_t *> pointers = labelIterator->second.pointers;

    //iterate over all of the pointers to the label
    for (vector<uint32_t *>::iterator pointerIterator = pointers.begin();
         pointerIterator != pointers.end();++pointerIterator)
    {
      **pointerIterator = address;
    }
  }
}