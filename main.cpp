#include <easy2d/easy2d.h>
#include <string>

using namespace easy2d;

bool gameOver = false;

class Background : public Sprite
{
public:
    Background() // 超醜海灘背景
    {
        this->open("resource/background.png");
        this->setAnchor(0, 0);
        float scaleX = Window::getWidth() / this->getWidth();
        float scaleY = Window::getHeight() / this->getHeight();
        this->setScale(scaleX, scaleY);
        Logger::messageln("背景出現");
    }
};

class pikachu_left : public Sprite
{
public:
    pikachu_left() ////重置皮卡左
    {
        this->open("resource/pikachu_left.png");
        this->setAnchor(0.5f, 0.5f);
        this->setScale(2, 2);
        this->setPos(Window::getWidth() / 4, Window::getHeight() / 10 * 8.5);
        isJumping = false;
        jumpVelocity = 0;
        gravity = 0.5f;
        initialY = this->getPosY();
    }

    bool isJumping;
    float jumpVelocity;
    float gravity;
    float initialY;

    void onUpdate() // 皮卡左移動跳躍
    {
        if (gameOver)
            return;

        if (Input::isDown(KeyCode::A))
        {
            float x = this->getPosX();
            if (x > 50)
            {
                this->movePosX(-2);
            }
        }
        if (Input::isDown(KeyCode::D))
        {
            float x = this->getPosX();
            if (x < 540)
            {
                this->movePosX(2);
            }
        }
        if (Input::isDown(KeyCode::W) && !isJumping)
        {
            isJumping = true;
            jumpVelocity = -15;
            Logger::messageln("左皮卡跳");
        }

        if (isJumping)
        {
            this->movePosY(jumpVelocity);
            jumpVelocity += gravity;

            if (this->getPosY() >= initialY)
            {
                this->setPosY(initialY);
                isJumping = false;
                jumpVelocity = 0;
            }
        }
    }
};

class pikachu_right : public Sprite
{
public:
    pikachu_right() /// 重置皮卡右的位置
    {
        this->open("resource/pikachu_right.png");
        this->setAnchor(0.5f, 0.5f);
        this->setScale(2, 2);
        this->setPos(Window::getWidth() / 4 * 3, Window::getHeight() / 10 * 8.5);
        isJumping = false;
        jumpVelocity = 0;
        gravity = 0.5f;
        initialY = this->getPosY();
    }

    bool isJumping;
    float jumpVelocity;
    float gravity;
    float initialY;

    void onUpdate() // 皮卡右的移動跟跳
    {
        if (gameOver)
            return;

        if (Input::isDown(KeyCode::Left))
        {
            float x = this->getPosX();
            if (x > 660)
            {
                this->movePosX(-2);
            }
        }
        if (Input::isDown(KeyCode::Right))
        {
            float x = this->getPosX();
            if (x < 1150)
            {
                this->movePosX(2);
            }
        }
        if (Input::isDown(KeyCode::Up) && !isJumping)
        {
            isJumping = true;
            jumpVelocity = -15;
            //////排錯看看到時候要不要刪掉
            Logger::messageln("右皮卡跳");
            //////////////////
        }

        if (isJumping)
        {
            this->movePosY(jumpVelocity);
            jumpVelocity += gravity;

            if (this->getPosY() >= initialY)
            {
                this->setPosY(initialY);
                isJumping = false;
                jumpVelocity = 0;
            }
        }
    }
};

class pokeball : public Sprite
{
public:
    pokeball(Sprite *leftPikachu, Sprite *rightPikachu, Text *scoreLeftText, Text *scoreRightText, int *scoreLeft, int *scoreRight, int *Second, Text *Ssssss, Text *Win)
        : leftPikachu(leftPikachu), rightPikachu(rightPikachu),
          scoreLeftText(scoreLeftText), scoreRightText(scoreRightText),
          scoreLeft(scoreLeft), scoreRight(scoreRight), Second(Second), Ssssss(Ssssss), Win(Win)
    {
        this->open("resource/pokeball.png");
        this->setAnchor(0.5f, 0.5f);
        this->setScale(0.8, 0.8);
        this->setPos(600, 350);
        alliconstoppp = 0;
    }

    int speed = 10;
    int x = 1;
    int y = 1;
    int stop = 0;
    int alliconstoppp;
    Sprite *leftPikachu;
    Sprite *rightPikachu;
    Text *scoreLeftText;
    Text *scoreRightText;
    Text *Ssssss;
    Text *Win;
    int *scoreLeft;
    int *scoreRight;
    int *Second;

    void handleCollision(Sprite *pikachu) // 球球與皮卡丘的激情對撞
    {
        float ballX = this->getPosX();
        float pikachuX = pikachu->getPosX();

        if (ballX < pikachuX)
        {
            x = -1;
        }
        else
        {
            x = 1;
        }
        y = -y;

        float moveDistance = speed * 2;
        this->movePosX(x * moveDistance);
        this->movePosY(y * moveDistance);

        alliconstoppp = 10;
    }

    void onUpdate()
    {
        if (gameOver)
            return;

        if (alliconstoppp > 0)
        {
            alliconstoppp--;
        }

        if (this->getPosX() >= 1150)
        {
            x = -1;
        }
        if (this->getPosX() <= 50)
        {
            x = 1;
        }
        if (this->getPosY() <= 50)
        {
            y = 1;
        }

        if (alliconstoppp == 0 && (*Second) <= 0)
        {
            if (isCollidingWith(rightPikachu))
            {
                handleCollision(rightPikachu);
            }

            if (isCollidingWith(leftPikachu))
            {
                handleCollision(leftPikachu);
            }
        }

        if (this->getPosY() >= 600)
        {
            float posX = this->getPosX();
            if (posX > 660 && posX < 1150)
            {
                (*scoreLeft)++;
                scoreLeftText->setText("左邊分數:" + std::to_string(*scoreLeft));
            }
            else if (posX > 50 && posX < 540)
            {
                (*scoreRight)++;
                scoreRightText->setText("右邊分數:" + std::to_string(*scoreRight));
            }
            this->setPos(600, 350);
            y = -y;
            return;
        }
        if (((*Second) / 60) > 0 && stop != 1)
        {
            Ssssss->setText(std::to_string((*Second) / 60));
        }
        else
        {
            Ssssss->setText("");
        }

        (*Second)--;

        if ((*Second) <= 0)
        {
            this->movePosX(x * speed);
            this->movePosY(y * speed);
        }
        if ((*scoreRight) >= 5)
        {
            Win->setText("右邊獲勝！");
            Win->setPos(Window::getWidth() / 4 * 3, Window::getHeight() / 2);
            this->setScale(0);
            stop = 1;
            gameOver = true;
        }
        if ((*scoreLeft) >= 5)
        {
            Win->setText("左邊獲勝 ！");
            Win->setPos(Window::getWidth() / 4, Window::getHeight() / 2);
            this->setScale(0);
            stop = 1;
            gameOver = true;
        }
    }

    bool isCollidingWith(Sprite *other) // 檢測球與其他物體的碰撞
    {
        float thisLeft = this->getPosX() - this->getWidth() * this->getAnchorX();
        float thisRight = thisLeft + this->getWidth();
        float thisTop = this->getPosY() - this->getHeight() * this->getAnchorY();
        float thisBottom = thisTop + this->getHeight();

        float otherLeft = other->getPosX() - other->getWidth() * other->getAnchorX();
        float otherRight = otherLeft + other->getWidth();
        float otherTop = other->getPosY() - other->getHeight() * other->getAnchorY();
        float otherBottom = otherTop + other->getHeight();

        return !(thisRight < otherLeft || thisLeft > otherRight ||
                 thisBottom < otherTop || thisTop > otherBottom);
    }
};

int main()
{
    if (Game::init("程式設計期末專題-皮卡丘打排球", 1200, 700))
    {
        auto scene = gcnew Scene;
        SceneManager::enter(scene);

        auto background = gcnew Background;
        scene->addChild(background);

        auto pika_left = gcnew pikachu_left;
        scene->addChild(pika_left);

        auto pika_right = gcnew pikachu_right;
        scene->addChild(pika_right);

        int score_left = 0;
        int score_right = 0;

        auto scoreLeftText = gcnew Text("左邊分數: 0");
        scoreLeftText->setAnchor(0.0f, 0.0f);
        scoreLeftText->setPos(10, 10);
        scene->addChild(scoreLeftText);

        auto scoreRightText = gcnew Text("右邊分數: 0");
        scoreRightText->setAnchor(1.0f, 0.0f);
        scoreRightText->setPos(Window::getWidth() - 10, 10);
        scene->addChild(scoreRightText);

        auto ssssss = gcnew Text("5");
        ssssss->setAnchor(0.5f, 0.5f);
        ssssss->setScale(12);
        ssssss->setPos(Window::getWidth() / 2, 100);
        scene->addChild(ssssss);

        auto win = gcnew Text("");
        win->setAnchor(0.5f, 0.5f);
        win->setScale(5);
        win->setFontWeight(500);
        win->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
        win->setFillColor(Color::Red);
        scene->addChild(win);

        int second = 360;
        auto ball = gcnew pokeball(pika_left, pika_right, scoreLeftText, scoreRightText, &score_left, &score_right, &second, ssssss, win);
        scene->addChild(ball);

        Game::start();
    }
    Game::destroy();
    return 0;
}
