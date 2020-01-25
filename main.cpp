
#include "Main.h"

int main(int argc, char* argv[]) {

    if (argc == 1) {

        cout<<"missing port in command line"<<endl;
        return 0;
    }
    boot::Main m;
    m.main(atoi(argv[1]));
    //m.main(5600);

}

