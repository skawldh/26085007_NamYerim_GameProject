#pragma once

class Piece
{
public:
    Piece();

    void Init(int startPosition);
    void Reset(int startPosition);

    void Move(int direction);

    int GetPosition() const;

private:
    int m_position = 0;
};