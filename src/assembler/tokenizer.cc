#include "tokenizer.hh"

#include <stdio.h>
#include <vector>
#include <cwctype>


#define TOKEN_BUFFER_LENGTH 1024
#define FILE_BUFFER_LENGTH 4096

#define COMMENT_CHAR ';'
#define QUOTE '\"'



using namespace std;


char * fit(char * data)
{
  printf("fit %s\n",data);

  int length = 0;
  while (data[length] != '\0')
    length++;

  char * fittedData = new char[length];
  for (int i = 0;i < length;i++)
  {
    fittedData[i] = data[i];
  }

  return fittedData;
}


vector<char *> * tokenize(char const * data)
{
  vector<char *> * tokens = new vector<char *>();
  char buffer[TOKEN_BUFFER_LENGTH];
  int bufferIndex = 0;
  bool inString = false;
  bool inComment = false;

  for (int i = 0;data[i];i++)
  {
    //if it's currently inside a string literal
    if (inString)
    {
      //if it's the end of the string
      if (data[i] == QUOTE)
      {
        //put the string into the list of tokens
        buffer[bufferIndex] = '\"';
        buffer[bufferIndex + 1] = '\0';
        tokens->push_back(fit(buffer));

        //get ready for the next token
        inString = false;
        bufferIndex = 0;
      }

      //if it's not at the end of the string
      else
      {
        buffer[bufferIndex] = data[i];
        bufferIndex++;
      }
    }

    //if it's currently inside a comment
    else if (inComment)
    {
      //when it hits a newline, go back to making tokens
      if (data[i] == '\n')
      {
        inComment = false;
        bufferIndex = 0;
      }
    }

    //if it's just doing it's normal thing
    else
    {
      //if a string literal is starting
      if (data[i] == QUOTE)
      {
        buffer[0] = '\"';
        bufferIndex = 1;
        inString = true;
      }

      //if a comment is starting
      else if (data[i] == COMMENT_CHAR)
      {
        inComment = true;

        //if some characters have been saved
        if (bufferIndex != 0)
        {
          //put the string into the list of tokens
          buffer[bufferIndex] = '\0';
          tokens->push_back(fit(buffer));

          //get ready for the next token
          bufferIndex = 0;
        }
      }

      //if it's whitespace
      else if (iswspace(data[i]))
      {
        //if some characters have been saved
        if (bufferIndex != 0)
        {
          //put the string into the list of tokens
          buffer[bufferIndex] = '\0';
          tokens->push_back(fit(buffer));

          //get ready for the next token
          bufferIndex = 0;
        }
      }

      //if it's anything else
      else
      {
        buffer[bufferIndex] = data[i];
        bufferIndex++;
      }
    }
  }

  //at the end of the thing see if there was one more token
  if (bufferIndex > 0)
  {
    //put the string into the list of tokens
    buffer[bufferIndex] = '\0';
    tokens->push_back(fit(buffer));
  }

  //now return those tasty little beans
  return tokens;
}

vector<char *> * tokenize(FILE * dataFile)
{
  char buffer[FILE_BUFFER_LENGTH];
  char c;

  int i = 0;
  while ((c = fgetc(dataFile)) != EOF)
  {
    buffer[i] = c;

    i++;
  }
  buffer[i] = '\0';

  return tokenize(fit(buffer));
}