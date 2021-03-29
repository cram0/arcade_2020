/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
** File description:
** LibSDL2
*/

#include "LibSDL2.hpp"

LibSDL2::LibSDL2()
{
    Initialize();
}

LibSDL2::~LibSDL2()
{
    Destroy();
}

void LibSDL2::Initialize()
{
    InitEverything();
    InitRenderer();
    InitFont();
    InitGameText();
    InitMenuText();
    InitGameOverText();
    _start_clock = clock();
}

void LibSDL2::InitFont()
{
    if(TTF_Init() == -1) {
        SDL_LogError(0, "TTF_Init initialisation : %s %d : %s", __FILE__, __LINE__, TTF_GetError());
        return;
    }
    _font = TTF_OpenFont("lib/graphics/sdl2/font/OpenSans-Regular.ttf", 50);
}

void LibSDL2::InitGameText()
{
    _score_text_list.emplace_back(std::make_pair("0", (SDL_Rect){190, 710, 100, 100}));
    _score_text_list.emplace_back(std::make_pair("Score :", (SDL_Rect){10, 710, 100, 100}));
}

void LibSDL2::InitMenuText()
{
    _menu_text_list.emplace_back(std::make_pair("Arcade", (SDL_Rect){WINDOW_WIDTH / 4 + 100, WINDOW_HEIGHT / 4, 100, 100}));
    _menu_text_list.emplace_back(std::make_pair("Nibbler\n   O", (SDL_Rect){WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 + 100, 100, 100}));
    _menu_text_list.emplace_back(std::make_pair("Pacman\n   P", (SDL_Rect){WINDOW_WIDTH / 4 + 200, WINDOW_HEIGHT / 4 + 100, 100, 100}));
}

void LibSDL2::InitGameOverText()
{
    _game_over_text_list.emplace_back(std::make_pair("0", (SDL_Rect){WINDOW_WIDTH / 2 + 50, WINDOW_HEIGHT / 3 + 20, 100, 100}));
    _game_over_text_list.emplace_back(std::make_pair("Game Over", (SDL_Rect){WINDOW_WIDTH / 2 - 125, WINDOW_HEIGHT / 4, 100, 100}));
    _game_over_text_list.emplace_back(std::make_pair("Score :", (SDL_Rect){WINDOW_WIDTH / 2 - 125, WINDOW_HEIGHT / 3 + 20, 100, 100}));
    _game_over_text_list.emplace_back(std::make_pair("Enter name :", (SDL_Rect){10, WINDOW_HEIGHT - 250, 100, 100}));
    _game_over_text_list.emplace_back(std::make_pair("", (SDL_Rect){10, WINDOW_HEIGHT - 150, 100, 100}));
}

void LibSDL2::InitEverything()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_LogError(0, "SDL_Init initialisation : %s %d : %s", __FILE__, __LINE__, SDL_GetError());
		return;
	}
	else {
		_window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (_window == NULL) {
			SDL_LogError(0, "Window initialisation : %s %d : %s", __FILE__, __LINE__, SDL_GetError());
			return;
		}
	}
}

void LibSDL2::InitRenderer()
{
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        SDL_LogError(0, "Renderer initialisation : %s %d : %s", __FILE__, __LINE__, SDL_GetError());
        SDL_assert(_renderer);
        return;
    }
}

void LibSDL2::DrawMapBackground()
{
    SDL_FRect r_pos = {0, 0, CELL_SIZE * GRID_SIZE_X + 2, CELL_SIZE * GRID_SIZE_Y + 2};
    SDL_Surface *bg_rect_sf = SDL_CreateRGBSurface(0, CELL_SIZE * GRID_SIZE_X + 2, CELL_SIZE * GRID_SIZE_Y + 2, 32, 0, 0, 0, 0);
    SDL_FillRect(bg_rect_sf, NULL, SDL_MapRGBA(bg_rect_sf->format, 255, 255, 255, 255));
    SDL_Texture *txt = SDL_CreateTextureFromSurface(_renderer, bg_rect_sf);
    SDL_RenderCopyF(_renderer, txt, NULL, &r_pos);
    SDL_FreeSurface(bg_rect_sf);
    SDL_DestroyTexture(txt);

    r_pos = {1, 1, CELL_SIZE * GRID_SIZE_X, CELL_SIZE * GRID_SIZE_Y};
    bg_rect_sf = SDL_CreateRGBSurface(0, CELL_SIZE * GRID_SIZE_X, CELL_SIZE * GRID_SIZE_Y, 32, 0, 0, 0, 0);
    SDL_FillRect(bg_rect_sf, NULL, SDL_MapRGBA(bg_rect_sf->format, 0, 0, 0, 255));
    txt = SDL_CreateTextureFromSurface(_renderer, bg_rect_sf);
    SDL_RenderCopyF(_renderer, txt, NULL, &r_pos);
    SDL_FreeSurface(bg_rect_sf);
    SDL_DestroyTexture(txt);
}

void LibSDL2::DrawRectangle(char id, SDL_Point r_pos)
{
    SDL_FRect pos = {(float)r_pos.x, (float)r_pos.y, CELL_SIZE, CELL_SIZE};
    SDL_Surface *rect_sf = SDL_CreateRGBSurface(0, CELL_SIZE, CELL_SIZE, 32, 0, 0, 0, 0);
    if (id == '0')
        SDL_FillRect(rect_sf, NULL, SDL_MapRGBA(rect_sf->format, 0, 0, 0, 255));
    if (id == '1')
        SDL_FillRect(rect_sf, NULL, SDL_MapRGBA(rect_sf->format, 255, 0, 0, 255));
    if (id == '2')
        SDL_FillRect(rect_sf, NULL, SDL_MapRGBA(rect_sf->format, 255, 255, 255, 255));
    if (id == '3')
        SDL_FillRect(rect_sf, NULL, SDL_MapRGBA(rect_sf->format, 0, 255, 0, 255));
    if (id == '4')
        SDL_FillRect(rect_sf, NULL, SDL_MapRGBA(rect_sf->format, 0, 100, 255, 255));
    if (id == '5') {
        rect_sf = SDL_CreateRGBSurface(0, CELL_SIZE / 12, CELL_SIZE / 12, 32, 0, 0, 0, 0);
        SDL_FillRect(rect_sf, NULL, SDL_MapRGBA(rect_sf->format, 255, 255, 255, 255));
    }
    if (id == '-') {
        rect_sf = SDL_CreateRGBSurface(0, CELL_SIZE, CELL_SIZE / 2, 32, 0, 0, 0, 0);
        SDL_FillRect(rect_sf, NULL, SDL_MapRGBA(rect_sf->format, 255, 255, 255, 255));
    }
    SDL_Texture *txt = SDL_CreateTextureFromSurface(_renderer, rect_sf);

    if (id == '5') {
        float offset = (CELL_SIZE / 12.0) / 2.0;
        float gum_pos = CELL_SIZE / 2.0 - offset;
        SDL_FRect tmp = {pos.x + gum_pos, pos.y + gum_pos, CELL_SIZE / 6, CELL_SIZE / 6};
        SDL_RenderCopyF(_renderer, txt, NULL, &tmp);
    }

    else {
        SDL_RenderCopyF(_renderer, txt, NULL, &pos);
    }
    SDL_FreeSurface(rect_sf);
    SDL_DestroyTexture(txt);
}

void LibSDL2::SDL_RenderFillCircle(int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawLine(_renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(_renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(_renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(_renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

void LibSDL2::DrawCircle(char id, SDL_Point r_pos)
{
    if (id == 'a') {
        SDL_SetRenderDrawColor(_renderer, 255, 255, 0, 255);
        SDL_RenderFillCircle(r_pos.x + CELL_SIZE / 2, r_pos.y + CELL_SIZE / 2, (int)CELL_SIZE / 2.2);
    }
    if (id == 'u') {
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
        SDL_RenderFillCircle(r_pos.x + CELL_SIZE / 2, r_pos.y + CELL_SIZE / 2, (int)CELL_SIZE / 4);
    }
    if (id == 'p') {
        SDL_SetRenderDrawColor(_renderer, 255, 105, 180, 255);
        SDL_RenderFillCircle(r_pos.x + CELL_SIZE / 2, r_pos.y + CELL_SIZE / 2, (int)CELL_SIZE / 2.2);
    }
    if (id == 'b') {
        SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
        SDL_RenderFillCircle(r_pos.x + CELL_SIZE / 2, r_pos.y + CELL_SIZE / 2, (int)CELL_SIZE / 2.2);
    }
    if (id == 'i') {
        SDL_SetRenderDrawColor(_renderer, 0, 255, 255, 255);
        SDL_RenderFillCircle(r_pos.x + CELL_SIZE / 2, r_pos.y + CELL_SIZE / 2, (int)CELL_SIZE / 2.2);
    }
    if (id == 'c') {
        SDL_SetRenderDrawColor(_renderer, 255, 165, 0, 255);
        SDL_RenderFillCircle(r_pos.x + CELL_SIZE / 2, r_pos.y + CELL_SIZE / 2, (int)CELL_SIZE / 2.2);
    }
    if (id == 's') {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
        SDL_RenderFillCircle(r_pos.x + CELL_SIZE / 2, r_pos.y + CELL_SIZE / 2, (int)CELL_SIZE / 2.2);
    }
}

void LibSDL2::DrawShapeFromID(char id, SDL_Point r_pos)
{
    if ((id >= '0' && id <= '9') || id == '-')
        DrawRectangle(id, r_pos);
    else
        DrawCircle(id, r_pos);
}

void LibSDL2::DrawMap(std::vector<std::string> map)
{
    DrawMapBackground();
    SDL_Point r_pos = {1, 1};
    for (int y = 0; y < GRID_SIZE_Y; y++) {
        for (int x = 0; x < GRID_SIZE_X; x++) {
            DrawShapeFromID(map[y][x], r_pos);
            r_pos.x += CELL_SIZE;
        }
        r_pos.y += CELL_SIZE;
        r_pos.x = 1;
    }
}

void LibSDL2::DrawText(const char *text, SDL_Rect rect)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *text_sf = TTF_RenderText_Blended_Wrapped(_font, text, color, (Uint32)1000);
    SDL_Texture *tmp = SDL_CreateTextureFromSurface(_renderer, text_sf);
    SDL_QueryTexture(tmp, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(_renderer, tmp, NULL, &rect);
    SDL_FreeSurface(text_sf);
    SDL_DestroyTexture(tmp);
}

void LibSDL2::UpdateScoreValue(int score)
{
    _score_text_list[0].first = std::to_string(score);
    _game_over_text_list[0].first = std::to_string(score);
}

void LibSDL2::DrawScore(int score)
{
    UpdateScoreValue(score);
    for (auto text : _score_text_list) {
        DrawText(text.first.c_str(), text.second);
    }
}

void LibSDL2::Display()
{
    clock_t _end_clock = clock();
    while ((double)(_end_clock - _start_clock) / CLOCKS_PER_SEC <= 0.1) {
        _end_clock = clock();
        SDL_RenderPresent(_renderer);
    }
    _start_clock = clock();
}

void LibSDL2::DisplayMenu()
{
    for (auto text : _menu_text_list) {
        DrawText(text.first.c_str(), text.second);
    }
    SDL_RenderPresent(_renderer);
}

void LibSDL2::DisplayGameOver()
{
    for (auto text : _game_over_text_list) {
        DrawText(text.first.c_str(), text.second);
    }
    SDL_RenderPresent(_renderer);
}

void LibSDL2::Destroy()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void LibSDL2::Clear()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void LibSDL2::Close()
{
    Destroy();
}

evtKey LibSDL2::GetEventKey()
{
    while (SDL_PollEvent(&_event)) {
        switch (_event.type) {
            case SDL_KEYDOWN:
                switch (_event.key.keysym.sym) {
                    case SDLK_UP:
                        return (evtKey::UP);
                    case SDLK_DOWN:
                        return (evtKey::DOWN);
                    case SDLK_LEFT:
                        return (evtKey::LEFT);
                    case SDLK_RIGHT:
                        return (evtKey::RIGHT);
                    case SDLK_o:
                        return (evtKey::PREV_GAME);
                    case SDLK_p:
                        return (evtKey::NEXT_GAME);
                    case SDLK_r:
                        return (evtKey::RESET_GAME);
                    case SDLK_DELETE:
                        return (evtKey::GO_MENU);
                    case SDLK_RETURN:
                        return (evtKey::CONFIRM_NAME);
                    case SDLK_b:
                        return (evtKey::PREV_GRAPH);
                    case SDLK_n:
                        return (evtKey::NEXT_GRAPH);
                    case SDLK_ESCAPE:
                        return (evtKey::QUIT_GAME);
                    default:
                        return (evtKey::NONE);
                }
            case SDL_QUIT:
                return (evtKey::QUIT_GAME);
        }
    }
    return (evtKey::NONE);
}
