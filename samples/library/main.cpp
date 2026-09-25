#include <stdio.h>
#include <string.h>
#include <sstream>

#include "../../_common/graphics.h"
#include "../../_common/log.h"

#define FRAME_WIDTH  1920
#define FRAME_HEIGHT 1080
#define FRAME_DEPTH  4

#define FONT_SIZE 64

std::stringstream debugLogStream;

Color bgColor = { 18, 18, 24 };
Color whiteColor = { 255, 255, 255 };
Color selectedColor = { 40, 100, 180 };
Color cardColor = { 30, 30, 40 };

FT_Face font;

int frameID = 0;

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);

    Scene2D* scene =
        new Scene2D(
            FRAME_WIDTH,
            FRAME_HEIGHT,
            FRAME_DEPTH
        );

    if (!scene->Init(0xC000000, 2))
    {
        DEBUGLOG << "Scene initialization failed";
        for (;;);
    }

    const char* fontPath =
        "/app0/assets/fonts/Gontserrat-Regular.ttf";

    if (!scene->InitFont(
        &font,
        fontPath,
        FONT_SIZE))
    {
        DEBUGLOG << "Font initialization failed";
        for (;;);
    }

    for (;;)
    {
        scene->FrameBufferFill(bgColor);

        /*
         * Header
         */
        Color header = { 12, 12, 18 };

        scene->DrawRectangle(
            0,
            0,
            FRAME_WIDTH,
            170,
            header
        );

        char title[] =
            "PISSCOU PS4 APP STORE";

        scene->DrawText(
            title,
            font,
            120,
            110,
            header,
            whiteColor
        );

        /*
         * Application card
         */
        scene->DrawRectangle(
            100,
            250,
            1720,
            430,
            cardColor
        );

        scene->DrawRectangle(
            100,
            250,
            1720,
            12,
            selectedColor
        );

        char appName[] =
            "FPKGi";

        scene->DrawText(
            appName,
            font,
            180,
            390,
            cardColor,
            whiteColor
        );

        char description[] =
            "PS4 Homebrew Application";

        scene->DrawText(
            description,
            font,
            180,
            500,
            cardColor,
            whiteColor
        );

        /*
         * Button
         */
        scene->DrawRectangle(
            180,
            560,
            420,
            80,
            selectedColor
        );

        char button[] =
            "OPEN";

        scene->DrawText(
            button,
            font,
            300,
            615,
            selectedColor,
            whiteColor
        );

        /*
         * Footer
         */
        char footer[] =
            "PISSCOU APP LIBRARY  |  v1.00";

        scene->DrawText(
            footer,
            font,
            120,
            980,
            bgColor,
            whiteColor
        );

        scene->SubmitFlip(frameID);
        scene->FrameWait(frameID);
        scene->FrameBufferSwap();

        frameID++;
    }

    return 0;
}
