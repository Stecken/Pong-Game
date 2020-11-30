#include <Windows.h>
#include "libsgame.h"
#include <iostream>
#include "game.h"

const Uint8* keystates;
SDL_Event event;
bool rodando = true;
SDL_Window* window;
SDL_Surface* icon;
SDL_Texture* background;
SDL_Surface* screen;
TTF_Font* font;
Mix_Chunk* music1;
SDL_Renderer* renderer;
int width, height;

void initAll();
void closeReturn(Mix_Chunk* music1, SDL_Renderer* renderer, SDL_Window* window);
void EventsSDL(Game& Jogo, SDL_Event& event, int lim);
void CriaTexto(int x, int y, SDL_Rect* textRect, SDL_Surface* text, int w, int h);
void changeText(SDL_Surface* textTitle, SDL_Texture* textTextureTitle, SDL_Rect* textRect, SDL_Color *colorText, int* w, int* h);

int main(int argc, char* argv[]) {
    
    // SDL_INIT_EVERYTHING
    initAll();
    
    int color[3] = { 255, 0, 0 };
    int widthpl2 = width - 50;
    Player* player1 = new Player(20, (height / 2) - 20, 30, 60, color);
    Player* player2 = new Player(widthpl2, (height / 2) - 20, 30, 60, color);
    Game *Jogo = new Game(player1, player2, &(*renderer));
    /*C:\\DevStecken\\Tests\\SDLTestVisualStudio\\gui.png*/
    /*C:/DevStecken/Tests/SDLTestVisualStudio/gui.png*/
    /*gui.png*/
    icon = IMG_Load("GUI.png");
    if (!icon) {
        printf("IMG_Load: %s\n", IMG_GetError());
    }
    background = SDL_CreateTextureFromSurface(renderer, icon);
    bool reini = true;
    SDL_Color colorText = { 0, 0, 255 };
    SDL_Surface* text = TTF_RenderText_Solid(font,"Pressione a tecla ENTER", colorText);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);
    colorText = { 1, 1, 1 };
    font = TTF_OpenFont("Kiano-Trial.ttf", 20);
    /*EbertaLightDemoRegular.ttf*/
    SDL_Surface* textSteck = TTF_RenderText_Solid(font, "Made by Stecken", colorText);
    SDL_Texture* textTextureSteck = SDL_CreateTextureFromSurface(renderer, textSteck);


    colorText = { 50, 250, 50 };
    font = TTF_OpenFont("EbertaLightDemoRegular.ttf", 60);
    SDL_Surface* textTitle = TTF_RenderText_Solid(font, "GuiPong", colorText);
    SDL_Texture* textTextureTitle = SDL_CreateTextureFromSurface(renderer, textTitle);

    int texW, texH, texStecW, texStecH, textTIw, textTIh ;
    SDL_QueryTexture(textTexture, NULL, NULL, &texW, &texH);
    SDL_QueryTexture(textTextureSteck, NULL, NULL, &texStecW, &texStecH);
    SDL_QueryTexture(textTextureTitle, NULL, NULL, &textTIw, &textTIh);
    SDL_Rect textRect = { 0 };
    SDL_Rect textBySte = { 0 };
    SDL_Rect textTitleRec = { 0 };
    screen = SDL_GetWindowSurface(window);
    SDL_Rect back;
    back.x = 70;
    back.y = 10;
    back.w = width;
    back.h = height;
    while (reini) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    reini = false;
                }
            }
        }
        //background image
        
        //SDL_RenderPresent(renderer);
        //SDL_UpdateWindowSurface(window);
        //SDL_RenderCopy(renderer, background, NULL, NULL);
        //SDL_SetRenderTarget(renderer, background);
        SDL_BlitSurface(icon, NULL, screen, &back);
        //SDL_BlitSurface(text, NULL, screen, &textRect);
        CriaTexto(190, 260, &textRect, &(*text), texH, texW);
        CriaTexto(90, 420, &textBySte, &(*textSteck), texStecH, texStecW);
        //changeText(&(*textTitle), &(*textTextureTitle), &textTitleRec, &colorText, &textTIh, &textTIw);
        CriaTexto(220, 50, &textTitleRec, &(*textTitle), textTIh, textTIw);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderCopy(renderer, textTextureSteck, NULL, &textBySte);
        SDL_RenderCopy(renderer, textTextureTitle, NULL, &textTitleRec);
        SDL_UpdateWindowSurface(window);
        //SDL_RenderPresent(renderer);
    }
    TTF_CloseFont(font);
    SDL_DestroyTexture(textTextureTitle);
    SDL_FreeSurface(textTitle);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(textTextureSteck);
    SDL_FreeSurface(textSteck);
    limpaTela(renderer);
    SDL_DestroyTexture(background);
    int i = 1;
    SDL_SetWindowIcon(window, icon);
    Jogo->desenhaPlayer(player1);
    Jogo->desenhaPlayer(player2);
    // processo principal, espera evento de saída.
    while (Jogo->estadoGame()) {
        SDL_PumpEvents();
        std::cout << "Tecla: " << (keystates[SDL_SCANCODE_W] && keystates[SDL_SCANCODE_UP]) << std::endl;
        Jogo->KeyState(keystates, height);
        EventsSDL(*Jogo, event, height);
        Jogo->mostraMovimento(player1);
        Jogo->mostraMovimento(player2);
        limpaTela(renderer);
        //Jogo->mostraMovimento(player1);
    }
    closeReturn(&(*music1), &(*renderer), &(*window));
    return 0;
}

void initAll() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    IMG_Init(IMG_INIT_JPG);
    keystates = SDL_GetKeyboardState(NULL);
    event = { 0 };
    TTF_Init();
    font = TTF_OpenFont("NerkoOne-Regular.ttf", 25);
    window = SDL_CreateWindow("GuiPong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    music1 = Mix_LoadWAV("beto.wav");
    if (!music1) {
        std::cout << "Erro ao carregar musica: " << Mix_GetError() << std::endl;
    }
    SDL_GetWindowSize(&(*window), &width, &height);
    Mix_PlayChannel(-1, music1, -1);
    Mix_Volume(-1, 15);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (window == NULL) {
        printf("Impossivel abrir o jogo, motivo: %s\n", SDL_GetError());
    }
}

void closeReturn(Mix_Chunk* music1, SDL_Renderer* renderer, SDL_Window* window) {
    TTF_Quit();
    Mix_FreeChunk(music1);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void EventsSDL(Game& Jogo, SDL_Event& event, int lim) {
    if (SDL_PollEvent(&event)) {
        Jogo.EventWindow(&event);
    }
}

void changeText(SDL_Surface* textTitle, SDL_Texture* textTextureTitle, SDL_Rect* textRect, SDL_Color* colorText, int* w, int* h) {
    font = TTF_OpenFont("EbertaLightDemoRegular.ttf", 60);
    if (colorText->r <= 255) {
        ++colorText->r;
    }
    else {
        if (colorText->g <= 255) {
            ++colorText->g;
        }
        else {
            if (++colorText->b) {
                ++colorText->b;
            }
            else {
                colorText->r = 0;
                colorText->g = 0;
                colorText->b = 0;
            }
        }
    }
    textTitle = TTF_RenderText_Solid(font, "GuiPong", *colorText);
    textTextureTitle = SDL_CreateTextureFromSurface(renderer, textTitle);
    SDL_QueryTexture(textTextureTitle, NULL, NULL, &(*w), &(*h));
    SDL_BlitSurface(textTitle, NULL, screen, &(*textRect));
}

void CriaTexto(int x, int y, SDL_Rect *textRect, SDL_Surface* text, int w, int h) {
    /// defina antes sua variável
    textRect->x = x;  //controls the rect's x coordinate 
    textRect->y = y; // controls the rect's y coordinte
    textRect->w = w; // controls the width of the rect
    textRect->h = h; // controls the height of the rect

    SDL_BlitSurface(text, NULL, screen, &(*textRect));
}