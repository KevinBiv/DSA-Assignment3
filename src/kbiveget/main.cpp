#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node
{
    string word;
    int count;
    int depth;
    int probes;
    Node *left;
    Node *right;
};

Node *createNewNode(string word, int depth)
{
    Node *newNode = new Node();
    newNode->word = word;
    newNode->count = 1;
    newNode->depth = depth;
    newNode->probes = 0; // Initialize probes to 0
    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

string toLowercase(string word)
{
    for (char &c : word)
    {
        c = tolower(c);
    }
    return word;
}

Node *insertNode(Node *root, string word, int depth = 0)
{
    word = toLowercase(word);
    // depth = 0;
    if (root == nullptr)
    {
        root = createNewNode(word, depth);
        root->depth = depth;
        root->probes = 1;
    }
    else if (root->word > word)
    {
        root->left = insertNode(root->left, word, depth + 1);
        root->probes++;
    }
    else if (word > root->word)
    {
        root->right = insertNode(root->right, word, depth + 1);
        root->probes++;
    }
    else
    {
        // Word is already present, increment the number of occurrences
        root->count++;
    }

    return root;
}

// Function to compute average number of probes
void averageNumberOfProbes(Node *root)
{
    int sum = 0;
    int count = 0;
    sum += root->depth;
    count++;
}

void InOrderTraversal(Node *root, ofstream &outputFile, int &sumOfProbes, int &count)
{
    if (root == NULL)
    {
        return;
    }
    InOrderTraversal(root->left, outputFile, sumOfProbes, count);
    cout << root->word << "\t" << root->count << " (" << root->depth << ")"
         << " probes: " << root->depth << endl;
    outputFile << root->word << "\t" << root->count << " (" << root->depth << ")" << endl;

    // Computing the average number of probes
    sumOfProbes = sumOfProbes + root->depth;
    count = count + 1;

    cout << "sum of probes: "
         << " " << sumOfProbes << "\t"
         << "number of nodes: " << count << endl;

    InOrderTraversal(root->right, outputFile, sumOfProbes, count);
}

int main()
{
    Node *root = nullptr;

    int sumOfProbes = 0;
    int count = 0;

    ofstream outputFile("output.txt");
    outputFile << "kbiveget" << endl;

    ifstream inputFile("input.txt");

    string currentPath;
    inputFile >> currentPath;

    // Opening the currentPath
    ifstream currentFile;
    currentFile.open(currentPath);

    string wordFromTextFile;

    while (getline(currentFile, wordFromTextFile, ' '))
    {
        root = insertNode(root, wordFromTextFile, 1);
    }

    InOrderTraversal(root, outputFile, sumOfProbes, count);

    return 0;
}