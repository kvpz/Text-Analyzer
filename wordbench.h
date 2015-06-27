/*
  wordbench.h
  6/13/15
  Kevin Perez
  
  This class uses associative data structures defined in ovector.h
  and olist.h. MOVector<T,P> (ordered)and UOVector<T,P> (unordered) behave 
  like a class with one template parameter because P is default to 
  LessThan<T>, but it can be intialized with another predicate class otherwise. 
  
  Wordify is a helper method (included as a slave file) written in wordify.cpp
  that is used to cleanup the string passed to it by reference. 

*/

#ifndef WORDBENCH_H
#define WORDBENCH_H
#include <xstring.h>
#include <list.h>
#include <pair.h>
#include <olist.h>
#include <ovector.h>

class WordBench
{
public:
  bool ReadText     (const fsu::String& infile);
  bool WriteReport  (const fsu::String& outfile, unsigned short c1 = 15, unsigned short c2 = 15) const; 
  void ShowSummary  () const;
  void ClearData    ();

private:
  // the internal class terminology:
  typedef fsu::Pair      < fsu::String, unsigned long >  EntryType;
  typedef fsu::LessThan  < EntryType >                   PredicateType;

  // choose one associative container class for SetType:
  // typedef fsu::UOList          < EntryType , PredicateType >      SetType;
  // typedef fsu::MOList          < EntryType , PredicateType >      SetType;
  typedef fsu::UOVector        < EntryType , PredicateType >      SetType;
  // typedef fsu::MOVector        < EntryType , PredicateType >      SetType;
  // typedef fsu::RBLLT           < EntryType , PredicateType >      SetType;

  // declare the two class variables:
  SetType                    wordset_;
  fsu::List < fsu::String >  infiles_;
  static void Wordify  (fsu::String&);
                                                                               
};
#include <wordify.cpp> //slave file 
#endif
