#include <QCoreApplication>
#include <thread>
#include <vector>
#include <memory>
#include <windows.h>

#include "model.h"
#include "exponentialdelayer.h"
#include "application.h"


int main(int argc, char *argv[])
{
    Application a(argc, argv);
    return a.exec();
}

