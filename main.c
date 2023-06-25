// #include <stdio.h>
// #include <math.h>
// 
// #define SCREEN_WIDTH 640
// #define SCREEN_HEIGHT 480
// #define FOV_ANGLE 60
// #define NUM_RAYS SCREEN_WIDTH
// 
// float playerX = 300;
// float playerY = 300;
// float playerA = 0;
// 
// void castRays()
// {
// 	for (int x = 0; x < NUM_RAYS; x++)
// 	{
// 		float rayAngle = (playerA - FOV_ANGLE / 2) + ((float)x / NUM_RAYS) * FOV_ANGLE;
// 
// 		float rayDirX = cos(rayAngle);
// 		float rayDirY = sin(rayAngle);
// 
// 		float wallHitX, wallHitY;
// 		if (castRay(rayDirX, rayDirY, &wallHitX, &wallHitY))
// 		{
// 			float distance = sqrt((wallHitX - playerX) * (wallHitX - playerX) + (wallHitY - playerY) * (wallHitY - playerY));
// 
// 			int wallHeight = (int)(SCREEN_HEIGHT / distance);
// 			drawColumn(x, wallHeight);
// 		}
// 	}
// }
// 
// int castRay(float rayDirX, float rayDirY, float *wallHitX, float *wallHitY)
// {
// 	float deltaX = 0, deltaY = 0;
// 	float nextX = playerX, nextY = playerY;
// 
// 	while (nextX >= 0 && nextY >= 0 && nextX < SCREEN_HEIGHT && nextY < SCREEN_HEIGHT)
// 	{
// 		nextX += deltaX;
// 		nextX += deltaY;
// 
// 		if (map[(int)nextY][(int)nextX] == '#')
// 		{
// 			*wallHitX = nextX;
// 			*wallHitY = nextY;
// 			return (1);
// 		}
// 	}
// 	return (0);
// }
// 
// 
// void	drawColumn(int column, int wallHeight)
// {
// 	for (int y = 0; y < SCREEN_HEIGHT; y++)
// 	{
// 		if (y < (SCREEN_HEIGHT - wallHeight) / 2 || y >= (SCREEN_HEIGHT + wallHeight) / 2)
// 		{
// 			drawPixel(column, y, ,' ');
// 		}
// 		else
// 		{
// 			drawPixel(column, y, '#');
// 		}
// 	}
// }
// 
// void	drawScreen()
// {
// 	for (int y = 0; y < SCREEN_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < SCREEN_WIDTH; x++)
// 		{
// 			printf("%c", screen[y][x]);
// 		}
// 		printf("\n");
// 	}
// }
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// void castRays()
// {
//     for (int x = 0; x < NUM_RAYS; x++)
//     {
//         // プレイヤーの視点からの角度を計算
//         float rayAngle = (playerA - FOV_ANGLE / 2) + ((float)x / NUM_RAYS) * FOV_ANGLE;
// 
//         // 光線の方向ベクトルを計算
//         float rayDirX = cos(rayAngle);
//         float rayDirY = sin(rayAngle);
// 
//         // 光線と壁の交差判定を行う関数を呼び出し
//         // この関数では、光線の方向ベクトルとプレイヤーの位置を使用して交差判定を行い、
//         // 交差点の位置や距離、衝突した壁の情報を取得します。
//         // ここでは仮にwallHitXとwallHitYに交差点の位置を格納するものとします。
//         float wallHitX, wallHitY;
//         if (castRay(rayDirX, rayDirY, &wallHitX, &wallHitY))
//         {
//             // 交差点からプレイヤーまでの距離を計算
//             float distance = sqrt((wallHitX - playerX) * (wallHitX - playerX) + (wallHitY - playerY) * (wallHitY - playerY));
// 
//             // 距離に応じて壁の高さを計算し、画面上に描画
//             int wallHeight = (int)(SCREEN_HEIGHT / distance);
//             drawColumn(x, wallHeight);
//         }
//     }
// }
// 
// 
// int castRay(float rayDirX, float rayDirY, float *wallHitX, float *wallHitY)
// {
//     float deltaX = 0, deltaY = 0;
//     float nextX = playerX, nextY = playerY;
// 
//     // 光線が壁に当たるまでのループ
//     while (nextX >= 0 && nextY >= 0 && nextX < SCREEN_WIDTH && nextY < SCREEN_HEIGHT)
//     {
//         nextX += deltaX;
//         nextY += deltaY;
// 
//         // 壁との交差判定を行う
//         if (map[(int)nextY][(int)nextX] == '#')
//         {
//             *wallHitX = nextX;
//             *wallHitY = nextY;
//             return 1; // 交差点が見つかった場合は1を返す
//         }
//     }
// 
//     return 0; // 交差点が見つからなかった場合は0を返す
// }
// 
// void drawColumn(int column, int wallHeight)
// {
//     // 壁の高さに応じて垂直な線を描画
//     for (int y = 0; y < SCREEN_HEIGHT; y++)
//     {
//         if (y < (SCREEN_HEIGHT - wallHeight) / 2 || y >= (SCREEN_HEIGHT + wallHeight) / 2)
//         {
//             // 壁の範囲外は背景色で塗りつぶし
//             drawPixel(column, y, ' ');
//         }
//         else
//         {
//             // 壁の範囲内は壁の色で塗りつぶし
//             drawPixel(column, y, '#');
//         }
//     }
// }
// 
// void drawScreen()
// {
//     for (int y = 0; y < SCREEN_HEIGHT; y++)
//     {
//         for (int x = 0; x < SCREEN_WIDTH; x++)
//         {
//             printf("%c", screen[y][x]);
//         }
//         printf("\n");
//     }
// }

// #define SCREEN_WIDTH 640
// #define SCREEN_HEIGHT 480
// #define FOV_ANGLE 60
// #define NUM_RAYS SCREEN_WIDTH
// 
// float playerX = 300;
// float playerY = 300;
// float playerA = 0;

#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define TILE_SIZE 64
#define FOV_ANGLE (60 * (M_PI / 180))
#define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

#include <stdio.h>
#include <math.h>

typedef s_player	t_player;
typedef s_ray		t_ray;

struct	s_player
{
	float	position_x;
	float	position_y;
	float	direction_x;
	float	direction_y;
};

struct	s_ray
{
	float	plane_x;
	float	plane_y;
	float	distance;
};

Player player;
Ray rays[WINDOW_WIDTH];

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	cast_all_rays(void)
{
	int		num_rays = WINDOW_WIDTH;
	float	ray_angle = player.rotation_angle - (FOV_ANGLE / 2);

	for (int i = 0; i < num_rays; i++)
	{
		float	ray_distance = cast_ray(ray_angle);
		rays[i].distance = ray_distance;
		rays[i].ray_angle = ray_angle;

		ray_angle += FOV_ANGLE / num_rays;
	}
}

float	cast_ray(float angle)
{
	angle = normalize_angle(angle)
	:
}









































#include <stdio.h>
#include <math.h>

#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define TILE_SIZE 64
#define FOV_ANGLE (60 * (M_PI / 180))
#define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

typedef struct  {
    float x;
    float y;
    float width;
    float height;
} Player;

typedef struct {
    float x;
    float y;
    float ray_angle;
    float distance;
    int is_vertical;
} Ray;

Player player;
Ray rays[WINDOW_WIDTH];

void cast_all_rays(void) {
    int num_rays = WINDOW_WIDTH;
    float ray_angle = player.rotation_angle - (FOV_ANGLE / 2);

    for (int i = 0; i < num_rays; i++) {
        float ray_distance = cast_ray(ray_angle);
        rays[i].distance = ray_distance;
        rays[i].ray_angle = ray_angle;

        ray_angle += FOV_ANGLE / num_rays;
    }
}

float cast_ray(float angle) {
    // レイの角度を正規化
    angle = normalize_angle(angle);

    // レイが上下左右どの方向を向いているかをチェック
    int is_ray_facing_up = angle > 0 && angle < M_PI;
    int is_ray_facing_down = !is_ray_facing_up;
    int is_ray_facing_right = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
    int is_ray_facing_left = !is_ray_facing_right;

    // 初期化
    float xintercept, yintercept;
    float xstep, ystep;

    /////////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    /////////////////////////////////////////////

    // ...

    /////////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    /////////////////////////////////////////////

    // ...

    // 両方の距離を計算し、最小値を選ぶ
    float horizontal_distance = (is_horizontal_hit) ? distance_between_points(player.x, player.y, horz_hit_x, horz_hit_y) : INT_MAX;
    float vertical_distance = (is_vertical_hit) ? distance_between_points(player.x, player.y, vert_hit_x, vert_hit_y) : INT_MAX;

    // 最小の距離をレイの距離とする
    if (vertical_distance < horizontal_distance) {
        rays[i].distance = vertical_distance;
        rays[i].is_vertical = 1;
    } else {
        rays[i].distance = horizontal_distance;
        rays[i].is_vertical = 0;
    }
}

