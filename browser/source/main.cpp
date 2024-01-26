#include <astra/astra.h>

int main() {
    auto app = new Astra::Application();
    app->Run();
    delete app;
}
