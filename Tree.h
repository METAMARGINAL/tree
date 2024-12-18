#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
#include "raylib.h"

// ��������� ���� ��������� ������
struct TreeNode {
    std::string word;
    TreeNode* left;
    TreeNode* right;
    bool highlight;

    TreeNode(std::string w);
};

// ������� ��� ������ � �������
TreeNode* Insert(TreeNode* root, const std::string& word);
int CountAndHighlight(TreeNode* root, char letter);
void DrawTree(TreeNode* root, int x, int y, int offsetX, int level);
void DeleteTree(TreeNode* root);

#endif // TREE_H
