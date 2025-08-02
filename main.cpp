#include <iostream>
#include <ostream>

#include "cava/System.h"
#include "cava/macros/public.h"
#include "cava/types/integer/Integer.h"

int main(int argc, char *argv[]) {
    Integer hehe = 1;

    int a = hehe;

    System::println(a);
}
