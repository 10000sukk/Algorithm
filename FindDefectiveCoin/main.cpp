#include "balance.h"
#include <iostream>
using namespace std;

int a[2] = { 0 }; int b[2] = { 0 }; int c[2] = { 0 }; // 하나씩 올릴때 이용할 배열
int aa[4] = { 0 }; int bb[4] = { 0 }; int cc[4] = { 0 }; // 세개씩 올릴때 이용할 배열
int aaa[10] = { 0 }; int bbb[10] = { 0 }; int ccc[10] = { 0 };// 9개씩 올릴때 이용할 배열
int aaaa[28] = { 0 }; int bbbb[28] = { 0 }; int cccc[28] = { 0 };
int threeCoinStatus[33] = { 0 }; // 동전을 3개씩 묶었을때 그 묶음의 상태를 나타냄 0이면 아직 모른다 1이면 상태파악완료 2이면 모두 진짜는 아니다 3이면 모두 가짜는 아니다
int n1 = 0;
int trueCoinIndex;
int falseCoinIndex;
int sampleProbability; //표본 확률
int trueNum = 0; //인덱스가 3*i 미만인 진짜동전의 갯수
int falseNum = 0; // 인덱스가 3*i 미만인 가짜동전의 갯수
int coin[100];//우리가 판별한 동전을 저장할 배열 -1이면 아직 모른다 0이면 가짜동전 1이면 진짜동전

int samPro(int i) {
    trueNum = 0; //인덱스가 3*i 미만인 진짜동전의 갯수
    falseNum = 0; // 인덱스가 3*i 미만인 가짜동전의 갯수
    for (int j = 0; j < 3 * i; j++) {
        if (coin[j] == 0) {
            falseNum++;
        }
        else if (coin[j] == 1) {
            trueNum++;
        }
    }
    sampleProbability = (100 * falseNum) / (falseNum + trueNum);
    return sampleProbability;
}

int main() {

    initialize(50);

    a[1] = -1; b[1] = -1; c[1] = -1;
    aa[3] = -1; bb[3] = -1; cc[3] = -1;
    aaa[9] = -1; bbb[9] = -1; ccc[9] = -1;
    aaaa[27] = -1; bbbb[27] = -1; cccc[27] = -1;
    for (int i = 0; i < 100; i++) {
        coin[i] = -1;
    }

    //여기부터 저울질 시작
    int i;
    for (i = 0; i < 33; i++) {

        //최소 12개는 상태 파악후에 통계 표본 얻을려고 break한다
        if (i > 5) {
            break;
        }

        if (threeCoinStatus[i] != 1) {
            a[0] = 3 * i;
            b[0] = 3 * i + 1;
            c[0] = 3 * i + 2;

            switch (balance(a, b, c))
            {
            case A:
                coin[a[0]] = 1; coin[b[0]] = 0; coin[c[0]] = 0; threeCoinStatus[i] = 1; break;

            case B:
                coin[a[0]] = 0; coin[b[0]] = 1; coin[c[0]] = 0; threeCoinStatus[i] = 1; break;

            case C:
                coin[a[0]] = 0; coin[b[0]] = 0; coin[c[0]] = 1; threeCoinStatus[i] = 1; break;

            case EQUAL_AB:
                coin[a[0]] = 1; coin[b[0]] = 1; coin[c[0]] = 0; threeCoinStatus[i] = 1; break;

            case EQUAL_AC:
                coin[a[0]] = 1; coin[b[0]] = 0; coin[c[0]] = 1; threeCoinStatus[i] = 1; break;

            case EQUAL_BC:
                coin[a[0]] = 0; coin[b[0]] = 1; coin[c[0]] = 1; threeCoinStatus[i] = 1; break;

            case EQUAL_ALL:

                if (threeCoinStatus[i] == 0 && (a[0] / 3 < 31)) {
                    aa[0] = 3 * i; aa[1] = 3 * i + 1; aa[2] = 3 * i + 2;
                    bb[0] = 3 * (i + 1); bb[1] = 3 * (i + 1) + 1; bb[2] = 3 * (i + 1) + 2;
                    cc[0] = 3 * (i + 2); cc[1] = 3 * (i + 2) + 1; cc[2] = 3 * (i + 2) + 2;

                    switch (balance(aa, bb, cc))
                    {
                    case A:
                        coin[aa[0]] = 1; coin[aa[1]] = 1; coin[aa[2]] = 1; threeCoinStatus[i] = 1; break;

                    case B:
                        coin[aa[0]] = 0; coin[aa[1]] = 0; coin[aa[2]] = 0; threeCoinStatus[i] = 1; threeCoinStatus[i + 1] = 3; threeCoinStatus[i + 2] = 2; break;

                    case C:
                        coin[aa[0]] = 0; coin[aa[1]] = 0; coin[aa[2]] = 0; threeCoinStatus[i] = 1; threeCoinStatus[i + 1] = 2; threeCoinStatus[i + 2] = 3; break;

                    case EQUAL_AB:
                        coin[aa[0]] = 1; coin[aa[1]] = 1; coin[aa[2]] = 1; threeCoinStatus[i] = 1;
                        coin[bb[0]] = 1; coin[bb[1]] = 1; coin[bb[2]] = 1; threeCoinStatus[i + 1] = 1; threeCoinStatus[i + 2] = 2; break;

                    case EQUAL_AC:
                        coin[aa[0]] = 1; coin[aa[1]] = 1; coin[aa[2]] = 1; threeCoinStatus[i] = 1;
                        coin[cc[0]] = 1; coin[cc[1]] = 1; coin[cc[2]] = 1; threeCoinStatus[i + 2] = 1; threeCoinStatus[i + 1] = 2; break;

                    case EQUAL_BC:
                        coin[aa[0]] = 0; coin[aa[1]] = 0; coin[aa[2]] = 0; threeCoinStatus[i] = 1; threeCoinStatus[i + 1] = 3; threeCoinStatus[i + 2] = 3; break;

                    case EQUAL_ALL:
                        aaa[0] = aa[0]; aaa[1] = aa[1]; aaa[2] = aa[2]; aaa[3] = bb[0]; aaa[4] = bb[1]; aaa[5] = bb[2]; aaa[6] = cc[0]; aaa[7] = cc[1]; aaa[8] = cc[2];
                        bbb[0] = cc[2] + 1; bbb[1] = bbb[0] + 1; bbb[2] = bbb[1] + 1; bbb[3] = bbb[2] + 1; bbb[4] = bbb[3] + 1; bbb[5] = bbb[4] + 1; bbb[6] = bbb[5] + 1;
                        bbb[7] = bbb[6] + 1; bbb[8] = bbb[7] + 1;
                        ccc[0] = bbb[8] + 1; ccc[1] = ccc[0] + 1; ccc[2] = ccc[1] + 1; ccc[3] = ccc[2] + 1; ccc[4] = ccc[3] + 1; ccc[5] = ccc[4] + 1; ccc[6] = ccc[5] + 1;
                        ccc[7] = ccc[6] + 1; ccc[8] = ccc[7] + 1;

                        switch (balance(aaa, bbb, ccc))
                        {
                        case A:
                            coin[aaa[0]] = 1; coin[aaa[1]] = 1; coin[aaa[2]] = 1; coin[aaa[3]] = 1; coin[aaa[4]] = 1; coin[aaa[5]] = 1; coin[aaa[6]] = 1; coin[aaa[7]] = 1;
                            coin[aaa[8]] = 1; threeCoinStatus[aaa[0] / 3] = 1; threeCoinStatus[aaa[3] / 3] = 1; threeCoinStatus[aaa[6] / 3] = 1; break;

                        case B:
                            coin[aaa[0]] = 0; coin[aaa[1]] = 0; coin[aaa[2]] = 0; coin[aaa[3]] = 0; coin[aaa[4]] = 0; coin[aaa[5]] = 0; coin[aaa[6]] = 0; coin[aaa[7]] = 0;
                            coin[aaa[8]] = 0; threeCoinStatus[aaa[0] / 3] = 1; threeCoinStatus[aaa[3] / 3] = 1; threeCoinStatus[aaa[6] / 3] = 1; break;

                        case C:
                            coin[aaa[0]] = 0; coin[aaa[1]] = 0; coin[aaa[2]] = 0; coin[aaa[3]] = 0; coin[aaa[4]] = 0; coin[aaa[5]] = 0; coin[aaa[6]] = 0; coin[aaa[7]] = 0;
                            coin[aaa[8]] = 0; threeCoinStatus[aaa[0] / 3] = 1; threeCoinStatus[aaa[3] / 3] = 1; threeCoinStatus[aaa[6] / 3] = 1; break;

                        case EQUAL_AB:
                            coin[aaa[0]] = 1; coin[aaa[1]] = 1; coin[aaa[2]] = 1; coin[aaa[3]] = 1; coin[aaa[4]] = 1; coin[aaa[5]] = 1; coin[aaa[6]] = 1; coin[aaa[7]] = 1;
                            coin[aaa[8]] = 1; threeCoinStatus[aaa[0] / 3] = 1; threeCoinStatus[aaa[3] / 3] = 1; threeCoinStatus[aaa[6] / 3] = 1;

                            coin[bbb[0]] = 1; coin[bbb[1]] = 1; coin[bbb[2]] = 1; coin[bbb[3]] = 1; coin[bbb[4]] = 1; coin[bbb[5]] = 1; coin[bbb[6]] = 1; coin[bbb[7]] = 1;
                            coin[bbb[8]] = 1; threeCoinStatus[bbb[0] / 3] = 1; threeCoinStatus[bbb[3] / 3] = 1; threeCoinStatus[bbb[6] / 3] = 1; break;

                        case EQUAL_AC:
                            coin[aaa[0]] = 1; coin[aaa[1]] = 1; coin[aaa[2]] = 1; coin[aaa[3]] = 1; coin[aaa[4]] = 1; coin[aaa[5]] = 1; coin[aaa[6]] = 1; coin[aaa[7]] = 1;
                            coin[aaa[8]] = 1; threeCoinStatus[aaa[0] / 3] = 1; threeCoinStatus[aaa[3] / 3] = 1; threeCoinStatus[aaa[6] / 3] = 1;

                            coin[ccc[0]] = 1; coin[ccc[1]] = 1; coin[ccc[2]] = 1; coin[ccc[3]] = 1; coin[ccc[4]] = 1; coin[ccc[5]] = 1; coin[ccc[6]] = 1; coin[ccc[7]] = 1;
                            coin[ccc[8]] = 1; threeCoinStatus[ccc[0] / 3] = 1; threeCoinStatus[ccc[3] / 3] = 1; threeCoinStatus[ccc[6] / 3] = 1; break;

                        case EQUAL_BC:
                            coin[aaa[0]] = 0; coin[aaa[1]] = 0; coin[aaa[2]] = 0; coin[aaa[3]] = 0; coin[aaa[4]] = 0; coin[aaa[5]] = 0; coin[aaa[6]] = 0; coin[aaa[7]] = 0;
                            coin[aaa[8]] = 0; threeCoinStatus[aaa[0] / 3] = 1; threeCoinStatus[aaa[3] / 3] = 1; threeCoinStatus[aaa[6] / 3] = 1; break;

                        case EQUAL_ALL:

                            for (int j = 0; j < 27; j++) {
                                aaaa[j] = aaa[0] + j;
                            }

                            for (int j = 0; j < 27; j++) {
                                bbbb[j] = aaaa[j] + 27;
                            }

                            for (int j = 0; j < 27; j++) {
                                cccc[j] = bbbb[j] + 27;
                            }

                            switch (balance(aaaa, bbbb, cccc))
                            {
                            case A:
                                for (int j = 0; j < 27; j++) {
                                    coin[aaaa[j]] = 1;
                                    threeCoinStatus[(int)aaaa[j] / 3] = 1;
                                }
                                break;

                            case B:
                                for (int j = 0; j < 27; j++) {
                                    coin[aaaa[j]] = 0;
                                    threeCoinStatus[(int)aaaa[j] / 3] = 1;
                                }
                                break;
                            case C:
                                for (int j = 0; j < 27; j++) {
                                    coin[aaaa[j]] = 0;
                                    threeCoinStatus[(int)aaaa[j] / 3] = 1;
                                }
                                break;

                            case EQUAL_AB:
                                for (int j = 0; j < 27; j++) {
                                    coin[aaaa[j]] = 1;
                                    threeCoinStatus[(int)aaaa[j] / 3] = 1;
                                }
                                for (int j = 0; j < 27; j++) {
                                    coin[bbbb[j]] = 1;
                                    threeCoinStatus[(int)bbbb[j] / 3] = 1; break;
                                }
                                break;

                            case EQUAL_AC:
                                for (int j = 0; j < 27; j++) {
                                    coin[aaaa[j]] = 1;
                                    threeCoinStatus[(int)aaaa[j] / 3] = 1;
                                }
                                for (int j = 0; j < 27; j++) {
                                    coin[cccc[j]] = 1;
                                    threeCoinStatus[(int)cccc[j] / 3] = 1; break;
                                }
                                break;
                            case EQUAL_BC:
                                for (int j = 0; j < 27; j++) {
                                    coin[aaaa[j]] = 0;
                                    threeCoinStatus[(int)aaaa[j] / 3] = 1;
                                }
                                break;

                            case EQUAL_ALL:
                                for (int k = 0; k < 90; k++) {
                                    if (coin[k] == 1 && 3 * i != k) {
                                        trueCoinIndex = k;
                                        break;
                                    }
                                }
                                a[0] = trueCoinIndex; b[0] = bbbb[0]; c[0] = cccc[0];
                                switch (balance(a, b, c))
                                {
                                case A:
                                    for (int j = 0; j < 27; j++) {
                                        coin[aaaa[j]] = 0;
                                        coin[bbbb[j]] = 0;
                                        coin[cccc[j]] = 0;
                                        threeCoinStatus[(int)aaaa[j] / 3] = 1;
                                        threeCoinStatus[(int)bbbb[j] / 3] = 1;
                                        threeCoinStatus[(int)cccc[j] / 3] = 1;
                                    }
                                case EQUAL_ALL:
                                    for (int j = 0; j < 27; j++) {
                                        coin[aaaa[j]] = 1;
                                        coin[bbbb[j]] = 1;
                                        coin[cccc[j]] = 1;
                                        threeCoinStatus[(int)aaaa[j] / 3] = 1;
                                        threeCoinStatus[(int)bbbb[j] / 3] = 1;
                                        threeCoinStatus[(int)cccc[j] / 3] = 1;
                                    }

                                }

                            }






                        }


                    }


                }
                else if (threeCoinStatus[i] != 0) {
                    if (threeCoinStatus[i] == 2) {
                        coin[3 * i] = 0; coin[3 * i + 1] = 0; coin[3 * i + 2] = 0; threeCoinStatus[i] = 1;
                    }
                    else if (threeCoinStatus[i] == 3) {
                        coin[3 * i] = 1; coin[3 * i + 1] = 1; coin[3 * i + 2] = 1; threeCoinStatus[i] = 1;
                    }
                }

            }

        }
        else if (threeCoinStatus[i] == 1)
            continue;
    }


    //여기부터 샘플확률을 이용한 판별
    for (i = 0; i < 33; i++) {
        if (threeCoinStatus[i] == 1) {
            continue;
        }
        else {
            a[0] = 3 * i;
            b[0] = 3 * i + 1;
            c[0] = 3 * i + 2;

            switch (balance(a, b, c))
            {
            case A:
                coin[a[0]] = 1; coin[b[0]] = 0; coin[c[0]] = 0; threeCoinStatus[i] = 1; break;

            case B:
                coin[a[0]] = 0; coin[b[0]] = 1; coin[c[0]] = 0; threeCoinStatus[i] = 1; break;

            case C:
                coin[a[0]] = 0; coin[b[0]] = 0; coin[c[0]] = 1; threeCoinStatus[i] = 1; break;

            case EQUAL_AB:
                coin[a[0]] = 1; coin[b[0]] = 1; coin[c[0]] = 0; threeCoinStatus[i] = 1; break;

            case EQUAL_AC:
                coin[a[0]] = 1; coin[b[0]] = 0; coin[c[0]] = 1; threeCoinStatus[i] = 1; break;

            case EQUAL_BC:
                coin[a[0]] = 0; coin[b[0]] = 1; coin[c[0]] = 1; threeCoinStatus[i] = 1; break;

            case EQUAL_ALL:

                if (threeCoinStatus[i] == 0 && (a[0] / 3 < 31)) {
                    aa[0] = 3 * i; aa[1] = 3 * i + 1; aa[2] = 3 * i + 2;
                    bb[0] = 3 * (i + 1); bb[1] = 3 * (i + 1) + 1; bb[2] = 3 * (i + 1) + 2;
                    cc[0] = 3 * (i + 2); cc[1] = 3 * (i + 2) + 1; cc[2] = 3 * (i + 2) + 2;

                    switch (balance(aa, bb, cc))
                    {
                    case A:
                        coin[aa[0]] = 1; coin[aa[1]] = 1; coin[aa[2]] = 1; threeCoinStatus[i] = 1; break;

                    case B:
                        coin[aa[0]] = 0; coin[aa[1]] = 0; coin[aa[2]] = 0; threeCoinStatus[i] = 1; threeCoinStatus[i + 1] = 3; threeCoinStatus[i + 2] = 2; break;

                    case C:
                        coin[aa[0]] = 0; coin[aa[1]] = 0; coin[aa[2]] = 0; threeCoinStatus[i] = 1; threeCoinStatus[i + 1] = 2; threeCoinStatus[i + 2] = 3; break;

                    case EQUAL_AB:
                        coin[aa[0]] = 1; coin[aa[1]] = 1; coin[aa[2]] = 1; threeCoinStatus[i] = 1;
                        coin[bb[0]] = 1; coin[bb[1]] = 1; coin[bb[2]] = 1; threeCoinStatus[i + 1] = 1; threeCoinStatus[i + 2] = 2; break;

                    case EQUAL_AC:
                        coin[aa[0]] = 1; coin[aa[1]] = 1; coin[aa[2]] = 1; threeCoinStatus[i] = 1;
                        coin[cc[0]] = 1; coin[cc[1]] = 1; coin[cc[2]] = 1; threeCoinStatus[i + 2] = 1; threeCoinStatus[i + 1] = 2; break;

                    case EQUAL_BC:
                        coin[aa[0]] = 0; coin[aa[1]] = 0; coin[aa[2]] = 0; threeCoinStatus[i] = 1; threeCoinStatus[i + 1] = 3; threeCoinStatus[i + 2] = 3; break;

                    case EQUAL_ALL:
                        if (samPro(i) <= 40) {
                            for (int j = 0; j < 9; j++) {
                                coin[3 * i + j] = 1;
                                threeCoinStatus[(3 * i + j) / 3] = 1;

                            }
                        }
                        else if (samPro(i) >= 60) {
                            for (int j = 0; j < 9; j++) {
                                coin[3 * i + j] = 0;
                                threeCoinStatus[(3 * i + j) / 3] = 1;

                            }

                        }
                        else {

                            for (int k = 0; k < 90; k++) {
                                if (coin[k] == 1 && k != aa[0]) {
                                    trueCoinIndex = k;
                                    break;
                                }
                            }
                            a[0] = trueCoinIndex; b[0] = bb[0]; c[0] = cc[0];
                            switch (balance(a, b, c))
                            {
                            case A:
                                coin[aa[0]] = 0; coin[aa[1]] = 0; coin[aa[2]] = 0; threeCoinStatus[i] = 1;
                                coin[bb[0]] = 0; coin[bb[1]] = 0; coin[bb[2]] = 0; threeCoinStatus[i + 1] = 1;
                                coin[cc[0]] = 0; coin[cc[1]] = 0; coin[cc[2]] = 0; threeCoinStatus[i + 2] = 1; break;
                            case EQUAL_ALL:
                                coin[aa[0]] = 1; coin[aa[1]] = 1; coin[aa[2]] = 1; threeCoinStatus[i] = 1;
                                coin[bb[0]] = 1; coin[bb[1]] = 1; coin[bb[2]] = 1; threeCoinStatus[i + 1] = 1;
                                coin[cc[0]] = 1; coin[cc[1]] = 1; coin[cc[2]] = 1; threeCoinStatus[i + 2] = 1; break;
                            }
                        }



                    }

                }
                else if (threeCoinStatus[i] != 0) {
                    if (threeCoinStatus[i] == 2) {
                        coin[3 * i] = 0; coin[3 * i + 1] = 0; coin[3 * i + 2] = 0; threeCoinStatus[i] = 1;
                    }
                    else if (threeCoinStatus[i] == 3) {
                        coin[3 * i] = 1; coin[3 * i + 1] = 1; coin[3 * i + 2] = 1; threeCoinStatus[i] = 1;
                    }
                }
                if (threeCoinStatus[i] == 0 && i > 30) {
                    if (samPro(i) <= 25) {
                        coin[3 * i] = 1; coin[3 * i + 1] = 1; coin[3 * i + 2] = 1; threeCoinStatus[i] = 1;
                    }
                    else if (samPro(i) >= 75) {
                        coin[3 * i] = 0; coin[3 * i + 1] = 0; coin[3 * i + 2] = 0; threeCoinStatus[i] = 1;
                    }
                    else if (samPro(i) > 25 && samPro(i) < 75) {

                        for (int k = 0; k < 90; k++) {
                            if (coin[k] == 1 && 3 * i != k) {
                                trueCoinIndex = k;
                                break;
                            }
                        }

                        a[0] = trueCoinIndex; b[0] = 99; c[0] = 3 * i + 1;

                        switch (balance(a, b, c))
                        {
                        case A:
                            coin[3 * i] = 0; coin[3 * i + 1] = 0; coin[3 * i + 2] = 0; threeCoinStatus[i] = 1; coin[99] = 0; break;

                        case EQUAL_AB:
                            coin[3 * i] = 0; coin[3 * i + 1] = 0; coin[3 * i + 2] = 0; threeCoinStatus[i] = 1; coin[99] = 1; break;

                        case EQUAL_AC:
                            coin[3 * i] = 1; coin[3 * i + 1] = 1; coin[3 * i + 2] = 1; threeCoinStatus[i] = 1; coin[99] = 0; break;
                        case EQUAL_ALL:
                            coin[3 * i] = 1; coin[3 * i + 1] = 1; coin[3 * i + 2] = 1; threeCoinStatus[i] = 1; coin[99] = 1; break;

                        }
                    }
                }
            }
        }
    }

    //마지막 남은 동전한잎 판별
    if (coin[99] == -1) {
        for (int k = 0; k < 90; k++) {
            if (coin[k] == 1) {
                trueCoinIndex = k;
                break;
            }
        }
        for (int k = 0; k < 90; k++) {
            if (coin[k] == 0) {
                falseCoinIndex = k;
                break;
            }
        }
        a[0] = trueCoinIndex; b[0] = falseCoinIndex; c[0] = 99;
        switch (balance(a, b, c))
        {
        case A:
            coin[99] = 0; break;

        case EQUAL_AC:
            coin[99] = 1; break;
        }
    }

    printf("불량동전의 인덱스 출력\n");
    for (int i = 0; i < 100; i++) {
        if (coin[i] == 0) {
            printf("%d  ,", i);
        }
    }

    int n4 = 0;
    int resultFalseCoin[100] = { 0 };
    b[0] = -1; c[0] = -1;
    for (int j = 0; j < 100; j++) {
        if (coin[j] == 0) {
            resultFalseCoin[n4++] = j;
        }
    }
    resultFalseCoin[n4] = -1;
    balance(resultFalseCoin, b, c);
    printf(" 마지막 표본 확률 = %d ", sampleProbability);
}



