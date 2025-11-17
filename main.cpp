#include <cmath>
#include <iostream>
#include <cstdio>
#include <functional>
#include <vector>
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

void DrawProjector();

void InitLight();

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

void DrawThirdPrism(float alpha);

void DrawSecondPrism(float alpha);

void DrawObjectsInCircle(float radius, int numObjects, const std::function<void(float)>& drawFunction);

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
                          "Lab 7",
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

    InitLight();
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
            // Enable OpenGL states and clear buffers
            glClearColor((float) 255.f / 255.f, (float) 254.f / 255.f, (float) 200.f / 255.f, 1.0f);
            // Set background to nice slight yellow :) (255, 254, 200 rgb)
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
            glTranslatef(0.f, 0.f, 0.1f);
            DrawSpinningTriangle(theta);
            glPopMatrix();

            // Draw the axes
            glPushMatrix();
            DrawAxes(windowWidth, windowHeight);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(2.f, 2.f, 2.f);
            Draw_Cube();
            glPopMatrix();


            // Bulb

            // Outer matrix
            glPushMatrix();

            DrawProjector();

            // Radius of rotation around the cube
            float radius = 14.0f;

            // // TODO: make theta instead of 0
            // Calculate the position of the bulb relative to the cube's center
            float bulb_x = radius * cos(theta * M_PI / 180); // Convert theta to radians
            float bulb_y = radius * sin(theta * M_PI / 180); // Convert theta to radians

            glTranslatef(2.0f + bulb_x, 2.0f + bulb_y, 12.0f);

            // Inner matrix
            glPushMatrix();

            // Angle between the x-axis and the line connecting the bulb to the center of the cube
            float bulbAngle = atan2(bulb_y, bulb_x) * 180 / M_PI + 90;

            // Rotate the bulb around its own axis
            glRotatef(bulbAngle, 0.0f, 0.0f, 1.0f);

            // Lean the bulb by 45 degrees around the X-axis
            glRotatef(50, 1.0f, 0.0f, 0.0f);

            // Color
            // GLfloat bulb_color[] = {1.f, 0.5f, 0.f}; // Orange color

            // Draw the bulb
            Draw_Bulb(new GLfloat[]{1.f, .5f, .5f, .5f}, (GLfloat) 3.f, (GLfloat) 3.f);

            // End Inner matrix
            glPopMatrix();

            // End Outer matrix
            glPopMatrix();

            //

            // 7
            glPushMatrix();
            glTranslatef(10.f, 10.f, 1.f);
            DrawObjectsInCircle(5.f, 10, [](float alpha) {
                            DrawThirdPrism(alpha);
                        });
            glPopMatrix();

            glPushMatrix();
            glTranslatef(25.f, 10.f, 1.f);
            glScalef(-1.f, 1.f, 1.f); // Mirror horizontally
            DrawObjectsInCircle(5.f, 10, [](float alpha) {
                DrawSecondPrism(alpha);
            });
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

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC) {
    glDepthMask(FALSE);
    glDisable(GL_DEPTH_TEST);

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

void MoveCamera() {
    Camera_MoveDirectional(
        GetKeyState('W') < 0
            ? 1
            : GetKeyState('S') < 0
                  ? -1
                  : 0,
        GetKeyState('D') < 0
            ? 1
            : GetKeyState('A') < 0
                  ? -1
                  : 0,
        0.1);
    Camera_MoveUpDown(
        GetKeyState(VK_SPACE) < 0
            ? 1
            : GetKeyState(VK_SHIFT) < 0
                  ? -1
                  : 0,
        0.1
    );
    Camera_AutoMoveByMouse(400, 400);
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

    float normal_vert[] = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, &normal_vert);


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

    glDisable(GL_NORMAL_ARRAY);
}

void DrawFloor(float width, float length, float tileSize) {
    // Define the vertices of the floor
    float minX = -width / 2.0f; // Calculate minimum x-coordinate
    float minY = -length / 2.0f; // Calculate minimum y-coordinate
    float maxX = width / 2.0f; // Calculate maximum x-coordinate
    float maxY = length / 2.0f; // Calculate maximum y-coordinate

    // TODO: why do i need that?..
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

// 6

void InitLight() {
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
}

void DrawProjector() {
    GLfloat light_ambient[] = {.5f, .5f, .5f, 1.0f};
    GLfloat light_diffuse[] = {.5f, .5f, .5f, 1.0f};
    GLfloat light_specular[] = {.5f, .5f, .5f, 1.0f};

    GLfloat light_position[] = {13.f, 10.0f, 15.0f, 1.0f};
    GLfloat light_direction[] = {0.0f, 0.0f, -1.0f}; // Pointing straight down
    GLfloat light_cutoff = 90.0f; // 10 and 15 are also good

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
    // Exponent for smoother illumination, set to ~5-10 for better perfomance
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0f);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light_cutoff);

    glEnable(GL_LIGHT0);
}

void Init_Material() {
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    GLfloat material_ambient[] = {0.2f, 0.2f, 0.2f, .5f};
    GLfloat material_diffuse[] = {1.0f, 1.0f, 1.0f, .5f};
    GLfloat material_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat material_shininess[] = {100.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

    // glColor3f(0.9f, 0.0f, 0.9f); // Лиловый цвет
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

// TODO: remove redundant comments
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
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 128.0f);
    // Adjusted exponent for smoother illumination, set to ~5-10 for better perfomance

    // Set up the light cutoff angle
    GLfloat light_cutoff = 15.0f; // 10 and 15 are also good
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

// 7
void DrawThirdPrism(float alpha) {
    const int numVerticesPerSection = 7;
    const int numSections = 3; // top, middle, bottom
    const GLfloat radius = 1.5f;
    const GLfloat height = 2.0f;

    // Allocate memory
    std::vector<GLfloat> vertices(numVerticesPerSection * numSections * 3);
    std::vector<GLuint> indices(numVerticesPerSection * (numSections - 1) * 3 * 2);
    std::vector<GLfloat> normals(numVerticesPerSection * numSections * 3);

    // Calculate vertices
    for (int i = 0; i < numSections; i++) {
        GLfloat z = i * height / (numSections - 1);
        GLfloat currentRadius = radius;

        // If middle, make its radius half a size
        if (i == 1) currentRadius *= 0.5;

        for (int j = 0; j < numVerticesPerSection; j++) {
            GLfloat angle = j * 2 * M_PI / numVerticesPerSection;
            GLfloat x = currentRadius * cos(angle);
            GLfloat y = currentRadius * sin(angle);
            vertices[(i * numVerticesPerSection + j) * 3 + 0] = x;
            vertices[(i * numVerticesPerSection + j) * 3 + 1] = y;
            vertices[(i * numVerticesPerSection + j) * 3 + 2] = z;
        }
    }

    // Calculate indices for the sides
    for (int i = 0; i < numSections - 1; i++) {
        for (int j = 0; j < numVerticesPerSection; j++) {
            GLuint idx1 = i * numVerticesPerSection + j;
            GLuint idx2 = (j < numVerticesPerSection - 1) ? idx1 + 1 : i * numVerticesPerSection;
            GLuint idx3 = (i + 1) * numVerticesPerSection + j;
            GLuint idx4 = (j < numVerticesPerSection - 1) ? idx3 + 1 : (i + 1) * numVerticesPerSection;
            indices.push_back(idx1);
            indices.push_back(idx2);
            indices.push_back(idx3);
            indices.push_back(idx2);
            indices.push_back(idx4);
            indices.push_back(idx3);
        }
    }

    // Calculate indices for the top
    int topCenterIndex = vertices.size() / 3; // Index of the virtual center vertex for the top
    vertices.push_back(0); // x
    vertices.push_back(0); // y
    vertices.push_back(height); // z (top of the prism)
    for (int j = 0; j < numVerticesPerSection; j++) {
        indices.push_back(topCenterIndex);
        indices.push_back((numSections - 1) * numVerticesPerSection + j);
        indices.push_back((numSections - 1) * numVerticesPerSection + ((j + 1) % numVerticesPerSection));
    }

    // Calculate indices for the bottom
    int bottomCenterIndex = vertices.size() / 3; // Index of the virtual center vertex for the bottom
    vertices.push_back(0); // x
    vertices.push_back(0); // y
    vertices.push_back(0); // z (bottom of the prism)
    for (int j = 0; j < numVerticesPerSection; j++) {
        indices.push_back(bottomCenterIndex);
        indices.push_back(j);
        indices.push_back((j + 1) % numVerticesPerSection);
    }

    // Use vertex values as normals
    for (int i = 0; i < numSections; i++) {
        for (int j = 0; j < numVerticesPerSection; j++) {
            GLfloat x = vertices[(i * numVerticesPerSection + j) * 3 + 0];
            GLfloat y = vertices[(i * numVerticesPerSection + j) * 3 + 1];
            GLfloat nx = x;
            GLfloat ny = y;
            GLfloat nz = 0.0f; // Since the sides are vertical
            normals[(i * numVerticesPerSection + j) * 3 + 0] = nx;
            normals[(i * numVerticesPerSection + j) * 3 + 1] = ny;
            normals[(i * numVerticesPerSection + j) * 3 + 2] = nz;
        }
    }

    // Normals for the top center, pointing up
    normals.push_back(0); // nx
    normals.push_back(0); // ny
    normals.push_back(1); // nz (top face normal)

    // Normals for the bottom center, pointing down
    normals.push_back(0); // nx
    normals.push_back(0); // ny
    normals.push_back(-1); // nz (bottom face normal)


    // Draw the faces of the prism
    glColor4f(100 / 255.0f, 149 / 255.0f, 237 / 255.0f, alpha); // Cornflower Blue
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < indices.size(); i += 3) {
        glVertex3f(vertices[indices[i] * 3], vertices[indices[i] * 3 + 1], vertices[indices[i] * 3 + 2]);
        glVertex3f(vertices[indices[i + 1] * 3], vertices[indices[i + 1] * 3 + 1], vertices[indices[i + 1] * 3 + 2]);
        glVertex3f(vertices[indices[i + 2] * 3], vertices[indices[i + 2] * 3 + 1], vertices[indices[i + 2] * 3 + 2]);
    }
    glEnd();


    // Enable polygon offset fill to offset filled polygons for depth testing
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f); // Offset, so the outline doesnt clip the face

    // Draw the outline
    glColor4f(0.0f, 1.0f, 0.0f, alpha); // Green
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (size_t i = 0; i < indices.size(); i += 3) {
        glVertex3f(vertices[indices[i] * 3], vertices[indices[i] * 3 + 1], vertices[indices[i] * 3 + 2]);
        glVertex3f(vertices[indices[i + 1] * 3], vertices[indices[i + 1] * 3 + 1], vertices[indices[i + 1] * 3 + 2]);

        glVertex3f(vertices[indices[i + 1] * 3], vertices[indices[i + 1] * 3 + 1], vertices[indices[i + 1] * 3 + 2]);
        glVertex3f(vertices[indices[i + 2] * 3], vertices[indices[i + 2] * 3 + 1], vertices[indices[i + 2] * 3 + 2]);

        glVertex3f(vertices[indices[i + 2] * 3], vertices[indices[i + 2] * 3 + 1], vertices[indices[i + 2] * 3 + 2]);
        glVertex3f(vertices[indices[i] * 3], vertices[indices[i] * 3 + 1], vertices[indices[i] * 3 + 2]);
    }
    glEnd();

    // Disable line offset after drawing lines
    glDisable(GL_POLYGON_OFFSET_LINE);
}

void DrawSecondPrism(float alpha) {
    const int numVerticesPerSection = 7;
    const int numSections = 2; // bottom and top
    const GLfloat radius = 1.5f;
    const GLfloat height = 2.0f;

    std::vector<GLfloat> vertices(numVerticesPerSection * numSections * 3);
    std::vector<GLuint> indices;
    std::vector<GLfloat> normals(numVerticesPerSection * numSections * 3);

    // Calculate vertices
    for (int i = 0; i < numSections; i++) {
        GLfloat z = i * height / (numSections - 1);
        GLfloat currentRadius = (i == 1) ? radius * 0.5 : radius; // Half radius at the top

        for (int j = 0; j < numVerticesPerSection; j++) {
            GLfloat angle = j * 2 * M_PI / numVerticesPerSection;
            GLfloat x = currentRadius * cos(angle);
            GLfloat y = currentRadius * sin(angle);
            vertices[(i * numVerticesPerSection + j) * 3 + 0] = x;
            vertices[(i * numVerticesPerSection + j) * 3 + 1] = y;
            vertices[(i * numVerticesPerSection + j) * 3 + 2] = z;
        }
    }

    // Calculate indices for the sides
    for (int i = 0; i < numSections - 1; i++) {
        for (int j = 0; j < numVerticesPerSection; j++) {
            GLuint idx1 = i * numVerticesPerSection + j;
            GLuint idx2 = (j < numVerticesPerSection - 1) ? idx1 + 1 : i * numVerticesPerSection;
            GLuint idx3 = (i + 1) * numVerticesPerSection + j;
            GLuint idx4 = (j < numVerticesPerSection - 1) ? idx3 + 1 : (i + 1) * numVerticesPerSection;
            indices.push_back(idx1);
            indices.push_back(idx2);
            indices.push_back(idx3);
            indices.push_back(idx2);
            indices.push_back(idx4);
            indices.push_back(idx3);
        }
    }

    // Calculate indices for the top and bottom
    int topCenterIndex = vertices.size() / 3;
    vertices.push_back(0); // x
    vertices.push_back(0); // y
    vertices.push_back(height); // z (top of the prism)
    for (int j = 0; j < numVerticesPerSection; j++) {
        indices.push_back(topCenterIndex);
        indices.push_back((numSections - 1) * numVerticesPerSection + j);
        indices.push_back((numSections - 1) * numVerticesPerSection + ((j + 1) % numVerticesPerSection));
    }

    int bottomCenterIndex = vertices.size() / 3;
    vertices.push_back(0); // x
    vertices.push_back(0); // y
    vertices.push_back(0); // z (bottom of the prism)
    for (int j = 0; j < numVerticesPerSection; j++) {
        indices.push_back(bottomCenterIndex);
        indices.push_back(j);
        indices.push_back((j + 1) % numVerticesPerSection);
    }

    // Use vertex values as normals
    for (int i = 0; i < numSections; i++) {
        for (int j = 0; j < numVerticesPerSection; j++) {
            GLfloat x = vertices[(i * numVerticesPerSection + j) * 3 + 0];
            GLfloat y = vertices[(i * numVerticesPerSection + j) * 3 + 1];
            GLfloat nx = x;
            GLfloat ny = y;
            GLfloat nz = 0.0f; // Since the sides are vertical
            normals[(i * numVerticesPerSection + j) * 3 + 0] = nx;
            normals[(i * numVerticesPerSection + j) * 3 + 1] = ny;
            normals[(i * numVerticesPerSection + j) * 3 + 2] = nz;
        }
    }

    // Normals for the top center, pointing up
    normals.push_back(0); // nx
    normals.push_back(0); // ny
    normals.push_back(1); // nz (top face normal)

    // Normals for the bottom center, pointing down
    normals.push_back(0); // nx
    normals.push_back(0); // ny
    normals.push_back(-1); // nz (bottom face normal)

    // Draw the faces of the prism
    glColor4f(100 / 255.0f, 149 / 255.0f, 237 / 255.0f, alpha); // Cornflower Blue
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < indices.size(); i += 3) {
        glVertex3f(vertices[indices[i] * 3], vertices[indices[i] * 3 + 1], vertices[indices[i] * 3 + 2]);
        glVertex3f(vertices[indices[i + 1] * 3], vertices[indices[i + 1] * 3 + 1], vertices[indices[i + 1] * 3 + 2]);
        glVertex3f(vertices[indices[i + 2] * 3], vertices[indices[i + 2] * 3 + 1], vertices[indices[i + 2] * 3 + 2]);
    }
    glEnd();


    // Enable polygon offset fill to offset filled polygons for depth testing
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f); // Offset, so the outline doesnt clip the face

    // Draw the outline
    glColor4f(0.0f, 1.0f, 0.0f, alpha); // Green
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (size_t i = 0; i < indices.size(); i += 3) {
        glVertex3f(vertices[indices[i] * 3], vertices[indices[i] * 3 + 1], vertices[indices[i] * 3 + 2]);
        glVertex3f(vertices[indices[i + 1] * 3], vertices[indices[i + 1] * 3 + 1], vertices[indices[i + 1] * 3 + 2]);

        glVertex3f(vertices[indices[i + 1] * 3], vertices[indices[i + 1] * 3 + 1], vertices[indices[i + 1] * 3 + 2]);
        glVertex3f(vertices[indices[i + 2] * 3], vertices[indices[i + 2] * 3 + 1], vertices[indices[i + 2] * 3 + 2]);

        glVertex3f(vertices[indices[i + 2] * 3], vertices[indices[i + 2] * 3 + 1], vertices[indices[i + 2] * 3 + 2]);
        glVertex3f(vertices[indices[i] * 3], vertices[indices[i] * 3 + 1], vertices[indices[i] * 3 + 2]);
    }
    glEnd();

    // Disable line offset after drawing lines
    glDisable(GL_POLYGON_OFFSET_LINE);
}

void DrawObjectsInCircle(float radius, int numObjects, const std::function<void(float)>& drawFunction) {
    for (int i = 0; i < numObjects; ++i) {
        float alpha = (i + 1) * 1.0f / numObjects;
        float prismAngle = alpha * 2.f * M_PI;
        float prismX = radius * cos(prismAngle);
        float prismY = radius * sin(prismAngle);

        glPushMatrix();
        glTranslatef(prismX, prismY, 0.f);

        float prismRotationAngle = atan2(-prismY, -prismX) * 180.f / M_PI;
        glRotatef(prismRotationAngle, 0.f, 0.f, 1.f);

        drawFunction(alpha); // Call the passed function

        glPopMatrix();
    }
}