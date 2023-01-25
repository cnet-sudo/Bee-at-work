#include "Player.h"

void Player::MoveRight()
{
    if (BeeSprite.getPosition().x < 1100) stepx = 5.0f;
    if (BeeAnim.GetCurrentAnimationName() != "idleForward") BeeAnim.SwitchAnimation("idleForward"); 
           
}

void Player::MoveLeft()
{
    if (BeeSprite.getPosition().x > 50) stepx = -5.0f;
    if (BeeAnim.GetCurrentAnimationName() != "idleBack") BeeAnim.SwitchAnimation("idleBack"); 
 
}

void Player::MoveUp()
{
    if (BeeSprite.getPosition().y > 100) stepy = -5.0f;
}

void Player::MoveDown()
{
    if (BeeSprite.getPosition().y < 620) stepy = 5.0f;
}

void Player::startDied(float x,float y)
{
    if (BeeAnim.GetCurrentAnimationName() != "idleBack") x -= 30; else x -= 20;
    Splash.setPosition(x, y+20);
    SplashAnim.restart();
}



void Player::setStepx(float x)
{
    stepx = x;
}

void Player::setStepy(float y)
{
    stepy = y;
}

void Player::setdiedBee(bool diedVarible)
{
    diedBee = diedVarible;
}

void Player::setmead(bool meadVarible)
{
    mead = meadVarible;
}

void Player::setreturnBee(bool ret)
{
    returnBee = ret;
}

void Player::update(sf::Time const& deltaTime)
{
    // Проигрышь анимации бризгов
    if (diedBee && !SplashAnim.getEndAnim()) SplashAnim.Update(deltaTime);
    if (!diedBee) BeeAnim.Update(deltaTime);
    BeeTime += deltaTime;
   
    if (BeeTime > sf::milliseconds(20))
    {
        BeeTime = sf::milliseconds(0);

        if (!diedBee)
        {
            BeeSprite.move(stepx, stepy);

            if (BeeSprite.getPosition().x < 50) { BeeSprite.setPosition(50, BeeSprite.getPosition().y); }
            if (BeeSprite.getPosition().x > 1100) { BeeSprite.setPosition(1100, BeeSprite.getPosition().y); }
            if (BeeSprite.getPosition().y < 100) { BeeSprite.setPosition(BeeSprite.getPosition().x, 100); }
            if (BeeSprite.getPosition().y > 620) { BeeSprite.setPosition(BeeSprite.getPosition().x, 620); }
        }
        else
        {  
            if (SplashAnim.getEndAnim()) {
                BeeSprite.setRotation(90);
                BeeSprite.move(0, 7); gsound.play(4);
                if (BeeSprite.getPosition().y > 820) {
                    reset();
                }
            }
        }
    }
    beemead.setPosition(BeeSprite.getPosition().x - 20, BeeSprite.getPosition().y + 40);
}

void Player::draw()
{
    window.draw(BeeSprite);
    if (mead)  window.draw(beemead);
    if (diedBee) window.draw(Splash);
}

void Player::reset()
{
    gsound.stop(4);
    BeeSprite.setPosition(90, 365);
    BeeSprite.setRotation(0);
    BeeAnim.SwitchAnimation("idleForward");
    diedBee = false;
    returnBee = true;
}