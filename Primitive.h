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

void Primitive_PlotCirclePoints(SDL_Renderer *renderer, int center_x, int center_y, 
                                         int x, int y, Primitive_Color color) 
{ 
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 

    SDL_RenderDrawPoint(renderer, center_x + x, center_y + y); 
    SDL_RenderDrawPoint(renderer, center_x - x, center_y + y); 
    SDL_RenderDrawPoint(renderer, center_x + x, center_y - y); 
    SDL_RenderDrawPoint(renderer, center_x - x, center_y - y); 
    SDL_RenderDrawPoint(renderer, center_x + y, center_y + x); 
    SDL_RenderDrawPoint(renderer, center_x - y, center_y + x); 
    SDL_RenderDrawPoint(renderer, center_x + y, center_y - x); 
    SDL_RenderDrawPoint(renderer, center_x - y, center_y - x); 
} 

void Primitive_DrawCircleLines(SDL_Renderer *renderer, int center_x, int center_y, 
                               int x, int y, Primitive_Color color) 
{ 
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 

    // NOTE: currently not filling in the enitre circle (near 45 degrees) because line is 1px thick
    SDL_RenderDrawLine(renderer, center_x + y, center_y + x, center_x - y, center_y - x);
    SDL_RenderDrawLine(renderer, center_x + x, center_y + y, center_x - x, center_y - y);
    SDL_RenderDrawLine(renderer, center_x + x, center_y - y, center_x - x, center_y + y);
    SDL_RenderDrawLine(renderer, center_x + y, center_y - x, center_x - y, center_y + x);
} 

void Primitive_DrawCircle(SDL_Renderer *renderer, int center_x, int center_y, 
                          int radius, Primitive_Color color)
{
    int x = 0; 
    int y = radius; 
    int decision = 3 - 2 * radius; 

    Primitive_PlotCirclePoints(renderer, center_x, center_y, x, y, color); 

    while (x <= y)
    {
        x++; 

        if (decision > 0)
        {
            y--;

            decision += 4 * (x - y) + 10; 
        }
        else 
        {
            decision += 4 * x + 6; 
        }

        Primitive_PlotCirclePoints(renderer, center_x, center_y, x, y, color); 
    }
}

void Primitive_DrawFilledCircle(SDL_Renderer *renderer, int center_x, int center_y, 
                                int radius, Primitive_Color color)
{
    int x = 0; 
    int y = radius; 
    int decision = 3 - 2 * radius; 

    Primitive_DrawCircleLines(renderer, center_x, center_y, x, y, color); 

    while (x <= y)
    {
        x++; 

        if (decision > 0)
        {
            y--;

            decision += 4 * (x - y) + 10; 
        }
        else 
        {
            decision += 4 * x + 6; 
        }

        Primitive_DrawCircleLines(renderer, center_x, center_y, x, y, color); 
    }
}

 // void Primitive_Triangle(SDL_Renderer, Primitive_Point, Primitive_Point, Primitive_Point, Primitive_Color); 
 // void Primitive_TriangleFilled(SDL_Renderer, Primitive_Point, Primitive_Point, Primitive_Point, Primitive_Color); 