#include <chrono>
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

#include "./data.cpp"
#include "./functions.cpp"

using namespace std::chrono;

int main() {
  float userInput[4];
  int solutionCount = 0;
  std::vector<std::string> resultArray;

  bool isInputValid = handleInput(userInput);
  if (!isInputValid) {
    std::cout << "Masukkan tidak valid\n";
    return 0;
  }

  auto startTime = high_resolution_clock::now();

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
        bool isCalcValid;

        for (int k = 0; k < 7; k++) {
          if (operationOrders[order][k] == 0) {
            operationStack.push(permutedInputs[i][currNum]);
            currNum++;
          } else {
            float val2 = operationStack.top();
            operationStack.pop();
            float val1 = operationStack.top();
            operationStack.pop();

            float result;
            std::tie(result, isCalcValid) =
                calc(val1, val2, permutedOps[j][currOp]);

            if (isCalcValid) {
              operationStack.push(result);
              currOp++;
            } else {
              k += 7;
            }
          }
        }

        if (isCalcValid && operationStack.top() == 24.0) {
          solutionCount++;
          char resultString[18];
          operationToString(resultString, permutedInputs[i], permutedOps[j],
                            order);
          resultArray.push_back((std::string)resultString);
        }
      }
    }
  }

  auto stopTime = high_resolution_clock::now();

  if (solutionCount > 0) {
    std::cout << solutionCount << " solutions found\n";
    for (std::string s : resultArray) {
      std::cout << s;
    }
  } else {
    std::cout << "No solution found\n";
  }

  microseconds execTime = duration_cast<microseconds>(stopTime - startTime);
  printf("Algorithm execution time: %ld microseconds\n", execTime.count());

  return 0;
}