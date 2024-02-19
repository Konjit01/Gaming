#include "node.h"

Node::Node(int xPos, int yPos, int dist, int priority)
    :xPos{xPos}, yPos{yPos}, level{dist}, priority{priority}
{

}

int Node::getXPos() const
{
    return xPos;
}

void Node::setXPos(int newXPos)
{
    xPos = newXPos;
}

int Node::getYPos() const
{
    return yPos;
}

void Node::setYPos(int newYPos)
{
    yPos = newYPos;
}

int Node::getLevel() const
{
    return level;
}

void Node::setLevel(int newLevel)
{
    level = newLevel;
}

int Node::getPriority() const
{
    return priority;
}

void Node::setPriority(int newPriority)
{
    priority = newPriority;
}
