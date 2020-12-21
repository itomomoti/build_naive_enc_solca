/*compress_main.cpp
MIT License

Copyright (c) 2017 Yoshimasa Takabatake

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <string>
#include <iostream>
#include <stdio.h>
#include "solca.hpp"
#include "cmdline.h"

using namespace std;

int main(int argc, char *argv[])
{
  cmdline::parser p;
  p.add<string>("input_file",  'i', "input file name",  true);
  p.add<string>("output_file", 'o', "output file name", true);
  p.add<bool>  ("erase_br",    'e', "erase line break", false);
  p.add<bool>  ("print_logs",  'p', "print logs", false);

  p.parse_check(argc, argv);
  const string input_file   = p.get<string>("input_file");
  const string output_file  = p.get<string>("output_file");
  const bool   erase_br     = p.get<bool>  ("erase_br");
  const bool   print_logs   = p.get<bool>  ("print_logs");

  solca_comp::SOLCA solca;
  
  solca.Build(input_file, 
              output_file, 
              erase_br,
              print_logs);

  // std::cout << "num of rules = " << solca.NumRules() - solca_comp::kAlphabetSize << std::endl;
  // for (uint64_t i = solca_comp::kAlphabetSize; i < solca.NumRules(); ++i) {
  //   std::cout << solca.Left(i) << ", " << solca.Right(i) << std::endl;
  // }

  FILE* file;
  file = fopen(output_file.c_str(), "wb");
  for (uint64_t i = solca_comp::kAlphabetSize; i < solca.NumRules(); ++i) {
    unsigned int left = solca.Left(i);
    unsigned int right = solca.Right(i);
    fwrite(&left, sizeof(left), 1, file);
    fwrite(&right, sizeof(right), 1, file);
  }

  return 0;
}

