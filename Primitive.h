#pragma once 

struct Primitive_Color {
    int r; 
    int g; 
    int b; 
    int a; 
};

void Primitive_DrawLine(SDL_Renderer *renderer, int x1, int y1, 
                    int x2, int y2, Primitive_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Primitive_DrawRect(SDL_Renderer *renderer, int x, int y,
                    int width, int height, Primitive_Color color)
{
    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 
    SDL_RenderDrawRect(renderer, &rect); 
}

void Primitive_DrawFilledRect(SDL_Renderer *renderer, int x, int y,
                              int width, int height, Primitive_Color color)
{
    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 
    SDL_RenderFillRect(renderer, &rect);
}

void Primitive_DrawCircle(SDL_Renderer *renderer, int x, int y, 
                          int radius, Primitive_Color color)
{
    int origin_x = x - radius; 
    int origin_y = y - radius; 

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 

    for (int i = origin_y; i < 2 * radius; ++i)
    {
        for (int j = origin_x; j < 2 * radius; ++j)
        {
            int current_y = (i - y > 0) ? (i - y) : -(i - y);
            int current_x = (j - x > 0) ? (j - x) : -(j - x);

            if (current_y == radius && current_x == radius)
            {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }
}

void Primitive_DrawFilledCircle(SDL_Renderer *renderer, int x, int y, 
                                int radius, Primitive_Color color)
{
    int origin_x = x - radius; 
    int origin_y = y - radius; 

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 

    for (int i = origin_y; i < 2 * radius; ++i)
    {
        for (int j = origin_x; j < 2 * radius; ++j)
        {
            int current_y = (i - y > 0) ? (i - y) : -(i - y);
            int current_x = (j - x > 0) ? (j - x) : -(j - x);

            if (current_y <= radius && current_x <= radius)
            {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }
}

void drawCircle(int xc, int yc, int x, int y) 
{ 
    SDL_RenderDrawPoint(xc+x, yc+y, RED); 
    SDL_RenderDrawPoint(xc-x, yc+y, RED); 
    SDL_RenderDrawPoint(xc+x, yc-y, RED); 
    SDL_RenderDrawPoint(xc-x, yc-y, RED); 
    SDL_RenderDrawPoint(xc+y, yc+x, RED); 
    SDL_RenderDrawPoint(xc-y, yc+x, RED); 
    SDL_(xc+y, yc-x, RED); 
    putpixel(xc-y, yc-x, RED); 
} 


 // void Primitive_Triangle(SDL_Renderer, Primitive_Point, Primitive_Point, Primitive_Point, Primitive_Color); 
 // void Primitive_TriangleFilled(SDL_Renderer, Primitive_Point, Primitive_Point, Primitive_Point, Primitive_Color); 