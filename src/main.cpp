#include <iostream>
#include <stack>

#include "./data.cpp"
#include "./functions.cpp"

int main() {
  float userInput[4];
  int solutionCount = 0;

  bool isInputValid = handleInput(userInput);
  if (!isInputValid) {
    std::cout << "Masukkan tidak valid\n";
    return 0;
  }

  for (int order = 0; order < 5; order++) {
    int permutedOps[64][3];
    float permutedInputs[24][4];

    permuteOperator(permutedOps);
    permuteInput(permutedInputs, userInput);

    for (int i = 0; i < 24; i++) {
      for (int j = 0; j < 64; j++) {
        std::stack<float> operationStack;
        int currNum = 0;
        int currOp = 0;

        for (int k = 0; k < 7; k++) {
          if (operationOrders[order][k] == 0) {
            operationStack.push(permutedInputs[i][currNum]);
            currNum++;
          } else {
            float val2 = operationStack.top();
            operationStack.pop();
            float val1 = operationStack.top();
            operationStack.pop();

            operationStack.push(calc(val1, val2, permutedOps[j][currOp]));
            currOp++;
          }
        }

        if (operationStack.top() == 24.0) {
          solutionCount++;
          showOperation(permutedInputs[i], permutedOps[j], order);
        }
      }
    }
  }

  std::cout << solutionCount << " solusi ditemukan\n";
  return 0;
}