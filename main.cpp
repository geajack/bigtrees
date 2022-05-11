#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class BinaryTreePath
{
public:
    int length;
    long seed;

    BinaryTreePath(int depth)
    {
        length = 0;
        seed = 0;
    }    

    void left()
    {
        seed = seed & (0 << length++);
    }

    void right()
    {
        seed = seed | (1 << length++);
    }

    void back()
    {
        length--;
    }

    void reset()
    {
        seed = 0;
        length = 0;
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
            srand(path->seed);
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
    int score;

    BinaryTree tree(DEPTH);
    BinaryTreePath path(DEPTH);

    score = maximin(&tree, &path);
    printf("Score: %d\n", score);

    path.reset();
    score = maximin(&tree, &path);
    printf("Score: %d\n", score);

    return 0;
}