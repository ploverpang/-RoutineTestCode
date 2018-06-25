#ifndef BOYER_MOORE_STRING_SEARCH_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class BoyerMooreStringSearch
{
  public:
    BoyerMooreStringSearch();

    virtual ~BoyerMooreStringSearch();

    vector<int> search(const string &text,const string &patten);

  private:
    string m_patten;

    vector<int> m_bad_char_offset_lut;
    vector<int> m_good_suffix_offset_lut;

    void make_bad_char_offset_lut(const string &patten);
    void make_good_suffix_offset_lut(const string &patten);

};


#endif