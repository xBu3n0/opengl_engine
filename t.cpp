#include <iostream>
#include <vector>
#include <algorithm>

bool solve(int value, std::vector<int>& dp, std::vector<int>& moedas, int index)
{
    std::cout << value << std::endl;

    if(value < 0)
      return false;
    if(dp[value] != -1)
        return dp[value];
    if(index == moedas.size())
      return false;
    return (dp[value] = solve(value-moedas[index], dp, moedas, index+1) || solve(value, dp, moedas, index+1));
}

int main()
{
    int M, N, value;

    std::cin >> M >> N;

    value = M;

    std::vector<int> dp(M+1, -1);
    dp[0] = 1;
    
    std::vector<int> moedas(N);

    for(int i = 0; i < N; ++i)
        std::cin >> moedas[i];

    std::sort(moedas.begin(), moedas.end(), [](const int &a, const int &b){return a > b;});

    std::cout << (solve(value, dp, moedas, 0) ? "S" : "N") << std::endl;

    return 0;
}