#include <cmath>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "camera.h"

bool isPlaying = true;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

void EnableOpenGL(HWND hwnd, HDC *, HGLRC *);

void DisableOpenGL(HWND, HDC, HGLRC);

void WndResize(int x, int y);

void MoveCamera();

void DrawSpinningTriangle(float theta);

void DrawFloor(float width, float length);

void DrawAxes(int windowWidth, int windowHeight);

void DrawChessBoard(float startX, float startY, int n = 8);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow) {
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "ComputerGraphic";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "ComputerGraphic",
                          "CGLAB5",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          800,
                          600,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);


    ShowWindow(hwnd, nCmdShow);
    ShowCursor(FALSE);

    RECT windowRect;
    GetClientRect(hwnd, &windowRect);
    int windowWidth = windowRect.right - windowRect.left;
    int windowHeight = windowRect.bottom - windowRect.top;

    WndResize(windowRect.right, windowRect.bottom);


    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit) {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT) {
                bQuit = TRUE;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
            // if (isPlaying) {
            // if (isPlaying) ShowCursor(FALSE);
            // else ShowCursor(TRUE);
                // Enable OpenGL states and clear buffers
                glClearColor((float)255.f/255.f, (float)254.f/255.f, (float)200.f/255.f, 1.0f); // Set background to nice slight yellow :) (255, 254, 200 rgb)
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                if (isPlaying && GetForegroundWindow() == hwnd) {
                    MoveCamera();
                }

                // Set up projection matrix
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(45.0f, (float) windowWidth / (float) windowHeight, 0.1f, 100.0f);

                // Set up modelview matrix
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                // Move the camera
                Camera_Apply();

                // Draw the floor
                glPushMatrix();
                DrawFloor(200, 200);
                glPopMatrix();

                // Draw the triangle
                glPushMatrix();
                DrawSpinningTriangle(theta);
                glPopMatrix();

                // Draw the axes
                glPushMatrix();
                DrawAxes(windowWidth, windowHeight);
                glPopMatrix();

                // Render chess board
                glPushMatrix();
                DrawChessBoard(5.0f, 3.0f, 7); // Draw the chessboard starting from coordinates (5, 3)
                glPopMatrix();


                // Check for OpenGL errors
                GLenum error = glGetError();
                if (error != GL_NO_ERROR) {
                    fprintf(stderr, "OpenGL error: %d\n", error);
                }

                // Swap buffers and update rotation
                SwapBuffers(hDC);
                theta += 1.0f;
                Sleep(1);
        }
    }


    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
            switch (wParam) {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    // isPlaying = !isPlaying;
                    break;
            }
            break;

        case WM_SIZE:
            WndResize(LOWORD(lParam), HIWORD(lParam));
            break;


        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC *hDC, HGLRC *hRC) {
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC) {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

void MoveCamera() {
    Camera_MoveDirectional(
        GetKeyState('W') < 0 ? 1 : GetKeyState('S') < 0 ? -1 : 0,
        GetKeyState('D') < 0 ? 1 : GetKeyState('A') < 0 ? -1 : 0,
        0.1);
    Camera_AutoMoveByMouse(400, 400, 0.1);
}

void WndResize(int x, int y) {
    glViewport(0, 0, x, y); // Resize the viewport to match the new window size

    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix
    glLoadIdentity(); // Reset the projection matrix

    float aspectRatio = (float) x / (float) y; // Calculate the new aspect ratio

    // Set up a perspective projection matrix
    gluPerspective(45.0f, aspectRatio, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW); // Switch back to the modelview matrix
}

void DrawSpinningTriangle(float theta) {
    // Apply rotation to the entire scene
    glRotatef(theta, 0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.87f, -0.5f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.87f, -0.5f, 0.0f);
    glEnd();
}

void DrawAxes(int windowWidth, int windowHeight) {
    // Define axis length and padding
    float axisLength = 0.1f * std::min(windowWidth, windowHeight); // Length of each axis line
    float padding = 50.0f; // Padding from the edges of the window

    // Get camera rotation angles
    float camXRot = camera.Xrot;
    float camZRot = camera.Zrot;

    // Calculate the rotation lines' end points
    float xAxisEndX = padding + axisLength * cos(camZRot * M_PI / 180.0f);
    float xAxisEndY = padding + axisLength * sin(camZRot * M_PI / 180.0f);
    float yAxisEndX = padding - axisLength * sin(camZRot * M_PI / 180.0f);
    float yAxisEndY = padding + axisLength * cos(camZRot * M_PI / 180.0f);
    float zAxisEndX = padding + axisLength * cos(camXRot * M_PI / 180.0f);
    float zAxisEndY = padding + axisLength * sin(camXRot * M_PI / 180.0f);

    // Clear the depth buffer to ensure the axes are drawn in front of everything else
    glClear(GL_DEPTH_BUFFER_BIT);

    // Set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);

    // Set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw X-axis (red)
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_LINES);
    glVertex2f(padding, padding);
    glVertex2f(xAxisEndX, xAxisEndY);
    glEnd();

    // Draw Y-axis (green)
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glBegin(GL_LINES);
    glVertex2f(padding, padding);
    glVertex2f(yAxisEndX, yAxisEndY);
    glEnd();

    // Draw Z-axis (blue)
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glBegin(GL_LINES);
    glVertex2f(padding, padding);
    glVertex2f(zAxisEndX, zAxisEndY);
    glEnd();

    // Restore the projection matrix
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);

    // Restore the modelview matrix
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void DrawChessBoard(float startX, float startY, int n) {
    float tileSize = 1.0f; // Size of each tile in the chessboard

    // Rows
    for (int i = 0; i < n; ++i) {
        // Columns
        for (int j = 0; j < n; ++j) {
            if ((i + j) % 2 == 0) {
                // Light color for even indices
                glColor3f(0.8f, 0.8f, 0.8f); // Light gray
            } else {
                // Dark color for odd indices
                glColor3f(0.2f, 0.2f, 0.2f); // Dark gray
            }

            // Calculate the position of the current tile
            float x = startX + j * tileSize;
            float y = startY + i * tileSize;

            // Print the coordinates of the current tile
            // std::cout << "Tile at (" << x << ", 0, " << y << ")" << std::endl;

            // Draw the current tile as a quadrilateral
            glBegin(GL_QUADS);
            glVertex3f(x, 0.0f, y);
            glVertex3f(x + tileSize, 0.0f, y);
            glVertex3f(x + tileSize, 0.0f, y + tileSize);
            glVertex3f(x, 0.0f, y + tileSize);
            glEnd();
        }
    }
}

void DrawFloor(float width, float length) {
    glColor3d(204/255.f, 204/255.f, 204/255.f);

    // Define the vertices of the floor
    float minX = -width / 2.0f; // Calculate minimum x-coordinate
    float minY = -length / 2.0f; // Calculate minimum y-coordinate
    float maxX = width / 2.0f; // Calculate maximum x-coordinate
    float maxY = length / 2.0f; // Calculate maximum y-coordinate

    // Draw the floor as a quadrilateral lying on the x-y plane
    glBegin(GL_QUADS);
    glVertex3f(minX, minY, 0.0f);
    glVertex3f(maxX, minY, 0.0f);
    glVertex3f(maxX, maxY, 0.0f);
    glVertex3f(minX, maxY, 0.0f);
    glEnd();
}





