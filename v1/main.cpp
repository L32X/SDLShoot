#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <cstddef>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

int main() {
    // SDL 初始化
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL INIT FAIL: " << SDL_GetError() << std::endl;
        return 1;
    }
    // 创建窗口(窗口)
    SDL_Window *window = SDL_CreateWindow("SDLShooter", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    // 创建渲染器(绑定window的画笔)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // SDL_image 初始化(渲染图片)
    if(SDL_Init(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG))) {
        std::cerr << "SDL IMAGE INIT FAIL: " << IMG_GetError() << std::endl;
        return 1;
    }
    // 加载图片
    SDL_Texture *texture = IMG_LoadTexture(renderer, "assets/image/Stars-A.png");

    // mixer初始化(music)
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL MIXER INIT FAIL: " << Mix_GetError() << std::endl;
        return 1;
    }
    // 读取音乐
    Mix_Music *music = Mix_LoadMUS("assets/music/03_Racing_Through_Asteroids_Loop.ogg");
    // 播放音乐
    Mix_PlayMusic(music, 0);

    // SDL_ttf(字体) 初始化
    if(TTF_Init() != 0) {
        std::cerr << "SDL TTF INIT FAIL: " << TTF_GetError() << std::endl;
        return 1;
    }
    // 加载字体
    TTF_Font *font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 24);
    // 创建文字纹理
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, "SDL 中文", color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, surface);

    // 渲染循环
    while (true) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
            // 清屏
            SDL_RenderClear(renderer);
            // 画一个长方形
            SDL_Rect rect = {100, 100, 200, 200};
            // 设置颜色
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);

            // 插入图片
            SDL_RenderCopy(renderer, texture, NULL, NULL);

            // 画文本
            SDL_Rect textRect = {0, 0, surface->w,surface->h};
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

            // 初始化画笔
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            // 更新屏幕
            SDL_RenderPresent(renderer);
        }
    }

    // 清理图片资源
    SDL_DestroyTexture(texture);
    IMG_Quit();

    // 清理音乐资源
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();

    // 释放字体资源
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    TTF_Quit();

    // 释放退出
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}