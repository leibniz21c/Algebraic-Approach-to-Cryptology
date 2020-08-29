/* 
    Brute Force Attacker 
    to additive cipher

    Additive Cipher 해독을 위한
    무차별 대입 공격 프로그램

    Usage :
    atk_add codetext plaintext

    시간이 없어서 대충만들었습니다.
    코드 참고시 양해바랍니다.
*/

#include <stdio.h>
#include <stdlib.h>

void found(unsigned long long int cntOp, int k);

int main(int argc, char *argv[]) 
{
    int k = 0, i, codeChar, decodeChar, plainChar;
    unsigned long long int cntOp = 0;
    FILE * codefp;
    FILE * plainfp;
    FILE * decodefp;
    
    for ( k = 0 ; k < 26 ; k ++) {
        decodefp = fopen("decode_add.txt", "w");
        codefp = fopen(argv[1], "r");
        while ( (codeChar = fgetc(codefp)) != EOF ) {
            cntOp ++;
            decodeChar = 'A' + (codeChar - 'A' - k + 26)%26;
            fputc(decodeChar, decodefp);
        }
        fclose(decodefp);
        fclose(codefp);

        decodefp = fopen("decode_add.txt", "r");
        plainfp = fopen(argv[2], "r");
        while ( 1 ) {
            if ( (decodeChar = fgetc(decodefp)) == EOF) {
                fclose(decodefp);
                fclose(plainfp);
                found(cntOp, k);
            }
            plainChar = fgetc(plainfp);

            if ( decodeChar != plainChar) break;
        }
        fclose(decodefp);
        fclose(codefp);
    }

    printf("Cipher Breaking Failed\nNumber of Operations : %llu\n", cntOp);
    return 1;
}
void found(unsigned long long int cntOp, int k)
{
    printf("Cipher Breaking Completed\nNumber of Operations : %llu\nkey = %d\n", cntOp, k);
    exit(EXIT_SUCCESS);
}