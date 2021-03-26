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


SDL_Surface* text;
SDL_Texture* textTexture;

SDL_Surface* textSteck;
SDL_Texture* textTextureSteck;

SDL_Surface* textTitle;
SDL_Texture* textTextureTitle;



void initAll();
void closeReturn();
void EventsSDL(Game& Jogo, SDL_Event& event, int lim);
void CriaTexto(int x, int y, SDL_Rect* textRect, SDL_Surface* text, int w, int h);
void limpaRecursos();

int main(int argc, char* argv[]) {
    
    // SDL_INIT_EVERYTHING
    initAll();
    
    int color[3] = { 255, 0, 0 };
    int widthpl2 = width - 50;
    Player* player1 = new Player(20, (height / 2) - 20, 30, 60, color);
    Player* player2 = new Player(widthpl2, (height / 2) - 20, 30, 60, color);
    Game *Jogo = new Game(player1, player2, &(*renderer));

    icon = IMG_Load("GUI.png");
    if (!icon) {
        printf("IMG_Load: %s\n", IMG_GetError());
    }

    background = SDL_CreateTextureFromSurface(renderer, icon);
    bool reini = true;
    SDL_Color colorText = { 0, 0, 255 };
    text = TTF_RenderText_Solid(font,"Pressione a tecla ENTER", colorText);
    textTexture = SDL_CreateTextureFromSurface(renderer, text);

    colorText = { 1, 1, 1 };
    font = TTF_OpenFont("Kiano-Trial.ttf", 20);

    textSteck = TTF_RenderText_Solid(font, "Made by Stecken", colorText);
    textTextureSteck = SDL_CreateTextureFromSurface(renderer, textSteck);


    colorText = { 50, 250, 50 };
    font = TTF_OpenFont("EbertaLightDemoRegular.ttf", 60);
    textTitle = TTF_RenderText_Solid(font, "GuiPong", colorText);
    textTextureTitle = SDL_CreateTextureFromSurface(renderer, textTitle);

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

    SDL_BlitSurface(icon, NULL, screen, &back);

    CriaTexto(190, 260, &textRect, &(*text), texH, texW);
    CriaTexto(90, 420, &textBySte, &(*textSteck), texStecH, texStecW);

    CriaTexto(220, 50, &textTitleRec, &(*textTitle), textTIh, textTIw);
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderCopy(renderer, textTextureSteck, NULL, &textBySte);
    SDL_RenderCopy(renderer, textTextureTitle, NULL, &textTitleRec);
    SDL_UpdateWindowSurface(window);

    while (reini) { 
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    reini = false;
                }
            }
            else if (event.type == SDL_QUIT) {
                limpaRecursos();
                closeReturn();
            }
        }  
    }
    
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
    closeReturn();
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

void closeReturn() {
    TTF_Quit();
    Mix_FreeChunk(music1);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    exit(1);
}

void EventsSDL(Game& Jogo, SDL_Event& event, int lim) {
    if (SDL_PollEvent(&event)) {
        Jogo.EventWindow(&event);
    }
}

void CriaTexto(int x, int y, SDL_Rect *textRect, SDL_Surface* text, int w, int h) {
    /// defina antes sua variável
    textRect->x = x;  //controls the rect's x coordinate 
    textRect->y = y; // controls the rect's y coordinte
    textRect->w = w; // controls the width of the rect
    textRect->h = h; // controls the height of the rect

    SDL_BlitSurface(text, NULL, screen, &(*textRect));
}

void limpaRecursos() {
    TTF_CloseFont(font);
    SDL_DestroyTexture(textTextureTitle);
    SDL_FreeSurface(textTitle);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(textTextureSteck);
    SDL_FreeSurface(textSteck);
    limpaTela(renderer);
    SDL_DestroyTexture(background);
}