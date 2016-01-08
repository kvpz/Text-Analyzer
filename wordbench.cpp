/*
  wordbench.cpp
  Kevin Perez
  06/13/15

  This implementation file of Wordbench. The Set API is used which provides
  logarithmic time for insertion, deletion, and searching. 
  The procedure ReadText extracts string
  from a file; each string is "cleaned up" i.e. extract a word from the
  string. The criteria for what qualifies as a word can be found in wordify.cpp, the
  "cleaner-upper." 
  WriteReport() writes to a file specified by the user all the words and how
  many times they appeared in the text.
 */

#include <wordbench.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <wordify.cpp>

bool WordBench::ReadText(const fsu::String& infile)
{
  std::ifstream fstr;
  fstr.open(infile.Cstr());
  if(fstr.fail())
  {
    return false;
  }
  else
  {
    fsu::String word;
    infiles_.PushBack(infile);
    unsigned int wordsRead = 0;
    unsigned int vocabSize = 0;
    while(fstr >> word)
    { 
      WordBench::Wordify(word); // clean up string
      EntryType p(word);
      if(word.Size() != 0)      //i.e. if a word was "cleaned" out of string
      {
        ++wordsRead;
        SetType::Iterator iter = wordset_.Includes(p); //LowerBound(p)
        if(iter != wordset_.End()) // if word is already in set
        {
          SetType::Iterator temp = wordset_.Begin();
          for(iter = wordset_.LowerBound(p); iter != wordset_.UpperBound(p); )
          {
            p.second_ = (*iter).second_ + 1;
            ++iter;
          }
          wordset_.Insert(p);
        }
        else
        { //when word is not in the set
          p.first_ = word;
          p.second_ = 1;
          wordset_.Insert(p);
        }
      } //outer if
      
    }//while

    
    // Determine Vocabulary Size
    for(SetType::Iterator iter = wordset_.Begin(); iter != wordset_.End(); ++iter)
    {
      ++vocabSize;
      /*
      SetType::Iterator temp = iter;
      ++iter;
      if((*temp).first_ != (*iter).first_)
      {
        ++vocabSize;
      }
      */
    }
    
    std::cout << std::endl;
    std::cout << std::setw(30) << std::left;
    std::cout << "     Number of words read: ";
    std::cout << wordsRead << std::endl;
    std::cout << std::setw(30) << std::left;
    std::cout << "     Current vocabulary size: ";
    std::cout << vocabSize << std::endl;
    return true;
  }//outer-if
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
      ostr << std::left;
      ostr << "word";
      ostr.width(c2);
      ostr << std::left;
      ostr << "frequency";
      ostr << std::endl;
      ostr.width(c1);
      ostr << std::left;
      ostr << "----";
      ostr.width(c2);
      ostr << std::left;
      ostr << "---------";
      ostr << std::endl;
      SetType::ConstIterator itr = wordset_.Begin();

      while(itr != wordset_.End())
      {  
        ostr.width(c1);
        ostr << std::left;
        ostr << (*itr).first_;
        ostr.width(9);
        ostr << std::right;
        ostr << (*itr).second_;
        ostr << std::endl;
        ++itr;
      }

      //Calculating number of words
      /*
      std::ifstream fstr;
      fstr.open(outfile.Cstr());
      fsu::String word;
      unsigned long wordsRead = 0;
      while(fstr >> word)
      {
        WordBench::Wordify(word);
        if(word.Size() != 0)
        {
          ++wordsRead;
        }
      }
      */

      std::ifstream fstr;
      fstr.open(outfile.Cstr());
      itr = wordset_.Begin();
      unsigned long wordsRead = 0;
      while(itr != wordset_.End())
      {
        wordsRead += (*itr).second_;
        ++itr;
      }
      
      ostr << "Number of words: " << wordsRead;
      ostr << std::endl;
      ostr << "Vocabulary Size: " << wordset_.Size();
      std::cout << std::setw(30) << std::right;
      std::cout << "Number of words:";
      std::cout << std::setw(12) << std::right;
      std::cout << wordsRead << std::endl;
      std::cout << std::setw(30) << std::right;
      std::cout << "Vocabulary Size:";
      std::cout << std::setw(12) << std::right;
      std::cout << wordset_.Size() << std::endl;
      std::cout << std::setw(30) << std::right;
      std::cout << "Analysis written to file ";
      std::cout << std::setw(12) << std::right << outfile << std::endl;
      
    }
    ostr.close();
    return true;
  }
}

void WordBench::ShowSummary() const
{
  std::cout << std::setw(35) << std::left;
  std::cout << "\tCurrent files:";
  for(fsu::ConstListIterator<fsu::String> itr = infiles_.Begin(); itr != infiles_.End(); )
  {
    std::cout << *itr;
    if(++itr != infiles_.End())
    {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;
  EntryType firstWord = wordset_.Front();

  //Calculating number of words
  unsigned long wordsRead = 0;
  SetType::Iterator iter = wordset_.Begin();
  for( ; iter != wordset_.End(); ++iter)
  {
    wordsRead += (*iter).second_;
  }

    /*
  SetType::Iterator temp = iter;
  while(iter != wordset_.End())
  {
    ++iter;
    if((*temp).second_ < (*iter).second_)
    {
      wordsRead += (*temp).second_;
    }
    ++temp;
  }
    */
  std::cout << std::setw(35) << std::left;
  std::cout << "\tCurrent word count: ";
  std::cout << std::left;
  std::cout << wordsRead << std::endl;
  std::cout << std::setw(35) << std::left;
  std::cout << "\tCurrent vocabulary count:";
  std::cout << std::left;
  std::cout<< wordset_.Size() << std::endl;  
  
}

void WordBench::ClearData()
{
  wordset_.Clear();
  infiles_.Clear();
  std::cout << "\tCurrent data erased" << std::endl;
}

