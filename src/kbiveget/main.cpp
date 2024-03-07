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

void InOrderTraversal(Node *root, ofstream &outputFile)
{
    if (root == NULL)
    {
        return;
    }
    InOrderTraversal(root->left, outputFile);

    cout << root->word << "\t" << root->count << " (" << root->depth << ")" << endl;
    outputFile << root->word << "\t" << root->count << " (" << root->depth << ")" << endl;

    InOrderTraversal(root->right, outputFile);
}

void InOrderTraversalToComputeMaximumAndAverageProbes(Node *root, ofstream &outputFile, int &sumOfProbes, int &count)
{
    if (root == NULL)
    {
        return;
    }
    InOrderTraversalToComputeMaximumAndAverageProbes(root->left, outputFile, sumOfProbes, count);

    // Computing the average number of probes
    // TODO: CHECK IF ADDING 1 IS VALID (IF WE DON'T ADD IT THE AVERAGE IS NOT CORRECT), I THINK IT IS NECESSARY BUT CHECK
    sumOfProbes = sumOfProbes + root->depth + 1; // ADDING ONE TO COMPUTE THE SUM OF PROBES WELL BECAUSE THE PROBES START FROM 0
    count = count + 1;

    InOrderTraversalToComputeMaximumAndAverageProbes(root->right, outputFile, sumOfProbes, count);
}

// void calculateAverageNumberOfProbes(ofstream &outputFile, double &averageNumberOfProbes, int &sumOfProbes)
// {
//     int count = 0;
//     if (count > 0)
//     {
//         double averageProbe = static_cast<double>(sumOfProbes) / count;
//         outputFile << "Average number of probes: " << averageProbe << endl;
//         // averageNumberOfProbes = averageProbe;
//     }
//     else
//     {
//         outputFile << "Average number of probes: 0" << endl; // Handle division by zero
//     }
// }

int main()
{
    Node *root = nullptr;

    int sumOfProbes = 0;
    int count = 0;
    int maximumProbe = 0;
    // int averageProbe = 0;

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
        root = insertNode(root, wordFromTextFile, 0);
    }

    InOrderTraversalToComputeMaximumAndAverageProbes(root, outputFile, sumOfProbes, count);

    if (count > 0)
    {
        double averageProbe = static_cast<double>(sumOfProbes) / count;
        outputFile << "Average number of probes: " << averageProbe << endl;
    }
    else
    {
        outputFile << "Average number of probes: 0" << endl; // Handle division by zero
    }

    InOrderTraversal(root, outputFile);

    return 0;
}