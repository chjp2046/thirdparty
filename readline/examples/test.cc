/**
 * @file test.cc
 * @brief
 * @author lornaxue
 * @version 1.0
 * @date 2010-09-09
 */
#define USE_VARARGS
#define PREFER_STDARG

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <stdarg.h>
#include <readline.h>
#include <history.h>
#include <string>
#include "stdio.h"
#include <vector>
#include "assert.h"
#define NONE "\033[m"
#define GREEN "\033[0;32;32m"
#define RED "\033[0;32;31m"

static  key_color_info key_color_table[] = {{"create", RED,  6}, {"add", GREEN,  3}, {NULL, NULL, 0} };

void init()
{
	rl_set_key_color_table(key_color_table);
}

int main(int argc, char** argv)
{
   init();
   while (1)
   {
	   std::string a = "xcube>";

	   std::string read_line=  readline(a.c_str());

	   bool is_initial = true;
	   add_history(read_line.c_str());
	   std::cout<<"line:::"<<read_line<<std::endl;
   }
}
