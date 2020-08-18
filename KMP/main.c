#include <stdio.h>
#include <string.h>

#define MAX 100

int lps[MAX] = {0,};

void makeLPS(char *pattern);
void KMP(char *parent , char *pattern);

int main(void)
{
    char *pattern = "sawqfwfnonwqidonwdiosawqfwf";
    char *string = "gewgweggewgsawqfwfnonwqidonwdiosawqfwfgewnlgewjgkekbgekjsawqfwfnonwqidonwdiosawqfwf";
    KMP(string, pattern);
    
    return 0;
    
}

void makeLPS(char *pattern)
{
    int patternSize = strlen(pattern);
    int j = 0;
    for(int i = 0; i < patternSize; i++)
    {
        while(j>0 && pattern[i] != pattern[j])
        {
            j = lps[j-1];
        }
        if(pattern[i] == pattern[j])
            *(lps+j) = ++j;
    }
}
void KMP(char *parent , char *pattern)
{
    int parentSize = strlen(parent);
    int patternSize = strlen(pattern);
    int j = 0;
    makeLPS(pattern);
    
    for(int i =0; i<parentSize; i++)
    {
        while(j>0 && parent[i] != pattern[j])
            j = lps[j-1];
        
        if(parent[i] == pattern[j])
        {
            if(j == patternSize -1)
            {
                printf("%d 번째 에서 찾았습니다\n", i - patternSize +2);
                j = lps[j];
            }
            else
            {
                j++;
            }
        }
    }
    
    
    
}
