#include "System/Console.h"
#include "System/System.h"
#include "System/Gfx.h"
#include "System/Math.h"

extern "C" int main()
{
    System::InitSystemComponents();

    Random rnd = Random();

    bool game_over = false;

    int block_size = 10;
    int input_dir_x = 1, input_dir_y = 0;
    int game_dir_x = 1, game_dir_y = 0;

    int x_snake[SCREEN_WIDTH] = {1, 2, 3}, y_snake[SCREEN_HEIGHT] = {1, 1, 1};
    int snake_length = 3;

    int x_apple = rnd.Next(0, (SCREEN_WIDTH / block_size) - 1), y_apple = rnd.Next(0, (SCREEN_HEIGHT / block_size) - 1);
    for(int i = 0; i < snake_length; i++)
    {
        while(x_apple == x_snake[i] && y_apple == y_snake[i])
        {
            x_apple = rnd.Next(0, (SCREEN_WIDTH / block_size) - 1), y_apple = rnd.Next(0, (SCREEN_HEIGHT / block_size) - 1);
        }
    }
    
    //GFX::DrawSphere((SCREEN_WIDTH / 2), (SCREEN_WIDTH / 2) - 50, fromRGB(85, 63, 201));

    //asm volatile("int $0x0");

    while(true)
    {
        if(game_over) break;

        //Input
        switch(Keyboard::GetKeyCodeStatic())
        {
            case KEY_W:
                if(input_dir_y != 1) { input_dir_y = -1; input_dir_x = 0; }
                break;
            case KEY_S:
                if(input_dir_y != -1) { input_dir_y = 1; input_dir_x = 0; }
                break;
            case KEY_A:
                if(input_dir_x != 1) { input_dir_y = 0; input_dir_x = -1; }
                break;
            case KEY_D:
                if(input_dir_x != -1) { input_dir_y = 0; input_dir_x = 1; }
                break;
            case KEY_UP:
                if(input_dir_y != 1) { input_dir_y = -1; input_dir_x = 0; }
                break;
            case KEY_DOWN:
                if(input_dir_y != -1) { input_dir_y = 1; input_dir_x = 0; }
                break;
            case KEY_LEFT:
                if(input_dir_x != 1) { input_dir_y = 0; input_dir_x = -1; }
                break;
            case KEY_RIGHT:
                if(input_dir_x != -1) { input_dir_y = 0; input_dir_x = 1; }
                break;
        }

        //Update
        if(x_snake[snake_length - 1] > (SCREEN_WIDTH / block_size) - 1) x_snake[snake_length - 1] = 0;
        if(x_snake[snake_length - 1] < 0) x_snake[snake_length - 1] = SCREEN_WIDTH / block_size - 1;
        if(y_snake[snake_length - 1] > (SCREEN_HEIGHT / block_size) - 1) y_snake[snake_length - 1] = 0;
        if(y_snake[snake_length - 1] < 0) y_snake[snake_length - 1] = SCREEN_HEIGHT / block_size - 1;

        GFX::DrawRectangle(x_apple * block_size, y_apple * block_size, block_size, block_size, 0, fromRGB(190, 0, 0));

        for(int i = 0; i < snake_length; i++)
        {
            GFX::DrawRectangle(x_snake[i] * block_size, y_snake[i] * block_size, block_size, block_size, 0, fromRGB(0, 190, 0));

            if(i != snake_length - 1)
            {
                if(x_snake[snake_length - 1] == x_snake[i] && y_snake[snake_length - 1] == y_snake[i])
                {
                    game_over = true;
                }
                else 
                {
                    x_snake[i] = x_snake[i + 1];
                    y_snake[i] = y_snake[i + 1];
                }
            }
            else
            {
                x_snake[i] += input_dir_x;
                y_snake[i] += input_dir_y;
            }
        }
        
        if(x_snake[snake_length - 1] == x_apple && y_snake[snake_length - 1] == y_apple)
        {
            x_apple = rnd.Next(0, (SCREEN_WIDTH / block_size) - 1), y_apple = rnd.Next(0, (SCREEN_HEIGHT / block_size) - 1);
            for(int i = 0; i < snake_length; i++)
            {
                while(x_apple == x_snake[i] && y_apple == y_snake[i])
                {
                    x_apple = rnd.Next(0, (SCREEN_WIDTH / block_size) - 1), y_apple = rnd.Next(0, (SCREEN_HEIGHT / block_size) - 1);
                }
            }
            
           
            snake_length++;
            x_snake[snake_length - 1] = x_snake[snake_length - 2] + input_dir_x;
            y_snake[snake_length - 1] = y_snake[snake_length - 2] + input_dir_y;
        }
        //GFX::DrawText(to_string(snake_length), 2, 2);

        System::Sleep(100);
        VGA::Clear();
    }
    GFX::DrawText("GAME OVER", (SCREEN_WIDTH / 2) - ((9 * 8) / 2), (SCREEN_HEIGHT / 2) - (4));
    
    for(;;);
}
