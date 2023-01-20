#include <iostream>
#include <map>
#include <tuple>

// Fungsi untuk melakukan perhitungan val1 op val2
std::tuple<float, bool> calc(float val1, float val2, int op) {
  float x;
  switch (op) {
    case 0:
      x = val1 + val2;
      break;
    case 1:
      x = val1 - val2;
      break;
    case 2:
      x = val1 * val2;
      break;
    case 3:
      if (val2 == 0) {
        x = 0;
        return std::make_tuple(x, false);
      } else {
        x = val1 / val2;
      }
      break;
    default:
      x = 0;
  }
  return std::make_tuple(x, true);
}

// Fungsi untuk menghasilkan semua kemungkinan permutasi operator
void permuteOperator(int arr[64][3]) {
  int n = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        arr[n][0] = i;
        arr[n][1] = j;
        arr[n][2] = k;
        n++;
      }
    }
  }
}

// Fungsi untuk menghasilkan semua kemungkinan permutasi input
void permuteInput(float arrOutput[24][4], float arrInput[4]) {
  int n = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        for (int l = 0; l < 4; l++) {
          if (i == j || i == k || i == l || j == k || j == l || k == l) {
            continue;
          } else {
            arrOutput[n][0] = arrInput[i];
            arrOutput[n][1] = arrInput[j];
            arrOutput[n][2] = arrInput[k];
            arrOutput[n][3] = arrInput[l];
            n++;
          }
        }
      }
    }
  }
}

// Fungsi untuk menampilkan operasi ke layar
void showOperation(float num[4], int op[3], int order) {
  char temp[4] = {'+', '-', '*', '/'};
  switch (order) {
    case 0:
      printf("((%d %c %d) %c %d) %c %d\n", int(num[0]), temp[op[0]],
             int(num[1]), temp[op[1]], int(num[2]), temp[op[2]], int(num[3]));
      break;
    case 1:
      printf("(%d %c (%d %c %d)) %c %d\n", int(num[0]), temp[op[1]],
             int(num[1]), temp[op[0]], int(num[2]), temp[op[2]], int(num[3]));
      break;
    case 2:
      printf("%d %c ((%d %c %d) %c %d)\n", int(num[0]), temp[op[2]],
             int(num[1]), temp[op[0]], int(num[2]), temp[op[1]], int(num[3]));
      break;
    case 3:
      printf("%d %c (%d %c (%d %c %d))\n", int(num[0]), temp[op[2]],
             int(num[1]), temp[op[1]], int(num[2]), temp[op[0]], int(num[3]));
      break;
    case 4:
      printf("(%d %c %d) %c (%d %c %d)\n", int(num[0]), temp[op[0]],
             int(num[1]), temp[op[2]], int(num[2]), temp[op[1]], int(num[3]));
      break;
  }
}

// Fungsi untuk menerima masukkan pengguna
bool handleInput(float inputArr[4]) {
  std::map<std::string, float> inputMap;
  inputMap["A"] = 1.0;
  inputMap["2"] = 2.0;
  inputMap["3"] = 3.0;
  inputMap["4"] = 4.0;
  inputMap["5"] = 5.0;
  inputMap["6"] = 6.0;
  inputMap["7"] = 7.0;
  inputMap["8"] = 8.0;
  inputMap["9"] = 9.0;
  inputMap["10"] = 10.0;
  inputMap["J"] = 11.0;
  inputMap["Q"] = 12.0;
  inputMap["K"] = 13.0;

  for (int i = 0; i < 4; i++) {
    std::string temp;
    std::cin >> temp;

    if (inputMap.find(temp) == inputMap.end()) {
      return false;
    }

    inputArr[i] = inputMap[temp];
  }
  return true;
}