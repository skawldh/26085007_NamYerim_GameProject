#include "Piece.h"

Piece::Piece()
    : m_position(0)
{
}

void Piece::Init(int startPosition)
{
    m_position = startPosition;
}

void Piece::Reset(int startPosition)
{
    m_position = startPosition;
}

void Piece::Move(int direction)
{
    m_position += direction;
}

int Piece::GetPosition() const
{
    return m_position;
}