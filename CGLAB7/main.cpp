#include <cmath>
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "camera.h"

// Constaints
bool isPlaying = true;
bool isCameraLightOn = true;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

void EnableOpenGL(HWND hwnd, HDC *, HGLRC *);

void DisableOpenGL(HWND, HDC, HGLRC);

void WndResize(int x, int y);

void Init_Light();

void Init_Material();

void MoveCamera();

void DrawSpinningTriangle(float theta);

void DrawFloor(float width, float length, float tileSize);

void DrawAxes(int windowWidth, int windowHeight);

void DrawChessBoard(float startX, float startY, int n = 8);

void Draw_LightPyramid();

void Draw_Cube();

void Draw_Bulb(GLfloat bulb_color[] = nullptr, GLfloat bulb_width = 2.0f, GLfloat bulb_height = 2.0f,
               GLfloat bulb_position[] = nullptr);

void Draw_Prism(int num_sides, float bottom_radius, float top_radius, float height, float alpha);

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
                          "CGLAB7",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          1600,
                          900,
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    Init_Light();
    Init_Material();

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
            glClearColor((float) 255.f / 255.f, (float) 254.f / 255.f, (float) 200.f / 255.f, 1.0f);
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
            DrawFloor(200, 200, 2);
            glPopMatrix();

            // Draw the triangle
            glPushMatrix();
            DrawSpinningTriangle(theta);
            glPopMatrix();

            // Draw the axes
            glPushMatrix();
            DrawAxes(windowWidth, windowHeight);
            glPopMatrix();

            for (int i = 0; i < 10; ++i) {
                glPushMatrix();
                glTranslatef(i * 3.0f, 0.0f, 1.0f);  // В ряд по X, чуть выше пола
                float alpha = i * 0.1f;  // Градация от 0.0 до 0.9
                Draw_Prism(6, 1.0f, 1.0f, 2.0f, alpha);  // 6 сторон, тип I (радиусы равны), высота 2
                glPopMatrix();
            }

            // Outer matrix
            glPushMatrix();
            float radius = 14.0f;
            float bulb_x = radius * cos(theta * M_PI / 180);
            float bulb_y = radius * sin(theta * M_PI / 180);
            glTranslatef(2.0f + bulb_x, 2.0f + bulb_y, 12.0f);
            // Inner matrix
            glPushMatrix();
            float angle = atan2(bulb_y, bulb_x) * 180 / M_PI + 90;
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
            glRotatef(50, 1.0f, 0.0f, 0.0f);
            Draw_Bulb(new GLfloat[]{1.f, .5f, .5f, .5f}, (GLfloat)3.f, (GLfloat)3.f);
            glPopMatrix();
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
                    break;
                case 'T': {
                    isCameraLightOn = !isCameraLightOn;
                    if (isCameraLightOn) {
                        glEnable(GL_LIGHT0);
                    } else {
                        glDisable(GL_LIGHT0);
                    }
                    break;
                }
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

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

void WndResize(int width, int height)
{
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MoveCamera() {
    int forward = 0, right = 0, vertical = 0;
    float speed = 0.2f;

    if (GetAsyncKeyState('W') & 0x8000) forward = 1;
    if (GetAsyncKeyState('S') & 0x8000) forward = -1;
    if (GetAsyncKeyState('A') & 0x8000) right = -1;
    if (GetAsyncKeyState('D') & 0x8000) right = 1;
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) vertical = 1;
    if (GetAsyncKeyState(VK_CONTROL) & 0x8000) vertical = -1;

    Camera_MoveDirectional(forward, right, speed);
    Camera_MoveUpDown(vertical, speed);

    RECT rect;
    GetClientRect(GetForegroundWindow(), &rect);
    Camera_AutoMoveByMouse(rect.right / 2, rect.bottom / 2);
}

void DrawSpinningTriangle(float theta) {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
    glPopMatrix();
}

void DrawAxes(int windowWidth, int windowHeight) {
    glLineWidth(3.0f);

    glBegin(GL_LINES);
    // X-axis (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    // Y-axis (green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    // Z-axis (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
}

void DrawChessBoard(float startX, float startY, int n) {
    float tileSize = 1.0f; // Size of each tile

    float normal_vert[] = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, &normal_vert);

    // Draw the chessboard pattern
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Alternate between black and white tiles
            if ((i + j) % 2 == 0) {
                glColor3f(1.0f, 1.0f, 1.0f); // White
            } else {
                glColor3f(0.0f, 0.0f, 0.0f); // Black
            }

            float x = startX + j * tileSize;
            float y = startY + i * tileSize;

            // Draw the current tile as a quadrilateral
            glBegin(GL_QUADS);
            glVertex3f(x, 0.0f, y);
            glVertex3f(x + tileSize, 0.0f, y);
            glVertex3f(x + tileSize, 0.0f, y + tileSize);
            glVertex3f(x, 0.0f, y + tileSize);
            glEnd();
        }
    }

    glDisable(GL_NORMAL_ARRAY);
}

void DrawFloor(float width, float length, float tileSize) {
    // Define the vertices of the floor
    float minX = -width / 2.0f; // Calculate minimum x-coordinate
    float minY = -length / 2.0f; // Calculate minimum y-coordinate
    float maxX = width / 2.0f; // Calculate maximum x-coordinate
    float maxY = length / 2.0f; // Calculate maximum y-coordinate

    float normal_vert[] = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, &normal_vert);

    // Draw the floor as a quadrilateral lying on the x-y plane
    glBegin(GL_QUADS);
    glColor3d(204 / 255.f, 204 / 255.f, 204 / 255.f); // Light gray color

    // Draw the chessboard pattern directly on the floor
    bool isLight = true;

    for (float x = minX; x < maxX; x += tileSize) {
        isLight = !isLight; // Toggle between light and dark rows
        for (float y = minY; y < maxY; y += tileSize) {
            if (isLight) {
                // Light color for even tiles
                glColor3f(0.8f, 0.8f, 0.8f); // Light gray
            } else {
                // Dark color for odd tiles
                glColor3f(0.2f, 0.2f, 0.2f); // Dark gray
            }

            // Draw the current tile as a quadrilateral
            glVertex3f(x, y, 0.0f);
            glVertex3f(x + tileSize, y, 0.0f);
            glVertex3f(x + tileSize, y + tileSize, 0.0f);
            glVertex3f(x, y + tileSize, 0.0f);

            isLight = !isLight; // Toggle between light and dark tiles for next column
        }
    }

    glEnd();

    glDisable(GL_NORMAL_ARRAY);
}

void Init_Light() {
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f}; // Torch position (initialized at the camera)
    GLfloat light_direction[] = {0.0f, 0.0f, -1.0f}; // Torch direction (same as camera direction)
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 16.0f);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0f);
    glEnable(GL_LIGHT0);
}

void Init_Material() {
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    GLfloat material_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat material_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat material_shininess[] = { 100.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
}

void Draw_Cube() {
    // Dimensions (0.5 to half a size)
    const GLfloat vertices[] = {
        -1.0, -1.0, 1.0, // A
        1.0, -1.0, 1.0, // B
        1.0, 1.0, 1.0, // D
        -1.0, 1.0, 1.0, // C

        -1.0, -1.0, -1.0, // E
        1.0, -1.0, -1.0, // F
        1.0, 1.0, -1.0, // H
        -1.0, 1.0, -1.0, // G
    };

    const GLuint indices[] = {
        0, 1, 2, // Front face (ABC)
        2, 3, 0, // Front face (CDA)

        1, 5, 6, // Right face (BFH)
        6, 2, 1, // Right face (HCD)

        7, 6, 5, // Back face (GHF)
        5, 4, 7, // Back face (FEG)

        4, 0, 3, // Left face (EAD)
        3, 7, 4, // Left face (DGE)

        3, 2, 6, // Top face (DCH)
        6, 7, 3, // Top face (HGD)

        4, 5, 1, // Bottom face (EFB)
        1, 0, 4 // Bottom face (BAE)
    };

    const GLfloat normals[] = {
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glColor3f(.8f, .8f, .8f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, &normals); // Provide normals to OpenGL

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_CULL_FACE);
}

void Draw_Bulb(GLfloat bulb_color[], GLfloat bulb_width, GLfloat bulb_height, GLfloat bulb_position[]) {
    // Set default color if not provided
    GLfloat default_color[] = {1.0f, 1.0f, 0.0f}; // Yellow color
    if (bulb_color == nullptr) {
        bulb_color = default_color;
    }

    // Set default position if not provided
    GLfloat default_position[] = {0.0f, 0.0f, 0.0f};
    if (bulb_position == nullptr) {
        bulb_position = default_position;
    }

    // Set the color of the bulb with intensity
    GLfloat intensity = 2.f;
    GLfloat bulb_color_with_intensity[3]; // Array to store color with intensity
    for (int i = 0; i < 3; ++i) {
        bulb_color_with_intensity[i] = bulb_color[i] * intensity;
    }

    // Set the position of the bulb light source
    GLfloat light_position[] = {bulb_position[0], bulb_position[1], bulb_position[2], 1.0f};
    // Set as a positional light

    // Set up the light properties
    glEnable(GL_LIGHT1); // Enable the additional light source
    glLightfv(GL_LIGHT1, GL_DIFFUSE, bulb_color_with_intensity); // Make illumination color to bulb_color
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);

    // Set up the light direction
    GLfloat light_direction[] = {0.0f, 0.0f, -1.0f}; // Pointing towards the cube
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 128.0f); // Adjusted exponent for smoother illumination

    // Set up the light cutoff angle
    GLfloat light_cutoff = 15.0f;
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light_cutoff);

    // Draw the bulb as a simple rectangle
    glColor3fv(bulb_color_with_intensity);
    glPushMatrix();
    glTranslatef(bulb_position[0], bulb_position[1], bulb_position[2]);
    glBegin(GL_QUADS);
    glVertex3f(-bulb_width / 2, -bulb_height / 2, 0.0f);
    glVertex3f(bulb_width / 2, -bulb_height / 2, 0.0f);
    glVertex3f(bulb_width / 2, bulb_height / 2, 0.0f);
    glVertex3f(-bulb_width / 2, bulb_height / 2, 0.0f);
    glEnd();
    glPopMatrix();
}

void Draw_Prism(int num_sides, float bottom_radius, float top_radius, float height, float alpha) {
    GLfloat mat_ambient[] = {0.2f, 0.2f, 0.2f, alpha};
    GLfloat mat_diffuse[] = {0.0f, 0.0f, 1.0f, alpha};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, alpha};
    GLfloat mat_shininess[] = {50.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    float angle_step = 2 * M_PI / num_sides;

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    for (int i = num_sides - 1; i >= 0; --i) {
        float angle = i * angle_step;
        glVertex3f(bottom_radius * cos(angle), bottom_radius * sin(angle), 0.0f);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    for (int i = 0; i < num_sides; ++i) {
        float angle = i * angle_step;
        glVertex3f(top_radius * cos(angle), top_radius * sin(angle), height);
    }
    glEnd();

    for (int i = 0; i < num_sides; ++i) {
        float angle1 = i * angle_step;
        float angle2 = (i + 1) * angle_step;

        float bx1 = bottom_radius * cos(angle1);
        float by1 = bottom_radius * sin(angle1);
        float bx2 = bottom_radius * cos(angle2);
        float by2 = bottom_radius * sin(angle2);

        float tx1 = top_radius * cos(angle1);
        float ty1 = top_radius * sin(angle1);
        float tx2 = top_radius * cos(angle2);
        float ty2 = top_radius * sin(angle2);

        float nx1 = cos(angle1);
        float ny1 = sin(angle1);
        float nx2 = cos(angle2);
        float ny2 = sin(angle2);

        glBegin(GL_QUADS);
        glNormal3f(nx1, ny1, 0.0f);
        glVertex3f(bx1, by1, 0.0f);
        glNormal3f(nx2, ny2, 0.0f);
        glVertex3f(bx2, by2, 0.0f);
        glNormal3f(nx2, ny2, 0.0f);
        glVertex3f(tx2, ty2, height);
        glNormal3f(nx1, ny1, 0.0f);
        glVertex3f(tx1, ty1, height);
        glEnd();
    }
}
