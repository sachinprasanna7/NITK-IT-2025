#include <iostream>
#include <vector>
using namespace std;


int levenshteinRecursive(string str1, string str2, int m, int n)
{

  // If the length of one of the strings is zero, the distance is equal to the length of the other string
  if (m == 0)
    return n;
  if (n == 0)
    return m;

  // If the last characters of the two strings are equal, ignore them and calculate the distance for the remaining substrings
  if (str1[m - 1] == str2[n - 1])
    return levenshteinRecursive(str1, str2, m - 1, n - 1);

  //Options existing for the last character of the first string:
  // 1. Insert a character into the first string
  // 2. Delete a character from the first string
  // 3. Replace a character in the first string with a different character
  return 1 + min(levenshteinRecursive(str1, str2, m, n - 1), min(levenshteinRecursive(str1, str2, m - 1, n), levenshteinRecursive(str1, str2, m - 1, n - 1)));
}

// TOP DOWN DYNAMIC PROGRAMMING
int levenshteinMemoization(string str1, string str2, int m, int n, vector<vector<int>> &dp)
{

  // If the length of one of the strings is zero, the distance is equal to the length of the other string
  if (m == 0)
    return n;
  if (n == 0)
    return m;

  // If the last characters of the two strings are equal, we can ignore them and calculate the distance for the remaining substrings
  if (str1[m - 1] == str2[n - 1])
    return levenshteinMemoization(str1, str2, m - 1, n - 1, dp);

  // Checking  if the result has already been computed and stored in the vector, this is the memoization step
  if (dp[m][n] != -1)
    return dp[m][n];

  // Compute the Levenshtein distance recursively and store the result in the dp vector
  dp[m][n] = 1 + min(levenshteinMemoization(str1, str2, m, n - 1, dp), min(levenshteinMemoization(str1, str2, m - 1, n, dp), levenshteinMemoization(str1, str2, m - 1, n - 1, dp)));

  // Return the result
  return dp[m][n];
}


// BOTTOM UP DYNAMIC PROGRAMMING
int levenshteinTabulution(string str1, string str2, int m, int n)
{

  // dp vector to store the results of subproblems
  vector<vector<int>> dp(m + 1, vector<int>(n + 1));

  // initialize the first row and column of the dp vector, which represent the case where one of the strings is empty
  for (int j = 0; j <= n; j++)
    dp[0][j] = j;
  for (int i = 0; i <= m; i++)
    dp[i][0] = i;

  // filling the dp vector using bottom-up dynamic programming
  for (int i = 1; i <= m; i++)
  {
    for (int j = 1; j <= n; j++)
    {

      if (str1[i - 1] == str2[j - 1]) // if the characters are the same
        dp[i][j] = dp[i - 1][j - 1];  // no operation needed; take value from diagonal element, which represents the minimum edit distance for the remaining substrings

      else                                                                     // if the characters are different
        dp[i][j] = 1 + min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1])); // take minimum of the three possible operations mentioned in recursive solution and add 1
    }
  }

  return dp[m][n]; // return the last element in the dp matrix, which represents the minimum edit distance
}



// BOTTOM UP - OPTIMISED DYNAMIC PROGRAMMING
int levenshteinOptimised(string str1, string str2, int m, int n)
{
  // Creating a vector with n+1 elements and initialise it to 0
  // This vector will store the minimum number of edits required to transform
  // the first i characters of str1 into the first j characters of str2.
  vector<int> dp(n + 1, 0);

  // Initialising dp[j] to j for all j from 0 to n.
  // This represents the number of insertions required to transform an empty
  // string into the first j characters of str2.
  for (int i = 0; i <= n; i++)
    dp[i] = i;

  // Looping over each character in str1.
  for (int i = 1; i <= m; i++)
  {
    // Storing the previous value of dp[j] in prev.
    int prev = dp[0];

    // Setting dp[0] to i.
    // This represents the number of deletions required to transform the first
    // i characters of str1 into an empty string.
    dp[0] = i;

    // Looping over each character in str2.
    for (int j = 1; j <= n; j++)
    {
      // Storing the current value of dp[j] in temp.
      int temp = dp[j];

      // If the i-th character of str1 is the same as the j-th character of str2,
      // don't need to make any edits, so setting dp[j] to the previous value of dp[j-1]
      if (str1[i - 1] == str2[j - 1])
        dp[j] = prev;

      //Normal flow as before, finding minimum
      else
        dp[j] = 1 + min(prev, min(dp[j], dp[j - 1]));

      // Updating prev to the previous value of dp[j]
      prev = temp;
    }
  }

  // The final value of dp[n] represents the minimum number of edits required to
  // transform the first m characters of str1 into the first n characters of str2.
  return dp[n];
}

string takeInput()
{
  string str;
  bool contains_special = false;
  int ctr = 0;
  do
  {
    if (ctr)
      cout << "Re enter the string: ";
    cin >> str;
    for (int i = 0; i < str.length(); i++)
    {
      if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
      {
        contains_special = 1;
        cout << "Invalid input. Please enter a string without special characters or integers." << endl;
        break;
      }
      else
      {
        contains_special = 0;
      }
    }
    ctr++;
  } while (contains_special == true);

  return str;
}


int main()
{

  cout << "Enter the first string: ";
  string str1 = takeInput();
  cout << "Enter the second string: ";
  string str2 = takeInput();

  vector<vector<int>> dp(str1.length() + 1, vector<int>(str2.length() + 1, -1));

  // This method has been commented out because of its exponential time complexity. It is only used for testing purposes.
  //  cout<<levenshteinRecursive(str1, str2, str1.length(), str2.length());

  cout << endl;
  cout << "The Levenshtein distance between the two strings using TOP DOWN DP is: ";
  cout << levenshteinMemoization(str1, str2, str1.length(), str2.length(), dp);
  cout << endl;
  cout << "The Levenshtein distance between the two strings using BOTTOM UP DP is: ";
  cout << levenshteinTabulution(str1, str2, str1.length(), str2.length());
  cout << endl;
  cout << "The Levenshtein distance between the two strings using OPTIMISED BOTTOM UP DP is: ";
  cout << levenshteinOptimised(str1, str2, str1.length(), str2.length());
  cout << endl << endl;

  return 0;
}