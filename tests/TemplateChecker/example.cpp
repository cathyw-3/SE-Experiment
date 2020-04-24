#include <stdio.h>

enum Month {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};


int main()
{
    unsigned i = 9;
    switch (i) {
      case 0: printf("Jan\n"); break;
      case 9: printf("Oct\n"); break;
      default: printf("None\n"); break;
    }

    return 0;
}
