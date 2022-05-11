#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class BinaryTreePath
{
    char *path;
public:
    int length;

    BinaryTreePath(int depth)
    {
        path = new char[depth];
        length = 0;
    }    

    void left()
    {
        path[length++] = 0;
    }

    void right()
    {
        path[length++] = 1;
    }

    void back()
    {
        length--;
    }
};

class BinaryTree
{
    int depth;
public:
    BinaryTree(int depth)
    {
        this->depth = depth;
    }

    int score(BinaryTreePath *path)
    {
        if (path->length == depth)
        {
            return rand();
        }
        else
        {
            return -1;
        }
    }
};

int maximin(BinaryTree *tree, BinaryTreePath *path)
{
    int score = tree->score(path);

    if (score == -1)
    {
        path->left();
        int left_score = maximin(tree, path);
        path->back();

        path->right();
        int right_score = maximin(tree, path);
        path->back();

        return std::max(left_score, right_score);
    }
    else
    {
        return score;
    }
}

int main()
{
    const int DEPTH = 20;

    BinaryTree tree(DEPTH);
    BinaryTreePath path(DEPTH);

    int score = maximin(&tree, &path);

    printf("Score: %d\n", score);

    return 0;
}