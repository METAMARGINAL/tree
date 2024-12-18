#include "Tree.h"
#include "raylib.h"

TreeNode::TreeNode(std::string w) : word(w), left(nullptr), right(nullptr), highlight(false) {}

TreeNode* Insert(TreeNode* root, const std::string& word) {
    if (root == nullptr) {
        return new TreeNode(word);
    }
    if (word < root->word) {
        root->left = Insert(root->left, word);
    }
    else {
        root->right = Insert(root->right, word);
    }
    return root;
}

int CountAndHighlight(TreeNode* root, char letter) {
    if (root == nullptr) return 0;

    int count = 0;
    root->highlight = false; // —брос подсветки
    if (!root->word.empty() && root->word[0] == letter) {
        root->highlight = true;
        count++;
    }
    count += CountAndHighlight(root->left, letter);
    count += CountAndHighlight(root->right, letter);
    return count;
}

void DrawTree(TreeNode* root, int x, int y, int offsetX, int level) {
    if (root == nullptr) return;

    Color nodeColor = root->highlight ? RED : DARKBLUE;
    DrawCircle(x, y, 20, nodeColor);
    DrawText(root->word.c_str(), x - 20, y - 10, 10, WHITE);

    if (root->left) {
        DrawLine(x, y, x - offsetX, y + 80, WHITE);
        DrawTree(root->left, x - offsetX, y + 80, offsetX / 2, level + 1);
    }

    if (root->right) {
        DrawLine(x, y, x + offsetX, y + 80, WHITE);
        DrawTree(root->right, x + offsetX, y + 80, offsetX / 2, level + 1);
    }
}

void DeleteTree(TreeNode* root) {
    if (root == nullptr) return;
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
}
