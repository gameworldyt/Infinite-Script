#include "UIRuntime.h"

#include <windows.h>
#include <windowsx.h>

#include <string>
#include <iostream>

UIRuntime::UIRuntime()
{
    instance =
        GetModuleHandleA(nullptr);
}

UIRuntime::~UIRuntime()
{
}

std::string UIRuntime::removeQuotes(
    std::string value)
{
    if (value.size() >= 2 &&
        value.front() == '"' &&
        value.back() == '"')
    {
        return value.substr(
            1,
            value.size() - 2);
    }

    return value;
}

AST UIRuntime::findUI(
    const AST& node)
{
    if (!node)
        return nullptr;

    if (node->type == NodeType::UI)
        return node;

    for (const auto& child :
         node->children)
    {
        AST result =
            findUI(child);

        if (result)
            return result;
    }

    return nullptr;
}

AST UIRuntime::findWindow(
    const AST& node)
{
    if (!node)
        return nullptr;

    if (node->type == NodeType::UIWindow)
        return node;

    for (const auto& child :
         node->children)
    {
        AST result =
            findWindow(child);

        if (result)
            return result;
    }

    return nullptr;
}

bool UIRuntime::show(
    const AST& root)
{
    AST uiNode =
        findUI(root);

    if (!uiNode)
    {
        std::cerr
            << "Error [INF1403]\n"
            << "No UI node found.\n";

        return false;
    }

    AST windowNode =
        findWindow(uiNode);

    if (!windowNode)
    {
        std::cerr
            << "Error [INF1404]\n"
            << "No Window found inside UI.\n";

        return false;
    }

    if (!createWindow(windowNode))
        return false;

    MSG message{};

    while (true)
    {
        BOOL result =
            GetMessageA(
                &message,
                nullptr,
                0,
                0);

        if (result == -1)
            return false;

        if (result == 0)
            break;

        TranslateMessage(&message);
        DispatchMessageA(&message);
    }

    return true;
}

void UIRuntime::collectElements(
    const AST& node)
{
    if (!node)
        return;

    if (node->type == NodeType::UITitle)
    {
        if (!node->children.empty())
        {
            AST value =
                node->children[0];

            if (value &&
                value->type == NodeType::Literal)
            {
                windowTitle =
                    removeQuotes(
                        value->value);
            }
        }
    }

    if (node->type == NodeType::UIText)
    {
        if (!node->children.empty())
        {
            AST value =
                node->children[0];

            if (value &&
                value->type == NodeType::Literal)
            {
                std::string text =
                    removeQuotes(
                        value->value);

                if (text.find(
                        "One language") !=
                    std::string::npos)
                {
                    heroTitle = text;
                }
                else if (text.find(
                             "Build applications") !=
                         std::string::npos)
                {
                    heroDescription = text;
                }
            }
        }
    }

    if (node->type == NodeType::UIButton)
    {
        for (const auto& child :
             node->children)
        {
            if (!child)
                continue;

            if (child->type ==
                NodeType::UIText &&
                !child->children.empty())
            {
                AST value =
                    child->children[0];

                if (value &&
                    value->type ==
                        NodeType::Literal)
                {
                    buttonText =
                        removeQuotes(
                            value->value);
                }
            }
        }
    }

    for (const auto& child :
         node->children)
    {
        collectElements(child);
    }
}

bool UIRuntime::createWindow(
    const AST& windowNode)
{
    collectElements(windowNode);

    const char* className =
        "InfiniteScriptNativeWindowV2";

    WNDCLASSA windowClass{};

    windowClass.style =
        CS_HREDRAW | CS_VREDRAW;

    windowClass.lpfnWndProc =
        &UIRuntime::WindowProc;

    windowClass.hInstance =
        instance;

    windowClass.hCursor =
        LoadCursorA(
            nullptr,
            IDC_ARROW);

    windowClass.hbrBackground =
        nullptr;

    windowClass.lpszClassName =
        className;

    ATOM registered =
        RegisterClassA(
            &windowClass);

    if (registered == 0)
    {
        DWORD error =
            GetLastError();

        if (error !=
            ERROR_CLASS_ALREADY_EXISTS)
        {
            std::cerr
                << "Error [INF1401]\n"
                << "Could not register native UI class.\n"
                << "Windows error: "
                << error
                << '\n';

            return false;
        }
    }

    mainWindow =
        CreateWindowExA(
            0,
            className,
            windowTitle.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            1000,
            650,
            nullptr,
            nullptr,
            instance,
            this);

    if (!mainWindow)
    {
        std::cerr
            << "Error [INF1402]\n"
            << "Could not create native UI window.\n"
            << "Windows error: "
            << GetLastError()
            << '\n';

        return false;
    }

    ShowWindow(
        mainWindow,
        SW_SHOW);

    UpdateWindow(
        mainWindow);

    return true;
}

void UIRuntime::drawText(
    HDC hdc,
    const std::string& text,
    int x,
    int y,
    int width,
    int height,
    int fontSize,
    COLORREF color,
    bool bold,
    UINT alignment)
{
    HFONT font =
        CreateFontA(
            -fontSize,
            0,
            0,
            0,
            bold ? FW_BOLD : FW_NORMAL,
            FALSE,
            FALSE,
            FALSE,
            DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE,
            "Segoe UI");

    HFONT oldFont =
        static_cast<HFONT>(
            SelectObject(hdc, font));

    SetTextColor(
        hdc,
        color);

    SetBkMode(
        hdc,
        TRANSPARENT);

    RECT rect{
        x,
        y,
        x + width,
        y + height
    };

    DrawTextA(
        hdc,
        text.c_str(),
        -1,
        &rect,
        alignment |
        DT_WORDBREAK |
        DT_NOPREFIX);

    SelectObject(
        hdc,
        oldFont);

    DeleteObject(font);
}

void UIRuntime::drawButton(
    HDC hdc)
{
    RECT rect{
        buttonX,
        buttonY,
        buttonX + buttonWidth,
        buttonY + buttonHeight
    };

    HBRUSH brush =
        CreateSolidBrush(
            buttonHovered
                ? RGB(96, 165, 250)
                : RGB(59, 130, 246));

    HPEN pen =
        CreatePen(
            PS_NULL,
            0,
            RGB(0, 0, 0));

    HBRUSH oldBrush =
        static_cast<HBRUSH>(
            SelectObject(hdc, brush));

    HPEN oldPen =
        static_cast<HPEN>(
            SelectObject(hdc, pen));

    RoundRect(
        hdc,
        rect.left,
        rect.top,
        rect.right,
        rect.bottom,
        18,
        18);

    SelectObject(
        hdc,
        oldBrush);

    SelectObject(
        hdc,
        oldPen);

    DeleteObject(brush);
    DeleteObject(pen);

    drawText(
        hdc,
        buttonText,
        buttonX,
        buttonY + 13,
        buttonWidth,
        30,
        17,
        RGB(255, 255, 255),
        true,
        DT_CENTER);
}

void UIRuntime::drawInterface(
    HDC hdc)
{
    RECT clientRect{};

    GetClientRect(
        mainWindow,
        &clientRect);

    int width =
        clientRect.right -
        clientRect.left;

    int height =
        clientRect.bottom -
        clientRect.top;

    HBRUSH background =
        CreateSolidBrush(
            RGB(15, 23, 42));

    FillRect(
        hdc,
        &clientRect,
        background);

    DeleteObject(background);

    int centreX =
        width / 2;

    drawText(
        hdc,
        "INFINITESCRIPT",
        centreX - 300,
        95,
        600,
        35,
        16,
        RGB(96, 165, 250),
        true,
        DT_CENTER);

    drawText(
        hdc,
        heroTitle,
        centreX - 430,
        155,
        860,
        110,
        42,
        RGB(255, 255, 255),
        true,
        DT_CENTER);

    drawText(
        hdc,
        heroDescription,
        centreX - 350,
        290,
        700,
        80,
        18,
        RGB(203, 213, 225),
        false,
        DT_CENTER);

    buttonX =
        centreX -
        buttonWidth / 2;

    buttonY =
        height / 2 +
        55;

    drawButton(hdc);
}

void UIRuntime::handleClick(
    int mouseX,
    int mouseY)
{
    if (mouseX >= buttonX &&
        mouseX <= buttonX + buttonWidth &&
        mouseY >= buttonY &&
        mouseY <= buttonY + buttonHeight)
    {
        MessageBoxA(
            mainWindow,
            "Welcome to InfiniteScript!",
            "InfiniteScript",
            MB_OK |
            MB_ICONINFORMATION);
    }
}

LRESULT CALLBACK UIRuntime::WindowProc(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    UIRuntime* runtime =
        reinterpret_cast<UIRuntime*>(
            GetWindowLongPtrA(
                hwnd,
                GWLP_USERDATA));

    if (message == WM_NCCREATE)
    {
        CREATESTRUCTA* createStruct =
            reinterpret_cast<CREATESTRUCTA*>(
                lParam);

        runtime =
            reinterpret_cast<UIRuntime*>(
                createStruct->lpCreateParams);

        SetWindowLongPtrA(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(
                runtime));
    }

    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT paint{};

        HDC hdc =
            BeginPaint(
                hwnd,
                &paint);

        if (runtime)
            runtime->drawInterface(hdc);

        EndPaint(
            hwnd,
            &paint);

        return 0;
    }

    case WM_MOUSEMOVE:
    {
        if (!runtime)
            break;

        int mouseX =
            GET_X_LPARAM(lParam);

        int mouseY =
            GET_Y_LPARAM(lParam);

        bool hovering =
            mouseX >= runtime->buttonX &&
            mouseX <=
                runtime->buttonX +
                runtime->buttonWidth &&
            mouseY >= runtime->buttonY &&
            mouseY <=
                runtime->buttonY +
                runtime->buttonHeight;

        if (hovering !=
            runtime->buttonHovered)
        {
            runtime->buttonHovered =
                hovering;

            InvalidateRect(
                hwnd,
                nullptr,
                FALSE);
        }

        return 0;
    }

    case WM_LBUTTONDOWN:
    {
        if (runtime)
        {
            runtime->handleClick(
                GET_X_LPARAM(lParam),
                GET_Y_LPARAM(lParam));
        }

        return 0;
    }

    case WM_SIZE:

        if (runtime)
        {
            InvalidateRect(
                hwnd,
                nullptr,
                FALSE);
        }

        return 0;

    case WM_DESTROY:

        PostQuitMessage(0);

        return 0;
    }

    return DefWindowProcA(
        hwnd,
        message,
        wParam,
        lParam);
}

