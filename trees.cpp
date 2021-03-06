#include <cstdio>
#include <cstdlib>
#include <time.h>

#define max(x, y) (x >= y ? x : y)
#define min(x, y) (x <= y ? x : y)

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
        seed = seed & ~(1UL << length++);
    }

    void right()
    {
        seed = seed | (1UL << length++);
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
            return path->seed;
        }
        else
        {
            return -1;
        }
    }
};

int maximin_alphabeta(BinaryTree *tree, BinaryTreePath *path, int lower, int upper);
int minimax_alphabeta(BinaryTree *tree, BinaryTreePath *path, int lower, int upper);

struct MaximinState
{
    long path;
    int depth;
};

class MaximinSolver
{
    int maximin(BinaryTree *tree, BinaryTreePath *path, int sign)
    {
        history[t].path = path->seed;
        history[t].depth = path->length;
        t++;

        int score = tree->score(path);

        if (score == -1)
        {
            path->left();
            int left_score = sign * maximin(tree, path, -sign);
            path->back();

            path->right();
            int right_score = sign * maximin(tree, path, -sign);
            path->back();

            return sign * max(left_score, right_score);
        }
        else
        {
            return sign * score;
        }    
    }

public:
    MaximinState *history;
    unsigned long t;

    MaximinSolver(int depth)
    {
        int n_nodes = (1 << depth);
        int max_steps = n_nodes * 3;
        history = new MaximinState[max_steps];
        t = 0;
    }

    int solve(BinaryTree *tree, BinaryTreePath *path)
    {
        return maximin(tree, path, 1);
    }
};

int maximin_alphabeta(BinaryTree *tree, BinaryTreePath *path, int lower, int upper)
{
    int score = tree->score(path);

    if (score == -1)
    {
        path->left();
        int left_score = minimax_alphabeta(tree, path, lower, upper);
        path->back();

        if (upper != -1 && left_score >= upper) return upper;

        lower = left_score;

        path->right();
        int right_score = minimax_alphabeta(tree, path, lower, upper);
        path->back();

        return max(left_score, right_score);
    }
    else
    {
        return score;
    }
}

int minimax_alphabeta(BinaryTree *tree, BinaryTreePath *path, int lower, int upper)
{
    int score = tree->score(path);

    if (score == -1)
    {
        path->left();
        int left_score = maximin_alphabeta(tree, path, lower, upper);
        path->back();

        if (lower != -1 && left_score <= lower) return lower;

        upper = left_score;

        path->right();
        int right_score = maximin_alphabeta(tree, path, lower, upper);
        path->back();

        return min(left_score, right_score);
    }
    else
    {
        return score;
    }
}

// int main()
// {
//     const int DEPTH = 18;
//     int score;

//     BinaryTree tree(DEPTH);
//     BinaryTreePath path(DEPTH);

//     MaximinSolver solver(DEPTH);

//     time_t start_time = clock();
//     score = solver.solve(&tree, &path);
//     printf("Score: %o (%ldus)\n", score, clock() - start_time);

//     path.reset();
//     start_time = clock();
//     score = maximin_alphabeta(&tree, &path, -1, -1);
//     printf("Score: %o (%ldus)\n", score, clock() - start_time);

//     return 0;
// }