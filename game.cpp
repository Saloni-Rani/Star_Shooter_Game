// ADVANCED SPACE SHOOTER GAME
// STAR ENEMIES + SCORE + HIGH SCORE + TIMER
// ESC = EXIT
// R = RESTART

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// ---------------- PLAYER ----------------
float playerX = 0.0f;

// ---------------- BULLETS ----------------
vector<float> bulletX;
vector<float> bulletY;

// ---------------- ENEMIES ----------------
vector<float> enemyX;
vector<float> enemyY;

// ---------------- GAME DATA ----------------
int score = 0;
int highScore = 0;
int shots = 0;
int hits = 0;

bool gameOver = false;

int startTime = 0;

// ---------------- DRAW TEXT ----------------
void drawText(float x, float y, string text)
{
    glRasterPos2f(x, y);

    for(char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// ---------------- RESET GAME ----------------
void resetGame()
{
    playerX = 0.0f;

    bulletX.clear();
    bulletY.clear();

    enemyX.clear();
    enemyY.clear();

    score = 0;
    shots = 0;
    hits = 0;

    gameOver = false;

    startTime = glutGet(GLUT_ELAPSED_TIME);

    // CREATE STAR ENEMIES
    for(int i = 0; i < 7; i++)
    {
        enemyX.push_back(((rand() % 180) - 90) / 100.0f);
        enemyY.push_back(0.5f + (i * 0.25f));
    }
}

// ---------------- DRAW PLAYER ----------------
void drawPlayer()
{
    glColor3f(0.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);

        glVertex2f(playerX, -0.9f);
        glVertex2f(playerX - 0.05f, -0.8f);
        glVertex2f(playerX + 0.05f, -0.8f);

    glEnd();
}

// ---------------- DRAW BULLETS ----------------
void drawBullets()
{
    glColor3f(1.0f, 0.0f, 0.0f);

    for(int i = 0; i < bulletX.size(); i++)
    {
        glBegin(GL_QUADS);

            glVertex2f(bulletX[i] - 0.01f, bulletY[i]);
            glVertex2f(bulletX[i] + 0.01f, bulletY[i]);
            glVertex2f(bulletX[i] + 0.01f, bulletY[i] + 0.05f);
            glVertex2f(bulletX[i] - 0.01f, bulletY[i] + 0.05f);

        glEnd();
    }
}

// ---------------- DRAW STAR ENEMIES ----------------
void drawEnemies()
{
    glColor3f(1.0f, 1.0f, 0.0f);

    for(int i = 0; i < enemyX.size(); i++)
    {
        float x = enemyX[i];
        float y = enemyY[i];

        glBegin(GL_POLYGON);

            glVertex2f(x, y + 0.06f);

            glVertex2f(x + 0.02f, y + 0.02f);
            glVertex2f(x + 0.06f, y + 0.02f);

            glVertex2f(x + 0.03f, y - 0.01f);
            glVertex2f(x + 0.04f, y - 0.06f);

            glVertex2f(x, y - 0.03f);

            glVertex2f(x - 0.04f, y - 0.06f);
            glVertex2f(x - 0.03f, y - 0.01f);

            glVertex2f(x - 0.06f, y + 0.02f);
            glVertex2f(x - 0.02f, y + 0.02f);

        glEnd();
    }
}

// ---------------- DISPLAY ----------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawPlayer();
    drawBullets();
    drawEnemies();

    glColor3f(1.0f, 1.0f, 1.0f);

    drawText(-0.95f, 0.92f, "Score: " + to_string(score));
    drawText(-0.95f, 0.84f, "High Score: " + to_string(highScore));
    drawText(-0.95f, 0.76f, "Shots: " + to_string(shots));
    drawText(-0.95f, 0.68f, "Hits: " + to_string(hits));

    // TIMER
    int elapsed = (glutGet(GLUT_ELAPSED_TIME) - startTime) / 1000;
    int remainingTime = 50 - elapsed;

    if(remainingTime < 0)
        remainingTime = 0;

    drawText(0.45f, 0.92f, "Time Left: " + to_string(remainingTime) + "s");

    drawText(0.45f, 0.84f, "ESC = Exit");
    drawText(0.45f, 0.76f, "R = Restart");

    // GAME OVER SCREEN
    if(gameOver)
    {
        glColor3f(1.0f, 0.0f, 0.0f);

        drawText(-0.15f, 0.0f, "GAME OVER");
        drawText(-0.20f, -0.10f, "FINAL SCORE: " + to_string(score));
    }

    glutSwapBuffers();
}

// ---------------- UPDATE ----------------
void update(int value)
{
    if(!gameOver)
    {
        // GAME OVER AFTER 50 SECONDS
        int elapsed = (glutGet(GLUT_ELAPSED_TIME) - startTime) / 1000;

        if(elapsed >= 50)
        {
            gameOver = true;
        }

        // MOVE BULLETS
        for(int i = 0; i < bulletY.size(); i++)
        {
            bulletY[i] += 0.08f;

            if(bulletY[i] > 1.0f)
            {
                bulletY.erase(bulletY.begin() + i);
                bulletX.erase(bulletX.begin() + i);

                i--;
            }
        }

        // MOVE ENEMIES
        for(int i = 0; i < enemyY.size(); i++)
        {
            enemyY[i] -= 0.008f;

            if(enemyY[i] < -1.1f)
            {
                enemyY[i] = 1.0f;
                enemyX[i] = ((rand() % 180) - 90) / 100.0f;
            }
        }

        // COLLISION DETECTION
        for(int i = 0; i < bulletX.size(); i++)
        {
            for(int j = 0; j < enemyX.size(); j++)
            {
                if(bulletX[i] > enemyX[j] - 0.07f &&
                   bulletX[i] < enemyX[j] + 0.07f &&
                   bulletY[i] > enemyY[j] - 0.07f &&
                   bulletY[i] < enemyY[j] + 0.07f)
                {
                    score++;
                    hits++;

                    if(score > highScore)
                        highScore = score;

                    bulletX.erase(bulletX.begin() + i);
                    bulletY.erase(bulletY.begin() + i);

                    enemyY[j] = 1.0f;
                    enemyX[j] = ((rand() % 180) - 90) / 100.0f;

                    i--;

                    break;
                }
            }
        }
    }

    glutPostRedisplay();

    glutTimerFunc(16, update, 0);
}

// ---------------- ARROW KEYS ----------------
void specialKeys(int key, int x, int y)
{
    if(!gameOver)
    {
        if(key == GLUT_KEY_LEFT)
            playerX -= 0.08f;

        if(key == GLUT_KEY_RIGHT)
            playerX += 0.08f;

        if(playerX < -0.95f)
            playerX = -0.95f;

        if(playerX > 0.95f)
            playerX = 0.95f;
    }

    glutPostRedisplay();
}

// ---------------- KEYBOARD ----------------
void keyboard(unsigned char key, int x, int y)
{
    // SHOOT
    if(key == ' ' && !gameOver)
    {
        bulletX.push_back(playerX);
        bulletY.push_back(-0.8f);

        shots++;
    }

    // EXIT
    if(key == 27)
    {
        exit(0);
    }

    // RESTART
    if(key == 'r' || key == 'R')
    {
        resetGame();
    }

    glutPostRedisplay();
}

// ---------------- INIT ----------------
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(-1, 1, -1, 1);

    resetGame();
}

// ---------------- MAIN ----------------
int main(int argc, char** argv)
{
    srand(time(0));

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(1000, 700);

    glutCreateWindow("Advanced Space Shooter");

    init();

    glutDisplayFunc(display);

    glutSpecialFunc(specialKeys);

    glutKeyboardFunc(keyboard);

    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}