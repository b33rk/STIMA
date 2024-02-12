#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

void printMatrix(const vector<vector<string>>& matrix) {
    for (const auto& row : matrix) {
        for (const string& value : row) {
            cout << value << ' ';
        }
        cout << endl;
    }
}

int getTotalValue(int SequenceAmount, 
                vector<vector<string>>& matrixSequence, 
                vector<string>& arrayCode, 
                vector<int>& arrayRewards, 
                vector<int>& listSequenceLength, 
                int buff) {
    int totalReward = 0;
    for (int i = 0; i < SequenceAmount; i++){
        vector<int> vectorRow;
        int count = 0;
        int indexCode = 0;
        bool found = false;
        while (indexCode < buff && !found) {
            if (matrixSequence[i][count] == arrayCode[indexCode]) {
                count++;
            } else {
                count = 0;
            }
            if (count == listSequenceLength[i]) {
                totalReward += arrayRewards[i];
                found = true;
            }
            indexCode++;
        }
    }
    return totalReward;
}

void generateNumbers(int SequenceAmount, 
                    vector<string>& arrayCode2, 
                    vector<int>& arrayDigit2, 
                    vector<int>& arrayDigit, 
                    vector<vector<string>>& matrixCode, 
                    vector<vector<string>>& matrixSequence, 
                    vector<int>& arrayRewards, 
                    vector<int>& listSequenceLength, 
                    bool isVertical, 
                    int x, int buff, 
                    int row, int col,
                    int currentRow, 
                    int currentCol, 
                    vector<string>& arrayCode, 
                    int* max) {
    int currentMaxValue;
    int c;
    if (x == 0) {
        int reward = getTotalValue(SequenceAmount, 
                                matrixSequence, 
                                arrayCode, arrayRewards, 
                                listSequenceLength, buff);
        if (reward > *max) {
            *max = reward;
            arrayCode2.clear();
            arrayDigit2.clear();
            for (int i = 0; i < buff; i++) {
                arrayCode2.push_back(arrayCode[i]);
                arrayDigit2.push_back(arrayDigit[i]);
            }
        }
        return;
    }
    if (isVertical) {
        currentMaxValue = row;
        c = currentRow;
    } else {
        currentMaxValue = col;
        c = currentCol;
    }
    for (int digit = 0 ; digit < currentMaxValue; digit++) {
        if (digit != c) {
            arrayCode.push_back(matrixCode[currentRow][currentCol]);
            arrayDigit.push_back(digit);
            if (isVertical) {
                currentRow = digit;
            } else {
                currentCol = digit;
            }
            generateNumbers(SequenceAmount,
                            arrayCode2, 
                            arrayDigit2, 
                            arrayDigit, matrixCode, 
                            matrixSequence, arrayRewards, 
                            listSequenceLength, 
                            !isVertical, 
                            x - 1, buff, 
                            row, col, 
                            currentRow, currentCol, 
                            arrayCode, max);
            arrayCode.pop_back();
            arrayDigit.pop_back();
        }
    }
}

bool isVectorInMatrix (vector<string> v, vector<vector<string>> matrix, int rowMatrix) {
    for (int i = 0; i < rowMatrix; i++) {
        if (v == matrix[i]) {
            return true;
        }
    }
    return false;
}

void randomize(vector<vector<string>>& matrixCode,
            int* SequenceAmount, 
            int* buff, int* row, int* col, 
            vector<vector<string>>& matrixSequence, 
            vector<int>& listRewardsAmount, 
            vector<int>& listSequenceLength, 
            int* minSequenceLength) {
    int amountToken;
    int maxSequenceLength;
    vector<string> listToken;
    string token;
    cin >> amountToken;
    for (int i = 0; i < amountToken; i++) {
        cin >> token;
        listToken.push_back(token);
    }
    cin >> *buff;
    *minSequenceLength = *buff;

    cin >> *row;
    cin >> *col;
    cin >> *SequenceAmount;
    cin >> maxSequenceLength;

    cout << endl << "Hasil matriks acak: " << endl;

    random_device rd;
    mt19937 eng(rd());

    for (int i = 0; i < *row; i++) {
        vector<string> rowMatrixCode;
        for (int j = 0; j < *col; j++) {
            uniform_int_distribution<int> distr(0, amountToken - 1);
            int index = distr(eng);
            token = listToken[index];
            cout << token << " ";
            rowMatrixCode.push_back(token);
        }
        cout << endl;
        matrixCode.push_back(rowMatrixCode);
    }

    cout << endl << "Sequence acak dan reward-nya: " << endl;
    for (int i = 0; i < *SequenceAmount; i++) {
        uniform_int_distribution<int> distr(2, maxSequenceLength - 1);
        int sequenceLength = distr(eng);
        if (sequenceLength < *minSequenceLength) {
            *minSequenceLength = sequenceLength;
        }
        bool found = false;

        listSequenceLength.push_back(sequenceLength);

        vector<string> rowMatrixSequence;
        while (found || rowMatrixSequence.empty()) {
            rowMatrixSequence.clear();
            for (int j = 0; j < sequenceLength; j++) {
                uniform_int_distribution<int> distr2(0, amountToken - 1);
                token = listToken[distr2(eng)];
                rowMatrixSequence.push_back(token);
            }
            found = isVectorInMatrix(rowMatrixSequence, matrixSequence, i);
        }
        for (int j = 0; j < sequenceLength; j++) {
            cout << rowMatrixSequence[j] << " ";
        }
        cout << endl;

        uniform_int_distribution<int> distr3(0, 50);
        int rewardAmount = distr3(eng);
        cout << rewardAmount << endl;

        matrixSequence.push_back(rowMatrixSequence);
        listRewardsAmount.push_back(rewardAmount);
    }
    
}

int main() {
    string line;
    int i = 1;
    int buff;
    int row;
    int col;
    vector<vector<string>> matrixCode;
    int SequenceAmount;
    vector<vector<string>> matrixSequence;
    vector<int> listRewardsAmount;
    vector<int> listSequenceLength;
    int minSequenceLength;
    int input;

    cout << "Pilih input yang ingin digunakan (1 atau 2):" << endl << "1. File" << endl << "2. Randomize" << endl;
    cin >> input;

    if (input == 1) {
        string filename;

        cout << "Masukkan nama file : "; 
        cin >> filename;
        ifstream inputfile (filename);

        while (!inputfile.is_open()) {
            cout << "Nama file tidak valid!" << endl;
            cout << "Masukkan Nama file : ";
            cin >> filename;
            inputfile.open(filename);
        }

        while (getline(inputfile, line)) {
            if (i == 1) {
                buff = stoi(line);
                minSequenceLength = buff;
            } else if (i == 2) {
                row = line[0] - '0';
                col = line[2] - '0';
            } else if ( i < row + 3) {
                vector<string> rowMatrix;
                int c = 0;
                int indexRow = 0;
                
                while (indexRow < col) {
                    rowMatrix.push_back(line.substr(c,2));
                    c += 3;
                    indexRow++;
                }

                matrixCode.push_back(rowMatrix);
            } else if (i == row + 3) {
                SequenceAmount = stoi(line);
            } else {
                vector<string> rowMatrixtRewards;
                int count = 0;
                if ((i - (row + 3)) % 2 == 1) {
                    int c = 0;
                    int length = line.length();
                    if (length < minSequenceLength) {
                        minSequenceLength = length;
                    }
                    while(c < length){
                        rowMatrixtRewards.push_back(line.substr(c,2));
                        c += 3;
                    }
                    matrixSequence.push_back(rowMatrixtRewards);
                    listSequenceLength.push_back((length + 1) / 3);
                } else {
                    listRewardsAmount.push_back(stoi(line));
                }
            }
            i++;
        }
        inputfile.close();
    } else {
        randomize(matrixCode, 
                &SequenceAmount, 
                &buff, &row, &col, 
                matrixSequence, 
                listRewardsAmount, 
                listSequenceLength, 
                &minSequenceLength);
    }

    cout << endl << "Hasil: " << endl;

    auto start = chrono :: high_resolution_clock :: now();
    vector<string> arrayCode;
    vector<string> arrayCode2;
    vector<string> arrayCodeFinal;
    vector<int> arrayDigit;
    vector<int> arrayDigit2;
    vector<int> arrayDigitFinal;
    int indexStartCol;
    int maxbuff;
    int max = 0;
    int value;

    for (int i = 0; i < col; i++) {
        for (int currentCodeLength = minSequenceLength; currentCodeLength <= buff; currentCodeLength++) {
            value = 0;
            arrayDigit.clear();
            arrayCode.clear();
            generateNumbers(SequenceAmount, 
                        arrayCode2, 
                        arrayDigit2, 
                        arrayDigit, matrixCode, 
                        matrixSequence, 
                        listRewardsAmount, 
                        listSequenceLength, true, 
                        currentCodeLength, currentCodeLength, 
                        row, col, 0, i, arrayCode, &value);
            if (value > max) {
                max = value;
                indexStartCol = i;
                maxbuff = currentCodeLength;
                arrayDigitFinal.clear();
                arrayCodeFinal.clear();
                for (int j = 0; j < currentCodeLength; j++) {
                    arrayDigitFinal.push_back(arrayDigit2[j]);
                    arrayCodeFinal.push_back(arrayCode2[j]);
                }
            }
        }
    }
    auto end = chrono :: high_resolution_clock :: now();
    auto duration = chrono :: duration_cast <chrono :: milliseconds> (end - start);
    int x = 1;
    int y = indexStartCol + 1;
    cout << max << endl;

    if (arrayDigitFinal.size() != 0) {
        for (int i = 0; i < maxbuff; i++) {
            cout << arrayCodeFinal[i] << " ";
        }
        cout << endl;
        cout << x << ", " << y << endl;
        for (int i = 0; i < maxbuff - 1; i++) {
            if (i % 2 == 0) {
                x = arrayDigitFinal[i] + 1;
            } else {
                y = arrayDigitFinal[i] + 1;
            }
            cout << x << ", " << y << endl;
        }
    }
    cout << endl;
    cout << duration.count() << "ms" << endl;
    cout << "Apakah ingin menyimpan solusi? (y/n)" << endl;

    char isSave;
    cin >> isSave;
    if (isSave == 'y') {
        string filename;
        cout << "Masukkan nama file: ";
        cin >> filename;
        ofstream outputFile(filename);

        while (!outputFile.is_open()) {
            cout << "Nama atau path file tidak valid!" << endl;
            cout << "Masukkan Nama file : ";
            cin >> filename;
            outputFile.open(filename);
        }
        outputFile << max << endl;
        for (int o = 0; o < maxbuff; o++) {
            outputFile << arrayCodeFinal[o] << " ";
        }
        outputFile << endl;

        if (arrayDigitFinal.size() != 0) {
            outputFile << 1 << ", " << y << endl;
            for (int o = 0; o < maxbuff - 1; o++) {
                if (o % 2 == 0) {
                    x = arrayDigitFinal[o] + 1;
                } else {
                    y = arrayDigitFinal[o] + 1;
                }
                outputFile << x << ", " << y << endl;
            }
        }
        outputFile << endl;
        outputFile << duration.count() << "ms";
        outputFile.close();
        cout << "Data berhasil tertulis ke file." << endl;
    }
}