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
  while (!isInputValid) {
    std::cout << "Masukkan tidak valid!\n";
    isInputValid = handleInput(userInput);
  }

  auto startTime = high_resolution_clock::now();

  int permutedOps[64][3];
  float permutedInputs[24][4];

  permuteOperator(permutedOps);
  permuteInput(permutedInputs, userInput);

  for (int order = 0; order < 5; order++) {
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

  char solutionString[22];
  if (solutionCount > 0) {
    sprintf(solutionString, "%d solusi ditemukan\n", solutionCount);
    std::cout << solutionCount << " solusi ditemukan\n";
    for (std::string s : resultArray) {
      std::cout << s;
    }
  } else {
    sprintf(solutionString, "Tidak ada solusi yang ditemukan\n");
    std::cout << "Tidak ada solusi yang ditemukan\n";
  }

  int tempInput;
  std::cout << "Ketik 1 untuk menyimpan hasil ke file\nKetik 2 untuk keluar "
               "dari program\n";
  std::cin >> tempInput;

  while (tempInput != 1 && tempInput != 2) {
    std::cout << "Masukkan tidak valid!\n";
    std::cout << "Ketik 1 untuk menyimpan hasil ke file\nKetik 2 untuk keluar "
                 "dari program\n";
    std::cin >> tempInput;
  }

  if (tempInput == 1) {
    std::string fileName;
    std::cout << "Nama file: ";
    std::cin >> fileName;
    std::string filePath = "./test/" + fileName;
    writeToFile(filePath, resultArray, (std::string) solutionString, userInput);
    std::cout << "Berhasil menyimpan hasil ke file\n";
  }

  microseconds execTime = duration_cast<microseconds>(stopTime - startTime);
  printf("Waktu eksekusi algoritma: %ld microseconds\n", execTime.count());

  return 0;
}