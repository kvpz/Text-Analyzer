/*
  wordbench.cpp
  Kevin Perez
  06/13/15

*/

#include <wordbench.h>
#include <iostream>
#include <fstream>

bool WordBench::ReadText(const fsu::String& infile)
{
  std::ifstream fstr;
  fstr.open(infile.Cstr());
  fsu::String stemp;  
  if(fstr.fail())
  {
    return false;
  }
  else
  {
    infiles_.PushBack(infile);
    int temp = 0;
    while(!fstr.eof())
    {
      std::getline(fstr, stemp);
      ++temp;
    }
    
    std::cout << "Testing" << std::endl;
    std::cout << "Number of words read:\t";
    std::cout << temp << std::endl;
    std::cout << std::endl;
    std::cout << "Current vocabulary size:\t";

    std::cout << std::endl;
    return true;
  }
}

bool WordBench::WriteReport(const fsu::String& outfile, unsigned short c1, unsigned short c2) const
{
  std::ofstream ostr;
  ostr.open(outfile.Cstr());
  if(ostr.fail())
  {
    return false;
  }
  else
  {

    if(wordset_.Empty())
    {
      std::cout << "  No files in read list. leaving " << outfile << " unopened" << std::endl;
    }
    else
    {
      
      ostr.width(c1);
      //      ostr >> "word";
      ostr.width(c2);
      //      ostr >> "frequency" >> std::endl;
      ostr.width(c1);
      //      ostr >> "----";
      //      ostr.width(c2);
      //      ostr >> "---------" >> std::endl;
      std::cout << "Number of words:\t\t";
      
    }
    ostr.close();
    return true;
  }
  
}

void WordBench::ShowSummary() const
{
  std::cout << "Current files:\t\t\t";
  for(fsu::ConstListIterator<fsu::String> itr = infiles_.Begin(); itr != infiles_.End(); ++itr)
  {
    std::cout << *itr;
    //if(itr+1 != infiles_.End())
      std::cout << ", ";
  }
  
  
}

void WordBench::ClearData()
{
  wordset_.Clear();
  infiles_.Clear();
  std::cout << "\tCurrent data erased" << std::endl;
}

