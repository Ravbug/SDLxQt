#include <SDL3/SDL.h>
#include <cmath>
#include <SDL3/SDL_main.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QFrame>

class MainWindow : public QMainWindow{
public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent){
        this->setWindowTitle("Qt Window");
        
        auto layout = new QHBoxLayout;
        
        auto button = new QPushButton("Push me!", this);
        layout->addWidget(button);
        
        connect(button,&QPushButton::released,this,&MainWindow::ButtonClicked);
        
        auto frame = new QFrame;
        frame->setLayout(layout);
        
        this->setCentralWidget(frame);
    }
    
    void ButtonClicked(){
        SDL_Log("Qt Button Clicked!");
    }
};

void SDL_Fail(){
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
    exit(1);
}


// Note: your main function __must__ take this form, otherwise on nonstandard platforms (iOS, etc), your app will not launch.
int main(int argc, char* argv[]){
    
    // init the library, here we make a window so we only need the Video capabilities.
    if (SDL_Init(SDL_INIT_VIDEO)){
        SDL_Fail();
    }
    
    // create a window
    SDL_Window* window = SDL_CreateWindow("SDL Window", 352, 430, SDL_WINDOW_RESIZABLE);
    if (!window){
        SDL_Fail();
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer){
        SDL_Fail();
    }
    
    // print some information about the window
    SDL_ShowWindow(window);
    {
        int width, height, bbwidth, bbheight;
        SDL_GetWindowSize(window, &width, &height);
        SDL_GetWindowSizeInPixels(window, &bbwidth, &bbheight);
        SDL_Log("Window size: %ix%i", width, height);
        SDL_Log("Backbuffer size: %ix%i", bbwidth, bbheight);
        if (width != bbwidth){
            SDL_Log("This is a highdpi environment.");
        }
    }
    
    // create the Qt application
    QApplication qtApplication(argc, argv);
    auto win = std::make_unique<MainWindow>();
    win->show();
    
    SDL_Log("Application started successfully!");
    bool app_quit = false;
    while (!app_quit) {
        // Get events.
        qtApplication.processEvents(QEventLoop::ProcessEventsFlag::AllEvents);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                app_quit = true;
            if (event.type == SDL_EVENT_WINDOW_RESIZED){
                SDL_Log("Window resized to: %dx%d",event.window.data1, event.window.data2);
            }
            break;
        }
        
        // draw a color
        auto time = SDL_GetTicks() / 1000.f;
        auto red = (std::sin(time) + 1) / 2.0 * 255;
        auto green = (std::sin(time / 2) + 1) / 2.0 * 255;
        auto blue = (std::sin(time) * 2 + 1) / 2.0 * 255;
        
        SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }


    // cleanup everything at the end
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("Application quit successfully!");
    return 0;
}
