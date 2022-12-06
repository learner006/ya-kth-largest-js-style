/********************************************
00-99-ya-kth-largest-js-style-source-code.cpp
********************************************/

#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <vector>
#include <cstdio>
//---------------------------------------------------------------------------
using std::string;
using std::map;
using std::vector;

typedef map<char,int> TCharCountMap;
const char* E_CANNOT_INSERT_KEY_INTO_MAP = "Can not insert key (%c) into map!";
const char* E_COUNT_FOR_KEY_IS_ZERO = "Count for key (%c) is zero!";


void debug_MapPrint(const TCharCountMap& p_charCountMap);
//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
   const char* TEST_SUITE1_DATA[][3] = {
      {"812675429038","917608128",
       "988776429238"},
      {"812675429038","17608128",
       "888776429238"},
      {"124","1",
       "124"},
      {"124","9",
       "924"},
      {"6295323672435","5386210",
       "8695533672435"},
      {"6295323602430","5386210",
       "8695533622431"}
   };

   const int inputIndex = 0;
   
   string A = TEST_SUITE1_DATA[inputIndex][0];
   const string B = TEST_SUITE1_DATA[inputIndex][1];

   const string A_backup = A;

   std::cout << "B: " << B << "\n"
      << "old A: " << A << std::endl;

   TCharCountMap B_charCountMap;

   // Do not count zeros
   const char charToExclude = '0';
   // 'Sort' charactes for B string
   for(unsigned n = 0; n < B.length(); ++n)
   {
      const char chDigit = B[n];
      if (chDigit == charToExclude)
         continue;

      TCharCountMap::iterator it = B_charCountMap.find(chDigit);
      if (it == B_charCountMap.end())
      {
         std::pair<TCharCountMap::iterator,bool> pair =
            B_charCountMap.insert(TCharCountMap::value_type(chDigit,0));

         if (const bool fSuccess = pair.second)
            it = pair.first;
         else
            throw new std::runtime_error(E_CANNOT_INSERT_KEY_INTO_MAP);

      }

      it->second++;
   }

   debug_MapPrint(B_charCountMap);

   
   vector<char> B_digitsSortedDescendingArray;
   unsigned int digitIndexToUse = 0;

   for (TCharCountMap::reverse_iterator it = B_charCountMap.rbegin(); it != B_charCountMap.rend(); ++it)
      B_digitsSortedDescendingArray.push_back(it->first);

   for (unsigned n = 0; n < A.length(); ++n)
   {
      const vector<char>& v = B_digitsSortedDescendingArray;
      if (digitIndexToUse + 1 > v.size())
         break;
      const char B_digit = v[digitIndexToUse];

      if (A[n] < B_digit)
      {
         TCharCountMap::iterator it = B_charCountMap.find(B_digit);
         if (it->second <= 0)
            throw new std::runtime_error(E_COUNT_FOR_KEY_IS_ZERO);

         A[n] = it->first;
         it->second--;

         if (it->second == 0)
            digitIndexToUse++;
      }
   }


   std::cout << "B: " << B << std::endl;
   std::cout << "old A: " << A_backup << std::endl;
   std::cout << "new A: " << A << std::endl;

   // std::cin.get();
}
//---------------------------------------------------------------------------
void debug_MapPrint(const TCharCountMap& p_charCountMap)
{
   for(char ch = '9'; ch >= '0'; --ch)
   {
      TCharCountMap::const_iterator it = p_charCountMap.lower_bound(ch);
//      TCharCountMap::const_iterator it = p_charCountMap.upper_bound(ch);

      int charCount = 0;

      if (it->first == ch)
         charCount = it->second;

      if (charCount == 0)
         continue;

      std::printf("%c -> [%3d] key == %c", ch, charCount, it->first);

      if (it == p_charCountMap.end())
         std::cout << "[it == p_charCountMap.end()]";

      std::cout << std::endl;
   }
}
//---------------------------------------------------------------------------