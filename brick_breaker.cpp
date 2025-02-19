#include <SFML/Graphics.hpp>
#include <vector>

// Game Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BRICK_ROWS = 5;
const int BRICK_COLUMNS = 10;
const int BRICK_WIDTH = 70;
const int BRICK_HEIGHT = 20;
const float BALL_SPEED = 0.3f;
const float PADDLE_SPEED = 0.5f;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Brick Breaker", sf::Style::Close);
    
    // Paddle
    sf::RectangleShape paddle(sf::Vector2f(100.f, 15.f));
    paddle.setFillColor(sf::Color::White);
    paddle.setPosition(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT - 50);

    // Ball
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    sf::Vector2f ballVelocity(BALL_SPEED, -BALL_SPEED);

    // Bricks
    std::vector<sf::RectangleShape> bricks;
    for (int i = 0; i < BRICK_ROWS; ++i) {
        for (int j = 0; j < BRICK_COLUMNS; ++j) {
            sf::RectangleShape brick(sf::Vector2f(BRICK_WIDTH, BRICK_HEIGHT));
            brick.setFillColor(sf::Color::Red);
            brick.setPosition(j * (BRICK_WIDTH + 10) + 30, i * (BRICK_HEIGHT + 10) + 50);
            bricks.push_back(brick);
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        // Paddle Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddle.getPosition().x > 0)
            paddle.move(-PADDLE_SPEED, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddle.getPosition().x < WINDOW_WIDTH - 100)
            paddle.move(PADDLE_SPEED, 0.f);

        // Ball Movement
        ball.move(ballVelocity);

        // Ball Collision with Walls
        if (ball.getPosition().x <= 0 || ball.getPosition().x >= WINDOW_WIDTH - 20)
            ballVelocity.x = -ballVelocity.x;
        if (ball.getPosition().y <= 0)
            ballVelocity.y = -ballVelocity.y;

        // Ball Collision with Paddle
        if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds()))
            ballVelocity.y = -ballVelocity.y;

        // Ball Collision with Bricks
        for (size_t i = 0; i < bricks.size(); i++) {
            if (ball.getGlobalBounds().intersects(bricks[i].getGlobalBounds())) {
                bricks.erase(bricks.begin() + i);
                ballVelocity.y = -ballVelocity.y;
                break;
            }
        }

        // Lose Condition
        if (ball.getPosition().y > WINDOW_HEIGHT) {
            window.close();
        }

        // Render
        window.clear(sf::Color::Black);
        window.draw(paddle);
        window.draw(ball);
        for (auto& brick : bricks)
            window.draw(brick);
        window.display();
    }
    return 0;
}

