#include <string>
#include <cctype>

#include "string_utils.h"

std::string capitalise (const std::string& s)
{
  std::string s2 = s;
  for (auto& c : s2)
    c = std::toupper (c);
  return s2;
}

