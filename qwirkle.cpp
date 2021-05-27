#include <iostream>

#include "LinkedList.h"
#include "Menu.h"

int main(void)
{
   sharedLinkedListPtr list = std::make_shared<LinkedList>();

   runMenu();

   return EXIT_SUCCESS;
}
