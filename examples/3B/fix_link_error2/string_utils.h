#pragma once

#include <string>

// flip the string back to front:
std::string invert (const std::string& s)
{
  std::string s2 (s.size(), ' ');
  for (int n = 0; n < s.size(); n++)
    s2[n] = s[s.size()-1-n];

  return s2;
}

// convert every letter to upper case:
std::string capitalise (const std::string& s);

