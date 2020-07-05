//
// Created by XBB-PC on 2020/6/23.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

/**
 * 208. 实现 Trie (前缀树)
 * 实现一个 Trie (前缀树)，包含 insert, search, 和 startsWith 这三个操作。
 *
 * 字典树
 */
class Trie {
public:
    struct Node {
        vector<Node *> childs; // 字典树只涉及26个字符，可以用列表来模拟下层链接
        bool isleaf; // 用来判断字典树上的节点是不是字符串最后一个匹配的叶子节点，保证字典树包含 inn 时不会匹配 in

        Node(bool leaf) : isleaf(leaf), childs(vector<Node *>(26, NULL)) {}
    };

    Node *root;

    /** Initialize your data structure here. */
    Trie() {
        root = new Node(false);
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        do_insert(word, root);
    }

    void do_insert(string word, Node *node) {
        if (!node) return;
        if (word.size() == 0) {
            node->isleaf = true; // 如果已经到了目标字符串的最后一个，则设叶子节点为true
            return;
        }
        if (!node->childs[word[0] - 'a']) // 如果没有下层节点，则构建
            node->childs[word[0] - 'a'] = new Node(false);
        do_insert(word.substr(1, word.size() - 1), node->childs[word[0] - 'a']);
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        return do_search(word, root);
    }

    bool do_search(string word, Node *node) {
        if (!node) return false;
        if (word.size() == 0) return node->isleaf; // 搜索时如果已经到字符串的最后，则返回是否是叶子节点
        return do_search(word.substr(1, word.size() - 1), node->childs[word[0] - 'a']);
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return do_startsWith(prefix, root);
    }

    bool do_startsWith(string prefix, Node *node) {
        if (!node) return false;
        if (prefix.size() == 0) return true; // 按前缀返回时，不是叶子节点也可以认为是满足前缀
        return do_startsWith(prefix.substr(1, prefix.size() - 1), node->childs[prefix[0] - 'a']);
    }
};


/**
 * 677. 键值映射
 *
 * 实现一个 MapSum 类里的两个方法，insert 和 sum。
 * 对于方法 insert，你将得到一对（字符串，整数）的键值对。字符串表示键，整数表示值。如果键已经存在，那么原来的键值对将被替代成新的键值对。
 * 对于方法 sum，你将得到一个表示前缀的字符串，你需要返回所有以该前缀开头的键的值的总和。
 *
 * 构建字典树trie
 */
class MapSum {
public:
    /** Initialize your data structure here. */

    struct Node {
        vector<Node *> childs;
        bool isLeaf;
        int val;

        Node() : isLeaf(false), childs(vector<Node *>(26, NULL)), val(0) {}
    };

    Node *root;

    MapSum() {
        root = new Node();
    }

    void insert(string key, int val) {
        do_insert(key, val, root);
    }

    void do_insert(string key, int val, Node *node) {
        if (!node) return;
        if (key.size() == 0) {
            node->isLeaf = true;
            node->val = val;
            return;
        }

        if (!node->childs[key[0] - 'a'])
            node->childs[key[0] - 'a'] = new Node();
        return do_insert(key.substr(1, key.size() - 1), val, node->childs[key[0] - 'a']);
    }

    int sum(string prefix) {
        return do_sum(prefix, root);
    }

    int do_sum(string prefix, Node *node) {
        if (!node) return 0;
        if (prefix.size() == 0) {
            int tmp = 0;
            for (auto n : node->childs)
                if (n)
                    tmp += do_sum(prefix, n);

            if (node->isLeaf)
                return tmp + node->val;
            else
                return tmp;
        }

        return do_sum(prefix.substr(1, prefix.size() - 1), node->childs[prefix[0] - 'a']);
    }
};


/**
 * 648. 单词替换
 * 在英语中，我们有一个叫做 词根(root)的概念，它可以跟着其他一些词组成另一个较长的单词——我们称这个词为 继承词(successor)。例如，词根an，跟随着单词 other(其他)，可以形成新的单词 another(另一个)。
 * 现在，给定一个由许多词根组成的词典和一个句子。你需要将句子中的所有继承词用词根替换掉。如果继承词有许多可以形成它的词根，则用最短的词根替换它。
 * 你需要输出替换之后的句子。
 */
class Solution {
public:
    struct Node {
        vector<Node *> childs;
        bool isleaf;

        Node(bool leaf) : isleaf(leaf), childs(vector<Node *>(26, NULL)) {};
    };

    Node *root;

    void insert(string word, Node *node) {
        if (!node) return;
        if (word.size() == 0) {
            node->isleaf = true;
            return;
        }

        if (!node->childs[word[0] - 'a'])
            node->childs[word[0] - 'a'] = new Node(false);
        insert(word.substr(1, word.size() - 1), node->childs[word[0] - 'a']);
    }

    string search(string word, Node *node, int i) {
        if (!node) return word;
        if (node->isleaf) return word.substr(0, i - 1);
        if (word.size() <= i) return word;

        return search(word, node->childs[word[i - 1] - 'a'], i + 1);
    }

    void fun(vector<string> &dict) {
        root = new Node(false);
        for (auto s : dict)
            insert(s, root);
    }

    string replaceWords(vector<string> &dict, string sentence) {
        fun(dict);
        string s = sentence + " ";
        string ans = "";
        while (s.size() > 0) { // 字符串分割
            int pos = s.find(" ", 0);
            ans += search(s.substr(0, pos), root, 1);
            ans += " ";
            s = s.substr(pos + 1, s.size() - pos);
        }
        return ans.substr(0, ans.size() - 1);
    }
};