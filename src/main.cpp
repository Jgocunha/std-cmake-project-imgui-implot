#include <iostream>

#include "example-imgui.h"

int main()
{
    std::cout << "Hello, world!" << std::endl;

    UserInterface ui;

    ui.init();

    while(!ui.getCloseUI())
    {
        ui.step();
    }
    ui.close();

    return 0;
}