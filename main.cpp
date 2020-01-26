
#include "Main.h"

int main(int argc, char* argv[]) {

    boot::Main m;
    if (argc <= 1) {
        m.main(5600);
    } else {
        m.main(atoi(argv[1]));
    }
    return  0;
}

