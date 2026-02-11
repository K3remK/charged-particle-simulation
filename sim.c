#include <raylib.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int InitCharges();
void DrawCharges();
void ComputeForces();
void ResetForces();
void UpdateCharges(float);
void HandleInput(void);

#define WIDTH 900
#define HEIGHT 600

#define FPS 60

#define NUM_CHARGES 300
#define SPEED 5
#define POSITIVE_PARTICLE_COLOR RED
#define NEGATIVE_PARTICLE_COLOR BLUE
#define NEGATIVE_PARTICLE_PERCENTAGE 0

#define FORCE_MAG 100000
#define RADIUS 7

#define EPS0 8.8541878176E-12

static bool DRAW_VELOCITY = false;
static bool DRAW_INDIVIDUAL_FORCES = false;
static bool DRAW_OVERALL_FORCES = false;

typedef struct {
    float x, y, r, vx, vy, fx, fy;
    int charge;  // can be +1 or -1
} Charge;

Charge charges[NUM_CHARGES];

int num_positive = 0;
int num_negative = 0;

int main(void) {

    InitWindow(WIDTH, HEIGHT, "charged particle simulation");
    SetTargetFPS(FPS);
    srand(time(NULL));
    num_negative = InitCharges();
    num_positive = NUM_CHARGES - num_negative;

    SetWindowTitle(TextFormat("charged particle simulation (%d positive, %d negative)", num_positive, num_negative));
    

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            HandleInput();
            ResetForces();
            ComputeForces();
            UpdateCharges(GetFrameTime());
            DrawCharges();
        EndDrawing();
    }


    return 0;
}

void UpdateCharges(float dt) {
    Charge *c;
    for (int i = 0; i < NUM_CHARGES; i++) {
        c = &charges[i];
        
        c->x += c->vx * dt + c->fx * dt * dt * 0.5;
        c->y += c->vy * dt + c->fy * dt * dt * 0.5;

        c->vx += c->fx * dt;
        c->vy += c->fy * dt;

        // HACK!!
        // to prevent increase in the overall energy
        c->vx *= 0.99f;
        c->vy *= 0.99f;

        if (c->x - c->r < 0 || c->x + c->r > WIDTH) c->vx *= -1;
        if (c->y - c->r < 0 || c->y + c->r > HEIGHT) c->vy *= -1;
    }
}

void ComputeForces(void) {

    Charge* c1;
    Charge* c2;

    for (int i = 0; i < NUM_CHARGES; i++) {
        c1 = &charges[i];

        for (int j = i + 1; j < NUM_CHARGES; j++) {
           c2 = &charges[j];
           
            float dx = c1->x - c2->x;
            float dy = c1->y - c2->y;
            float d2 = (dx * dx) + (dy * dy);
            
            if (d2 < 1)
                d2 = 1;
            
            float d = sqrtf(d2);
            float nx = dx / d;
            float ny = dy / d;
            float f1x = FORCE_MAG * c1->charge * c2->charge * nx / (4 * PI * d2);
            float f1y = FORCE_MAG * c1->charge * c2->charge * ny / (4 * PI * d2);
            c1->fx += f1x;
            c1->fy += f1y;
            c2->fx -= f1x;
            c2->fy -= f1y;

            // DRAW
            if (DRAW_INDIVIDUAL_FORCES) {
                DrawLine(c1->x, c1->y, c1->x + f1x, c1->y + f1y, (Color){255, 255, 255, 255});
                DrawLine(c2->x, c2->y, c2->x - f1x, c2->y - f1y, (Color){255, 255, 255, 255});
            }
        }
    }
}

void HandleInput(void)
{
    if (IsKeyPressed(KEY_V))
        DRAW_VELOCITY = !DRAW_VELOCITY;
    if (IsKeyPressed(KEY_F))
        DRAW_INDIVIDUAL_FORCES = !DRAW_INDIVIDUAL_FORCES;
    if (IsKeyPressed(KEY_G))
        DRAW_OVERALL_FORCES = !DRAW_OVERALL_FORCES;
}

void ResetForces() {
    for (int i = 0; i < NUM_CHARGES; i++) {
        charges[i].fx = 0;
        charges[i].fy = 0;
    }
}

void DrawCharges(void) {
    Charge* c;
    for (int i = 0; i < NUM_CHARGES; i++) {
        c = &charges[i];
        DrawCircle(
                c->x,
                c->y,
                c->r,
                c->charge == 1 ? POSITIVE_PARTICLE_COLOR : NEGATIVE_PARTICLE_COLOR);
        float v = sqrtf(c->vx*c->vx + c->vy*c->vy);
        if (DRAW_VELOCITY)
        {    DrawText(TextFormat("%.02f", v), c->x + 20, c->y + 20, 10, WHITE);
            char x = (int)((c->vx + c->vy) * 1000) % 255;
            DrawLine(c->x, c->y, c->x + c->vx, c->y + c->vy, (Color){x, 255, 255, 255});
        }
        if (DRAW_OVERALL_FORCES) {
            DrawLine(c->x, c->y, c->x + c->fx, c->y + c->fy, (Color){255, 255, 255, 255});
        }
    }
}

int InitCharges(void) {
    float r = RADIUS;
    int count = 0;
    for (int i = 0; i < NUM_CHARGES; i++) {
        Charge* charge = &charges[i];
        charge->r      = r; // radius
        charge->x      = GetRandomValue(r, WIDTH - r);
        charge->y      = GetRandomValue(r, HEIGHT - r);
        charge->vx     = GetRandomValue(-SPEED, SPEED);
        charge->vy     = GetRandomValue(-SPEED, SPEED);
        charge->fx     = 0;
        charge->fy     = 0;
        charge->charge = rand() % 100 <= NEGATIVE_PARTICLE_PERCENTAGE ? -1 : 1;
        if (charge->charge == -1) {
            count++;
        }
    }
    return count;
}