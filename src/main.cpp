#include "Zmetek.h"

int main(int argc, char *argv[]) {
    ZmetekApp app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}