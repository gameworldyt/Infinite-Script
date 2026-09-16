#pragma once

#include <windows.h>
#include <memory>
#include <string>
#include <vector>

#include "../../Language/Parser/AST.h"

class UIRuntime
{
public:
    UIRuntime();
    ~UIRuntime();

    bool show(const AST& root);

private:
    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam);

    bool createWindow(
        const AST& windowNode);

    void collectElements(
        const AST& node);

    void drawInterface(
        HDC hdc);

    void drawText(
        HDC hdc,
        const std::string& text,
        int x,
        int y,
        int width,
        int height,
        int fontSize,
        COLORREF color,
        bool bold,
        UINT alignment);

    void drawButton(
        HDC hdc);

    void handleClick(
        int mouseX,
        int mouseY);

    std::string removeQuotes(
        std::string value);

    AST findUI(
        const AST& node);

    AST findWindow(
        const AST& node);

    HWND mainWindow = nullptr;
    HINSTANCE instance = nullptr;

    std::string windowTitle =
        "InfiniteScript";

    std::string heroTitle =
        "One language. Infinite possibilities.";

    std::string heroDescription =
        "Build applications, interfaces, animations and more with InfiniteScript.";

    std::string buttonText =
        "Get Started";

    bool buttonHovered = false;

    int buttonX = 0;
    int buttonY = 0;
    int buttonWidth = 190;
    int buttonHeight = 52;
};
