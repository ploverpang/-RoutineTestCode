#include "boyer_moore_string_search.h"
#include <algorithm>

BoyerMooreStringSearch::BoyerMooreStringSearch()
{

}

BoyerMooreStringSearch::~BoyerMooreStringSearch()
{

}

vector<int> BoyerMooreStringSearch::search(const string &text, const string &patten)
{
  vector<int> matching_loc;
  make_bad_char_offset_lut(patten);

  make_good_suffix_offset_lut(patten);
  
  int idx = 0; 
  int len = patten.length();

  while(idx < (int)(text.length()-len))
  {
    int good_suffix_len = -1; 
    char bad_char = 0;
    int bad_char_loc = 0;

    bool success_matched = true;
    for(int i=len-1; i>=0; i--)
    {
      if(text[idx+i] != patten[i])
      {
        good_suffix_len = len-1-i-1; 
        bad_char = text[idx+i];
        bad_char_loc = i;

        success_matched = false;
        break;
      }
    }
    if(success_matched == true)
    {
      matching_loc.push_back(idx);
      idx += len;
    }
    else 
    {
      int bad_char_offset = bad_char_loc - m_bad_char_offset_lut[bad_char];
      int good_suffix_offset = m_good_suffix_offset_lut[good_suffix_len];
      int max_offset = std::max(bad_char_offset, good_suffix_offset);

      cout << text.substr(idx) << endl;
      cout << patten << endl;
      cout << "max_offset" << max_offset;

      idx += max_offset;
    }
  }

  return matching_loc;
}

void BoyerMooreStringSearch::make_bad_char_offset_lut(const string &patten)
{
  m_bad_char_offset_lut.resize(256);

  for (char c = 0; c < 255; c++)
  {
    size_t it = patten.find(c);
    if(it != string::npos)
    {
      m_bad_char_offset_lut[c] = it;
    }else {
      m_bad_char_offset_lut[c] = -1;
    }
    cout << "char: " << c << " offset: " << m_bad_char_offset_lut[c] << endl;
  }
  
}

void BoyerMooreStringSearch::make_good_suffix_offset_lut(const string &patten)
{
  const int len = patten.length();

  m_good_suffix_offset_lut.resize(patten.size());
  m_good_suffix_offset_lut[0] = (patten[0]== patten[len-1]) ? len-1 : len;
  
  for(int i=1; i<(int)patten.length()-1; i++)
  {
    bool is_good_suffix = true;
    for(int j=0; j<=i; j++)
    {
      if(patten[j] != patten[len-1-i+j])
      {
        is_good_suffix = false;
        break;
      }
    }
    if(is_good_suffix)
    {
      m_good_suffix_offset_lut[i] = len-i-1;
    }
    else {
      m_good_suffix_offset_lut[i] = m_good_suffix_offset_lut[i - 1];
    }

    cout << "good i " << i << " offset: " << m_good_suffix_offset_lut[i] << endl;

  }
}

int main()
{
  BoyerMooreStringSearch sln;
  string text("HERE IS A SIMPLE EXAMPLE");
  string patten("EXAMPLE");
  vector<int> ans = sln.search(text, patten);
  
  for_each(ans.begin(), ans.end(), [](int &n){
    cout << n << endl;
  });
  
  return 0;
}