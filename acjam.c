// TODO: load player texture with frames

#include "raylib.h"
#include "raymath.h" 

#define DRAW_FPS 60
#define LOGIC_FPS 60
#define LOGIC_FRAME_TIME 1.0f / (float)LOGIC_FPS
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600


#define SCREEN_CENTER (Vector2){(float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2}


#define TILE_SIZE 32
#define MAX_ENEMIES 1000

// Variables

enum State{
    IDLE,
    WALKING,
    DODGING
};

enum ShotType{
    NORMAL,
    PIERCING
};

typedef struct Animation{
    Texture2D sprite;
    Vector2 origin;
    Vector2 size;
    float rotation;
    Color tint;
    float t;
} Animation;

typedef struct Player
{
    int maxHp;
    int hp;
    Vector2 position;
    Vector2 currSpeed;
    float maxSpeed;

    float damage;
    float shotSpeed;
    int shotType;
    float shotInterval;
    int state;

    float radius;
    Animation animation;

} Player;

Player InitPlayer(){
    Texture2D sprite = LoadTexture("resources/player.png");

    Animation pAnim = {
        .origin = Vector2Zero(),
        .rotation = 0.0f,
        .size = {32.0f, 32.0f},
        .sprite = sprite,
        .tint = WHITE,
        .t = 0.0f,
    };

    Player p = {
        .animation = pAnim,
        .currSpeed = Vector2Zero(),
        .damage = 10,
        .hp = 100,
        .maxHp = 100,
        .maxSpeed = 5.0f,
        .position = Vector2Zero(),
    };

    return p;
}
int DrawPlayer(Player *p)
{
    Animation a = p->animation;
    DrawTexturePro(a.sprite,
                   (Rectangle){0.0f, 0.0f, a.size.x, a.size.y},
                   (Rectangle){p->position.x, p->position.y, a.size.x, a.size.y},
                   a.origin,
                   a.rotation,
                   a.tint
                   );
}
void UpdatePlayer(Player *p){
    Vector2 direction = Vector2Zero();
    if (IsKeyDown(KEY_A)) 
    direction = Vector2Add(direction, (Vector2){-1.0f,  0.0f});
    if (IsKeyDown(KEY_S)) direction = Vector2Add(direction, (Vector2){ 0.0f,  1.0f});
    if (IsKeyDown(KEY_D)) direction = Vector2Add(direction, (Vector2){ 1.0f,  0.0f});
    if (IsKeyDown(KEY_W)) direction = Vector2Add(direction, (Vector2){ 0.0f, -1.0f});

    p->currSpeed = Vector2Scale(Vector2Normalize(direction), p->maxSpeed);
    p->position = Vector2Add(p->position, p->currSpeed);
}


typedef struct Enemy
{
     
} Enemy;

typedef struct EnemyHandler{
    Enemy enemyArray[MAX_ENEMIES];
} EnemyHandler;

typedef struct Bullet{

} Bullet;

typedef struct BulletHandler{

} BulletHandler;

typedef struct Effect{

} Effect;

typedef struct EffectHandler{

} EffectHandler;

// Main

int main()
{
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AcerolaJam0");
    SetTargetFPS(DRAW_FPS);

    float logic_acc = 0.0f;

    Player player = InitPlayer();
    Camera2D camera = {.offset = SCREEN_CENTER,
                       .rotation = 0.0f,
                       .target = Vector2Subtract(player.position, Vector2Scale(player.animation.size, 0.5f)),
                       .zoom = 1.0f, 
                      };

    while (!WindowShouldClose())
    {
        logic_acc += GetFrameTime();

        if (logic_acc > LOGIC_FRAME_TIME){
            logic_acc -= LOGIC_FRAME_TIME;
            
            UpdatePlayer(&player);
        }

        camera.target = player.position;
        // Draw
        BeginDrawing();
        BeginMode2D(camera);
        
        ClearBackground(RAYWHITE);
        DrawPlayer(&player);

        EndMode2D();

        EndDrawing();
    }
    CloseWindow(); 
    return 0;
}


