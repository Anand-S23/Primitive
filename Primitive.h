#pragma once 

struct Primitive_Color {
    int r; 
    int g; 
    int b; 
    int a; 
};

// Clears screen to color
void Primitive_Clear(SDL_Renderer *renderer, Primitive_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

// Draws point at (x, y) 
void Primitie_DrawPoint(SDL_Renderer *renderer, int x, int y, color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, x, y); 
}

// Draws line from (x1, y1) to (x2, y2) 
void Primitive_DrawLine(SDL_Renderer *renderer, int x1, int y1, 
                    int x2, int y2, Primitive_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

// Draws rectangle from the origin (x, y) that is width x height
void Primitive_DrawRect(SDL_Renderer *renderer, int x, int y,
                    int width, int height, Primitive_Color color)
{
    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 
    SDL_RenderDrawRect(renderer, &rect); 
}

// Draws a filled rectangle from the origin (x, y) that is width x height
void Primitive_DrawFilledRect(SDL_Renderer *renderer, int x, int y,
                              int width, int height, Primitive_Color color)
{
    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 
    SDL_RenderFillRect(renderer, &rect);
}

static void Primitive_PlotCirclePoints(SDL_Renderer *renderer, int center_x, int center_y, 
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

// Draws a circle with a radius of [radius] at (center_x, center_y)
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

static void Primitive_DrawCircleLines(SDL_Renderer *renderer, int center_x, int center_y, 
                               int x, int y, Primitive_Color color) 
{ 
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 

    // NOTE: currently not filling in the enitre circle (near 45 degrees) because line is 1px thick
    SDL_RenderDrawLine(renderer, center_x + y, center_y + x, center_x - y, center_y - x);
    SDL_RenderDrawLine(renderer, center_x + x, center_y + y, center_x - x, center_y - y);
    SDL_RenderDrawLine(renderer, center_x + x, center_y - y, center_x - x, center_y + y);
    SDL_RenderDrawLine(renderer, center_x + y, center_y - x, center_x - y, center_y + x);
} 

// Draws a filled circle with a radius of [radius] at (center_x, center_y)
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

// Draws a triangle with the vertices (x1, y1), (x2, y2), (x3, y3)
void Primitive_DrawTriangle(SDL_Renderer *renderer, int x1, int y1, int x2, int y2,                         
                            int x3, int y3, Primitive_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 

    SDL_RenderDrawLine(renderer, x1, y1, x2, y2); 
    SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(renderer, x3, y3, x1, y1); 
}

// Draws a filled triangle with the vertices (x1, y1), (x2, y2), (x3, y3)
void Primitive_DrawFilledTriangle(SDL_Renderer *renderer, int x1, int y1, int x2, int y2,                         
                                  int x3, int y3, Primitive_Color color)
{
    int delta_x1 = (y2 - y1 > 0) ? (x2 - x1) / (y2 - y1) : 0; 
    int delta_x2 = (y3 - y1 > 0) ? (x3 - x1) / (y3 - y1) : 0; 
    int delta_x3 = (y3 - y2 > 0) ? (x3 - x2) / (y3 - y2) : 0; 

    int sx = x1; 
    int ex = x1; 
    int sy = y1; 
    int ey = y1; 
    
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 

    // NOTE: The orienatation of the points can change the production of the triangle
    //       Might want to order the point before going through the algorithem
    //       Maybe have to switch to a different algorithm altogether
    if (delta_x1 > delta_x2)
    {
        for (;sy <= y2; ++sy, ++ey, sx += delta_x2, ex += delta_x1)
        {
            SDL_RenderDrawLine(renderer, sx, sy, ex, sy);
        }

        ex = x2; 
        ey = y2;

        for (;sy <= y3; ++sy, ++ey, sx += delta_x2, ex += delta_x3)
        {
            SDL_RenderDrawLine(renderer, sx, sy, ex, sy);
        }
    }
    else 
    {
        for (;sy <= y2; ++sy, ++ey, sx += delta_x1, ex += delta_x2)
        {
            SDL_RenderDrawLine(renderer, sx, sy, ex, sy);
        }

        sx = x2; 
        sy = y2;

        for (;sy <= y3; ++sy, ++ey, sx += delta_x1, ex += delta_x2)
        {
            SDL_RenderDrawLine(renderer, sx, sy, ex, sy);
        }
    }
}
