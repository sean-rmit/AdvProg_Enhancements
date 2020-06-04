#include "painter.h"

Painter::Painter()
{
}

Painter::~Painter()
{
}

std::string Painter::paintTile(char tile)
{
    std::string paintedTile = "";
    if (tile == RED)
    {
        paintedTile += RED_TEXT;
        paintedTile += tile;
    }
    else if (tile == YELLOW)
    {
        paintedTile += YELLOW_TEXT;
        paintedTile += tile;
    }
    else if (tile == DARKBLUE)
    {
        paintedTile += DARKBLUE_TEXT;
        paintedTile += tile;
    }
    else if (tile == LIGHTBLUE)
    {
        paintedTile += LIGHTBLUE_TEXT;
        paintedTile += tile;
    }

    else if (tile == BLACK)
    {
        paintedTile += BLACK_TEXT;
        paintedTile += tile;
    }
    else if (tile == ORANGE)
    {
        paintedTile += ORANGE_TEXT;
        paintedTile += tile;
    }
    else if (tile == FIRSTPLAYER)
    {
        paintedTile += GREEN_TEXT;
        paintedTile += tile;
    }
    paintedTile += RESET;
    return paintedTile;
}

std::string Painter::paintWallTile(char actualTile, char templateTile)
{
    std::string paintedTile = "";
    std::string actualTileAsString = "";
    if (actualTile == NOTILE)
    {
        actualTileAsString += " ";
    }

    else
    {
        actualTileAsString += actualTile;
    }
    if (templateTile == RED)
    {
        if (actualTile == NOTILE)
        {
            paintedTile += RED_BACKGROUND;
        }
        else
        {
            paintedTile += RED_TEXT;
        }
        paintedTile += actualTileAsString;
    }
    else if (templateTile == YELLOW)
    {
        if (actualTile == NOTILE)
        {
            paintedTile += YELLOW_BACKGROUND;
        }
        else
        {
            paintedTile += YELLOW_TEXT;
        }
        paintedTile += actualTileAsString;
    }
    else if (templateTile == DARKBLUE)
    {
        if (actualTile == NOTILE)
        {
            paintedTile += DARKBLUE_BACKGROUND;
        }
        else
        {
            paintedTile += DARKBLUE_TEXT;
        }
        paintedTile += actualTileAsString;
    }
    else if (templateTile == LIGHTBLUE)
    {
        if (actualTile == NOTILE)
        {
            paintedTile += LIGHTBLUE_BACKGROUND;
        }
        else
        {
            paintedTile += LIGHTBLUE_TEXT;
        }
        paintedTile += actualTileAsString;
    }
    else if (templateTile == BLACK)
    {
        if (actualTile == NOTILE)
        {
            paintedTile += BLACK_BACKGROUND;
        }
        else
        {
            paintedTile += BLACK_TEXT;
        }
        paintedTile += actualTileAsString;
    }
    else if (templateTile == ORANGE)
    {
        if (actualTile == NOTILE)
        {
            paintedTile += ORANGE_BACKGROUND;
        }
        else
        {
            paintedTile += ORANGE_TEXT;
        }
        paintedTile += actualTileAsString;
    }
    paintedTile += RESET;
    return paintedTile;
}

std::string Painter::paintString(std::string text, std::string colour)
{
    std::string paintedTile = "";
    if (colour == "red")
    {
        paintedTile += RED_TEXT;
        paintedTile += text;
    }
    else if (colour == "yellow")
    {
        paintedTile += YELLOW_TEXT;
        paintedTile += text;
    }
    else if (colour == "darkblue")
    {
        paintedTile += DARKBLUE_TEXT;
        paintedTile += text;
    }
    else if (colour == "lightblue")
    {
        paintedTile += LIGHTBLUE_TEXT;
        paintedTile += text;
    }
    else if (colour == "black")
    {
        paintedTile += BLACK_TEXT;
        paintedTile += text;
    }
    else if (colour == "orange")
    {
        paintedTile += BOLD_TEXT;
        paintedTile += ORANGE_TEXT;
        paintedTile += text;
    }
    paintedTile += RESET;
    return paintedTile;
}
