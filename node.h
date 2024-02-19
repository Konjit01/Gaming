#ifndef NODE_H
#define NODE_H

/**
 * @brief The Node class
 * This class represents a node where a 2D grid will be constructed.
 */
class Node
{
public:
    Node(int xPos, int yPos, int dist, int priority);


    // getters and setters
    int getXPos() const;
    void setXPos(int newXPos);

    int getYPos() const;
    void setYPos(int newYPos);

    int getLevel() const;
    void setLevel(int newLevel);

    int getPriority() const;
    void setPriority(int newPriority);

private:
    int xPos, yPos;
    int level, priority;
};

#endif // NODE_H
